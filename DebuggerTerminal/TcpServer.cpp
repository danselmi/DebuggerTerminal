#include "TcpServer.hpp"


TcpServer::TcpServer(uint16_t* TcpPort, boost::asio::io_service& io) :
    io_service_(io),
    tcp_port_(TcpPort),
    accepted_(false),
    acceptor_(nullptr)
{
    start_timer();
}

void TcpServer::start_timer()
{
    std::thread([this](){
        while(1)
        {
            Polling();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }).detach();
}

TcpServer::~TcpServer()
{
    if(acceptor_->is_open())
        acceptor_->close();
    if(socket_->is_open())
        socket_->close();
    delete[] acceptor_;
    delete[] socket_;
}


void TcpServer::Polling ()
{
    if(!msg_buf_send.empty()&&accepted_)
        send();

    if(acceptor_)
        if(!acceptor_->is_open())
            accepted_ = false;
}


void TcpServer::start_accept ()
{
    acceptor_->async_accept(*socket_,boost::bind(&TcpServer::handle_accept,this,boost::asio::placeholders::error));
}


void TcpServer::handle_accept(const boost::system::error_code& error)
{
    if (!error)
    {
        accepted_ = true;
        receive();    ///start nonblocking receive process
    }
    else
        start_accept();
}


void TcpServer::start()
{
    socket_ = new boost::asio::ip::tcp::socket(io_service_);
    acceptor_ = new boost::asio::ip::tcp::acceptor(io_service_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),*tcp_port_));
    start_accept();
}


bool TcpServer::conncted()
{
    return accepted_;
}


void TcpServer::stop()
{
    accepted_ = false;
    socket_->close();
    acceptor_->close();
}


void TcpServer::get_received_data(uint8_t **data, size_t *length)
{
    if(!msg_buf_recvd.empty())
    {
        std::vector<uint8_t> temprecv = msg_buf_recvd.front();
        uint8_t *d = new uint8_t[temprecv.size()];
        memcpy(d,&temprecv[0],temprecv.size());
        *data = d;
        *length = (temprecv.size());
        msg_buf_recvd.pop();
    }
}


void TcpServer::set_transmit_data(uint8_t *data, size_t length)
{
    std::vector<uint8_t> temp_data;
    for(size_t i = 0;i < length; i++)
        temp_data.push_back(data[i]);
    msg_buf_send.push(temp_data);
}


void TcpServer::send()
{
    socket_->async_send(boost::asio::buffer(msg_buf_send.front(),msg_buf_send.front().size()), boost::bind(&TcpServer::handle_send, this,
        boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
    msg_buf_send.pop();
}


void TcpServer::handle_send(const boost::system::error_code& error,std::size_t bytes_transferred)
{
    if (error)
    {
        stop();
        start();
    }
}


void TcpServer::receive()
{
    socket_->async_receive(boost::asio::buffer(recv_buffer_), boost::bind(&TcpServer::handle_receive, this,
        boost::asio::placeholders::error,boost::asio::placeholders::bytes_transferred));
}


void TcpServer::handle_receive(const boost::system::error_code& error,std::size_t bytes_transferred)
{
    std::vector<uint8_t> vec_local;
    if (!error&&bytes_transferred>0)
    {
        for(size_t i = 0; i < bytes_transferred; i++)
        {
            vec_local.push_back(recv_buffer_[i]);
        }
        msg_buf_recvd.push(vec_local);
        receive();
    }
    else
    {
        stop();
        start();
    }
}
