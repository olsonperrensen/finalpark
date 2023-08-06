//
// Created by Admin on 8/5/2023.
//

#include "Employee.h"

Employee::Employee(std::string name, std::string address, std::string mail, std::string paymentMethod,bool isOnLeave) :
Customer(name,address,mail,paymentMethod),isOnLeave(isOnLeave){

}

void Employee::createCustomer(VacationParcs &company, const Customer &newCustomer) {
    company.addCustomer(newCustomer);
}

void Employee::modifyCustomer(VacationParcs &company, int userID, const Customer &updatedCustomer) {
    if (Customer* customer = findItemByID(company.getCustomers(), userID)) {
        *customer = updatedCustomer;
        std::cout << "Customer " << userID << " has been modified successfully." << std::endl;
        return;
    }
    std::cout << "Error: Customer not found.\n";
}
