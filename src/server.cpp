#include "../include/server.hpp"
#include <iostream>
#include <llhttp.h>

void unetmux::server::createServer(unetmux::server::handler_cb cb)
{
    this->m_handler_cb = cb;

    this->m_loop = uv_default_loop();

    uv_tcp_init(this->m_loop, this->m_server);

    sockaddr_in * addr = new sockaddr_in;

    uv_ip4_addr("0.0.0.0", this->m_port, addr);
    
    uv_tcp_bind(this->m_server, reinterpret_cast<const sockaddr *>(addr), 0);

    uv_handle_set_data(reinterpret_cast<uv_handle_t *>(this->m_server), this);

    const int DEFAULT_BACKLOG = 128;

    int status = uv_listen(reinterpret_cast<uv_stream_t *>(this->m_server), DEFAULT_BACKLOG, 
    [](uv_stream_t * stream, int status)
    {
        if (status < 0)
        {
            std::cerr << "New connection error " << uv_strerror(status) << std::endl;

            return;
        }

        unetmux::server * server = reinterpret_cast<unetmux::server *>(reinterpret_cast<uv_handle_t *>(stream)->data);

        uv_tcp_t * client = new uv_tcp_t;
        uv_handle_set_data(reinterpret_cast<uv_handle_t *>(client), server);

        uv_tcp_init(uv_handle_get_loop(reinterpret_cast<uv_handle_t *>(stream)), client);

        if (uv_accept(stream, reinterpret_cast<uv_stream_t *>(client)) == 0)
        {
            uv_read_start(reinterpret_cast<uv_stream_t *>(client), 
            [](uv_handle_t * handle, size_t suggested_size, uv_buf_t * buf)
            {
                buf->base = (char *)malloc(suggested_size);
                buf->len = suggested_size;
            }, 
            [](uv_stream_t * stream, ssize_t nread, const uv_buf_t * buf)
            {
                // static int numRead = 0;

                // llhttp_settings_t settings;
                // llhttp_t * request = new llhttp_t;
                // llhttp_t * response = new llhttp_t;

                // llhttp_settings_init(&settings);
                // llhttp_init(request, HTTP_REQUEST, &settings);

                // llhttp_errno error = llhttp_execute(request, buf->base, nread);

                // // std::cout << (request->method == llhttp_method::HTTP_GET);

                // std::cout << buf->base << std::endl << "=========== ";
                // std::cout << buf->len << " " << nread;
                std::cout << buf->base;
                // printf("%s \n === %ld \n %ld", buf->base, buf->len, nread);
            });
        }

        if (status < 0)
        {
            std::cerr << "Listening error " << uv_strerror(status) << std::endl;
        }
    });
}

void unetmux::server::run() const
{
    uv_run(this->m_loop, UV_RUN_DEFAULT);
}