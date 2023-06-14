#pragma once 
#include <iostream>
#include <boost/asio.hpp>

#define MESSAGE_BUFFER 1024
#define PORT 6504




class NetworkComponent
{
using udp = boost::asio::ip::udp;

udp::socket socket;
udp::endpoint endpoint;
char data[MESSAGE_BUFFER];
// boost::asio::io_context *io_context;

public:

    // Constructor for client
    NetworkComponent(std::string serverIP, boost::asio::io_context &io_context) : socket(io_context, udp::endpoint(boost::asio::ip::address::from_string(serverIP), PORT)){};
    
    // Constructor for server
    NetworkComponent(boost::asio::io_context &io_context) : socket(io_context, udp::endpoint(udp::v4(), PORT)){};
    
    ~NetworkComponent();
};