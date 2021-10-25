#include "ServerStub.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include<pthread.h>
#include <queue>
using namespace std;

//for simple engineer
//pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

//queue requestQueue;

struct arg_struct {
    int engineerId;
    ServerStub* new_sock;
    ThreadPool* tp;
};



void* connection_handler(void* arguments)
{
    struct arg_struct* args = (struct arg_struct*)arguments;

    std::cout << "enginner assigned  " << std::endl;

    ServerStub *new_sock = args->new_sock;
   // pthread_mutex_lock(&lock);
  
    char buffer[2048];
  
    new_sock->receiveOrder1(buffer, args->engineerId, args->tp);

    //pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
    return 0;
}


int main ( int argc, char* argv[] )
{
  std::cout << "running....\n";

  try
    {

      //int port = argv[0];
      //int expertNo = argv[1];
      int port = 30000;
      int expertNo = 2;
      
      // Create the socket
      ServerStub server(port);
	  ServerStub new_sock;
       
   // while ( true )
	//{

	  try
	    {
          pthread_t pthread;
          //pthread_t expertPool[expertNo];

          ThreadPool pool(expertNo);
          std::vector<std::future<int>> futures;

            int count = 0;
          while (server.accept(new_sock)) {
              count=count+1;
            //  while (true) {
              struct arg_struct args;
              args.engineerId = count;
              args.new_sock = &new_sock;
              args.tp = &pool;


              std::cout << "connection received " << std::endl;


                  if (pthread_create(&pthread, NULL, connection_handler, (void*)&args) < 0)
                  {
                      perror("could not create thread");
                      return 1;
                  }

                  
                  std::cout << "engineer assigned outer" << std::endl;
                  pthread_join(pthread, NULL);
              //}

          }
  
          return 0;


	    }
	  catch ( SocketException& ) {
          std::cout << "Exception was caught inside while:" << std::endl;
      }
	//}
    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }

  return 0;
}
