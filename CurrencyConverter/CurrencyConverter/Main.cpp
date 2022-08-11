#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <vector>
#include <iomanip>
#include <math.h>


using std::cout;
using std::string;
using std::cin;
using std::endl;
using std::vector;

string clrRes(string stToClr);
string matchStrCodeToInt(string currCode);
vector<string> formatedData();
float convertedCurr(vector<string> data, string currfr, string currto, int currval);
string inputAndOutput();

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string currfr;
	string currto;
	vector<string> data = formatedData();
	int currval;
	cout << "Введіть валюту, із якої будете конвертувати: ";
	cin >> currfr;
	cout << "Введіть валюту, в яку будете конвертувати: ";
	cin >> currto;
	cout << "Введіть кількість валюти яку хочете обміняти: ";
	cin >> currval;
	currfr = matchStrCodeToInt(currfr);
	currto = matchStrCodeToInt(currto);

	if (currfr == "" || currto == "") {
		cout << "Невірно введені дані" << endl;
		return 0;
	}
	float res = convertedCurr(data, currfr, currto, currval);
	cout << "Валюта, яку ви отримаєте: " << res << endl;

	return 0;

	/*if (s.size() < 3) {
			if (comco == 5) {
				s.push_back(b.substr(pos2, pos1 - pos2));
				pos2 = pos1 + 1;
				comco = 0;
			}
		}
		else if (s.size() >= 3) {
			if (comco == 4) {
				s.push_back(b.substr(pos2, pos1 - pos2));
				pos2 = pos1 + 1;
				comco = 0;
			}
		}*/
}

string inputAndOutput() {
	string currfr;
	string currto;
	vector<string> data = formatedData();
	int currval;
	cout << "Введіть валюту, із якої будете конвертувати: ";
	cin >> currfr;
	cout << "Введіть валюту, в яку будете конвертувати: ";
	cin >> currto;
	cout << "Введіть кількість валюти яку хочете обміняти: ";
	cin >> currval;
	currfr = matchStrCodeToInt(currfr);
	currto = matchStrCodeToInt(currto);
}

float convertedCurr(vector<string> data, string currfr, string currto, int currval) {
	float t = 0;

	for (string a : data) {
		string rate;
		if (a.find(currfr) && a.find(currto)) {
			vector<string> elem;
			int pos = 0;
			
			for (int i = 0; i < a.size(); i++) {
				if (a[i] == ',') {
					elem.push_back(a.substr(pos, i - pos));
					pos = i + 1;
				}
				if (i == a.size() - 1) {
					elem.push_back(a.substr(pos, i - pos));
				}
			}
			int f = a.find(currfr);
			int g = a.find(currto);
			if (a.find(currfr) > a.find(currto)) {
				rate = elem[3].substr(elem[3].find(":") + 1, elem[3].size() - elem[3].find(":"));
				t = std::stod(rate);
			}
			else {
				rate = elem[4].substr(elem[4].find(":") + 1, elem[4].size() - elem[4].find(":"));
				t = std::stod(rate);
				t = t / 100;
			}
			
			break;
		}
	}
	
	return currval * t;

}

string clrRes(string stToClr) {
	stToClr.erase(stToClr.find("{"), 1);
	stToClr.erase(stToClr.find("}"), 1);
	
	/*Тут такий момент, я не розумію чому, навіть якщо я видаляю " із рядка, то find все одно знаходить той символ
	  Мені здається, що він не обновляє якось рядок, і він хоч і зберігається але find бере старий рядок
	*/ 
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
		if (c.find(currCode)) {
			return c.substr(c.find(":") + 1, 3);
		}
	}
	return "";
}

vector<string> formatedData() {
	auto response = cpr::Get(cpr::Url{ "https://api.monobank.ua/bank/currency" });
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

void temp() {
	string currfr;
	string currto;
	int currval;
	cout << "Введіть валюту, із якої будете конвертувати: ";
	cin >> currfr;
	cout << "Введіть валюту, в яку будете конвертувати: ";
	cin >> currto;
	cout << "Введіть кількість валюти яку хочете обміняти: ";
	cin >> currval;
	if (currfr == "UAH" && currto == "USD") {
		int res = currval * 36;
		cout << "Конвертована кількість валюти: " << res;
	}
}