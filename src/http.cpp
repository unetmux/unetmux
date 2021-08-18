#include "../include/http.hpp"

void unetmux::http::httpCreateServer(unetmux::server::handler_cb cb)
{   
    this->m_handler_cb = cb;

    this->createServer(cb);

    this->run();
}