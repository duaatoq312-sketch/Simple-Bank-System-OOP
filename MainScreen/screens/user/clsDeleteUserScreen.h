#pragma once
#include<iostream>
using namespace std;
#include"clsScreen.h"
#include "clsUser.h"

class clsDeleteUserScreen :protected clsScreen
{
private:
	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";

	}

public:
	static void ShowDeleteUserScreen()
	{
		_DrawScreenHeader("\t  Delete User Screen");
		cout << "\nEnter a UserName: ";
		string username = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(username))
		{
			cout << "\nUser not existed , try another one : ";
			string AccNum = clsInputValidate::ReadString();

		}
		clsUser user = clsUser::Find(username);
		_PrintUser(user);
		char answer = 'n';
		cout << "\nAre you sure you want delete user ?y/n";
		cin >> answer;
		if (tolower(answer) == 'y')
		{
			if (user.Delete())
			{
				cout << "\nUser deleted successfully :)";
				_PrintUser(user);

			}
			else
			{
				cout << "\nError , user not deleted";
			}
		
		}
	}
};

