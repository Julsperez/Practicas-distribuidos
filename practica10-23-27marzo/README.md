### Compilar 
make -f MakefileServidor.makefile <br>
make -f MakefileCliente.makefile

### Ejecutar
./Servidor <puerto_local> <br>
./Cliente <ip_foranea> <puerto_foraneo> <num1> <num2>
  
### Ejemplo
./Servidor 7200 <br>
./Cliente 127.0.0.1 7200 5 2

#### Si hay error de "permission denied" al ejecutar alguno, ejecutar comando
sudo chmod 777 *

