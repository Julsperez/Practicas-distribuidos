all:
	g++ Solicitud.cpp -c
	g++ Respuesta.cpp -c
	g++ PaqueteDatagrama.cpp -c
	g++ SocketMulticast.cpp -c
	g++ PaqueteDatagrama.o SocketMulticast.o Respuesta.o servidor.cpp -o srv
	g++ PaqueteDatagrama.o SocketMulticast.o Solicitud.o cliente.cpp -o cli
