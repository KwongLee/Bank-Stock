
#ifndef Account_h
#define Account_h


# include <iostream>
# include <windows.h>
# include <math.h>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class Account {
public:
	Account();
	virtual void menu() = 0;
	double getBalance();
	void setBalance(double);
	string getTime();
	string getDate();

private:
	double cashBalance = 10000;

protected:

	int numOfStock = 0;

	struct Stock {
		string symbol;
		string company;
		double stockPrice;
		int shares;
	};

	vector <Stock> portfolio;
	vector <Stock> currentList;


};


#endif /* Account_hpp */