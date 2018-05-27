#pragma once
#include <zmq.h>

namespace Remote
{
    // defined of all the broker url
    struct proxy_url
    {
        bool master_;                   // is master
        std::string id_;                // uuid of [server/client]
        std::string proxy_recver_in_;   // [outer]proxy recv in
        std::string proxy_recver_out_;  // [inner]proxy recv out
        std::string proxy_sender_in_;   // [inner]proxy send in
        std::string proxy_sender_out_;  // [outer]proxy send out
        std::string client_recver_in_;  // [outer]pub recv in
        std::string client_sender_out_; // [outer]pub send out
    };                      

// Server
#define SERVER_PROXY_RECV_FONTEND   "tcp://*:8801"
#define SERVER_PROXY_RECV_BACKEND   "inproc://robo_remote_channel:8101"     // [proxy] recv frontend
#define SERVER_PROXY_SEND_FONTEND   "inproc://robo_remote_channel:8102"     // [proxy] send backend
#define SERVER_PROXY_SEND_BACKEND   "tcp://*:8802"

// Client
#define CLIENT_PROXY_RECV_FONTEND   "inproc://robo_remote_channel:8901"
#define CLIENT_PROXY_RECV_BACKEND   "inproc://robo_remote_channel:8201"     // [proxy] recv frontend
#define CLIENT_PROXY_SEND_FONTEND   "inproc://robo_remote_channel:8202"     // [proxy] send backend
#define CLIENT_PROXY_SEND_BACKEND   "inproc://robo_remote_channel:8902"



}  // name space GPIORW