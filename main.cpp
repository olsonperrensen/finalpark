#include <iostream>
#include "Parcs.h"
#include "VacationParcs.h"
#include "Owner.h"
#include <vector>
int main() {
    std::cout << "Hello, World!" << std::endl;

    LuxuryLevel l(false,false, false, false);
    std::vector<Accommodations> v;
    Accommodations a(1,13,2,false,l);
    Accommodations anew(66,2,4,true,l);
    v.push_back(a);
    Parcs::ParcServices s(false,false, false, false, false, false);
    std::vector<Parcs>pv;
    Parcs p("Destination 1","bloemlaan 7",s,v);
    pv.push_back(p);
    Customer c("Bruce Lee","hongkongstraat 178", "blee@hotmail.co.uk", "Bancontact");
    std::vector<Customer> cv;
    cv.push_back(c);
    VacationParcs vp("jonh", "lane 8", s,
                     v, "BE01", pv,
                     cv);
//    TODO convert to explicit so NO VacationParcs can go ipv Parcs (derived attributes get lost)
    VacationParcs vpupdate("SAM", "Kyotostraat 88", s,
                     v, "FI01", pv,
                     cv);

    std::vector<Parcs> vp2 = vp.getParcs();
//    for (Parcs e:vp2) {
//    e.removeAccommodation(1);
//    }
//    vp.removePark(1);
//    User test
    Owner o("Bruce","Kennisstraat 13","Lee@Lee.lee");
    o.modifyPark(vp, 1, vpupdate);
//    o.deletePark(vp,1);
    o.createAccommodation(vp,3,anew);
//    TODO change does not take effect ... Index 1 is out of range where it should've been created
    std::cout << vp.getAccommodations().at(0);
    return 0;
}
