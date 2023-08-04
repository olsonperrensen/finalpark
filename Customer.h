//
// Created by Admin on 8/4/2023.
//

#ifndef FINALPARK_CUSTOMER_H
#define FINALPARK_CUSTOMER_H
#include <string>
#include <iostream>

class Customer {
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
    Customer(std::string name, std::string address, std::string mail);
};


#endif //FINALPARK_CUSTOMER_H
