
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <Windows.h>

using namespace std;

class Inventory {



protected:
    struct Items {
        string full_product_name; //this will also be the description, since it will be full product name
        string supplier_name;
        string product_id;
        float price = 0;
        int product_quantity = 0;
        int reorder_point = 0;
        string category;
        string unit_of_measurement;
        bool reorder_status;
        string ro_status; // to show true or false
    };

    vector<string> id_list; // this will store all product id's so that no two products have the same id
    vector<string> p_list; // checks if product is repeated by storing products and checking each

    vector<Items> inv; // this will store struct objects of type Items to be used
    vector <Items> rol; // stands for reorder list

    // this will check if id only contains numbers and no spaces
    void id_valididty(bool& id_check, string id) {
        bool checker = true;
        for (int i = 0; i < id.size(); i++) {
            if (isalpha(id[i]) || isspace(id[i])) {
                cout << "Invalid character\n\n";
                checker = false;
                break;
            }
        }

        if (checker == false) {
            id_check = true;
        }
        else {
            id_check = false;
        }
    }

    // limit is for lower limit
    void validation_with_limit(bool& validation, int num, int limit) {
        if (cin.fail() || num < limit) {
            cout << "Invalid Input\n";
            system("pause");
            cin.clear();
            cin.ignore(256, '\n');
            system("cls");
        }
        else {
            validation = false;
        }
    }

    void validation(bool& validation) {
        if (cin.fail()) {
            cout << "Invalid Input\n";
            system("pause");
            cin.clear();
            cin.ignore(256, '\n');
            system("cls");
        }
        else {
            validation = false;
        }
    }

    // function to get user input for new inventory
    void new_inventory() {
        bool validate_size = true;
        int size_input;
        // getting the number of items
        do {
            cout << "Creating new inventory, How many items to make (minimum is 15): ";
            cin >> size_input;
            validation_with_limit(validate_size, size_input, 5);
        } while (validate_size == true);

        cin.clear();
        cin.ignore(256, '\n');

        // getting data from user input
        for (int i = 0; i < size_input; i++) {
            system("cls");
            bool id_check = true; // boolean value for checking id
            bool price_check = true;
            bool quantity_check = true;
            bool uom_check = true;
            bool product_check = true;

            inv.push_back(Items());

            // product description
            do {
                int counter = 0;
                cout << "Enter full product name (a.k.a. description):\n";
                getline(cin, inv[i].full_product_name);
                if (i == 0) {
                    product_check = false;
                    p_list.push_back(inv[i].full_product_name);
                }
                else {
                    for (int j = 0; j < p_list.size(); j++) {
                        if (inv[i].full_product_name == p_list[j]) {
                            counter++;
                        }
                    }
                    if (counter == 0) {
                        product_check = false;
                    }
                    else {
                        cout << "Product is already in Inventory\n\n";
                    }
                }
            } while (product_check == true);
            // product's supplier name
            cout << "Enter the name of the supplier:\n";
            getline(cin, inv[i].supplier_name);

            // category of the product
            cout << "Enter category:\n";
            getline(cin, inv[i].category);
            for (int j = 0; j < inv[i].category.length(); j++) {
                if (isalpha(inv[i].category[j])) {
                    inv[i].category[j] = toupper(inv[i].category[j]);
                }
            }

            // product id
            do {
                cout << "Enter the product id:\n";
                getline(cin, inv[i].product_id);

                if (inv[i].product_id.length() < 3) {
                    cout << "ID is too short\n\n";
                }

                else {
                    id_valididty(id_check, inv[i].product_id);
                    // checking if id is not the same with other products
                    if (id_check == false) {
                        inv[i].product_id.insert(0, "P");
                        if (i > 0) {
                            bool valid = true;
                            for (int j = 0; j < id_list.size(); j++) {
                                if (inv[i].product_id == id_list[j]) {
                                    valid = false;
                                    system("cls");
                                    cout << "This id is already taken\n\n";
                                    break;
                                }
                            }
                            if (valid == false) {
                                id_check = true;
                            }
                            else {
                                id_list.push_back(inv[i].product_id);

                            }
                        }
                        // first id to be stored
                        else {
                            id_list.push_back(inv[i].product_id);
                        }
                    }
                }

            } while (id_check == true);

            // product price
            do {
                cout << "Set the product price:\n";
                cin >> inv[i].price;
                validation(price_check);
            } while (price_check == true || inv[i].price <= 0.00);

            // reorder point
            if (inv[i].price < 200.00) {
                inv[i].reorder_point = 5;
            }
            else if ((inv[i].price >= 200.00) && (inv[i].price <= 500.00)) {
                inv[i].reorder_point = 10;
            }
            else {
                inv[i].reorder_point = 15;
            }

            // quantity
            do {
                cout << "Enter product quantity:\n";
                cin >> inv[i].product_quantity;
                validation_with_limit(quantity_check, inv[i].product_quantity, 0);
            } while (quantity_check == true);

            // reorder status
            if (inv[i].product_quantity <= inv[i].reorder_point) {
                inv[i].reorder_status = true;
            }
            else {
                inv[i].reorder_status = false;
            }
            if (inv[i].reorder_status == true) {
                inv[i].ro_status = "true";
            }
            else {
                inv[i].ro_status = "false";
            }

            // unit of measurement
            cin.clear();
            cin.ignore(256, '\n');
            string uom_input;
            do {

                int counter = 0;
                cout << "Set the product's unit of measurement (one word only):\n";
                getline(cin, uom_input);
                for (int j = 0; j < uom_input.length(); j++) {
                    if (isspace(uom_input[j])) {
                        counter++;
                    }
                }
                if (counter == 0) {
                    uom_check = false;
                }
                else {
                    uom_check = true;
                }
            } while (uom_check == true);
            inv[i].unit_of_measurement = uom_input;
        }
    }

    void read_inventory() {
        ifstream inv_read("Inventory.txt");

        if (inv_read.is_open()) {
            string line;
            getline(inv_read, line);
            int a = 0;

            if (!inv.empty()) {
                inv.clear();
            }

            if (!p_list.empty()) {
                p_list.clear();
            }

            if (!id_list.empty()) {
                id_list.clear();
            }

            while (!inv_read.eof()) {
                getline(inv_read, line);
                getline(inv_read, line);
                if (inv_read.eof()) {
                    break;
                }
                inv.push_back(Items());
                inv[a].category = line;
                getline(inv_read, line);
                inv[a].full_product_name = line;
                getline(inv_read, line);
                inv[a].supplier_name = line;
                getline(inv_read, line);
                inv_read >> inv[a].product_id >> inv[a].product_quantity >> inv[a].price >> inv[a].reorder_point >> inv[a].unit_of_measurement;
                inv_read >> inv[a].ro_status;
                if (inv[a].ro_status == "false") {
                    inv[a].reorder_status = false;
                }
                else {
                    inv[a].reorder_status = true;
                }
                getline(inv_read, line);
                id_list.push_back(inv[a].product_id);
                p_list.push_back(inv[a].full_product_name);
                a++;
            }
            inv_read.close();

        }
        else {
            cout << "Error reading from file\n\n";
        }

    }

    // writing to the inventory file
    void update_inventory() {
        ofstream write("Inventory.txt");
        if (write.is_open()) {
            // this also includes updating the list that stores the product and product id for checking
            // mostly after user exits does this functionality become necessary to keep track of them
            if (!p_list.empty()) {
                p_list.clear();
            }
            if (!id_list.empty()) {
                id_list.clear();
            }
            write << "\t\tInventory of Items" << endl << endl;
            for (int i = 0; i < inv.size(); i++) {

                string status;
                write << setprecision(2) << fixed;
                write << inv[i].category << endl;
                write << inv[i].full_product_name << endl;
                write << inv[i].supplier_name << endl;
                write << left << setw(30) << "Product ID" << setw(30) << "Qty" << setw(30) << "Price" << setw(30) << "ROP" << setw(30) << "UOM" << setw(30) << "Reorder Status" << endl;
                write << left << setw(30) << inv[i].product_id << setw(30) << inv[i].product_quantity << setw(30) << inv[i].price << setw(30) << inv[i].reorder_point << setw(30) << inv[i].unit_of_measurement;
                write << setw(30) << inv[i].ro_status << endl << endl;
                id_list.push_back(inv[i].product_id);
                p_list.push_back(inv[i].full_product_name);
            }

            write.close();
        }
        else {
            cout << "Error making new inventory file\n\n";
        }
    }



public:
    void inventory_check() {
        ifstream file_check("Inventory.txt");
        // will check if there is an existing inventory file 
        if (file_check.is_open()) {
            file_check.close();
            read_inventory();
        }
        // will ask for user input for new file
        else {
            new_inventory();
            update_inventory();
        }
    };

    Inventory() {
        cout << "\t\tWelcome\n\n";
        cout << "Starting up...\n";
        Sleep(3000);

        inventory_check();
    }
    ~Inventory() {
        system("cls");
        cout << "\t\tThank you\n\n";
    }
    // show inventory from file
    void view_inventory() {
        update_inventory();
        ifstream viewprint("Inventory.txt");
        if (viewprint.is_open()) {
            string line;
            while (!viewprint.eof()) {
                getline(viewprint, line);
                cout << line << endl;
            }
        }
        else {
            cout << "Error reading from file" << endl;
        }
    }

    // adds an item to the inventory
    void add_item() {

        system("cls");
        bool id_check = true; // boolean value for checking id
        bool price_check = true;
        bool quantity_check = true;
        bool uom_check = true;
        bool product_check = true;

        int temp = inv.size();

        inv.push_back(Items());
        cin.clear();
        cin.ignore(256, '\n');
        // product description
        do {
            int counter = 0;
            cout << "Enter full product name (a.k.a. description):\n";
            getline(cin, inv[temp].full_product_name);


            for (int j = 0; j < p_list.size(); j++) {
                if (inv[temp].full_product_name == p_list[j]) {
                    counter++;
                }
            }
            if (counter == 0) {
                product_check = false;
            }
            else {
                cout << "Product is already in Inventory\n\n";
            }

        } while (product_check == true);
        // product's supplier name
        cout << "Enter the name of the supplier:\n";
        getline(cin, inv[temp].supplier_name);

        // category of the product
        cout << "Enter category:\n";
        getline(cin, inv[temp].category);
        for (int j = 0; j < inv[temp].category.length(); j++) {
            if (isalpha(inv[temp].category[j])) {
                inv[temp].category[j] = toupper(inv[temp].category[j]);
            }
        }

        // product id
        do {
            cout << "Enter the product id (minimum of 3characters long, numerical digits only):\n";
            getline(cin, inv[temp].product_id);

            if (inv[temp].product_id.length() < 3) {
                cout << "ID is too short\n\n";
            }

            else {
                id_valididty(id_check, inv[temp].product_id);
                // checking if id is not the same with other products
                if (id_check == false) {
                    inv[temp].product_id.insert(0, "P");

                    bool valid = true;
                    for (int j = 0; j < id_list.size(); j++) {
                        if (inv[temp].product_id == id_list[j]) {
                            valid = false;
                            system("cls");
                            cout << "This id is already taken\n\n";
                            break;
                        }
                    }
                    if (valid == false) {
                        id_check = true;
                    }
                    else {
                        id_list.push_back(inv[temp].product_id);
                    }

                }
            }

        } while (id_check == true);

        // product price
        do {
            cout << "Set the product price:\n";
            cin >> inv[temp].price;
            validation(price_check);
        } while (price_check == true || inv[temp].price <= 0.00);

        // reorder point
        if (inv[temp].price < 200.00) {
            inv[temp].reorder_point = 5;
        }
        else if ((inv[temp].price >= 200.00) && (inv[temp].price <= 500.00)) {
            inv[temp].reorder_point = 10;
        }
        else {
            inv[temp].reorder_point = 15;
        }

        // quantity
        do {
            cout << "Enter product quantity:\n";
            cin >> inv[temp].product_quantity;
            validation_with_limit(quantity_check, inv[temp].product_quantity, 0);
        } while (quantity_check == true);

        // reorder status
        if (inv[temp].product_quantity <= inv[temp].reorder_point) {
            inv[temp].reorder_status = true;
        }
        else {
            inv[temp].reorder_status = false;
        }

        if (inv[temp].reorder_status == true) {
            inv[temp].ro_status = "true";
        }
        else {
            inv[temp].ro_status = "false";
        }

        // unit of measurement
        cin.clear();
        cin.ignore(256, '\n');
        string uom_input;
        do {

            int counter = 0;
            cout << "Set the product's unit of measurement (one word only):\n";
            getline(cin, uom_input);
            for (int j = 0; j < uom_input.length(); j++) {
                if (isspace(uom_input[j])) {
                    counter++;
                }
            }
            if (counter == 0) {
                uom_check = false;
            }
            else {
                uom_check = true;
            }
        } while (uom_check == true);
        inv[temp].unit_of_measurement = uom_input;

        update_inventory();

    }

    // show items to be reordered
    void show_reorder() {
        // getting items to be reordered
        int a = 0;
        if (!rol.empty()) {
            rol.clear();
        }
        for (int i = 0; i < inv.size(); i++) {
            if (inv[i].reorder_status == true) {
                rol.push_back(Items());
                rol[a].full_product_name = inv[i].full_product_name;
                rol[a].supplier_name = inv[i].supplier_name;
                rol[a].category = inv[i].category;
                rol[a].product_id = inv[i].product_id;
                rol[a].price = inv[i].price;
                rol[a].product_quantity = inv[i].product_quantity;
                rol[a].reorder_point = inv[i].reorder_point;
                rol[a].reorder_status = inv[i].reorder_status;
                rol[a].ro_status = inv[i].ro_status;
                rol[a].unit_of_measurement = inv[i].unit_of_measurement;
                a++;
            }
        }

        if (rol.empty()) {
            cout << "Currently there are no items for Reorder\n\n";
        }
        else {
            // updating reorder list file
            ofstream write_ro("Reorder.txt");
            write_ro << "\t\tReorder List" << endl << endl;
            for (int i = 0; i < rol.size(); i++) {
                write_ro << setprecision(2) << fixed;
                write_ro << rol[i].category << endl;
                write_ro << rol[i].full_product_name << endl;
                write_ro << rol[i].supplier_name << endl;
                write_ro << left << setw(30) << "Product ID" << setw(30) << "Qty" << setw(30) << "Price" << setw(30) << "ROP" << setw(30) << "UOM" << setw(30) << "Reorder Status" << endl;
                write_ro << left << setw(30) << rol[i].product_id << setw(30) << rol[i].product_quantity << setw(30) << rol[i].price << setw(30) << rol[i].reorder_point << setw(30) << rol[i].unit_of_measurement;
                write_ro << setw(30) << rol[i].ro_status << endl << endl;
            }
            write_ro.close();

            // printing Reorder file content
            ifstream read_ro("Reorder.txt");
            if (read_ro.is_open()) {
                string line;
                while (!read_ro.eof()) {
                    getline(read_ro, line);
                    cout << line << endl;
                }
            }
            else {
                cout << "Error opening file\n\n";
            }
        }
    }

    // selection for try again
    void try_again(bool& repeat) {
        bool ans_check = true;
        do {
            char select;
            cout << "Try again[Y/N]\n\n";
            cin >> select;
            select = toupper(select);
            switch (select) {
            case 'Y': {
                ans_check = false;
                break;
            }
            case 'N': {
                ans_check = false;
                repeat = false;
                break;
            }
            default: {
                cout << "Invalid Input\n\n";
                break;
            }
            }
        } while (ans_check == true);
        system("cls");
    }

};

class Transactions : public Inventory {
    // still in progress
};

int main()
{
    Transactions t;
    bool repeat = true;
    bool repeat_check = true;
    char choice;
    char choice2;
    // start of program, selection
    do {
        cout << "Welcome there please choose what you would like to do:\n\n";
        cout << "1. Manage inventory\n";
        cout << "2. Manage Transactions\n";
        cout << "3. Exit\n\n";
        cin >> choice;
        switch (choice) {
        case '1': {
            // managing inventory
            system("cls");
            cout << "[1] View Inventory\n";
            cout << "[2] Add Item to inventory\n";
            cout << "[3] Check Reorder List\n\n";
            cin >> choice2;

            switch (choice2) {
            case '1': {
                t.view_inventory();
                break;
            }
            case '2': {
                t.add_item();
                break;
            }
            case '3': {
                t.show_reorder();
                break;
            }
            default: {
                cout << "Invalid Input\n\n";
                break;
            }
            }
            break;
        }
        case '2': {
            // managing transactions
            // under progress
            break;
        }
        case '3': {
            repeat_check = false;
            repeat = false;
            break;
        }
        default: {
            cout << "Invalid Input\n\n";
            break;
        }
        }
        if (repeat_check == true) {
            t.try_again(repeat);
        }
    } while (repeat == true);

}


