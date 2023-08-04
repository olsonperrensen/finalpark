#include <iostream>
#include "Parcs.h"
#include "VacationParcs.h"
#include <vector>
int main() {
    std::cout << "Hello, World!" << std::endl;

    LuxuryLevel l(false,false, false, false);
    std::vector<Accommodations> v;
    Accommodations a(1,13,2,false,l);
    v.push_back(a);
    Parcs::ParcServices s(false,false, false, false, false, false);
    std::vector<Parcs>pv;
    Parcs p("p","k",s,v);
    pv.push_back(p);
    Customer c("lee","hong lane 1","bruce@lee.vn");
    std::vector<Customer> cv;
    cv.push_back(c);
    VacationParcs vp("jonh", "lane 8", s,
                     v, "BE01", pv,
                     cv);

    std::vector<Parcs> vp2 = vp.getParcs();
    for (Parcs e:vp2) {
    e.removeAccommodation(1);
    }
    vp.removePark(1);
    return 0;
}
