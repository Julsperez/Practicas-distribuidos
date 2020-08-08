#ifndef REGISTROVOTOS_H_
#define REGISTROVOTOS_H_

class RegistroVotos{
  private:
    int numVotosSA;
    int numVotosSB;
  public:
    RegistroVotos();
    int getVotosSA();
    int getVotosSB();
    void setVotosSA(int numVotos);
    void setVotosSB(int numVotos);
}

#endif
