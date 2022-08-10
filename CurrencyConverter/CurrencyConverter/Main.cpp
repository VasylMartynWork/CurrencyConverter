#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <vector>


using std::cout;
using std::string;
using std::cin;
using std::endl;
using std::vector;

string clrRes(string stToClr);

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//temp();
	auto response = cpr::Get(cpr::Url{ "https://api.monobank.ua/bank/currency" });
	//std::cout << response.text << std::endl;
	string b = response.text;
	vector<string> s;
	int comco = 0;
	
	int pos1 = 0;
	int pos2 = 0;

	b.erase(b.find('['), 1);
	b.erase(b.find(']'), 1);
	for (int i = 0; i < b.size(); i++) {
		if (b[i] == ',')
			comco++;
		bool check;
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
	}


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

string clrRes(string stToClr) {
	stToClr.erase(stToClr.find("{"), 1);
	stToClr.erase(stToClr.find("}"), 1);
	
	/*��� ����� ������, � �� ������ ����, ����� ���� � ������� " �� �����, �� find ��� ���� ��������� ��� ������
	  ��� �������, �� �� �� �������� ����� �����, � �� ��� � ���������� ��� find ���� ������ �����
	*/ 
	while (stToClr.find("\\\"")) {
		try {
			stToClr.erase(stToClr.find("\""), 1);
		}
		catch(std::exception) {
			break;
		}
	}
	return stToClr;
}

void temp() {
	string currfr;
	string currto;
	int currval;
	cout << "������ ������, �� ��� ������ ������������: ";
	cin >> currfr;
	cout << "������ ������, � ��� ������ ������������: ";
	cin >> currto;
	cout << "������ ������� ������ ��� ������ �������: ";
	cin >> currval;
	if (currfr == "UAH" && currto == "USD") {
		int res = currval * 36;
		cout << "������������ ������� ������: " << res;
	}
}