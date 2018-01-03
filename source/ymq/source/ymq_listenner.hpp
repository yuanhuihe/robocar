#ifndef YMQ_LISTENNER_HPP_
#define YMQ_LISTENNER_HPP_

#include "_inl.hpp"
#include "ymq_socket.hpp"
#include <functional>
#include <mutex>
#include <vector>

namespace ymq
{
class ymq_listenner : public ymq_socket
{
  public:
    ymq_listenner(char* url)
    {
        this->kq_ = 0;
        this->running_ = false;
        this->obj_thread_ = nullptr;

        fn_received_data_ = nullptr;

        url_ = url;
        int p1 = url_.rfind('/') + 1;
        int p2 = url_.rfind(':');
        ip_ = url_.substr(p1, p2-p1);

        p2 += 1;
        std::string str_port = url_.substr(p2, url_.length()-p2);
        port_ = atoi(str_port.c_str());
    }
    virtual ~ymq_listenner()
    {
        stop();
    }

    void set_received_callback(fn_received_data_handle fn)
    {
        fn_received_data_ = fn;
    }

    virtual bool start()
    {
        stop();

        if(!ymq_socket::start()) return false;

        /* Create kqueue. */
        this->kq_ = kqueue();
        
        /* Create listener on port*/
        if(!create_listener(listen_port_))
        {
            return false;
        }

        /*Register events on kqueue*/
        register_event(kq_, sock_);
        
        /*Start events thread*/
        obj_thread_ = new std::thread(&ymq_listenner::process_event, this);

        return true;
    }

    virtual void stop()
    {
        ymq_socket::stop();

        running_ = false;
        if (obj_thread_)
        {
            close(kq_);
            obj_thread_->join();
            delete obj_thread_;
            obj_thread_ = nullptr;
        }
    }

    virtual int send(char* data, int data_len)
    {
        for(auto sock : clients_fd_)
        {
            ::send(sock, data, data_len, 0);
        }
    }

    virtual int recv(char* buff, int buff_len)
    {

    }

  private:
    void process_event()
    {
        struct kevent *events = new struct kevent[MAX_EVENT_COUNT];
        int ret = 0;
        running_ = true;
        while (running_)
        {
            //ret = accept(sock_, NULL, NULL);
            ret = kevent(kq_, NULL, 0, events, MAX_EVENT_COUNT, NULL);
            if(-1==ret)
            {
                continue;
            }

            handle_events(kq_, events, ret);
        }

        delete[] events;
    }

    bool create_listener(int port)
    {
        struct sockaddr_in addr;
        addr.sin_len = sizeof(addr);
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);

        int ret = ::bind(sock_, (struct sockaddr *)&addr, sizeof(struct sockaddr));
        if (ret == -1)
        {
            std::cerr << "bind()　failed:" << errno << std::endl;
            return false;
        }

        if( ::listen(sock_,5) == -1)
        {
            std::cerr << " listen()　failed:" << errno << std::endl;
            return false;
        }

        return true;
    }

    void handle_events(int kq, struct kevent *events, int nevents)
    {
        for (int i = 0; i < nevents; i++)
        {
            int sock = events[i].ident;
            int data = events[i].data;

            if (sock == sock_)
                accept_conn(kq, data);
            else
                receive_data(sock, data);
        }
    }

    bool register_event(int kq, int fd)
    {
        /* Initialize kevent structure. */
        struct kevent changes[1];
        EV_SET(&changes[0], fd, EVFILT_READ, EV_ADD, 0, 0, NULL);

        /* Attach event to the	kqueue.	*/
        int ret = kevent(kq, changes, 1, NULL, 0, NULL);
        if (ret == -1)
        {
            return false;
        }

        return true;
    }

    bool unregister_event(int kq, int fd)
    {
        struct kevent changes[1];
        EV_SET(&changes[0], fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);

        /* Attach event to the	kqueue.	*/
        int ret = kevent(kq, changes, 1, NULL, 0, NULL);
        if (ret == -1)
        {
            return false;
        }

        return true;
    }

    void accept_conn(int kq, int connSize)
    {
        for (int i = 0; i < connSize; i++)
        {
            int client = accept(sock_, NULL, NULL);
            if (client == -1)
            {
                std::cerr << "Accept failed. ";
                continue;
            }

            if (!register_event(kq, client))
            {
                close(client);
                std::cerr << "Register client failed. ";
                return;
            }

            std::lock_guard<std::mutex> l(mtx_);
            clients_fd_.push_back(client);
        }
    }

    void receive_data(int sock, int availBytes)
    {
        int bytes = ::recv(sock, buf_, availBytes, 0);
        if (bytes == 0 || bytes == -1)
        {
            std::lock_guard<std::mutex> l(mtx_);
            auto s = std::find(std::begin(clients_fd_), std::end(clients_fd_), sock);
            if (s != std::end(clients_fd_))
            {
                clients_fd_.erase(s);
            }
            unregister_event(kq_, sock);
            close(sock);
            std::cerr << "client close or recv failed. ";
            return;
        }
        
        if(fn_received_data_)
        {
            fn_received_data_(buf_, bytes);
        }
    }

  private:
    std::string url_;
    std::string ip_;
    int port_;

    bool running_;
    int kq_;
    int listen_port_;
    
    char buf_[MAX_RECV_BUFF_SIZE];
    fn_received_data_handle fn_received_data_;
    std::thread *obj_thread_;

    std::mutex mtx_;
    std::vector<int> clients_fd_;
};
} // namespace ymq

#endif //!YMQ_LISTENNER_HPP_