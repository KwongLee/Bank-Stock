

#ifndef stockAccount_h
#define stockAccount_h

# include <iostream>
# include <windows.h>
# include "bankAccount.h"
# include "Account.h"


	using namespace std;

class stockAccount : public bankAccount {
public:
	stockAccount();
	void menu();
	void stockPrice(string);
	void buyStock(string, int, double);
	void sellStock(string, int, double);
	void displayPortfolio();
	double stockCost(string);
	void StockTrans();
	void createStock();

private:
};


#endif /* stockAccount_h */
