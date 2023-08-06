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
    else
        throw std::invalid_argument("\nPlease choose a valid payment method. Valid options:\n+ " + PAYMENT_METHODS[0]
        + "\n+ " + PAYMENT_METHODS[1] + "\n+ " + PAYMENT_METHODS[2] + "\nYour option was:\n- "+paymentMethod+"\nTry again.\n");

}

Customer::Customer(std::string name,
                   std::string address, std::string mail, std::string paymentMethod) : User(name, address, mail){
//    Idem as with accomodationKind, can't list init due to check
    setPaymentMethod(paymentMethod);
}
