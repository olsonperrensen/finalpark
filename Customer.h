//
// Created by Admin on 8/5/2023.
//

#ifndef FINALPARK_CUSTOMER_H
#define FINALPARK_CUSTOMER_H


#include "Sys/User.h"

class Customer: public User {
private:
    std::string paymentMethod;
public:
//    dunder
    friend std::ostream& operator<<(std::ostream& os, const Customer& obj) {
        os << "Customer ( ID: " << obj.getID() << ", name: " << obj.getName() << ", address: " << obj.getAddress()
           << ", mail: " << obj.getMail() <<
           ", password: " << "**********"<<", paymentMethod: " << obj.paymentMethod<<" ) ";
        return os;
    }
    bool operator==(const User& other) const override {
        const Customer* derivedOther = dynamic_cast<const Customer*>(&other);
        if (derivedOther == nullptr) {
            // The other object is not of type Derived, so the objects are not equal.
            return false;
        }

        // Compare base class members and derived class members.
        return User::operator==(other) && (this->paymentMethod==derivedOther->paymentMethod);
    }
    Customer(std::string name,std::string address, std::string mail,std::string password,std::string location, std::string paymentMethod);
    Customer()=default;
    const std::string &getPaymentMethod() const;

    void setPaymentMethod(const std::string &paymentMethod);
//    Meta
    void modifyData(const Customer &updatedCustomer);
    std::string serialize() const;
    void deserialize(const std::string& data);


};


#endif //FINALPARK_CUSTOMER_H
