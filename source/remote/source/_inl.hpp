#pragma once

namespace Remote
{

    // defined of all the broker url
    struct proxy_url
    {
        bool master_;           // is master
        std::string id_;        // uuid of [server/client]
        std::string broker_in_; // [outer]broker in
        std::string broker_out_;// [outer]broker out
        std::string recv_in_;   // [inner]proxy recv in
        std::string recv_out_;  // [inner]proxy recv out
        std::string send_in_;   // [inner]proxy send in
        std::string send_out_;  // [inner]proxy send out
        std::string pub_in_;    // [inner]broker pub in
        std::string pub_out_;   // [inner]broker pub out
    };

// Server
#define S_PROXY_RECV_FONTEND        "inproc://robo_remote_channel:5500"     // [proxy] recv frontend
#define S_PROXY_RECV_BACKEND        "inproc://robo_remote_channel:5501"     // [proxy] recv backend
#define S_PROXY_SEND_FONTEND        "inproc://robo_remote_channel:5502"     // [proxy] send frontend
#define S_PROXY_SEND_BACKEND        "inproc://robo_remote_channel:5503"     // [proxy] send backend

#define S_IPC_PUB_RECV              S_PROXY_SEND_BACKEND                    // [pub] recv
#define S_IPC_PUB_SEND              "tcp://127.0.0.1:8012"                  // [pub] send

// Client
#define C_PROXY_RECV_FONTEND        "inproc://robo_remote_channel:5600"     // [proxy] recv frontend
#define C_PROXY_RECV_BACKEND        "inproc://robo_remote_channel:5601"     // [proxy] recv backend
#define C_PROXY_SEND_FONTEND        "inproc://robo_remote_channel:5602"     // [proxy] send frontend
#define C_PROXY_SEND_BACKEND        "inproc://robo_remote_channel:5603"     // [proxy] send backend

#define C_IPC_PUB_RECV              C_PROXY_SEND_BACKEND                    // [pub] recv
#define C_IPC_PUB_SEND              "tcp://127.0.0.1:8014"                  // [pub] send



}  // name space GPIORW