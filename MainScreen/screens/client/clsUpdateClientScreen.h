#pragma once
#include"clsScreen.h"
#include<iostream>
#include"clsBankClient.h"
#include"clsInputValidate.h"
using namespace std;

class clsUpdateClientScreen:protected clsScreen
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

	static void _UpdateClientInfo(clsBankClient& client)
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
public:
	static void ShowUpdateClientScreen()
	{
		_DrawScreenHeader("\tUpdate Client Screen");
		cout << "\nEnter account number:  ";
		string AccNum = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccNum))
		{
			cout << "\nClient Not existed , try another one";
		    AccNum = clsInputValidate::ReadString();
		}
		clsBankClient client = clsBankClient::Find(AccNum);
		_PrintClient(client);
		cout << "\nAre you sure you want to update : [y|n] ";
		char answer='n';
		cin >> answer;
		if(tolower(answer)=='y')
		{
			_UpdateClientInfo(client);
			clsBankClient::enSaveResults result = client.Save();
			switch (result)
			{
			case clsBankClient::enSaveResults::svSucceeded:
				cout << "\nClient updated successfully \n";
				_PrintClient(client);
				break;
			case clsBankClient::enSaveResults::svFaildEmptyObject:
				cout << "\nError , object is empty..";
				break;
			}
		}
		
	}

};

