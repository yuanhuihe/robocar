
#include <iostream>
#include <fiblib/Fibonacci.h>
#include <chrono>
#include <thread>
#include <atomic>
#include <iostream>
#include <msgpack.hpp>
#include <functional>
#include <algorithm>
#include "StackAlloc.h"
#include <random>
#include "ProducerConsumerQueue.h"

typedef std::vector<char> char_array;
char_array charset()
{
    return char_array(
            {'0','1','2','3','4',
            '5','6','7','8','9',
            'A','B','C','D','E','F',
            'G','H','I','J','K',
            'L','M','N','O','P',
            'Q','R','S','T','U',
            'V','W','X','Y','Z',
            'a','b','c','d','e','f',
            'g','h','i','j','k',
            'l','m','n','o','p',
            'q','r','s','t','u',
            'v','w','x','y','z'
            });
};

std::string random_string( size_t length, std::function<char(void)> rand_char )
{
    std::string str(length,0);
    std::generate_n( str.begin(), length, rand_char );
    return str;
}

int main(int /*argc*/, char* /*argv*/[])
{
    // Calculate and print fibonacci number
    std::cout << "Fibonacci library" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Fibonacci(8) = " << fiblib::Fibonacci()(8) << std::endl;
    std::cout << std::endl;
    const auto ch_set = charset();
    std::default_random_engine rng(std::random_device{}());
    std::uniform_int_distribution<> dist(0, ch_set.size()-1);
    auto randchar = [ ch_set,&dist,&rng ](){return ch_set[ dist(rng) ];};

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    


    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
    std::cout << "Waited " << elapsed.count() << " ms\n";

    /*start = std::chrono::steady_clock::now();

    count=0;
    while(1){
        zmsg *reply = session.recv();
        if (reply) {
            delete reply;
        }
        count++;
        reply->pop_front();
        std::string reply_str = std::string((char*)reply->pop_front().c_str());
        stackPool.pop(count);
        std::cout<<"reply str: "<<reply->body()<<std::endl;
        if(count>100) break;
    }
    end = std::chrono::steady_clock::now();
    elapsed = end-start;
    std::cout << "Waited " << elapsed.count() << " ms\n";

    std::cout << "got msg reply: "<<count<<std::endl;*/

    return 0;
}
