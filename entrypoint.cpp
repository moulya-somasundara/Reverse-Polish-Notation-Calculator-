#include <iostream>
#include <string>
#include <sstream>
#include "StringProcess.h"

using namespace std;

/*
Name: Devinder Sodhi
Project: RPN Calculator with POW 
Course: CS_590
Date 10-10-2016

This is the entry point of the program
*/

int main()
{
	cout << "Welcome to the RPN calculator" << endl;
	cout << "the accepted operators are POW, ( ) , %, +, -, /, * " << endl;
	cout << "Please note that incorrect out put will be handled accordingly:" << endl;
	cout << " The calculator will attempt to work through bad operators, or exit" << endl;
	cout << " if no operators are input, then you will be returned the last number in the list" << endl;
	string readThis;

	while (true)
	{
		cout << "Please enter an infix math problem." << endl;
		
		getline(cin, readThis);

		StringProcess evaluateThis(readThis);



		//convertToReadableAndPush

		//convertToPostFix

		//CalculateResults and display

	}

}