
#include<string>
#include <iostream>
#include "polynomial.h"
#include"bigint.h"
#include"inverse.h"
#include"findingCircularPolynomial.h"
#include<vector>
using namespace std;


int main()
{
	polynomial p = findCircularPolynomial(1);
	cout << p;
	cout<<checkForFreeFromSquares(1);
	cout << Mobiusfunction(3);
   
}




