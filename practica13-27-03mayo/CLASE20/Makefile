Servidor: Servidor.cpp Respuesta.o SocketDatagrama.o PaqueteDatagrama.o
	g++ Servidor.cpp Respuesta.o SocketDatagrama.o PaqueteDatagrama.o -o Servidor
Cliente: Cliente.cpp Solicitud.o SocketDatagrama.o PaqueteDatagrama.o
	g++ Cliente.cpp Solicitud.o SocketDatagrama.o PaqueteDatagrama.o -o Cliente
Respuesta.o: Respuesta.cpp Respuesta.h
	g++ Respuesta.cpp -c
Solicitud.o: Solicitud.cpp Solicitud.h
	g++ Solicitud.cpp -c
SocketDatagrama.o: SocketDatagrama.cpp SocketDatagrama.h
	g++ SocketDatagrama.cpp -c
PaqueteDatagrama.o: PaqueteDatagrama.cpp  PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c