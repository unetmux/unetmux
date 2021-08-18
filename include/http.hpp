#pragma once

#include "server.hpp"
#include <string>

namespace unetmux
{
    class http : public unetmux::server
    {
    public:
        explicit http(const int port) : unetmux::server::server(port)
        {
        }

        void httpCreateServer(unetmux::server::handler_cb);

        ~http() {}
    };
}
