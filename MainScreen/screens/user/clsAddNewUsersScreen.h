#pragma once
#include<iostream>
#include"clsScreen.h"
#include<iomanip>
#include "clsUser.h"

using namespace std;

class clsAddNewUsersScreen :protected clsScreen
{
private:
	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\nEnter FirstName: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password: ";
		User.Password = clsInputValidate::ReadString();

		cout << "\nEnter Permission: ";
		User.Permissions = _ReadPermissionsToSet();

	}

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

	static int _ReadPermissionsToSet()
	{
		int permission = 0;
		char answer = 'n';
		cout << "\nDo you want Full access to user? ";
		cin >> answer;
		if (tolower(answer) == 'y')
		{
			return -1;
		}

		cout << "\nDo you want to give access to : \n ";

		cout << "\nShow Client List? y/n? ";
		cin >> answer;
		if (tolower(answer) == 'y')
		{
			permission |= clsUser::enPermissions::pListClients;
		}
		cout << "\nAdd New Client? y/n? ";
		cin >> answer;
		if (tolower(answer) == 'y')
		{
			permission |= clsUser::enPermissions::pAddNewClient;
		}
		cout << "\nDelete Client? y/n? ";
		cin >> answer;
		if (tolower(answer) == 'y')
		{
			permission |= clsUser::enPermissions::pDeleteClient;
		}

		cout << "\nUpdate Client? y/n? ";
		cin >> answer;
		if (tolower(answer) == 'y')
		{
			permission |= clsUser::enPermissions::pUpdateClient;
		}
		cout << "\nFind Client? y/n? ";
		cin >> answer;
		if (tolower(answer) == 'y')
		{
			permission |= clsUser::enPermissions::pFindClient;
		}
		cout << "\nTransactions? y/n? ";
		cin >> answer;
		if (tolower(answer) == 'y')
		{
			permission |= clsUser::enPermissions::pTransactions;
		}
		cout << "\nManage Users? y/n? ";
		cin >> answer;
		if (tolower(answer) == 'y')
		{
			permission |= clsUser::enPermissions::pManageUsers;
		}
		cout << "\nShow Logins Register Record? y/n? ";
		cin >> answer;
		if (tolower(answer) == 'y')
		{
			permission |= clsUser::enPermissions::pLogsRecord;
		}
		return permission;
	}

public:
	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("\t  Add New User Screen");
		cout << "\nEnter a UserName: ";
		string username = clsInputValidate::ReadString();
		while (clsUser::IsUserExist(username))
		{
			cout << "User Already existed , try another one : ";
			string AccNum = clsInputValidate::ReadString();

		}
		clsUser user = clsUser::GetAddNewUserObject(username);
		_ReadUserInfo(user);
		clsUser::enSaveResults result = user.Save();
		switch (result)
		{
		case clsUser::enSaveResults::svSuccessfully:
		{
			cout << "\nNew user saved successfully :)";
			_PrintUser(user);
			break;
		}
		case clsUser::enSaveResults::svFailedExisted:
		{
			cout << "\nUser is already existed";
			break;
		}
		case clsUser::enSaveResults::svFailedIsEmpty:
			cout << "\nError User was not saved because it's Empty";
			break;
		}
	}

};

