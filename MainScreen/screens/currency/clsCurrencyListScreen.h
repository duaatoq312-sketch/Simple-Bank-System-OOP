#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"Global.h"
#include"clsCurrency.h"
using namespace std;
class clsCurrencyListScreen :clsScreen
{
private:
	static void _TableHeader()
	{
		cout << setw(8) << left << "" << "\n\t-------------------------------------------------------------------------------------------------\n";
		cout << setw(8) << left << "" << "| ";
		cout << setw(30) << left << "Country";
		cout << "| " << setw(15) << left << "Code";
		cout << "| " << setw(30) << left << "Name";
		cout << "| " << setw(15) << left << "Rate/(1$)";

		cout << setw(8) << left << "" << "\n\t-------------------------------------------------------------------------------------------------\n";

	}
	static void _PrintCurrency( clsCurrency& currency)
	{
		cout << setw(8) << left << "" << "| ";
		cout << setw(30) << left << currency.Code();
		cout << "| " << setw(15) << left << currency.Country();
		cout << "| " << setw(30) << left << currency.Name();
		cout << "| " << setw(15) << left << currency.Rate();

	}


public:
	static void ShowCurrenciesListScreen()
	{
		system("cls");
		vector<clsCurrency>vCurrencies = clsCurrency::GetCurrenciesList();
		string subtitle = " \t(" + to_string(vCurrencies.size()) + ") Currencies";
		_DrawScreenHeader(" \tCurrencies List Screen", subtitle);
		_TableHeader();
		for (clsCurrency& c : vCurrencies)
		{
			_PrintCurrency(c);
			cout << endl;
		}
		cout << setw(8) << left << "" << "\n\t-------------------------------------------------------------------------------------------------\n";

	}
};

