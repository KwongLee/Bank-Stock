

# include <iostream>
# include <string>
# include <fstream>
# include <windows.h>
# include <ctime>
# include <iomanip>
# include "Account.h"
# include "stockAccount.h"
# include "bankAccount.h"
# include <vector>


	using namespace std;
	std::ofstream ofs;


int main() {


	cout << "Welcome to Account Management System.";
	stockAccount d2;
	cout << endl << endl;
	bool flag = true;
	int selection = 0;
	char test[256];
	while (flag) {

		cout << "Please select an account to access" << endl
			<< "\t1. Stock Portfolio Account" << endl
			<< "\t2. Bank Account" << endl
			<< "\t3. Exit" << endl
			<< "\tYour selection: ";

		cin.getline(test, 256);
		cout << test << endl;
		selection = atoi(test);





		switch (selection) {
		case 1:
			d2.menu();
			break;
		case 2:
			d2.bankmenu();
			break;
		case 3:
			ofs.open("stock_transaction_history.txt", ios::out | ios::trunc);
			ofs.close();
			ofs.open("bank_transaction_history.txt", ios::out | ios::trunc);
			ofs.close();
			flag = false;
			break;
		default:
			break;
		}
	}

	return 0;
}

