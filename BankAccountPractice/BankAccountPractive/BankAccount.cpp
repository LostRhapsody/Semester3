/*
*Name:	Bank Account Practice
*Desc:	A project to practice creating classes and subclasses
*Date	Sept 10th 2020
*By:	Evan Robertson
* Recent Updates:
*		Sept 17th - Added Customer Class, ChequingAccount class,
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
		std::cout << "Invalid enter\n";
		std::cout << "Enter a new account numer (1000 - 9999): ";
		in >> ba.accountNum;
	}

	std::cout << "\nEnter a new balance ($0.00 - $100,000.00): ";
	in >> ba.balance;
	while (! ba.isValidBalance(ba.balance)) {
		std::cout << "Invalid enter\n";
		std::cout << "Enter a new balance ($0.00 - $100,000.00): ";
		in >> ba.balance;
	}
	return in;
}

//Savings Account Sub Class Starts Here ////////////////////
class SavingsAccount :public BankAccount {
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

//Savings account overloaded input operator for simplified input
bool SavingsAccount::isValidInterestRate(double intRate) {
	bool result = false;
	if (intRate >= .005 && intRate <= .04) {
		result = true;
	}
	return result;
}
//Savings Account Sub Class Ends Here ////////////////////

//ChequingAccount Starts Here ////////////////////
class ChequingAccount :public BankAccount {
private:
	int numOfTransactions;
public:
	int getTransactionNum();
	void setTransactionNum(int);
	void cheque(double);
	void applyFees(int);
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
void ChequingAccount::setTransactionNum(int newNum) {
	if (newNum < 0) {
		while (newNum < 0) {
			std::cout << "Number of transactions cannot be less than zero\nEnter number of transactions: " << std::endl;
			std::cin >> newNum;

		}
		numOfTransactions = newNum;
	}
	else {
		numOfTransactions = newNum;
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

//ChequingAccount Ends Here////////////////////

//Customer Class Starts Here ////////////////////
class Customer {
private:
	std::string name;
	BankAccount* accounts;
	int numOfAccounts;
public:
	std::string getName();
	BankAccount* getAccounts();
	int getNumOfAccounts();
	void setName(std::string);
	void setAccounts(int, BankAccount*);
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
void Customer::setName(std::string newName) {
	if (newName == "") {
		while (newName == "") {
			std::cout << "Name must not be empty\nEnter name: " << std::endl;
			std::cin >> newName;
			name = newName;
		}
	}
	else {
		name = newName;
	}
}

//Sets Accounts for Customer object
void Customer::setAccounts(int newNumOfAccounts, BankAccount* accts) {
	if (newNumOfAccounts < 0) {
		while (newNumOfAccounts < 0) {
			std::cout << "Number of accounts cannot be less than zero\nEnter number of accounts: " << std::endl;
			std::cin >> newNumOfAccounts;
			numOfAccounts = newNumOfAccounts;
		}
	}
	else {
		numOfAccounts = newNumOfAccounts;
	}
	accounts = accts;
}
//Customer Class Ends Here ////////////////////

int main() {

	BankAccount acct1;
	Customer cust1;
	BankAccount cust1Accounts[] = { acct1 };
	cust1.setAccounts(1, cust1Accounts);
	cust1.setName("evan");
	std::cout << cust1.getAccounts()[0] << std::endl;
	std::cout << cust1.getNumOfAccounts() << std::endl;
	std::cout << cust1.getName() << std::endl;

	return 0;
}