Servidor: Servidor.cpp Respuesta.o SocketDatagrama.o PaqueteDatagrama.o
	g++ Servidor.cpp Respuesta.o SocketDatagrama.o PaqueteDatagrama.o -o Servidor
Cliente: Cliente.cpp Solicitud.o SocketDatagrama.o PaqueteDatagrama.o
	g++ Cliente.cpp Solicitud.o SocketDatagrama.o PaqueteDatagrama.o -o Cliente
Respuesta.o: ./dependencies/Respuesta.cpp ./dependencies/Respuesta.h
	g++ ./dependencies/Respuesta.cpp -c
Solicitud.o: ./dependencies/Solicitud.cpp ./dependencies/Solicitud.h
	g++ ./dependencies/Solicitud.cpp -c
SocketDatagrama.o: ./dependencies/SocketDatagrama.cpp ./dependencies/SocketDatagrama.h
	g++ ./dependencies/SocketDatagrama.cpp -c
PaqueteDatagrama.o: ./dependencies/PaqueteDatagrama.cpp  ./dependencies/PaqueteDatagrama.h
	g++ ./dependencies/PaqueteDatagrama.cpp -c
clear:
	rm *.o Servidor Cliente
