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

    private:
        const int m_port;
        std::vector<int8_t> * m_data;
        uv_loop_t * m_loop;
        uv_tcp_t * m_server;
        void * m_custom_data;
        size_t m_custom_data_size;
        //Callback members
        handler_cb m_handler_cb;

    public:
        explicit server(const int port) : m_port(port), m_custom_data_size(0) //Initializing not pointer member values
        {
            //Initialize members
            this->m_data = new std::vector<int8_t>;
            this->m_loop = new uv_loop_t;
            this->m_server = new uv_tcp_t;
            this->m_custom_data = nullptr;
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

        inline void * get_custom_data() const
        {
            return this->m_custom_data;
        }

        inline void set_custom_data(void * custom_data)
        {
            this->m_custom_data = custom_data;
        }

        ~server()
        {
            delete this->m_data;
            delete this->m_loop;
            delete this->m_server;
        }
    };



}