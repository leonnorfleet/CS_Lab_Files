#include <iostream>

using namespace std;

class bAccount {

private:
	string name;
	double balance = 0;
	string code;
	bool approved;

public:

	void codeSet() {

		string input;

		cout << "Please enter a passcode: ";

		cin >> input;

		code = input;

		cout << "Password set!" << endl;

	}

	

	void addMoney(double amount) {

		if(approved) {
			
			balance += amount;

			cout << "You added: " << amount << " dollars." << endl;
		
		}
		else {

			cout << "Passcode denied." << endl;

		}

		approved = false;

	}

	double getBalance() {

		if(approved)

		return balance;

	}

	void withdrawMoney(double amount) {
		if (amount > balance) {

			cout << "Insufficient funds. Withdrawal canceled." << endl;

		}
		else {

			balance -= amount;

		}

	}

};

int main() {

	bAccount acct;
	acct.codeSet();
	acct.addMoney(500);
	cout << acct.getBalance() << endl;
	acct.withdrawMoney(750);
	cout << acct.getBalance() << endl;

	
}