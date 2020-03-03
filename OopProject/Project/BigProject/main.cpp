#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include "sql_server.h"

using namespace std;
//#define TEST
void setConsoleColor(ConsoleTextColor textColor = WHITE, ConsoleBackGroundColor backgroundColor = _BLACK)
{
	//STD_ERROR_HANDLE;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, textColor | backgroundColor);
}
void setColor() {
	string bc, tc;
	cout << "Hello, Please select the textcolor you like :" << endl;
	cout << "******************************************" << endl;
	cout << "**" << "       1\t\t RED        " << "              **" << endl;
	cout << "**" << "       2\t\t GREEN      " << "              **" << endl;
	cout << "**" << "       3\t\t BLUE       " << "              **" << endl;
	cout << "**" << "       4\t\t YELLOW     " << "              **" << endl;
	cout << "**" << "       5\t\t PURPLE     " << "              **" << endl;
	cout << "**" << "       6\t\t CYAN       " << "              **" << endl;
	cout << "**" << "       7\t\t DEFAULT    " << "              **" << endl;
	cout << "******************************************" << endl;
	cout << "Enter the corresponding ID for the color :" << endl;

	int c;
	cin >> c;
	switch (c) {
	case 1:
		setConsoleColor(RED);
		break;
	case 2:
		setConsoleColor(GREEN);
		break;
	case 3:
		setConsoleColor(BLUE);
		break;
	case 4:
		setConsoleColor(YELLOW);
		break;
	case 5:
		setConsoleColor(PURPLE);
		break;
	case 6:
		setConsoleColor(CYAN);
		break;
	case 7:
		setConsoleColor(WHITE);
		break;
	default:
		setConsoleColor(BLACK);
	}
}
string readFileIntoString(string filename)
{
	ifstream ifile(filename);
	if (!ifile) {
		return "Notfound";
	}
	string tmp;
	/*ostringstream buf;
	char ch;
	while (buf && ifile.get(ch))
		buf.put(ch);
	*/
	getline(ifile, tmp);
	ifile.close();
	return tmp;
}
int main(int argc, const char* argv[]) {
#ifndef TEST
	setColor();
	cout << "Please enter user's name:";
	string id;
	cin >> id;
	string a = readFileIntoString("code"+id+".txt");
	if (a == "Notfound") {
		cout << "No current user name exists. Create a new one? Enter Y or N\n";
		char c;
		cin >> c;
		if (c == 'y'||c=='Y') {
			ofstream fout("code" + id + ".txt");
			string tmp;
			cout << "Enter your new password:";
			cin >> tmp;
			fout << tmp << "\n";
		}
		else if (c == 'n'||c=='N') {
			return 0;
		}
		else {
			cout << "Invalid" << endl;
			return 0;
		}
	}
	else {
		//找到了用户名
		bool checked = false;
		cout << "Mysql found. Enter password:";
		int cnt = 5;
		while (!checked) {
			string temp;
			cin >> temp;
			if (a != temp) {
				cnt--;
				if (cnt <= 0) {
					cout << "Wrong code. Quitting......";
					return 0;
				}
				cout << "Wrong code. You have "<<cnt<<" times left. Enter again:";
				continue;
			}
			checked = true;
		}
	}
	sql_server mysql;                           //mysql中储存若干database
	mysql.start("code" + id + ".txt");
	mysql.restart("code" + id + ".txt");                              //start
#endif
#ifdef TEST
	while (true) {
		sql_server mysql;
		string id;
		cout << "Enter Test point #";
		cin >> id;
		if (id == "exit"||id=="114514") {
			return 0;
		}
		std::ofstream testout("TestPoint" + id);
		std::streambuf* oldbuf = std::cout.rdbuf(testout.rdbuf());
		mysql.start();
		mysql.start();
		std::cout.rdbuf(oldbuf);
	}
#endif
	return 0;
}
