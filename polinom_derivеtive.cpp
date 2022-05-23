#include <bits/stdc++.h>
using namespace std;

long long getValue(string pTerm, long long val) {
	// Get coefficient
    string coeffStr = "";
    int i;
    for (i = 0; (pTerm[i] != 'x'); i++)
        coeffStr.push_back(pTerm[i]);
    long long coeff = atol(coeffStr.c_str());
    // Get Power (Skip 2 characters for x and ^)
    string powStr = "";
    for (i = i + 2; i != pTerm.size(); i++)
        powStr.push_back(pTerm[i]);
    long long power = atol(powStr.c_str());
    // ax^n
    return coeff * pow(val, power);
}
long long calculateValue(string& poly, int val) {
	long long ans = 0; 
    // We use istringstream to get input in tokens
    istringstream is(poly);
    string pTerm;
    char movement='+';
    while (is >> pTerm) {
 
        // If the token is equal to '+' then
        // continue with the string
        if (pTerm == "+") {
        	movement='+';
        	continue;
		}  else if (pTerm == "-") {
			movement='-';
        	continue;
		}    
 
        // Otherwise find the derivative of that
        // particular term
        else {
        	if (movement == '+'){
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
	for (i = key; (pTerm[i] != 'x' && i < pTerm.length()); i++) {
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
		if (key<pTerm.length()-1) {
			derivativeTerm(pTerm,  val);
		}
	}
}
// Driver code
int main() {
	string str1 = "41x^5 - 13x^4 + 4x^1 + 13x^0";//bad, in future remove x^0
	
	int val = 1;
	cout << str << endl;
	cout << calculateValue(str, val) << std::endl;
	derivativeTerm(str, val);
	return 0;
}
