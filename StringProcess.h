#pragma once
/*
Name: Devinder Sodhi
Project: RPN Calculator with POW
Course: CS_590
Date 10-10-2016

Sstring Process:
This Class deals with The info as its accepted into the cin stream
The processing for infix -> postfix and the calculations thereafter are done here.
*/

#include <iostream>
#include <stack>
#include <deque>
#include <sstream>
#include "TokenInfo.h"
#include <math.h>
#include <stdlib.h>

using namespace std;



class StringProcess
{
public:
	StringProcess();
	StringProcess(const string & a_string);

	~StringProcess();

private:


	bool fillUpInfix();

	void infixToPostFix();

	int getWeight(Type a_type);

//https://gist.github.com/mycodeschool/7867739 helped me make some sense of the last part of the algorithm in RPN
	bool isRightAssociative(Type type);
	bool HasHigherPrecedence(Type a_op1, Type a_op2);

	double evaluatePostFix();
	
	void printPostFix();

	

	stack<TokenInfo> opStack; //stack of operators
	deque<TokenInfo> postQ, infixQ; 

	istringstream readBuffer;
};

