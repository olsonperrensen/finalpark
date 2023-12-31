//
// Created by r0834721 - vak YT6254 on 8/5/2023.
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
                   std::string address, std::string mail, std::string password,std::string location,std::string paymentMethod) :
                   User(name, address, mail,password,location){
//    Idem as with accomodationKind, can't list init due to check
    setPaymentMethod(paymentMethod);
}

void Customer::modifyData(const Customer &updatedCustomer) {
//    Learning note: *this dereferences the current instance (which "this" points to 0x RAM address)
// by doing *this you allow the content of the instance pointer to be accessed and, zoals in this case,
// rewritten
    *this = updatedCustomer;
    std::cout << "Customer " << this->getID() << " has updated their data successfully." << std::endl;
}

std::string Customer::serialize() const {
    return std::to_string(userID) + "_" + name + "_" + address + "_" + mail + "_" + password + "_" + location + "_" + paymentMethod;
}

void Customer::deserialize(const std::string& data) {
    std::stringstream ss(data);
    std::string tmp;
    std::getline(ss, tmp, '_');
    userID = std::stoi(tmp);
    std::getline(ss, name, '_');
    std::getline(ss, address, '_');
    std::getline(ss, mail, '_');
    std::getline(ss, password, '_');
    std::getline(ss, location, '_');
    std::getline(ss, paymentMethod, '_');
}
