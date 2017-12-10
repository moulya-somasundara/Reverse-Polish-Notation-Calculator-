#include "StringProcess.h"



StringProcess::StringProcess()
{
}

//The constructor for this Class will take in the read Buffer
StringProcess::StringProcess(const string & a_string)	: readBuffer(a_string)
{

		bool returnIfFalse = fillUpInfix();
		if (!returnIfFalse)
		{
			return;
		}
		infixToPostFix();
		printPostFix();

		std::cout << " The answer is: ";
		double valToDisplay =  evaluatePostFix();

		if (valToDisplay != std::numeric_limits<double>::max())
		{
			cout << valToDisplay;
		}

		cout << " \n done" << endl;


	
}


StringProcess::~StringProcess()
{
}


/***********************************************************************
NAME:
void fillUpInfix()

SYNOPSIS:

bool fillUpInfix() --> fill up infix

DESCRIPTION:
This function will  take in cin input and create the tokens for each piece.
stored in the infix queue

RETURNS:
true is all went well, false to warn off some corner cases like "bad formatting".
bad formatting does NOT account for say Just poorly formatted problem strings


AUTHOR:
Devinder Sodhi
SOURCES:
NONE. Figured this one myself
DATE:
10-11-2016
***************************************************************************/
bool StringProcess::fillUpInfix()
{
	double testNum;
	char singleChar;

	//while (readBuffer.get(singleChar) && singleChar == ' ');//skip spaces

	while (readBuffer.get(singleChar))
	{

		if (readBuffer.good() && singleChar != '\n' && singleChar != '\0')
		{
			if (singleChar == ' ')
			{
				continue;
			}
			//if its an exponent...
			if (singleChar == 'P')
			{
				if (readBuffer.get(singleChar) && singleChar == 'O')
				{
					if (readBuffer.get(singleChar) && singleChar == 'W')
					{
						TokenInfo t = TokenInfo(EXPONENT);
						infixQ.push_back(t);
						continue;
					}
					else
					{
						cout << "invalid syntax" << endl;
						return false;
					}
				}
				else
				{
					cout << "invalid syntax" << endl;
					return false;
				}
			}

			if (singleChar == 'Q' || singleChar == 
				'q')
			{
				if (readBuffer.get(singleChar) && (singleChar == 'U' || singleChar == 'u'))
				{
					if (readBuffer.get(singleChar) && (singleChar == 'I' || singleChar == 'i'))
					{
						if (readBuffer.get(singleChar) && (singleChar == 'T' || singleChar == 't'))
						{
							cout << "quitting program" << endl;
							exit(1);
						}
						else
						{
							cout << "invalid syntax" << endl;
							return false;
						}
					}
					else
					{
						cout << "invalid syntax" << endl;
						return false;
					}
				}
				else
				{
					cout << "invalid syntax" << endl;
					return false;
				}
			}

			//if valid operator
			Type type;
			testNum = 0;
			switch (singleChar)
			{
			case '*':type = MULT;
				testNum = 0;
				break;
			case '/': type = DIV;
				testNum = 0;
				break;
			case '+': type = ADD;
				testNum = 0;
				break;
			case '-': type = SUBTRACT;
				testNum = 0;
				break;
			case '(': type = LEFTPAREN;
				testNum = 0;
				break;
			case ')': type = RIGHTPAREN;
				testNum = 0;
				break;
			case '%': type = MODULO;
				testNum = 0;
				break;
			default:
				readBuffer.putback(singleChar);
				if (!(readBuffer >> testNum))
				{
					cout << "invalid syntax" << endl;
					return false;
				}
				type = NUMBER;
			}
			TokenInfo t = TokenInfo(type, testNum);
			infixQ.push_back(t);
		}
	}

	return true;
}


/***********************************************************************
NAME:
void infixToPostFix()

SYNOPSIS:

void infixToPostfix() --> convert infix to postfix 

DESCRIPTION:
There are class deques that hold my converted Tokens. 
I take my list of infix tokens and convert to postfix type.
then the information is stored in the postQ deque
RETURNS:
nothing

AUTHOR:
Devinder Sodhi
SOURCES:
NONE. Figured this one myself
DATE:
10-11-2016
***************************************************************************/
void StringProcess::infixToPostFix()
{
	TokenInfo temp;
	while (!infixQ.empty())
	{
		temp = infixQ.front();
		infixQ.pop_front();

		if (temp.getType() == NUMBER)
		{
			postQ.push_back(temp);
		}
		else if (opStack.empty())
		{
			opStack.push(temp);
		}
		else if (temp.getType() == LEFTPAREN)
		{
			opStack.push(temp);
		}
		else if (temp.getType() == RIGHTPAREN)
		{
			while (opStack.top().getType() != LEFTPAREN)
			{
				postQ.push_back(opStack.top());
				opStack.pop();
			}
			opStack.pop();
		}
		else
		{
			while (!opStack.empty() && opStack.top().getType() != LEFTPAREN && HasHigherPrecedence(opStack.top().getType(), temp.getType()))
			{

					postQ.push_back(opStack.top());
					opStack.pop();
				
			}
			opStack.push(temp);
		}
		//cout << temp.getType() << temp.getVal() << endl;
	}
	while (!opStack.empty())
	{
		postQ.push_back(opStack.top());
		opStack.pop();
	}

}


/***********************************************************************
NAME:
void getWeight(Type type)

SYNOPSIS:

void fillUpInfix() --> evaulate a type
a_type -> Type to evaluate

DESCRIPTION:
Evaluate a Type and gives it a precedence Rank based on the operator type.
this was an idea
RETURNS:
int value with ranking

AUTHOR:
Devinder Sodhi
SOURCES:
NONE. Looked at an old data structures homework i did a while ago though
DATE:
10-11-2016
***************************************************************************/
int StringProcess::getWeight(Type a_type)
{
	if (a_type == ADD || a_type == SUBTRACT)
	{
		return 1;
	}
	if (a_type == MULT || a_type == DIV || a_type == MODULO)
	{
		return 2;
	}
	if (a_type == EXPONENT)
	{
		return 3;
	}
	if (a_type == LEFTPAREN || a_type == RIGHTPAREN)
	{
		return 4;
	}

}


/***********************************************************************
NAME:
isRightAssociative(Type a_type)

SYNOPSIS:

isRightAssociative() ->check if operator is right associative
a_type -> Type to evaluate

DESCRIPTION:
see if operator is right associative
RETURNS: bool indicvating whether it is or not right associative.

AUTHOR:
Devinder Sodhi
SOURCES:
NONE
DATE:
10-11-2016
***************************************************************************/
bool StringProcess::isRightAssociative(Type a_type)
{
	if (a_type == EXPONENT)
	{
		return true;
	}
	return false;
}


/***********************************************************************
NAME:
HasHigherPrecedence(Type a_op1, Type a_op2)
SYNOPSIS:

HasHigherPrecedence( ) --> its left higher than right?
a_op1 -> left type
a_op2 -> right type

DESCRIPTION:
this function determines which of the two tokens have higher precedence.
It also makes a check to adjust for 

RETURNS: bool indicating whether lval is bigger than rval

AUTHOR:
Devinder Sodhi
SOURCES:
//https://gist.github.com/mycodeschool/7867739 helped me make some sense of the last part of the algorithm in RPN
DATE:
10-11-2016
***************************************************************************/
bool StringProcess::HasHigherPrecedence(Type a_op1, Type a_op2)
{
	int op1Weight = getWeight(a_op1);
	int op2Weight = getWeight(a_op2);

	// If operators have equal precedence, return true if they are left associative.
	// BUT REMEMBER...return false, if right associative.
	// if operator is left-associative, left one should be given priority.
	if (op1Weight == op2Weight) {
		if (isRightAssociative(a_op1)) {
			return false;
		}
		else {
			return true;
		}
	}
	return op1Weight > op2Weight ? true : false;
}

/***********************************************************************
NAME:
evaluatePostFix()
SYNOPSIS:
evaluatePostFix() ->evaluate the postfix  list

DESCRIPTION:
iterate through the list and evaluate the results based on the postfix.
This should be relatively simple

RETURNS:
double, this will either get printed of have an exception where is doesn't
AUTHOR:
Devinder Sodhi
SOURCES:
I think the question source was entirely the pseudo code for this. I figured out the implementating
looking at it
DATE:
10-11-2016
***************************************************************************/
double StringProcess::evaluatePostFix()
{

	
	stack<double> eval;
	TokenInfo temp;
	double topNum, nextNum, answer =0;

	while (!postQ.empty())
	{
		temp = postQ.front();
		postQ.pop_front();

		if (temp.getType() == NUMBER)
		{
			eval.push(temp.getVal());
		}
		else
		{
			if (eval.empty())
			{
				cerr << "wrong operation usage, try again." << endl;
				return std::numeric_limits<double>::max();
			}

			topNum = eval.top();
			eval.pop();
			nextNum = eval.top();
			eval.pop();

			if (temp.getType() == ADD)
			{
				answer = nextNum + topNum;
				 
			}
			if (temp.getType() == SUBTRACT)
			{
				answer = nextNum - topNum;
			}
			if (temp.getType() == MULT)
			{
				answer = nextNum * topNum;

			}
			if (temp.getType() == DIV)
			{
				answer = nextNum / topNum;
			}
			if (temp.getType() == EXPONENT)
			{
				answer = pow(nextNum, topNum);
			}
			if (temp.getType() == MODULO)
			{
				answer = fmod(nextNum, topNum);
			}
			eval.push(answer);
		}


	}

	if (eval.empty())
	{
		cerr << "wrong operation usage, try again." << endl;
		return std::numeric_limits<double>::max();
	}
	else
	{
		return eval.top();

	}

}


//print everything to cout
void StringProcess::printPostFix()
{
	deque<TokenInfo>::iterator It;

	std::cout << " the post fix eval is: ";

	for (It = postQ.begin(); It != postQ.end(); It++)
	{
		if (It->getType() == ADD)
		{
			std::cout << " + ";
		}
		if (It->getType() == SUBTRACT)
		{
			std::cout << " - ";
		}
		if (It->getType() == MULT)
		{
			std::cout << " * ";
		}
		if (It->getType() == DIV)
		{
			std::cout << " / ";
		}
		if (It->getType() == MODULO)
		{
			std::cout << " % ";
		}
		if (It->getType() == EXPONENT)
		{
			std::cout << " ^ ";
		}
		if (It->getType() == NUMBER)
		{
			std::cout << " " << It->getVal() << " " ;
		}

	}


	std::cout << endl;
}

