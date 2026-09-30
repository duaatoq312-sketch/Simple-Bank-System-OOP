#pragma once
#include<iostream>
#include<iomanip>
#include<vector>
#include"clsUser.h"
#include"clsScreen.h"
#include"Global.h"
using namespace std;
class clsLoginRegisterScreen:protected clsScreen
{
private:

	static void _PrintLogsLine(clsUser::stLogsRegisterRecord record, string sep = "#//#")
	{
		cout << setw(8) << left << "" << "| " << setw(30) << left << record.Time;
		cout << "| " << setw(25) << left << record.Username;
		cout<< "| " << setw(15) << left << record.password;
		cout<< "| " << setw(15) << left << record.permission;
	}
	static void _PrintLogsTableHeader()
	{
		cout << setw(8) << left << "" << "\n\t----------------"
			<< "----------------------------------------------------------------------------\n";
		cout << setw(8) << left << "" << "| " << setw(30) << left << "Date/Time";
		cout << "| " << setw(25) << left << "Username";
		cout << "| " << setw(15) << left << "Password";
		cout << "| " << setw(15) << left << "Permissions";
		cout << setw(8) << left << "" << "\n\t-------------------------"
			<< "-------------------------------------------------------------------\n";

	}

public:
	static void ShowLogsRegisterScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pLogsRecord))
		{
			return;
		}
		vector<clsUser::stLogsRegisterRecord>vLogs = clsUser::GetLoginRegisterRecordList();

		string Title = "\t  Logs Register Screen";
		string subtitle = "\t\t(" + to_string(vLogs.size()) + ") Record(s).";

		_DrawScreenHeader(Title,subtitle);

		_PrintLogsTableHeader();

		if (vLogs.size() != 0)
		{
			for (clsUser::stLogsRegisterRecord& log : vLogs)
			{
				_PrintLogsLine(log);
				cout << endl;
			}
			cout << setw(8) << left << "" << "\n\t----------------"
				<< "----------------------------------------------------------------------------\n";
		}
	 	else
		{
			cout << "\n\nNo logins yet";
		}
	}
};

