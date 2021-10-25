// Implementation of the ClientSocket class

#include "ClientStub.h"
#include "SocketException.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>
#include <chrono>
using namespace std;

ClientStub::ClientStub ( std::string host, int port )
{
  if ( ! Socket::create() )
    {
      throw SocketException ( "Could not create client socket." );
    }

  if ( ! Socket::connect ( host, port ) )
    {
      throw SocketException ( "Could not bind to port." );
    }

}



void ClientStub::order(vector<Order> orders)

{
    std::cout << "threads started task" << endl;

    if (orders.size() == 0)
    {
        //change the return type
        return ;
    }

    char buffer[2048];
    
    for (int i = 0; i < orders.size(); i++) {
        auto start = std::chrono::high_resolution_clock::now();
        Order o = orders[i];
       std::cout << "client send customerId" << o.getCustomerId() << "order" << o.getOrderNumber() << std::endl;

        int offset = 0;
       
        int net_type1 = htonl(o.getCustomerId()); // pre-def code
        int net_type2 = htonl(o.getOrderNumber()); // pre-def code
        int net_type3 = htonl(o.getLaptopType());
        memcpy(buffer, &net_type1, sizeof(int));
        offset += sizeof(int);
        memcpy(buffer + offset, &net_type2, sizeof(int));
        offset += sizeof(int);
        memcpy(buffer + offset, &net_type3, sizeof(int));

        if (!Socket::send(buffer, 12))
        {
            throw SocketException("Could not write to socket.");
        }

      

        char buffer1[2048] ;

        int read_bytes = 0;
        if ((read_bytes = Socket::recv(buffer)) > 0)
        {
            int offset = 0;

            int net_type1 = 0;
            int net_type2 = 0;
            int net_type3 = 0;
            int net_type4 = 0;
            int net_type5 = 0;

            memcpy(&net_type1, buffer1, sizeof(int));
            offset += sizeof(int);
            memcpy(&net_type2, buffer1 + offset, sizeof(int));
            offset += sizeof(int);
            memcpy(&net_type3, buffer1 + offset, sizeof(int));
            offset += sizeof(int);
            memcpy(&net_type4, buffer1 + offset, sizeof(int));
            offset += sizeof(int);
            memcpy(&net_type5, buffer1 + offset, sizeof(int));

            int customerId = ntohl(net_type1);
            int orderNo = ntohl(net_type2);
            int laptopType = ntohl(net_type3);
            int engineerId = ntohl(net_type4);
            int expertId = ntohl(net_type5);

           

            //std::cout << "Customer ID:" << customerId << " Order ID:" << orderNo << " Laptop Type:" << laptopType << "Engineer Id: " << engineerId << "Expert Id:" << expertId << std::endl;
           

        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::cout << "time for order " << i << " is " << elapsed.count() << " ms\n";

       // std::cout << "threads started task order outer" << i << std::endl;
    }

    std::cout << "threads finished task" << std::endl;

    return ;

}

