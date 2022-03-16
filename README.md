# ClientServer

# Software Design Summary : 
Design consist of server factory, server stub, client factory, client stub, generic socket.h and generic threadpool.h . Client factory initializes the client program and using client stub orders the customers order. Every customer in client is a thread which creates a client-socket connection and using client stub transfers the order on the network and server accepts the client connection via server socket spawn an engineer thread for each customer thread. Customer threads wait for engineer thread to respond with the laptop information. ServerFactory is responsible for creating threadpool of expert engineer. If laptop is of type 1 then engineer thread pushes the order task to FIFO request queue and to get the expertid of the thread from expert thread pool processing the order, have used the future concept which gives the id of the expert thread. The synchronization among the threads is achieved by mutex and condition variable.

# How to run:

a) As command line argument feature is not working. 

b) Change the below parameters in ClientFactory.cpp to perform for some other statistics.

      std::string ipAddr = "localhost"; int port = 30000; int customers = 1;
       int orderCount = 1000; int laptopType = 0;
       
c) Change the port and expertNo parameters in ServerFactory.cpp to perform for some other statistics.

d) run the make command on code folder.

e) Run server ./simple_server and run client ./simple_client

# Graphs/Plots: 
# Scenario 1      
![image](https://user-images.githubusercontent.com/79550954/158515634-9bb59181-9b95-4dee-876d-76fe8219988c.png)

 ![image](https://user-images.githubusercontent.com/79550954/158515605-9f1752bd-42e8-45c8-a093-2b9ff296a915.png)

    In this scenario throughput is max for 1st customer, as the customers increases total number of orders also increases, hence the load increases, which leads to increase in latency and decrease in throughput as the resources with each run of the experiment is same.
    
# Scenario 2:
 ![image](https://user-images.githubusercontent.com/79550954/158515718-d35130fc-5225-4304-ad89-2e3eb014c983.png)
![image](https://user-images.githubusercontent.com/79550954/158515728-a86b3431-a59f-4cb8-b2d0-8944bbd9753f.png)


In this scenario laptop type is 1 and the expert engineer thread is 1, therefore throughput increases in the beginning and later on it’s a bottleneck when the number of customer increases but the resources available is limited.

# Scenario 3:
 
 ![image](https://user-images.githubusercontent.com/79550954/158515742-1ed558c5-10f8-42f1-b73b-dc8501cee802.png)

![image](https://user-images.githubusercontent.com/79550954/158515751-35016025-4439-4381-b1b5-2d9007f7da00.png)

In this scenario laptop type is 1 and the expert engineer thread is 8 which leads to more parallelism; therefore, throughput is better than the second scenario. However, it increases in the beginning and later it’s a bottleneck when the number of customer increases.




# Scenario 4:
 ![image](https://user-images.githubusercontent.com/79550954/158515761-7d4d093a-35c4-4b6c-91d6-6fb911941c2e.png)
![image](https://user-images.githubusercontent.com/79550954/158515772-00b47319-14bd-4c58-94c0-620e3e57f629.png)

 
In this scenario, throughput increases for laptop type in the beginning as the number of customer thread equals to expert engineer thread. It keeps on increasing but the bottleneck is reached when the resources available is limited and number of customers keeps increasing.
For all the scenario latency is inverse of the throughput.
