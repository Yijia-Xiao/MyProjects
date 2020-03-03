#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include "sql_server.h"
#include "SQL.h"
#include "Database.h"
using namespace std;
void addtime(string a, int n) {
	int hour, min, sec;
	hour = stoi(a.substr(0, 2));
	min = stoi(a.substr(3, 2));
	sec = stoi(a.substr(6, 2));
	//cout << hour << " " << min << " " << sec << endl;
	if (n < 0||min>60||sec>60) {
		cout << "Invalid" << endl;
		return;
	}
	else if (n == 0) {
		cout << a << endl;
		return;
	}
	while (n > 0) {
		while (n >= 3600) {
			hour++;
			n -= 3600;
		}
		while (n >= 60) {
			min++;
			n -= 60;
			if (min == 60) {
				hour++;
				min -= 60;
			}
		}
		if (n >= 60 - sec) {
			sec = n + sec - 60;
			min++;
			n = 0;
			if (min == 60) {
				hour++;
				min -= 60;
			}
		}
		else {
			sec += n;
			n = 0;
		}
	}
	cout << hour << ":" << min << ":" << sec << endl;
}

void adddate(string a, int n) {
	if (a[0] == '-') {
		cout << "Invalid" << endl;
		return;
	}
	int year, month, day;
	year=stoi(a.substr(0,4));
	month = stoi(a.substr(5,2));
	day=stoi(a.substr(8,9));
	if (n < 0) {
		cout << "Invalid" << endl;
		return;
	}
	else if (n == 0) {
		cout << a << endl;
		return;
	}
	while (n > 0) {
		if (month > 13) {
			cout << "Invalid" << endl;
			return;
		}
		else {
			bool run = false;
			if ((year / 4 == 0 && year / 100 != 0) || (year / 400 == 0)) run = true;
			if (month == 1||month==3||month==5|| month == 7|| month == 8|| month == 10|| month == 12) {
				if (day > 31) {
					cout << "Invalid" << endl;
					return;
				}
				if (n <= 31 - day) {
					day += n;
					cout << year << "-" << month << "-" << day << endl;
					return;
				}
				n -= (31 - day);
				day = 0;
				month++;
				if (month == 13) {
					month -= 12;
					year++;
					if ((year / 4 == 0 && year / 100 != 0) || (year / 400 == 0)) {
						run = true;
					}
					else run = false;
				}
			}
			else if (month == 4 || month == 6 || month == 9 || month == 11) {
				if (day > 30) {
					cout << "Invalid" << endl;
					return;
				}
				if (n <= 30 - day) {
					day += n;
					cout << year << "-" << month << "-" << day << endl;
					return;
				}
				n -= (30 - day);
				day = 0;
				month++;
			}
			else {
				if (run == true) {
					if (day > 29) {
						cout << "Invalid" << endl;
						return;
					}
					if (n <= 29 - day) {
						day += n;
						cout << year << "-" << month << "-" << day << endl;
						return;
					}
					n -= (29 - day);
					day = 0;
					month++;
				}
				else {
					if (day > 28) {
						cout << "Invalid" << endl;
						return;
					}
					if (n <= 28 - day) {
						day += n;
						cout << year << "-" << month << "-" << day << endl;
						return;
					}
					n -= (28 - day);
					day = 0;
					month++;
				}
				
			}
		}
	}
}
void sql_server::start() 
{
	//Test模式专用函数
	
	
	string temp;
	while (true) { //判断文件是否到末尾 利用了重载的bool运算符
		getline(cin, temp);
		if (temp == "quit" || temp == "")                  //若为quit
		{
			return;                                 //程序结束
		}
		else                                        //否则
		{
			SQL sql(temp);                          //创建sql对象，对指令进行处理
			operate(sql);                           //对处理后的sql指令进行相应操作
		}
	}
}
void sql_server::start(string a)
{

	while (true)
	{
		ifstream ifs(a);
		if (!ifs) {
			sql_server::restart(a);
			return;
		}
		string tmp;
		getline(ifs, tmp);
		if (ifs.eof()) {
			sql_server::restart(a);
			return;
		}
		while (!ifs.eof()) { //判断文件是否到末尾 利用了重载的bool运算符
			string temp;
			getline(ifs, temp);
			if (temp == "quit" || temp == "")                  //若为quit
			{
				sql_server::restart(a);
				return;                                 //程序结束
			}
			else                                        //否则
			{
				SQL sql(temp);                          //创建sql对象，对指令进行处理
				operate(sql);                           //对处理后的sql指令进行相应操作
			}
		}
		ifs.close();
	}
}

void sql_server::restart(string a) {
	ofstream ofs(a,ios::app);
	while (true)
	{
		//cout<<"mysql>";
		string temp;
		getline(cin, temp); 
		if (temp == "quit" || temp == "")        
		{
			return;             
		}
		else                             
		{
			SQL sql(temp);
			if (sql[0] != "SELECT" && sql[0] != "SHOW") {
				ofs << temp <<"\n";
			}
			operate(sql);            
		}
	}
}

void sql_server::operate(SQL& sql)
{
	if (sql[0] == "USE")                               //如果是use操作，将迭代器指向数据库名称为sql[1]的pair
	{
		current = db.find(sql[1]);
	}
	else if (sql[1] == "DATABASE")                     //如果是database操作
	{
		if (sql[0] == "CREATE")                        //如果是create操作
		{
			Database temp;                          //建立新的数据库
			db[sql[2]] = temp;                        //将pair:(sql[2], new database)加入db map
			current = db.find(sql[2]);                //将迭代器current指向new database
			//cout<<"create database "<<sql[2]<<endl;
		}
		else if (sql[0] == "DROP")                     //如果是drop操作
		{
			//cout<<"drop database "<<sql[2]<<endl;
			db.erase(sql[2]);                       //从map中删除名为sql[2]的database
		}
	}
	else if (sql[0] == "SHOW" && sql[1] == "DATABASES")    //如果是show databases的操作
	{
		cout << "Database\n";
		for (auto it = db.begin(); it != db.end(); it++)   //遍历db
		{
			cout << it->first << endl;                  //输出所有的databases的name
		}
	}
	else if (sql[0] == "SHOW" && sql[1] == "TABLES")       //如果是show table的操作
	{
		cout << "Tables_in_" << current->first << endl;
		current->second.show_tables();              //调用show_tables()输出current所指的database的所有tables
	}
	else if (sql[0] == "SELECT" && sql[1] == "LN") {
		cout << log(stod(sql[2])) << endl;
	}
	else if (sql[0] == "SELECT" && sql[1] == "SQRT") {
		cout << sqrt(stoi(sql[2])) << endl;
	}
	else if (sql[0] == "SELECT" && sql[1] == "ABS") {
		cout << fabs(stod(sql[2])) << endl;
	}
	else if (sql[0] == "SELECT" && sql[1] == "SIN") {
		cout << sin(stod(sql[2])) << endl;
	}
	else if (sql[0] == "SELECT" && sql[1] == "TAN") {
		cout << tan(stod(sql[2])) << endl;
	}
	else if (sql[0] == "SELECT" && sql[1] == "COS") {
		cout << cos(stod(sql[2])) << endl;
	}
	else if (sql[0] == "SELECT" && sql[1] == "ASIN") {
		cout << asin(stod(sql[2])) << endl;
	}
	else if (sql[0] == "SELECT" && sql[1] == "COT") {
		cout << cos(stod(sql[2])) * 1.0 / sin(stod(sql[2])) << endl;
	}
	else if (sql[0] == "SELECT" && sql[1] == "CEILING") {
		cout << ceil(stod(sql[2])) << endl;
	}
	else if (sql[0] == "SELECT" && sql[1] == "ACOS") {
		cout << acos(stod(sql[2])) << endl;
	}
	else if (sql[0] == "SELECT" && sql[1] == "ATAN") {
		cout << atan(stod(sql[2])) << endl;
	}
	else if (sql[0] == "SELECT" && sql[1] == "POWER") {
		cout << pow(stod(sql[2]), stod(sql[3])) << endl;
	}
	else if (sql[0] == "SELECT" && sql[1] == "SPACE") {
		for (int i = 0; i < stoi(sql[2]); i++) {
			cout << " ";
		}
		cout << endl;
	}
	else if (sql[0] == "SELECT" && sql[1] == "ROUND") {
		cout << round(stod(sql[2])) << endl;
	}
	else if (sql[0] == "SELECT" && sql[1] == "FLOOR") {
		cout << floor(stod(sql[2])) << endl;
	}
	else if (sql[0] == "SELECT" && sql[1] == "PI") {
		cout << pi << endl;
	}
	else if (sql[0] == "SELECT" && sql[1] == "DEGREES") {
		cout << stod(sql[2]) * 180.0 / pi << endl;
	}
	else if (sql[0] == "SELECT" && sql[1] == "EXP") {
		cout << pow(e, stod(sql[2])) << endl;
	}
	else if (sql[0] == "SELECT" && sql[2] == "DIV") {
		cout << stod(sql[1]) / stod(sql[3]) << endl;
	}
	else if (sql[0] == "SELECT" && sql[1] == "ADDDATE") {
		string a = sql[2];
		a = a.substr(1, a.length() - 2);
		int n = stoi(sql[4]);
		adddate(a, n);
	}
	else if (sql[0] == "SELECT" && sql[1] == "ADDTIME") {
		string a = sql[2];
		//string b = sql[3];
		a = a.substr(1, a.length() - 2);
		//b = b.substr(0, b.length() - 1);
		int n = stoi(sql[3]);
		addtime(a, n);
	}
	else if (sql[2] == "FROM" && sql[4] == "UNION") {
		//这里两个select的东西以及order by的也是同一个attribute name
		if (sql[5] == "ALL") {
			//不删除重复数据
			vector<string> all;
			int flag1 = current->second.tables[sql[3]].pri();
			int flag2 = current->second.tables[sql[9]].pri();//主键
			int sign1 = current->second.tables[sql[3]].show_loca(sql[1]);
			int sign2 = current->second.tables[sql[9]].show_loca(sql[7]);//要找的
			for (int i = 0; i < current->second.tables[sql[3]].rnum_f(); i++) {
				all.push_back(current->second.tables[sql[3]].record_f()[i * current->second.tables[sql[3]].cnum_f() + sign1]);
			}
			for (int i = 0; i < current->second.tables[sql[9]].rnum_f(); i++) {
				all.push_back(current->second.tables[sql[9]].record_f()[i * current->second.tables[sql[9]].cnum_f() + sign2]);
			}
			if (all.size() == 0) {
				return;
			}
			sort(all.begin(), all.end());
			cout << sql[1] << endl;
			for (auto it : all) cout << it << endl;
		}
		else if (sql[5] == "SELECT") {
			//删除重复数据
			int flag1 = current->second.tables[sql[3]].pri();
			int flag2 = current->second.tables[sql[8]].pri();
			int sign1 = current->second.tables[sql[3]].show_loca(sql[1]);
			int sign2 = current->second.tables[sql[8]].show_loca(sql[6]);
			vector<string> all;
			for (int i = 0; i < current->second.tables[sql[3]].rnum_f(); i++) {
				all.push_back(current->second.tables[sql[3]].record_f()[i * current->second.tables[sql[3]].cnum_f() + sign1]);
			}
			for (int i = 0; i < current->second.tables[sql[8]].rnum_f(); i++) {
				all.push_back(current->second.tables[sql[8]].record_f()[i * current->second.tables[sql[8]].cnum_f() + sign2]);
			}
			if (all.size() == 0) {
				return;
			}
			sort(all.begin(), all.end());
			cout << sql[1] << endl << all[0] << endl;
			for (int i = 1; i < all.size(); i++) {
				if (all[i] != all[i - 1]) cout << all[i] << endl;
			}
		}
	}
	else
	{
		current->second.operate(sql);               //否则，不是database级操作，将sql语句传入current所指的pair中的database类的operate(SQL&)函数中
	}
}