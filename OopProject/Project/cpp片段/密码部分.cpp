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