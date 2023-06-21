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
void Dashboard();
void TotalProd();
void TotalOrder();
void stock();
void initializeUsers();
void logout();
void Product();
void AddProduct();
void displayProd();
void updateProduct(int selectedId);
void selectProduct();
void deleteProduct(int selectedId);

vector<string> categories; // Declare the vector globally

struct User {
    string username;
    string password;
};

struct Product {
    int id;
    string name;
    string category;
    string description;
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
int stringToInt(const std::string& str) {
    std::istringstream iss(str);
    int value;
    iss >> value;
    return value;
}

// Function to convert string to double
double stringToDouble(const std::string& str) {
    std::istringstream iss(str);
    double value;
    iss >> value;
    return value;
}

std::string formatPrice(double price) {
    std::ostringstream ss;
    ss << "$" << std::fixed << std::setprecision(2) << price;

    std::string priceString = ss.str();
    std::string::size_type decimalPos = priceString.find('.');

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

void login() {
    string username, password;
    int attemptCount = 0;  // Counter for login attempts

    system("cls");
    cout << "\t\t\t      |================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                              Joetech (Stock) Management System                                 |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |================================================================================================|\n";
    cout << "\t\t\t      |                                            Login                                               |\n";
    cout << "\t\t\t      |================================================================================================|\n";
    cout << "\n" << endl;
    cout << "\t\t\t\t\t\t\t\t    Username: ";
    cin >> username;
    cout << "\t\t\t\t\t\t\t\t    Password: ";

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
    ifstream inputFile("users.txt");
    if (inputFile.is_open()) {
        string fileUsername, filePassword;
        while (inputFile >> fileUsername >> filePassword) {
            if (fileUsername == username && filePassword == password) {
                found = true;
                break;
            }
        }
        inputFile.close();
    } else {
        cout << "Failed to open file for reading." << endl;
        system("pause");
    }

    if (found) {
        cout << "\n\n\t\t\t\t\t\t\t\t    Login successful!" << endl;
        Sleep(3000);
        three_Admin();
    } else {
        attemptCount++;
        const int MAX_ATTEMPTS = 3;

        if (attemptCount > MAX_ATTEMPTS) {
            cout << "\n\n\t\t\t\t\t\t\t\t    Maximum number of login attempts reached. Exiting." << endl;
            Sleep(3000);
            exit(0);  // Terminate the program
        } else {
            cout << "\n\n\t\t\t\t\t\t\t\t    Login failed. Invalid username or password." << endl;
            Sleep(3000);
            login();
        }
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
    string username, password, confirmPassword;
    system("cls");
    cout << "\t\t\t      |================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                              Joetech (Stock) Management System                                 |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |================================================================================================|\n";
    cout << "\t\t\t      |                                            Register                                            |\n";
    cout << "\t\t\t      |================================================================================================|\n";
    cout << "\n" << endl;
    cout << "\t\t\t\t\t\t\t\t    Username: ";
    cin >> username;

    while (true) {
        cout << "\t\t\t\t\t\t\t\t    Password: ";
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
        cout << endl;

        cout << "\t\t\t\t\t\t\t\t    Confirm Password: ";
        confirmPassword = "";
        while ((ch = _getch()) != '\r') {  // Read characters until Enter is pressed
            if (ch == '\b') {  // Handle backspace
                if (!confirmPassword.empty()) {
                    confirmPassword.erase(confirmPassword.size() - 1);  // Remove the last character
                    cout << "\b \b";  // Erase previous asterisk
                }
            } else {
                confirmPassword.push_back(ch);
                cout << '*';  // Print asterisk instead of the actual character
            }
        }
        cout << endl;

        if (password == confirmPassword) {
            // Rest of your code for registration...
            // ...
            cout << "\t\t\t\t\t\t\t\t    Registration successful!" << endl;
            Sleep(2000);
            break;  
        } else {
            cout << "Passwords do not match. Please try again." << endl;
            system("pause");  
            password = "";
            confirmPassword = "";
            system("cls");
            cout << "\t\t\t      |================================================================================================|\n";
            cout << "\t\t\t      |                                                                                                |\n";
            cout << "\t\t\t      |                              Joetech (Stock) Management System                                 |\n";
            cout << "\t\t\t      |                                                                                                |\n";
            cout << "\t\t\t      |================================================================================================|\n";
            cout << "\t\t\t      |                                            Register                                            |\n";
            cout << "\t\t\t      |================================================================================================|\n";
            cout << "\n" << endl;
            cout << "\t\t\t\t\t\t\t\t    Username: " << username << endl;  
        }
    }
    
    ofstream outputFile("users.txt", ios::app); // Open file in append mode
    if (outputFile.is_open()) {
        outputFile << username << " " << password << endl;
        outputFile.close();
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
    cout << "\t\t\t      |                                                      Joetech (Stock) Inventory Management System                                              |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |       [D] Dashboard        [B] Brand        [C] Category         [P] Product          [O] Orders          [A] Account          [L] Logout     |\n";
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
		cout<<" Display Account";
	} else if (choice3 == "2"){
		cout<<" Edit Account";
	}else if (choice3 == "3"){
		cout<<" Remove Account";
	}else if (choice3 == "D" || choice3 == "d") {
        Dashboard();
    } else if (choice3 == "A" || choice3 == "a") {
    	account();
	} else if (choice3 == "P" || choice3 == "p"){
        Product();
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
    cout << "\t\t\t      |                                                      Joetech (Stock) Inventory Management System                                              |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |       [D] Dashboard        [B] Brand        [C] Category         [P] Product          [O] Orders          [A] Account          [L] Logout     |\n";
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
    }else {
        start();
    }
}

void Product(){
    system("cls"); // Clear the screen
    string products;
    int selectedId = 0;
    cout << "\t\t\t      |================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                            Joetech (POS) Inventory Management System                           |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |             [D] Dashboard |  [P] Product | [O] Orders | [A] Account | [L] Logout               |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |================================================================================================|\n";
    cout << "\t\t\t      |                                            Product                                             |\n";
    cout << "\t\t\t      |================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                                       [1] Add Products                                         |\n";
    cout << "\t\t\t      |                                       [2] Display Products                                     |\n";
    cout << "\t\t\t      |                                       [3] Edit products                                        |\n";
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
    cin >> products;

    if (products == "1"){
        AddProduct();
    }
    else if (products == "2"){
        displayProd();
    }else if (products =="3"){
    	if (selectedId != 0) {
            updateProduct(selectedId);
        } else {
            // Prompt for selecting a product by ID
            cout << "Enter the ID of the product you want to edit: ";
            cin >> selectedId;
            system("cls");
            updateProduct(selectedId);
        }
	}else{
    	Product();
	}
}
void AddProduct() {
    system("cls"); // Clear the screen
    string name, category, description, price, quantity;

    // Read the existing IDs from the file
    vector<int> existingIDs;
    ifstream inputFile("comproddis.txt");
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
    while (std::find(existingIDs.begin(), existingIDs.end(), id) != existingIDs.end()) {
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

        ofstream file("comproddis.txt", ios::app);
        if (file.is_open()) {
            file << id << "," << name << "," << category << "," << description << "," << price << "," << quantity << endl;

            cout << "Product added successfully!" << endl;
            file.close();
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
    ifstream inputFile("comproddis.txt");
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string token;

            // Extract data from the line using comma as the delimiter
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
            double price;
            istringstream(token) >> price;

            getline(ss, token, ',');
            int quantity;
            istringstream(token) >> quantity;
            
            // Display the product information
            cout << setw(20) << " NAME  " << setw(20) << " CATEGORY " << setw(20) << " Description " << setw(20) << " PRICE " << setw(20) << " Quantity " << endl;
            cout << setw(20) <<"  " << id <<" ";
            cout << setw(20) << "  " << name <<"  ";
            cout << setw(20) <<"  " << category <<"  ";
            cout << setw(20) <<"  " << description <<"  ";
            cout << setw(20) <<" $" << fixed << setprecision(2) << price <<"  ";
            cout << setw(20) <<"  " << quantity <<"  ";
            cout << "\n"<<endl;
        }
        	string pick2;
            cout << "\t\t\t\t\t\t========================================================================================================================\n";
            cout << "\t\t\t\t\t\t                          [B] Back [A] Add Product  [S] Select Product [D] Delete Product  [U] Update Product [O] Order \n";
            cout << "\t\t\t\t\t\t========================================================================================================================\n";
            cout << "\t\t\t\t\t\t [<=>] : ";
            cin >> pick2;
            
            if(pick2 == "B" || pick2 == "b"){
            	Product();
			}else if (pick2 == "A" || pick2 == "a"){
				AddProduct();
			}else if (pick2 == "S" || pick2 == "s"){
				selectProduct();
			}else if (pick2 == "D" || pick2 == "d") {
		    // Prompt for selecting a product by ID
			    int selectedId;
			    cout << "Enter the ID of the product you want to delete: ";
			    cin >> selectedId;
			    system("cls");
			    deleteProduct(selectedId);
			}else if (pick2 == "U" || pick2 == "u") {
            // Prompt for selecting a product by ID
	            int selectedId;
	            cout << "Enter the ID of the product you want to update: ";
	            cin >> selectedId;
	            system("cls");
	            updateProduct(selectedId);
	        } else{
				cout << "Order";
			}
        inputFile.close();
    } else {
        cout << "Failed to open file for reading." << endl;
    }
}
void updateProduct(int selectedId) {
    // Open the file for reading
    ifstream inputFile("comproddis.txt");
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
                string name, category, description, price, quantity;
                cout << "Enter updated product name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, name);
                cout << "Enter updated product category: ";
                getline(cin, category);
                cout << "Enter updated product description: ";
                getline(cin, description);
                cout << "Enter updated product price: ";
                getline(cin, price);
                cout << "Enter updated product quantity: ";
                getline(cin, quantity);

                // Create the updated product line
                stringstream updatedProduct;
                updatedProduct << id << "," << name << "," << category << "," << description << "," << price << "," << quantity;
                products.push_back(updatedProduct.str());
            } else {
                products.push_back(line);
            }
        }

        inputFile.close();

        if (found) {
            // Open the file for writing (clears the file)
            ofstream outputFile("comproddis.txt");
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
    ifstream inputFile("comproddis.txt");
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
                double price;
                istringstream(token) >> price;

                getline(ss, token, ',');
                int quantity;
                istringstream(token) >> quantity;

                // Display the product information
                cout << "Selected Product ID: " << id << endl;
                cout << "Name: " << name << endl;
                cout << "Category: " << category << endl;
                cout << "Description: " << description << endl;
                cout << "Price: $" << fixed << setprecision(2) << price << endl;
                cout << "Quantity: " << quantity << endl;

                // Prompt for options (Update or Delete)
                string pick2;
                cout << "\nChoose an option:\n";
                cout << "U. Update Product\n";
                cout << "D. Delete Product\n";
                cout << "Enter your choice: ";
                cin >> pick2;
                system("cls");

                if (pick2 == "U" || pick2 == "u") {
                    updateProduct(selectedId);
                } else if (pick2 == "D" || pick2 == "d") {
                    deleteProduct(selectedId);
                } else {
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
    ifstream inputFile("comproddis.txt");
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
            ofstream outputFile("comproddis.txt");
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



void start() {
    int opt;
    system("cls");// clear screen
    cout << "\t\t\t      |================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                            Joetech (Stock) Inventory Management System                         |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                                         Login Inventory                                        |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                                         [1] Log in                                             |\n";
    cout << "\t\t\t      |                                         [2] Register                                           |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |                                                                                                |\n";
    cout << "\t\t\t      |================================================================================================|\n";
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
    cout << "\t\t\t      |                            Joetech (POS) Inventory Management System                           |\n";
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
    char open;
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\t\t\t      |===============================================================================================================================================|\n";
    cout << "\t\t\t      |                                                                                                                                               |\n";
    cout << "\t\t\t      |                                                        Joetech Computer Hardware Inventory                                                    |\n";
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
    } 

    return 0;
}

