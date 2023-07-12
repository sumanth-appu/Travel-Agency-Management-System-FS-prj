#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <locale>

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

using namespace std;

// ANSI escape code for green text
const string GREEN_TEXT = "\033[1;32m";
const string RESET_COLOR = "\033[0m";
const string RED_TEXT="\077[1;32m";

void clearScreen() {
    system(CLEAR_SCREEN);
}

class CustomerManager {
    // ... Rest of the class implementation remains unchanged
    public:
    CustomerManager() {
        loadIndex();
    }
     bool authenticateAdmin(const string& username, const string& password) {
        string adminUsername = "sumanth";
        string adminPassword = "Appu@1234";

        return (username == adminUsername && password == adminPassword);
    }
     void addCustomer(const string& customerData) {
        ofstream file(customersFilename, ios::app); // Open the file in append mode

        if (file.is_open()) {
            file << customerData << endl; // Append the customer data to the file
            file.close();
            
            

            // Update the index map
            string customerID = customerData.substr(0, customerData.find(","));
            indexMap[customerID] = file.tellp();
        } else {
            cout << "Unable to open the file." << endl;
        }
    }
      void displayCustomers() {
        ifstream file(customersFilename);

        if (file.is_open()) {
            string line;
            cout << "Existing Customers:" << endl;
            while (getline(file, line)) {
                cout << line << endl; // Print each customer record
            }
            file.close();
        } else {
            cout << "Unable to open the file." << endl;
        }
    }
    void saveIndex() {
        ofstream indexFile(indexFilename);
        if (indexFile.is_open()) {
            for (const auto& entry : indexMap) {
                indexFile << entry.first << " " << entry.second << endl;
            }
            indexFile.close();
        } else {
            cout << "Unable to open the index file." << endl;
        }
    }
 // Inside the CustomerManager class

void deleteCustomer(const string& customerId) {
    ifstream inFile("customers.txt");
    ofstream outFile("temp.txt");

    bool found = false;
    string line;

    while (getline(inFile, line)) {
        if (line.substr(0, customerId.length()) != customerId) {
            outFile << line << endl;
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("customers.txt");
    rename("temp.txt", "customers.txt");

    if (found) {
        cout << GREEN_TEXT << "Customer record deleted successfully." << RESET_COLOR << endl;
    } else {
        cout << GREEN_TEXT << "Customer record not found. Please enter a valid customer ID." << RESET_COLOR << endl;
    }
}
 


private:
    unordered_map<string, int> indexMap;
    const string indexFilename = "index.txt";
    const string customersFilename = "customers.txt";

    void loadIndex() {
        ifstream indexFile(indexFilename);
        if (indexFile.is_open()) {
            string id;
            int pos;
            while (indexFile >> id >> pos) {
                indexMap[id] = pos;
            }
            indexFile.close();
        }
    }

};

class CabManager {
public:
    void bookCab() {
        int choice;

        while (true) {
            cout << GREEN_TEXT << "Book Cab" << RESET_COLOR << endl;
            cout << GREEN_TEXT << "1. Check for available cabs" << RESET_COLOR << endl;
            cout << GREEN_TEXT << "2. View ride details" << RESET_COLOR << endl;
            cout << GREEN_TEXT << "3.Go Back" << RESET_COLOR << endl;
            cout << GREEN_TEXT << "Enter your choice: " << RESET_COLOR;
            cin >> choice;

            clearScreen();
                        switch (choice) {
                case 1: {
                    // ... Existing implementation for checking available cabs
                            string customerId;
                            string cabType;
                            double distance;
                            double price;

                            cout << GREEN_TEXT << "Enter customer ID: " << RESET_COLOR;
                            cin >> customerId;

                            cout << GREEN_TEXT << "Select cab type:" << RESET_COLOR << endl;
                            cout << GREEN_TEXT << "1. Normal Cab (Price: $12.0)" << RESET_COLOR << endl;
                            cout << GREEN_TEXT << "2. Premium Cab (Price: $25.0)" << RESET_COLOR << endl;
                            cout << GREEN_TEXT << "Enter your choice: " << RESET_COLOR;
                            cin >> cabType;

                            cout << GREEN_TEXT << "Enter total distance (in km): " << RESET_COLOR;
                            cin >> distance;

                           
                   
                        string cabTypeName;

                        if (cabType == "1") {
                            price = 12.0;
                            cabTypeName = "Normal";
                        } else if (cabType == "2") {
                            price = 25.0;
                            cabTypeName = "Premium";
                        } else {
                            cout << GREEN_TEXT << "Invalid cab type. Please try again." << RESET_COLOR << endl;
                            return;
                        }

                        double totalCost = price * distance;

                        // ... Existing implementation for booking a cab

                        cout << "Cab booked successfully. Ride details: " << cabTypeName << " Cab, Distance: " << distance << " km, Total Fare: $" << totalCost<< endl;
                        
                        // Store ride details in a file

                        ofstream outFile("ride_details.txt", ios::app);
                        if (outFile.is_open()) {
                            outFile << customerId << ":" << cabTypeName << "," << distance << "," << totalCost << endl;
                            outFile.close();
                            cout << GREEN_TEXT << "Ride details stored successfully." << RESET_COLOR << endl;
                        } else {
                            cout << GREEN_TEXT << "Failed to store ride details." << RESET_COLOR << endl;
                        }
                        break;
                    }

                
                case 2: {
                    viewRideDetails();
                    break;
                }
                case 3: {
                  
                    break;
                }
                default:
                    cout << GREEN_TEXT << "Invalid choice. Please try again." << RESET_COLOR << endl;
            }
            if (choice==3){
                break;
            }
        }
    }
    void viewRideDetails() {
        ifstream inFile("ride_details.txt");
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                cout << GREEN_TEXT << line << RESET_COLOR << endl;
            }
            inFile.close();
        } else {
            cout << GREEN_TEXT << "Unable to open ride details file." << RESET_COLOR << endl;
        }
    }
};

class HotelManager {
public:
    void bookHotel() {
        int Hchoice;

  while (true) {
            cout << GREEN_TEXT << "Book Hotel" << RESET_COLOR << endl;
            cout << GREEN_TEXT << "1. Check for available hotels" << RESET_COLOR << endl;
            cout << GREEN_TEXT << "2. View booking details" << RESET_COLOR << endl;
            cout << GREEN_TEXT << "3.Go Back" << RESET_COLOR << endl;
            cout << GREEN_TEXT << "Enter your choice: " << RESET_COLOR;
            cin >> Hchoice;

            clearScreen();

            switch (Hchoice) {
                        case 1: {
                            // ... Existing implementation for checking available hotels
                                    string customerId;
                                    string HotelType;
                                    double days;
                                    double price;

                                    cout << GREEN_TEXT << "Enter customer ID: " << RESET_COLOR;
                                    cin >> customerId;

                                    cout << GREEN_TEXT << "Select hotel type:" << RESET_COLOR << endl;
                                    cout << GREEN_TEXT << "1. Hotel Anand (Price: $50.0)" << RESET_COLOR << endl;
                                    cout << GREEN_TEXT << "2. Premium hanse Hotel   (Price: $80.0)" << RESET_COLOR << endl;
                                    cout << GREEN_TEXT << "Enter your choice: " << RESET_COLOR;
                                    cin >> HotelType;

                                    cout << GREEN_TEXT << "Enter total Number of days: " << RESET_COLOR;
                                    cin >> days;

                                
                        
                                string hotelTypeName;

                                if (HotelType == "1") {
                                    price = 5000.0;
                                    hotelTypeName = "Normal";
                                } else if (HotelType == "2") {
                                    price = 8000.0;
                                    hotelTypeName = "Premium";
                                } else {
                                    cout << GREEN_TEXT << "Invalid cab type. Please try again." << RESET_COLOR << endl;
                                    return;
                                }

                                double totalhotelCost = price * days;

                                // ... Existing implementation for booking a cab

                                cout << "Hotel  booked successfully. Hotel details: " << hotelTypeName << " Hotel, NUmber of days: " <<days << ", Total Hotel BIll: $" << totalhotelCost<< endl;
                                
                                // Store ride details in a file

                                ofstream outFile("hotel_booking_details.txt", ios::app);
                                if (outFile.is_open()) {
                                    outFile << customerId << ":" << hotelTypeName << "," << days << "," << totalhotelCost << endl;
                                    outFile.close();
                                    cout << GREEN_TEXT << "Ride details stored successfully." << RESET_COLOR << endl;
                                } else {
                                    cout << GREEN_TEXT << "Failed to store ride details." << RESET_COLOR << endl;
                                }
                                break;
                            }

                        
                        
                        case 2: {
                            viewBookingDetails();
                            break;
                        }
                        case 3:{

                            cout<<"Return to the main menu "<<endl;
                            break;
                        }

                                      
                        default:{cout << GREEN_TEXT << "Invalid choice. Please try again." << RESET_COLOR << endl; break;}
        }
        if(Hchoice==3){break;} 
                } 

        }
       
 void viewBookingDetails() {
        ifstream inFile("hotel_booking_details.txt");
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                cout << GREEN_TEXT << line << RESET_COLOR << endl;
            }
            inFile.close();
        } else {
            cout << GREEN_TEXT << "Unable to open hotel booking details file." << RESET_COLOR << endl;
        }
    }

};
class Billing {
public:
    double calculateTotalPrice(const string& customerId) {
        double cabPrice = getCabPrice(customerId);
        double hotelPrice = getHotelPrice(customerId);

        return cabPrice + hotelPrice;
    }

private:
    double getCabPrice(const string& customerId) {
    ifstream inFile("ride_details.txt");
    double cabPrice = 0.0;

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            size_t pos = line.find(":");
            if (line.substr(0, pos) == customerId) {
                size_t start = pos + 1;
                size_t end = line.find(",", start);
                string cabPriceStr = line.substr(start, end - start);
                
                try {
                    cabPrice = stod(cabPriceStr);
                } catch (const std::invalid_argument& e) {
                    cout << GREEN_TEXT << "Invalid cab price. Please check the ride details file." << RESET_COLOR << endl;
                }
                break;
            }
        }
        inFile.close();
    } else {
        cout << GREEN_TEXT << "Unable to open ride details file." << RESET_COLOR << endl;
    }

    return cabPrice;
}

double getHotelPrice(const string& customerId) {
    ifstream inFile("hotel_booking_details.txt");
    double hotelPrice = 0.0;

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            size_t pos = line.find(":");
            if (line.substr(0, pos) == customerId) {
                size_t start = pos + 1;
                size_t end = line.find(",", start);
                string hotelPriceStr = line.substr(start, end - start);

                try {
                    hotelPrice = stod(hotelPriceStr);
                } catch (const std::invalid_argument& e) {
                    cout << GREEN_TEXT << "Invalid hotel price. Please check the hotel booking details file." << RESET_COLOR << endl;
                }
                break;
            }
        }
        inFile.close();
    } else {
        cout << GREEN_TEXT << "Unable to open hotel booking details file." << RESET_COLOR << endl;
    }

    return hotelPrice;
}

};




int main() {
    string adminUsername = "admin";
    string adminPassword = "password";
    int n;
    while(n<4){
            string username, password;
            cout << GREEN_TEXT << "Admin Login" << RESET_COLOR << endl;
            cout << GREEN_TEXT << "Please enter your username: " << RESET_COLOR;
            cin >> username;
            cout << GREEN_TEXT << "Please enter your password: " << RESET_COLOR;
            cin >> password;

             CustomerManager customerManager;
             CabManager cabManager;
             HotelManager HotelManager;
             Billing billing;
            if (customerManager.authenticateAdmin(username, password)) {
                cout << GREEN_TEXT << "Authentication successful. Welcome, admin!" << RESET_COLOR << endl;

                int choice;
                while (true) {
                    cout << GREEN_TEXT << " _________ Choose an action__________ " << RESET_COLOR << endl;
                    cout << GREEN_TEXT << "|                                    |" << RESET_COLOR << endl;
                    cout << GREEN_TEXT << "|        1. Manage Customers         |"    << RESET_COLOR << endl;
                    cout << GREEN_TEXT << "|        2. Book Cab                 |" << RESET_COLOR << endl;
                    cout << GREEN_TEXT << "|        3. Book Hotels              |" << RESET_COLOR << endl;
                    cout << GREEN_TEXT << "|        4. Billing                  |" << RESET_COLOR << endl;
                    cout << GREEN_TEXT << "|        5. logout                   |" << RESET_COLOR << endl;
                    cout << GREEN_TEXT << "|____________________________________|" << RESET_COLOR << endl;
                    cout << GREEN_TEXT << "Enter your choice: " << RESET_COLOR;
                    cin >> choice;

                    clearScreen();

                    switch (choice) {
                        case 1: {
                            cout << GREEN_TEXT << "Customer Management" << RESET_COLOR << endl;

                            int customerChoice;
                            while (true) {
                                cout << GREEN_TEXT << "Choose an action:" << RESET_COLOR << endl;
                                cout << GREEN_TEXT << "1. Add Customer" << RESET_COLOR << endl;
                                cout << GREEN_TEXT << "2. Display Customers" << RESET_COLOR << endl;
                                cout << GREEN_TEXT << "3. Delete Customer" << RESET_COLOR << endl;
                                cout << GREEN_TEXT << "4. Go Back" << RESET_COLOR << endl;
                                cout << GREEN_TEXT << "Enter your choice: " << RESET_COLOR;
                                cin >> customerChoice;

                                clearScreen();

                                switch (customerChoice) {
                                    case 1: {
                                        string customerName, customerAddress, customerPhone,customerID;
                                        cout << GREEN_TEXT << "Enter customerID: " << RESET_COLOR;
                                        cin.ignore(); // Ignore the newline character in the input buffer
                                        getline(cin, customerID);
                                        cout << GREEN_TEXT << "Enter customer name: " << RESET_COLOR;
                                        getline(cin, customerName);

                                        cout << GREEN_TEXT << "Enter customer address: " << RESET_COLOR;
                                        getline(cin, customerAddress);

                                        cout << GREEN_TEXT << "Enter customer phone number: " << RESET_COLOR;
                                        getline(cin, customerPhone);

                                        string customerData = customerID + "|"+ customerName +"|" +customerAddress + "|" + customerPhone + "|$|";

                                        customerManager.addCustomer(customerData);
                                        cout << GREEN_TEXT << "Customer added successfully." << RESET_COLOR << endl;
                                        
                                        // customerManager.sortCustomersByID();
                                        break;
                                    }
                                    case 2:
                                        // ... Existing implementation for displaying customers
                                        customerManager.displayCustomers();
                                        break;
                                    case 3: {
                                        // ... Existing implementation for deleting customers
                                                                        string customerId;
                                        cout << GREEN_TEXT << "________________________Delete Customer___________________________________" << RESET_COLOR <<endl;
                                        cout << GREEN_TEXT << "                                                                          " << RESET_COLOR <<endl;
                                        cout << GREEN_TEXT << "Enter the customer ID to delete (or enter 'all' to delete all customers): " << RESET_COLOR <<endl;
                                        cin >> customerId;

                                        clearScreen();

                                        customerManager.deleteCustomer(customerId);
                                        cout << GREEN_TEXT << "Customer deleted successfully." << RESET_COLOR << endl;

                                        break;
                                    }
                                    case 4:
                                        cout << GREEN_TEXT << "Returning to Admin Menu" << RESET_COLOR << endl;
                                        break;
                                    default:
                                        cout << GREEN_TEXT << "Invalid choice! Please try again." << RESET_COLOR << endl;
                                }

                                if (customerChoice == 4) {
                                    break;
                                }
                            }
                            break;
                        }
                        case 2: {
                            cabManager.bookCab();
                            break;
                        }
                        case 3:
                            HotelManager.bookHotel();
                            break;

                        case 4:{
                                string customerId;
                                cout<<GREEN_TEXT<<"______________Bill GENERATION________________"<<endl;
                                cout << GREEN_TEXT << "Enter Customer ID: " << RESET_COLOR;
                                cin >> customerId;
                                double totalPrice = billing.calculateTotalPrice(customerId);
                                cout << GREEN_TEXT << "Total Price for Customer ID " << customerId << ": $" << totalPrice << RESET_COLOR << endl;
                                break;
                        }

                        case 5:{
                            cout<<GREEN_TEXT<< "logging out!!!"<<RESET_COLOR<<endl;
                            exit(0);
                            }
                        default:
                            cout << GREEN_TEXT << "Invalid choice! Please try again." << RESET_COLOR << endl;
                    }

                
                }
            } else {
                cout << GREEN_TEXT << "Authentication failed. Invalid username or password.\n Renter the details." << RESET_COLOR << endl;
            }
            n++;
    }
    cout<<GREEN_TEXT<<"OPPS!!!!!!!!!!!!!!!!!!!!You enter wrong details more than 3 times , Soo Login failed Try to  after Sometime!!!!!!!!!!!!!!!!!!!!"<<RESET_COLOR<<endl;
    return 0;
}
