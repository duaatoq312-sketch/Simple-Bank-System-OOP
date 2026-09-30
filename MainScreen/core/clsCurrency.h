#pragma once
#include<iostream>
#include"clsString.h"
#include<vector>
#include<fstream>
#include<filesystem>
#include<string>
using namespace std;

class clsCurrency
{
private:

	enum enMode { eEmpty = 0, eUpdate = 1 };
	string _Code;
	string _Country;
	string _Name;
	float _Rate = 0.0;
	enMode _Mode;


	static clsCurrency _ConvertLineToCurrency(string line, string sep = "#//#")
	{
		vector<string>vString = clsString::Split(line, sep);

		return clsCurrency(enMode::eUpdate, vString[0],
			vString[1], vString[2], stof(vString[3]));
	}

	static vector<clsCurrency> _LoadCurrenciesFromFile()
	{
		fstream File;
		vector<clsCurrency>vCurrencies;
		cout << filesystem::current_path() << endl;
		File.open("Currencies.txt", ios::in);
		if (File.is_open())
		{
			string line;
			while (getline(File, line))
			{
				vCurrencies.push_back(_ConvertLineToCurrency(line));
			}
		}
		File.close();
		return vCurrencies;
	}
	static string _ConvertObjectToLine(clsCurrency& Currency, string sep = "#//#")
	{
		string line = "";
		line += Currency.Country() + sep;
		line += Currency.Code() + sep;
		line += Currency.Name() + sep;
		line += to_string(Currency.Rate());
		return line;
	}
	static void _SaveCurrencyDateToFile(vector<clsCurrency>& vCurrencies)
	{
		fstream File;
		File.open("Currencies.txt", ios::out);
		if (File.is_open())
		{
			for (clsCurrency& currency : vCurrencies)
			{
				string line = _ConvertObjectToLine(currency);
				File << line << endl;
			}
			File.close();
		}
	}
	static clsCurrency _GetEmptyObject()
	{
		return clsCurrency(enMode::eEmpty, "", "", "", 0.0);
	}
	void _Update()
	{
		vector<clsCurrency>vCurrencies = _LoadCurrenciesFromFile();
		for (clsCurrency& currency : vCurrencies)
		{
			if (currency.Country() == _Country)
			{
				currency = *this;
				break;
			}
		}
		_SaveCurrencyDateToFile(vCurrencies);
	}

public:

	clsCurrency(enMode mode, string country, string code, string name, float rate)
	{
		_Mode = mode;
		_Code = code;
		_Country = country;
		_Name = name;
		_Rate = rate;
	};

	string Country()
	{
		return _Country;
	}
	string Name()
	{
		return _Name;
	}
	string Code()
	{
		return _Code;
	}
	float Rate()
	{
		return _Rate;
	}
	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();

	}
	bool IsEmpty()
	{
		return (_Mode == enMode::eEmpty);
	}
	static clsCurrency FindByCode(string code)
	{
		code = clsString::UpperAllString(code);
		fstream File;
		File.open("Currencies.txt", ios::in);
		if (File.is_open())
		{
			string line;
			while (getline(File, line))
			{
				clsCurrency currency = _ConvertLineToCurrency(line);
				if (clsString::UpperAllString(currency.Code()) == code)
				{
					File.close();
					return currency;
				}
			}
			File.close();
		}
		return _GetEmptyObject();
	}
	static clsCurrency FindByCountry(string country)
	{
		country = clsString::UpperAllString(country);
		fstream File;
		File.open("Currencies.txt", ios::in);
		if (File.is_open())
		{
			string line;
			while (getline(File, line))
			{
				clsCurrency currency = _ConvertLineToCurrency(line);
				if (clsString::UpperAllString(currency.Country()) == country)
				{
					File.close();
					return currency;
				}
			}
			File.close();
		}

		return _GetEmptyObject();
	}
	static bool IsExisted(string code)
	{
		clsCurrency currency = FindByCode(code);
		return !currency.IsEmpty();
	}

	static vector<clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrenciesFromFile();
	}

	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / Rate());
	}
	float ConvertToOtherCurrency(clsCurrency currency2, float amount)
	{
		float AmountInUSD = ConvertToUSD(amount);
		if (currency2.Code() == "USD")
		{
			return AmountInUSD;
		}
		return (float)(AmountInUSD * currency2.Rate());
	}
};

	