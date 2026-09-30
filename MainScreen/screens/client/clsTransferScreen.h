#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsPerson.h"
#include"clsBankClient.h"
#include"Global.h"
#include<iomanip>
using namespace std;

class clsTransferScreen :protected clsScreen
{
private:
	static void _PrintClientCard(clsBankClient& client)
	{
		cout << " \n\t\tClient Card";

		cout << "\n---------------------------------\n";;

		cout << "\nFull Name: " << client.AccountNumber();
		cout << "\nAcc.Number: " << client.FullName();
		cout << "\nBalance: " << client.AccountBalance << endl;
	}
	static string _ReadAccNumber()
	{
		string AccNum = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccNum))
		{
			cout << "\nAccount Number isn't Existed !,Enter another one: ";
			 AccNum = clsInputValidate::ReadString();

		}
		return AccNum;
	}
	static float _ReadAmount(clsBankClient& SourceDestination)
	{
		cout << "\nEnter Transfer Amount: ";
		float amount = clsInputValidate::ReadNumber<float>();
		while (amount > SourceDestination.AccountBalance)
		{
			cout << "\nAmount exceeds your balance! Enter another amount: ";
			amount = clsInputValidate::ReadNumber<float>();

		}
		return amount;
	}

public:
	static void ShowTransferScreen()

	{
		_DrawScreenHeader("\t Transfer Screen");

		cout << "\nEnter Account Number you want Transfer From: ";
		clsBankClient FromClient = (clsBankClient::Find(_ReadAccNumber()));
		_PrintClientCard(FromClient);

		cout << "\nEnter Account Number you want Transfer To: ";
		clsBankClient ToClient = (clsBankClient::Find(_ReadAccNumber()));
		_PrintClientCard(ToClient);

		float amount = _ReadAmount(FromClient);
		cout << "\nAre you sure you want to perform this transaction? Y|N  ";
		char answer = 'n';
		cin >> answer;
		if(tolower(answer=='y'))
		{
			if (FromClient.Transfer(ToClient, amount))
			{
				cout << "Transfer Done Successfully :) \n";
				_PrintClientCard(FromClient);
				_PrintClientCard(ToClient);
			}
			else
			{
				cout << "\nTransfer Fsiled :(";
			}
		}

		

	}
};