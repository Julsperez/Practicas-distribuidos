Cliente: Cliente.cpp Solicitud.o SocketDatagrama.o PaqueteDatagrama.o msongoose.o	
	g++ -std=c++11 Cliente.cpp Solicitud.o SocketDatagrama.o PaqueteDatagrama.o mongoose.o -o Cliente -lpthread
mongoose.o: mongoose.c mongoose.h
	gcc mongoose.cpp -c
Solicitud.o: Solicitud.cpp Solicitud.h
	g++ Solicitud.cpp -c
SocketDatagrama.o: SocketDatagrama.cpp SocketDatagrama.h
	g++ SocketDatagrama.cpp -c
PaqueteDatagrama.o: PaqueteDatagrama.cpp  PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c