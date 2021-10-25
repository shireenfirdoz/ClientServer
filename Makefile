simple_server_objects = ServerStub.o Socket.o ServerFactory.o
simple_client_objects = ClientStub.o Socket.o ClientFactory.o


all : simple_server simple_client

simple_server: $(simple_server_objects)
	g++ -pthread -o simple_server $(simple_server_objects)


simple_client: $(simple_client_objects)
	g++ -pthread -o simple_client $(simple_client_objects) 


Socket:	Socket.cpp
ServerSocket:	ServerStub.cpp
ClientSocket:	ClientStub.cpp
ServerFactory: ServerFactory.cpp
ClientFactory: ClientFactory.cpp 


clean:	rm -f *.o simple_server simple_client

