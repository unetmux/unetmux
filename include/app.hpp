#pragma once
#include "server.hpp"


namespace unetmux
{
    class http_server : unetmux::server
    {
    public:
        http_server(void * ptr);
        ~http_server();
    };
}
