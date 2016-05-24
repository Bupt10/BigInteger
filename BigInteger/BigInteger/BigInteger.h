#ifndef BigInteger_h__
#define BigInteger_h__

//////////////////////////////////////////////////////////////////// 
//                          _ooOoo_                               // 
//                         o8888888o                              // 
//                         88" . "88                              // 
//                         (| ^_^ |)                              // 
//                         O\  =  /O                              // 
//                      ____/`---'\____                           // 
//                    .'  \\|     |//  `.                         // 
//                   /  \\|||  :  |||//  \                        // 
//                  /  _||||| -:- |||||-  \                       // 
//                  |   | \\\  -  /// |   |                       // 
//                  | \_|  ''\---/''  |   |                       // 
//                  \  .-\__  `-`  ___/-. /                       // 
//                ___`. .'  /--.--\  `. . ___                     // 
//              ."" '<  `.___\_<|>_/___.'  >'"".                  // 
//            | | :  `- \`.;`\ _ /`;.`/ - ` : | |                 // 
//            \  \ `-.   \_ __\ /__ _/   .-` /  /                 // 
//      ========`-.____`-.___\_____/___.-`____.-'========         // 
//                           `=---='                              // 
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^        // 
//              佛祖保佑       永无BUG     永不修改                   // 
//////////////////////////////////////////////////////////////////// 

 
#include <string>
#include <iostream>

#define MAX 10000 // for strings

using namespace std;

//-------------------------------------------------------------
class BigInteger
{
private:
	string number;
	bool sign;

public:
	BigInteger(); // empty constructor initializes zero
	BigInteger(const string &s); // "string" constructor
	BigInteger(const string &s, const bool sin); // "string" constructor
	BigInteger(const int n); // "int" constructor
	void setNumber(const string &s);
	const string& getNumber() const; // retrieves the number
	void setSign(const bool s);
	const bool& getSign() const;
	BigInteger absolute() const; // returns the absolute value
    long long convert_2_long_long(bool *ok) const;
	void operator = (const BigInteger &b);
	bool operator == (const BigInteger &b);
	bool operator != (const BigInteger &b);
	bool operator > (const BigInteger &b);
	bool operator < (const BigInteger &b);
	bool operator >= (const BigInteger &b);
	bool operator <= (const BigInteger &b);
    friend ostream& operator << (ostream &os, const BigInteger &rhs);
    friend istream& operator >> (istream &is, BigInteger &rhs);

	BigInteger& operator ++(); // prefix
	BigInteger  operator ++(int); // postfix
	BigInteger& operator --(); // prefix
	BigInteger  operator --(int); // postfix
	BigInteger operator + (const BigInteger &b);
	BigInteger operator - (const BigInteger &b);
	BigInteger operator * (const BigInteger &b);
	BigInteger operator / (const BigInteger &b);
	//BigInteger operator / (const int b);
	BigInteger operator % (const BigInteger &b);
	BigInteger& operator += (const BigInteger &b);
	BigInteger& operator -= (const BigInteger &b);
	BigInteger& operator *= (const BigInteger &b);
	BigInteger& operator /= (const BigInteger &b);
	BigInteger& operator %= (const BigInteger &b);
	BigInteger& operator [] (const int n);
	BigInteger operator -(); // unary minus sign
	operator string(); // for conversion from BigInteger to string

private:
	bool equals(const BigInteger &n1, const BigInteger &n2);
	bool less(const BigInteger &n1, const BigInteger &n2);
	bool greater(const BigInteger &n1, const BigInteger &n2);
	string add(string number1, string number2);
	string subtract(string number1, string number2);
	string multiply(string n1, string n2);
public:
	pair<string, long long> divide(string n, long long den);
	string toString(const long long n) const;
	long long toInt(const string s) const;
};

#endif // BigInteger_h__