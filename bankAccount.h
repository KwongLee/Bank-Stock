

#ifndef bankAccount_h
#define bankAccount_h

#include <iostream>
#include <fstream>
# include <windows.h>
# include "Account.h"

	class bankAccount : public Account {
	public:
		bankAccount();
		void bankmenu();
		void deposit(double, bool);
		void withdraw(double, bool);
		double validInput(double, bool);
		void BankTrans();

		void createStock2();
		void displayPortfolio2();
		double stockCost2(string);

	private:
};

#endif /* bankAccount_h */
