#include <iostream>
#include "Parcs.h"
#include "VacationParcs.h"
#include "Owner.h"
#include "Booking.h"
#include <vector>
int main() {
    std::cout << "Hello, World!" << std::endl;

    LuxuryLevel l(false,false, false, false,"Best in town");
    std::vector<Accommodations> v;

    Accommodations a(1,13,2,false,l);
    Accommodations anew(66,2,4,true,l);
    Accommodations anewnew(999,9,9,true,l);
    std::vector<Accommodations> vnew{anewnew};
    v.push_back(a);

    Parcs::ParcServices s(false,false, false, false, false, false);
    std::vector<Parcs>pv;
    Parcs p("Destination 1","bloemlaan 7",s,v);
    pv.push_back(p);
    Customer c("Bruce Lee","hongkongstraat 178", "blee@hotmail.co.uk", "Bancontact");
    std::vector<Customer> cv;
    cv.push_back(c);

    VacationParcs vp("jonh", "lane 8", "BE01", pv,
                     cv);
//std::string name, std::string address, ParcServices services, std::vector<Accommodations> accommodations
    Parcs parkupdate("SAM", "Kyotostraat 88", s,
                     v);

    std::vector<Parcs> vp2 = vp.getParcs();
//    for (Parcs e:vp2) {
//    e.removeAccommodation(1);
//    }
//    vp.removePark(1);
//    User test
    Owner o("Bruce","Kennisstraat 13","Lee@Lee.lee");
    o.modifyPark(vp, 1, parkupdate);
//    o.deletePark(vp,1);
    o.createAccommodation(vp,2,anew);
    o.modifyAccommodations(vp,2,vnew);
    o.deleteAccommodation(vp,2,999);
//    TODO just as you did with accommodations, remove all consts for customers so Employees can modify them
    std::cout << vp;
//TODO only accept true w/static cast, not 1
    Booking b(1,c,v,1,1,1,1);
//TODO accommodationKind should only come from a shared.h array
//TODO find by id Booking
//   std::cout << b;
    return 0;
}
