#pragma once
#include"clsScreen.h"
#include<iostream>
#include"clsInputValidate.h"
#include "clsBankClient.h"

using namespace std;
class clsDepositScreen:protected clsScreen
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
	static void ShowDepositScreen()
	{
		_DrawScreenHeader("\tDeposit Screen");
		string AccountNumber = _ReadAccountNumber();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount isn't existed try another one..\n";
			AccountNumber = _ReadAccountNumber();
		}
		clsBankClient client = clsBankClient::Find(AccountNumber);
		_PrintClient(client);
		cout << "\nEnter amount you want Deposit: ";
		double amount = clsInputValidate::ReadNumber<double>();
		cout << "\nAre you sure you want to deposite? [y|N] ";
		char answer = 'n';
		cin >> answer;
		if (tolower(answer)=='y')
		{
			client.Deposit(amount);
			cout << "\nAmount has been added successfully:)\n";
			cout << "\nYour balance now is : " << client.AccountBalance<<endl;
		}
		else
		{
			cout << "\nOperation has been cancelled.\n";
		}
	}
};

