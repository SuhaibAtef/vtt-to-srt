#include <iostream>
#include <string>
#include <vector>
//File names Library 
#include <windows.h>
//reading files 
#include <fstream> 
using namespace std;

//make the code easier to read 
typedef vector<string> stringvec;

//get file directory names to adjest (stolen from the internet 
void read_directory(const string& name, stringvec& v)
{
	string pattern(name);
	pattern.append("\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;

	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			string s = data.cFileName;
			//if(s.find(".vtt")!=string::npos)//extension 
			if (s.substr(s.find_last_of(".") + 1) == "vtt")
				v.push_back(s);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
}

int main()
{
	stringvec v;
	string ln;
	read_directory(".", v);
	for (stringvec::iterator it = v.begin(); it != v.end(); ++it) {
		ifstream inFile;
		string out = (*it).substr(0, (*it).length() - 4) + ".srt";
		ofstream outfile(out);


		inFile.open(*it);
		if (!inFile) {
			cout << "Unable to open file";
			exit(1); // terminate with error
		}
		int counter = 1, flag = 3;
		inFile.ignore(7, '\n');
		inFile.ignore(7, '\n');
		while (getline(inFile, ln)) {
			if (flag % 3 == 0) {
				outfile << counter++ << endl;

			}
			outfile << ln.c_str() << endl;
			flag++;
			//haha
		}

		inFile.close();
		outfile.close();

		cout << "Done with :" << *it << endl;
	}


	system("Pause");
	return 0;
}