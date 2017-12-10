#pragma once
/*
Name: Devinder Sodhi
Project: RPN Calculator with POW
Course: CS_590
Date 10-10-2016

TokenInfo
This Class deals with TokenInfo
Each character set in the input is converted into a token type. 
number data has a value, and every data has a type. 
The ENUM defines all the possible Token types.
*/

#include <limits>

enum Type { LEFTPAREN, RIGHTPAREN, EXPONENT, MULT, DIV, MODULO, ADD, SUBTRACT, NUMBER };
class TokenInfo
{
public:
	TokenInfo();

	TokenInfo(Type a_tokenType, double a_value = 0);

	Type getType()
	{
		return m_tokenType;
	}

	double getVal()
	{
		if (m_tokenType == NUMBER)
		{
			return m_numberVal;
		}
		else return std::numeric_limits<int>::max();
	}
	~TokenInfo();

private: 
	Type m_tokenType;
	double m_numberVal; //if this is defined
	

};

