//
// Created by Admin on 8/4/2023.
//

#include "User.h"
// Have no parks at the beginning of the program
int User::aantalUsers = 0;

User::User(std::string name, std::string address, std::string mail): name(name), address(address), mail(mail){
    this->userID = ++User::aantalUsers;
}

const std::string &User::getName() const {
    return name;
}

void User::setName(const std::string &name) {
    User::name = name;
}

const std::string &User::getAddress() const {
    return address;
}

void User::setAddress(const std::string &address) {
    User::address = address;
}

const std::string &User::getMail() const {
    return mail;
}

void User::setMail(const std::string &mail) {
    User::mail = mail;
}

int User::getID() const {
    return userID;
}
