

#include <stdio.h>
# include <windows.h>
# include <vector>
# include <fstream>
# include <iomanip>
# include <math.h>
# include <string>

# include <time.h>
#include "stockAccount.h"


	stockAccount::stockAccount() : bankAccount() {
}

void stockAccount::menu() {
	bool flag = true;
	int selection = 0;
	char test[256];

	while (flag) {
		cout << "\nPlease select an option" << endl
			<< "\t1. Display current price for a stock symbol" << endl
			<< "\t2. Buy stock" << endl
			<< "\t3. Sell stock" << endl
			<< "\t4. Display current portfolio" << endl
			<< "\t5. Display transaction history" << endl
			<< "\t6. Return to previous menu" << endl;

		cout << "\tYour selection: ";

		cin.getline(test, 256);
		cout << test << endl;
		selection = atoi(test);




		switch (selection) {
		case 1: {
			char line[256];
			cin.getline(line, 256);
			string symbol(line);
			stockPrice(symbol);
			break;
		}
		case 2: {
			char line[256];
			cin.getline(line, 256);
			string symbol(line); 

			vector <string> tokens;

			char delim = ' ';

			for (int i = 0; i < 3; i++) // making 3 tokens
			{
				if (i == 2) { // handling newline character
					symbol = symbol.substr(symbol.rfind(delim) + 1, string::npos);

				}
				tokens.push_back(symbol.substr(0, symbol.find(delim)));
				symbol = symbol.substr(symbol.find(delim) + 1, string::npos);
			}

			symbol = tokens[0];
			int numShare = stoi(tokens[1]);
			double price = stod(tokens[2]);

			buyStock(symbol, numShare, price);
			break;
		}
		case 3: {
			char line[256];
			cin.getline(line, 256);
	
			string symbol(line); // CONVERT TO STRING SO YOU CAN USE THE CODE SNIPPET IN THE PREVIOUS INSTRUCTION

			vector <string> tokens;

			char delim = ' ';

			for (int i = 0; i < 3; i++) // making 3 tokens
			{
				if (i == 2) { // handling newline character
					symbol = symbol.substr(symbol.rfind(delim) + 1, string::npos);

				}
				tokens.push_back(symbol.substr(0, symbol.find(delim)));
				symbol = symbol.substr(symbol.find(delim) + 1, string::npos);
			}


			
			symbol = tokens[0];
			int numShare = stoi(tokens[1]);
			double price = stod(tokens[2]);


			sellStock(symbol, numShare, price);
			break;
		}
		case 4:
			displayPortfolio();
			break;
		case 5:
			StockTrans();
			break;
		case 6:
			cout << endl << endl;
			flag = false;
			break;
		default:
			break;
		}
	}
}

void stockAccount::stockPrice(string symbol) {

	bool b = 1;
	cout << endl << "Enter stock symbol for checking price: " << symbol << endl << endl;
	createStock();
	for (int x = 0; x < 35; x++) {
		if (symbol == portfolio[x].symbol) {
			cout << portfolio[x].symbol << "    " << portfolio[x].company << "    " << portfolio[x].stockPrice << "    ";
			cout << getTime() << endl;
			b = 0;
			break;
		}
	}
	if (b) {
		cout << "Symbol Not Found";
	}

}


void stockAccount::buyStock(string symbol, int numShare, double price) {
	cout << endl << endl << "\tEnter buy options: " << symbol << " " << numShare << " " << price << endl << endl;
	int index = 0;
	bool check2 = 0;
	int index2 = 0;
	createStock();
	bool check = 0;
	for (int j = 0; j < 35; j++) {
		if (portfolio[j].symbol == symbol) {
			index = j;
			check = 1;
			break;
		}
	}
	if (price < portfolio[index].stockPrice || (price*numShare)>getBalance() || !check) {
		cout << "Cannot process transaction" << endl;
	}
	else {
		withdraw(portfolio[index].stockPrice*numShare, 0);//fix
		string line = "Buy\t\t" + symbol + "\t" + to_string(numShare) + "\t\t" + to_string(portfolio[index].stockPrice) + "\t" + getTime();
		ofstream myfile;
		myfile.open("stock_transaction_history.txt", ios_base::app);
		myfile << line << endl;
		myfile.close();
		for (int j = 0; j < numOfStock; j++) {
			if (currentList[j].symbol == symbol) {
				index2 = j;
				check2 = 1;
				break;
			}
		}
		if (check2) {
			currentList[index2].shares += numShare;
		}
		else {
			currentList.push_back({ portfolio[index].symbol,portfolio[index].company,0,numShare });
			numOfStock++;
		}
		string line2 = "Withdraw\t" + to_string(portfolio[index].stockPrice*numShare) + "\t\t" + to_string(getBalance()) + "\t\t" + getDate() + "\t\t" + getTime();
		ofstream myfile2;
		myfile2.open("bank_transaction_history.txt", ios_base::app);
		myfile2 << line2 << endl;
		myfile2.close();
	}
}

void stockAccount::sellStock(string symbol, int numShare, double price) {
	cout << endl << "Enter selling options: " << symbol << " " << numShare << " " << price << endl << endl;

	int index = 0;
	int index2 = 0;
	bool check = 0;
	createStock();
	for (int j = 0; j < numOfStock; j++) { //issue
		if (currentList[j].symbol == symbol) {
			index = j;
			check = 1;
			break;
		}
	}
	for (int j = 0; j < 35; j++) {
		if (portfolio[j].symbol == symbol) {
			index2 = j;
			break;
		}
	}

	if (!check) {
		goto block;
	}

	if (price > portfolio[index2].stockPrice || numShare > currentList[index].shares || !check) {
	block:
		cout << "Cannot process transaction" << endl;
	}
	else {
		deposit(portfolio[index2].stockPrice*numShare, 0);
		string line = "Sell\t" + symbol + "\t" + to_string(numShare) + "\t\t" + to_string(portfolio[index2].stockPrice) + "\t" + getTime();
		ofstream myfile;
		myfile.open("stock_transaction_history.txt", ios_base::app);
		myfile << line << endl;
		myfile.close();
		if (currentList[index].shares == numShare) {
			currentList.erase(currentList.begin() + index);
			numOfStock--;
		}
		else {
			currentList[index].shares -= numShare;
		}
		string line2 = "Deposit\t\t" + to_string(portfolio[index2].stockPrice*numShare) + "\t\t" + to_string(getBalance()) + "\t\t" + getDate() + "\t\t" + getTime();
		ofstream myfile2;
		myfile2.open("bank_transaction_history.txt", ios_base::app);
		myfile2 << line2 << endl;
		myfile2.close();

	}

}


void stockAccount::displayPortfolio() {

	createStock();
	double TotalPort = 0;
	cout << endl << "Cash Balance = $ " << getBalance() << endl << endl;
	cout << "Symbol\tCompany\t\t\t\tNumber\tPrice\tTotal" << endl;
	int pricing = 0;
	for (int i = 0; i < numOfStock; i++) {
		pricing = stockCost(currentList[i].symbol);
		cout << currentList[i].symbol << "\t" << currentList[i].company << "\t\t" << currentList[i].shares << "\t" << pricing << "\t" << pricing*currentList[i].shares << endl;
		TotalPort = pricing*currentList[i].shares + TotalPort;
	}

	cout << endl << "Total Portolio Value: " << (TotalPort + getBalance()) << endl;
}

double stockAccount::stockCost(string sys) {

	int index = 0;

	createStock();

	for (int j = 0; j < 35; j++) {
		if (portfolio[j].symbol == sys) {
			index = j;
			break;
		}
	}

	return portfolio[index].stockPrice;

}

void stockAccount::StockTrans() {
	ifstream file("stock_transaction_history.txt");
	string line;
	cout << endl << "Action\tSymbol\t\t\t\tShares\tPrice\tTime" << endl;
	while (getline(file, line))
	{
		cout << line << endl;
	}
	file.close();

}

void stockAccount::createStock() {
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

