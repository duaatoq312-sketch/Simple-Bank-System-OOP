#pragma once
#include<iostream>
#include<iomanip>
#include"clsScreen.h"
#include"clsBankClient.h"
using namespace std;

class clsTransferLogScreen :protected clsScreen
{
private:
	static void _PrintTableHeader()
	{
		cout << setw(8) << left << "" << "\n\t----------------"
			<< "----------------------------------------------------------------------------\n";
		cout << setw(8) << left << "" << "| " << setw(20) << left << "Date/Time";
		cout << "| " << setw(10) << left << "s.Acct";
		cout << "| " << setw(10) << left << "d.Acct";
		cout << "| " << setw(10) << left << "Amount";
		cout << "| " << setw(10) << left << "s.Balance";
		cout << "| " << setw(10) << left << "d.Balance";
		cout << "| " << setw(10) << left << "User";

		cout << setw(8) << left << "" << "\n\t-------------------------"
			<< "-------------------------------------------------------------------\n";

	}
	static void _PrintLogsLine(clsBankClient::stTransferLogRecord record, string sep = "#//#")
	{
		cout <<setw(8) << left << "" <<"| "<< setw(20) << left << record.DateTime;
		cout << "| "<<setw(10) << left << record.s_Acct;
		cout << "| "<<setw(10) << left << record.d_Acct;
		cout << "| "<<setw(10) << left << record.Amount;
		cout << "| "<<setw(10) << left << record.s_Balance;
		cout << "| "<<setw(10) << left << record.d_Balance;
		cout << "| "<<setw(10) << left << record.user;
	}
public:
	static void ShowTransferLogScreen()
	{
		vector<clsBankClient::stTransferLogRecord>vLogs = clsBankClient::GetTransferLogList();

		string Title = "\t Transfer Log Screen";
		string subtitle = "\t (" + to_string(vLogs.size()) + ") Record(s).";
		_DrawScreenHeader(Title, subtitle);
		_PrintTableHeader();
		for (clsBankClient::stTransferLogRecord& log : vLogs)
		{
			_PrintLogsLine(log);
			cout << endl;
		}
		cout << setw(8) << left << "" << "\n\t-------------------------"
			<< "-------------------------------------------------------------------\n";
	}
};

