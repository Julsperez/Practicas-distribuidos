#include "SocketDatagrama.h"

using namespace std;

int main(int argc, char const *argv[]){
	SocketDatagrama socket = SocketDatagrama(0);
    int numeros[2];
    numeros[0] = 5;
    numeros[1] = 3;

    cout << "Calculando: " << numeros[0] << " + " << numeros[1] << endl;
    PaqueteDatagrama datagramaEnvia = PaqueteDatagrama((char *) numeros, 2 * sizeof(int), "127.0.0.1", 7300);
    socket.envia(datagramaEnvia);
    
    PaqueteDatagrama datagramaRecibe =  PaqueteDatagrama(sizeof(int));
    socket.recibe(datagramaRecibe);
    printf("Recibido de: %s puerto %i ", datagramaRecibe.obtieneDireccion(), datagramaRecibe.obtienePuerto());
    int * ans = (int*)datagramaRecibe.obtieneDatos();
    cout << "Reusltado: " << *ans << endl;
    return 0;
}
