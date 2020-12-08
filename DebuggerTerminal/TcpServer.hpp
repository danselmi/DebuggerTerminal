#ifndef TCPSERVER_HPP_INCLUDED
#define TCPSERVER_HPP_INCLUDED

#include <boost/asio.hpp>
#include <queue>
#include "boost/array.hpp"
#include <boost/bind.hpp>
#include <thread>
#include <chrono>

using std::string;
using boost::asio::ip::tcp;

using namespace std;

class TcpServer
{
public:
    TcpServer(uint16_t* TcpPort, boost::asio::io_service& io);
    ~TcpServer();
    void start();
    void stop();
    bool conncted();
    void get_received_data(uint8_t **data, size_t *length); ///caller takes ownership of data
    void set_transmit_data(uint8_t *data, size_t length);   /// data will be copied by callee
private:
    void handle_receive(const boost::system::error_code& error,std::size_t bytes_transferred);
    void handle_send(const boost::system::error_code& error,std::size_t bytes_transferred);
    void handle_accept (const boost::system::error_code& error);
    void start_accept ();
    void Polling ();
    void start_timer();
    void send();
    void receive();
    boost::asio::io_service& io_service_;
    boost::array<uint8_t,1024> recv_buffer_;
    boost::array<uint8_t,1024> send_buffer_;
    std::queue<std::vector<uint8_t>> msg_buf_recvd;
    std::queue<std::vector<uint8_t>> msg_buf_send;
    uint16_t* tcp_port_;
    tcp::socket* socket_;
    bool accepted_;
    tcp::acceptor* acceptor_;

};

#endif // TCPSERVER_HPP_INCLUDED
