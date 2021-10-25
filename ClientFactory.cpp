#include "ClientStub.h"
#include "SocketException.h"
#include <iostream>
//#include <string>
#include <vector>
#include <stdlib.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include<pthread.h>
//#include <string.h>
#include <stdio.h>
#include <iomanip> 



pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

struct arg_struct {
    string ipAddr;
    int port;
    int orderCount;
    int laptopType;
    int customerId;
};
//int count = 0;
void* cientThread(void* arguments)
{
    struct arg_struct* args = (struct arg_struct*)arguments;
      
    ClientStub client_socket(args->ipAddr, args->port);
 
    const pthread_t tid = pthread_self();

    try
    {
        vector<Order> orders;
      //  pthread_mutex_lock(&lock);
      
        for (int i = 0; i < args->orderCount; i++) {
            Order* o = new Order(tid, i, args->laptopType);
            orders.push_back(*o);

        }
        client_socket.order(orders);
        //pthread_mutex_unlock(&lock);
    }
    catch (SocketException&) {

    }
   
    pthread_exit(NULL);
}

int main ( int argc, char* argv[] )
{
    try
    {

        std::string ipAddr = argv[1];
        int port = atoi(argv[2]);
        int customers = atoi(argv[3]);
        int orderCount = atoi(argv[4]);
        int laptopType = atoi(argv[5]);

        std::cout << ipAddr << port << customers << orderCount << laptopType << std::endl;

       /* std::string ipAddr = "localhost";
        int port = 30000;
        int customers = 5;
        int orderCount = 5;
        int laptopType = 1;*/

        

        int i = 0;
        int count = 0;
        pthread_t tid[customers+1];
        while (i < customers)
        {
            struct arg_struct args;
            args.ipAddr = ipAddr;
            args.port = port;
            args.orderCount = orderCount;
            args.laptopType = laptopType;
            args.customerId = i;
           
                if (pthread_create(&tid[i], NULL, &cientThread, (void*)&args) != 0) {
                    printf("Failed to create thread\n");
                }
                i++;
        }
       // sleep(20);
        i = 0;
        while (i < customers)
        {
            pthread_join(tid[i++], NULL);
           // printf("%d:\n", i);
        }

    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\n";
    }

  return 0;
}

