#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <iomanip>  

using namespace std;

class Item {
public:
    int productID;   
    string name;     
    int quantity;    
    double price;    
    string category; 

    Item(int id, string n, int q, double p, string c)
        : productID(id), name(n), quantity(q), price(p), category(c) {}

    void displayItem() const {
        cout << setw(6) << productID
             << setw(20) << left << name
             << setw(10) << quantity
             << setw(10) << fixed << setprecision(2) << price
             << setw(15) << left << category
             << endl;
    }
};

class Inventory {
private:
    vector<Item> items;  
    int nextProductID;   

public:
    Inventory() : nextProductID(1) {}

    void addItem(string name, int quantity, double price, string category) {
        Item newItem(nextProductID++, name, quantity, price, category);
        items.push_back(newItem);
        cout << "Item added successfully!" << endl;
    }

    void updateItem(int id, char choice, double newValue) {
        for (auto& item : items) {
            if (item.productID == id) {
                if (choice == 'q') {
                    item.quantity = static_cast<int>(newValue);
                    cout << "Quantity updated to " << item.quantity << endl;
                } else if (choice == 'p') {
                    item.price = newValue;
                    cout << "Price updated to " << item.price << endl;
                }
                return;
            }
        }
        cout << "Item not found!" << endl;
    }

    void removeItem(int id) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->productID == id) {
                cout << "Item " << it->name << " has been removed." << endl;
                items.erase(it);
                return;
            }
        }
        cout << "Item not found!" << endl;
    }

    void displayAllItems() {
        cout << setw(6) << "ID   "
             << setw(20) << left << "Name"
             << setw(10) << "Quantity"
             << setw(10) << "Price"
             << setw(15) << "Category" << endl;

        for (const auto& item : items) {
            item.displayItem();
        }
    }

    void searchItem(int id) {
        for (const auto& item : items) {
            if (item.productID == id) {
                item.displayItem();
                return;
            }
        }
        cout << "Item not found!" << endl;
    }

    void displayLowStockItems() {
        cout << setw(10) << "ID"
             << setw(20)  << "Name"
             << setw(10) << "Quantity"
             << setw(10) << "Price"
             << setw(15) << "Category" << endl;

        for (const auto& item : items) {
            if (item.quantity <= 5) {
                item.displayItem();
            }
        }
    }

    void sortItems() {
        sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.price < b.price;  
        });
        cout << "Items sorted by price!" << endl;
    }
};

int getValidIntegerInput() {
    int input;
    while (!(cin >> input)) {
        cin.clear();  
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cout << "Invalid input! Please enter a valid integer: ";
    }
    return input;
}

double getValidDoubleInput() {
    double input;
    while (!(cin >> input)) {
        cin.clear();  
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cout << "Invalid input! Please enter a valid number: ";
    }
    return input;
}

int main() {
    Inventory inventory;  
    int choice;
    string name, category;
    int quantity, productID;
    double price;
    char updateChoice;

    while (true) {
        cout << "==========================================\n";
        cout << " + MENU + \n";
        cout << "|1 - Add Item                 |\n";
        cout << "|2 - Update Item              |\n";
        cout << "|3 - Remove Item              |\n";
        cout << "|4 - Display All Items        |\n";
        cout << "|5 - Search Item              |\n";
        cout << "|6 - Display Low Stock Items  |\n";
        cout << "|7 - Sort Items by Price      |\n";  
        cout << "|8 - Exit                     |\n";  
        cout << "==========================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');  

        switch (choice) {
        case 1:
            cout << "Enter item name: ";
            getline(cin, name);
            cout << "Enter quantity: ";
            quantity = getValidIntegerInput();
            cout << "Enter price: ";
            price = getValidDoubleInput();
            cout << "Enter category: ";
            cin >> category; 
            inventory.addItem(name, quantity, price, category);
            break;

        case 2:
            cout << "Enter product ID to update: ";
            productID = getValidIntegerInput();
            cout << "Do you want to update quantity (q) or price (p)? ";
            cin >> updateChoice;
            cout << "Enter new value: ";
            price = getValidDoubleInput();
            inventory.updateItem(productID, updateChoice, price);
            break;

        case 3:
            cout << "Enter product ID to remove: ";
            productID = getValidIntegerInput();
            inventory.removeItem(productID);
            break;

        case 4:
            inventory.displayAllItems();
            break;

        case 5:
            cout << "Enter product ID to search: ";
            productID = getValidIntegerInput();
            inventory.searchItem(productID);
            break;

        case 6:
            inventory.displayLowStockItems();
            break;

        case 7:
            inventory.sortItems();
            break;

        case 8:
            cout << "Exiting..." << endl;
            return 0;

        default:
            cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}
