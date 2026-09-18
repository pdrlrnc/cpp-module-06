#ifndef SCALARCONVERTER_H
#define SCALARCONVERTER_H


#include <cstdlib>
#include <string>
#include <iostream>
#include <cctype>
#include <cerrno>
#include <climits>
#include <cfloat>
#include <iomanip>
#include <cmath>

class ScalarConverter {

	//this is kinda dumb i know but the class can't be instantiated and by 42 rulles 
	//it needs to be in the OCF
	private:
		ScalarConverter();
		~ScalarConverter();
		ScalarConverter(const ScalarConverter& other);
		ScalarConverter& operator=(const ScalarConverter& other);

		//helpers
		static bool validateInput(const std::string& input);

		static bool isPseudo(const std::string& input);

		static bool isChar(const std::string& input);
		static bool isFloat(const std::string& input);
		static bool isDouble(const std::string& input);
		static bool isInt(const std::string& input);

		static bool checkOverflow(const std::string& input);
		static void printOverflow();
		static void printCharOverflow();
		static void printIntOverflow();
		static void printFloatOverflow();
		static void printDoubleOverflow();
	
		static void printChar(const std::string& input);
		static void printChar(int c);

		static void printInt(const std::string& input);
		static void printInt(int i);

		static void printFloat(const std::string& input);
		static void printFloat(float f);
		
		static void printDouble(const std::string& input);
		static void printDouble(double d);

		static bool isIntegral(double d);
		static bool isIntegral(float f);

		static int getPrecision(double d);
	public:
		static void convert(const std::string& input);
		

};

#endif
