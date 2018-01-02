#ifndef SOCK_KQUEUE_HPP_
#define SOCK_KQUEUE_HPP_

#include "ymq_socket.hpp"
#include <functional>
#include <mutex>
#include <vector>

namespace ymq
{
class sock_kqueue : public ymq_socket
{
#define MAX_EVENT_COUNT 5000
#define MAX_RECV_BUFF 65535

  public:
    sock_kqueue(int port)
    : listern_port_(port)
    {
        this->listerner_ = -1;
        this->kq_ = 0;
        this->running_ = false;
        this->obj_thread_ = nullptr;

        fn_received_data_ = nullptr;
    }
    virtual ~sock_kqueue()
    {
        stop();
    }

    void set_received_callback(fn_received_data_handle fn)
    {
        fn_received_data_ = fn;
    }

    void start()
    {
        /* Create kqueue. */
        this->kq_ = kqueue();
        /* Create listerner on port*/
        listerner_ = create_listerner(listern_port_);
        /*Register events on kqueue*/
        register_event(kq_, listerner_);
        /*Start events thread*/
        obj_thread_ = new std::thread(&sock_kqueue::process_event, this);
    }

    void stop()
    {
        if(listerner_>0)
        {
            close(listerner_);
            listerner_ = 0;
        }

        running_ = false;
        if (obj_thread_)
        {
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
        while (running_)
        {
            ret = kevent(kq_, NULL, 0, events, MAX_EVENT_COUNT, NULL);
            handle_events(kq_, events, ret);
        }

        delete[] events;
    }

    int create_listerner(int port)
    {
        int sock = socket(PF_INET, SOCK_STREAM, 0);
        if (sock == -1)
        {
            std::cerr << "socket()　failed:" << errno << std::endl;
            return -1;
        }

        int set = 1;
        setsockopt(sock, SOL_SOCKET, SO_NOSIGPIPE, (void *)&set, sizeof(int));

        struct sockaddr_in addr;
        addr.sin_len = sizeof(addr);
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);

        int ret = ::bind(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr));
        if (ret == -1)
        {
            std::cerr << "bind()　failed:" << errno << std::endl;
            return -1;
        }

        // if( listern(sock,5) == -1)
        // {
        //     std::cerr << " listern()　failed:" << errno << std::endl;
        //     return -1;
        // }
        return sock;
    }

    void handle_events(int kq, struct kevent *events, int nevents)
    {
        for (int i = 0; i < nevents; i++)
        {
            int sock = events[i].ident;
            int data = events[i].data;

            if (sock == listerner_)
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
            int client = accept(listerner_, NULL, NULL);
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
    bool running_;
    int kq_;
    int listern_port_;
    int listerner_;
    char buf_[MAX_RECV_BUFF];
    fn_received_data_handle fn_received_data_;
    std::thread *obj_thread_;

    std::mutex mtx_;
    std::vector<int> clients_fd_;
};
} // namespace ymq

#endif //!SOCK_KQUEUE_HPP_