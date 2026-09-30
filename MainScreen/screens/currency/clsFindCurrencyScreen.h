#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsString.h"
#include"clsInputValidate.h"
#include"clsCurrency.h"
using namespace std;

class clsFindCurrencyScreen :protected clsScreen
{
private:

	static void _PrintCurrencyCard(clsCurrency& currency)
	{
		cout << "\n------------------------------------------------\n";
		cout << "Country: " << currency.Country()
			<< "\nCode: " << currency.Code()
			<< "\nName: " << currency.Name()
			<< "\nRate(1$): " << currency.Rate();
		cout << "\n------------------------------------------------\n";

	}
	static void _ShowResult(clsCurrency currency)
	{
		if (!currency.IsEmpty())
		{
			cout << "\nCurrency is founded :)";
			_PrintCurrencyCard(currency);

		}
		else
		{
			cout << "\nCurrency not founded!";
		}
	}


public:

	static void ShowFindCurrencyScreen()
	{
		system("cls");
		_DrawScreenHeader("\tFind Currency Screen");

		cout << "Find by: [1]Code or [2]Country : ";
		short method = clsInputValidate::ReadNumberBetween<short>(1, 2);

		if (method == 1)
		{
			cout << "\npleas Enter Currency Code: ";
			string code = clsInputValidate::ReadString();
			_ShowResult(clsCurrency::FindByCode(code));
		}
		else
		{
			cout << "\npleas Enter Country: ";
			string country = clsInputValidate::ReadString();
			_ShowResult(clsCurrency::FindByCountry(country));
		}
	}
};

