#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <vector>


using std::cout;
using std::string;
using std::cin;
using std::endl;
using std::vector;
using std::getline;

string clrRes(string stToClr);
string matchStrCodeToInt(string currCode);
vector<string> formatedData();
float convertedCurr(vector<string> data, string currfr, string currto, int currval);
string repeat();

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector<string> data = formatedData();
	string currfr;
	string currto;
	int currval = 0;
	string choice;
	string currvalst;
	int test = 0;

	do {
		system("cls");
		cout << "Доступні валюти: USD, EUR, UAH" << endl;
		cout << "Введіть валюту, із якої будете конвертувати: ";

		getline(cin, currfr);

		cout << "Введіть валюту, в яку будете конвертувати: ";
		getline(cin, currto);

		cout << "Введіть кількість валюти, яку хочете обміняти: ";
		getline(cin, currvalst);
		try {
			currval = std::stoi(currvalst);
		}
		catch (std::exception) {
			choice = repeat();
			if (choice == "1") {
				test = 1;
				continue;
			}
			else{
				break;
			}
		}

		if (currval <= 0) {
			choice = repeat();
			if (choice == "1") {
				test = 1;
				continue;
			}
			else{
				break;
			}
		}
		currfr = matchStrCodeToInt(currfr);
		currto = matchStrCodeToInt(currto);

		if (currfr == "" || currto == "") {
			choice = repeat();
			if (choice == "1") {
				test = 1;
				continue;
			}
			else{
				break;
			}
		}
		float res = convertedCurr(data, currfr, currto, currval);
		cout << "Валюта, яку ви отримаєте: " << res << endl;

		cout << "\nБажаєте спробувати ще раз?\n1 - Спробувати ще раз\n2 - Вийти\nВвівши будь-яке інше значення програма завершиться" << endl;
		getline(cin, choice);
		if (choice == "1") {
			test = 1;
			continue;
		}
		else{
			break;
		}
	} while (true);

	return 0;
}

string repeat() {
	string choice;
	cout << "Невірно введені дані\n" << endl;
	cout << "Бажаєте спробувати ще раз?\n1 - Спробувати ще раз\n2 - Вийти\nВвівши будь-яке інше значення програма завершиться" << endl;
	getline(cin, choice);
	return choice;
}

float convertedCurr(vector<string> data, string currfr, string currto, int currval) {
	float t = 0;

	for (string a : data) {
		string rate;
		if (a.find(currfr) != -1 && a.find(currto) != -1) {
			vector<string> elem;
			int pos = 0;
			
			for (int i = 0; i < a.size(); i++) {
				if (a[i] == ',') {
					elem.push_back(a.substr(pos, i - pos));
					pos = i + 1;
				}
				if (i == a.size() - 1) {
					elem.push_back(a.substr(pos, i - pos + 1));
				}
			}

			if (a.find(currfr) < a.find(currto)) {
				rate = elem[3].substr(elem[3].find(":") + 1, elem[3].size() - elem[3].find(":"));
				t = std::stod(rate);
			}
			else {
				rate = elem[4].substr(elem[4].find(":") + 1, elem[4].size() - elem[4].find(":"));
				t = std::stod(rate);
				if (t >= 10) {
					t = t / 100;
				}
				else {
					t = currval - (std::stod(rate) - std::stod(elem[3].substr(elem[3].find(":") + 1, elem[3].size() - elem[3].find(":"))));
				}
			}
			
			break;
		}
	}
	
	return currval * t;

}

string clrRes(string stToClr) {
	stToClr.erase(stToClr.find("{"), 1);
	stToClr.erase(stToClr.find("}"), 1);
	 
	while (stToClr.find("\\\"")) {
		try {
			stToClr.erase(stToClr.find("\""), 1);
		}
		catch (std::exception) {
			break;
		}
	}
	return stToClr;
}

string matchStrCodeToInt(string currCode) {
	string arr[] = {"UAH:980", "USD:840", "EUR:978"};
	for (string c : arr) {
		int te = c.find(currCode);
		if (c.find(currCode) != -1 && currCode != "") {
			return c.substr(c.find(":") + 1, 3);
		}
	}
	return "";
}

vector<string> formatedData() {
	auto response = cpr::Get(cpr::Url{ "https://api.monobank.ua/bank/currency" });
	while (response.text == "{\"errorDescription\":\"Too many requests\"}") {
		system("cls");
		cout << "Будь ласка, зачекайте кілька секунд, та натисність Enter" << endl;
		cin.get();
		response = cpr::Get(cpr::Url{ "https://api.monobank.ua/bank/currency" });
	}
	string b = response.text;
	vector<string> s;
	bool check;
	int comco = 0;

	int pos1 = 0;
	int pos2 = 0;

	b.erase(b.find('['), 1);
	b.erase(b.find(']'), 1);
	for (int i = 0; i < b.size(); i++) {
		if (b[i] == ',')
			comco++;

		if (s.size() < 3) {
			check = comco == 5;
		}
		else
			check = comco == 4;
		if (check) {
			s.push_back(clrRes(b.substr(pos2, pos1 - pos2)));
			pos2 = pos1 + 1;
			comco = 0;
		}

		pos1++;
		if (s.size() == 3) {
			break;
		}
	}
	return s;
}