// Implementation of the ServerSocket class

#include "ServerStub.h"
#include "SocketException.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <cstring>
#include "ThreadPool.h"

ServerStub::ServerStub ( int port )
{
  if ( ! Socket::create() )
    {
      throw SocketException ( "Could not create server socket." );
    }

  if ( ! Socket::bind ( port ) )
    {
      throw SocketException ( "Could not bind to port." );
    }

  if ( ! Socket::listen() )
    {
      throw SocketException ( "Could not listen to socket." );
    }

}

ServerStub::~ServerStub()
{
}



bool ServerStub::accept ( ServerStub& sock )
{
  if ( ! Socket::accept ( sock ) )
    {
      throw SocketException ( "Could not accept socket." );
    }
  return true;
}


/*
int ServerStub::receiveOrder(char* buffer, Order* order)
{
    int read_bytes = 0;
    if ((read_bytes = Socket::recv( buffer )) > 0)
    {
        int offset = 0;

        int net_type1 = 0;
        int net_type2 = 0;
        int net_type3 = 0;
        memcpy(&net_type1, buffer, sizeof(int));
        offset += sizeof(int);
        memcpy(&net_type2, buffer + offset, sizeof(int));
        offset += sizeof(int);
        memcpy(&net_type3, buffer + offset, sizeof(int));

        int customerId = ntohl(net_type1);
        int orderNo = ntohl(net_type2);
        int laptopType = ntohl(net_type3);

        std::cout << "Customer ID:" << customerId << " Order ID:"<< orderNo << " Laptop Type:" << laptopType << std::endl;
         order = new Order(customerId, orderNo, laptopType);

    } else {
        throw SocketException("Could not read from socket.");
    }
    return read_bytes;
}

void ServerStub::shipLaptop(Order* o, int engineerId)
 {
    char buffer[128];
    int offset = 0;
    int net_type1 = htonl(o->getCustomerId()); // pre-def code
    int net_type2 = htonl(o->getOrderNumber()); // pre-def code
    int net_type3 = htonl(o->getLaptopType());
    int net_type4 = htonl(engineerId);
    int net_type5 = htonl(-1);
    memcpy(buffer, &net_type1, sizeof(int));
    offset += sizeof(int);
    memcpy(buffer + offset, &net_type2, sizeof(int));
    offset += sizeof(int);
    memcpy(buffer + offset, &net_type3, sizeof(int));
    offset += sizeof(int);
    memcpy(buffer + offset, &net_type4, sizeof(int));
    offset += sizeof(int);
    memcpy(buffer + offset, &net_type5, sizeof(int));

    if (!Socket::send(buffer, 20))
    {
        throw SocketException("Could not write server to client socket.");
    }


}
*/

/*
Order ServerStub::receiveOrder(char* buffer)
{
    int read_bytes = 0;
    if ((read_bytes = Socket::recv(buffer)) > 0)
    {
        int offset = 0;

        int net_type1 = 0;
        int net_type2 = 0;
        int net_type3 = 0;
        memcpy(&net_type1, buffer, sizeof(int));
        offset += sizeof(int);
        memcpy(&net_type2, buffer + offset, sizeof(int));
        offset += sizeof(int);
        memcpy(&net_type3, buffer + offset, sizeof(int));

        int customerId = ntohl(net_type1);
        int orderNo = ntohl(net_type2);
        int laptopType = ntohl(net_type3);

        std::cout << "Customer ID:" << customerId << " Order ID:" << orderNo << " Laptop Type:" << laptopType << std::endl;
        Order* order = new Order(customerId, orderNo, laptopType);
        return *order;
    }
    else {
        throw SocketException("Could not read from socket.");
    }

    Order* order = new Order(-1, -1, -1);
    return *order;
}

void ServerStub::shipLaptop(Order o, int engineerId)
{
    char buffer[128];
    int offset = 0;
    int net_type1 = htonl(o.getCustomerId()); // pre-def code
    int net_type2 = htonl(o.getOrderNumber()); // pre-def code
    int net_type3 = htonl(o.getLaptopType());
    int net_type4 = htonl(engineerId);
    int net_type5 = htonl(-1);
    memcpy(buffer, &net_type1, sizeof(int));
    offset += sizeof(int);
    memcpy(buffer + offset, &net_type2, sizeof(int));
    offset += sizeof(int);
    memcpy(buffer + offset, &net_type3, sizeof(int));
    offset += sizeof(int);
    memcpy(buffer + offset, &net_type4, sizeof(int));
    offset += sizeof(int);
    memcpy(buffer + offset, &net_type5, sizeof(int));

    if (!Socket::send(buffer, 20))
    {
        throw SocketException("Could not write server to client socket.");
    }


}
*/

void ServerStub::receiveOrder1(char* buffer, int engineerId, ThreadPool* tp) {

    int read_bytes = 0;
    while((read_bytes = Socket::recv(buffer)) > 0)
    {
        int offset = 0;

        int net_type11 = 0;
        int net_type21 = 0;
        int net_type31 = 0;
        memcpy(&net_type11, buffer, sizeof(int));
        offset += sizeof(int);
        memcpy(&net_type21, buffer + offset, sizeof(int));
        offset += sizeof(int);
        memcpy(&net_type31, buffer + offset, sizeof(int));

        int customerId = ntohl(net_type11);
        int orderNo = ntohl(net_type21);
        int laptopType = ntohl(net_type31);
        int expertId = -1;


        if (laptopType == 1) {
            auto result = tp->enqueue([]() { return std::this_thread::get_id(); });
            std::cout << "Customer ID:" << customerId << " Order ID:" << orderNo << " Laptop Type:" << laptopType << "expert id:" << result.get() << std::endl;
        }
        else {

            std::cout << "Customer ID:" << customerId << " Order ID:" << orderNo << " Laptop Type:" << laptopType << "expertId" << expertId << std::endl;

        }


        char buffer1[2048];
         offset = 0;
        int net_type1 = htonl(customerId); // pre-def code
        int net_type2 = htonl(orderNo); // pre-def code
        int net_type3 = htonl(laptopType);
        int net_type4 = htonl(engineerId);
        int net_type5 = htonl(expertId);
        memcpy(buffer1, &net_type1, sizeof(int));
        offset += sizeof(int);
        memcpy(buffer1 + offset, &net_type2, sizeof(int));
        offset += sizeof(int);
        memcpy(buffer1 + offset, &net_type3, sizeof(int));
        offset += sizeof(int);
        memcpy(buffer1 + offset, &net_type4, sizeof(int));
        offset += sizeof(int);
        memcpy(buffer1+ offset, &net_type5, sizeof(int));

        if (!Socket::send(buffer1, 20))
        {
            throw SocketException("Could not write server to client socket.");
        }

       
    }

}
