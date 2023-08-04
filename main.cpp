#include <iostream>
#include "Parcs.h"
#include <vector>
int main() {
    std::cout << "Hello, World!" << std::endl;
    LuxuryLevel l(false,false, false, false);
    std::vector<Accommodations> v;
    Accommodations a(1,13,2,false,l);
    Parcs::ParcServices s(false,false, false, false, false, false);
    Parcs p("p","k",s,v);
    std::cout << p.getParcId();
    return 0;
}
