#include "longint.h"

//	This method overload the input stream
istream & operator >> (istream & input, LongInt & rhs) {
	rhs.digits.clear();    // Clean the LongInt before put new data into
	char read = '0';
	while (input.good() && ((read = input.get()) != '-') && (read < '0' || read >'9'))
	{
		// must be from range 0-9
	}
	if (read == '-') // Check for negative sign
	{
		rhs.negative = true;
		if (input.good())
		{
			read = input.get(); // Check for the next characer
		}
	}
	while (read >= '0' && read <= '9')
	{
		rhs.digits.addBack(read - '0');
		// read a new charactor
		read = input.get(); // Check next available item
	}
	rhs.remove0s(); // Trim the number
	return input;
}


//  This method overload the output operator and print out the LongInt

ostream & operator<<(ostream & output, const LongInt & rhs)
{
	Deque<char> x = rhs.digits; // Creat a copy to print out
	if (rhs.negative) // Check for the sign
	{
		output << " - ";
	}
	if (x.isEmpty())
	{
		output << "0";
		return output;

	}
	while (x.size() > 0) // Iterate and print out
	{
		output << (int) (x.removeFront() );
	}
	return output;
}


//	This constructor will construct a new LongInt based on the given string

LongInt::LongInt(const string str)
{
	digits.clear(); // Clean up
	negative = false;
	bool oddThings = false;   // To check if there are any odd things between number
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '-' && negative == false)
		{
			negative = true;   // Check the sign of the string
			continue;
		}
		if (str[i] >= '0' && str[i] <= '9')
		{
			oddThings = true;
			digits.addBack((char)str[i] - '0');
		}
		else
			if (oddThings == true)
			{
				break;
			}
	}
	remove0s();
}

//  This is the copy constructor for the LongInt

LongInt::LongInt(const LongInt & rhs)
{
	digits.clear();
	negative = false;
	*this = rhs; // Utilize the = operator
	remove0s();
}

//  This is the default constructor for the LongInt

LongInt::LongInt()
{
	digits.clear();    // Make the deque empty to hold new variable
	negative = false;
}

//  This is the destructor for the LongInt

LongInt::~LongInt()
{
	digits.clear();
}

/*
	This method will overload the addition operator
	It will add 2 LongInt together and return a new LongInt
*/
LongInt LongInt::operator+(const LongInt & rhs) const
{
	if (negative == false && rhs.negative == true)
	{
		LongInt temporary = rhs;
		temporary.negative = false;
		return *this - temporary; // Utilize the - operator
	}
	if (negative == true && rhs.negative == false)
	{
		LongInt temporary = *this;
		temporary.negative = false;
		return rhs - temporary;
	}
	// The only cases left are + + and - -
	int size = rhs.digits.size() < digits.size() ? rhs.digits.size() : digits.size(); // Compare the size of 2 LongInt
	LongInt answer;
	Deque<char> firstCopy = digits; // Get the queue of 2 LongInt to perform addition
	Deque<char> secondCopy = rhs.digits;
	int carry = 0;
	while (size != 0) // Go through the smaller queue
	{
		int x = (int)firstCopy.removeBack();
		int y = (int)secondCopy.removeBack();
		int result = x + y + carry;
		carry = result / 10;
		answer.digits.addFront((char)(result % 10));
		size--;
	}
	int resultSecond = 0;
	while (firstCopy.size() > 0) // Check if it still have more elements
	{   // latest carry integer
		resultSecond = (int)firstCopy.removeBack() + carry;
		answer.digits.addFront((char)(resultSecond % 10)); // Exhaust the remaining of 2 deque to make sure no elements are behind
		carry = resultSecond / 10;
	}
	while (secondCopy.size() > 0)
	{
		resultSecond = (int)secondCopy.removeBack() + carry;
		answer.digits.addFront((char)(resultSecond % 10));
		carry = resultSecond / 10;
	}
	if (negative == false && rhs.negative == false)
	{
		answer.negative = false;
		if (carry != 0)
		{
			answer.digits.addFront((char)carry); // Add the remaning carry
		}
		answer.remove0s();
	}
	if (negative == true && rhs.negative == true)
	{
		// This is the case where -(lhs+rhs). Put the negative infront
		answer.negative = true;
		if (carry != 0)
		{
			answer.digits.addFront((char)carry);
		}
		answer.remove0s();
	}
	return answer;
}

//  This method will perform subtraction of 2 LongInt

LongInt LongInt::operator-(const LongInt & rhs) const
{

	LongInt answer;
	if (*this == rhs) // Special case when the result is equal to 0;
	{
		answer.negative = false;
		answer.digits.addBack(0);
		return answer;
	}
	if (rhs.negative == true && negative == false)
	{
		LongInt temporary = rhs;
		temporary.negative = false; // a - - b = a + b
		answer = *this + temporary;
		answer.negative = false; // Utilize the + operator
		return answer;
	}
	if (rhs.negative == false && negative == true)
	{
		LongInt temporary = rhs;  // - a - b = -(a+b)
		temporary.negative = false;
		LongInt temporarySecond = *this;
		temporarySecond.negative = false;
		answer = temporarySecond + temporary;
		answer.negative = true;
		return answer;
	}

	Deque<char> firstCopy;
	Deque<char> secondCopy;

	if (negative == true && rhs.negative == true)
	{
		if (*this >= rhs)
		{
			// Check for multiple cases and compare between 2 LongInt to determine the sign first

			answer.negative = false;
			firstCopy = rhs.digits;
			secondCopy = digits;
		}
		else
		{
			answer.negative = true ;
			firstCopy = digits;
			secondCopy = rhs.digits;
		}
	}
	if (negative == false && rhs.negative == false)
	{
		if (*this < rhs)
		{
			answer.negative = true;
			firstCopy = rhs.digits;
			secondCopy = digits;

		}
		else
		{
			answer.negative = false;
			firstCopy = digits;
			secondCopy = rhs.digits;
		}
	}
	int size = firstCopy.size() > secondCopy.size() ? firstCopy.size() : secondCopy.size();
	int carry = 0;
	int result = 0;
	while (size != 0) // Go through all the number
	{
		int x = firstCopy.size() > 0 ? (int)firstCopy.removeBack() : 0;
		int y = secondCopy.size() > 0 ? (int)secondCopy.removeBack() : 0;
		if ((x - y - carry )>= 0)
		{

			result = x -y- carry; // This will still in positive range
			carry = 0;

		}
		else
		{
			result = x + 10 - y - carry; // This will get negative integer, so add 10 to make up
			carry = 1;
		}
		answer.digits.addFront((char) abs(result));
		size--;

	}
	answer.remove0s();
	return answer;

}


//  This method overloaded the assignment operator for the LongInt

const LongInt & LongInt::operator=(const LongInt & rhs)
{

	negative = rhs.negative;
	digits = rhs.digits; // Already overloaded the = operator in Deque class

	return *this;
}

/*
	This method will compare if the current LongInt is less than the compared LongInt
	This will check the sign first and return the result.
	If the sign is the same, It will then interate to check the whole deque
*/
bool LongInt::operator<(const LongInt & rhs) const
{
	bool result = true;
	if (negative == true && rhs.negative == false)
	{
		// negative lhs is less than positive rhs
		return result;
	}
	if (negative == false && rhs.negative == true)
	{
		// positive lhs is greater than negative rhs
		return !result;
	}
	int firstSize = digits.size();
	int secondSize = rhs.digits.size();
	if (firstSize < secondSize)
	{
		if (negative == true && rhs.negative == true)
		{
			return !result;
		}
		else
		{
			return result;
		}
	}
	if (firstSize > secondSize)
	{
		if (negative == true && rhs.negative == true)
		{
			return !result;
		}
		else
		{
			return !result;
		}
	}
	if (firstSize == secondSize)
	{
		Deque<char> a = digits;
		Deque<char>b = rhs.digits;
		while (firstSize > 0)
		{
			int x = (int)a.removeFront() ;    // Iterate and check from the front
			int y =  (int) b.removeFront() ;
			if ((x - y) != 0)
			{
				if (negative == true && rhs.negative == true)
				{
					return x < y ? !result : result;
				}
				else
				{
					return x < y ? result : !result;
				}
			}
		}
	}
	return result;
}

//  This method overloaded the <= operator

bool LongInt::operator<=(const LongInt & rhs) const
{
	if (*this < rhs)
	{
		return true;
	}
	if (*this == rhs)
	{
		return true;
	}
	return false;
}

//  This method will overload the > operator

bool LongInt::operator>(const LongInt & rhs) const
{
	return  !(*this <= rhs);
}

//  This method will overload the >= operator

bool LongInt::operator>=(const LongInt & rhs) const
{
	return !(*this < rhs);
}

//  This method will overload the == operator

bool LongInt::operator==(const LongInt & rhs) const
{
	if (negative != rhs.negative)
	{
		return false; // Check the sign first
	}
	if (digits.size() != rhs.digits.size())
	{
		return false; // Check the size second
	}
	Deque<char> thisCompare = digits;
	Deque<char> theCompare = rhs.digits;
	while (theCompare.size() > 0) // Iterate through both LongInt and compare each element
	{
		int theResult = (int) thisCompare.removeFront()  - (int) theCompare.removeFront() ;
		if (theResult != 0)
		{
			return false;
		}
	}
	return true;
}

//  This method will overload the != operator

bool LongInt::operator!=(const LongInt & rhs) const
{
	return !(*this == rhs);
}

//  This private helper method will remove all the 0 that appear infront of the LongInt

void LongInt::remove0s()
{

	while (digits.getFront() == 0) // While the front is still 0, remove it and iterate to the next one
	{
		digits.removeFront();

	}
	if (digits.isEmpty())
	{
		digits.addBack(0);
		negative = false;
	}
	return;
}

