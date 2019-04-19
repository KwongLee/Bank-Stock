#include "Account.h"
# include <windows.h>
# include <math.h>
# include <fstream>
# include <string>



Account::Account() {
	cashBalance = 10000;
}

double Account::getBalance() {

	return cashBalance;
}

void Account::setBalance(double cash) {

	cashBalance = cash;

}

string Account::getDate() {
#pragma warning(default: 4996)
	string all;
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);

	all = to_string(now->tm_mon + 1) + "/" + to_string(now->tm_mday) + "/" + to_string(now->tm_year + 1900);

	return all;
#pragma warning(default: 4996)

}



string Account::getTime() {

	time_t timer;
	struct tm y2k = { 0 };
	double seconds;

	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

	time(&timer);

	seconds = difftime(timer, mktime(&y2k));

	int tot_seconds_today = remainder(seconds, 86400);
	if (tot_seconds_today < 0)
		tot_seconds_today += 86400;

	int hours_today = (floor(tot_seconds_today / 3600));
	int count_hour_digits = 0;

	while (hours_today > 0)
	{
		count_hour_digits++;
		hours_today = hours_today / 10;
	}

	string hours;
	string minute;
	string second;
	hours_today = (floor(tot_seconds_today / 3600));
	if (count_hour_digits == 1)
	{
		hours = "0" + to_string(hours_today + 1);
	}
	else {
		hours = to_string(hours_today + 1);
	}

	int minutes_today = floor((tot_seconds_today - hours_today * 3600) / 60);
	int count_minute_digits = 0;
	while (minutes_today > 0)
	{
		count_minute_digits++;
		minutes_today = minutes_today / 10;
	}

	minutes_today = floor((tot_seconds_today - hours_today * 3600) / 60);
	if (count_minute_digits == 1)
	{
		minute = "0" + to_string(minutes_today);
	}
	else {
		minute = to_string(minutes_today);
	}

	int seconds_today = abs((tot_seconds_today - hours_today * 3600 - minutes_today * 60));
	int count_seconds_digits = 0;
	while (seconds_today > 0)
	{
		count_seconds_digits++;
		seconds_today = seconds_today / 10;
	}

	seconds_today = abs((tot_seconds_today - hours_today * 3600 - minutes_today * 60));
	if (count_seconds_digits == 1)
	{
		second = "0" + to_string(seconds_today);
	}
	else {
		second = to_string(seconds_today);
	}
	string all = hours + ":" + minute + ":" + second;

	return all;
}
