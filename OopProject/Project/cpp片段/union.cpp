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