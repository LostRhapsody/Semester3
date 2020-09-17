/*
*Name:	Bank Account Practice
*Desc:	A project to practice creating classes and subclasses
*Date	Sept 10th 2020
*By:	Evan Robertson
* Recent Updates:
*		Sept 17th - Added Customer Class
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
	int setAccountNum(int newNum);
	double setBalance(double newBalance);
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
	double setInterestRate(double newRate);
	void applyInterestRate();
	static bool isValidInterestRate(double);
	SavingsAccount();
	SavingsAccount(double intRate, int accountNum, double balance);
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

//Customer Class Starts Here ////////////////////
class Customer {
private:
	std::string name;
	BankAccount* accounts;
	int numOfAccounts;
public:
	std::string getName();
	BankAccount* getAccounts();
	int getnumOfAccounts();
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
	return accounts;
}

//Returns numOfAccounts for Customer object
int Customer::getnumOfAccounts() {
	return numOfAccounts;
}

//Sets name for a Customer object
void Customer::setName(std::string newName) {
	name = newName;
}

//Sets Accounts for Customer object
void Customer::setAccounts(int newNumOfAccounts, BankAccount* accts) {
	numOfAccounts = newNumOfAccounts;
	accounts = accts;
}
//Customer Class Ends Here ////////////////////

int main() {

	BankAccount acct1, acct2;
	BankAccount acct3(1234, 2165.45);
	SavingsAccount savingsAcct1, savingsAcct2(0.005, 8787, 90000);

	Customer defCustomer;

	std::cout << "Customer 1: " << defCustomer.getName() 
		<< "\nNumber of Accounts: " << defCustomer.getnumOfAccounts() << std::endl;

	BankAccount cust2Accts[] = { acct1, acct3, };
	Customer cust2("Johny Joe", 2, cust2Accts);

	std::cout << "Customer 2: " << cust2.getName() 
		<< "\nNumber of Accounts: " << cust2.getnumOfAccounts() 
		<< "\nAccounts: " << cust2.getAccounts()[0] << cust2.getAccounts()[1] << std::endl;

	/*std::cout << "Account #" << acct1.getAccountNumber() << "\nBalance: " << acct1.getBalance()
	*	<< "\nInterest Rate: " << acct1.getInterestRate() << std::endl;
	*std::cout << "\nApplying interest rate of " << (acct1.getInterestRate() * 100) << "%" << std::endl;
	*acct1.applyInterestRate();
	*std::cout << "\nAccount #" << acct1.getAccountNumber() << "\nBalance: " << acct1.getBalance()
	*	<< "\nInterest Rate: " << acct1.getInterestRate() << std::endl;
	*std::cin >> acct1;
	*std::cout << acct1;
	*acct1.setInterestRate(0.009);
	*std::cout << "Acct1 int rate: " << acct1.getInterestRate() << std::endl;
	*/
	/*Bank Account Tests Week 1 Class 2
	SavingsAccount savingsAcct3(0.002, 3333, 45);

	std::cout << "\nSavings Account #" << savingsAcct1.getAccountNumber()
		<< "\nBalance: " << savingsAcct1.getBalance()
		<< "\nInterest Rate: " << savingsAcct1.getInterestRate();
	std::cout << "\n\nSavings Account #" << savingsAcct2.getAccountNumber()
		<< "\nBalance: " << savingsAcct2.getBalance()
		<< "\nInterest Rate: " << savingsAcct2.getInterestRate();
	std::cout << "\n\nSavings Account #" << savingsAcct3.getAccountNumber()
		<< "\nBalance: " << savingsAcct3.getBalance()
		<< "\nInterest Rate: " << savingsAcct3.getInterestRate();

	std::cout << "\n\n**Attempted to change interest rate for Savings Account 1 to invalid integer here**" << std::endl;
	savingsAcct1.setInterestRate(1);
	std::cout << "\nSavings Account 1 Interest Rate: " << savingsAcct1.getInterestRate() << std::endl;
	std::cout << "\n**Created a new savings account with invalid interest rate here**" << std::endl;
	SavingsAccount savingsAcct4(-1, 2222, 33);
	std::cout << "\nSavings Account 4 Interest Rate: " << savingsAcct4.getInterestRate() << std::endl;


	BankAccount acct1, acct2;
	BankAccount acct3(2002, 101), acct4(101, -13), acct5(99999, 100001);
	std::cout << "\n\n // Accounts numbers 1 and 2 check // \n\n" << std::endl;
	std::cout << "Account #" << acct1.getAccountNumber()
		<< "\nBalance: " << acct1.getBalance() << std::endl;
	std::cout << "Account #" << acct2.getAccountNumber()
		<< "\nBalance: " << acct2.getBalance() << std::endl;
	acct1.setAccountNum(999);
	acct1.setBalance(-10);
	acct2.setAccountNum(99991);
	acct2.setBalance(99999999);
	std::cout << "\n\n // Accounts numbers 1, 2, 3, 4, and 5 tests // \n\n" << std::endl;
	std::cout << "Account #" << acct1.getAccountNumber()
		<< "\nBalance: " << acct1.getBalance() << std::endl;
	std::cout << "Account #" << acct2.getAccountNumber()
		<< "\nBalance: " << acct2.getBalance() << std::endl;
	std::cout << "Account #" << acct3.getAccountNumber()
		<< "\nBalance: " << acct3.getBalance() << std::endl;
	std::cout << "Account #" << acct4.getAccountNumber()
		<< "\nBalance: " << acct4.getBalance() << std::endl;
		*/
	return 0;
}