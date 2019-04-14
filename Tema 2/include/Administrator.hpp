#pragma once
#include "Angajat.hpp"

class Administrator : public Angajat {
    int sectie;
public:
    Administrator(char* n, float sal, int sec);
    Administrator(const Administrator& r);
    int getSection();
};
