#ifndef SCALARCONVERTER_H
#define SCALARCONVERTER_H


#include <cstdlib>
#include <string>
#include <iostream>
#include <cctype>

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
		static bool isChar(const std::string& input);
		static bool isFloat(const std::string& input);
		static bool isDouble(const std::string& input);
		static bool isInt(const std::string& input);
	
	public:
		static void converter(const std::string& input);
		

};

#endif
