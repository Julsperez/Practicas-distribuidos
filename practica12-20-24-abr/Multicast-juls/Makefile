receptor: receptor.o SocketMulticast.o PaqueteDatagrama.o
	g++ receptor.o SocketMulticast.o PaqueteDatagrama.o -o receptor
emisor: emisor.o SocketMulticast.o PaqueteDatagrama.o
	g++ emisor.o SocketMulticast.o PaqueteDatagrama.o -o emisor
receptor.o: receptor.cpp
	g++ receptor.cpp -c -Wall
emisor.o: emisor.cpp
	g++ emisor.cpp -c -Wall
SocketMulticast.o: SocketMulticast.cpp  SocketMulticast.h mensaje.h
	g++ SocketMulticast.cpp -c -Wall
PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h 
	g++ PaqueteDatagrama.cpp -c -Wall
clear:
	rm *.o receptor emisor