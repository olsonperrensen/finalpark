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
//TODO remove manual ID placing
    HotelRoom a(1,"Bahamas",12,false,1,12,32,false,l);
    Cabin* anew = new Cabin(2,2,2,false,l,3);
    HotelRoom anewnew(42,"Maldives",12,false,1,12,32,false,l);
    Cabin* afinal = new Cabin(999,2,2,false,l,3);
    std::vector<Accommodations*> vnew{&anewnew};
    v.push_back(&a);

    Parcs::ParcServices s(true,true, true, true, true, true);
    std::vector<Parcs*>pv;
    Parcs* p = new Parcs("Destination 1","bloemlaan 7",s,v);
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
    o.modifyPark(vp, 1, parkupdate);
//    o.deletePark(vp,1);
    o.createAccommodation(vp,2,anew);
    o.modifyAccommodations(vp,2,vnew);
//    o.deleteAccommodation(vp,2,999);
    if(0){
        int srv;
        std::cout << "Choose which services to remove:" << R"(
SUBTROPIC_SWIMMING_POOL=1,
SPORTS_INFRASTRUCTURE=2,
BOWLING_ALLEY=3,
BICYCLE_RENT=4,
CHILDRENS_PARADISE=5,
WATER_BIKES=6)" << std::endl << "Choose: ";
        std::cin >> srv;
        o.changeService(vp,2,srv,false);
    }
//    TODO just as you did with accommodations, remove all consts for customers so Employees can modify them
//TODO only accept true w/static cast, not 1
//TODO remove manual IDing
    Booking* b = new Booking(1,c,v,1,1,1,1);
    Employee e("Tom Sawyer","laanbaan 1", "tom@boom.be", "Bancontact",false);
    os.createCustomer(vp,neuc);

//TODO    Also accept on the fly creation
//    e.createCustomer(vp,new Customer("Mary Manson","Brusselsepoort 2", "mary@manson.no", "Payconiq"));
    os.modifyCustomer(vp,2,Customer("Bush Anderson","Manhattanweg 33", "mht@work.cn", "Contant Geld"));

    std::cout << "Customers present in VP:\n";
    for (auto e:vp.getCustomers()) {
//        TODO fix ID being replaced
    std::cout << std::endl << "Customer ID: "<<e->getID() << std::endl;
    }
//    TODO update dunder str so vp outputs Bookings as well

    os.bookAccommodation(vp,1,1,b);
    os.modifyBooking(vp,1,Booking(72,neuc,v,0,1,0,1));
//    TODO prevent change ID Booking
//    e.deleteBooking(vp,72);
//    e.deleteCustomer(vp,1);
//individual modifying
    os.modifyAccommodation(vp,2,1,afinal);
    c->modifyData(Customer("Larry Page","Sergeistraat 9", "larry@goo.gl", "Bancontact"));

    std::cout << vp;
//TODO find by id Booking
    return 0;
//    TODO implement polymorphism -> pointer getting the right call
}
