#pragma once
#include<iostream>
#include"clsScreen.h"
#include "clsUser.h"

class clsFindUserScreen:protected clsScreen
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
	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("\t  Find User Screen");
		cout << "\nEnter a UserName: ";
		string username = clsInputValidate::ReadString();
		while (!clsUser::IsUserExist(username))
		{
			cout << "\nUser not existed , try another one : ";
			string AccNum = clsInputValidate::ReadString();

		};
		clsUser user = clsUser::Find(username);
		if (user.IsEmpty())
		{
			cout << "\nUser was not Found :(";
		}
		else
		{
			cout << "\nUser was Found :)";
		}
		_PrintUser(user);
	}
};

