#include <iostream>
#include <sys/time.h>

using namespace std;

int main(int argc, char const *argv[]){
	
	while(1){

		 //gettimeofday
		 timeval tim;
		 char buffer[80];
    	 gettimeofday(&tim,NULL);
    	 double segundos = tim.tv_sec;
    	 double microsec = tim.tv_usec;

    	 //localtime
    	 time_t rawtime;
  		 struct tm * timeinfo;

  		 time (&rawtime);
  		 timeinfo = localtime (&rawtime);
 		 strftime (buffer,80,"%X",timeinfo);
 		 cout << buffer << "." << microsec << endl;
	}
	return 0;
}