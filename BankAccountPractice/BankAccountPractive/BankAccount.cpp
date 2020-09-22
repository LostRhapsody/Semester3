/*
*Name:	Bank Account Practice
*Desc:	A project to practice creating classes and subclasses
*Date	Sept 10th 2020
*By:	Evan Robertson
* Recent Updates:
*		Sept 17th - Added Customer Class, ChequingAccount class,
*		Sept 18th - Added insertion and extraction operators for new classes, added static validatiod methods
*		Sept 20th - Changed testing methods, more thorough. Should be ready for next class 
*/

#include <iostream>
#include <string>

//Bank Account Class Starts Here ////////////////////
class BankAccount {
	friend std::ostream& operator<<(std::ostream&, BankAccount&);
	friend std::istream& operator>>(std::istream&, BankAccount&);
private:
	int accountNum;
	double balance;
	static int nextAccountNum;
public:
	int getAccountNumber();
	double getBalance();
	int setAccountNum(int);
	double setBalance(double);
	void deposit(double);
	void withdrawal(double);
	static bool isValidAccountNumber(int);
	static bool isValidBalance(double);
	BankAccount();
	BankAccount(int, double);
};
int BankAccount::nextAccountNum = 1000;

//Constructs a default BankAccount object
BankAccount::BankAccount() {
	accountNum = nextAccountNum;
	nextAccountNum++;
	balance = 0;

	std::cout << "bank account " << accountNum << " created.\n" << std::endl;
}

//Constructs a BankAcccount object with custom values for the properties
BankAccount::BankAccount(int acctNum, double balance) {
	if(isValidAccountNumber(acctNum)) {
		this->accountNum = acctNum;
	}
	else {
		accountNum = nextAccountNum;
		nextAccountNum++;
	}

	if (isValidBalance(balance)) {
		this->balance = balance;
	}
	else {
		this->balance = 0;
	}

	std::cout << "bank account " << accountNum << " created.\n" << std::endl;
}

//Returns account number for this BankAccount
int BankAccount::getAccountNumber() {
	return this->accountNum;
}

//Returns balance for this BankAccount
double BankAccount::getBalance() {
	return this->balance;
}

//Sets a new account number for this BankAccount
int BankAccount::setAccountNum(int newNum) {
	if (isValidAccountNumber(newNum)) {
		this->accountNum = newNum;
	}
	return this->accountNum;
}

//Sets a new balance for this BankAccount
double BankAccount::setBalance(double newBalance) {
	if (isValidBalance(newBalance)) {
		this->balance = newBalance;
	}
	else {
		std::cout << "Balance cannot be over $100,000" << std::endl;
		return this->balance;
	}
}

//Makes a deposit into the BankAccount object
void BankAccount::deposit(double deposit) {
	balance += deposit;
}

//Makes a withdrawl from the BankAccount object
void BankAccount::withdrawal(double withdrawal) {
	balance -= withdrawal;
}

//Validates BankAccount account number
bool BankAccount::isValidAccountNumber(int num) {
	bool result = false;
	if (num >= 1000 && num <= 9999) {
		result = true;
	}
		return result;
}

//Validate BankAccount balance
bool BankAccount::isValidBalance(double balance) {
	bool result = false;
	if (balance >= 0 && balance <= 100000) {
		result = true;
	}
	return result;
}
//Bank Account Class Ends Here ////////////////////

//Bank Account Overloaded output operator for simplified display
std::ostream& operator<<(std::ostream& out, BankAccount& ba) {
	out << "\nAccount Number: " << ba.getAccountNumber()
		<< "\nAccount Balance: $" << ba.getBalance() << std::endl;
	return out;
}

//Bank Account overloaded input operator for simplified input
std::istream& operator>>(std::istream& in, BankAccount& ba) {
	std::cout << "Enter a new account number (1000 - 9999): ";
	in >> ba.accountNum;
	while (! BankAccount::isValidAccountNumber(ba.accountNum)) {
		std::cout << "Invalid account number\n";
		std::cout << "Enter a new account numer (1000 - 9999): ";
		in >> ba.accountNum;
	}

	std::cout << "\nEnter a new balance ($0.00 - $100,000.00): ";
	in >> ba.balance;
	while (! ba.isValidBalance(ba.balance)) {
		std::cout << "Invalid balance\n";
		std::cout << "Enter a new balance ($0.00 - $100,000.00): ";
		in >> ba.balance;
	}
	return in;
}

//Savings Account Sub Class Starts Here ////////////////////
class SavingsAccount :public BankAccount {
	friend std::ostream& operator<<(std::ostream&, SavingsAccount&);
	friend std::istream& operator>>(std::istream&, SavingsAccount&);
private:
	double interestRate;
	static double defaultIntRate;
public:
	double getInterestRate();
	double setInterestRate(double);
	void applyInterestRate();
	static bool isValidInterestRate(double);
	SavingsAccount();
	SavingsAccount(double, int, double);
};
double SavingsAccount::defaultIntRate = 0.005;

//Creates a new SavingsAccount object using default values
SavingsAccount::SavingsAccount() :BankAccount() {
	this->interestRate = defaultIntRate;
}

//Creates a new custom SavingsAccount object by calling the BankAccount Super Class
SavingsAccount::SavingsAccount(double intRate, int accountNum, double balance)
	: BankAccount(accountNum, balance) {
	//Set interest rate
	if (isValidInterestRate(intRate)) {
		this->interestRate = intRate;
	}
	else {
		this->interestRate = defaultIntRate;
	}
}

//Returns the interest rate for this SavingsAccount
double SavingsAccount::getInterestRate() {
	return this->interestRate;
}

//Sets a new interest rate for this SavingsAccount
double SavingsAccount::setInterestRate(double newRate) {
	if (isValidInterestRate(newRate)) {
		this->interestRate = newRate;
	}
	else {
		return this->interestRate;
	}
}

//Applies the current interest rate of a SavingsAccount to the objects balance
void SavingsAccount::applyInterestRate() {
	double newBalance, oldBalance, intRate;
	newBalance = 0;
	oldBalance = this->getBalance();
	intRate = this->getInterestRate();
	newBalance = oldBalance * intRate + oldBalance;
	setBalance(newBalance);
}

//Validate SavingsAccount Interest Rate
bool SavingsAccount::isValidInterestRate(double intRate) {
	bool result = false;
	if (intRate >= .005 && intRate <= .04) {
		result = true;
	}
	return result;
}
//Savings Account Sub Class Ends Here ////////////////////

//Overloaded Output operator for simplified output of SavingsAccount object
std::ostream& operator<<(std::ostream& out, SavingsAccount& sa) {
	out << "\nAccount Number: " << sa.getAccountNumber()
		<< "\nAccount Balance: $" << sa.getBalance()
		<< "\nAccount Interest Rate: " << sa.getInterestRate() << "%" << std::endl;
	return out;
}

//Overloaded Input operator for simplified input of SavingsAccount object
std::istream& operator>>(std::istream& in, SavingsAccount& sa) {
	int acctNum = sa.getAccountNumber();
	double balance = sa.getBalance();
	std::cout << "Enter a new account number (1000 - 9999): ";
	in >> acctNum;
	while (!BankAccount::isValidAccountNumber(acctNum)) {
		std::cout << "Invalid account number\n";
		std::cout << "Enter a new account numer (1000 - 9999): ";
		in >> acctNum;
		sa.setAccountNum(acctNum);
	}
	sa.setAccountNum(acctNum);

	std::cout << "\nEnter a new balance ($0.00 - $100,000.00): ";
	in >> balance;
	while (!sa.isValidBalance(balance)) {
		std::cout << "Invalid balance\n";
		std::cout << "Enter a new balance ($0.00 - $100,000.00): ";
		in >> balance;
		sa.setBalance(balance);
	}
	sa.setBalance(balance);

	std::cout << "\nEnter a new interest rate (0.005% - 0.04%) ";
	in >> sa.interestRate;
	while (!sa.isValidInterestRate(sa.interestRate)) {
		std::cout << "invalid interest rate\n";
		std::cout<<"Enter a new interest rate (0.005% - 0.04%) ";
		in >> sa.interestRate;
	}
	return in;
}

//ChequingAccount Starts Here ////////////////////
class ChequingAccount :public BankAccount {
	friend std::ostream& operator<<(std::ostream&, ChequingAccount&);
	friend std::istream& operator>>(std::istream&, ChequingAccount&);
private:
	int numOfTransactions;
public:
	int getTransactionNum();
	int setTransactionNum(int);
	void cheque(double);
	void applyFees(int);
	static bool isValidTransactionNum(int);
	ChequingAccount();
	ChequingAccount(int, int, double);
};

//Constructs a ChequingAccount object with default values
ChequingAccount::ChequingAccount() {
	numOfTransactions = 0;
}

//Constructs a ChequingAccount object with custom values
ChequingAccount::ChequingAccount(int transactions, int accountNum, double balance)
	: BankAccount(accountNum, balance) {
	numOfTransactions = transactions;
}

//Returns the number of transactions for this ChequingAccount object
int ChequingAccount::getTransactionNum() {
	return numOfTransactions;
}

//Sets the number of transactions for this ChequingAccount object
int ChequingAccount::setTransactionNum(int newNum) {
	if (isValidTransactionNum(newNum)) {
		numOfTransactions = newNum;
	}
	else {
		return numOfTransactions;
	}
}

//Cheque method used to debit account by the amount of the cheque
void ChequingAccount::cheque(double debitAmount) {
	double balance = getBalance();
	balance -= debitAmount;
	setBalance(balance);
	//Increment Transaction Count
	numOfTransactions++;
}

//Applies fees to this ChequingAccount object according to numOfTransactions
void ChequingAccount::applyFees(int transactions) {
	double balance = getBalance();
	balance -= transactions * 0.25;
	setBalance(balance);
	//Set numOfTransactions to zero
	numOfTransactions = 0;
}

//Validate ChequingAccount Transaction numbers
bool ChequingAccount::isValidTransactionNum(int transactionNum) {
	bool result = false;
	if (transactionNum >= 0) {
		result = true;
	}
	return result;
}
//ChequingAccount Ends Here////////////////////

std::ostream& operator<<(std::ostream& out, ChequingAccount& ca) {
	out << "\nAccount Number: " << ca.getAccountNumber()
		<< "\nAccount Balance: $" << ca.getBalance()
		<< "\nAccount Transactions: " << ca.getTransactionNum() << std::endl;
	return out;
}

std::istream& operator>>(std::istream& in, ChequingAccount& ca) {
	int acctNum = ca.getAccountNumber();
	double balance = ca.getBalance();
	std::cout << "Enter a new account number (1000 - 9999): ";
	in >> acctNum;
	while (!BankAccount::isValidAccountNumber(acctNum)) {
		std::cout << "Invalid account number\n";
		std::cout << "Enter a new account numer (1000 - 9999): ";
		in >> acctNum;
		ca.setAccountNum(acctNum);
	}
	ca.setAccountNum(acctNum);

	std::cout << "\nEnter a new balance ($0.00 - $100,000.00): ";
	in >> balance;
	while (!ca.isValidBalance(balance)) {
		std::cout << "Invalid balance\n";
		std::cout << "Enter a new balance ($0.00 - $100,000.00): ";
		in >> balance;
		ca.setBalance(balance);
	}
	ca.setBalance(balance);

	std::cout << "\nEnter a new number of transactions: ";
	in >> ca.numOfTransactions;
	while (!ca.isValidTransactionNum(ca.numOfTransactions)) {
		std::cout << "Invalid number of transactions\n";
		std::cout << "Enter a new number of transactions: ";
		in >> ca.numOfTransactions;
	}
	return in;
}

//Customer Class Starts Here ////////////////////
class Customer {
	friend std::ostream& operator<<(std::ostream&, Customer&);
	friend std::istream& operator>>(std::istream&, Customer&);
private:
	std::string name;
	BankAccount* accounts;
	int numOfAccounts;
public:
	std::string getName();
	BankAccount* getAccounts();
	int getNumOfAccounts();
	std::string setName(std::string);
	int setAccounts(int, BankAccount*);
	static bool isValidName(std::string);
	static bool isValidNumOfAccts(int);
	Customer();
	Customer(std::string, int, BankAccount*);
};

//Constructs a Customer object with default values
Customer::Customer() {
	name = "Drew Doe";
	numOfAccounts = 0;
	accounts = new BankAccount[0];
}

//Constructs a Customer object with custom values for the properties
Customer::Customer(std::string newName, int newNumOfAccounts, BankAccount* accts) {
	name = newName;
	numOfAccounts = newNumOfAccounts;
	accounts = accts;
}

//Returns name for Customer object
std::string Customer::getName() {
	return std::string(name);
}

//Returns Accounts for Customer object
BankAccount* Customer::getAccounts() {
	if (numOfAccounts == 0) {
		std::cout << "Customer has no accounts" << std::endl;
	}
		return accounts;
}

//Returns numOfAccounts for Customer object
int Customer::getNumOfAccounts() {
	return numOfAccounts;
}

//Sets name for a Customer object
std::string Customer::setName(std::string newName) {
	if (isValidName(newName)) {
		name = newName;
	}
	return name;
}

//Sets Accounts for Customer object
int Customer::setAccounts(int newNumOfAccounts, BankAccount* accts) {
	accounts = accts;
	if (isValidNumOfAccts(newNumOfAccounts)) {
		numOfAccounts = newNumOfAccounts;
	}
	return numOfAccounts;
}

//Verifies Customer object name
bool Customer::isValidName(std::string name) {
	bool result = false;
	if (name != "") {
		result = true;
	}
	return result;
}

//Verifies Customer object number of accounts
bool Customer::isValidNumOfAccts(int numOfAccts) {
	bool result = false;
	if (numOfAccts >= 0) {
		result = true;
	}
	return result;
}
//Customer Class Ends Here ////////////////////

//Customer object overloaded output operator
std::ostream& operator<<(std::ostream& out, Customer& customer) {
	out << "Customer name: " << customer.name
		<< "\nNumber of Customer Accounts: " << customer.numOfAccounts
		<< "\nCustomer Accounts: ";
	if (customer.numOfAccounts == 0) {
		std::cout << "\nCustomer has no accounts" << std::endl;
	}
	else {
	for (int x = 0; x < customer.numOfAccounts; x++) {
		out << customer.accounts[x];
		}
	}
	return out;
}

//Customer object overloaded input operator
std::istream& operator>>(std::istream& in, Customer& customer) {
	std::cout << "Enter name for Customer: ";
	in >> customer.name;
	while (!customer.isValidName(customer.name)) {
		std::cout << "Name must not be left empty\n";
		std::cout << "Enter name for Customer: ";
		in >> customer.name;
	}

	std::cout << "Enter number of accounts for this customer: ";
	in >> customer.numOfAccounts;
	while (!customer.isValidNumOfAccts(customer.numOfAccounts)) {
		std::cout << "Number of accounts must not be less than zero\n";
		std::cout << "Enter number of accounts for this customer: ";
		in >> customer.numOfAccounts;
	}
	return in;
}

int main() {

	BankAccount acct1, acct2(9876, 400);
	SavingsAccount savAcct1, savAcct2(0.008, 5678, 85.43);
	ChequingAccount cheAcct1, cheAcct2(1, 8383, 99.76);
	Customer cust1, cust2, cust3, cust4;
	BankAccount cust1Accounts[] = { acct1 };
	BankAccount cust2Accounts[] = { savAcct1, cheAcct1};
	BankAccount cust3Accounts[] = { acct2, savAcct2, cheAcct2 };
	cust1.setAccounts(1, cust1Accounts);
	cust2.setAccounts(2, cust2Accounts);
	cust3.setAccounts(3, cust3Accounts);

	/* Testing Customer Objects Using Overloaded Operators: Begin */
	std::cout << "Testing Phase : Overloaded Operators : Customer Objects : Display\n" << std::endl;
	std::cout << cust1 << std::endl;
	std::cout << cust2 << std::endl;
	std::cout << cust3 << std::endl;
	std::cout << cust4 << std::endl;

	/* Testing Savings Account Setters and Getters : Begin*/
	std::cout << "Testing Phase : Setters and Getters : Savings Account Objects" << std::endl;
	savAcct1.setAccountNum(5555);
	savAcct1.setBalance(88.97);
	savAcct1.setInterestRate(0.006);
	std::cout << savAcct1.getAccountNumber() << std::endl;
	std::cout << savAcct1.getBalance() << std::endl;
	std::cout << savAcct1.getInterestRate() << std::endl;
	/* Testing Savings Account Setters and Getters : End*/

	/* Testing Chequing Account Setters and Getters : Begin*/
	std::cout << "Testing Phase : Setters and Getters : Chequing Account Objects" << std::endl;
	cheAcct1.setAccountNum(4444);
	cheAcct1.setBalance(500.02);
	cheAcct1.setTransactionNum(2);
	std::cout << cheAcct1.getAccountNumber() << std::endl;
	std::cout << cheAcct1.getBalance() << std::endl;
	std::cout << cheAcct1.getTransactionNum() << std::endl;
	/* Testing Chequing Account Setters and Getters : End*/

	/* Testing Customer Account Setters and Getters : Begin*/
	std::cout << "Testing Phase : Setters and Getters : Customer Objects" << std::endl;
	cust1.setName("Evan Robertson");
	std::cout << cust1.getName() << std::endl;
	std::cout << cust1.getNumOfAccounts() << std::endl;
	std::cout << cust1.getAccounts()[0] << std::endl;
	/* Testing Customer Account Setters and Getters : End*/

	std::cout << "Testing Phase : Overloaded Operators : Customer Objects (cust1) : Input\n" << std::endl;
	std::cin >> cust1;

	std::cout << "Testing Phase : Overloaded Operators : Customer Objects (cust1) : Display\n" << std::endl;
	std::cout << cust1 << std::endl;
	/* Testing Customer Objects Using Overloaded Operators: End*/

	/* Testing BankAccount Objects Using Overloaded Operators: Begin */
	std::cout << "Testing Phase : Overloaded Operators : BankAccount" << std::endl;
	std::cout << acct1;
	std::cin >> acct1;
	std::cout << acct1;
	/* Testing BankAccount Objects Using Overloaded Operators: Begin*/

	/* Testing SavingsAccount Objects Using Overloaded Operators: Begin */
	std::cout << "Testing Phase : Overloaded Operators : SavingsAccount" << std::endl;
	std::cout << savAcct1;
	std::cin >> savAcct1;
	std::cout << savAcct1;
	/* Testing SavingsAccount Objects Using Overloaded Operators: Begin*/

	/* Testing ChequingAccount Objects Using Overloaded Operators: Begin */
	std::cout << "Testing Phase : Overloaded Operators : ChequingAccount" << std::endl;
	std::cout << cheAcct1;
	std::cin >> cheAcct1;
	std::cout << cheAcct1;
	/* Testing ChequingAccount Objects Using Overloaded Operators: Begin*/

	/* Testing SavingsAccount Objects applyInterestRate() function: Begin*/
	std::cout << "Testing Phase : applyInterestRate() Function : Savings Account" << std::endl;
	std::cout << savAcct2;
	savAcct2.applyInterestRate();
	std::cout << savAcct2;
	/* Testing SavingsAccount Objects applyInterestRate() function: Begin*/

	/* Testing SavingsAccount Objects applyFees() function: Begin*/
	std::cout << "Testing Phase : applyFees() Function : Chequing Account" << std::endl;
	std::cout << cheAcct2;
	cheAcct2.applyFees(cheAcct2.getTransactionNum());
	std::cout << cheAcct2;
	/* Testing SavingsAccount Objects applyFees() function: Begin*/

	return 0;
}