#pragma once
#include<iostream>
#include"clsScreen.h"
#include<iomanip>
#include<clsInputValidate.h>
#include"clsDepositScreen.h"
#include"clsWithdrawScreen.h"
#include"clsTotalBalancesScreen.h"
#include"clsTransferScreen.h"
#include"clsTransferLogScreen.h"

using namespace std;

class clsTransactionScreen :protected clsScreen
{
private:
	enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eTransfer=4, eTransferLog=5,eMainMenue = 6};
	static short ReadTransactionsMenueOption()
	{
		cout << setw(37) << left << "" << "\t\tChoose number [1-6]: ";
		short choice = clsInputValidate::ReadNumberBetween<int>(1, 6, "Enter number between 1 to 6");
		return choice;
	}
	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}
	static void _ShowWithdrawScreen()
	{
		clsWithdrawScreen::ShowWithdrawScreen();
	}
	static void _ShowTotalBalancesScreen()
	{
		clsTotalBalancesScreen::ShowTotalBalances();
	}
	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransferScreen();
	}
	static void _ShowTransferLogScreen()
	{
		clsTransferLogScreen::ShowTransferLogScreen();
	}
	static void _PerformTransactionsMenueOption(enTransactionsMenueOptions option)
	{
		system("cls");

		switch (option)
		{
		case enTransactionsMenueOptions::eDeposit:
		{
			_ShowDepositScreen();
			_GoBackToTransactionMenue();
			break;
		}
		case enTransactionsMenueOptions::eWithdraw:
		{
			_ShowWithdrawScreen();
			_GoBackToTransactionMenue();
			break;
		}
		case enTransactionsMenueOptions::eTotalBalances:
		{
			_ShowTotalBalancesScreen();
			_GoBackToTransactionMenue();
			break;
		}
		case enTransactionsMenueOptions::eTransfer:
		{
			_ShowTransferScreen();
			_GoBackToTransactionMenue();
			break;
		}
		case enTransactionsMenueOptions::eTransferLog:
		{
			_ShowTransferLogScreen();
			_GoBackToTransactionMenue();
			break;
		}

		case enTransactionsMenueOptions::eMainMenue:
		{

		}
		}
	}
		static  void _GoBackToTransactionMenue()
		{
			cout << setw(37) << left << "" << "\n\tPress any key to go back to Transactions Menue...\n";
			system("pause>0");
			ShowTransactionsMenue();
		}
public:

	static void ShowTransactionsMenue()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pTransactions))
		{
			return;
		}

		system("cls");
		_DrawScreenHeader("\t Transactions Screen");

		cout << setw(37) << left << "" << "--------------------------------------\n";
		cout << setw(37) << left << "" << "\t\tTransactions Menue \n";
		cout << setw(37) << left << "" << "--------------------------------------\n";
		cout << setw(37) << left << "" << "\t\t[1]Deposit.\n";
		cout << setw(37) << left << "" << "\t\t[2]Withdraw.\n";
		cout << setw(37) << left << "" << "\t\t[3]Total Balances.\n";
		cout << setw(37) << left << "" << "\t\t[4]Transfer.\n";
		cout << setw(37) << left << "" << "\t\t[5]Transfer Log..\n";
		cout << setw(37) << left << "" << "\t\t[6]Main Menue.\n";
		cout << setw(37) << left << "" << "--------------------------------------\n\n";

		_PerformTransactionsMenueOption(enTransactionsMenueOptions(ReadTransactionsMenueOption()));
	}

};

