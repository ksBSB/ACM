#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
typedef vector<string> VS;
const int manx = 1005;

int mv, N;
string str, word;

bool isletter (char ch) {
	if (ch >= 'a' && ch <= 'z')
		return true;
	if (ch >= 'A' && ch <= 'Z')
		return true;
	if (ch >= '0' && ch <= '9')
		return true;
	if (ch == '_')
		return true;
	return false;
}

int changeTonumber () {
	int ret = 0;
	for (int i = 0; i < word.size(); i++)
		ret = ret * 10 + word[i] - '0';
	return ret;
}
string getword () {
	string cur = "";
	while (isletter(str[mv]))
		cur = cur + str[mv++];
	mv--;
	return cur;
}

void gettoken () {

	if (mv == str.size()) {
		word = "";
		return;
	}

	while (str[mv] == ' ')
		mv++;

	switch (str[mv]) {
		case '.':
			word = ".";
			break;
		case '#':
			word = "#";
			break;
		case '>':
			word = ">";
			break;
		case '(':
			word = "(";
			break;
		case ')':
			word = ")";
			break;
		case '*':
			word = "*";
			break;
		default:
			word = getword();
			break;
	}
	mv++;
}

void putstring (string name, VS setid, VS setclass) {
	cout << "<" << name;

	if (setid.size() != 0) {
		cout << " id=\"" << setid[0];
		for (int i = 1; i < setid.size(); i++)
			cout << " " << setid[i];
		cout << "\"";
	}

	if (setclass.size() != 0) {
		cout << " class=\"" << setclass[0];
		for (int i = 1; i < setclass.size(); i++)
			cout << " " << setclass[i];
		cout << "\"";
	}

	cout << ">";
}

void solve () {
	int ret = mv, x, y, ti = 1;
	string recstring = "";

	gettoken();
	while (word == "(") {
		solve();
		// now word is ")";
		gettoken(); // get a new token;
	}

	if (word == ">") { // after solve '()';
		solve();
		return;
	}

	if (word == "" || word == ")")
		return;

	string name;
	VS setclass, setid;

	while (true) {

		if (word == ".") {
			gettoken();
			setclass.push_back(word);
		} else if (word == "#") {
			gettoken();
			setid.push_back(word);
		} else if (word == ">") {
			putstring(name, setid, setclass);
			solve();
			break;
		} else if (word == ")" || word == "") {
			putstring(name, setid, setclass);
			break;
		} else if (word == "*") {
			x = mv - 1;
			gettoken();
			y = mv;
			ti = changeTonumber();
			for (int i = x; i < y; i++) {
				recstring += str[i];
				str[i] = ' ';
			}
		} else
			name = word;
		gettoken();
	}
	cout << "</" << name << ">";

	for (int i = 1; i < ti; i++) {
		mv = ret;
		solve();
	}

	for (int i = 0; i < recstring.size(); i++)
		str[i+x] = recstring[i];
}

int main () {
	int cas;
	cin >> cas;
	while (cas--) {
		cin >> str;
		mv = 0;
		solve();
		cout << endl;
	}
	return 0;
}
