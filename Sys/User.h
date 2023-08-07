//
// Created by Admin on 8/4/2023.
//

#ifndef FINALPARK_USER_H
#define FINALPARK_USER_H
#include <string>
#include <iostream>

class User {
protected:
    static unsigned short int aantalUsers;
    unsigned short int userID;
    std::string name,address,mail;
public:
//    base dunder
    friend std::ostream& operator<<(std::ostream& os, const User& obj) {
        os << "User ( ID: " << obj.getID() << ", name: " << obj.getName() << ", address: " << obj.getAddress() << " ) ";
        return os;
    }
//    no (direct) User instance can ever be born.
    virtual bool operator==(const User& other) const {
        return (this->userID == other.userID)&&(this->name==other.name)&&(this->address==other.address)
        &&(this->mail==other.mail);
    }
    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getAddress() const;

    void setAddress(const std::string &address);

    const std::string &getMail() const;

    void setMail(const std::string &mail);

    unsigned short int getID() const;

public:
    User(std::string name, std::string address, std::string mail);
    virtual ~User() {}
};


#endif //FINALPARK_USER_H
