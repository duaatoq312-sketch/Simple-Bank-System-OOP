#pragma once
#include<iostream>
#include"clsScreen.h"
#include<iomanip>
#include "clsUser.h"

using namespace std;
class clsListUsersScreen :protected clsScreen
{
private:
	static void _PrintUserInfoLine(clsUser& User)
	{
		cout << setw(8) << left << "" << "| " << setw(12) << left << User.UserName;
		cout << "| " << setw(25) << left << User.FullName();
		cout << "| " << setw(12) << left << User.Phone;
		cout << "| " << setw(20) << left << User.Email;
		cout << "| " << setw(10) << left << User.Password;
		cout << "| " << setw(12) << left << User.Permissions;

	}

public:
	static void ShowUsersListScreen()
	{
		vector<clsUser>vUsers = clsUser::GetUsersList();

		string Title = "\tUsers List Screen";
		string subtitle = "\tUsers List (" + to_string(vUsers.size()) + ") User(s).";
		_DrawScreenHeader(Title, subtitle);
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
		cout << "| " << left << setw(25) << "Full Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Password";
		cout << "| " << left << setw(12) << "Permissions";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "______________________________________________\n" << endl;

		if (vUsers.size() == 0)
		{
			cout << "\nThere is no users yet in the file .";
		}
		else
		{
			for (clsUser& u : vUsers)
			{
				_PrintUserInfoLine(u);
				cout << endl;
			}
			cout << setw(8) << left << "" << "\n\t_______________________________________________________";
			cout << "______________________________________________\n" << endl;
		}

	}
};

