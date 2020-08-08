#include "RegistroVotos.h"
#include <iostream>

using namespace std;

RegistroVotos::RegistroVotos() {
  numVotosSA = 0;
  numVotosSB = 0;
}

int RegistroVotos::getVotosSA() {
  return numVotosSA;
}

int RegistroVotos::getVotosSB() {
  return numVotosSB;
}

void RegistroVotos::setVotosSA(int numVotos) {
  numVotosSA = numVotos;
}

void RegistroVotos::setVotosSB(int numVotos) {
  numVotosSB = numVotos;
}
