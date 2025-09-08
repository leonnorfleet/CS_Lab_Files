#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
#include <math.h>
#include <vector>
#include<cstring>
#include<string>
#include <cstdlib>
#include <ctime>
using namespace std;


/*vector <double>	remove_negative(vector<double>& vec) {
	vector <double> copy;

	for (int i = 0; i < vec.size(); i++) {

		if (vec[i] < 0) {

			copy.push_back(vec[i]);

			for (int j = i; j < vec.size() - 1; j++) {

				vec[j] = vec[j + 1];

			}

			vec.pop_back();
		}
	}

	return copy;
}*/

/*char* merge(char str1[], char str2[]) {
	int n = strlen(str1) + strlen(str2);
	int len1 = strlen(str1);
	int len2 = strlen(str2);

	char* temp = new char[n];
	char* final = new char[n];

	int even = 0;
	int odd = 1;

	if (len1 > len2) {
		for (int i = 0; i < len2; i++) {
			temp[even] = str1[i];
			temp[odd] = str2[i];
			even += 2;
			odd += 2;
		}
	}
	else {

		for (int i = 0; i < len1; i++) {
			temp[even] = str2[i];
			temp[odd] = str1[i];
			even += 2;
			odd += 2;
		}
	}

	int count = strlen(temp);

	if (len1 > len2) {
		for (int j = 0; j < len1 - len2; j++) {
			temp[count + j] = str1[len2 + j];
		}
	}
	else {
		for (int j = 0; j < len2 - len1; j++) {
			temp[count + j] = str2[len1 + j];
		}

	}

	return temp;
}*/

class BankAccount {
private:
	string name;
	double balance;

public:
	BankAccount(string n, double amount);
	BankAccount();  //default constructor
	BankAccount(string n) { name = n; balance = 0; }

	//copy constructor: need a proper (and deep) copy of data member
	BankAccount(const BankAccount& anAcount) {
		name = anAcount.name;
		balance = anAcount.balance;
		cout << "copy constructor called\n";
	};

	//accessor:
	string getName() const;
	double getBalance() const;
	void display() const;

	//mutator:
	void deposit(double amount);
	void setName(string n);
	void setBalance(double amount);
	void withdraw(double amount);
	void transferTo(BankAccount& anAccount, double amount) {
		cout << "call transferTo( BankAccount &, double)\n";
		if (amount < balance && amount>0) {
			//because this is a member function, then you can access data member of the 
			// parameter object directly via .
			anAccount.balance += amount;
			balance -= amount;
		}
		else {
			cout << "insufficient fund\n";
		}
	}

	void transferTo(BankAccount* anAccount, double amount) {
		cout << "call transferTo( BankAccount *, double)\n";
		if (amount < balance && amount>0) {
			//because this is a member function, then you can access data member of the 
			// parameter object directly via .
			anAccount->balance += amount;
			balance -= amount;
		}
		else {
			cout << "insufficient fund\n";
		}
	}

	// function return an object
	BankAccount createSubAccount(string subname, double amount);
	BankAccount* createSubAccountPtr(string subname, double amount);

};

BankAccount::BankAccount() {
	name = "unknown";
	balance = 0;
}

// this pointer helps to distingish data member
BankAccount::BankAccount(string n, double balance) {
	this->name = n;
	this->balance = balance;
}

string BankAccount::getName() const {
	return name;
}

double BankAccount::getBalance() const {
	return balance;
}

void BankAccount::display() const {
	cout << "Name: " << name << ", balance = " << balance << endl;
}

//mutator:
void BankAccount::deposit(double amount) {
	balance += amount;
}
void BankAccount::setName(string n) {
	name = n;
}
void BankAccount::setBalance(double amount) {
	balance = amount;
}

void BankAccount::withdraw(double amount) {
	if (balance >= amount) {
		balance -= amount;
		cout << "withdraw " << amount << " from account's name " << name << " successfully\n";
	}
	else {
		cout << "insufficient fund for withdraw. withdraw cancelled\n";
	}
}

BankAccount BankAccount::createSubAccount(string subname, double amount) {
	if (balance >= amount) {
		balance -= amount;
		return BankAccount(subname, amount);
	}
	else {
		cout << "insufficient fund for creating a sub account\n";
		return BankAccount(subname, 0);
	}
}

BankAccount* BankAccount::createSubAccountPtr(string subname, double amount) {
	if (balance >= amount) {
		balance -= amount;
		return new BankAccount(subname, amount);
	}
	else {
		cout << "insufficient fund for creating a sub account\n";
		return new BankAccount(subname, 0);
	}
}

void Merge2Accounts(BankAccount& acc1, BankAccount& acc2, string new_name) {
	acc1.display();
	acc2.display();
	BankAccount acc3;
	acc3.setName(new_name);
	double new_balance = acc1.getBalance() + acc2.getBalance();
	acc3.setBalance(new_balance);

	cout << "Transfer Completed! Accounts Cleared." << endl;

	acc1.setName("inactive account");
	acc1.setBalance(0);

	acc2.setName("inactive account");
	acc2.setBalance(0);

	acc3.display();
	acc2.display();
	acc1.display();

}


int main() {

	srand(time(0));

	for (int i = 0; i < 100; i++) {
		double x = rand() * 8.0 / RAND_MAX - 5.0;

		cout << x << endl;
	}

	return 0;

}
/*

	srand(time(0));

	for (int i = 0; i < 100; i++) {
		double x = rand() * 8.0 / RAND_MAX - 5.0;

		cout << x << endl;
	}
	--------------------------
	int n;
	long long result = pow(7, 23);

	cout << result << endl;

	for (int i = 1; i <= 25; i++) {

		result = pow(7, i) + 1;
		cout << i << "th " << "(7 ^ n + 1) % 7 = " << result % 7 << endl;
	}
	-------------------------
	void fun(double a[], double value) {
		*(a + 1) = value * value * value;
	}
		double x = 3.0;
		double* x_ptr = &x;
		fun(x_ptr, 5);
		cout << "*x_ptr = " << *x_ptr << endl;
		cout << "*(x_ptr+1) = " << *(x_ptr + 1) << endl;
	---------------------------------------
	BankAccount* BankArray = new BankAccount[100];

	srand(time(0) * 1.0);

	for (int i = 0; i < 100; i++) {

		int value = (rand() % 31 + 10)*100;

		string name = "account " + to_string(i + 1);

		(BankArray + i)->setName(name);

		(BankArray + i)->setBalance(value);

		(BankArray + i)->display();


	}
*/
