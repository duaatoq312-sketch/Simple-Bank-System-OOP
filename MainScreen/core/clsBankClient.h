#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;
class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

	}

	static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{

		string stClientRecord = "";
		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += Client.PinCode + Seperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;

	}

	static  vector <clsBankClient> _LoadClientsDataFromFile()
	{

		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;


			while (getline(MyFile, Line))
			{

				clsBankClient Client = _ConvertLinetoClientObject(Line);

				vClients.push_back(Client);
			}

			MyFile.close();

		}

		return vClients;

	}

	static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
	{

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);//overwrite

		string DataLine;

		if (MyFile.is_open())
		{

			for (clsBankClient C : vClients)
			{
				if (C.MarkedForDeleted() == false)
				{
					//we only write records that are not marked for delete.  
					DataLine = _ConverClientObjectToLine(C);
					MyFile << DataLine << endl;

				}

			}

			MyFile.close();

		}

	}

	void _Update()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}

		}

		_SaveCleintsDataToFile(_vClients);

	}

	void _AddNew()
	{

		_AddDataLineToFile(_ConverClientObjectToLine(*this));
	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
	//////////////////////////////////////////////////////////
	struct stTransferLogRecord;

	string _PrepareTransferLogLine(float amount,clsBankClient DestinationClient,string user, string sep = "#//#")
	{
		string record=clsDate::GetSystemDateTimeToString() + sep
			+ _AccountNumber + sep
			+ DestinationClient.AccountNumber() + sep
			+ to_string(amount) + sep
			+ to_string(_AccountBalance) + sep
			+ to_string(DestinationClient.AccountBalance) + sep
			+ user;
		return record;
	}
	
	static stTransferLogRecord _ConvertLineToRecord(string line)
	{
		stTransferLogRecord log;
		vector<string>vString = clsString::Split(line, "#//#");
		log.DateTime = vString[0];
		log.s_Acct = vString[1];
		log.d_Acct = vString[2];
		log.Amount = stof(vString[3]);
		log.s_Balance = stof(vString[4]);
		log.d_Balance = stof(vString[5]);
		log.user = vString[6];
		return log;
	}
	void _RegisterTransferLog(float Amount, clsBankClient ToClient, string user)
	{
		string log = _PrepareTransferLogLine(Amount, ToClient, user);
		
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << log << endl;

			MyFile.close();
		}

	}
public:


	clsBankClient(enMode Mode, string FirstName, string LastName,
		string Email, string Phone, string AccountNumber, string PinCode,
		float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone)

	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;

	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDeleted()
	{
		return _MarkedForDelete;
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;


	static clsBankClient Find(string AccountNumber)
	{


		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}

			}

			MyFile.close();

		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{



		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}

			}

			MyFile.close();

		}
		return _GetEmptyClientObject();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };
	enSaveResults Save()
	{

		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{

				return enSaveResults::svFaildEmptyObject;

			}

		}

		case enMode::UpdateMode:
		{


			_Update();

			return enSaveResults::svSucceeded;

			break;
		}

		case enMode::AddNewMode:
		{
			//This will add new record to file or database
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();

				//We need to set the mode to update after add new
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}

			break;
		}
		}



	}

	static bool IsClientExist(string AccountNumber)
	{

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		return (!Client1.IsEmpty());
	}

	bool Delete()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkedForDelete = true;
				break;
			}

		}

		_SaveCleintsDataToFile(_vClients);

		*this = _GetEmptyClientObject();

		return true;

	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}


	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
			return true;
		}

	}


	static double GetTotalBalances()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		double TotalBalances = 0;

		for (clsBankClient Client : vClients)
		{

			TotalBalances += Client.AccountBalance;
		}

		return TotalBalances;
	}
	bool Transfer(clsBankClient& toclient, double amount)
	{
		if (_AccountBalance >= amount)
		{
			Withdraw(amount);
			toclient.Deposit(amount);
			_RegisterTransferLog(amount,toclient,CurrentUser.GetUeserName());
			return true;
		}
		else
		{
			return false;
		}
	}
	struct stTransferLogRecord
	{
		string DateTime;
		string s_Acct;
		string d_Acct;
		float Amount;
		float s_Balance;
		float d_Balance;
		string user;
	};
	static vector<stTransferLogRecord>GetTransferLogList()
	{
		fstream File;
		vector <stTransferLogRecord>vLogs;
		File.open("TransferLog.txt", ios::in);
		if (File.is_open())
		{
			string line;
			while (getline(File, line))
			{
				vLogs.push_back(_ConvertLineToRecord(line));
			}
			File.close();
		}
		return vLogs;
	}
	

};

