// Definition of the ClientStub class

#ifndef ClientStub_class
#define ClientStub_class

#include "Socket.h"
#include "Order.cpp"
#include <vector>

using namespace std;
class ClientStub : private Socket
{
 public:

  ClientStub ( std::string host, int port );
  virtual ~ClientStub(){};// abstract function

  void order(vector<Order> orders );

};


#endif
