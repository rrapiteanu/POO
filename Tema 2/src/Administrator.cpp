#include "Administrator.hpp"

Administrator::Administrator(char* n, float sal, int sec):Angajat(n, sal) {
    this->sectie = sec;
}

Administrator::Administrator(const Administrator &r):Angajat(r) {
    this->sectie = r.sectie;
}

int Administrator::getSection() {
    return this->sectie;
};