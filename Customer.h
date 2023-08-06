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
           << ", mail: " << obj.getMail() << ", paymentMethod: " << obj.paymentMethod<<" ) ";
        return os;
    }

    Customer(std::string name,std::string address, std::string mail, std::string paymentMethod);
    const std::string &getPaymentMethod() const;

    void setPaymentMethod(const std::string &paymentMethod);
//    Meta
    void modifyData(const Customer &updatedCustomer);
};


#endif //FINALPARK_CUSTOMER_H
