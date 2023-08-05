//
// Created by Admin on 8/5/2023.
//

#include "Customer.h"
#include "Shared.h"

const std::string &Customer::getPaymentMethod() const {
    return paymentMethod;
}

void Customer::setPaymentMethod(const std::string &paymentMethod) {
    if(std::find(PAYMENT_METHODS.begin(),PAYMENT_METHODS.end(),paymentMethod)!=PAYMENT_METHODS.end())
        Customer::paymentMethod = paymentMethod;
}

Customer::Customer(std::string name,
                   std::string address, std::string mail, std::string paymentMethod) : User(name, address, mail),
                   paymentMethod(paymentMethod){

}
