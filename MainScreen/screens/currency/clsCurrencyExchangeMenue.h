#pragma once
#include<iostream>
#include"clsInputValidate.h"
#include"clsScreen.h"
#include<iomanip>
#include"Global.h"
#include"clsCurrencyListScreen.h"
#include"clsFindCurrencyScreen.h"
#include"clsUpdateRateScreen.h"
#include"clsCurrencyCalaculatorScreen.h"

using namespace std;

class clsCurrencyExchangeMenue :protected clsScreen
{
private:
	enum enMenueOptions { eCurrencyList = 1, eFind = 2, eUpdateRate = 3, eCalculator = 4, eMainMenue = 5 };

	static short ReadMenueOption()
	{
		short option = clsInputValidate::ReadNumberBetween<short>(1, 5);
		return option;
	}
	static void GoBackToCurrencyExchangeMenue()
	{
		cout << "\n\nPress any key to go back to currency menue...";
		system("pause>0");
		ShowCurrencyExchangeMainMenue();
	}
	static void _ShowCurrencyListScreen()
	{
		clsCurrencyListScreen::ShowCurrenciesListScreen();
	}
	static void _ShowUpdateRateScreen()
	{

		clsUpdateRateScreen::ShowUpdateCurrencyScreen();
	}
	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}
	static void _ShowCalculatorScreen()
	{
		clsCurrencyCalaculatorScreen::ShowCalculatorScreen();
	}
	static void PerformMenueOption(enMenueOptions option)
	{
		switch (option)
		{
		case eCurrencyList:
		{
			_ShowCurrencyListScreen();
			GoBackToCurrencyExchangeMenue();
			break;
		}
		case eFind:
		{
			_ShowFindCurrencyScreen();
			GoBackToCurrencyExchangeMenue();
			break;
		}
		case eUpdateRate:
		{
			_ShowUpdateRateScreen();
			GoBackToCurrencyExchangeMenue();
			break;
		}
		case eCalculator:
		{
			_ShowCalculatorScreen();
			GoBackToCurrencyExchangeMenue();
			break;
		}
		case eMainMenue:
		{

		}

		}
	}
public:
	static void ShowCurrencyExchangeMainMenue()
	{
		system("cls");
		_DrawScreenHeader("\t  Currency Exchange Main Screen");
		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t\Currency Exchange Menue\n";

		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "\t[1]List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2]Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3]Update Rate.\n";
		cout << setw(37) << left << "" << "\t[4]Currency Calculator.\n";
		cout << setw(37) << left << "" << "\t[5]Main Menue.\n";
		cout << setw(37) << left << "" << "=============================================\n";
		cout << setw(37) << left << "" << "Choose what do you want to do ?[1 to 5]\n";
		PerformMenueOption(enMenueOptions(ReadMenueOption()));
	}
};

