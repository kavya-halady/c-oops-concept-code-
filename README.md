# c-oops-concept-code-
# C++ Object-Oriented Programming - Complete Demonstration

## Overview
This project demonstrates all core Object-Oriented Programming (OOP) concepts in C++ through a practical example of a **Banking System**.

## OOP Concepts Covered

### 1. **Class and Object**
- **Class**: A blueprint for creating objects (e.g., `Account`, `SavingsAccount`)
- **Object**: An instance of a class (e.g., `savings1`, `checking1`)

### 2. **Encapsulation**
- **Definition**: Bundling data (attributes) and methods (functions) that operate on the data into a single unit (class)
- **Implementation**: 
  - Private member variables (e.g., `balance`, `accountNumber`)
  - Public methods to access and modify data (getters/setters)
  - Data hiding to protect internal state

### 3. **Access Specifiers**
- **private**: Members accessible only within the class
- **protected**: Members accessible within the class and derived classes
- **public**: Members accessible from anywhere

### 4. **Abstraction**
- **Definition**: Hiding complex implementation details and showing only essential features
- **Implementation**:
  - Abstract base class `Account` with pure virtual function `calculateInterest()`
  - Users interact with high-level interfaces without knowing internal workings

### 5. **Inheritance**
- **Definition**: Creating new classes from existing classes
- **Types Demonstrated**:
  - Single Inheritance: `SavingsAccount` inherits from `Account`
  - Single Inheritance: `CheckingAccount` inherits from `Account`
  - Multi-level Inheritance: `PremiumAccount` inherits from `SavingsAccount`
- **Benefits**: Code reusability, establishing relationships

### 6. **Polymorphism**
- **Compile-time Polymorphism**:
  - Function Overloading: Multiple `deposit()` methods with different parameters
  - Operator Overloading: Custom `+` operator for combining accounts
- **Runtime Polymorphism**:
  - Virtual functions: `calculateInterest()`, `display()`
  - Function overriding in derived classes
  - Base class pointers calling derived class methods

### 7. **Constructor**
- **Default Constructor**: No parameters (e.g., `Account()`)
- **Parameterized Constructor**: With parameters (e.g., `Account(string name, double balance)`)
- **Copy Constructor**: Creates object from another object
- **Constructor Chaining**: Derived class calling base class constructor

### 8. **Destructor**
- **Definition**: Special function called when object is destroyed
- **Purpose**: Clean up resources (memory, file handles, etc.)
- **Syntax**: `~ClassName()`
- **Implementation**: Shown in all classes with cleanup messages

## Project Structure

```
Banking System
│
├── Account (Abstract Base Class)
│   ├── Data: accountNumber, accountHolderName, balance
│   ├── Pure Virtual: calculateInterest()
│   └── Virtual: display()
│
├── SavingsAccount (Derived from Account)
│   ├── Additional Data: interestRate
│   ├── Implements: calculateInterest()
│   └── Adds: Minimum balance requirement
│
├── CheckingAccount (Derived from Account)
│   ├── Additional Data: overdraftLimit
│   ├── Implements: calculateInterest()
│   └── Adds: Overdraft protection
│
└── PremiumAccount (Derived from SavingsAccount)
    ├── Additional Data: bonusRate
    ├── Overrides: calculateInterest()
    └── Adds: Premium benefits
```

## Code Features

### Encapsulation Example
```cpp
private:
    double balance;  // Hidden data
    
public:
    double getBalance() const { return balance; }  // Controlled access
    void deposit(double amount) { /* validation */ }  // Controlled modification
```

### Inheritance Example
```cpp
class SavingsAccount : public Account {
    // Inherits all members from Account
    // Adds new functionality
};
```

### Polymorphism Example
```cpp
Account* acc = new SavingsAccount(...);
acc->calculateInterest();  // Calls SavingsAccount's version (Runtime)
acc->deposit(100);         // Function overloading (Compile-time)
```

### Abstraction Example
```cpp
class Account {
public:
    virtual double calculateInterest() = 0;  // Pure virtual function
    // Forces derived classes to implement
};
```

## How to Compile and Run

### Using g++:
```bash
g++ -std=c++11 oop_demo.cpp -o oop_demo
./oop_demo
```

### Using Visual Studio / Code::Blocks:
1. Create a new C++ project
2. Add `oop_demo.cpp` to the project
3. Build and run

## Expected Output
The program demonstrates:
1. Creating different types of bank accounts
2. Performing deposits and withdrawals
3. Calculating interest (different for each account type)
4. Displaying account information
5. Polymorphic behavior with base class pointers
6. Operator overloading (combining accounts)
7. Constructor and destructor calls

## Learning Points

1. **Encapsulation** protects data integrity by controlling access
2. **Inheritance** promotes code reuse and logical hierarchy
3. **Polymorphism** enables flexible and extensible code
4. **Abstraction** simplifies complex systems
5. **Constructors** initialize objects properly
6. **Destructors** clean up resources automatically
7. **Access specifiers** control visibility and access

## Additional Notes

- The code uses **virtual destructors** in base classes to ensure proper cleanup
- **const** keyword is used for methods that don't modify object state
- **Static members** could be added to track total accounts (optional extension)
- Exception handling could be added for robust error management (optional extension)

## Author
This is a comprehensive educational example demonstrating C++ OOP principles.
