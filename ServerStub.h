// Definition of the ServerSocket class

#ifndef ServerStub_class
#define ServerStub_class

#include <vector>
#include "Socket.h"
#include "Order.cpp"
#include "Laptop.cpp"
#include <iostream>
#include "ThreadPool.h"


class ServerStub : private Socket
{
 public:

  ServerStub ( int port );
  ServerStub (){};
  virtual ~ServerStub();

  bool accept ( ServerStub& );

  //Order receiveOrder(char* buffer);
  //int receiveOrder(char* buffer, Order* order);
  //void shipLaptop(Order* o, int engineerId);

  //Order receiveOrder(char* buffer);
  //void shipLaptop(Order o, int engineerId);
  void receiveOrder1(char* buffer, int engineerId, ThreadPool* tp);
};


#endif
