#pragma once
#include<iostream>
#include<string>
#include"clsCurrency.h"
#include"clsScreen.h"
#include"clsInputValidate.h"
using namespace std;

class clsUpdateRateScreen : protected clsScreen
{
private:
	static void _PrintCurrencyCard(clsCurrency& currency)
	{
		cout << "\n---------------------------\n";
		cout << "Country: " << currency.Country()
			<< "\nCode:" << currency.Code()
			<< "\nName:" << currency.Name()
			<< "\nRate($): " << currency.Rate();
		cout << "\n---------------------------\n";

	}

	static float _ReadNewRate()
	{

		cout << "\nEnter New Rate: ";
		float NewRate = 0;
		NewRate = clsInputValidate::ReadNumber<float>();
		return NewRate;

	}
public:
	static void ShowUpdateCurrencyScreen()
	{
		system("cls");
		_DrawScreenHeader("\t Update Currency Screen");

		cout << "\nPlease Enter Currency Code: ";
		string code = "";
		code = clsInputValidate::ReadString();
		while(!clsCurrency::IsExisted(code))
		{
			cout << "\nCode not existed , try again: ";
			code = clsInputValidate::ReadString();

		}
		clsCurrency currency = clsCurrency::FindByCode(code);
		_PrintCurrencyCard(currency);
		cout << "\nAre you sure you want to update rate? [Y|N]: ";
		char answer='n';
		cin >> answer;
		if (tolower(answer) == 'y')
		{
			cout << "\n   Update currency Rate";
			cout << "\n---------------------------\n";
			currency.UpdateRate(_ReadNewRate());
			cout << "\nCurrency has been updated successfully :)\n";
			_PrintCurrencyCard(currency);
		}

	}
};

