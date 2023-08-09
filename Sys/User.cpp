//
// Created by Admin on 8/4/2023.
//

#include "User.h"
// Have no parks at the beginning of the program
unsigned short int User::aantalUsers = 0;

User::User(std::string name, std::string address, std::string mail,std::string password,std::string location):
name(name), address(address), mail(mail),password(password),location(location){
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

unsigned short int User::getID() const {
    return userID;
}

const std::string &User::getPassword() const {
    return password;
}

void User::setPassword(const std::string &password) {
    User::password = password;
}

const std::string &User::getLocation() const {
    return location;
}

void User::setLocation(const std::string &location) {
    User::location = location;
}
