#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <TCPserver.h>

using namespace boost::asio;
using ip::tcp;
using namespace std;

     class con_handler : public boost::enable_shared_from_this<con_handler>
    {
         private:
              tcp::socket sock;
         public:
              typedef boost::shared_ptr<con_handler> pointer;
              con_handler(boost::asio::io_service& io_service): sock(io_service){}

    // creating the pointer
         static pointer create(boost::asio::io_service& io_service){
              return pointer(new con_handler(io_service));
         }

    //socket creation
         tcp::socket& socket(){
              return sock;

         }

    };

class Server
{
    Server_functions Server_functions_;
     private:
          tcp::acceptor acceptor_;
          void start_accept()
          {
     // socket
          con_handler::pointer connection =
          con_handler::create(acceptor_.get_io_service());
     // asynchronous accept operation and wait for a new connection.
          acceptor_.async_accept(connection->socket(),
               boost::bind(&Server::handle_accept, this, connection,
               boost::asio::placeholders::error));
          }
     public:
     // constructor for accepting connection from client
     Server(boost::asio::io_service& io_service): acceptor_(io_service, tcp::endpoint(tcp::v4(), 4242)) // 4241,4242,4243,4244
     {
        start_accept();

     }

     void handle_accept(con_handler::pointer connection,const boost::system::error_code& err){
          if (!err)
          {
            //run

          }
          else
          {
              Server_functions_.close_connection()
          }
        start_accept();
     }

};

class Server_functions: public boost::enable_shared_from_this<Server_functions>
{
    boost::asio::io_service io_service_;
    tcp::socket sock;

    public:
     void TCP_Server_write(string data_server, char length)                         //close after
        {
             sock.async_write_some(boost::asio::buffer(data_server,length),
                   shared_from_this(),
                   boost::asio::placeholders::error,
                   boost::asio::placeholders::bytes_transferred));
        }
//
//    void TCP_Server_read(string data_client, char length)
//    {
//        sock.async_read_some(boost::asio::buffer(data_client, length),
//               shared_from_this(),
//               boost::asio::placeholders::error,
//               boost::asio::placeholders::bytes_transferred));             //while bytes_transferred not 0
//    }                                                                     //  close after
//  bool  close_connection( bool x )
//        {
//            x = false;
//            io_service_.stop();
//            return x;
//        }
//
//
//        bool hasConnection( bool x  )
//         {
//           x = true;
//           return x;
//         }
//

};

int main()
 {
     boost::asio::io_service io_service_;
     Server server(io_service_);
     io_service_.run();
     return 0;
 }
