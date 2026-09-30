#pragma once
#include<iostream>
#include"clsInputValidate.h"
#include"clsScreen.h"
#include"clsBankClient.h"
using namespace std;

class clsWithdrawScreen:protected clsScreen
{
private:
	static void _PrintClient(clsBankClient& client)
	{
		cout << "\nInfo:";
		cout << "\n___________________";
		cout << "\nFirstName: " << client.FirstName;
		cout << "\nLastName : " << client.LastName;
		cout << "\nFull Name: " << client.FullName();
		cout << "\nEmail    : " << client.Email;
		cout << "\nPhone    : " << client.Phone;
		cout << "\nAcc-Number: " << client.AccountNumber();
		cout << "\nPincode  : " << client.PinCode;
		cout << "\nAcc-Balance: " << client.AccountBalance;
		cout << "\n___________________\n";
	}
	static string _ReadAccountNumber()
	{
		cout << "\nPlease enter account number: ";
		return clsInputValidate::ReadString();

	}
	
public:
	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("\t  Withdraw Screen");
		string AccountNumber = _ReadAccountNumber();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount number isn't existed ,try another one.. ";
			AccountNumber = _ReadAccountNumber();
		}
		clsBankClient client = clsBankClient::Find(AccountNumber);
		_PrintClient(client);
		cout << "\nEnter the amount you want to withdraw: ";
		double amount = clsInputValidate::ReadNumber<float>();

		cout << "\nAre you sure you want withdraw " << amount << " [Y|N] ";
		char answer = 'n';
		cin >> answer;
		if (tolower(answer) == 'y')
		{
			if (client.Withdraw(amount))
			{
				cout << "\nAmount Added successfully :) ";
				cout << "\nYour balance now is " << client.AccountBalance<<endl;
			}
			else
			{
				cout << "\nCannot withdraw, Insufficient balance.";
				cout << "\nyour balance is " << client.AccountBalance<<endl; ;

			}
		}
		else
		{
			cout << "\nOperation cancelled.\n";
		}
	}
};

