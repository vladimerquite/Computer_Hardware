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
void Order();
void Dashboard();
void TotalProd();
void TotalOrder();
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
    ifstream inputFile("users.txt");
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

void logout(){
	system("cls");
	cout << " System Logout Processing......\n";
	start();
}

void Order(){
	cout << "Order";
}

void searchProduct() {
    system("cls");

    ifstream inputFile("Prod.txt");

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
    ifstream inputFile("users.txt");
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
        three_Admin();
    } else {
        cout << "\n\n\t\t\t\t\t\t\t\t    Login failed. Invalid username or password." << endl;
        Sleep(3000);
        login();
    }
}

void three_Admin(){
	int pick1;
	system("cls");
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
    cout << "\t\t\t      |                                                 [1] Dealer          [2] Customer          [3] Admin                                           |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t       [<=>]: ";
    cin >> pick1;
    
	if(pick1 == '1'){
		cout<<" Dealer";
	} else if(pick1 == '2'){
		cout<<" Customer";
	}else{
		menu();
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

    ifstream inputFile("users.txt");
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

    ofstream outputFile("users.txt", ios::app); // Open file in append mode
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
    }else {
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
		Order();
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
    ifstream inputFile("Prod.txt");
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
        ofstream outputFile("Prod.txt", ios::app);
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
    ifstream inputFile("Prod.txt");
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
        cout << "\t\t      |                      [B] Back     [A] Add Product     [S] Select Product     [D] Delete Product     [U] Update Product     [O] Order                    |\n";
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
        } else {
            cout << "Order";
        }
        inputFile.close();
    } else {
        cout << "Failed to open file for reading." << endl;
    }
}


void updateProduct(int selectedId) {
    // Open the file for reading
    ifstream inputFile("Prod.txt");
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
            ofstream outputFile("Prod.txt");
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
    ifstream inputFile("Prod.txt");
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
	cout << setw(28) << id << setw(30) << name << setw(25) << category << setw(32) << description << setw(15) << "$" << fixed << setprecision(2) << price << setw(15) << quantity << setw(15) << status << endl;
    // Prompt for options (Update or Delete)
    string pick2;
    cout << " \n" << endl;
    cout << " \n" << endl;
    cout << "\t\t      |=========================================================================================================================================================|\n";
    cout << "\t\t      |                      [B] Back     [A] Add Product     [S] Select Product     [D] Delete Product     [U] Update Product     [O] Order                    |\n";
    cout << "\t\t      |=========================================================================================================================================================|\n";
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
    ifstream inputFile("Prod.txt");
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
            ofstream outputFile("Prod.txt");
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

void deleteAccount(int accountId) {
    // Read all accounts from the file
    ifstream inputFile("users.txt");
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
    ofstream outputFile("users.txt");
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

    ifstream inputFile("users.txt");
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
    ifstream inputFile("users.txt");
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
    ifstream inputFile("users.txt");
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
    ifstream inputFile2("users.txt");
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
        rename("users_tmp.txt", "users.txt");

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
    cout << "\t\t\t      |================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                            Joetech (Stock) Management System                                   |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |      [D] Dashboard | [C] Category | [P] Product | [O] Orders | [A] Account | [L] Logout        |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |================================================================================================|\n";
    cout << "\t\t\t      |                                          Dashboard                                             |\n";
    cout << "\t\t\t      |================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                                       [1] Total Products                                       |\n";
    cout << "\t\t\t      |                                       [2] Total Orders                                         |\n";
    cout << "\t\t\t      |                                       [3] Stock                                                |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |================================================================================================|\n";
    cout << "\t\t\t        [<=>] : ";
    cin >> dash;

    if (dash == "1") {
        TotalProd();
    } else if (dash == "2") {
        TotalOrder();
    } else if (dash == "3") {
        stock();
    } else if (dash == "D" || dash == "d") {
        Dashboard();
    }else if (dash == "A" || dash == "a"){
    	account();
	} else {
        menu();
    }
}


void TotalProd() {
    cout << " Total Prod\n";
    system("pause");
    Dashboard();
}

void TotalOrder() {
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
