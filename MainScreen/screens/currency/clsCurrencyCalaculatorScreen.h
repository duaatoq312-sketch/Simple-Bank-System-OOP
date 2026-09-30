#pragma once
#include<iostream>
#include"clsInputValidate.h"
#include"clsScreen.h"
#include"clsCurrency.h"
using namespace std;

class clsCurrencyCalaculatorScreen :protected clsScreen
{
private:

	static  clsCurrency _ReadCurrency()
	{
		string code = "";
		code = clsInputValidate::ReadString();

		while (!clsCurrency::IsExisted(code))
		{
			cout << "\nCode is not in the system , Try again: ";
			code = clsInputValidate::ReadString();

		}
		return clsCurrency::FindByCode(code);
	}
	static float _ReadAmount()
	{
		cout << "\nEnter Amount to Exchange: ";
		float amount = 0;
		amount = clsInputValidate::ReadNumber<float>();
		return amount;
	}
	static void _PrintCurrencyCard(clsCurrency& currency,string title)
	{
		cout << "\n"<<title;
		cout << "\n---------------------------\n";
		cout << "Country: " << currency.Country()
			<< "\nCode:" << currency.Code()
			<< "\nName:" << currency.Name()
			<< "\nRate($): " << currency.Rate();
		cout << "\n---------------------------\n";

	}
	static void _PrintResults(clsCurrency From, clsCurrency To, float Amount)
	{
		_PrintCurrencyCard(From, "Convert From: ");
		cout << Amount << " " << From.Code() << " = "
			<< From.ConvertToUSD(Amount) << " USD\n";
		if (To.Code() == "USD")
		{
			return;
		}
		_PrintCurrencyCard(To, "Convert To : ");
		cout<< Amount << " " << From.Code() << " = "
			<< From.ConvertToOtherCurrency(To,Amount)<<" "<<To.Code();
	}
public:

	static void ShowCalculatorScreen()
	{
		char answer = 'n';
		do
		{
			system("cls");
			_DrawScreenHeader("\t Currency Calculator Screen");

			cout << "\nPlease Enter currency1 code : ";
			clsCurrency currency1 = _ReadCurrency();
			cout << "\nPleas Enter Currency2 : ";
			clsCurrency currency2 = _ReadCurrency();

			float Amount = _ReadAmount();
			
			_PrintResults(currency1,currency2,Amount);
		
		} while (answer == 'y' || answer == 'Y');
	}
};

