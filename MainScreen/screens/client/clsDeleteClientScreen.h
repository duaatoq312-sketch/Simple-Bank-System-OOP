#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include<iomanip>
using namespace std;

class clsDeleteClientScreen:protected clsScreen
{
private:

	static void _PrintClient(clsBankClient client)
	{
		// i removed print func from clsBankClient 
		//to seperate UI related code from object
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

public:

	static void ShowDeleteClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
		{
			return;
		}
		_DrawScreenHeader("\tDelete Client Screen");
		string AccNum;
		cout << "\nEnter account number: ";
		AccNum = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccNum))
		{
			cout << "This account number isn't existed , Try another one : ";

			AccNum = clsInputValidate::ReadString();
		}
		clsBankClient client = clsBankClient::Find(AccNum);
		_PrintClient(client);
		char answer = 'Y';
		cout << "\nAre you sure you wanna delete client ?   [Y|N] ";
		cin >> answer;
		if (tolower(answer) == 'y')
		{
			if (client.Delete())
			{
				cout << "\nClient deleted successfully ";
				_PrintClient(client);
			}
			else
			{
				cout << "\nError,client was Not deleted";
			}
		}

	}
};

