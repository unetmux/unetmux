#pragma once

#include <functional>
#include <uv.h>
#include <vector>

namespace unetmux
{       
    class server
    {
    public:
        using handler_cb = std::function<void(void *, void *)>;

    protected:
        const int m_port;
        uv_loop_t * m_loop;
        uv_tcp_t * m_server;
        //Callback members
        handler_cb m_handler_cb;

    public:
        explicit server(const int port) : m_port(port) //Initializing not pointer member values
        {
            //Initialize members            
            this->m_loop = new uv_loop_t;
            this->m_server = new uv_tcp_t;
            this->m_handler_cb = nullptr;
        }

        void createServer(handler_cb);

        void run() const;

        inline uv_loop_t * get_loop() const
        {
            return this->m_loop;
        }

        inline uv_tcp_t * get_server() const
        {
            return this->m_server;
        }

        virtual ~server()
        {
            uv_close(reinterpret_cast<uv_handle_t *>(this->m_loop), [](uv_handle_t * handle) {});
            delete this->m_loop;
            delete this->m_server;
        }
    };



}