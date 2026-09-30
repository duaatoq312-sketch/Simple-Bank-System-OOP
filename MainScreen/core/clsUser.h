#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"clsPerson.h"
#include"clsUtil.h"
#include"clsString.h"
#include"clsDate.h"

using namespace std;

class clsUser :public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	string _UserName;
	int _Permissions;
	string _Password;
	enMode _Mode;
	bool _MarkForDelete = false;
	struct stLogsRegisterRecord;
	struct stLogsRegisterRecord;

	static clsUser _GetEmptyUserObject()
	{
		return clsUser("", "", "", "", "", "", 0, enMode::EmptyMode);
	}
	static clsUser _ConvertLineToUserObject(string line, string sep = "#//#")
	{
		vector<string> vString = clsString::Split(line, sep);
		return clsUser(vString[0], vString[1], vString[2], vString[3], vString[4],clsUtil::DecryptText(vString[5]), stoi(vString[6]), enMode::UpdateMode);
	}

	static string _ConvertUserObjetToLine(clsUser& user, string sep = "#//#")
	{
		string line = "";
		line += user.FirstName + sep;
		line += user.LastName + sep;
		line += user.Email + sep;
		line += user.Phone + sep;
		line += user.UserName + sep;
		line += clsUtil::EncryptText(user.Password) + sep;
		line += to_string(user.Permissions);
		return line;
	}
	void AddDataLineToFile(string line)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << line << endl;
			MyFile.close();
		}
	}

	static void _SaveUsersDataToFile(vector<clsUser>& vUsers)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);
		if (MyFile.is_open())
		{
			string line;
			for (clsUser& u : vUsers)
			{
				if (u._MarkForDelete == false)
				{
					line = _ConvertUserObjetToLine(u);
					MyFile << line << endl;
				}
			}
			MyFile.close();
		}
	}

	static vector<clsUser>_LoadUsersFromFile()
	{
		vector<clsUser>vUsers;
		fstream MyFile;

		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string line;

			while (getline(MyFile, line))
			{
				clsUser user = _ConvertLineToUserObject(line);
				vUsers.push_back(user);
			}
			MyFile.close();
		}
		return vUsers;
	}
	void _UpdateUser()
	{
		vector<clsUser>vUsers = _LoadUsersFromFile();
		for (clsUser& u : vUsers)
		{
			if (u.UserName == this->UserName)
			{
				u = *this;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);
	}
	void _AddNew()
	{
		AddDataLineToFile(_ConvertUserObjetToLine(*this));
	}
	string _PrepareLoginRegister(string sep = "#//#")
	{
		string TimeLine = clsDate::GetSystemDateTimeToString()
			+ sep + _UserName + sep
			+ clsUtil::EncryptText(_Password)+sep + to_string(_Permissions);
		return TimeLine;
	}
	static stLogsRegisterRecord _ConvertLineToRegisterRcord(string line, string sep = "#//#")
	{
		stLogsRegisterRecord record;
		vector<string>vString = clsString::Split(line, sep);
		record.Time = vString[0];
		record.Username = vString[1];
		record.password = clsUtil::DecryptText(vString[2]);
		record.permission = stoi(vString[3]);
		return record;
	}

public:
	enum enPermissions { eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64, pLogsRecord = 128 };

	clsUser(string FirstName, string LastName, string Email, string Phone,
		string UserName, string Password, int Permissions, enMode Mode)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}
	struct stLogsRegisterRecord
	{
		string Username;
		string password;
		string Time;
		int permission = 0;
	};
	void SetUserName(string username)
	{
		_UserName = username;
	}
	string GetUeserName()
	{
		return _UserName;
	}
	__declspec(property(put = SetUserName, get = GetUeserName))string UserName;


	void SetPassword(string password)
	{
		_Password = password;
	}
	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(put = SetPassword, get = GetPassword))string Password;

	void SetPermissions(int perm)
	{
		_Permissions = perm;
	}
	int GetPermissions()
	{
		return _Permissions;
	}
	__declspec(property(put = SetPermissions, get = GetPermissions))int Permissions;

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	static vector<clsUser>GetUsersList()
	{
		return _LoadUsersFromFile();
	}
	static bool IsUserExist(string username)
	{
		clsUser user = Find(username);
		return (!user.IsEmpty());
	}
	static clsUser Find(string username, string password)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
			{
				clsUser user = _ConvertLineToUserObject(line);
				if (user.UserName == username && user.Password == password)
				{
					MyFile.close();
					return user;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();
	}

	static clsUser Find(string username)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
			{
				clsUser user = _ConvertLineToUserObject(line);
				if (user.UserName == username)
				{
					MyFile.close();
					return user;
				}
			}
			MyFile.close();
		}
		return _GetEmptyUserObject();

	}
	enum enSaveResults { svSuccessfully = 1, svFailedExisted = 2, svFailedIsEmpty = 3 };
	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::UpdateMode:
		{
			_UpdateUser();
			return enSaveResults::svSuccessfully;
			break;
		}
		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{
				return enSaveResults::svFailedIsEmpty;
				break;
			}
		}
		case enMode::AddNewMode:
		{
			if (!IsUserExist(_UserName))
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSuccessfully;
			}
			else
			{
				return svFailedExisted;
			}
			break;
		}

		}
	};

	bool MarkedForDeleting()
	{
		return _MarkForDelete;
	}

	bool Delete()
	{
		vector<clsUser>vUsers = _LoadUsersFromFile();
		for (clsUser& u : vUsers)
		{
			if (u.UserName == _UserName)
			{
				u._MarkForDelete = true;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);
		*this = _GetEmptyUserObject();
		return true;
	}
	static clsUser GetAddNewUserObject(string username)
	{
		if (!IsUserExist(username))
			return clsUser("", "", "", "", username, "", 0, enMode::AddNewMode);

	}
	bool CheckAccessPermission(enPermissions permission)
	{
		if (this->_Permissions == -1)
			return true;

		if ((this->_Permissions & permission) == permission)
			return true;
		else
			return false;
	}

	void RegisterLogin()
	{
		fstream File;
		string DateTimeLine = _PrepareLoginRegister();
		File.open("Logins Register.txt", ios::out | ios::app);
		if (File.is_open())
		{
			File << DateTimeLine << endl;
			File.close();
		}
	}

	static	vector<stLogsRegisterRecord> GetLoginRegisterRecordList()
	{
		fstream File;
		vector<stLogsRegisterRecord>vRecordsList;
		File.open("Logins Register.txt", ios::in);
		if (File.is_open())
		{
			string line;
			while (getline(File, line))
			{
				vRecordsList.push_back(_ConvertLineToRegisterRcord(line));
			}
			File.close();
			return vRecordsList;
		}
	}
};

