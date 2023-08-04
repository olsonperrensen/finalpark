//
// Created by Admin on 8/4/2023.
//

#include "Customer.h"


Customer::Customer(std::string name, std::string address, std::string mail):name(name),address(address),mail(mail){
}

const std::string &Customer::getName() const {
    return name;
}

void Customer::setName(const std::string &name) {
    Customer::name = name;
}

const std::string &Customer::getAddress() const {
    return address;
}

void Customer::setAddress(const std::string &address) {
    Customer::address = address;
}

const std::string &Customer::getMail() const {
    return mail;
}

void Customer::setMail(const std::string &mail) {
    Customer::mail = mail;
}
