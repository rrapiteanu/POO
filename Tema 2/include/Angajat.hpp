#pragma once

class Angajat {

    char* nume;
    float salariu;

public:
    ~Angajat();
    Angajat();
    Angajat(char* n, float sal);
    Angajat(const Angajat &r);
    void display();
    float getSalariu();
    void setSalariu(float s);
};
