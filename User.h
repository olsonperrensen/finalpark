//
// Created by Admin on 8/4/2023.
//

#ifndef FINALPARK_USER_H
#define FINALPARK_USER_H
#include <string>
#include <iostream>

class User {
private:
    std::string name,address,mail;
public:
    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getAddress() const;

    void setAddress(const std::string &address);

    const std::string &getMail() const;

    void setMail(const std::string &mail);

public:
    User(std::string name, std::string address, std::string mail);
};


#endif //FINALPARK_USER_H
