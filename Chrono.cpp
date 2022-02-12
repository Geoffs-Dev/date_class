/*
* std_lib_facilities.h  include files are:
* 
* #include<iostream>
* #include<iomanip>
* #include<fstream>
* #include<sstream>
* #include<cmath>
* #include<cstdlib>
* #include<string>
* #include<list>
* #include <forward_list>
* #include<vector>
* #include<unordered_map>
* #include<algorithm>
* #include <array>
* #include <regex>
* #include<random>
* #include<stdexcept>
* 
*/
#include "std_lib_facilities.h"

#include "Chrono.h"

namespace Chrono {
	//member function definitions:

	Date::Date(int yy, Month mm, int dd)
	 : y{ yy }, m{ mm }, d{ dd }
	{
		if (!is_date(yy, mm, dd)) throw Invalid{};
	}

	const Date& default_date()
	{
		static Date dd { 2001, Month::jan,1 };	//Set the default date
		return dd;
	}

	Date::Date()
		: y{ default_date().year() },
		m{ default_date().month() },
		d{ default_date().day() }
	{
	}
	
	void Date::add_day(int n)
	{
		//...
	}

	void Date::add_month(int n)
	{
		//...
	}

	/*
	I have changed the code from Stroustrups book : m == feb is now m == Month::feb same again on the line below
	 for some reason i cannot access the enum class Month { ... } members unless explicitly directed?
	I can't see an error in the code yet????
	*/
	void Date::add_year(int n)
	{
		if (m == Month::feb && d == 29 && !leapyear(y + n)) { //test for leap year if false adjust the month and day to 1st March
			m = Month::mar;
			d = 1;
		} 

		y += n;
	}

	// Helper Functions:
	bool is_date(int y, Month m, int d)
	{
		// assume that y is valid [WHAT!!! ?]

		if(d<=0) return false;	//d must be positive
		if (m < Month::jan || Month::dec < m) return false;

		int days_in_month = 31;		// most months have 31 days

		switch (m) {
		case Month::feb:	//length of feb varies
			days_in_month = (leapyear(y)) ? 29 : 28;
			break;
		case Month::apr:
		case Month::jun:
		case Month::sep:
		case Month::nov:
			days_in_month = 30;		// the rest have 30 days
			break;
		}

		if (days_in_month < d) return false;
		
		return true;
	}

	bool leapyear(int y)
	{
		// See exercise 10 (CRAP!)
		// Actually this should be quite easy - laughs very out loud
	}

	// operator overloads
	bool operator==(const Date& a, const Date& b)
	{
		return a.year() == b.year()
			&& a.month() == b.month()
			&& a.day() == b.day();
	}

	bool operator!=(const Date& a, const Date& b)
	{
		return !(a == b);
	}

	//Errors "no operator "<<" matches these operands
	ostream& operator<<(ostream& os, const Date& d)
	{
		return os << '(' << d.year() <<  ',' << d.month() << ',' << d.day() << ')';
	}

	istream& operator>>(istream& is, Date& dd)
	{
		int y, m, d;
		char ch1, ch2, ch3, ch4;
		is >> ch1 >> y>> ch2 >> m >> ch3 >> d >>ch4;

		if (!is) return is;

		if (ch1 != '('
			|| ch2 != ','
			|| ch3 != ','
			|| ch4 != ')') { // oops format error
				is.clear(ios_base::failbit);		//set the fail bit:  What is fail_bit? Need to look it up.
			return is;
		}

		dd = Date(y, Month(m), d);		//update dd

		return is;
	}

}	// Chrono

int main()
{

	return 0;
}