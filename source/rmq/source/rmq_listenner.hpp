#ifndef RMQ_LISTENNER_HPP_
#define RMQ_LISTENNER_HPP_

#include "_inl.hpp"
#include "rmq_socket.hpp"
#include <functional>
#include <mutex>
#include <vector>
#include <thread>
#include <string.h>

#ifdef _WIN32

#elif (defined(__APPLE__))
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // for 'close'
#include <sys/event.h>
#include <sys/types.h>
#elif (defined(__linux__))
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // for 'close'
#include <sys/socket.h>
#include <sys/epoll.h>
#include <fcntl.h> 
#endif

namespace rmq
{
class rmq_listenner : public rmq_socket
{
  public:
    rmq_listenner(const char* url)
    {
        this->event_pool_fd_ = 0;
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
    virtual ~rmq_listenner()
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

        if(!rmq_socket::start()) return false;

#ifdef _WIN32
        /* Create IOCP handle*/
        this->event_pool_fd_ = -1;  // TBD
#elif (defined(__APPLE__))
        /* Create kqueue. */
        this->event_pool_fd_ = kqueue();
#elif (defined(__linux__))
        this->event_pool_fd_ = epoll_create(0);
#endif
        
        /* Create listener on port*/
        if(!create_listener(port_))
        {
            return false;
        }

        /*Register events on kqueue*/
        register_event(sock_);
        
        /*Start events thread*/
        obj_thread_ = new std::thread(&rmq_listenner::process_event, this);

        return true;
    }

    virtual void stop()
    {
        rmq_socket::stop();

        running_ = false;
        if (obj_thread_)
        {
#ifdef WIN32
            closesocket(event_pool_fd_);
#else
            close(event_pool_fd_);
#endif
            obj_thread_->join();
            delete obj_thread_;
            obj_thread_ = nullptr;
        }
    }

    virtual int send(char* data, int data_len)
    {
        size_t client_index = 0;
        int sent_len = 0;
        int total_sent = 0;
        int sock = 0;
        while(client_index < clients_fd_.size())
        {
            sock = clients_fd_[client_index];
            total_sent = 0;
            while(total_sent<data_len)
            {
                sent_len = ::send(sock, data, data_len, 0);
                if(sent_len>0)
                {
                    total_sent += sent_len;
                }
                else
                {
                    remove_client(sock);
                    client_index--;
                    break;
                }
            }

            // next client
            client_index++;
        }
        return data_len;
    }

    virtual int recv(char* /*buff*/, int /*buff_len*/)
    {
        // TBD
        return -1;
    }

  private:
    void process_event()
    {
        running_ = true;
#ifdef _WIN32
        /* IOCP event handle*/
#elif (defined(__APPLE__))
        struct kevent *events = new struct kevent[MAX_SOCKET_EVENT_COUNT];
        int ev_cnt = 0;
        while (running_)
        {
            ev_cnt = kevent(event_pool_fd_, NULL, 0, events, MAX_SOCKET_EVENT_COUNT, NULL);
            if(-1==ev_cnt)
            {
                continue;
            }

            // handle events
            for (int i = 0; i < ev_cnt; i++)
            {
                int sock = events[i].ident;
                int data = events[i].data;

                if (sock == sock_)
                {
                    int conn_cnt = data;
                    for (int i = 0; i < conn_cnt; i++)
                    {
                        accept_conn();
                    }
                }
                else
                {
                    int data_size = data;
                    receive_data(sock, data_size);
                }
            }
        }
        delete[] events;
#elif (defined(__linux__))
        int timeout = 1000; // ms
        int nfds;  
        struct epoll_event* events = new struct epoll_event[ MAX_SOCKET_EVENT_COUNT];
        while(running_)
        {
            nfds = epoll_wait(event_pool_fd_, events, LISTEN_BACKLOG, timeout);  
            if(-1==nfds)
            {
                continue;
            }

            // handle events
            for(int i=0;i<nfds;++i)  
            {  
                if(events[i].data.fd==sock_)
                {
                    accept_conn();
                }
                else if( events[i].events&EPOLLIN ) // received data, read socket
                {
                    if (events[i].data.fd < 0)
                        continue;
                        
                    receive_data(events[i].data.fd, -1);

                    /*
                    n = read(sockfd, line, MAXLINE)) < 0    // read data
                    ev.data.ptr = md;     //md is the data will be sent
                    ev.events=EPOLLOUT|EPOLLET;  
                    epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);// modify fd state flag, write event will be triged next tune
                    */   
                }
                else if(events[i].events&EPOLLOUT) //has data need to be sent，write socket
                {
                    /*
                    struct myepoll_data* md = (myepoll_data*)events[i].data.ptr;    // get data  
                    sockfd = md->fd;
                    send( sockfd, md->ptr, strlen((char*)md->ptr), 0 );        // send data
                    ev.data.fd=sockfd;
                    ev.events=EPOLLIN|EPOLLET;
                    epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev); //modify fd state flag, wait for next tune to read data
                    */
                }
                else  
                {


                }
            }
        }
        delete[] events;
#endif
    }

    bool create_listener(int port)
    {
        struct sockaddr_in addr;
#ifdef __APPLE__
        addr.sin_len = sizeof(addr);
#endif
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        /* Set all bits of the padding field to 0 */
        memset(addr.sin_zero, '\0', sizeof addr.sin_zero);  

        int ret = ::bind(sock_, (struct sockaddr *)&addr, sizeof(addr));
        if (ret == -1)
        {
            std::cerr << "bind()　failed:" << errno << std::endl;
            return false;
        }

        if( ::listen(sock_, LISTEN_BACKLOG) == -1)
        {
            std::cerr << " listen()　failed:" << errno << std::endl;
            return false;
        }

        return true;
    }

    bool register_event(int fd)
    {
#ifdef _WIN32
        // TBD



#elif (defined(__APPLE__))
        /* Initialize kevent structure. */
        struct kevent event;
        EV_SET(&event, fd, EVFILT_READ, EV_ADD|EV_ENABLE, 0, 0, NULL);

        /* Attach event to the kqueue. */
        int s = kevent(event_pool_fd_, &event, 1, NULL, 0, NULL);
        if (s == -1)
        {
            return false;
        }
#elif (defined(__linux__))
        struct epoll_event event;  
        event.data.fd = fd;  
        event.events = EPOLLIN | EPOLLET;  
        int s = epoll_ctl (event_pool_fd_, EPOLL_CTL_ADD, fd, &event);  
        if (s == -1)  
        {
            return false;
        }  
#endif

        return true;
    }

    bool unregister_event(int fd)
    {
#ifdef _WIN32

#elif (defined(__APPLE__))
        struct kevent event;
        EV_SET(&event, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
        int s = kevent(event_pool_fd_, &event, 1, NULL, 0, NULL);
        if (s == -1)
        {
            return false;
        }
#elif (defined(__linux__))
        struct epoll_event event;  
        event.data.fd = fd;  
        event.events = EPOLLIN | EPOLLET;  
        int s = epoll_ctl (event_pool_fd_, EPOLL_CTL_DEL, fd, &event);  
        if (s == -1)  
        {
            return false;
        }
#endif

        return true;
    }

    bool accept_conn()
    {
        struct sockaddr peer_addr;
        unsigned int peer_addr_size = sizeof(struct sockaddr);

        int client = ::accept(sock_, (struct sockaddr *) &peer_addr, &peer_addr_size);
        if (client == -1)
        {
            std::cerr << "Accept failed. ";
            return false;
        }

        if (!register_event(client))
        {
#ifdef WIN32
            closesocket(client);
#else
            close(client);
#endif
            std::cerr << "Register client failed. ";
            return false;
        }

        std::lock_guard<std::mutex> l(mtx_);
        clients_fd_.push_back(client);

        return true;
    }

    void receive_data(int sock, int availBytes)
    {
        int bytes = 0;
        int total_bytes = 0;

#ifdef _WIN32

#elif (defined(__APPLE__))
        while(total_bytes<availBytes)
        {
            bytes = ::recv(sock, buf_, MAX_RECV_BUFF_SIZE, 0);
            if (bytes == 0 || bytes == -1)
            {
                remove_client(sock);
                std::cerr << "client close or recv failed. ";
                return;
            }
            
            if(fn_received_data_)
            {
                fn_received_data_(buf_, bytes);
            }

            total_bytes+=bytes;
        }
        printf("availBytes=%d, recv=%d\n", availBytes, total_bytes);
#elif (defined(__linux__))
        while((bytes = ::recv(sock, buf_, MAX_RECV_BUFF_SIZE, 0))>0)
		{
            if(fn_received_data_)
            {
                fn_received_data_(buf_, bytes);
            }

            total_bytes+=bytes;
		}
        if (bytes == -1)
        {
            remove_client(sock);
            std::cerr << "client close or recv failed. ";
            return;
        }
        printf("availBytes=%d, recv=%d\n", availBytes, total_bytes);

		/*
        struct epoll_event event; 
        ev.data.ptr = md;
        ev.events=EPOLLOUT|EPOLLET;  
        epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);
		*/
#endif
    }

    void remove_client(int sock)
    {
        std::lock_guard<std::mutex> l(mtx_);
		int i=0;
        while(i<clients_fd_.size())
        {
            if(clients_fd_[i] == sock)
            {
                clients_fd_.erase(clients_fd_.begin()+i);
                unregister_event(sock);
#ifdef WIN32
                closesocket(sock);
#else
                close(sock);
#endif
                continue;
            }
	        i++;
        }
    }

  private:
    int event_pool_fd_;
    bool running_;

    std::string url_;
    std::string ip_;
    int port_;
    
    char buf_[MAX_RECV_BUFF_SIZE];
    fn_received_data_handle fn_received_data_;
    std::thread *obj_thread_;

    std::mutex mtx_;
    std::vector<int> clients_fd_;
};
} // namespace rmq

#endif //!RMQ_LISTENNER_HPP_
