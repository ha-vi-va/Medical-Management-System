#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>

// Structure to represent a Medicine
struct Medicine {
    std::string name;
    int quantity;
    double price;
};

void storeMedicinesToFile(const std::vector<Medicine>& inventory);
void loadMedicinesFromFile(std::vector<Medicine>& inventory);
void addMedicine(std::vector<Medicine>& inventory);
void displayInventory(const std::vector<Medicine>& inventory);
void searchMedicine(const std::vector<Medicine>& inventory);
void deleteMedicine(std::vector<Medicine>& inventory);
void modifyMedicine(std::vector<Medicine>& inventory);
void generateReceipt(const std::vector<Medicine>& order, int receiptNumber);
void storeSalesSummary(const std::string& filename, double totalSales, const std::vector<Medicine>& order, int receiptNumber);

// Function to add a new medicine to the inventory
void addMedicine(std::vector<Medicine>& inventory) {
    Medicine medicine;
    std::cout << "Enter the name of the medicine: ";
    std::cin >> medicine.name;
    std::cout << "Enter the quantity: ";
    std::cin >> medicine.quantity;
    std::cout << "Enter the price: ";
    std::cin >> medicine.price;

    inventory.push_back(medicine);

    std::cout << "Medicine added successfully!" << std::endl;

    // Store the medicines in a text file
    storeMedicinesToFile(inventory);
}

// Function to display the inventory
void displayInventory(const std::vector<Medicine>& inventory) {
    if (inventory.empty()) {
        std::cout << "Inventory is empty." << std::endl;
    } else {
        std::cout << "Inventory:" << std::endl;
        for (const auto& medicine : inventory) {
            std::cout << "Name: " << medicine.name << ", Quantity: " << medicine.quantity << ", Price: " << medicine.price << std::endl;
        }
    }
}

// Function to search for a medicine in the inventory
void searchMedicine(const std::vector<Medicine>& inventory) {
    std::string searchName;
    std::cout << "Enter the name of the medicine to search: ";
    std::cin >> searchName;

    auto it = std::find_if(inventory.begin(), inventory.end(), [&searchName](const Medicine& medicine) {
        return medicine.name == searchName;
    });

    if (it != inventory.end()) {
        std::cout << "Medicine found in the inventory:" << std::endl;
        std::cout << "Name: " << it->name << ", Quantity: " << it->quantity << ", Price: " << it->price << std::endl;
    } else {
        std::cout << "Medicine not found in the inventory." << std::endl;
    }
}

// Function to delete a medicine from the inventory
void deleteMedicine(std::vector<Medicine>& inventory) {
    std::string deleteName;
    std::cout << "Enter the name of the medicine to delete: ";
    std::cin >> deleteName;

    auto it = std::find_if(inventory.begin(), inventory.end(), [&deleteName](const Medicine& medicine) {
        return medicine.name == deleteName;
    });

    if (it != inventory.end()) {
        inventory.erase(it);
        std::cout << "Medicine deleted successfully!" << std::endl;

        // Store the medicines in a text file
        storeMedicinesToFile(inventory);
    } else {
        std::cout << "Medicine not found." << std::endl;
    }
}

// Function to modify the details of a medicine in the inventory
void modifyMedicine(std::vector<Medicine>& inventory) {
    std::string modifyName;
    std::cout << "Enter the name of the medicine to modify: ";
    std::cin >> modifyName;

    auto it = std::find_if(inventory.begin(), inventory.end(), [&modifyName](const Medicine& medicine) {
        return medicine.name == modifyName;
    });

    if (it != inventory.end()) {
        std::cout << "Enter the new quantity: ";
        std::cin >> it->quantity;
        std::cout << "Enter the new price: ";
        std::cin >> it->price;
        std::cout << "Medicine modified successfully!" << std::endl;

        // Store the medicines in a text file
        storeMedicinesToFile(inventory);
    } else {
        std::cout << "Medicine not found." << std::endl;
    }
}

void loadMedicinesFromFile(std::vector<Medicine>& inventory) {
    std::ifstream file("medicines.txt");
    if (file.is_open()) {
        inventory.clear(); // Clear the existing inventory

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            Medicine medicine;

            if (iss >> medicine.name >> medicine.quantity >> medicine.price) {
                inventory.push_back(medicine);
            }
        }

        file.close();
    } else {
        std::cout << "Error opening file." << std::endl;
    }
}
// Function to generate a receipt for an order
void generateReceipt(const std::vector<Medicine>& order, int receiptNumber) {
    std::string filename = "receipt" + std::to_string(receiptNumber) + ".txt";
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "---------------------------" << std::endl;
        file << "        Medical Store       " << std::endl;
        file << "---------------------------" << std::endl;
        file << std::left << std::setw(20) << "Name" << std::setw(10) << "Quantity" << std::setw(10) << "Price" << std::endl;
        file << "---------------------------" << std::endl;
        double total = 0.0;
        for (const auto& medicine : order) {
            file << std::left << std::setw(20) << medicine.name << std::setw(10) << medicine.quantity << std::setw(10) << medicine.price << std::endl;
            total += medicine.quantity * medicine.price;
        }
        file << "---------------------------" << std::endl;
        file << "Total: " << total << std::endl;
        file << "---------------------------" << std::endl;
        std::cout << "Receipt generated successfully. Saved as " << filename << std::endl;
    } else {
        std::cout << "Error: Unable to open file for writing." << std::endl;
    }
}

// Function to store the total sales summary of the day in a text file
void storeSalesSummary(const std::string& filename, double totalSales, const std::vector<Medicine>& order, int receiptNumber) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << "Receipt Number: " << receiptNumber << std::endl;
        file << "---------------------------" << std::endl;
        file << "Medicine Name    Price" << std::endl;
        file << "---------------------------" << std::endl;
        for (const auto& medicine : order) {
            file << std::left << std::setw(15) << medicine.name << " " << medicine.price << std::endl;
        }
        file << "---------------------------" << std::endl;
        file << "Total Sales: " << totalSales << std::endl;
        file << "---------------------------" << std::endl;
        std::cout << "Sales summary stored successfully. Saved as " << filename << std::endl;
    } else {
        std::cout << "Error: Unable to open file for writing." << std::endl;
    }
}

// Function to store the medicines in a text file
void storeMedicinesToFile(const std::vector<Medicine>& inventory) {
    std::ofstream file("medicines.txt");
    if (file.is_open()) {
        for (const auto& medicine : inventory) {
            file << medicine.name << " " << medicine.quantity << " " << medicine.price << std::endl;
        }
        std::cout << "Medicines stored successfully." << std::endl;
    } else {
        std::cout << "Error: Unable to open file for writing." << std::endl;
    }
}

int main() {
    std::vector<Medicine> inventory;
    int receiptNumber = 1;
    double totalSales = 0.0;
    std::string salesSummaryFile = "sales_summary.txt";

    // Load the medicines from the text file
    loadMedicinesFromFile(inventory);

    while (true) {
        std::cout << "---------------------------" << std::endl;
        std::cout << "    Medical Store System    " << std::endl;
        std::cout << "---------------------------" << std::endl;
        std::cout << "1. Add Medicine" << std::endl;
        std::cout << "2. Display Inventory" << std::endl;
        std::cout << "3. Search Medicine" << std::endl;
        std::cout << "4. Delete Medicine" << std::endl;
        std::cout << "5. Modify Medicine" << std::endl;
        std::cout << "6. Place Order" << std::endl;
        std::cout << "7. Exit" << std::endl;

        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            addMedicine(inventory);
            storeMedicinesToFile(inventory);
        } else if (choice == 2) {
            displayInventory(inventory);
        } else if (choice == 3) {
            searchMedicine(inventory);
        } else if (choice == 4) {
            deleteMedicine(inventory);
            storeMedicinesToFile(inventory);
        } else if (choice == 5) {
            modifyMedicine(inventory);
        } else if (choice == 6) {
            std::vector<Medicine> order;
            int orderChoice = 0;
            double orderTotal = 0.0;
            while (orderChoice != 2) {
                std::cout << "---------------------------" << std::endl;
                std::cout << "        Place Order        " << std::endl;
                std::cout << "---------------------------" << std::endl;
                std::cout << "1. Add Medicine to Order" << std::endl;
                std::cout << "2. Generate Receipt" << std::endl;
                std::cout << "Enter your choice: ";
                std::cin >> orderChoice;

                if (orderChoice == 1) {
                    std::string orderName;
                    std::cout << "Enter the name of the medicine to order: ";
                    std::cin >> orderName;

                    auto it = std::find_if(inventory.begin(), inventory.end(), [&orderName](const Medicine& medicine) {
                        return medicine.name == orderName;
                    });

                    if (it != inventory.end()) {
                        int orderQuantity;
                        std::cout << "Enter the quantity to order: ";
                        std::cin >> orderQuantity;

                        if (orderQuantity > 0 && orderQuantity <= it->quantity) {
                            Medicine orderedMedicine;
                            orderedMedicine.name = it->name;
                            orderedMedicine.quantity = orderQuantity;
                            orderedMedicine.price = it->price;
                            order.push_back(orderedMedicine);

                            it->quantity -= orderQuantity;
                            orderTotal += orderQuantity * it->price;

                            std::cout << "Medicine added to order." << std::endl;
                        } else {
                            std::cout << "Invalid quantity or insufficient stock." << std::endl;
                        }
                    } else {
                        std::cout << "Medicine not found in the inventory." << std::endl;
                    }
                } else if (orderChoice == 2) {
                    generateReceipt(order, receiptNumber);
                    storeSalesSummary(salesSummaryFile, orderTotal, order, receiptNumber);
                    totalSales += orderTotal;
                    receiptNumber++;
                } else {
                    std::cout << "Invalid choice. Please try again." << std::endl;
                }
            }
        } else if (choice == 7) {
            break;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
