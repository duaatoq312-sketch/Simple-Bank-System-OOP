#pragma once
#include<iostream>
#include"Global.h"
#include"clsMainScreen.h"
using namespace std;

class clsLoginScreen :protected clsScreen
{
private:
	
	static bool _Login()
	{
		string username, password;
		bool LoginFailed = false;
		short LoginFailedCount = 0;
		do {
			if (LoginFailed)
			{
				LoginFailedCount++;
				cout << "\nInvalid username/password ! \n\n";
				cout << "\nYou have " << (3 - LoginFailedCount) << " trials to login\n";

			}

			if (LoginFailedCount == 3)
			{
				cout << "\nYou're locked after 3 failed trials\n";
				return false;
			}

			cout << "\n\nEnter Username: ";
			cin >> username;
			cout << "\nEnter Password: ";
			cin >> password;
			CurrentUser = clsUser::Find(username, password);
			LoginFailed = CurrentUser.IsEmpty();
			
		} while (LoginFailed); 
		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenue();

		return true;
	}
	
public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t  Login Screen");
		return _Login();
	}
	
};

