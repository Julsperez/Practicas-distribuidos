#include "SocketDatagrama.h"

using namespace std;

int main(int argc, char const *argv[]){
	cout << "Servidor iniciado..."<<endl;
	SocketDatagrama socket = SocketDatagrama(7300);
    int * numeros;
    
    while(1){
    	PaqueteDatagrama datagrama = PaqueteDatagrama( 2 * sizeof(int));
	    socket.recibe(datagrama);
	    numeros = (int *) datagrama.obtieneDatos();
	    
	    int resultado[1];
	    resultado[0] = numeros[0] + numeros[1];
	    cout << "Se ha establecido conexion:" << endl;
	    cout << "Cliente: " << datagrama.obtieneDireccion() << endl;
	    cout << "Puerto: " << datagrama.obtienePuerto() << endl;
	    cout << "Numeros [" << numeros[0] << "] y [" << numeros[1] << "]" << endl;
	    cout << "Se regresa resultado: " << *resultado << endl;
	    PaqueteDatagrama datagramaRegreso =  PaqueteDatagrama((char*) resultado, sizeof(int), datagrama.obtieneDireccion(), datagrama.obtienePuerto());
	    socket.envia(datagramaRegreso);
	}
	
	return 0;
}
