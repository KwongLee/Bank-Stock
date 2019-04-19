
#include "bankAccount.h"
#include <iostream>
#include <fstream>
# include <string>
# include <windows.h>
using namespace std;

bankAccount::bankAccount() :Account() {
}

void bankAccount::bankmenu() {
	bool flag = true;
	int selection;
	char test[256];
	while (flag) {
		cout << "\nPlease select an option" << endl
			<< "\t1. View account balance" << endl
			<< "\t2. Deposit money" << endl
			<< "\t3. Withdraw money" << endl
			<< "\t4. Display transaction history" << endl
			<< "\t5. Return to previous menu" << endl;

		cout << "\tYour selection: ";

		cin.getline(test, 256);
		cout << test << endl;
		selection = atoi(test);

		switch (selection) {
		case 1:
			cout << endl;
			displayPortfolio2();

			break;
		case 2: {
			char line[256];
			double amount;
			cout << "\n\tEnter The amount to deposit: ";
			cin.getline(line, 256);
			cout << line << endl;
			amount = stod(line);
			amount = validInput(amount, 0);
			deposit(amount, 1);
			break;
		}
		case 3: {
			char line[256];
			double amount;
			cout << "\n\tEnter the amount to withdraw: ";
			cin.getline(line, 256);
			cout << line << endl;
			amount = stod(line);
			amount = validInput(amount, 1);
			withdraw(amount, 1);
			break;
		}
		case 4:
			cout << endl;
			BankTrans();
			break;
		case 5:
			cout << "\n\tReturning to Main Menu\n" << endl;
			flag = false;
			break;
		default:
			break;
		}
	}
}

void bankAccount::deposit(double val, bool b) {

	if (b) {
		cout << endl << "Deposit $" << val << " to bank account" << endl << endl;
		setBalance(getBalance() + val);
		string line2 = "Deposit\t\t" + to_string(val) + "\t" + to_string(getBalance()) + "\t" + getDate() + "\t" + getTime();
		ofstream myfile2;
		myfile2.open("bank_transaction_history.txt", ios_base::app);
		myfile2 << line2 << endl;
		myfile2.close();
		displayPortfolio2();
	}
	else {
		setBalance(getBalance() + val);
		string line2 = "Deposit\t\t" + to_string(val) + "\t" + to_string(getBalance()) + "\t" + getDate() + "\t" + getTime();
		ofstream myfile2;
		myfile2.open("bank_transaction_history.txt", ios_base::app);
		myfile2 << line2 << endl;
		myfile2.close();
	}

}

void bankAccount::withdraw(double val, bool b) {

	if (b) {
		cout << endl << "Withdraw $" << val << " to bank account" << endl << endl;
		setBalance(getBalance() - val);
		string line2 = "Withdraw\t" + to_string(val) + "\t" + to_string(getBalance()) + "\t" + getDate() + "\t" + getTime();
		ofstream myfile2;
		myfile2.open("bank_transaction_history.txt", ios_base::app);
		myfile2 << line2 << endl;
		myfile2.close();
		displayPortfolio2();
	}
	else {
		setBalance(getBalance() - val);
		string line2 = "Withdraw\t" + to_string(val) + "\t" + to_string(getBalance()) + "\t" + getDate() + "\t" + getTime();
		ofstream myfile2;
		myfile2.open("bank_transaction_history.txt", ios_base::app);
		myfile2 << line2 << endl;
		myfile2.close();
	}
}

double bankAccount::validInput(double x, bool y) {
begin:



	if (x < 0) {
		cout << "Please enter a positive number: ";
		cin >> x;
		goto begin;
	}

	if (y) {

		if ((getBalance() - x) < 0) {
			cout << "Insufficient funds. Enter a valid withdrawl amount: " << endl;
			cin >> x;
			goto begin;

		}
	}
	return x;

}

void bankAccount::BankTrans() {
	cout << "Action\t\tAmount\t\tCash Balance\tDate\t\tTime" << endl;
	ifstream file("bank_transaction_history.txt");
	string line;
	while (getline(file, line))
	{
		cout << line << endl;
	}
	file.close();

}

void bankAccount::displayPortfolio2() {

	createStock2();
	double TotalPort = 0;
	cout << "Cash Balance = $ " << getBalance() << endl << endl;
	cout << "Symbol\tCompany\t\t\t\tNumber\tPrice\tTotal" << endl;
	int pricing = 0;
	for (int i = 0; i < numOfStock; i++) {
		pricing = stockCost2(currentList[i].symbol);
		cout << currentList[i].symbol << "\t" << currentList[i].company << "\t\t" << currentList[i].shares << "\t" << pricing << "\t" << pricing*currentList[i].shares << endl;
		TotalPort = pricing*currentList[i].shares + TotalPort;
	}

	cout << endl << "Total Portolio Value: " << (TotalPort + getBalance()) << endl;
}

double bankAccount::stockCost2(string sys) {

	int index = 0;

	createStock2();

	for (int j = 0; j < 35; j++) {
		if (portfolio[j].symbol == sys) {
			index = j;
			break;
		}
	}

	return portfolio[index].stockPrice;

}

void bankAccount::createStock2() {
	vector <string> tokens;

	portfolio.clear();

	srand(unsigned(time(NULL)));
	int num = rand() % 4 + 1;
	string name = "stock" + to_string(num) + ".txt";
	ifstream file(name);
	string line;
	while (getline(file, line)) {
		string delim = "\t";
		for (int i = 0; i < 3; i++) {
			if (i == 2) {
				line = line.substr(line.rfind(delim) + 1, string::npos);
			}
			tokens.push_back(line.substr(0, line.find(delim)));
			line = line.substr(line.find(delim) + 1, string::npos);
		}
	}
	for (int i = 0; i < 35; i++) {
		string tempsym;
		string tempcomp;
		double tempprice;
		tempsym = tokens[3 * i];
		tempcomp = tokens[(3 * i) + 1];
		tempprice = stod(tokens[(3 * i) + 2]);
		portfolio.push_back({ tempsym,tempcomp,tempprice });
	}
	file.close();

}

