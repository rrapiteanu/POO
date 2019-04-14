#include <iostream>
#include "Angajat.hpp"
#include "Administrator.hpp"

using namespace std;

int main() {
	
    char* angajat = new char[40];
    float salariu;

    cout << "Nume angajat: ";
    cin.getline(angajat, 40);
    cout << "Salariu: ";
    cin >> salariu;

    Angajat A(angajat, salariu);
    A.display();
    cout << endl;

    Administrator B("Admin Test", 26500.0, 1);
    B.display();
    cout << "Sectia: [" << B.getSection() << "]" << endl;

    delete[] angajat;

    return 0;
}
