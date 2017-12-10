#include "TokenInfo.h"



TokenInfo::TokenInfo()
{
}



TokenInfo::TokenInfo(Type a_tokenType, double a_value)
{
	m_tokenType = a_tokenType;
	m_numberVal = a_value;
}

TokenInfo::~TokenInfo()
{
}
