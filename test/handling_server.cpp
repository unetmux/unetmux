#include "../include/server.hpp"

int main()
{
    unetmux::server server(5000);

    server.createServer(nullptr);
    server.run();

    return 0;
}