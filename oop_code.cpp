#include <iostream>
#include <string>
using namespace std;

// ============================================================================
// ABSTRACT BASE CLASS - Demonstrates Abstraction, Encapsulation, Virtual Functions
// ============================================================================
class Account {
private:  // ENCAPSULATION - Private members (data hiding)
    int accountNumber;
    string accountHolderName;
    
protected:  // ACCESS SPECIFIER - Protected (accessible in derived classes)
    double balance;
    
public:  // ACCESS SPECIFIER - Public (accessible everywhere)
    static int totalAccounts;  // Static member to track total accounts
    
    // DEFAULT CONSTRUCTOR
    Account() {
        accountNumber = 0;
        accountHolderName = "Unknown";
        balance = 0.0;
        totalAccounts++;
        cout << "Account Default Constructor called" << endl;
    }
    
    // PARAMETERIZED CONSTRUCTOR
    Account(int accNum, string name, double bal) {
        accountNumber = accNum;
        accountHolderName = name;
        balance = bal;
        totalAccounts++;
        cout << "Account Parameterized Constructor called for: " << name << endl;
    }
    
    // COPY CONSTRUCTOR
    Account(const Account& other) {
        accountNumber = other.accountNumber;
        accountHolderName = other.accountHolderName;
        balance = other.balance;
        totalAccounts++;
        cout << "Account Copy Constructor called" << endl;
    }
    
    // VIRTUAL DESTRUCTOR - Important for proper cleanup in inheritance
    virtual ~Account() {
        totalAccounts--;
        cout << "Account Destructor called for: " << accountHolderName << endl;
    }
    
    // FUNCTION OVERLOADING (Compile-time Polymorphism)
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << endl;
        }
    }
    
    void deposit(double amount, string description) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: $" << amount << " (" << description << ")" << endl;
        }
    }
    
    // Virtual function for withdrawal
    virtual bool withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            cout << "Withdrawn: $" << amount << endl;
            return true;
        }
        cout << "Insufficient funds!" << endl;
        return false;
    }
    
    // PURE VIRTUAL FUNCTION - Makes this an abstract class (Abstraction)
    virtual double calculateInterest() = 0;
    
    // VIRTUAL FUNCTION - Can be overridden (Runtime Polymorphism)
    virtual void display() const {
        cout << "\n--- Account Details ---" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Balance: $" << balance << endl;
    }
    
    // GETTER methods (Encapsulation - controlled access)
    int getAccountNumber() const { return accountNumber; }
    string getAccountHolderName() const { return accountHolderName; }
    double getBalance() const { return balance; }
    
    // SETTER methods (Encapsulation - controlled modification)
    void setAccountHolderName(string name) { accountHolderName = name; }
    
    // OPERATOR OVERLOADING (Compile-time Polymorphism)
    Account operator+(const Account& other) {
        Account temp;
        temp.balance = this->balance + other.balance;
        temp.accountHolderName = this->accountHolderName + " & " + other.accountHolderName;
        return temp;
    }
    
    // Static method
    static int getTotalAccounts() {
        return totalAccounts;
    }
};

// Initialize static member
int Account::totalAccounts = 0;

// ============================================================================
// DERIVED CLASS 1 - SavingsAccount (Demonstrates Inheritance)
// ============================================================================
class SavingsAccount : public Account {  // PUBLIC INHERITANCE
private:
    double interestRate;
    double minimumBalance;
    
public:
    // CONSTRUCTOR with initialization list (calls base class constructor)
    SavingsAccount(int accNum, string name, double bal, double rate) 
        : Account(accNum, name, bal), interestRate(rate), minimumBalance(1000.0) {
        cout << "SavingsAccount Constructor called" << endl;
    }
    
    // DESTRUCTOR
    ~SavingsAccount() {
        cout << "SavingsAccount Destructor called" << endl;
    }
    
    // IMPLEMENTING pure virtual function (Abstraction)
    double calculateInterest() override {
        double interest = balance * interestRate / 100;
        cout << "Interest calculated (Savings): $" << interest << endl;
        return interest;
    }
    
    // OVERRIDING virtual function (Runtime Polymorphism)
    void display() const override {
        Account::display();  // Call base class method
        cout << "Account Type: Savings" << endl;
        cout << "Interest Rate: " << interestRate << "%" << endl;
        cout << "Minimum Balance: $" << minimumBalance << endl;
    }
    
    // Override withdraw to enforce minimum balance
    bool withdraw(double amount) override {
        if (balance - amount >= minimumBalance) {
            balance -= amount;
            cout << "Withdrawn: $" << amount << endl;
            return true;
        }
        cout << "Cannot withdraw! Minimum balance requirement: $" << minimumBalance << endl;
        return false;
    }
    
    // Getter for interest rate
    double getInterestRate() const { return interestRate; }
    
    // Setter for interest rate
    void setInterestRate(double rate) {
        if (rate >= 0) {
            interestRate = rate;
        }
    }
};

// ============================================================================
// DERIVED CLASS 2 - CheckingAccount (Demonstrates Inheritance)
// ============================================================================
class CheckingAccount : public Account {
private:
    double overdraftLimit;
    int transactionCount;
    
public:
    // CONSTRUCTOR
    CheckingAccount(int accNum, string name, double bal, double overdraft)
        : Account(accNum, name, bal), overdraftLimit(overdraft), transactionCount(0) {
        cout << "CheckingAccount Constructor called" << endl;
    }
    
    // DESTRUCTOR
    ~CheckingAccount() {
        cout << "CheckingAccount Destructor called" << endl;
    }
    
    // IMPLEMENTING pure virtual function
    double calculateInterest() override {
        double interest = balance * 0.5 / 100;  // Lower interest for checking
        cout << "Interest calculated (Checking): $" << interest << endl;
        return interest;
    }
    
    // OVERRIDING display method
    void display() const override {
        Account::display();
        cout << "Account Type: Checking" << endl;
        cout << "Overdraft Limit: $" << overdraftLimit << endl;
        cout << "Transactions: " << transactionCount << endl;
    }
    
    // Override withdraw with overdraft protection
    bool withdraw(double amount) override {
        if (amount > 0 && (balance + overdraftLimit) >= amount) {
            balance -= amount;
            transactionCount++;
            cout << "Withdrawn: $" << amount << " (Overdraft available)" << endl;
            return true;
        }
        cout << "Insufficient funds even with overdraft!" << endl;
        return false;
    }
    
    void deposit(double amount) {
        Account::deposit(amount);
        transactionCount++;
    }
};

// ============================================================================
// MULTI-LEVEL INHERITANCE - PremiumAccount inherits from SavingsAccount
// ============================================================================
class PremiumAccount : public SavingsAccount {
private:
    double bonusRate;
    bool hasConciergeService;
    
public:
    // CONSTRUCTOR - demonstrates multi-level constructor chaining
    PremiumAccount(int accNum, string name, double bal, double rate, double bonus)
        : SavingsAccount(accNum, name, bal, rate), bonusRate(bonus), hasConciergeService(true) {
        cout << "PremiumAccount Constructor called" << endl;
    }
    
    // DESTRUCTOR
    ~PremiumAccount() {
        cout << "PremiumAccount Destructor called" << endl;
    }
    
    // OVERRIDING calculateInterest to add bonus
    double calculateInterest() override {
        double baseInterest = getBalance() * getInterestRate() / 100;
        double bonusInterest = getBalance() * bonusRate / 100;
        double totalInterest = baseInterest + bonusInterest;
        cout << "Interest calculated (Premium): $" << totalInterest 
             << " (Base: $" << baseInterest << " + Bonus: $" << bonusInterest << ")" << endl;
        return totalInterest;
    }
    
    // OVERRIDING display
    void display() const override {
        SavingsAccount::display();
        cout << "Account Type: PREMIUM" << endl;
        cout << "Bonus Rate: " << bonusRate << "%" << endl;
        cout << "Concierge Service: " << (hasConciergeService ? "Yes" : "No") << endl;
    }
    
    void activateConcierge() {
        hasConciergeService = true;
        cout << "Concierge service activated!" << endl;
    }
};

// ============================================================================
// UTILITY CLASS - Demonstrates additional OOP concepts
// ============================================================================
class Bank {
private:
    string bankName;
    
public:
    Bank(string name) : bankName(name) {
        cout << "\n*** " << bankName << " - Banking System Initialized ***\n" << endl;
    }
    
    ~Bank() {
        cout << "\n*** " << bankName << " - System Shutdown ***" << endl;
    }
    
    // Demonstrates polymorphism - accepts any Account type
    void processInterest(Account* account) {
        cout << "\nProcessing interest for account..." << endl;
        double interest = account->calculateInterest();  // Runtime polymorphism
        account->deposit(interest, "Interest Credit");
    }
    
    void displayAccountInfo(Account* account) {
        account->display();  // Runtime polymorphism
    }
};

// ============================================================================
// MAIN FUNCTION - Demonstrates all concepts in action
// ============================================================================
int main() {
    // Create Bank object
    Bank myBank("Global Bank");
    
    cout << "\n=== Creating Accounts (Constructors in action) ===" << endl;
    
    // Creating objects of different classes (demonstrates Inheritance)
    SavingsAccount savings1(1001, "Alice Johnson", 5000.0, 4.5);
    CheckingAccount checking1(2001, "Bob Smith", 3000.0, 500.0);
    PremiumAccount premium1(3001, "Charlie Brown", 10000.0, 5.0, 2.0);
    
    cout << "\n=== Encapsulation: Using Getter Methods ===" << endl;
    cout << "Savings Account Holder: " << savings1.getAccountHolderName() << endl;
    cout << "Savings Balance: $" << savings1.getBalance() << endl;
    
    cout << "\n=== Function Overloading (Compile-time Polymorphism) ===" << endl;
    savings1.deposit(1000.0);  // Single parameter
    savings1.deposit(500.0, "Salary");  // Two parameters
    
    cout << "\n=== Displaying Account Details (Virtual Functions) ===" << endl;
    savings1.display();
    checking1.display();
    premium1.display();
    
    cout << "\n=== Withdrawal Operations ===" << endl;
    savings1.withdraw(500.0);
    checking1.withdraw(3200.0);  // Uses overdraft
    
    cout << "\n=== Runtime Polymorphism with Base Class Pointers ===" << endl;
    Account* accounts[3];
    accounts[0] = &savings1;
    accounts[1] = &checking1;
    accounts[2] = &premium1;
    
    for (int i = 0; i < 3; i++) {
        cout << "\nAccount " << (i + 1) << ":" << endl;
        myBank.processInterest(accounts[i]);  // Calls appropriate calculateInterest()
    }
    
    cout << "\n=== Operator Overloading (Compile-time Polymorphism) ===" << endl;
    Account combinedAccount = savings1 + checking1;
    cout << "Combined balance: $" << combinedAccount.getBalance() << endl;
    
    cout << "\n=== Copy Constructor ===" << endl;
    SavingsAccount savings2 = savings1;  // Copy constructor called
    savings2.display();
    
    cout << "\n=== Static Members ===" << endl;
    cout << "Total accounts created: " << Account::getTotalAccounts() << endl;
    
    cout << "\n=== Multi-level Inheritance Feature ===" << endl;
    premium1.activateConcierge();
    
    cout << "\n=== Abstraction Demo ===" << endl;
    // Account acc;  // ERROR! Cannot instantiate abstract class
    Account* accPtr = new SavingsAccount(4001, "David Lee", 7000.0, 3.5);
    myBank.displayAccountInfo(accPtr);
    myBank.processInterest(accPtr);
    delete accPtr;  // Destructor called (cleanup)
    
    cout << "\n=== Program Ending (Destructors will be called) ===" << endl;
    // Destructors automatically called for stack objects in reverse order
    
    return 0;
}

// ============================================================================
// CONCEPTS DEMONSTRATED:
// ============================================================================
// 1. CLASS & OBJECT: Account, SavingsAccount, CheckingAccount, PremiumAccount, Bank
// 2. ENCAPSULATION: Private/protected members with public getters/setters
// 3. ACCESS SPECIFIERS: private, protected, public
// 4. ABSTRACTION: Abstract class Account with pure virtual function
// 5. INHERITANCE: 
//    - Single: SavingsAccount extends Account
//    - Single: CheckingAccount extends Account
//    - Multi-level: PremiumAccount extends SavingsAccount
// 6. POLYMORPHISM:
//    - Compile-time: Function overloading (deposit), Operator overloading (+)
//    - Runtime: Virtual functions (calculateInterest, display, withdraw)
// 7. CONSTRUCTOR: Default, Parameterized, Copy constructors
// 8. DESTRUCTOR: Cleanup in all classes, virtual destructor in base class
// ============================================================================
