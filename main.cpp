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
#include <vector>

void displayMainMenu();
void displayOwnerMenu();
void displayCustomerMenu();
void displayEmployeeMenu();

void manageParc(Parcs *selectedParc);

VacationParcs* company = nullptr;

int main() {
    std::cout << "Welcome to VacationParcs Management System!" << std::endl;
    std::cout << "Is this your first time using the app or would you like to load from a file? (1 for First Time, 2 for Load from File): ";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        std::string name, address, VAT, parcName, parcAddress, customerName, customerAddress, mail, password, location, paymentMethod,accommodationKind;
        bool subtropicSwimmingPool, sportsInfrastructure, bowlingAlley, bicycleRent, childrensParadise, waterBikes,bathroomWithBath,
        BBQ, surroundSystem, breakfastService, cleaningService;
        int nrPeople, size;
        std::vector<Accommodations*> accommodations;
        Parcs::ParcServices* services;
        LuxuryLevel* luxury;
        // Gather data for VacationParcs
        std::cout << "Enter details for the VacationParcs company:\n";
        std::cout << "Name: ";
        std::cin >> name;
        std::cout << "Address: ";
        std::cin >> address;
        std::cout << "VAT: ";
        std::cin >> VAT;

        // Gather data for Parcs
        std::cout << "Enter details for a Parc:\n";
        std::cout << "Name: ";
        std::cin >> parcName;
        std::cout << "Address: ";
        std::cin >> parcAddress;


        std::cout << "Enter details for Parc Services:\n";
        std::cout << "Subtropic Swimming Pool (1 for Yes, 0 for No): ";
        std::cin >> subtropicSwimmingPool;
        std::cout << "Sports Infrastructure (1 for Yes, 0 for No): ";
        std::cin >> sportsInfrastructure;
        std::cout << "Bowling Alley (1 for Yes, 0 for No): ";
        std::cin >> bowlingAlley;
        std::cout << "Bicycle Rent (1 for Yes, 0 for No): ";
        std::cin >> bicycleRent;
        std::cout << "Children's Paradise (1 for Yes, 0 for No): ";
        std::cin >> childrensParadise;
        std::cout << "Water Bikes (1 for Yes, 0 for No): ";
        std::cin >> waterBikes;

        services = new Parcs::ParcServices(subtropicSwimmingPool, sportsInfrastructure, bowlingAlley, bicycleRent, childrensParadise, waterBikes);
        int accommodationChoice;
        std::cout << "Choose type of Accommodation (1 for HotelRoom, 2 for Cabin): ";
        std::cin >> accommodationChoice;

        if (accommodationChoice == 1) {
            int floor, nrBeds;
            bool childrenBed;

            std::cout << "Enter details for HotelRoom:\n";
            std::cout << "Number of People: ";
            std::cin >> nrPeople;
            std::cout << "Size: ";
            std::cin >> size;
            std::cout << "Bathroom with Bath (1 for Yes, 0 for No): ";
            std::cin >> bathroomWithBath;
            std::cout << "Children Bed (1 for Yes, 0 for No): ";
            std::cin >> childrenBed;
            std::cout << "Floor: ";
            std::cin >> floor;
            std::cout << "Location: ";
            std::cin >> location;
            std::cout << "Number of Beds: ";
            std::cin >> nrBeds;

            // Gather data for LuxuryLevel
            std::cout << "Enter details for Luxury Level:\n";
            std::cout << "BBQ (1 for Yes, 0 for No): ";
            std::cin >> BBQ;
            std::cout << "Surround System (1 for Yes, 0 for No): ";
            std::cin >> surroundSystem;
            std::cout << "Breakfast Service (1 for Yes, 0 for No): ";
            std::cin >> breakfastService;
            std::cout << "Cleaning Service (1 for Yes, 0 for No): ";
            std::cin >> cleaningService;
            std::cout << "Accommodation Kind: ";
            std::cin >> accommodationKind;

            luxury = new LuxuryLevel(BBQ, surroundSystem, breakfastService, cleaningService, accommodationKind);
            HotelRoom* hotelRoom = new HotelRoom(nrPeople, size, bathroomWithBath, luxury, childrenBed, floor, location, nrBeds);
            accommodations.push_back(hotelRoom);

        } else if (accommodationChoice == 2) {
            int bedrooms;

            std::cout << "Enter details for Cabin:\n";
            std::cout << "Number of People: ";
            std::cin >> nrPeople;
            std::cout << "Size: ";
            std::cin >> size;
            std::cout << "Bathroom with Bath (1 for Yes, 0 for No): ";
            std::cin >> bathroomWithBath;
            std::cout << "Number of Bedrooms: ";
            std::cin >> bedrooms;

            // Gather data for LuxuryLevel
            std::cout << "Enter details for Luxury Level:\n";
            std::cout << "BBQ (1 for Yes, 0 for No): ";
            std::cin >> BBQ;
            std::cout << "Surround System (1 for Yes, 0 for No): ";
            std::cin >> surroundSystem;
            std::cout << "Breakfast Service (1 for Yes, 0 for No): ";
            std::cin >> breakfastService;
            std::cout << "Cleaning Service (1 for Yes, 0 for No): ";
            std::cin >> cleaningService;
            std::cout << "Accommodation Kind: ";
            std::cin >> accommodationKind;

            luxury = new LuxuryLevel(BBQ, surroundSystem, breakfastService, cleaningService, accommodationKind);
            Cabin* cabin = new Cabin(nrPeople, size, bathroomWithBath, luxury, bedrooms);
            accommodations.push_back(cabin);

        } else {
            std::cout << "Invalid choice for accommodation type.\n";
        }

        Parcs* newParc = new Parcs(parcName, parcAddress, services, accommodations);

        // Gather data for Customer
        std::cout << "Enter details for a Customer:\n";
        std::cout << "Name: ";
        std::cin >> customerName;
        std::cout << "Address: ";
        std::cin >> customerAddress;
        std::cout << "Mail: ";
        std::cin >> mail;
        std::cout << "Password: ";
        std::cin >> password;
        std::cout << "Location: ";
        std::cin >> location;
        std::cout << "Payment Method: ";
        std::cin >> paymentMethod;

        Customer* newCustomer = new Customer(customerName, customerAddress, mail, password, location, paymentMethod);

        // Create the VacationParcs company with the gathered data
        company = new VacationParcs(name, address, VAT, {newParc}, {newCustomer});
    } else if (choice == 2) {
//        TODO
        // Load data from file
        // Placeholder, you should implement the logic to read data from a file and create the company object
        // company = loadFromFile();
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
        std::cin >> choice;

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
        std::cin >> choice;

        switch (choice) {
            case 1:
                // Handle create parc
            {
                Parcs* newParc; // You'd gather details for the new parc from the user
                // For simplicity, I'm skipping that part here
                company->addPark(newParc);
            }
                break;
            case 2:
                // Handle delete parc
            {
                int parcID;
                std::cout << "Enter the ID of the parc to delete: ";
                std::cin >> parcID;
                company->removePark(parcID);
            }
                break;
            case 3:
                // Manage a specific parc
            {
                int parcID;
                std::cout << "Enter the ID of the parc to manage: ";
                std::cin >> parcID;
                Parcs* selectedParc = company->findParcByID(parcID);
                if (selectedParc) {
                    manageParc(selectedParc);
                } else {
                    std::cout << "Parc not found.\n";
                }
            }
                break;
            case 4:
                std::cout << company << "\n";
                break;
            case 5:
                std::cout << "Logging out...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
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
        std::cin >> choice;

        switch (choice) {
            case 1:
                // Handle create accommodation
            {
                // Inside the case where you manage a specific parc:

                int nrPeople, size, bedrooms, floor, nrBeds;
                bool bathroomWithBath, childrenBed, BBQ, surroundSystem, breakfastService, cleaningService;
                std::string accommodationKind, location;

                std::cout << "Enter details for the accommodation:\n";

                std::cout << "Number of People: ";
                std::cin >> nrPeople;

                std::cout << "Size: ";
                std::cin >> size;

                std::cout << "Bathroom with Bath (1 for Yes, 0 for No): ";
                std::cin >> bathroomWithBath;

                // LuxuryLevel details
                std::cout << "BBQ (1 for Yes, 0 for No): ";
                std::cin >> BBQ;

                std::cout << "Surround System (1 for Yes, 0 for No): ";
                std::cin >> surroundSystem;

                std::cout << "Breakfast Service (1 for Yes, 0 for No): ";
                std::cin >> breakfastService;

                std::cout << "Cleaning Service (1 for Yes, 0 for No): ";
                std::cin >> cleaningService;

                std::cout << "Accommodation Kind (HotelRoom or Cabin): ";
                std::cin >> accommodationKind;

                LuxuryLevel* luxury = new LuxuryLevel(BBQ, surroundSystem, breakfastService, cleaningService, accommodationKind);

                Accommodations* newAccommodation = nullptr;

                if (accommodationKind == "HotelRoom") {
                    std::cout << "Children Bed (1 for Yes, 0 for No): ";
                    std::cin >> childrenBed;

                    std::cout << "Floor: ";
                    std::cin >> floor;

                    std::cout << "Location: ";
                    std::cin >> location;

                    std::cout << "Number of Beds: ";
                    std::cin >> nrBeds;

                    newAccommodation = new HotelRoom(nrPeople, size, bathroomWithBath, luxury, childrenBed, floor, location, nrBeds);
                } else if (accommodationKind == "Cabin") {
                    std::cout << "Number of Bedrooms: ";
                    std::cin >> bedrooms;

                    newAccommodation = new Cabin(nrPeople, size, bathroomWithBath, luxury, bedrooms);
                } else {
                    std::cout << "Invalid accommodation kind. Please enter either HotelRoom or Cabin.\n";
                    delete luxury; // Clean up the dynamically allocated memory
                    return;
                }

                // Now, you can add the newAccommodation to the selected parc's accommodations list
                selectedParc->addAccommodation(newAccommodation);

            }
                break;
            case 2:
                // Handle delete accommodation
            {
                int accommodationID;
                std::cout << "Enter the ID of the accommodation to delete: ";
                std::cin >> accommodationID;
                selectedParc->removeAccommodation(accommodationID);
            }
                break;
            case 3:
                // Handle change parc services
            {
                // Inside the case where you manage a specific parc:

                bool subtropicSwimmingPool, sportsInfrastructure, bowlingAlley, bicycleRent, childrensParadise, waterBikes;

                std::cout << "Enter details for the parc services:\n";

                std::cout << "Subtropic Swimming Pool (1 for Yes, 0 for No): ";
                std::cin >> subtropicSwimmingPool;

                std::cout << "Sports Infrastructure (1 for Yes, 0 for No): ";
                std::cin >> sportsInfrastructure;

                std::cout << "Bowling Alley (1 for Yes, 0 for No): ";
                std::cin >> bowlingAlley;

                std::cout << "Bicycle Rent (1 for Yes, 0 for No): ";
                std::cin >> bicycleRent;

                std::cout << "Children's Paradise (1 for Yes, 0 for No): ";
                std::cin >> childrensParadise;

                std::cout << "Water Bikes (1 for Yes, 0 for No): ";
                std::cin >> waterBikes;

                // Create a new Parcs::ParcServices pointer
                Parcs::ParcServices* newServices = new Parcs::ParcServices{
                        subtropicSwimmingPool, sportsInfrastructure, bowlingAlley, bicycleRent, childrensParadise, waterBikes
                };

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
                std::cin >> accommodationID;

                // Inside the case where you manage a specific parc:

                int nrPeople, size, bedrooms, floor, nrBeds;
                bool bathroomWithBath, childrenBed, BBQ, surroundSystem, breakfastService, cleaningService;
                std::string accommodationKind, location;

                std::cout << "Enter details for the updated accommodation:\n";

                std::cout << "Number of People: ";
                std::cin >> nrPeople;

                std::cout << "Size: ";
                std::cin >> size;

                std::cout << "Bathroom with Bath (1 for Yes, 0 for No): ";
                std::cin >> bathroomWithBath;

                // LuxuryLevel details
                std::cout << "BBQ (1 for Yes, 0 for No): ";
                std::cin >> BBQ;

                std::cout << "Surround System (1 for Yes, 0 for No): ";
                std::cin >> surroundSystem;

                std::cout << "Breakfast Service (1 for Yes, 0 for No): ";
                std::cin >> breakfastService;

                std::cout << "Cleaning Service (1 for Yes, 0 for No): ";
                std::cin >> cleaningService;

                std::cout << "Accommodation Kind (HotelRoom or Cabin): ";
                std::cin >> accommodationKind;

                LuxuryLevel* luxury = new LuxuryLevel(BBQ, surroundSystem, breakfastService, cleaningService, accommodationKind);

                Accommodations* updatedAccommodation = nullptr;

                if (accommodationKind == "HotelRoom") {
                    std::cout << "Children Bed (1 for Yes, 0 for No): ";
                    std::cin >> childrenBed;

                    std::cout << "Floor: ";
                    std::cin >> floor;

                    std::cout << "Location: ";
                    std::cin >> location;

                    std::cout << "Number of Beds: ";
                    std::cin >> nrBeds;

                    updatedAccommodation = new HotelRoom(nrPeople, size, bathroomWithBath, luxury, childrenBed, floor, location, nrBeds);
                } else if (accommodationKind == "Cabin") {
                    std::cout << "Number of Bedrooms: ";
                    std::cin >> bedrooms;

                    updatedAccommodation = new Cabin(nrPeople, size, bathroomWithBath, luxury, bedrooms);
                } else {
                    std::cout << "Invalid accommodation kind. Please enter either HotelRoom or Cabin.\n";
                    delete luxury; // Clean up the dynamically allocated memory
                    return;
                }

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
        std::cin >> choice;

        switch (choice) {
            case 1:
                // Handle registration
                break;
            case 2:
                // Handle change customer data
                break;
            case 3:
                // Handle search accommodations
                break;
            case 4:
                // Handle create booking
                break;
            case 5:
                // Handle change booking
                break;
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
        std::cout << "\nEmployee Menu:\n";
        std::cout << "1. Delete Customer\n";
        std::cout << "2. Change Accommodation\n";
        std::cout << "3. Delete Booking\n";
        std::cout << "4. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                // Handle delete customer
                break;
            case 2:
                // Handle change accommodation
                break;
            case 3:
                // Handle delete booking
                break;
            case 4:
                std::cout << "Logging out...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}

