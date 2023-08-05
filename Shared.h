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
const std::vector<std::string> PAYMENT_METHODS = {"Bancontact","Payconiq","Contant Geld"};

template <typename T>
    void addItem(std::vector<T>& vec, const T& item) {
        vec.push_back(item);
        std::cout << "A new " << typeid(T).name() << " has been added successfully.\n";
    }

template <typename T>
void removeItem(std::vector<T>& vec, int id) {
//    TODO bug still deletes even when ID does not exist
    try {
        vec.erase(std::remove_if(vec.begin(), vec.end(), [id](const T& item) {
            return item.getID() == id;
        }), vec.end());
        std::cout << "The " << typeid(T).name() << " with ID " << id << " has been removed successfully.\n";
    }
    catch (const std::exception &e) {
        std::cout << "No " << typeid(T).name() << " with ID " << id << " was found. Error: " << e.what() << std::endl;
    }
}
// Base case: single name-value pair.
template<typename T>
void printBooleans(const std::string& name, T value) {
    static_assert(std::is_same<T, bool>::value, "All arguments should be of type bool.");
    std::cout << name << ": " << (value ? "true" : "false") << '\n';
}

// Recursive case: multiple name-value pairs.
template<typename T, typename... Args>
void printBooleans(const std::string& name, T value, Args... args) {
    static_assert(std::is_same<T, bool>::value, "All arguments should be of type bool.");
    std::cout << name << ": " << (value ? "true" : "false") << '\n';
    printBooleans(args...);
}

// Again use of tempaltes to facilitate setting multiple booleans at once instead of calling separate methods
// that basically do the same
// Base case: single name-value pair.
template<typename T>
void setBooleans(T& object, void(T::*setter)(bool), bool value) {
    static_assert(std::is_same<decltype(setter), void(T::*)(bool)>::value, "All setter methods should take a single bool argument.");
    (object.*setter)(value);
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
T* findItemByID(std::vector<T>& vec, int id) {
    for (T& item : vec) {
        if (item.getID() == id) {
            return &item;  // Return a pointer to the found item
        }
    }
    return nullptr;  // Return nullptr if no item was found
}

#endif //FINALPARK_SHARED_H
