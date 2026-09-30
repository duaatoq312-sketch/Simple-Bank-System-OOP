#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsBankClient.h"
using namespace std;
class clsFindClientScreen:protected clsScreen
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

	static void ShowFindClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
		{
			return;
		}
		_DrawScreenHeader("\tFind Client Screen");
		cout << "\nEnter account number:  ";
		string AccNum = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccNum))
		{
			cout << "\nClient Not existed , try another one";
			AccNum = clsInputValidate::ReadString();
		}
		clsBankClient client = clsBankClient::Find(AccNum);
		if (!client.IsEmpty())
			{ cout << "\nClient is found :)\n";}
		else
		{
			cout << "\nClient was not found :(\n";
		}
		_PrintClient(client);

	}
};

