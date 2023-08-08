//
// Created by Admin on 8/4/2023.
//

#ifndef FINALPARK_SHARED_H
#define FINALPARK_SHARED_H


#include <vector>
#include <cstdio>
#include <algorithm>
//    Own methods needed for the program to work
// Universal benefit of using template functions! No need for boilerplate repetition anymore.
const std::vector<std::string> LUXURIES = {"BBQ","Surround System","Breakfast Service","Cleaning Service"};
const std::vector<std::string> SERVICES = {"Subtropic Swimming Pool","Sports Infrastructure","Bowling Alley","Bicycle Rent", "Children's Paradise","Water Bikes"};
enum class ESERVICES:int{SUBTROPIC_SWIMMING_POOL=1,SPORTS_INFRASTRUCTURE=2,BOWLING_ALLEY=3,BICYCLE_RENT=4,CHILDRENS_PARADISE=5,WATER_BIKES=6};
const std::vector<std::string> PAYMENT_METHODS = {"Bancontact","Payconiq","Contant Geld"};
const std::vector<std::string> ACCO_KINDS = {"HotelRoom","Cabin"};
const int DAG_VSCH_MAAND[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


template <typename T>
    void addItem(std::vector<T*>& vec, T* item) {
        vec.push_back(item);
        std::cout << "\taddItem -> A new " << typeid(T).name() << " has been added successfully.\n";
    }

template <typename T>
void removeItem(std::vector<T*>& vec, int id) {
    bool deleted = false;

    // Use the erase-remove idiom to remove the item from the vector
    vec.erase(std::remove_if(vec.begin(), vec.end(),
                             [&deleted, id](T* e) {
                                 if (e->getID() == id) {
                                     deleted = true;
                                     delete e;  // If you're managing memory, you should delete the pointer
                                     return true;
                                 }
                                 return false;
                             }), vec.end());

    if (deleted) {
        std::cout << "\tremoveItem -> The item with ID " << id << " has been removed successfully.\n";
    } else if (id < 0) {
        std::cout << "\tremoveItem -> Invalid ID.\n";
    } else {
        std::cout << "\tremoveItem -> Sorry, your item (ID: " << id << " ) couldn't be deleted.\n";
    }
}

// Base case: single name-value pair.
template<typename T>
void printBooleans(const std::string& name, T value) {
    static_assert(std::is_same<T, bool>::value, "\tprintBooleans -> All arguments should be of type bool.");
    std::cout << name << ": " << (value ? "true" : "false") << '\n';
}

// Recursive case: multiple name-value pairs.
template<typename T, typename... Args>
void printBooleans(const std::string& name, T value, Args... args) {
    static_assert(std::is_same<T, bool>::value, "\tprintBooleans -> All arguments should be of type bool.");
    std::cout << name << ": " << (value ? "true" : "false") << '\n';
    printBooleans(args...);
}

// Again use of tempaltes to facilitate setting multiple booleans at once instead of calling separate methods
// that basically do the same
// Base case: single name-value pair.
template<typename T>
void setBooleans(T& object, void(T::*setter)(bool), bool value) {
    static_assert(std::is_same<decltype(setter), void(T::*)(bool)>::value, "\tsetBooleans-> All setter methods should take a single bool argument.");
    (object.*setter)(value);
    std::cout << "\tsetBooleans -> Boolean set.\n";
}

// Recursive case: multiple name-value pairs.
template <typename T, typename... Args>
void setBooleans(T& object, void(T::*setter)(bool), bool value, Args... args) {
    (object.*setter)(value);
    if constexpr (sizeof...(args) > 0) {
        setBooleans(object, args...);
    }
}

//More templates!
template <typename T>
T* findItemByID(std::vector<T*>& vec, int id) {
    for (T* item : vec) {
        if (item->getID() == id) {
            std::cout << "\tfindItemByID -> Item " << id << " found.\n";
            return item;  // Return the found item
        }
    }
    return nullptr;  // Return nullptr if no item was found
}
// DEPRECATED
// For non-pointers (Accommodation vectors are impossible in c++ unless with pointers. Therefore
// this function is meant for Customer to still work under the same mechanisms if you don't want to use pointers
//template <typename T>
//T* findItemByID(std::vector<T>& vec, int id) {
//    for (T* item : vec) {
//        if (item->getID() == id) {
//            return item;  // Return the found item
//        }
//    }
//    return nullptr;  // Return nullptr if no item was found
//}
#endif //FINALPARK_SHARED_H
