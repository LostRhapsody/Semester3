/*
*Name:	Bank Account Practice
*Desc:	A project to practice creating classes and subclasses
*Date	Sept 10th 2020
*By:		Evan Robertson
*/
#include <iostream>

//Bank Account Class Starts Here 
class BankAccount {
private:
	int accountNum;
	double balance;
	static int nextAccountNum;
public:
	int getAccountNumber();
	double getBalance();
	int setAccountNum(int newNum);
	double setBalance(double newBalance);
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
	if (acctNum >= 1000 && acctNum <= 9999) {
		this->accountNum = acctNum;
	}
	else {
		accountNum = nextAccountNum;
		nextAccountNum++;
	}

	if (balance < 0 || balance >= 100000) {
		this->balance = 0;
	}
	else {
		this->balance = balance;
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
	if (newNum >= 1000 && newNum <= 9999) {
		this->accountNum = newNum;
	}
	return this->accountNum;
}

//Sets a new balance for this BankAccount
double BankAccount::setBalance(double newBalance) {
	if (newBalance >= 0 && newBalance <= 100000) {
		this->balance = newBalance;
	} else {
		std::cout << "Balance cannot be over $100,000" << std::endl;
		return this->balance;
	}
}
//Bank Account Class Ends Here

//Savings Account Sub Class Starts Here
class SavingsAccount :public BankAccount {
private:
	double interestRate;
	static double defaultIntRate;
public:
	double getInterestRate();
	double setInterestRate(double newRate);
	void applyInterestRate();
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
	if (intRate >= .005 && intRate <= .04) {
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
	if (newRate > .005 && newRate < .04) {
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

//Savings Account Sub Class Starts Here

int main() {

	SavingsAccount acct1(0.005, 8787, 90000);
	std::cout << "Account #" << acct1.getAccountNumber() << "\nBalance: " << acct1.getBalance()
		<< "\nInterest Rate: " << acct1.getInterestRate() << std::endl;
	std::cout << "\nApplying interest rate of " << (acct1.getInterestRate() * 100) << "%" << std::endl;
	acct1.applyInterestRate();
	std::cout << "\nAccount #" << acct1.getAccountNumber() << "\nBalance: " << acct1.getBalance()
		<< "\nInterest Rate: " << acct1.getInterestRate() << std::endl;


	/*Bank Account Tests Week 1 Class 2
	SavingsAccount savingsAcct1, savingsAcct2;
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