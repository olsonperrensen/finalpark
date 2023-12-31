//
// Created by r0834721 - vak YT6254 on 8/4/2023.
//

#ifndef FINALPARK_VACATIONPARCS_H
#define FINALPARK_VACATIONPARCS_H
#include <string>
#include <vector>
#include "Parcs.h"
#include "Sys/User.h"
#include "Shared.h"
#include "Booking.h"

// Inheriting from Parcs would cause duplicates since a VacationParc could have by its own:
// vp.getAccommodations().at(0); and at the same time
//   vp.getParcs().at(0).getAccommodations().at(0);
// Not worth the hassle. So no inheritance taking place. More of a composition relationship
// Note below
class VacationParcs{
private:
//    OWN way of saving Bookings... was bt here and in Customer but since it would be easier to manipulate
// bookings directly if it belongs to the Customer class I think here is a bit safer
    std::vector<Booking*> bookings;
public:
     std::vector<Booking *> &getBookings() ;

    void setBookings(const std::vector<Booking *> &bookings);

//    At individual level - good
    void addBooking(Booking* newBooking);

private:
    std::string VAT;
//    Voor alle duidelijkheid:
// ***********************************************************************************************
//    This attribute represents the collection of all the parks that the vacation company manages.
//    Each item in the vector is an instance of the Parcs class, which represents a single park.
//    This is necessary because a vacation company typically manages multiple parks.
//    If VacationParcs is meant to represent a company that manages multiple parks,
//    then it would make sense for it to have a std::vector<Parcs> parcs attribute.
// ***********************************************************************************************
    std::vector<Parcs*> parcs;
    std::vector<Customer*> customers;
public:
     std::vector<Customer *> &getCustomers() ;

    void setCustomers(const std::vector<Customer *> &customers);

private:
//    Managing a business so these attributes from Parc are redefined here for sole convenience
    std::string bizName;
    std::string bizAddress;
public:
    const std::string &getBizName() const;

    void setBizName(const std::string &bizName);

    const std::string &getBizAddress() const;

    void setBizAddress(const std::string &bizAddress);

     std::vector<Parcs *> &getParcs() ;

    void setParcs(const std::vector<Parcs *> &parcs);

public:
//    dunder
    friend std::ostream& operator<<(std::ostream& os, VacationParcs obj) {
        os << "VacationParcs ( name: " << obj.getBizName() << ", address: " << obj.getBizAddress()
           << ", VAT: " << obj.getVAT() << ", Parcs: [";

        std::vector<Parcs*> parcs = obj.getParcs();
        for (size_t i = 0; i < parcs.size(); ++i) {
            os << *parcs[i];

            // If not the last element, add a comma and a space
            if (i != parcs.size() - 1) {
                os << ", ";
            }
        }
        os << "], Customers: [";

        std::vector<Customer*> customers = obj.getCustomers();
        for (size_t i = 0; i < customers.size(); ++i) {
            os << *customers[i];

            // If not the last element, add a comma and a space
            if (i != customers.size() - 1) {
                os << ", ";
            }
        }

        os << "], Bookings: [";

        std::vector<Booking *> bookings = obj.getBookings();
        for (size_t i = 0; i < bookings.size(); ++i) {
            os << *bookings[i];

            // If not the last element, add a comma and a space
            if (i != bookings.size() - 1) {
                os << ", ";
            }
        }

        os << "])" << std::endl;

        return os;
    }
//    discarded due to n complexity being raised too high for the scope of this project...
//    friend std::ostream& operator<<(std::ostream& os, VacationParcs obj, std::string infoLevel) {
//        os << "VacationParcs ( name: " << obj.getBizName() << ", address: " << obj.getBizAddress()
//           << ", VAT: " << obj.getVAT() << ", Parcs: [";
//
//        std::vector<Parcs*> parcs = obj.getParcs();
//        for (size_t i = 0; i < parcs.size(); ++i) {
//            os << *parcs[i];
//
//            // If not the last element, add a comma and a space
//            if (i != parcs.size() - 1) {
//                os << ", ";
//            }
//        }
//        os << "], Customers: [";
//
//        std::vector<Customer*> customers = obj.getCustomers();
//        for (size_t i = 0; i < customers.size(); ++i) {
//            os << *customers[i];
//
//            // If not the last element, add a comma and a space
//            if (i != customers.size() - 1) {
//                os << ", ";
//            }
//        }
//
//        os << "], Bookings: [";
//
//        std::vector<Booking *> bookings = obj.getBookings();
//        for (size_t i = 0; i < bookings.size(); ++i) {
//            os << *bookings[i];
//
//            // If not the last element, add a comma and a space
//            if (i != bookings.size() - 1) {
//                os << ", ";
//            }
//        }
//
//        os << "])" << std::endl;
//
//        return os;
//    }

    bool operator==(const VacationParcs* other) const {
    return (this->VAT==other->VAT)&&(this->parcs==other->parcs)&&(this->customers==other->customers)&&
    (this->bizName==other->bizName)&&(this->bizAddress==other->bizAddress);
}
    VacationParcs()=default;
    VacationParcs(std::string name, std::string address,
                  std::string VAT, std::vector<Parcs*> parcs,
                  std::vector<Customer*> customers);
    //        trouwens use of Constructor Overloading
    VacationParcs(std::string name, std::string address,
                  std::string VAT, std::vector<Parcs*> parcs,
                  std::vector<Customer*> customers,std::vector<Booking*>bookings);

// CRUD for Parc
//    Make good use of templates
    void addPark(Parcs* park);
//    Full object removal
    void removePark(int id);
//    Partial removal -> Service removal inside of Parc, not Parc itself!
    void changeParkSrv(int parcID,int srvToBeChanged,bool state);
    //    Own logic for MGMT
    Parcs* findParcByID(int parkID);
// Solved by using changeParkSrv instead

    const std::string &getVAT() const;

    void setVAT(const std::string &vat);


// BULK CUSTOMER ADDITION, NOT WHAT WE WANT normally

//    individual Customer adding
    void addCustomer(Customer* neuCustomer);
//    //    VP part
////    individual Customer adding
////    CLI execs fun
    void registerCustomer(Customer *newCustomer);
};


#endif //FINALPARK_VACATIONPARCS_H
