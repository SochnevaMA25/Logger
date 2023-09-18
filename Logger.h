#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <shared_mutex>
#include <stdio.h>

using namespace std;

class Logger
{
private:
	ofstream outfile;
	ifstream infile;
	shared_mutex mutex;
public:
	Logger()
	{
		outfile.open("Log.txt", ios::app);
		infile.open("Log.txt");
	}
	~Logger()
	{
		outfile.close();
	}
	void fopen(string data)
	{
		mutex.lock();
		if (!outfile.is_open())
		{
			cout << "file not open!" << endl;
			return;
		}
		outfile << data << endl;
		mutex.unlock();
	}
	void fread()
	{
		mutex.lock();
		if (!infile)
		{
			cout << "file not open!" << endl;
			return;
		}
		string s;
		while (getline(infile, s))
		{
			cout << s << endl;
			s += "\n";
			cout << s << endl; 
		}
		mutex.unlock();
	}
};