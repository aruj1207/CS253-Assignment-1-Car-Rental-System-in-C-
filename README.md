READ ME

This program code.cpp is a car rental management system implemented in C++. It provides functionality for managing cars, customers, and employees within a rental service.

IMPORTANT NOTES:
The password of the manager/admin is A ( Just Capital A ).
The password of the all the initial employees and customer are like password#n where n is the user ID.
For example , Password for Customer with userid=1 is "password1".
similarly password for employee with userid=102 is "password102".


1. Classes:
   - Car: Represents a car available for rental. It includes attributes such as model, condition, availability, and return date. The class provides methods for setting conditions, renting, returning, and managing return dates.

   - Customer: Represents a customer who can rent cars. It includes attributes such as ID, rented cars, fine due, customer record, name, and password. This class provides methods for renting, returning, browsing rented cars, managing dues, saving to/loading from files, and more.

   - Employee: Represents an employee who can rent cars. It has similar attributes and functionalities as the Customer class but with a higher limit on the number of cars that can be rented.
     
   - Manager: Derived from the Employee class, this class adds additional functionalities for managing customers, employees, and cars.

2. Functionality:
   - The program allows the creation, updating, and deletion of customers, employees, and cars.
   - Customers and employees can rent cars, and the system manages due dates, fines, and bills accordingly.
   - Managers have additional capabilities to manage customers, employees, and cars.

3. Usage:
   - The main() function initializes car, customer, and employee objects, adds them to respective databases, and demonstrates some functionalities.
   - Customers and employees are added to their respective databases using the addCustomer() and addEmployee() methods of the corresponding classes.
   - Cars are added to the carDatabase using the addCar() method of the Manager class.
   - Renting and returning cars are demonstrated using the rentCar() and returnCar() methods of the Customer and Employee classes.
   - The program also provides functionalities to browse rented cars, view all cars, and view rented cars, which are demonstrated in the main() function.

4. Additional Notes:
   - Error handling and user input validation are minimal in this code and can be further enhanced for robustness.
   - Passwords are stored in plain text, which is not secure. In practice, passwords should be encrypted.
   - The program utilizes file I/O for saving and loading data. Each customer and employee is associated with a text file for data storage.
   - The program demonstrates basic object-oriented principles such as inheritance, encapsulation, and polymorphism.

5. Requirements:
   - This program requires a C++ compiler that supports C++11 features.
   - The program uses standard C++ libraries such as iostream, fstream, sstream, vector, string, unordered_map, and ctime.

6. Execution:
   - Compile the source code with a C++ compiler and execute the compiled to run the program.

