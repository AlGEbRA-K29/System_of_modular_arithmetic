#include <bits/stdc++.h>
using namespace std;

long long getValue(string pTerm, long long val) {
	// Get coefficient
	string coeffStr = "";
	int i;
	for (i = 0; pTerm[i] != 'x'; i++)
		coeffStr.push_back(pTerm[i]);
	long long coeff = atol(coeffStr.c_str());

	// Get Power (Skip 2 characters for x and ^)
	string powStr = "";
	for (i = i + 2; i != pTerm.size(); i++)
		powStr.push_back(pTerm[i]);
	long long power = atol(powStr.c_str());

	// For ax^n, we return anx^(n-1)
	return coeff * pow(val, power);
}

long long calculateValue(string& poly, int val) {
	long long ans = 0;
	// We use istringstream to get input in tokens
	istringstream is(poly);
	char my_move = '+';
	string pTerm;
	while (is >> pTerm) {
		// If the token is equal to '+' then
		// continue with the string
		if (pTerm == "+") {
			continue;
		} else if (pTerm == "-") {
			my_move='-';
			continue;
		}

		// Otherwise find the derivative of that
		// particular term
		else {
			if(my_move=='+') {
				ans = (ans + getValue(pTerm, val));
			} else {
				ans = (ans - getValue(pTerm, val));
			}
		}
	}
	return ans;
}
void derivativeTerm(string pTerm, long long val) {
	// Get coefficient
	string coeffStr = "";
	int i;
	static int key=0;
	int stop=0;
	char symbol=' ';
	static bool first = true;
	if (first && pTerm[0]=='-') {
		symbol='-';
	}
	for (i = key; pTerm[i] != 'x'; i++) {
		if (pTerm[i] == '+') {
			symbol='+';
			stop++;
			continue;
		} else if (pTerm[i]=='-') {
			symbol='-';
			stop++;
			continue;
		}
		coeffStr.push_back(pTerm[i]);
		stop++;
	}
	long long coeff = atol(coeffStr.c_str());

	// Get Power (Skip 2 characters for x and ^)
	string powStr = "";
	for (i = i + 2; i != pTerm.size(); i++) {
		powStr.push_back(pTerm[i]);
	}
	key+=stop;
	key+=3;
	long long power = atol(powStr.c_str());
	// For ax^n, we return anx^(n-1)
	if (power==0) {
		cout << "";
	} else {
		if (first) {
			if(power==1 && symbol=='+') {
				cout << coeff*power;
			} else if (power==1 && symbol=='-') {
				cout << symbol << coeff*power;
			} else {
				if (symbol=='+') {
					cout << coeff*power << "x^" << power-1;
				} else {
					cout << symbol << coeff*power << "x^" << power-1;
				}
			}
			first=false;
		} else {
			if(power==1){
				cout << symbol << coeff*power;
			} else {
				cout << symbol << coeff*power << "x^" << power-1;
			}
		}
		if (key<pTerm.length()) {
			derivativeTerm(pTerm,  val);
		}
	}
}
string clear_spaces(string pTerm) {
	for (int i = 0; i<pTerm.length()-1; i++) {
		if(pTerm[i]==' ') {
			for (int j = i; j<pTerm.length()-1; j++) {
				pTerm[j]=pTerm[j+1];
			}
		}
	}
	cout <<pTerm<<endl;
	return pTerm;
}
// Driver code
int main() {
	string str = "41x^5-13x^4+4x^1";
	//clear_spaces(str);
	int val = 1;
	cout << str << endl;
	cout << calculateValue(str, val) << std::endl;
	derivativeTerm(str, val);
	return 0;
}
