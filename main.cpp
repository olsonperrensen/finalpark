#include <iostream>
#include "Parcs.h"
#include "VacationParcs.h"
#include "Sys/Owner.h"
#include "Booking.h"
#include "Sys/Employee.h"
#include "Sys/OS.h"
#include "HotelRoom.h"
#include "Cabin.h"
#include <vector>
int main() {
    OS os;
    std::cout << "Hello, World!" << std::endl;

    LuxuryLevel l(false,false, false, false,"Cabin");
    std::vector<Accommodations*> v;
//TODO remove manual IDing
    HotelRoom a(1,"Bahamas",12,false,1,12,32,false,l);
    Cabin* anew = new Cabin(2,2,2,false,l,3);
    HotelRoom anewnew(42,"Maldives",12,false,1,12,32,false,l);
    Cabin* afinal = new Cabin(999,2,2,false,l,3);
    std::vector<Accommodations*> vnew{&anewnew};
    v.push_back(&a);

    Parcs::ParcServices s(true,true, true, true, true, true);
    Parcs::ParcServices ss(false,false, true, true, false, true);
    std::vector<Parcs*>pv;
    Parcs* p = new Parcs("THE FIRST AWESOME PARK","bloemlaan 7",s,v);
    pv.push_back(p);
    Customer* c = new Customer("Bruce Lee","hongkongstraat 178", "blee@hotmail.co.uk", "Bancontact");
    Customer* neuc = new Customer("Mary Manson","Brusselsepoort 2", "mary@manson.no", "Payconiq");

    std::vector<Customer*> cv;
    cv.push_back(c);

    VacationParcs vp("jonh", "lane 8", "BE01", pv,
                     cv);
//std::string name, std::string address, ParcServices services, std::vector<Accommodations> accommodations
    Parcs parkupdate("SAM", "Kyotostraat 88", s,
                     v);

    std::vector<Parcs*> vp2 = vp.getParcs();
//    for (Parcs e:vp2) {
//    e.removeAccommodation(1);
//    }
//    vp.removePark(1);
//    User test
    Owner o("Bruce","Kennisstraat 13","Lee@Lee.lee");
    o.createPark(vp, new Parcs("THE RESORT OF YOUR DREAMS!","Hollandsebaan 2",ss,vnew));
////    o.modifyPark(vp, 1, parkupdate);
//    o.deletePark(vp,3);
//    o.createAccommodation(vp,2,anew);
//    o.modifyAccommodations(vp,2,vnew);
////    o.deleteAccommodation(vp,2,999);
    if(1){
        int srv,pid;
//        TODO offer names instead with for-range based loop
        std::cout << "Choose parkID:";
        std::cin >> pid;
        std::cout << "\nChoose which services to remove:" << R"(
SUBTROPIC_SWIMMING_POOL=1,
SPORTS_INFRASTRUCTURE=2,
BOWLING_ALLEY=3,
BICYCLE_RENT=4,
CHILDRENS_PARADISE=5,
WATER_BIKES=6)" << std::endl << "Choose: ";
        std::cin >> srv;
        o.changeService(vp,pid,srv,false);
    }
////TODO only accept true w/static cast, not 1
//    Booking* b = new Booking(1,c,v,1,1,1,1);
//    Employee e("Tom Sawyer","laanbaan 1", "tom@boom.be", "Bancontact",false);
//    os.createCustomer(vp,neuc);
//    os.modifyCustomer(vp,2,Customer("Bush Anderson","Manhattanweg 33", "mht@work.cn", "Contant Geld"));
//
//    std::cout << "Customers present in VP:\n";
//    for (auto e:vp.getCustomers()) {
////        TODO fix ID being replaced on all modify methods!
//        std::cout << std::endl << "Customer ID: " << e->getID() << std::endl;
//    }
//
//    os.bookAccommodation(vp,1,1,b);
//    os.modifyBooking(vp,1,Booking(72,neuc,v,0,1,0,1));
////    e.deleteBooking(vp,72);
////    e.deleteCustomer(vp,1);
////individual modifying
//    os.modifyAccommodation(vp,2,1,afinal);
//    c->modifyData(Customer("Larry Page","Sergeistraat 9", "larry@goo.gl", "Bancontact"));
//
//    std::cout << vp;
    return 0;
}
