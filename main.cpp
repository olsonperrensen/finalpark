#include <iostream>
#include "Parcs.h"
#include "VacationParcs.h"
#include "Sys/Owner.h"
#include "Booking.h"
#include "Sys/Employee.h"
#include "Sys/OS.h"
#include "HotelRoom.h"
#include "Cabin.h"
#include "Sys/FileIO.h"
#include "Shared.h"
#include <vector>
#include <limits>

Parcs* cliNewPark();
Parcs::ParcServices* cliNewSrv();
Accommodations* cliNewAccommo();
Customer* cliNewCust();
Booking* cliNewBkn();

void displayMainMenu();
void displayOwnerMenu();
void displayCustomerMenu();
void displayEmployeeMenu();

void manageParc(Parcs *selectedParc);

VacationParcs* company = nullptr;

int main() {
    std::cout << "Welcome to VacationParcs Management System! " << std::endl;
    std::cout << "Is this your first time using the app (1) or would you like to load from a file (2) ?"<< std::endl;
    int choice;
    choice= getInt(1,2);
    std::string name, address, VAT;
    if (choice == 1) {
        {// Gather data for VacationParcs
            std::cout << "Enter details for the VacationParcs company:\n";
            std::cout << "\tName: ";
            std::cin.clear();  // Clear any errors
            conditionalIgnore();
            std::getline(std::cin, name);

            std::cout << "\tAddress: ";
            std::cin.clear();  // Clear any errors
            conditionalIgnore();
            std::getline(std::cin, address);
            std::cout << "\tVAT: ";
            std::cin.clear();  // Clear any errors
            conditionalIgnore();  // Discard any leftover characters in the buffer
            std::getline(std::cin, VAT);
        }

        Parcs* newParc = cliNewPark();
        Customer* newCustomer = cliNewCust();

        // Create the VacationParcs company with the gathered data
        company = new VacationParcs(name, address, VAT, {newParc}, {newCustomer});
    } else if (choice == 2) {
        std::vector<Customer*>cv;
        std::vector<Parcs*>pv;
        std::vector<Booking*>bv;
        {// Gather data for VacationParcs
            std::cout << "Due to security reasons, please provide us with the following information of your VacationParc:\n";
            std::cout << "\tName: ";
            std::cin.clear();  // Clear any errors
            conditionalIgnore();
            std::getline(std::cin, name);

            std::cout << "\tAddress: ";
            std::cin.clear();  // Clear any errors
            conditionalIgnore();
            std::getline(std::cin, address);
            std::cout << "\tVAT: ";
            std::cin.clear();  // Clear any errors
            conditionalIgnore();  // Discard any leftover characters in the buffer
            std::getline(std::cin, VAT);
        }
        std::cout << "Thank you. Loading rest of data...\n";
        loadFromFile(cv,CUSTOMERS_BESTAND);
        loadFromFile(pv,PARCS_BESTAND);

//        trouwens use of Constructor Overloading
        company = new VacationParcs(name, address, VAT, pv, cv,bv);
        //        simulating booking
        company->addBooking(new Booking(1, cv.at(0), pv.at(0)->getAccommodations(), 1,
                                        1, 0, 1,new Datum(1,7,2003), new Datum(2,7,2003),"ACCEPTED"));
    } else {
        std::cout << "Invalid choice. Exiting...\n";
        return 0;
    }

    // Now, you can display the main menu and work with the company object
    displayMainMenu();

    // Don't forget to clean up any dynamically allocated memory before exiting
    delete company;

    return 0;
}




Parcs* cliNewPark(){
    std::string parcName, parcAddress;
    std::vector<Accommodations*> accommodations;
    Accommodations* accommo;
    Parcs::ParcServices* services;

    // Gather data for Parcs
    std::cout << "\tEnter details for a Parc:\n";
    std::cout << "\t\tName: ";
    std::cin.clear();  // Clear any errors
    conditionalIgnore();  // Discard any leftover characters in the buffer
    std::getline(std::cin, parcName);

    std::cout << "\t\tAddress: ";
    std::cin.clear();  // Clear any errors
    conditionalIgnore();  // Discard any leftover characters in the buffer
    std::getline(std::cin, parcAddress);

    services = cliNewSrv();
    accommo = cliNewAccommo();
    accommodations.push_back(accommo);
    return new Parcs(parcName, parcAddress, services, accommodations);
}

Accommodations* cliNewAccommo(){
    std::string accommodationKind;
    bool bathroomWithBath,
            BBQ, surroundSystem, breakfastService, cleaningService;
    int nrPeople, size;
    LuxuryLevel* luxury;
    std::cout << "\t\t\tEnter accommodation details: ";
//        shared attr
    std::cout << "\t\t\t\tNumber of People: ";
    nrPeople=getInt(1,22);
    std::cout << "\t\t\t\tSize: ";
    size=getInt(1,22);
    std::cout << "\t\t\t\tBathroom with Bath ";
    bathroomWithBath= getBool();
// Gather data for LuxuryLevel
    std::cout << "\t\t\t\tEnter details for Luxury Level:\n";
    std::cout << "\t\t\t\t\tBBQ ";
    BBQ= getBool();
    std::cout << "\t\t\t\t\tSurround System ";
    surroundSystem= getBool();
    std::cout << "\t\t\t\t\tBreakfast Service ";
    breakfastService= getBool();
    std::cout << "\t\t\t\t\tCleaning Service ";
    cleaningService= getBool();
    std::cout << "\t\t\t\t\tAccommodation Kind: ";
    std::cin.clear();  // Clear any errors
    conditionalIgnore();  // Discard any leftover characters in the buffer
    std::getline(std::cin, accommodationKind);
    if (accommodationKind == "HotelRoom") {
        std::string hotelRoomLocation;
        int floor, nrBeds;
        bool childrenBed;

        std::cout << "\t\t\t\t\tEnter details for HotelRoom:\n";
        std::cout << "\t\t\t\t\t\tChildren Bed ";
        childrenBed= getBool();
        std::cout << "\t\t\t\t\t\tFloor: ";
        floor=getInt(1,22);
        std::cout << "\t\t\t\t\t\tLocation: ";
        std::cin.clear();  // Clear any errors
        conditionalIgnore();  // Discard any leftover characters in the buffer
        std::getline(std::cin, hotelRoomLocation);
        std::cout << "\t\t\t\t\t\tNumber of Beds: ";
        nrBeds=getInt(1,22);

        luxury = new LuxuryLevel(BBQ, surroundSystem, breakfastService, cleaningService, accommodationKind);
        return new HotelRoom(nrPeople, size, bathroomWithBath, luxury, childrenBed, floor, hotelRoomLocation, nrBeds);


    } else if (accommodationKind == "Cabin") {
        int bedrooms;

        std::cout << "\t\t\t\t\tEnter details for Cabin:\n";
        std::cout << "\t\t\t\t\t\tNumber of Bedrooms: ";
        bedrooms=getInt(1,22);

        luxury = new LuxuryLevel(BBQ, surroundSystem, breakfastService, cleaningService, accommodationKind);
        return new Cabin(nrPeople, size, bathroomWithBath, luxury, bedrooms);
    } else {
        throw std::invalid_argument("Invalid choice for accommodation type.\n");
    }
}
Parcs::ParcServices* cliNewSrv(){
    bool subtropicSwimmingPool, sportsInfrastructure, bowlingAlley, bicycleRent, childrensParadise, waterBikes;
    std::cout << "\t\tEnter details for Parc Services:\n";
    std::cout << "\t\t\tSubtropic Swimming Pool ";
    subtropicSwimmingPool= getBool();
    std::cout << "\t\t\tSports Infrastructure ";
    sportsInfrastructure = getBool();
    std::cout << "\t\t\tBowling Alley ";
    bowlingAlley= getBool();
    std::cout << "\t\t\tBicycle Rent ";
    bicycleRent= getBool();
    std::cout << "\t\t\tChildren's Paradise ";
    childrensParadise= getBool();
    std::cout << "\t\t\tWater Bikes ";
    waterBikes= getBool();
    return new Parcs::ParcServices(subtropicSwimmingPool, sportsInfrastructure, bowlingAlley, bicycleRent, childrensParadise, waterBikes);
}
Customer* cliNewCust(){
    std::string customerName, customerAddress, mail, password, location, paymentMethod;
    // Gather data for Customer
    std::cout << "\tEnter details for a Customer:\n";
    std::cout << "\t\tName: ";
    std::cin.clear();  // Clear any errors
    conditionalIgnore();  // Discard any leftover characters in the buffer
    std::getline(std::cin, customerName);
    std::cout << "\t\tAddress: ";
    std::cin.clear();  // Clear any errors
    conditionalIgnore();  // Discard any leftover characters in the buffer
    std::getline(std::cin, customerAddress);
    std::cout << "\t\tMail: ";
    std::cin.clear();  // Clear any errors
    conditionalIgnore();  // Discard any leftover characters in the buffer
    std::getline(std::cin, mail);
    std::cout << "\t\tPassword: ";
    std::cin.clear();  // Clear any errors
    conditionalIgnore();  // Discard any leftover characters in the buffer
    std::getline(std::cin, password);
    std::cout << "\t\tLocation: ";
    std::cin.clear();  // Clear any errors
    conditionalIgnore();  // Discard any leftover characters in the buffer
    std::getline(std::cin, location);
    std::cout << "\t\tPayment Method: ";
    std::cin.clear();  // Clear any errors
    conditionalIgnore();  // Discard any leftover characters in the buffer
    std::getline(std::cin, paymentMethod);
    return new Customer(customerName, customerAddress, mail, password, location, paymentMethod);
}
Booking* cliNewBkn(){
    static int bookingID{0};
    int ID,jaar,maand,dag;
    Customer* customer;
    std::vector<Accommodations*> accommodations;
    bool activityPass, sportsPass, bicycleRent, swimmingPass;
    Datum* beginDate, *endDate;
    std::string status;

    // Ask for ID
    //    ID = ++bookingID;
    std::cout << "Enter Booking ID: ";
    ID = getInt(1,std::numeric_limits<int>::max());

    // Ask for Customer
    int customerID;
    std::cout << "Enter Customer ID: ";
    customerID = getInt(1,std::numeric_limits<int>::max());
    customer = findItemByID(company->getCustomers(), customerID);
    if (!customer) {
        std::cout << "Customer "<< std::to_string(customerID) << " not found. Exiting...\n";
        return nullptr;
    }

    // Ask for Accommodations
    int numAccommodations;
    std::cout << "How many accommodations for this booking? ";
    numAccommodations = getInt(1,std::numeric_limits<int>::max());
    for (int i = 0; i < numAccommodations; i++) {
        int accommodationID;
        std::cout << "Enter ID of accommodation " << (i + 1) << ": ";
        accommodationID = getInt(1,std::numeric_limits<int>::max());
        Accommodations* accommodation = nullptr;
        for (Parcs* parc : company->getParcs()) {
            accommodation = findItemByID(parc->getAccommodations(), accommodationID);
            if (accommodation) break;
        }
        if (accommodation) {
            accommodations.push_back(accommodation);
        } else {
            std::cout << "Accommodation with ID " << std::to_string(accommodationID) << " not found.\n";
        }
    }

    // Ask for other details
    std::cout << "Enter activityPass ";
    activityPass = getBool();
    std::cout << "Enter sportsPass ";
    sportsPass = getBool();
    std::cout << "Enter bicycleRent ";
    bicycleRent = getBool();
    std::cout << "Enter swimmingPass ";
    swimmingPass = getBool();

    // Assuming Datum has a constructor that takes a string in the format "YYYY-MM-DD"
    std::cout << "Enter begin date (YYYY-MM-DD): ";
    std::string beginDateString;
    std::getline(std::cin, beginDateString);

// Split the string into day, month, and year
     jaar = std::stoi(beginDateString.substr(0, 4));
     maand = std::stoi(beginDateString.substr(5, 2));
     dag = std::stoi(beginDateString.substr(8, 2));

// Use the split values to construct the Datum object
    beginDate = new Datum(dag, maand, jaar);


    std::cout << "Enter end date (YYYY-MM-DD): ";
    std::string endDateString;
    std::getline(std::cin, endDateString);

// Split the string into day, month, and year
     jaar = std::stoi(endDateString.substr(0, 4));
     maand = std::stoi(endDateString.substr(5, 2));
     dag = std::stoi(endDateString.substr(8, 2));

// Use the split values to construct the Datum object
    endDate = new Datum(dag, maand, jaar);
    std::cout << "Enter booking status: ";
    std::getline(std::cin, status);

    // Create the Booking object and return its pointer
    return new Booking(ID, customer, accommodations, activityPass, sportsPass, bicycleRent, swimmingPass, beginDate, endDate, status);
}
//TODO see vorige todo-s before pushing new main.cpp
void displayMainMenu() {
    int choice;
    do {
        std::cout << "Welcome to VacationParcs!\n";
        std::cout << "1. Login as Owner\n";
        std::cout << "2. Login as Customer\n";
        std::cout << "3. Login as Employee\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        choice=getInt(1,4);

        switch (choice) {
            case 1:
                displayOwnerMenu();
                break;
            case 2:
                displayCustomerMenu();
                break;
            case 3:
                displayEmployeeMenu();
                break;
            case 4:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}

void displayOwnerMenu() {
    int choice;
    do {
        std::cout << "\nOwner Menu:\n";
        std::cout << "1. Create Parc\n";
        std::cout << "2. Delete Parc\n";
        std::cout << "3. Manage Parc (Accommodations & Services)\n";
        std::cout << "4. Display Entire VacationParc\n";
        std::cout << "5. Logout\n";
        std::cout << "Enter your choice: ";
        choice=getInt(1,5);

        switch (choice) {
            case 1:
                // Handle create parc
            {
                Parcs* newParc=cliNewPark();
                company->addPark(newParc);
            }
                break;
            case 2:
                // Handle delete parc
            {
                int parcID;
                std::cout << "Enter the ID of the parc to delete: ";
                parcID=getInt(1,std::numeric_limits<int>::max());
                company->removePark(parcID);
            }
                break;
            case 3:
                // Manage a specific parc
            {
                int parcID;
                std::cout << "Enter the ID of the parc to manage: ";
                parcID=getInt(1,std::numeric_limits<int>::max());
                Parcs* selectedParc = company->findParcByID(parcID);
                if (selectedParc) {
                    manageParc(selectedParc);
                } else {
                    std::cout << "Parc " << std::to_string(parcID) << " not found.\n";
                }
            }
                break;
            case 4:
                std::cout << *company << "\n";
                break;
            case 5:
                std::cout << "Logging out...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

void manageParc(Parcs* selectedParc) {
    int choice;
    do {
        std::cout << "\nManage Parc Menu:\n";
        std::cout << "1. Create Accommodation\n";
        std::cout << "2. Delete Accommodation\n";
        std::cout << "3. Change Parc Services\n";
        std::cout << "4. Change Accommodation\n";
        std::cout << "5. Return to Owner Menu\n";
        std::cout << "Enter your choice: ";
        choice=getInt(1,5);

        switch (choice) {
            case 1:
                // Handle create accommodation
            {
                Accommodations* newAccommodation;
                newAccommodation = cliNewAccommo();
                selectedParc->addAccommodation(newAccommodation);
            }
                break;
            case 2:
                // Handle delete accommodation
            {
                int accommodationID;
                std::cout << "Enter the ID of the accommodation to delete: ";
                accommodationID=getInt(1,std::numeric_limits<int>::max());
                selectedParc->removeAccommodation(accommodationID);
            }
                break;
            case 3:
                // Handle change parc services
            {
                Parcs::ParcServices* newServices;
                newServices = cliNewSrv();
                // Set the services for the selected parc
                selectedParc->setServices(newServices);
                // Optionally, if you don't need the newServices pointer anymore, you can delete it to free the memory
                // delete newServices;
            }
                break;
            case 4:
                // Handle change accommodation
            {
                int accommodationID;
                std::cout << "Enter the ID of the accommodation to change: ";
                accommodationID=getInt(1,std::numeric_limits<int>::max());
                Accommodations* updatedAccommodation;
                updatedAccommodation = cliNewAccommo();
                // Now, you can add the updatedAccommodation to the selected parc's accommodations list
                selectedParc->setAccommodation(accommodationID,updatedAccommodation);
            }
                break;
            case 5:
                std::cout << "Returning to Owner Menu...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}



void displayCustomerMenu() {
    Customer* huidigG;
    int choice;
    do {
        std::cout << "\nCustomer Menu:\n";
        std::cout << "1. Register\n";
        std::cout << "2. Change Customer Data\n";
        std::cout << "3. Search Accommodations\n";
        std::cout << "4. Create Booking\n";
        std::cout << "5. Change Booking\n";
        std::cout << "6. Logout\n";
        std::cout << "Enter your choice: ";
        choice=getInt(1,6);

        switch (choice) {
            case 1:
            {
                Customer* newCustomer = cliNewCust();
                company->registerCustomer(newCustomer);
                huidigG = company->getCustomers().back();
                break;
            }
            case 2: {
                int userID;
                std::cout << "Enter your user ID: ";
                userID = getInt(1,std::numeric_limits<int>::max());
                Customer* updatedCustomer = cliNewCust();
                OS::modifyCustomer(company, userID, updatedCustomer);
                break;
            }
            case 3: {
                int accommodationID;
                std::cout << "Enter the ID of the accommodation you're looking for: ";
                accommodationID = getInt(1,std::numeric_limits<int>::max());
                std::vector<Parcs*>& parcs = company->getParcs();
                for (Parcs* parc : parcs) {
                    std::vector<Accommodations*>& accommodations = parc->getAccommodations();
                    Accommodations* accommodation = findItemByID(accommodations, accommodationID);
                    if (accommodation) {
                        std::cout << "Accommodation found: " << *accommodation << std::endl;
                        // Display more details about the accommodation if needed
                    } else std::cout << "No Accommodation exists with ID " << accommodationID << std::endl;
                }
                break;
            }
            case 4: {
                int accommodationID;
                std::cout << "Enter the ID of the accommodation you want to book: ";
                accommodationID = getInt(1,std::numeric_limits<int>::max());
                Booking* newBooking = cliNewBkn();
                OS::bookAccommodation(company, huidigG->getID(), accommodationID, newBooking);
                break;
            }
            case 5: {
                int bookingID;
                std::cout << "Enter the ID of the booking you want to change: ";
                bookingID = getInt(1,std::numeric_limits<int>::max());
                Booking* updatedBooking = cliNewBkn();
                OS::modifyBooking(company, bookingID, updatedBooking);
                break;
            }
            case 6:
                std::cout << "Logging out...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}


void displayEmployeeMenu() {
    int choice;
    do {
        std::cout << "\n--- Employee Menu ---\n";
        std::cout << "1. Delete Customer\n";
        std::cout << "2. Change Accommodation\n";
        std::cout << "3. Delete Booking\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        choice = getInt(1,4);

        switch (choice) {
            case 1: {
                // Delete Customer
                int customerID;
                std::cout << "Enter Customer ID to delete: ";
                customerID = getInt(1,std::numeric_limits<int>::max());
                OS::deleteCustomer(company,customerID);
                break;
            }
            case 2: {
                // Change Accommodation
                int accommodationID;
                std::cout << "Enter Accommodation ID to modify: ";
                accommodationID = getInt(1,std::numeric_limits<int>::max());
                for (Parcs* parc : company->getParcs()) {
                    Accommodations* accommodation = findItemByID(parc->getAccommodations(), accommodationID);
                    if (accommodation) {
                        parc->setAccommodation(accommodationID, accommodation);
                        break;}
                }
                break;
            }
            case 3: {
                // Delete Booking
                int bookingID;
                std::cout << "Enter Booking ID to delete: ";
                bookingID = getInt(1,std::numeric_limits<int>::max());
                OS::deleteBooking(company,bookingID);
                break;
            }
            case 4:
                std::cout << "Exiting Employee Menu...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 4);
}


