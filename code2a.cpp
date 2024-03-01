#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <ctime>

using namespace std;

class Car {
private:
    string model;
    string condition;
    bool available;
    time_t returnDate;
public:
    Car(string _model, string _condition) : model(_model), condition(_condition), available(true) {

    }
    void setCondition(const string& newCondition) {
        condition = newCondition;
    }
    static unordered_map<string, Car*> carDatabase;
    void rent();
    void returnCar();
    bool isAvailable() const { return available; }
    void setReturnDate(int days);
    void showDueDate();
    string getModel() const { return model; }
    string getCondition() const { return condition; }
    time_t getReturnDate() const { return returnDate; } // Added public accessor
};

class Customer {
private:
    int id;
    vector<Car*> rentedCars;
    float fineDue;
    int customerRecord;
    string c_name; // New member variable for customer name
    string password;
public:
    Customer(int _id, int _customerRecord) : id(_id), fineDue(0), customerRecord(_customerRecord) {}

    // New member function to set the customer name
    void setPass(const string& pass){password=pass;}
    string getPass(){return password;}
    void setName(const string& newName) { c_name = newName; }
    string getName() const { return c_name; }
    // Public member functions to access and modify private members
    void setId(int newId) { id = newId; }
    void setCustomerRecord(int newCustomerRecord) { customerRecord = newCustomerRecord; }
    int getId() const {
        return id;
    }
    void rentCar(Car* car);
    void returnCar(Car* car);
    void browseRentedCars();
    float getFineDue() const {
        return fineDue;
    }
    void clearDue();
    void saveToFile();
    static Customer* loadFromFile(int id);
    static unordered_map<int, Customer*> customerDatabase;
    static void addCustomer(int id, Customer* customer);
    static void deleteCustomer(int id);
    static Customer* searchCustomer(int id);
    vector<Car*>& getRentedCars() { return rentedCars; } // Public accessor for rentedCars
};


class Employee {
private:
    int id;
    vector<Car*> rentedCars;
    float fineDue;
    int employeeRecord;
    string e_name;
    string password;
public:
    Employee(int _id, int _employeeRecord) : id(_id), fineDue(0), employeeRecord(_employeeRecord) {}
    // New member function to set the customer name
    void setPass(const string& pass){password=pass;}
    string getPass(){return password;}
    void setName(const string& newName) { e_name = newName; }
    string getName() const { return e_name; }
    // Public member functions to access and modify private members
    void setId(int newId) { id = newId; }
    void setEmployeeRecord(int newEmployeeRecord) { employeeRecord = newEmployeeRecord; }
    int getId() const {
        return id;
    }
    void rentCar(Car* car);
    void returnCar(Car* car);
    void browseRentedCars();
    float getFineDue() const {
        return fineDue;
    }
    void clearDue();
    void saveToFile();
    static Employee* loadFromFile(int id);
    static unordered_map<int, Employee*> employeeDatabase;
    static void addEmployee(int id, Employee* employee);
    static void deleteEmployee(int id);
    static Employee* searchEmployee(int id);
    vector<Car*>& getRentedCars() { return rentedCars; } // Public accessor for rentedCars
};
class Manager : public Employee {
public:
    Manager(int _id, int _employeeRecord) : Employee(_id, _employeeRecord) {}

    // Additional functions for Manager's capabilities
    void addCustomer(int id, Customer* customer);
    void updateCustomer(int id, Customer* customer);
    void deleteCustomer(int id);
    void addEmployee(int id, Employee* employee);
    void updateEmployee(int id, Employee* employee);
    void deleteEmployee(int id);
    void addCar(const Car& car,vector<Car*>& cars_set);
    void updateCar(const string& model, const Car& car,vector<Car*>& cars_set);
    void deleteCar(const string& model,vector<Car*>& cars_set);
    void viewAllCars();
    void viewRentedCars();
};
void Manager::addCustomer(int id, Customer* customer) {
    Customer::addCustomer(id, customer);
}

void Manager::updateCustomer(int id, Customer* customer) {
    // Assuming the customer exists in the database
    if (Customer::customerDatabase.find(id) != Customer::customerDatabase.end()) {
        Customer::customerDatabase[id] = customer;
        customer->saveToFile();
    } else {
        cout << "Customer with ID " << id << " not found.\n";
    }
}

void Manager::deleteCustomer(int id) {
    Customer::deleteCustomer(id);
}

void Manager::addEmployee(int id, Employee* employee) {
    Employee::addEmployee(id, employee);
}

void Manager::updateEmployee(int id, Employee* employee) {
    // Assuming the employee exists in the database
    if (Employee::employeeDatabase.find(id) != Employee::employeeDatabase.end()) {
        Employee::employeeDatabase[id] = employee;
        employee->saveToFile();
    } else {
        cout << "Employee with ID " << id << " not found.\n";
    }
}

void Manager::deleteEmployee(int id) {
    Employee::deleteEmployee(id);
}

void Manager::addCar(const Car& car,vector<Car*>& cars_set) {
    // Assuming the car does not already exist in the database
    // string model = car.getModel();
    // if (Car::carDatabase.find(model) == Car::carDatabase.end()) {
    //     Car::carDatabase[model] = car;
    // } else {
    //     cout << "Car with model " << model << " already exists.\n";
    // }
    string model, condition;
                                
                                // Prompt the user to enter the details of the car
                                cout << "Enter the model of the car: ";
                                cin >> model;
                                cout << "Enter the condition of the car: ";
                                cin >> condition;

                                // Create a new Car object
                                Car* newCar = new Car(model, condition);

                                // Add the new car to the vector or database of cars
                                // For example, if you have a vector of cars:
                                cars_set.push_back(newCar);
                                cout << "Car added successfully.\n";
}

void Manager::updateCar(const string& model, const Car& car,vector<Car*>& cars_set) {
    // Assuming the car exists in the database
    // if (Car::carDatabase.find(model) != Car::carDatabase.end()) {
    //     Car::carDatabase[model] = car;
    // } else {
    //     cout << "Car with model " << model << " not found.\n";
    // }
    //string model;
                                bool found = false;

                                // Prompt the user to enter the model of the car to update

                                //cout << "Enter the model of the car to update: ";
                                //cin >> model;

                                // Search for the car in the vector or database of cars
                                for (Car* car : cars_set) {
                                    if (car->getModel() == model) {
                                        // Car found, allow the user to update its details
                                        string newCondition;

                                        // Prompt the user to enter the new condition of the car
                                        cout << "Enter the new condition of the car: ";
                                        cin >> newCondition;

                                        // Update the condition of the car
                                        car->setCondition(newCondition);

                                        cout << "Car updated successfully.\n";
                                        found = true;
                                        break;
                                    }
                                }

                                if (!found) {
                                    cout << "Car not found.\n";
                                }
}

void Manager::deleteCar(const string& model ,vector<Car*>& cars_set ) {
    // string model;
    bool found = false;

    //                             // Prompt the user to enter the model of the car to delete
    //                             cout << "Enter the model of the car to delete: ";
    //                             cin >> model;

    // Iterate through the vector or database of cars
    for (auto it = cars_set.begin(); it != cars_set.end(); ++it) {
        if ((*it)->getModel() == model) {
            // Car found, erase it from the list
            cars_set.erase(it);
            cout << "Car deleted successfully.\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Car not found.\n";
    }
}

void Manager::viewAllCars() {
    cout << "All Cars:\n";
    for (const auto& pair : Car::carDatabase) {
        cout << "Model: " << pair.first << ", Condition: " << pair.second->getCondition() << endl;
    }
}

void Manager::viewRentedCars() {
    cout << "Cars Rented:\n";
    for (const auto& pair : Customer::customerDatabase) {
        Customer* user = pair.second;
        cout << "User ID: " << user->getId() << endl;
        cout << "Cars rented:\n";
        for (auto car : user->getRentedCars()) {
            cout << "Model: " << car->getModel() << endl;
        }
    }
}


unordered_map<int, Customer*> Customer::customerDatabase;
unordered_map<int, Employee*> Employee::employeeDatabase;

unordered_map<string, Car*> Car::carDatabase;

void Car::rent() {
    available = false;
}
void Car::returnCar() {
    available = true;
}

void Car::setReturnDate(int days) {
    returnDate = time(0) + days * 24 * 60 * 60;
}

void Car::showDueDate() {
    cout << "Due date: " << ctime(&returnDate);
}

void Customer::rentCar(Car* car) {
    // Customers are allowed to own lesser cars than employees
    if (customerRecord >= 0 && rentedCars.size() < 2 && car->isAvailable()) {
        rentedCars.push_back(car);
        car->rent();
        car->setReturnDate(7);
        cout << "Car rented successfully!" << endl;
        saveToFile();
    } else {
        cout << "Unable to rent the car. Please check your customer record or car availability." << endl;
    }
}

void Customer::returnCar(Car* car) {
    car->returnCar();
    for (auto it = rentedCars.begin(); it != rentedCars.end(); ++it) {
        if (*it == car) {
            rentedCars.erase(it);
            break;
        }
    }
    time_t currentTime = time(0);
    if (difftime(currentTime, car->getReturnDate()) > 0) {
        fineDue += difftime(currentTime, car->getReturnDate()) / (24 * 60 * 60) * 10;
    }
    saveToFile();
}

void Customer::browseRentedCars() {
    cout << "Rented Cars:" << endl;
    for (auto car : rentedCars) {
        cout << car->getModel() << endl;
    }
}

void Customer::clearDue() {
    fineDue = 0;
    saveToFile();
}

void Customer::saveToFile() {
    ofstream file(to_string(id) + "_customer.txt");
    file << id << "," << customerRecord << "," << fineDue << endl;
    for (auto car : rentedCars) {
        file << car->getModel() << endl;
    }
    file.close();
}

Customer* Customer::loadFromFile(int id) {
    ifstream file(to_string(id) + "_customer.txt");
    if (!file) {
        return nullptr;
    }
    int loadedId, loadedCustomerRecord;
    float loadedFineDue;
    file >> loadedId >> loadedCustomerRecord >> loadedFineDue;
    Customer* customer = new Customer(loadedId, loadedCustomerRecord);
    customer->fineDue = loadedFineDue;
    string line;
    getline(file, line); // Consume newline character
    while (getline(file, line)) {
        Car* car = new Car(line, "Good");
        customer->rentedCars.push_back(car);
    }
    file.close();
    return customer;
}

void Customer::addCustomer(int id, Customer* customer) {
    customerDatabase[id] = customer;
    customer->saveToFile();
}

void Customer::deleteCustomer(int id) {
    customerDatabase.erase(id);
    remove((to_string(id) + "_customer.txt").c_str());
}

Customer* Customer::searchCustomer(int id) {
    if (customerDatabase.find(id) != customerDatabase.end()) {
        return customerDatabase[id];
    }
    Customer* loadedCustomer = loadFromFile(id);
    if (loadedCustomer) {
        customerDatabase[id] = loadedCustomer;
    }
    return loadedCustomer;
}

void Employee::rentCar(Car* car) {
    // Employees
    if (employeeRecord >= 0 && rentedCars.size() < 3 && car->isAvailable()) {
        rentedCars.push_back(car);
        car->rent();
        car->setReturnDate(7); // Set return date to 7 days from now
        cout << "Car rented successfully!" << endl;
        saveToFile();
    } else {
        cout << "Unable to rent the car. Please check your employee record or car availability." << endl;
    }
}

void Employee::returnCar(Car* car) {
    car->returnCar();
    for (auto it = rentedCars.begin(); it != rentedCars.end(); ++it) {
        if (*it == car) {
            rentedCars.erase(it);
            break;
        }
    }
    time_t currentTime = time(0);
    if (difftime(currentTime, car->getReturnDate()) > 0) {
        fineDue += difftime(currentTime, car->getReturnDate()) / (24 * 60 * 60) * 10;
    }
    saveToFile();
}

void Employee::browseRentedCars() {
    cout << "Rented Cars:" << endl;
    for (auto car : rentedCars) {
        cout << "Model: " << car->getModel() << ", Condition: " << car->getCondition() << endl;
    }
}

void Employee::clearDue() {
    fineDue = 0;
    saveToFile();
}

void Employee::saveToFile() {
    ofstream file(to_string(id) + "_employee.txt");
    file << id << "," << employeeRecord << "," << fineDue << endl;
    for (auto car : rentedCars) {
        file << car->getModel() << endl;
    }
    file.close();
}

Employee* Employee::loadFromFile(int id) {
    ifstream file(to_string(id) + "_employee.txt");
    if (!file) {
        return nullptr;
    }
    int loadedId, loadedEmployeeRecord;
    float loadedFineDue;
    file >> loadedId >> loadedEmployeeRecord >> loadedFineDue;
    Employee* employee = new Employee(loadedId, loadedEmployeeRecord);
    employee->fineDue = loadedFineDue;
    string line;
    getline(file, line); // Consume newline character
    while (getline(file, line)) {
        // Assuming each line contains a car model
        Car* car = new Car(line, "Good"); // Set default condition for simplicity
        employee->rentedCars.push_back(car);
    }
    file.close();
    return employee;
}

void Employee::addEmployee(int id, Employee* employee) {
    employeeDatabase[id] = employee;
    employee->saveToFile();
}

void Employee::deleteEmployee(int id) {
    employeeDatabase.erase(id);
    remove((to_string(id) + "_employee.txt").c_str());
}

Employee* Employee::searchEmployee(int id) {
    if (employeeDatabase.find(id) != employeeDatabase.end()) {
        return employeeDatabase[id];
    }
    Employee* loadedEmployee = loadFromFile(id);
    if (loadedEmployee) {
        employeeDatabase[id] = loadedEmployee;
    }
    return loadedEmployee;
}


int main() {
    string masterkey="A";
    // Creating cars
    Car car1("Toyota", "Good");
    Car car2("Honda", "Average");
    Car car3("BMW", "Excellent");
    Car car4("Ford", "Average");
    Car car5("Mercedes", "Good");
    Car car6("Audi", "Excellent");
    Car car7("Chevrolet", "Good");
    Car car8("Lamborghini", "Excellent");
    Car car9("Ferrari", "Excellent");
    Car car10("Nissan", "Average");
    Car car11("Hyundai", "Good");
    Car car12("Kia", "Average");
    Car car13("Volvo", "Good");
    Car car14("Subaru", "Average");
    Car car15("Mazda", "Good");
    Car car16("Jeep", "Average");
    Car car17("Chrysler", "Good");
    Car car18("Dodge", "Average");
    Car car19("Buick", "Good");
    Car car20("Lincoln", "Average");
    Car car21("Cadillac", "Good");
    Car car22("Acura", "Average");
    Car car23("Infiniti", "Good");
    Car car24("Land Rover", "Average");
    Car car25("Porsche", "Good");
    vector<Car*> cars_set;

    // Creating and storing cars_set
    cars_set.push_back(new Car("Toyota", "Good"));
    cars_set.push_back(new Car("Honda", "Average"));
    cars_set.push_back(new Car("BMW", "Excellent"));
    cars_set.push_back(new Car("Ford", "Average"));
    cars_set.push_back(new Car("Mercedes", "Good"));
    cars_set.push_back(new Car("Audi", "Excellent"));
    cars_set.push_back(new Car("Chevrolet", "Good"));
    cars_set.push_back(new Car("Lamborghini", "Excellent"));
    cars_set.push_back(new Car("Ferrari", "Excellent"));
    cars_set.push_back(new Car("Nissan", "Average"));
    cars_set.push_back(new Car("Hyundai", "Good"));
    cars_set.push_back(new Car("Kia", "Average"));
    cars_set.push_back(new Car("Volvo", "Good"));
    cars_set.push_back(new Car("Subaru", "Average"));
    cars_set.push_back(new Car("Mazda", "Good"));
    cars_set.push_back(new Car("Jeep", "Average"));
    cars_set.push_back(new Car("Chrysler", "Good"));
    cars_set.push_back(new Car("Dodge", "Average"));
    cars_set.push_back(new Car("Buick", "Good"));
    cars_set.push_back(new Car("Lincoln", "Average"));
    cars_set.push_back(new Car("Cadillac", "Good"));
    cars_set.push_back(new Car("Acura", "Average"));
    cars_set.push_back(new Car("Infiniti", "Good"));
    cars_set.push_back(new Car("Land Rover", "Average"));
    cars_set.push_back(new Car("Porsche", "Good"));

    for(int i=1;i<=25;i++){
        Car::carDatabase[cars_set[i-1]->getModel()]=cars_set[i-1];
    }
    // Creating customers
    Customer customer1(1, 5);
    Customer customer2(2, 3);
    Customer customer3(3, 4);
    Customer customer4(4, 2);
    Customer customer5(5, 1);

    customer1.setPass("password1");
    customer2.setPass("password2");
    customer3.setPass("password3");
    customer4.setPass("password4");
    customer5.setPass("password5");
    // Adding customers to the database
    Customer::addCustomer(1, &customer1);
    Customer::addCustomer(2, &customer2);
    Customer::addCustomer(3, &customer3);
    Customer::addCustomer(4, &customer4);
    Customer::addCustomer(5, &customer5);


    // Creating employees
    Employee employee1(101, 5);
    Employee employee2(102, 3);
    Employee employee3(103, 4);
    Employee employee4(104, 2);
    Employee employee5(105, 1);

    // Adding employees to the database
    Employee::addEmployee(101, &employee1);
    Employee::addEmployee(102, &employee2);
    Employee::addEmployee(103, &employee3);
    Employee::addEmployee(104, &employee4);
    Employee::addEmployee(105, &employee5);
    //Password for employees
    employee1.setPass("password1");
    employee2.setPass("password2");
    employee3.setPass("password3");
    employee4.setPass("password4");
    employee5.setPass("password5");

    bool exitProgram = false;
    while (!exitProgram) {
        int cinput1;
        cout<<"---------------------------------------------------------------------\n";
        cout<<"\n\nWelcome to the Car Rental System!\n\n";
        cout<<"1. Press 1 to log in : \n";
        cout<<"2. Press 2 to exit\n\n\n";
        cout<<"---------------------------------------------------------------------\n";
        cin >> cinput1;
        if(cinput1==1){
            cout<<"---------------------------------------------------------------------\n";
            cout<<"Login as User or Admin ??\n\n";
            int cinput2;
            cout<<"1. Press 1 to log in as USER : \n";
            cout<<"2. Press 2 to log in as ADMIN : \n\n";
            cout<<"---------------------------------------------------------------------\n";
            cin>>cinput2;
            if(cinput2==1){
                cout<<"---------------------------------------------------------------------\n";
                cout << "Enter your user type:\n";
                cout << "1. Customer\n";
                cout << "2. Employee\n";
                cout<<"---------------------------------------------------------------------\n";
                int usertype;
                cin>>usertype;
                if(usertype==1){
                    int id;
                    cout<<"Dear Customer ,Enter your id\n ";
                    cin>>id;
                    Customer* customer = Customer::searchCustomer(id);
                    if(customer){
                        cout<<"Please enter your password\n";
                        string trypassword;
                        cin>>trypassword;
                        if(trypassword==customer->getPass()){;
                            int userbreak=1;
                            while(userbreak){
                                cout<<"---------------------------------------------------------------------\n";
                                cout<<"\nYou have been logged in as Customer\n";
                                cout<<"Press 1 to see all the cars\n";
                                cout<<"Press 2 to view cars issued by you\n";
                                cout<<"Press 3 to check if a car is available for issue or not\n";
                                cout<<"Press 4 to view the fine\n";
                                cout<<"Press 5 to issue a car\n";
                                cout<<"Press 6 to return a car\n";
                                cout<<"Press 7 to know your fine\n";
                                cout<<"Press 8 to logout\n";
                                cout<<"---------------------------------------------------------------------\n";

                                char c;
                                cin>>c;

                                switch (c) {
                                    case '1': {
                                        // Code to see all the cars
                                        cout << "List of all cars:\n";
                                        for (const auto& car : cars_set) {
                                            cout << "Model: " << car->getModel() << ", Condition: " << car->getCondition();
                                            if (car->isAvailable()) {
                                                cout << ", Available: Yes\n";
                                            } else {
                                                cout << ", Available: No, Return Date: " << car->getReturnDate() << endl;
                                            }
                                        }
                                        break;
                                    }
                                    case '2': {
                                        // Code to view cars issued by the customer
                                        cout << "Cars issued by you:\n";
                                        for (Car* car : customer->getRentedCars()) {
                                            cout << "Model: " << car->getModel() << ", Condition: " << car->getCondition() << endl;
                                        }
                                        break;
                                    }

                                    case '3': {
                                        // Code to check if a car is available for issue or not
                                        string model;
                                        cout << "Enter the model of the car you want to check availability for: ";
                                        cin >> model;

                                        bool found = false;
                                        for (const auto& car : cars_set) {
                                            if (car->getModel() == model && car->isAvailable()) {
                                                found = true;
                                                cout << "Car is available for issue.\n";
                                                break;
                                            }
                                        }

                                        if (!found) {
                                            cout << "Car is not available for issue or does not exist.\n";
                                        }
                                        break;
                                    }

                                    case '4': {
                                        // Code to view the fine
                                        // int customerId;
                                        // cout << "Enter your customer ID: ";
                                        // cin >> customerId;
                                        // // Search for the customer
                                        // Customer* customer = Customer::searchCustomer(customerId);
                                        if (customer) {
                                            cout << "Your fine is: $" << customer->getFineDue() << endl;
                                        } else {
                                            cout << "Customer not found.\n";
                                        }
                                        break;
                                    }

                                    case '5': {
                                        string chosenModel;
                                        cout << "Enter the model of the car you want to rent: ";
                                        cin >> chosenModel;

                                        // Find the chosen car in the available cars
                                        bool found = false;
                                        for (auto& car : cars_set) {
                                            if (car->getModel() == chosenModel && car->isAvailable()) {
                                                // Rent the car to the customer
                                                customer->rentCar(car);
                                                // Update the car's availability
                                                found = true;
                                                cout << "Car rented successfully." << endl;
                                                break;
                                            }
                                        }

                                        if (!found) {
                                            cout << "Sorry, the chosen car is not available for rent." << endl;
                                        }
                                        break;
                                    }
                                    case '6': {
                                        // Display list of cars rented by the customer
                                        cout << "List of cars rented by you:" << endl;
                                        int index = 1;
                                        for (const auto& car : customer->getRentedCars()) {
                                            cout << index << ". Model: " << car->getModel() << ", Condition: " << car->getCondition() << endl;
                                            index++;
                                        }

                                        // Ask the customer to choose the car they want to return
                                        int choice;
                                        cout << "Enter the number corresponding to the car you want to return (or 0 to cancel): ";
                                        cin >> choice;

                                        if (choice >= 1 && choice <= customer->getRentedCars().size()) {
                                            // Get the chosen car
                                            Car* chosenCar = customer->getRentedCars()[choice - 1];
                                            
                                            // Return the car
                                            customer->returnCar(chosenCar);
                                            
                                            // Mark the car as available
                                            
                                            cout << "Car returned successfully." << endl;
                                        } 
                                        else if (choice != 0) {
                                            cout << "Invalid choice." << endl;
                                        }
                                        break;
                                    }

                                    case '7': {
                                        // Display the fine due
                                        cout << "Your current fine due is: $" << customer->getFineDue() << endl;
                                        break;
                                    }

                                    case '8': {
                                        cout<< "Logging Out\n";
                                        cout<<"Thanks Customer\n";
                                        userbreak=false;
                                        break;
                                    }
                                    default:
                                        cout << "Invalid choice. Please try again.\n";
                                        break;
                                }
                            }// while wala
                        }
                        else{
                            cout<<"Wrond PASSWORD\n";
                            continue;
                        }
                    }
                    else{
                        cout<<"User ID doesn't exist\n";
                        continue;
                    }

                }
                else if(usertype==2){
                    //BHARO BC
                    int id;
                    cout<<"Dear employee ,Enter your id\n";
                    cin>>id;
                    Employee* employee = Employee::searchEmployee(id);
                    if(employee){
                        cout<<"Please enter your password\n";
                        string trypassword;
                        cin>>trypassword;
                        if(trypassword==employee->getPass()){;
                            cout<<"---------------------------------------------------------------------\n";
                            cout<<"CORRECT PASSWORD\n";
                            cout<<"---------------------------------------------------------------------\n";
                            int userbreak=1;
                            while(userbreak){
                                cout<<"---------------------------------------------------------------------\n";
                                cout<<"\nYou have been logged in as employee\n";
                                cout<<"Press 1 to see all the cars\n";
                                cout<<"Press 2 to view cars issued by you\n";
                                cout<<"Press 3 to check if a car is available for issue or not\n";
                                cout<<"Press 4 to view the fine\n";
                                cout<<"Press 5 to issue a car\n";
                                cout<<"Press 6 to return a car\n";
                                cout<<"Press 7 to know your fine\n";
                                cout<<"Press 8 to logout\n";
                                cout<<"---------------------------------------------------------------------\n";

                                char c;
                                cin>>c;

                                switch (c) {
                                    case '1': {
                                        // Code to see all the cars
                                        cout << "List of all cars:\n";
                                        for (const auto& car : cars_set) {
                                            cout << "Model: " << car->getModel() << ", Condition: " << car->getCondition();
                                            if (car->isAvailable()) {
                                                cout << ", Available: Yes\n";
                                            } else {
                                                cout << ", Available: No, Return Date: " << car->getReturnDate() << endl;
                                            }
                                        }
                                        break;
                                    }
                                    case '2': {
                                        // Code to view cars issued by the employee
                                        cout << "Cars issued by you:\n";
                                        for (Car* car : employee->getRentedCars()) {
                                            cout << "Model: " << car->getModel() << ", Condition: " << car->getCondition() << endl;
                                        }
                                        break;
                                    }

                                    case '3': {
                                        // Code to check if a car is available for issue or not
                                        string model;
                                        cout << "Enter the model of the car you want to check availability for: ";
                                        cin >> model;

                                        bool found = false;
                                        for (const auto& car : cars_set) {
                                            if (car->getModel() == model && car->isAvailable()) {
                                                found = true;
                                                cout << "Car is available for issue.\n";
                                                break;
                                            }
                                        }

                                        if (!found) {
                                            cout << "Car is not available for issue or does not exist.\n";
                                        }
                                        break;
                                    }

                                    case '4': {
                                        // Code to view the fine
                                        // int employeeId;
                                        // cout << "Enter your employee ID: ";
                                        // cin >> employeeId;
                                        // // Search for the employee
                                        // Employee* employee = Employee::searchEmployee(employeeId);
                                        if (employee) {
                                            cout << "Your fine is: $" << employee->getFineDue() << endl;
                                        } else {
                                            cout << "employee not found.\n";
                                        }
                                        break;
                                    }

                                    case '5': {
                                        string chosenModel;
                                        cout << "Enter the model of the car you want to rent: ";
                                        cin >> chosenModel;

                                        // Find the chosen car in the available cars
                                        bool found = false;
                                        for (auto& car : cars_set) {
                                            if (car->getModel() == chosenModel && car->isAvailable()) {
                                                // Rent the car to the employee
                                                employee->rentCar(car);
                                                // Update the car's availability
                                                found = true;
                                                cout << "Car rented successfully." << endl;
                                                break;
                                            }
                                        }

                                        if (!found) {
                                            cout << "Sorry, the chosen car is not available for rent." << endl;
                                        }
                                        break;
                                    }
                                    case '6': {
                                        // Display list of cars rented by the employee
                                        cout << "List of cars rented by you:" << endl;
                                        int index = 1;
                                        for (const auto& car : employee->getRentedCars()) {
                                            cout << index << ". Model: " << car->getModel() << ", Condition: " << car->getCondition() << endl;
                                            index++;
                                        }

                                        // Ask the employee to choose the car they want to return
                                        int choice;
                                        cout << "Enter the number corresponding to the car you want to return (or 0 to cancel): ";
                                        cin >> choice;

                                        if (choice >= 1 && choice <= employee->getRentedCars().size()) {
                                            // Get the chosen car
                                            Car* chosenCar = employee->getRentedCars()[choice - 1];
                                            
                                            // Return the car
                                            employee->returnCar(chosenCar);
                                            
                                            // Mark the car as available
                                            
                                            cout << "Car returned successfully." << endl;
                                        } 
                                        else if (choice != 0) {
                                            cout << "Invalid choice." << endl;
                                        }
                                        break;
                                    }

                                    case '7': {
                                        // Display the fine due
                                        cout << "Your current fine due is: $" << employee->getFineDue() << endl;
                                        break;
                                    }

                                    case '8': {
                                        cout<< "Logging Out\n";
                                        cout<<"Thanks employee\n";
                                        userbreak=false;
                                        break;
                                    }
                                    default:
                                        cout << "Invalid choice. Please try again.\n";
                                        break;
                                }
                            }// while wala
                        }
                        else{
                            cout<<"Wrond PASSWORD\n";
                            continue;
                        }
                    }
                    else{
                        cout<<"User ID doesn't exist\n";
                        continue;
                    }

                }

                else{
                    cout<<"---------------------------------------------------------------------\n";
                    cout<< "\n\n Wrong Input ; Directing to Home Page\n\n" <<endl;
                    cout<<"---------------------------------------------------------------------\n";
                    continue;
                }
            }
            else if(cinput2==2){
                string master_attempt;
                cout<<"---------------------------------------------------------------------\n";
                cout<<"Enter admin password\n";
                cout<<"---------------------------------------------------------------------\n";
                cin>> master_attempt;
                if(master_attempt==masterkey){
                    cout<<"---------------------------------------------------------------------\n";
                    cout<<" WELCOME ADMIN ;)\n";
                    cout<<"---------------------------------------------------------------------\n\n\n\n\n";
                    // MAIN MENU
                    int adminbreak=1;
                    while (adminbreak) {
                        cout << "*********************************************************************\n";
                        cout << "\nWelcome! You are logged in as admin.\n\n";
                        cout << "Press 1 to add a user\n";
                        cout << "Press 2 to update a user\n";
                        cout << "Press 3 to delete a user\n";
                        cout << "Press 4 to add a car\n";
                        cout << "Press 5 to update a car\n";
                        cout << "Press 6 to delete a car\n";
                        cout << "Press 7 to see all cars issued to a particular user\n";
                        cout << "Press 8 to see which car is issued to which user\n";
                        cout << "Press 9 to view all users\n";
                        cout << "Press 0 to view all cars\n";
                        cout << "Press d to show due date of a car\n";
                        cout << "Press l to logout\n";
                        cout << "*********************************************************************\n";

                        char c;
                        cin >> c;
                        switch (c) {
                            case '1': {
                                int user_type;
                                cout << "Enter your user type:\n";
                                cout << "1. Customer\n";
                                cout << "2. Employee\n";
                                cin >> user_type;
                                switch (user_type) {
                                    case 1: {
                                        int id, customerRecord;
                                        cout << "Enter customer ID: ";
                                        cin >> id;
                                        cout << "Enter customer record: ";
                                        cin >> customerRecord;

                                        // Check if the customer already exists
                                        if (Customer::searchCustomer(id) != nullptr) {
                                            cout << "Customer with ID " << id << " already exists.\n";
                                        } 
                                        else {
                                            // Create a new customer
                                            Customer* newCustomer = new Customer(id, customerRecord);
                                            Customer::addCustomer(id, newCustomer);
                                            cout << "Customer added successfully.\n";

                                            cout<<"Do you want to set password for customer ?\n";
                                            cout<<"1 for Yes , 2 for No\n";
                                            int a1;
                                            cin>>a1;
                                            if(a1==1){
                                                cout << "Enter password for the customer: ";
                                                string password;
                                                cin >> password;
                                                newCustomer->setPass(password);
                                                cout << "Password set successfully.\n";
                                                break;
                                            }
                                            else if(a1==2){
                                                break;
                                            }
                                            else{
                                                cout<<"Wrong Input\n";
                                            }
                                        }
                                        break;
                                    }
                                    case 2: {
                                        int id, EmployeeRecord;
                                        cout << "Enter Employee ID: ";
                                        cin >> id;
                                        cout << "Enter Employee record: ";
                                        cin >> EmployeeRecord;

                                        // Check if the Employee already exists
                                        if (Employee::searchEmployee(id) != nullptr) {
                                            cout << "Employee with ID " << id << " already exists.\n";
                                        } 
                                        else {
                                            // Create a new Employee
                                            Employee* newEmployee = new Employee(id, EmployeeRecord);
                                            Employee::addEmployee(id, newEmployee);
                                            cout << "Employee added successfully.\n";

                                            cout<<"Do you want to set password for employee ?\n";
                                            cout<<"1 for Yes , 2 for No\n";
                                            int a1;
                                            cin>>a1;
                                            if(a1==1){
                                                cout << "Enter password for the employee: ";
                                                string password;
                                                cin >> password;
                                                newEmployee->setPass(password);
                                                cout << "Password set successfully.\n";
                                                break;
                                            }
                                            else if(a1==2){
                                                break;
                                            }
                                            else{
                                                cout<<"Wrong Input\n";
                                            }
                                        }
                                        break;
                                    }
                                    default:
                                        cout << "Invalid user type.\n";
                                        break;
                                }
                                break;
                            }

                            case '2': {
                                int user_type;
                                cout << "Enter your user type:\n";
                                cout << "1. Customer\n";
                                cout << "2. Employee\n";
                                cin >> user_type;

                                

                                // Search for the user
                                switch (user_type) {
                                    case 1: { 
                                        int id;
                                        cout << "Enter the ID of the user you want to update: ";
                                        cin >> id;

                                        Customer* userToUpdate = Customer::searchCustomer(id);

                                        if (userToUpdate != nullptr) {
                                            cout << "User found. Enter new details:\n";
                                            int newCustomerRecord;
                                            string new_name;
                                            int change_break=1;
                                            while(change_break){
                                                cout << "*********************************************************************\n";
                                                cout << "\nWhat Do you want to change/update ?.\n\n";
                                                cout << "1. Change Name\n";
                                                cout << "2. Change Customer Record / Rating\n";
                                                cout << "3. Change Customer Password\n";
                                                cout << "4. Nothing\n";
                                                cout << "*********************************************************************\n";
                                                char c1;
                                                cin >> c1;
                                                switch(c1){
                                                    case '1': {
                                                        cout << "Enter new name: ";
                                                        cin >> new_name;
                                                        userToUpdate->setName(new_name);
                                                        break;
                                                    }
                                                    case '2': {
                                                        cout << "Enter new customer record: ";
                                                        cin >> newCustomerRecord;
                                                        userToUpdate->setCustomerRecord(newCustomerRecord);
                                                        break;
                                                    }
                                                    case '3': {
                                                        cout << "Enter new password: ";
                                                        string newPassword;
                                                        cin >> newPassword;
                                                        userToUpdate->setPass(newPassword);
                                                        break;
                                                    }
                                                    case '4': {
                                                        change_break = false;
                                                        break;
                                                    }
                                                    default: {
                                                        cout << "Invalid choice. Please try again.\n";
                                                        break;
                                                    }
                                                }
                                            }

                                            cout << "User details updated successfully.\n";
                                            userToUpdate->saveToFile();
                                        } 
                                        else {
                                            cout << "User with ID " << id << " not found.\n";
                                        }
                                        break;
                                    }
                                    case 2:{
                                        int id;
                                        cout << "Enter the ID of the user you want to update: ";
                                        cin >> id;

                                        Employee* userToUpdate = Employee::searchEmployee(id);

                                        if (userToUpdate != nullptr) {
                                            cout << "User found. Enter new details:\n";
                                            int newEmployeeRecord;
                                            string new_name;
                                            int change_break=1;
                                            while(change_break){
                                                cout << "*********************************************************************\n";
                                                cout << "\nWhat Do you want to change/update ?.\n\n";
                                                cout << "1. Change Name\n";
                                                cout << "2. Change Employee Record / Rating\n";
                                                cout << "3. Change Employee Password\n";
                                                cout << "4. Nothing\n";
                                                cout << "*********************************************************************\n";
                                                char c1;
                                                cin >> c1;
                                                switch(c1){
                                                    case '1': {
                                                        cout << "Enter new name: ";
                                                        cin >> new_name;
                                                        userToUpdate->setName(new_name);
                                                        break;
                                                    }
                                                    case '2': {
                                                        cout << "Enter new Employee record: ";
                                                        cin >> newEmployeeRecord;
                                                        userToUpdate->setEmployeeRecord(newEmployeeRecord);
                                                        break;
                                                    }
                                                    case '3': {
                                                        cout << "Enter new password: ";
                                                        string newPassword;
                                                        cin >> newPassword;
                                                        userToUpdate->setPass(newPassword);
                                                        break;
                                                    }
                                                    case '4': {
                                                        change_break = false;
                                                        break;
                                                    }
                                                    default: {
                                                        cout << "Invalid choice. Please try again.\n";
                                                        break;
                                                    }
                                                }
                                            }

                                            cout << "User details updated successfully.\n";
                                            userToUpdate->saveToFile();
                                        } 
                                        else {
                                            cout << "User with ID " << id << " not found.\n";
                                        }
                                        break;
                                    }
                                    default:
                                        cout << "Invalid user type.\n";
                                        break;
                                }
                                break;
                            }

                            case '3': {

                                int user_type;
                                cout << "Enter your delete user type:\n";
                                cout << "1. Customer\n";
                                cout << "2. Employee\n";
                                cin >> user_type;

                                // Code to delete a user
                                int deleteId;
                                cout << "Enter the ID of the user you want to delete: ";
                                cin >> deleteId;
                                switch (user_type) {
                                    case 1: { 
                                        Customer* customerToDelete = Customer::searchCustomer(deleteId);
                                            if (customerToDelete) {
                                                // Remove the customer from the database
                                                Customer::deleteCustomer(deleteId);
                                                cout << "Customer with ID " << deleteId << " deleted successfully.\n";
                                            } 
                                            else {
                                                cout << "Customer not found.\n";
                                            }
                                            break;
                                            }
                                    case 2: {
                                        Employee* employeeToDelete = Employee::searchEmployee(deleteId);
                                            if (employeeToDelete) {
                                                // Remove the Employee from the database
                                                Employee::deleteEmployee(deleteId);
                                                cout << "Employee with ID " << deleteId << " deleted successfully.\n";
                                            } 
                                            else {
                                                cout << "Employee not found.\n";
                                            }
                                            break;
                                            }
                                    default:
                                        cout << "Invalid user type.\n";
                                        break;
                                    }
                                break;
                            }

                            case '4': {
                                // Code to add a car
                                string model, condition;
                                
                                // Prompt the user to enter the details of the car
                                cout << "Enter the model of the car: ";
                                cin >> model;
                                cout << "Enter the condition of the car: ";
                                cin >> condition;

                                // Create a new Car object
                                Car* newCar = new Car(model, condition);

                                // Add the new car to the vector or database of cars
                                // For example, if you have a vector of cars:
                                cars_set.push_back(newCar);

                                cout << "Car added successfully.\n";
                                break;
                            }

                            case '5': {
                                // Code to update a car
                                string model;
                                bool found = false;

                                // Prompt the user to enter the model of the car to update
                                cout << "Enter the model of the car to update: ";
                                cin >> model;

                                // Search for the car in the vector or database of cars
                                for (Car* car : cars_set) {
                                    if (car->getModel() == model) {
                                        // Car found, allow the user to update its details
                                        string newCondition;

                                        // Prompt the user to enter the new condition of the car
                                        cout << "Enter the new condition of the car: ";
                                        cin >> newCondition;

                                        // Update the condition of the car
                                        car->setCondition(newCondition);

                                        cout << "Car updated successfully.\n";
                                        found = true;
                                        break;
                                    }
                                }

                                if (!found) {
                                    cout << "Car not found.\n";
                                }
                                break;
                            }

                            case '6': {
                                // Code to delete a car
                                string model;
                                bool found = false;

                                // Prompt the user to enter the model of the car to delete
                                cout << "Enter the model of the car to delete: ";
                                cin >> model;

                                // Iterate through the vector or database of cars
                                for (auto it = cars_set.begin(); it != cars_set.end(); ++it) {
                                    if ((*it)->getModel() == model) {
                                        // Car found, erase it from the list
                                        cars_set.erase(it);
                                        cout << "Car deleted successfully.\n";
                                        found = true;
                                        break;
                                    }
                                }

                                if (!found) {
                                    cout << "Car not found.\n";
                                }
                                break;
                            }
                            case '7': {
                                int user_type;
                                cout << "Enter your user type:\n";
                                cout << "1. Customer\n";
                                cout << "2. Employee\n";
                                cin >> user_type;

                                int user_id;
                                cout << "Enter your user ID: ";
                                cin >> user_id;

                                switch (user_type) {
                                    case 1: { // Customer
                                        Customer* customer = Customer::searchCustomer(user_id);
                                        if (customer) {
                                            customer->browseRentedCars();
                                        } else {
                                            cout << "Customer not found.\n";
                                        }
                                        break;
                                    }
                                    case 2: { // Employee
                                        Employee* employee = Employee::searchEmployee(user_id);
                                        if (employee) {
                                            employee->browseRentedCars();
                                        } else {
                                            cout << "Employee not found.\n";
                                        }
                                        break;
                                    }
                                    default:
                                        cout << "Invalid user type.\n";
                                }
                                break;
                            }
                            case '8': {
                                cout << "Cars issued to users:\n";
                                for (const auto& pair : Customer::customerDatabase) {
                                    Customer* user = pair.second;
                                    cout << "User ID: " << user->getId() << endl; // Assuming id is public
                                    cout << "Cars rented:\n";
                                    for (auto car : user->getRentedCars()) {
                                        // check karLENA KI MODEL PRINT HO RHA HAI YA NHI 
                                        cout << "Model: " << car->getModel() << endl;
                                    }
                                    cout << endl;
                                }
                                for (const auto& pair : Employee::employeeDatabase) {
                                    Employee* user = pair.second;
                                    cout << "User ID: " << user->getId() << endl; // Assuming id is public
                                    cout << "Cars rented:\n";
                                    for (auto car : user->getRentedCars()) {
                                        // check karLENA KI MODEL PRINT HO RHA HAI YA NHI 
                                        cout << "Model: " << car->getModel() << endl;
                                    }
                                    cout << endl;
                                }
                                break;
                            }


                            case '9': {
                                // Code to view all users
                                cout << "List of all users:\n";
                                for (const auto& pair : Customer::customerDatabase) {
                                    cout << "User ID: " << pair.first << ", Name: " << pair.second->getName() << endl;
                                    // Assuming you have a getName() function to retrieve the name of the customer
                                }
                                for (const auto& pair : Employee::employeeDatabase) {
                                    cout << "User ID: " << pair.first << ", Name: " << pair.second->getName() << endl;
                                    // Assuming you have a getName() function to retrieve the name of the employee
                                }

                                break;
                            }

                            case '0': {
                                // Code to view all cars
                                cout << "List of all cars:\n";
                                for (const auto& car : cars_set) {
                                    cout << "Model: " << car->getModel() << ", Condition: " << car->getCondition();
                                    if (car->isAvailable()) {
                                        cout << ", Available: Yes\n";
                                    } else {
                                        cout << ", Available: No, Return Date: " << car->getReturnDate() << endl;
                                    }
                                }
                                break;
                            }

                            case 'd': {
                                // Code to show due date of a car
                                string model;
                                cout << "Enter the model of the car: ";
                                cin >> model;

                                bool found = false;
                                for (const auto& car_pair : Car::carDatabase) {
                                    Car* curr_car=car_pair.second;
                                    if (curr_car->getModel() == model) {
                                        found = true;
                                        cout << "Due date for car " << model << ": " << curr_car->getReturnDate() << endl;
                                        break;
                                    }
                                }

                                if (!found) {
                                    cout << "You have not rented a car with that model.\n";
                                }
                                break;
                            }

                            case 'l': {
                                adminbreak = false;
                                // Code to logout
                                break;
                            }
                            default:
                                cout << "Invalid choice. Please try again.\n";
                                break;
                        }
                    }// while wala code
                }// if correct password

                else{
                    cout<<"---------------------------------------------------------------------\n";
                    cout<< "\n\n Wrong Password ; Directing to Home Page\n\n" <<endl;
                    cout<<"---------------------------------------------------------------------\n";
                    continue;
                }
            }
            else{
                cout<<"---------------------------------------------------------------------\n";
                cout<< "\n\n Wrong Input ; Directing to Home Page\n\n" <<endl;
                cout<<"---------------------------------------------------------------------\n";
                continue;
            }
        }
        else if(cinput1==2){
            cout<<"---------------------------------------------------------------------\n";
            exitProgram = true;
            cout<< "\n\nProgram Exited" <<endl;
            cout<< "Thanks :)\n\n" <<endl;
            cout<<"---------------------------------------------------------------------\n";
            break;
        }
        else{
            cout<<"---------------------------------------------------------------------\n";
            cout<< "\n\n Wrong Input \n\n" <<endl;
            cout<<"---------------------------------------------------------------------\n";
            continue;
        }
        // cout << "Menu:\n";
        // //cout << "1. User Login\n";
        // cout << "2. Rent a car\n";
        // cout << "3. Return a car\n";
        // cout << "4. Browse rented cars\n";
        // cout << "5. Clear dues\n";
        // cout << "6. Exit\n";
        // cout << "Enter your choice: ";

        // int choice;
        // cin >> choice;

        // switch (choice) {

            // case 1: {
            //     cout << "Enter the character for type of user\n";
            //     cout << "1 for Customer\n";
            //     cout << "2 for Employee\n";
            //     cout << "3 for Manager\n";
            //     int user_c;
            //     cin >> user_c;

            //     switch (user_c) {
            //         case 1: {
            //             int curr_user_id;
            //             int passcode;
            //             // Code to take customer's user ID and password
            //             cout << "Enter Customer ID: ";
            //             cin >> curr_user_id;
            //             cout << "Enter Password: ";
            //             cin >> passcode;
            //             // Additional code for customer login goes here
            //             break;
            //         }
            //         case 2: {
            //             string emp_id;
            //             string password;
            //             // Code to take employee's user ID and password
            //             cout << "Enter Employee ID: ";
            //             cin >> emp_id;
            //             cout << "Enter Password: ";
            //             cin >> password;
            //             // Additional code for employee login goes here
            //             break;
            //         }
            //         case 3: {
            //             string manager_id;
            //             string pass;
            //             // Code to take manager's user ID and password
            //             cout << "Enter Manager ID: ";
            //             cin >> manager_id;
            //             cout << "Enter Password: ";
            //             cin >> pass;
            //             // Additional code for manager login goes here
            //             break;
            //         }
            //         default:
            //             cout << "Invalid choice. Please try again.\n";
            //     }

            //     break;
            // }

        //     case 2: {
        //         int user_type;
        //         cout << "Enter your user type:\n";
        //         cout << "1. Customer\n";
        //         cout << "2. Employee\n";
        //         cin >> user_type;

        //         int user_id;
        //         cout << "Enter your user ID: ";
        //         cin >> user_id;

        //         switch (user_type) {

        //             case 1: { // Customer
        //                 Customer* customer = Customer::searchCustomer(user_id);
        //                 if (customer) {
        //                     // Assuming the user will enter the model of the car they want to rent
        //                     string model;
        //                     cout << "Enter the model of the car you want to rent: ";
        //                     cin >> model;

        //                     // Search for the car in available cars
        //                     bool found = false;
        //                     for (auto y: cars_set) { 
        //                         if (y->getModel() == model && y->isAvailable()) {
        //                             // Rent the car and update its availability
        //                             customer->rentCar(y);
        //                             found = true;
        //                             cout << "Car rented successfully.\n";
        //                             break;
        //                         }
        //                     }
        //                     if (!found) {
        //                         cout << "Car not found or unavailable for rent.\n";
        //                     }
        //                 } 
        //                 else {
        //                     cout << "Customer not found.\n";
        //                 }
        //                 break;
        //             }
        //             case 2: { // Employee
        //                 Employee* employee = Employee::searchEmployee(user_id);
        //                 if (employee) {
        //                     // Assuming the user will enter the model of the car they want to rent
        //                     string model;
        //                     cout << "Enter the model of the car you want to rent: ";
        //                     cin >> model;

        //                     // Search for the car in available cars
        //                     bool found = false;
        //                     for (auto y: cars_set) { 
        //                         if (y->getModel() == model && y->isAvailable()) {
        //                             // Rent the car and update its availability
        //                             employee->rentCar(y);
        //                             found = true;
        //                             cout << "Car rented successfully.\n";
        //                             break;
        //                         }
        //                     }
        //                     if (!found) {
        //                         cout << "Car not found or unavailable for rent.\n";
        //                     }
        //                 } else {
        //                     cout << "Employee not found.\n";
        //                 }
        //                 break;
        //             }

        //             default:
        //                 cout << "Invalid user type.\n";

        //         }
        //         break;
        //     }

        //     case 3: {
        //         int user_type;
        //         cout << "Enter your user type:\n";
        //         cout << "1. Customer\n";
        //         cout << "2. Employee\n";
        //         cin >> user_type;

        //         int user_id;
        //         cout << "Enter your user ID: ";
        //         cin >> user_id;

        //         switch (user_type) {
        //             case 1: { // Customer
        //                 Customer* customer = Customer::searchCustomer(user_id);
        //                 if (customer) {
        //                     // Assuming the user will enter the model of the car they are returning
        //                     string model;
        //                     cout << "Enter the model of the car you are returning: ";
        //                     cin >> model;

        //                     // Search for the car in the customer's rented cars
        //                     bool found = false;
        //                     for (Car* car : customer->getRentedCars()) {
        //                         if (car->getModel() == model) {
        //                             // Return the car and update fines
        //                             customer->returnCar(car);
        //                             found = true;
        //                             cout << "Car returned successfully.\n";
        //                             break;
        //                         }
        //                     }
        //                     if (!found) {
        //                         cout << "You have not rented a car with that model.\n";
        //                     }
        //                 } else {
        //                     cout << "Customer not found.\n";
        //                 }
        //                 break;
        //             }
        //             case 2: { // Employee
        //                 Employee* employee = Employee::searchEmployee(user_id);
        //                 if (employee) {
        //                     // Assuming the user will enter the model of the car they are returning
        //                     string model;
        //                     cout << "Enter the model of the car you are returning: ";
        //                     cin >> model;

        //                     // Search for the car in the employee's rented cars
        //                     bool found = false;
        //                     for (Car* car : employee->getRentedCars()) {
        //                         if (car->getModel() == model) {
        //                             // Return the car and update fines
        //                             employee->returnCar(car);
        //                             found = true;
        //                             cout << "Car returned successfully.\n";
        //                             break;
        //                         }
        //                     }
        //                     if (!found) {
        //                         cout << "You have not rented a car with that model.\n";
        //                     }
        //                 } else {
        //                     cout << "Employee not found.\n";
        //                 }
        //                 break;
        //             }
        //             default:
        //                 cout << "Invalid user type.\n";
        //         }
        //         break;
        //     }
        //     case 4: {
        //         int user_type;
        //         cout << "Enter your user type:\n";
        //         cout << "1. Customer\n";
        //         cout << "2. Employee\n";
        //         cin >> user_type;

        //         int user_id;
        //         cout << "Enter your user ID: ";
        //         cin >> user_id;

        //         switch (user_type) {
        //             case 1: { // Customer
        //                 Customer* customer = Customer::searchCustomer(user_id);
        //                 if (customer) {
        //                     customer->browseRentedCars();
        //                 } else {
        //                     cout << "Customer not found.\n";
        //                 }
        //                 break;
        //             }
        //             case 2: { // Employee
        //                 Employee* employee = Employee::searchEmployee(user_id);
        //                 if (employee) {
        //                     employee->browseRentedCars();
        //                 } else {
        //                     cout << "Employee not found.\n";
        //                 }
        //                 break;
        //             }
        //             default:
        //                 cout << "Invalid user type.\n";
        //         }
        //         break;
        //     }
        //     case 5: {
        //         int user_type;
        //         cout << "Enter your user type:\n";
        //         cout << "1. Customer\n";
        //         cout << "2. Employee\n";
        //         cin >> user_type;

        //         int user_id;
        //         cout << "Enter your user ID: ";
        //         cin >> user_id;

        //         switch (user_type) {
        //             case 1: { // Customer
        //                 Customer* customer = Customer::searchCustomer(user_id);
        //                 if (customer) {
        //                     customer->clearDue();
        //                     cout << "Dues cleared successfully for Customer ID: " << user_id << endl;
        //                 } else {
        //                     cout << "Customer not found.\n";
        //                 }
        //                 break;
        //             }
        //             case 2: { // Employee
        //                 Employee* employee = Employee::searchEmployee(user_id);
        //                 if (employee) {
        //                     employee->clearDue();
        //                     cout << "Dues cleared successfully for Employee ID: " << user_id << endl;
        //                 } else {
        //                     cout << "Employee not found.\n";
        //                 }
        //                 break;
        //             }
        //             default:
        //                 cout << "Invalid user type.\n";
        //         }
        //         break;
        //     }
        //     case 6: {
        //         exitProgram = true;
        //         cout<< "Program Exited" <<endl;
        //         cout<< "Thanks :)" <<endl;
        //         break;
        //     }
        //     default:
        //         cout << "Invalid choice. Please try again.\n";
        // }
    }
    return 0;
}
