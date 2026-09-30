#pragma once
#include<iostream>
#include"clsUser.h"
#include"Global.h"
#include"clsDate.h"

using namespace std;
class clsScreen
{
protected:

	static void _DrawScreenHeader(string Title, string Subtitle = "")
	{
		cout << "\t\t\t\t\t______________________________________";
		cout << "\n\n\t\t\t\t\t  " << Title;
		if (Subtitle != "")
		{
			cout << "\n\t\t\t\t\t  " << Subtitle;
		}
		cout << "\n\t\t\t\t\t______________________________________\n";
		cout << "\n\t\t\t\t\tUser: " << CurrentUser.FullName();
		cout << "\t\tDate:"<<clsDate::DateToString(clsDate())<<"\n\n";
		 //clsDate::GetSystemDate();
	}
	static bool CheckAccessRights(clsUser::enPermissions permission)
	{
		if (!CurrentUser.CheckAccessPermission(permission))
		{
			cout << "\t\t\t\t\t______________________________________";
			cout << "\n\n\t\t\t\t\t  Access Denied ! Contact your Admin..\n" ;

			cout << "\t\t\t\t\t______________________________________\n";
			return false;
		}
		else
		{
			return true;
		}
	}
	static bool CheckAccessPermission(clsUser::enPermissions permission)
	{
		if (CurrentUser.Permissions == -1)
			return true;

		if ((CurrentUser.Permissions & permission) == permission)
			return true;
		else
			return false;
	}

};

