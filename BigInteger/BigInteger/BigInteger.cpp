#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cassert>

#include "BigInteger.h"

#define MAX 10000 // for strings

BigInteger::BigInteger() // empty constructor initializes zero
{
	number = "0";
	sign = false;
}

//-------------------------------------------------------------
BigInteger::BigInteger(const string &s) // "string" constructor
{
	if( isdigit(s[0]) ) { // if not signed
		setNumber(s);
		sign = false; // +ve
	} else {
		setNumber(s.substr(1));
		sign = (s[0] == '-');
	}
}

//-------------------------------------------------------------
BigInteger::BigInteger(const string &s, const bool sin) // "string" constructor
{
	setNumber( s );
	setSign( sin );
}

//-------------------------------------------------------------
BigInteger::BigInteger(const int n) // "int" constructor
{
	stringstream ss;
    string s;
	ss << n;
	ss >> s;
 
	if( isdigit(s[0]) ) { // if not signed
		setNumber( s );
		setSign( false ); // +ve
	} else {
		setNumber( s.substr(1) );
		setSign( s[0] == '-' );
	}
}

//-------------------------------------------------------------
void BigInteger::setNumber(const string &s)
{
	number = s;
}

//-------------------------------------------------------------
const string& BigInteger::getNumber() const // retrieves the number
{
	return number;
}

//-------------------------------------------------------------
void BigInteger::setSign(const bool s)
{
	sign = s;
}

//-------------------------------------------------------------
const bool& BigInteger::getSign() const
{
	return sign;
}

//-------------------------------------------------------------
// returns the absolute value
BigInteger BigInteger::absolute() const
{
	return BigInteger( getNumber() ); // +ve by default
}

//-------------------------------------------------------------
void BigInteger::operator = (const BigInteger &b)
{
	setNumber( b.getNumber() );
	setSign( b.getSign() );
}

//-------------------------------------------------------------
bool BigInteger::operator == (const BigInteger &b)
{
	return equals((*this) , b);
}

//-------------------------------------------------------------
bool BigInteger::operator != (const BigInteger &b)
{
	return ! equals((*this) , b);
}

//-------------------------------------------------------------
bool BigInteger::operator > (const BigInteger &b)
{
	return greater((*this) , b);
}

//-------------------------------------------------------------
bool BigInteger::operator < (const BigInteger &b)
{
	return less((*this) , b);
}

//-------------------------------------------------------------
bool BigInteger::operator >= (const BigInteger &b)
{
	return equals((*this) , b)
		|| greater((*this), b);
}

//-------------------------------------------------------------
bool BigInteger::operator <= (const BigInteger &b)
{
	return equals((*this) , b) 
		|| less((*this) , b);
}

//-------------------------------------------------------------
// increments the value, then returns its value
BigInteger& BigInteger::operator ++() // prefix
{
	(*this) = (*this) + 1;
	return (*this);
}

//-------------------------------------------------------------
// returns the value, then increments its value
BigInteger BigInteger::operator ++(int) // postfix
{
	BigInteger before = (*this);

	(*this) = (*this) + 1;

	return before;
}

//-------------------------------------------------------------
// decrements the value, then return it
BigInteger& BigInteger::operator --() // prefix
{
	(*this) = (*this) - 1;
	return (*this);

}

//-------------------------------------------------------------
// return the value, then decrements it
BigInteger BigInteger::operator --(int) // postfix
{	
	BigInteger before = (*this);

	(*this) = (*this) - 1;

	return before;
}

//-------------------------------------------------------------
BigInteger BigInteger::operator + (const BigInteger &b)
{
	BigInteger addition;
	if( getSign() == b.getSign() ) // both +ve or -ve
	{
		addition.setNumber( add(getNumber(), b.getNumber() ) );
		addition.setSign( getSign() );
	}
	else // sign different
	{
		if( absolute() > b.absolute() )
		{
			addition.setNumber( subtract(getNumber(), b.getNumber() ) );
			addition.setSign( getSign() );
		}
		else
		{
			addition.setNumber( subtract(b.getNumber(), getNumber() ) );
			addition.setSign( b.getSign() );
		}
	}
	if(addition.getNumber() == "0") // avoid (-0) problem
		addition.setSign(false);

	return addition;
}

//-------------------------------------------------------------
BigInteger BigInteger::operator - (const BigInteger &b)
{ 
	BigInteger ans = b; 

	ans.setSign( !ans.getSign() ); // x - y = x + (-y)

	return (*this) + ans;
}

//-------------------------------------------------------------
BigInteger BigInteger::operator * (const BigInteger &b)
{
	BigInteger mul;

	mul.setNumber( multiply(getNumber(), b.getNumber() ) );
	mul.setSign( getSign() != b.getSign() );

	if(mul.getNumber() == "0") // avoid (-0) problem
		mul.setSign(false);

	return mul;
}

/*
BigInteger BigInteger::operator / (const int b)
{
	BigInteger ans; 


	return ans;
}
*/

//-------------------------------------------------------------
// Warning: Denomerator must be within "long long" size not "BigInteger"
BigInteger BigInteger::operator / (const BigInteger &b)
{
    BigInteger ans;

    bool bSing = (this->sign != b.sign);

    string r_str = this->getNumber().substr(0, b.getNumber().length());

    const string &dividend_str = this->getNumber();
    const string &divisor_str = b.getNumber(); 
    BigInteger r(r_str);
    BigInteger divisor(divisor_str);

    int curPos = r_str.length() - 1;
    while(curPos < dividend_str.length()) {
        int tmpR = 0;
        while(r >= divisor) {
            r = r - divisor; 
            tmpR++;
        }
        ans = ans * 10 + tmpR; 
        if(++curPos == dividend_str.length())
            break;
        r = r * 10 + dividend_str[curPos] - '0';
    }

    ans.setSign(bSing);

    return ans;
    /*
	long long den = toInt( b.getNumber() );
	BigInteger div;

	div.setNumber( divide(getNumber(), den).first );
	div.setSign( getSign() != b.getSign() );

	if(div.getNumber() == "0") // avoid (-0) problem
		div.setSign(false);

	return div;
    */
}

//-------------------------------------------------------------
// Warning: Denomerator must be within "long long" size not "BigInteger"
BigInteger BigInteger::operator % (const BigInteger &b)
{
	BigInteger rem;

    rem = (*this) - ((*this) / b) * b;

	return rem; 
    /*
	long long den = toInt( b.getNumber() );

	BigInteger rem;
	long long rem_int = divide(number, den).second;
	rem.setNumber( toString(rem_int) );
	rem.setSign( getSign() != b.getSign() );

	if(rem.getNumber() == "0") // avoid (-0) problem
		rem.setSign(false);

	return rem; 
    */
}

//-------------------------------------------------------------
BigInteger& BigInteger::operator += (const BigInteger &b)
{
	(*this) = (*this) + b;
	return (*this);
}

//-------------------------------------------------------------
BigInteger& BigInteger::operator -= (const BigInteger &b)
{
	(*this) = (*this) - b;
	return (*this);
}

//-------------------------------------------------------------
BigInteger& BigInteger::operator *= (const BigInteger &b)
{
	(*this) = (*this) * b;
	return (*this);
}

//-------------------------------------------------------------
BigInteger& BigInteger::operator /= (const BigInteger &b)
{
	(*this) = (*this) / b;
	return (*this);
}

//-------------------------------------------------------------
BigInteger& BigInteger::operator %= (const BigInteger &b)
{
	(*this) = (*this) % b;
	return (*this);
}

//-------------------------------------------------------------
BigInteger& BigInteger::operator [] (const int n)
{
    assert(n >= 0);
    return *(this + (n*sizeof(BigInteger)));
}

//-------------------------------------------------------------
BigInteger BigInteger::operator -() // unary minus sign
{
	return (*this) * -1;
}

//-------------------------------------------------------------
BigInteger::operator string() // for conversion from BigInteger to string
{
	string signedString = ( getSign() ) ? "-" : ""; // if +ve, don't print + sign
	signedString += number;
	return signedString;
}

//-------------------------------------------------------------
bool BigInteger::equals(const BigInteger &n1, const BigInteger &n2)
{
	return n1.getSign() == n2.getSign() 
        && n1.getNumber() == n2.getNumber();
}

//-------------------------------------------------------------
bool BigInteger::less(const BigInteger &n1, const BigInteger &n2)
{
	bool sign1 = n1.getSign();
	bool sign2 = n2.getSign();

	if(sign1 && ! sign2) { // if n1 is -ve and n2 is +ve 
		return true; 
    } else if(! sign1 && sign2) {
		return false; 
    } else if(! sign1) { // both +ve
		if(n1.getNumber().length() < n2.getNumber().length() )
			return true;
		if(n1.getNumber().length() > n2.getNumber().length() )
			return false;
		return n1.getNumber() < n2.getNumber();
	} else { // both -ve
		if(n1.getNumber().length() > n2.getNumber().length())
			return true;
		if(n1.getNumber().length() < n2.getNumber().length())
			return false;
		return n1.getNumber().compare( n2.getNumber() ) > 0; // greater with -ve sign is LESS
	}
}

//-------------------------------------------------------------
bool BigInteger::greater(const BigInteger &n1, const BigInteger &n2)
{
	return ! equals(n1, n2) && ! less(n1, n2);
}

//-------------------------------------------------------------
// adds two strings and returns their sum in as a string
string BigInteger::add(string number1, string number2)
{
	string add = (number1.length() > number2.length()) ?  number1 : number2;
	char carry = '0';
	int differenceInLength = abs( (int) (number1.size() - number2.size()) );

	if(number1.size() > number2.size())
		number2.insert(0, differenceInLength, '0'); // put zeros from left 
	else// if(number1.size() < number2.size())
		number1.insert(0, differenceInLength, '0');

	for(int i=number1.size()-1; i>=0; --i) {
		add[i] = ((carry-'0')+(number1[i]-'0')+(number2[i]-'0')) + '0';

		if(i != 0) {	
			if(add[i] > '9') {
				add[i] -= 10;
				carry = '1';
			} else {
				carry = '0';
            }
		}
	}

	if(add[0] > '9') {
		add[0]-= 10;
		add.insert(0,1,'1');
	}
	return add;
}

//-------------------------------------------------------------
// subtracts two strings and returns their sum in as a string
string BigInteger::subtract(string lhs, string rhs)
{
    string ans = lhs; 
    int len1 = ans.length(), len2 = rhs.length();
    int carray = 0, i = 0, h = 0;

    for(i = 0; i < len2; i++) {
        if(ans[len1 - 1 - i] < rhs[len2 - 1 - i]) {
            for(h = len1 - i - 2; h >= 0; h --) {
                if(ans[h] == '0'){
                    ans[h] = '9';
                } else if (ans[h] > '0'){
                    ans[h]--; 
                    carray = 10;
                    break;
                }
            }
        }
        ans[len1 - 1 - i] = carray + ans[len1 - 1 - i] - rhs[len2 - 1 - i] + '0';
        carray = 0;
    }

    for(i = 0; i < len1 && ans[i] == '0'; i++) ;
 
    return i == len1 ? "0" : ans.substr(i);

	//string sub = (number1.length()>number2.length())? number1 : number2;
	//int differenceInLength = abs( (int)(number1.size() - number2.size()) );

	//if(number1.size() > number2.size())	
	//	number2.insert(0, differenceInLength, '0'); 
	//else
	//	number1.insert(0, differenceInLength, '0');

	//for(int i=number1.length()-1; i>=0; --i) {
	//	if(number1[i] < number2[i]) {
	//		number1[i] += 10;
	//		number1[i-1]--;
	//	}
	//	sub[i] = ((number1[i]-'0')-(number2[i]-'0')) + '0';
	//}

	//while(sub[0]=='0' && sub.length()!=1) // erase leading zeros
	//	sub.erase(0,1);

	//return sub;
}

//-------------------------------------------------------------
// multiplies two strings and returns their sum in as a string
string BigInteger::multiply(string n1, string n2)
{
	if(n1.length() > n2.length()) 
		n1.swap(n2);

	string res = "0";

	for(int i=n1.length()-1; i>=0; --i) {
		string temp = n2;
		int currentDigit = n1[i]-'0';
		int carry = 0;

		for(int j=temp.length()-1; j>=0; --j) {
			temp[j] = ((temp[j]-'0') * currentDigit) + carry;

			if(temp[j] > 9) {
				carry = (temp[j]/10);
				temp[j] -= (carry*10);
			} else {
				carry = 0;
            }

			temp[j] += '0'; // back to string mood
		}

		if(carry > 0)
			temp.insert(0, 1, (carry+'0'));
		
		temp.append((n1.length()-i-1), '0'); // as like mult by 10, 100, 1000, 10000 and so on

		res = add(res, temp); // O(n)
	}

	while(res[0] == '0' && res.length()!=1) // erase leading zeros
		res.erase(0,1);

	return res;
}

//-------------------------------------------------------------
// divides string on long long, returns pair(qutiont, remainder)
pair<string, long long> BigInteger::divide(string n, long long den)
{
	long long rem = 0;
	string result; 
    result.resize(MAX);
	
	for(int indx=0, len = n.length(); indx<len; ++indx) {
		rem = (rem * 10) + (n[indx] - '0');
		result[indx] = rem / den + '0';
		rem %= den;
	}
	result.resize( n.length() );

	while( result[0] == '0' && result.length() != 1)
		result.erase(0,1);

	if(result.length() == 0)
		result = "0";

	return make_pair(result, rem);
}

//-------------------------------------------------------------
// converts long long to string
string BigInteger::toString(const long long n) const
{
	stringstream ss;
	string temp;

	ss << n;
	ss >> temp;

	return temp;
}

long long BigInteger::convert_2_long_long(bool *ok) const
{
	long long sum = 0;

    *ok = true;
	for(int i=0; i<this->number.length(); i++) {
		sum = (sum*10) + (this->number[i] - '0');
        if(sum < 0) {
            *ok = false;
            break;
        }
    }

    if(*ok) {
        sum *= (this->sign ? -1 : 1); 
    }

	return sum;
}

//-------------------------------------------------------------
// converts string to long long
long long BigInteger::toInt(const string s) const
{ 
    // invalid 
    // plesse refer to convert_2_long_long

	long long sum = 0;

	for(int i=0; i<s.length(); i++) {
		sum = (sum*10) + (s[i] - '0');
    }

	return sum;
}

ostream& operator << (ostream &os, const BigInteger &rhs)
{
    if(rhs.sign) {
        os << "-";
    }

    os << rhs.number;

    return os;
}

istream& operator >> (istream &is, BigInteger &rhs)
{
    string num;
    is >> num;
    if(num[0] == '+' || num[0] == '-') {
        rhs.setNumber(num.substr(1)); 
        if(num[0] == '-') {
            rhs.setSign(true);
        }
    } else {
        int i = 0;
        for(i = 0; i < num.length(); i++) {
            if(!isdigit(num[i])) {
                break; 
            } 
        }
        rhs.setNumber(num.substr(0, i));
    }


    return is;
}