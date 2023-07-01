#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <conio.h>


using namespace std;

void start();
void menu();
void login();
void Register();
void three_Admin();
void account();
void order();
void addOrder(int productId, int quantity);
void Dashboard();
void ViewProd();
void ViewOrder();
void stock();
void initializeUsers();
void logout();
void Product();
void searchProduct();
void AddProduct();
void displayProd();
void updateProduct(int selectedId);
void selectProduct();
void deleteProduct(int selectedId);
void displayAccounts();
void selectAccount();
void updateAccount(int accountId);
void deleteAccount(int accountId);

vector<string> categories; // Declare the vector globally

struct User {
    string username;
    string password;
    string email;
};

struct Product {
    int id;
    string name;
    string category;
    string description;
    string status;
    double price;
    int quantity;
};



const int MAX_USERS = 100; 
User users[MAX_USERS]; 
int numUsers = 0;


void initializeUsers() {
    ifstream inputFile("C:\\Users\\vladi\\8_days\\users.txt");
    if (inputFile.is_open()) {
        string username, password;
        while (inputFile >> username >> password) {
            User user;
            user.username = username;
            user.password = password;
            users[numUsers++] = user;
        }
        inputFile.close();
    }
}

// Function to convert string to int
int stringToInt(const string& str) {
    istringstream iss(str);
    int value;
    iss >> value;
    return value;
}

// Function to convert string to double
double stringToDouble(const string& str) {
    istringstream iss(str);
    double value;
    iss >> value;
    return value;
}

string formatPrice(double price) {
    ostringstream ss;
    ss << "$" << fixed << setprecision(2) << price;

    string priceString = ss.str();
    string::size_type decimalPos = priceString.find('.');

    int startPos = (priceString[0] == '$') ? 1 : 0;
    int commaPos = decimalPos - 3;

    while (commaPos > startPos) {
        priceString.insert(commaPos, ",");
        commaPos -= 3;
    }

    return priceString;
}

std::string joinStrings(const std::vector<std::string>& strings, const std::string& delimiter) {
    std::string result;
    for (std::vector<std::string>::size_type i = 0; i < strings.size(); i++) {
        result += strings[i];
        if (i < strings.size() - 1) {
            result += delimiter;
        }
    }
    return result;
}


void logout(){
	system("cls");
	cout << " System Logout Processing......\n";
	start();
}


void searchProduct() {
    system("cls");

    ifstream inputFile("C:\\Users\\vladi\\8_days\\Prod.txt");

    if (!inputFile.is_open()) {
        cout << "Failed to open file for reading." << endl;
        return;
    }

    cout << "Search Product" << endl;

    string searchCriteria;
    cout << "Enter search criteria (name/id): ";
    cin >> searchCriteria;

    string searchValue;
    cout << "Enter search value: ";
    cin.ignore(); // Ignore newline character from previous input
    getline(cin, searchValue);

    bool found = false;
    string line;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string token;

        getline(ss, token, ',');
        int id;
        istringstream(token) >> id;

        getline(ss, token, ',');
        string name = token;

        getline(ss, token, ',');
        string category = token;

        getline(ss, token, ',');
        string description = token;

        getline(ss, token, ',');
        string status = token;

        getline(ss, token, ',');
        double price;
        istringstream(token) >> price;

        getline(ss, token, ',');
        int quantity;
        istringstream(token) >> quantity;

        if ((searchCriteria == "id" && to_string(id) == searchValue) ||
            (searchCriteria == "name" && name.find(searchValue) != string::npos)) {
            cout << "Product Found:" << endl;
            cout << "ID: " << id << endl;
            cout << "Name: " << name << endl;
            cout << "Category: "<< category << endl;
            cout << "Description: " << description << endl;
            cout << "Status: " << status << endl;
            cout << "Price: $" << fixed << setprecision(2) << price << endl;
            cout << "Quantity:" << quantity << endl;
            found = true;
            system("pause");
            Product();
        }
    }

    if (!found) {
        cout << "No product found matching the search criteria." << endl;
    }

    inputFile.close();
}



void login() {
    string username, password;

    system("cls");
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                        Joetech (Stock) Management System                                                      |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                   Login                                                                       |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\n" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t    Username: ";
    cin >> username;
    cout << "\t\t\t\t\t\t\t\t\t\t    Password: ";

    password = "";
    char ch;
    while ((ch = _getch()) != '\r') {  // Read characters until Enter is pressed
        if (ch == '\b') {  // Handle backspace
            if (!password.empty()) {
                password.erase(password.size() - 1);  // Remove the last character
                cout << "\b \b";  // Erase previous asterisk
            }
        } else {
            password.push_back(ch);
            cout << '*';  // Print asterisk instead of the actual character
        }
    }

    bool found = false;
    int userID;
    string email;
    ifstream inputFile("C:\\Users\\vladi\\8_days\\users.txt");
    if (inputFile.is_open()) {
        string fileUsername, filePassword, fileEmail;
        while (inputFile >> userID >> fileUsername >> filePassword >> fileEmail) {
            if (fileUsername == username && filePassword == password) {
                found = true;
                email = fileEmail;
                break;
            }
        }
        inputFile.close();
    } else {
        cout << "Failed to open file for reading." << endl;
        system("pause");
    }

    if (found) {
        cout << "\n\n\t\t\t\t\t\t\t\t\t\t    Login successful!" << endl;
        Sleep(3000);
        menu();
    } else {
        cout << "\n\n\t\t\t\t\t\t\t\t    Login failed. Invalid username or password." << endl;
        Sleep(3000);
        login();
    }
}


void Register() {
    using namespace std;
    string username, password, confirmPassword, email;
    system("cls");
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                        Joetech (Stock) Management System                                                      |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                  Register                                                                     |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\n" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t    Email: ";
    cin >> email;
    cout << "\t\t\t\t\t\t\t\t\t\t    Username: ";
    cin >> username;

    // Generate a unique ID for the user
    int userID = 0;

    ifstream inputFile("C:\\Users\\vladi\\8_days\\users.txt");
    if (inputFile.is_open()) {
        int fileUserID;
        string fileUsername, filePassword, fileEmail;
        while (inputFile >> fileUserID >> fileUsername >> filePassword >> fileEmail) {
            userID = fileUserID;  // Update the ID to the latest value
        }
        inputFile.close();
    } else {
        cout << "Failed to open file for reading." << endl;
        system("pause");
        login();
    }

    userID++;  // Increment the ID for the new user

    while (true) {
        cout << "\t\t\t\t\t\t\t\t\t\t    Password: ";
        password = "";
        char ch;
        while ((ch = _getch()) != '\r') {  // Read characters until Enter is pressed
            if (ch == '\b') {  // Handle backspace
                if (!password.empty()) {
                    password.erase(password.size() - 1);  // Remove the last character
                    cout << "\b \b";  // Erase previous character
                }
            } else {
                password.push_back(ch);
                cout << ch;  // Print the actual character
            }
        }
        cout << endl;

        cout << "\t\t\t\t\t\t\t\t\t\t    Confirm Password: ";
        confirmPassword = "";
        while ((ch = _getch()) != '\r') {  // Read characters until Enter is pressed
            if (ch == '\b') {  // Handle backspace
                if (!confirmPassword.empty()) {
                    confirmPassword.erase(confirmPassword.size() - 1);  // Remove the last character
                    cout << "\b \b";  // Erase previous character
                }
            } else {
                confirmPassword.push_back(ch);
                cout << ch;  // Print the actual character
            }
        }
        cout << endl;

        if (password == confirmPassword) {
            // Rest of your code for registration...
            // ...
            cout << "\t\t\t\t\t\t\t\t\t\t    Registration successful!" << endl;
            Sleep(2000);
            break;
        } else {
            cout << "\t\t\t\t\t\t\t\t\t\tPasswords do not match. Please try again." << endl;
            system("pause");
            password = "";
            confirmPassword = "";
            system("cls");
            cout << "\t\t\t      |===============================================================================================================================================|\n";
            cout << "\t\t\t      |                                                                                                                                               |\n";
            cout << "\t\t\t      |                                                        Joetech (Stock) Management System                                                      |\n";
            cout << "\t\t\t      |                                                                                                                                               |\n";
            cout << "\t\t\t      |===============================================================================================================================================|\n";
            cout << "\t\t\t      |                                                                  Register                                                                     |\n";
            cout << "\t\t\t      |===============================================================================================================================================|\n";
            cout << "\n" << endl;
            cout << "\t\t\t\t\t\t\t\t\t\t    Email: " << email << endl;
            cout << "\t\t\t\t\t\t\t\t\t\t    Username: " << username << endl;
        }
    }

    ofstream outputFile("C:\\Users\\vladi\\8_days\\users.txt", ios::app); // Open file in append mode
    if (outputFile.is_open()) {
        outputFile << userID << " " << username << " " << password << " " << email << endl;
        outputFile.close();
        cout << "Registration details saved." << endl;
        system("pause");
    } else {
        cout << "Failed to open file for writing." << endl;
        system("pause");
    }

    login();
}



void account(){
	string choice3;
    system("cls"); // clear screen
    cout << "\n";
    cout << "\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                         Joetech (Stock) Management System                                                     |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                 [D] Dashboard |  [P] Product | [O] Orders | [A] Account | [S] Search  | [L] Logout                            |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                      Account                                                                  |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                [1] Display Accounts                                                           |\n";
    cout << "\t\t\t      |                                                                [2] Edit Account                                                               |\n";
    cout << "\t\t\t      |                                                                [3] Remove Account                                                             |\n";
    cout << "\t\t\t      |                                                                [4] Back                                                                       |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t        [<=>] : ";
    cin >> choice3;
    
	if (choice3 == "1"){
        displayAccounts();
	} else if (choice3 == "2"){
		int accountId; // Declare the accountId variable
        cout << "Input ID to update: ";
        cin >> accountId;
        updateAccount(accountId);
	}else if (choice3 == "3"){
		int accountId;
        cout << "Input ID to delete: ";
        cin >> accountId;
        deleteAccount(accountId);
	}else if (choice3 == "D" || choice3 == "d") {
        Dashboard();
    } else if (choice3 == "A" || choice3 == "a") {
    	account();
	} else if (choice3 == "P" || choice3 == "p"){
        Product();
    } else if (choice3 == "S" || choice3 == "s"){
        searchProduct();
    }else if (choice3 == "O" || choice3 =="o") {
        order();
    } else {
        menu();
    } 

}

void menu() {
    system("cls");
    string choice;
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                      Joetech (Stock) Management System                                                        |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                 [D] Dashboard |  [P] Product | [O] Orders | [A] Account | [S] Search  | [L] Logout                            |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t        [<=>] : ";
    cin >> choice;

    if (choice == "D" || choice == "d") {
        Dashboard();
    }else if (choice == "A" || choice == "a") {
    	account();
	} else if (choice == "P" || choice == "p"){
        Product();
    } else if (choice == "S" || choice == "s") {
        searchProduct();
    }else if (choice == "O" || choice == "o"){
        order();
    }else {
        start();
    }
}

void Product(){
    system("cls"); // Clear the screen
    string products;
    int selectedId = 0;
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                        Joetech (Stock) Management System                                                      |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                 [D] Dashboard |  [P] Product | [O] Orders | [A] Account | [S] Search  | [L] Logout                            |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                   Product                                                                     |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                              [1] Add Products                                                                 |\n";
    cout << "\t\t\t      |                                                              [2] Display Products                                                             |\n"; 
    cout << "\t\t\t      |                                                              [3] Update products                                                              |\n";
    cout << "\t\t\t      |                                                              [4] Delete products                                                              |\n";
    cout << "\t\t\t      |                                                              [5] Display Specific Product                                                     |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t        [<=>] : ";
    cin >> products;

    if (products == "S" || products == "s") {
        searchProduct();
    }
    else if (products == "1"){
        AddProduct();
    }else if (products == "2"){
        displayProd();
    }else if (products =="3"){
    	if (selectedId != 0) {
            updateProduct(selectedId);
        }else {
            // Prompt for selecting a product by ID
            cout << "Enter the ID of the product you want to edit: ";
            cin >> selectedId;
            system("cls");
            updateProduct(selectedId);
        }
	}else if (products == "4"){
        // Prompt for selecting a product by ID
		int selectedId;
		cout << "Enter the ID of the product you want to delete: ";
		cin >> selectedId;
		system("cls");
		deleteProduct(selectedId);
	}else if (products == "5"){
		selectProduct();
	}else if(products == "D" || products == "d"){
    	Dashboard();
	}else if(products == "O" || products == "o"){
		order();
	}else if(products == "A" || products == "a"){
		account();
	}else if(products == "L" || products == "l"){
		logout();
	}else {
        Product();
    }
}
void AddProduct() {
    system("cls"); // Clear the screen
    string name, category, description, price, quantity, status;

    // Read the existing IDs from the file
    vector<int> existingIDs;
    ifstream inputFile("C:\\Users\\vladi\\8_days\\Prod.txt");
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string token;
            getline(ss, token, ',');
            int productID;
            istringstream(token) >> productID;
            existingIDs.push_back(productID);
        }
        inputFile.close();
    } else {
        cout << "Error opening the file!" << endl;
        return;
    }

    // Find the next available ID
    int id = 1;
    while (find(existingIDs.begin(), existingIDs.end(), id) != existingIDs.end()) {
        id++;
    }

    char choice;

    do {
        cout << "Add Product" << endl;
        cout << "Enter product name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input stream
        getline(cin, name);
        cout << "Enter product category: ";
        getline(cin, category);
        cout << "Enter product description: ";
        getline(cin, description);
        cout << "Enter product price: ";
        getline(cin, price);
        cout << "Enter product quantity: ";
        getline(cin, quantity);
        cout << "Enter product status: ";
        getline(cin, status);

        // Create the product line
        stringstream product;
        product << id << "," << name << "," << category << "," << description << "," << status << "," << price << "," << quantity;

        // Open the file for appending
        ofstream outputFile("C:\\Users\\vladi\\8_days\\Prod.txt", ios::app);
        if (outputFile.is_open()) {
            outputFile << product.str() << endl;
            outputFile.close();
            cout << "Product added successfully!" << endl;
            id++; // Increment the ID for the next product
        } else {
            cout << "Error opening the file!" << endl;
        }

        cout << "Do you want to add another product? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    Product();
}



void displayProd() {
    system("cls");
    ifstream inputFile("C:\\Users\\vladi\\8_days\\Prod.txt");
    cout << "\n\n\n";
    cout << " \n" << endl;
    cout << "\t\t     |=========================================================================================================================================================|\n";
    cout << "\t\t     |                                                                                                                                                         |\n";
    cout << "\t\t     |                                                                Joetech (Stock) Management System                                                        |\n";
    cout << "\t\t     |                                                                                                                                                         |\n";
    cout << "\t\t     |=========================================================================================================================================================|\n";
    cout << "\t\t     |                                                                                                                                                         |\n";
    cout << "\t\t     |                                                                       Products Records                                                                  |\n";
    cout << "\t\t     |                                                                                                                                                         |\n";
    cout << "\t\t     |=========================================================================================================================================================|\n";
    cout << " \n" << endl;
    cout << setw(30) <<"ID " << setw(25) << " NAME  " << setw(30) << " CATEGORY " << setw(30) << " Description " << setw(20) << " PRICE " << setw(20) << " Quantity " << setw(10) << "Status" << endl;

    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string token;

            getline(ss, token, ',');
            int id;
            istringstream(token) >> id;

            getline(ss, token, ',');
            string name = token.substr(0, 24);
            if (token.length() > 24)
                name += "...";

            getline(ss, token, ',');
            string category = token.substr(0, 19);
            if (token.length() > 19)
                category += "...";

            getline(ss, token, ',');
            string description = token.substr(0, 24);
            if (token.length() > 24)
                description += "...";

            getline(ss, token, ',');
            string status = token.substr(0, 14);
            if (token.length() > 14)
                status += "...";

            getline(ss, token, ',');
            double price;
            istringstream(token) >> price;

            getline(ss, token, ',');
            int quantity;
            istringstream(token) >> quantity;

        cout << setw(28) << id << setw(30) << name << setw(25) << category << setw(32) << description << setw(15) << "$" << fixed << setprecision(2) << price << setw(15) << quantity << setw(15) << status << endl;
        }
        string pick2;
        cout << " \n" << endl;
        cout << " \n" << endl;
        cout << "\t\t      |=========================================================================================================================================================|\n";
        cout << "\t\t      |                      [B] Back     [A] Add Product     [S] Select Product     [D] Delete Product     [U] Update Product     [O] Add Order                |\n";
        cout << "\t\t      |=========================================================================================================================================================|\n";
        cout << "\t\t\t\t\t[<=>] : ";
        cin >> pick2;

        if (pick2 == "B" || pick2 == "b") {
            Product();
        } else if (pick2 == "A" || pick2 == "a") {
            AddProduct();
        } else if (pick2 == "S" || pick2 == "s") {  
            selectProduct();
        } else if (pick2 == "D" || pick2 == "d") {
            int selectedId;
            cout << "Enter the ID of the product you want to delete: ";
            cin >> selectedId;
            system("cls");
            deleteProduct(selectedId);
        } else if (pick2 == "U" || pick2 == "u") {
            int selectedId;
            cout << "Enter the ID of the product you want to update: ";
            cin >> selectedId;
            system("cls");
            updateProduct(selectedId);
        } else if (pick2 == "O" || pick2 == "o") {
            int selectedId;
            cout << "Enter the ID of the product you want to order: ";
            cin >> selectedId;

            int orderQuantity;
            cout << "Enter the quantity for the order: ";
            cin >> orderQuantity;
            addOrder(selectedId, orderQuantity);
        }
        inputFile.close();
    } else {
        cout << "Failed to open file for reading." << endl;
    }
}


void updateProduct(int selectedId) {
    // Open the file for reading
    ifstream inputFile("C:\\Users\\vladi\\8_days\\Prod.txt");
    if (inputFile.is_open()) {
        string line;
        bool found = false;
        vector<string> products;

        // Read all the products from the file and store them in a vector
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string token;

            // Extract data from the line using comma as the delimiter
            getline(ss, token, ',');
            int id;
            istringstream(token) >> id;

            if (id == selectedId) {
                found = true;
                // Prompt for updated information
                string name, category, description, status, price, quantity;
                cout << "Enter updated product name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, name);
                cout << "Enter updated product category: ";
                getline(cin, category);
                cout << "Enter updated product description: ";
                getline(cin, description);

                cout << "Enter updated product status: ";
                getline(cin, status);

                cout << "Enter updated product price: ";
                getline(cin, price);
                cout << "Enter updated product quantity: ";
                getline(cin, quantity);

                // Create the updated product line
                stringstream updatedProduct;
                updatedProduct << id << "," << name << "," << category << "," << description << "," << status << "," << price << "," << quantity;
                products.push_back(updatedProduct.str());
            } else {
                products.push_back(line);
            }
        }

        inputFile.close();

        if (found) {
            // Open the file for writing (clears the file)
            ofstream outputFile("C:\\Users\\vladi\\8_days\\Prod.txt");
            if (outputFile.is_open()) {
                // Write all the products back to the file
                for (size_t i = 0; i < products.size(); ++i) {
                    outputFile << products[i] << endl;
                }
                outputFile.close();
                cout << "Product with ID " << selectedId << " updated successfully." << endl;
                displayProd();
            } else {
                cout << "Failed to open file for writing." << endl;
            }
        } else {
            cout << "Product with ID " << selectedId << " not found." << endl;
        }

    } else {
        cout << "Failed to open file for reading." << endl;
    }

    string pick5;
    cout << "Press any key to go back to the product list...";
    cin >> pick5;
    displayProd();
}

void selectProduct() {
    // Prompt for selecting a product by ID
    int selectedId;
    cout << "Enter the ID of the product you want to select: ";
    cin >> selectedId;
    system("cls");

    // Open the file for reading
    ifstream inputFile("C:\\Users\\vladi\\8_days\\Prod.txt");
    if (inputFile.is_open()) {
        string line;
        bool found = false;

        while (getline(inputFile, line)) {
            stringstream ss(line);
            string token;

            // Extract data from the line using comma as the delimiter
            getline(ss, token, ',');
            int id;
            istringstream(token) >> id;

            if (id == selectedId) {
                found = true;

                // Extract other product details
                getline(ss, token, ',');
                string name = token;

                getline(ss, token, ',');
                string category = token;

                getline(ss, token, ',');
                string description = token;

                getline(ss, token, ',');
                string status = token;

                getline(ss, token, ',');
                double price;
                istringstream(token) >> price;

                getline(ss, token, ',');
                int quantity;
                istringstream(token) >> quantity;

                // Display the product information
    cout << "\n\n\n";
    cout << " \n" << endl;
    cout << "\t\t     |==========================================================================================================================================================|\n";
    cout << "\t\t     |                                                                                                                                                          |\n";
    cout << "\t\t     |                                                                 Joetech (Stock) Management System                                                        |\n";
    cout << "\t\t     |                                                                                                                                                          |\n";
    cout << "\t\t     |==========================================================================================================================================================|\n";
    cout << "\t\t     |                                                                                                                                                          |\n";
    cout << "\t\t     |                                                                        Products Records                                                                  |\n";
    cout << "\t\t     |                                                                                                                                                          |\n";
    cout << "\t\t     |==========================================================================================================================================================|\n";
    cout << "\t\t     |                                                                                                                                                          |\n";
    cout << setw(22) <<"|"<<setw(9) <<"ID " << setw(25) << " NAME  " << setw(30) << " CATEGORY " << setw(30) << " Description " << setw(20) << " PRICE " << setw(20) << " Quantity " << setw(14) << "Status" << setw(7) <<" |" << endl;
	cout <<setw(23) <<"| " << setw(7) << id << setw(30) << name << setw(25) << category << setw(32) << description << setw(15) << "P" << fixed << setprecision(2) << price << setw(15) << quantity << setw(18) << status << setw(5) <<" |" <<endl;
    // Prompt for options (Update or Delete)
    string pick2;
    cout << "\t\t     |                                                                                                                                                          |\n";
    cout << "\t\t     |                                                                                                                                                          |\n";
    cout << "\t\t     |==========================================================================================================================================================|\n";
    cout << "\t\t     |                       [B] Back     [A] Add Product     [S] Select Product     [D] Delete Product     [U] Update Product     [O] Order                    |\n";
    cout << "\t\t     |==========================================================================================================================================================|\n";
    cout << "\t\t\t\t\t[<=>] : ";
                cin >> pick2;
                system("cls");
                if (pick2 == "U" || pick2 == "u") {
                    updateProduct(selectedId);
                }else if (pick2 == "D" || pick2 == "d") {
                    deleteProduct(selectedId);
                }else if (pick2 == "B" || pick2 == "b") {
                    displayProd();
                }else {
                    cout << "Invalid option. Please try again." << endl;
                    displayProd();
                }

                break; // No need to continue searching
            }
        }

        inputFile.close();

        if (!found) {
            cout << "Product with ID " << selectedId << " not found." << endl;
        }
    } else {
        cout << "Failed to open file for reading." << endl;
    }
}


void deleteProduct(int selectedId) {
    ifstream inputFile("C:\\Users\\vladi\\8_days\\Prod.txt");
    if (inputFile.is_open()) {
        string line;
        bool found = false;
        vector<string> products;

        while (getline(inputFile, line)) {
            stringstream ss(line);
            string token;

            // Extract data from the line using comma as the delimiter
            getline(ss, token, ',');
            int id;
            istringstream(token) >> id;

            if (id == selectedId) {
                found = true;
            } else {
                // Adjust the ID of the remaining products
                id = products.size() + 1;

                // Update the product line with the new ID
                stringstream updatedProduct;
                updatedProduct << id << line.substr(line.find(','));  // Retain the remaining data
                products.push_back(updatedProduct.str());
            }
        }

        inputFile.close();

        if (found) {
            ofstream outputFile("C:\\Users\\vladi\\8_days\\Prod.txt");
            if (outputFile.is_open()) {
                for (size_t i = 0; i < products.size(); ++i) {
                    outputFile << products[i] << endl;
                }
                outputFile.close();
                cout << "Product with ID " << selectedId << " deleted successfully." << endl;
                displayProd();
            } else {
                cout << "Failed to open file for writing." << endl;
            }
        } else {
            cout << "Product with ID " << selectedId << " not found." << endl;
        }
    } else {
        cout << "Failed to open file for reading." << endl;
    }

    string pick5;
    cout << "Press any key to go back to the product list...";
    cin >> pick5;
    displayProd();
}


// Function to display the orders
void order() {
    system("cls");

    // Read the order data from order.txt
    ifstream inputFile("C:\\Users\\vladi\\8_days\\order.txt");
    if (inputFile.is_open()) {
        string line;

        // Print the header
        cout << setw(10) << "OrderID" << setw(25) << "Product Name" << setw(15) << "Quantity" << setw(15) << "Price" << setw(15) << "Total" << endl;

        // Print the order details
        int orderID = 1;
        vector<string> orderRecords;
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string token;
            vector<string> orderData;
            while (getline(ss, token, ',')) {
                orderData.push_back(token);
            }

            cout << setw(10) << orderID << setw(25) << orderData[1] << setw(15) << orderData[2] << setw(15) << "$" << orderData[3] << setw(15) << "$" << orderData[4] << endl;

            orderRecords.push_back(line);
            orderID++;
        }
        inputFile.close();

        // Prompt user to manage an order
        cout << "\nEnter the Order ID to manage (0 to go back): ";
        cin >> orderID;

        if (orderID == 0) {
            Dashboard();
        } else if (orderID < 1 || orderID > orderRecords.size()) {
            cout << "Invalid Order ID.\n";
            system("pause");
            order();
        } else {
            // Prompt user to enter the new quantity
            int newQuantity;
            cout << "Enter the new quantity (0 to delete the record): ";
            cin >> newQuantity;

            // Validate the new quantity
            if (newQuantity == 0) {
                // Delete the record
                orderRecords.erase(orderRecords.begin() + orderID - 1);
                cout << "Order record deleted.\n";
            } else if (newQuantity < 0) {
                cout << "Invalid quantity.\n";
            } else {
                // Update the quantity and total price
                string& orderRecord = orderRecords[orderID - 1];
                stringstream ss(orderRecord);
                string token;

                // Split the order record by comma
                vector<string> orderData;
                while (getline(ss, token, ',')) {
                    orderData.push_back(token);
                }

                // Update the quantity and total price
                orderData[2] = to_string(newQuantity);
                double price = stod(orderData[3]);
                double totalPrice = price * newQuantity;
                orderData[4] = (totalPrice == static_cast<int>(totalPrice)) ? to_string(static_cast<int>(totalPrice)) : to_string(totalPrice);

                // Join the order data back into a string
                orderRecord = joinStrings(orderData, ",");

                cout << "Order record updated.\n";
            }

            // Write the updated order data back to order.txt
            ofstream outputFile("C:\\Users\\vladi\\8_days\\order.txt");
            if (outputFile.is_open()) {
                for (const string& record : orderRecords) {
                    outputFile << record << endl;
                }
                outputFile.close();
            } else {
                cout << "Failed to open file for writing.\n";
            }
        }
    } else {
        cout << "Failed to open file for reading.\n";
    }

    system("pause");
    order();
}


// Function to add an order
void addOrder(int productId, int quantity) {
    // Read the product data from Prod.txt
    ifstream inputFile("C:\\Users\\vladi\\8_days\\Prod.txt");
    if (inputFile.is_open()) {
        string line;
        bool productFound = false;
        stringstream updatedData;

        // Find the selected product in the file
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string token;

            getline(ss, token, ',');
            int id;
            istringstream(token) >> id;

            if (id == productId) {
                productFound = true;

                string name, category, description, status;
                double price;
                int availableQuantity;

                getline(ss, name, ',');
                getline(ss, category, ',');
                getline(ss, description, ',');
                getline(ss, status, ',');
                getline(ss, token, ',');
                istringstream(token) >> price;
                getline(ss, token, ',');
                istringstream(token) >> availableQuantity;

                if (availableQuantity > 0 && availableQuantity >= quantity) {
                    // Read the current highest order ID from order.txt
                    int orderId = 0;
                    ifstream orderFile("order.txt");
                    if (orderFile.is_open()) {
                        string orderLine;
                        while (getline(orderFile, orderLine)) {
                            stringstream orderSS(orderLine);
                            getline(orderSS, token, ',');
                            int orderID;
                            istringstream(token) >> orderID;
                            if (orderID > orderId) {
                                orderId = orderID;
                            }
                        }
                        orderFile.close();
                    }

                    // Calculate the total price of the order
                    double totalPrice = price * quantity;

                    // Save the order to the order.txt file
                    ofstream outputFile("C:\\Users\\vladi\\8_days\\Prod.txt", ios::app);
                    if (outputFile.is_open()) {
                        outputFile << ++orderId << "," << name << "," << quantity << "," << price << "," << totalPrice << endl;
                        outputFile.close();
                        cout << "Order placed successfully!\n";
                        system("pause");

                        // Subtract the ordered quantity from the available quantity
                        availableQuantity -= quantity;

                        // Update the product data in the updatedData stringstream
                        line = to_string(id) + "," + name + "," + category + "," + description + "," + status + "," + to_string(price) + "," + to_string(availableQuantity);
                    } else {
                        cout << "Failed to open file for writing.\n";
                    }
                } else {
                    if (availableQuantity == 0) {
                        cout << "Product is out of stock.\n";
                        system("pause");
                    } else {
                        cout << "Insufficient quantity available for this product.\n";
                        system("pause");
                    }
                }
            }

            // Store the existing product data in the updatedData stringstream
            updatedData << line << endl;
        }

        inputFile.close();

        if (!productFound) {
            cout << "Product not found.\n";
        } else {
            // Update the Prod.txt file with the updated product data
            ofstream outputFile("C:\\Users\\vladi\\8_days\\Prod.txt");
            if (outputFile.is_open()) {
                outputFile << updatedData.str();
                outputFile.close();
            } else {
                cout << "Failed to open file for writing.\n";
            }
        }
    } else {
        cout << "Failed to open file for reading.\n";
    }

    // Display the products again
    displayProd();
}

void deleteAccount(int accountId) {
    // Read all accounts from the file
    ifstream inputFile("C:\\Users\\vladi\\8_days\\users.txt");
    vector<string> accounts;
    if (inputFile.is_open()) {
        int fileUserID;
        string fileUsername, filePassword, fileEmail;
        while (inputFile >> fileUserID >> fileUsername >> filePassword >> fileEmail) {
            if (fileUserID != accountId) {
                // Add the account to the vector
                string account = to_string(fileUserID) + " " + fileUsername + " " + filePassword + " " + fileEmail;
                accounts.push_back(account);
            }
        }
        inputFile.close();
    } else {
        cout << "Failed to open file for reading." << endl;
        system("pause");
        return;
    }

    // Rewrite the file with updated accounts
    ofstream outputFile("C:\\Users\\vladi\\8_days\\users.txt");
    if (outputFile.is_open()) {
        int newAccountId = 1;
        for (const string& account : accounts) {
            // Extract the account details
            stringstream ss(account);
            int fileUserID;
            string fileUsername, filePassword, fileEmail;
            ss >> fileUserID >> fileUsername >> filePassword >> fileEmail;

            // Update the account ID
            outputFile << newAccountId << " " << fileUsername << " " << filePassword << " " << fileEmail << endl;
            newAccountId++;
        }
        outputFile.close();

        cout << "Account deleted successfully!" << endl;
        system("pause");
        displayAccounts();
    } else {
        cout << "Failed to open file for writing." << endl;
        system("pause");
    }
}


void displayAccounts() {
    system("cls");
    cout << "\t\t     |=========================================================================================================================================================|\n";
    cout << "\t\t     |                                                                                                                                                         |\n";
    cout << "\t\t     |                                                                Joetech (Stock) Management System                                                        |\n";
    cout << "\t\t     |                                                                                                                                                         |\n";
    cout << "\t\t     |=========================================================================================================================================================|\n";
    cout << "\t\t     |                                                                                                                                                         |\n";
    cout << "\t\t     |                                                                       List of Accounts                                                                  |\n";
    cout << "\t\t     |                                                                                                                                                         |\n";
    cout << "\t\t     |=========================================================================================================================================================|\n";
    cout << " \n" << endl;
    cout << setw(30) << "ID " << setw(25) << " NAME  " << setw(30) << " Email " << endl;

    ifstream inputFile("C:\\Users\\vladi\\8_days\\users.txt");
    if (inputFile.is_open()) {
        int userID;
        string username, password, email;
        while (inputFile >> userID >> username >> password >> email) {
            cout << setw(28) << userID << setw(25) << username << setw(25) << email << endl;
        }
        inputFile.close();
    } else {
        cout << "Failed to open file for reading." << endl;
        system("pause");
        return;
    }

    cout << " \n" << endl;
    cout << " \n" << endl;
    cout << "\t\t      |=========================================================================================================================================================|\n";
    cout << "\t\t      |                      [B] Back       [S] Select Account     [D] Delete Account     [U] Update Account                                                    |\n";
    cout << "\t\t      |=========================================================================================================================================================|\n";
    cout << "\t\t\t\t\t[<=>] : ";
    string pick6;
    cin >> pick6;
    if (pick6 == "B" || pick6 == "b") {
        account();
    } else if (pick6 == "S" || pick6 == "s") {
        selectAccount();
    } else if (pick6 == "D" || pick6 == "d") {
        int accountId;
        cout << "Input ID to delete: ";
        cin >> accountId;
        deleteAccount(accountId);
    } else if (pick6 == "U" || pick6 == "u") {
        int accountId;
        cout << "Input ID to update: ";
        cin >> accountId;
        updateAccount(accountId);
    } else {
        system("pause");
        displayAccounts();
    }
}

void selectAccount() {
    int accountId;
    cout << "Input ID to select: ";
    cin >> accountId;

    // Display the selected ID
    cout << "Selected ID: " << accountId << endl;

    // Read and display the current details of the selected account
    ifstream inputFile("C:\\Users\\vladi\\8_days\\users.txt");
    if (inputFile.is_open()) {
        int fileUserID;
        string fileUsername, filePassword, fileEmail;
        bool accountFound = false;
        while (inputFile >> fileUserID >> fileUsername >> filePassword >> fileEmail) {
            if (fileUserID == accountId) {
                accountFound = true;
                cout << "Current details of the selected account:" << endl;
                cout << "ID: " << fileUserID << endl;
                cout << "Username: " << fileUsername << endl;
                cout << "Password: " << filePassword << endl;
                cout << "Email: " << fileEmail << endl;
                break;
            }
        }
        inputFile.close();

        if (!accountFound) {
            cout << "Account not found." << endl;
            system("pause");
            displayAccounts();
            return;
        }
    } else {
        cout << "Failed to open file for reading." << endl;
        system("pause");
        return;
    }

    cout << "\t\t      |=========================================================================================================================================================|\n";
    cout << "\t\t      |                      [B] Back          [D] Delete Account     [U] Update Account                                                                        |\n";
    cout << "\t\t      |=========================================================================================================================================================|\n";
    cout << "\t\t\t\t\t[<=>] : ";

    string pick7;
    cin >> pick7;
    if (pick7 == "B" || pick7 == "b") {
        displayAccounts();
    } else if (pick7 == "D" || pick7 == "d") {
        deleteAccount(accountId);
    } else if (pick7 == "U" || pick7 == "u") {
        updateAccount(accountId);
    } else {
        system("pause");
        displayAccounts();
    }
}

void updateAccount(int accountId) {
    // Read and display the current details of the selected account
    ifstream inputFile("C:\\Users\\vladi\\8_days\\users.txt");
    if (inputFile.is_open()) {
        int fileUserID;
        string fileUsername, filePassword, fileEmail;
        while (inputFile >> fileUserID >> fileUsername >> filePassword >> fileEmail) {
            if (fileUserID == accountId) {
                cout << "Current details of the selected account:" << endl;
                cout << "ID: " << fileUserID << endl;
                cout << "Username: " << fileUsername << endl;
                cout << "Password: " << filePassword << endl;
                cout << "Email: " << fileEmail << endl;
                break;
            }
        }
        inputFile.close();
    } else {
        cout << "Failed to open file for reading." << endl;
        system("pause");
        return;
    }

    // Read the new details from the user
    string username, password, email;

    cout << "Enter new username: ";
    cin >> username;

    cout << "Enter new password: ";
    cin >> password;

    cout << "Enter new email: ";
    cin >> email;

    // Update the account details in the file
    ifstream inputFile2("C:\\Users\\vladi\\8_days\\users.txt");
    ofstream outputFile("users_tmp.txt");

    if (inputFile2.is_open() && outputFile.is_open()) {
        int fileUserID;
        string fileUsername, filePassword, fileEmail;
        while (inputFile2 >> fileUserID >> fileUsername >> filePassword >> fileEmail) {
            if (fileUserID == accountId) {
                // Update the details for the selected account
                outputFile << fileUserID << " " << username << " " << password << " " << email << endl;
            } else {
                // Write the other accounts as they are
                outputFile << fileUserID << " " << fileUsername << " " << filePassword << " " << fileEmail << endl;
            }
        }
        inputFile2.close();
        outputFile.close();

        // Remove the original file
        remove("users.txt");

        // Rename the temporary file to the original file
        rename("users_tmp.txt", "C:\\Users\\vladi\\8_days\\users.txt");

        cout << "Account details updated successfully!" << endl;
        system("pause");
    } else {
        cout << "Failed to open files for reading or writing." << endl;
        system("pause");
    }
}




void start() {
    int opt;
    system("cls");// clear screen
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                             Joetech Computer Hardware                                                         |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                      Welcome!!                                                                |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                  [1] Login                                                                    |\n";
    cout << "\t\t\t      |                                                                  [2] Register                                                                 |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t        [<=>] : ";
    cin >> opt;

    if (opt == 1) {
        login();// log in
    } else {
        Register();// Register
    }
}


void Dashboard() {
    system("cls");
    string dash; // Change the data type to string
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                           Joetech (Inventory) Management System                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                [D] Dashboard              [P] Product              [O] Orders              [A] Account              [L] Logout                |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                     Dashboard                                                                 |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                [1] View Products                                                              |\n";
    cout << "\t\t\t      |                                                                [2] View Orders                                                               |\n";
    cout << "\t\t\t      |                                                                [3] Search                                                                     |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t        [<=>] : ";
    cin >> dash;

    if (dash == "1") {
        displayProd();
    } else if (dash == "2") {
        ViewOrder();
    } else if (dash == "3") {
        searchProduct();
    } else if (dash == "D" || dash == "d") {
        Dashboard();
    }else if (dash == "A" || dash == "a"){
    	account();
	} else if (dash == "O" || dash == "o") {
        order();
    } else {
        menu();
    }
}


void ViewProd() {
    cout << " Total Prod\n";
    system("pause");
    Dashboard();
}

void ViewOrder() {
    cout << " Total Order\n";
    system("pause");
    Dashboard();
}

void stock() {
    cout << " Stock\n";
    system("pause");
    Dashboard();
}


int main() {
	system("cls");
    okay:
    char open;
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                             Joetech Computer Hardware                                                         |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                       Welcome!!                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t       [<=>]: ";
    cin >> open;

    if (open == 'y' || open == 'Y') {
        cout << "\t\t\t\t\t\t\t    Welcome to Stock Management System!\n";
        int x = 1000;
        Sleep(x);
		start();
    }else {
        system("cls");
        goto okay;
    } 

    return 0;
}
