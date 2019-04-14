#include "Angajat.hpp"
#include <iostream>
#include <string.h>

Angajat::~Angajat() {
  delete [] nume;
}

Angajat::Angajat() {
    this->salariu = 0.0;
    this->nume = new char[40];
    strcpy(nume, "");
}

Angajat::Angajat(char* n, float sal) {
    this->salariu = sal; 
    this->nume = new char[strlen(n) + 1];
    strcpy(nume, n);
}

Angajat::Angajat(const Angajat &r) {
     this->salariu = r.salariu;
     this->nume = new char[strlen(r.nume) + 1];
     strcpy(nume, r.nume);
}

void Angajat::display() {
     std::cout << "Angajat: [" << this->nume<<"] Salariu: [" << this->salariu << "] ";
}

float Angajat::getSalariu() {
    return this->salariu;
};

void  Angajat::setSalariu(float s) {
    this->salariu = s;
};