#include "../include/http.hpp"
#include <llhttp.h>
#include <iostream>

int main()
{
    unetmux::http http(5000);

    http.httpCreateServer([](void * request, void * response){
        std::cout << static_cast<uv_buf_t *>(request)->base;
    });

    return 0;
}