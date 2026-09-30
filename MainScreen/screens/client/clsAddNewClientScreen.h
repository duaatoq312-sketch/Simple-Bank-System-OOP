#pragma once
#include<iostream>
#include"clsScreen.h"
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include"clsUser.h"
#include<iomanip>

using namespace std;

class clsAddNewClientScreen :protected clsScreen
{
private:
	static void ReadNewClientInfo(clsBankClient& client)
	{
		cout << "\nEnter first name: ";
		client.FirstName = clsInputValidate::ReadString();
		cout << "\nEnter Last name: ";
		client.LastName = clsInputValidate::ReadString();
		cout << "\nEnter phone: ";
		client.Phone = clsInputValidate::ReadString();
		cout << "\nEnter Email: ";
		client.Email = clsInputValidate::ReadString();
		cout << "\nEnter Pincode: ";
		client.PinCode = clsInputValidate::ReadString();
		cout << "\nEnter account balance: ";
		client.AccountBalance = clsInputValidate::ReadNumber<float>();
	}

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

	static void AddNewClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
		{
			return;
		}

		//A class body defines members; it doesn't execute ordinary statements.
		//so i only write this function (_Draw..)inside a function not inside the class body directly
		_DrawScreenHeader("\tAdd New Client Screen");
		cout << "\nEnter account number: ";
		string AccNum = clsInputValidate::ReadString();
		while (clsBankClient::IsClientExist(AccNum))
		{
			cout << "\nClient is already existed, try another one..\n";
			AccNum = clsInputValidate::ReadString();
		}
		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccNum);
		ReadNewClientInfo(NewClient);
		clsBankClient::enSaveResults result = NewClient.Save();

		switch (result)
		{
		case clsBankClient::enSaveResults::svSucceeded:
		{
			cout << "\nClient Saved successfully..";
			_PrintClient(NewClient);
			break;
		}

		case clsBankClient::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError account was not saved because it's Empty";
			break;
		}

		case clsBankClient::enSaveResults::svFaildAccountNumberExists:
		{
			cout << "\nError , account was not saved because account number is used!\n";
			break;
		}

		}

	}

};

