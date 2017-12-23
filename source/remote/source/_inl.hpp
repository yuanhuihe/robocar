#pragma once

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
#define SERVER_RECV_URL             "tcp://*:6011"
#define SERVER_SEND_URL             "tcp://*:6012"
#define SERVER_PROXY_RECV_BACKEND   "inproc://robo_remote_channel:6600"     // [proxy] recv frontend
#define SERVER_PROXY_SEND_FONTEND   "inproc://robo_remote_channel:6601"     // [proxy] send backend

// Client
#define CLIENT_RECV_URL             "inproc://robo_remote_channel:7011"
#define CLIENT_SEND_URL             "inproc://robo_remote_channel:7012"
#define CLIENT_PROXY_RECV_BACKEND   "inproc://robo_remote_channel:7700"     // [proxy] recv frontend
#define CLIENT_PROXY_SEND_FONTEND   "inproc://robo_remote_channel:7701"     // [proxy] send backend



}  // name space GPIORW