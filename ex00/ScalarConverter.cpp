#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::~ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other)
{ 
	(void)other; 
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
{
	(void)other;
	return *this;
}

bool ScalarConverter::validateInput(const std::string& input)
{
	if (input.empty())
	{
		std::cout << "Error: input is empty" << std::endl;
		return false;
	}
	
	
	for (std::string::size_type i = 0; i < input.length(); i++)
	{
		if (!std::isprint(input[i]))
		{
			std::cout << "Error: input has invalid characters" << std::endl; 
			return false;
		}
	}
	return true;
}

bool ScalarConverter::isChar(const std::string& input)
{
	if (input.length() == 1 && !isdigit(input[0]))
		return true;
	return false;
}

bool ScalarConverter::isFloat(const std::string& input)
{

	std::string::size_type i = input.length();

	//at least 3 characters, the "simplest" valid float is 1.f, 3 chars long
	if (i < 3)
		return false;

	//last char has to be a 'f'
	i--;
	if (input[i] != 'f')
		return false;

	//after the 'f', we can have - or not - digits, then followed by a '.'
	i--;
	while (i != 0 && isdigit(input[i]))
		i--;
	if (i == 0 || input[i] != '.')
		return false;
	
	//after the '.' every char must be a digit, except the first one that can be either + or -
	i--;	
	while (i != 0 && isdigit(input[i]))
		i--;
	return (i == 0 && (isdigit(input[0]) || input[0] == '+' || input[0] == '-'));
}

bool ScalarConverter::isDouble(const std::string& input)
{
	std::string::size_type i = input.length();

	//at least 2 characters, the "simplest" valid double is 1., 2 chars long
	if (i < 2)
		return false;

	//there can be or not be digits, then followed by a '.'
	i--;
	while (i != 0 && isdigit(input[i]))
		i--;
	if (i == 0 || input[i] != '.')
		return false;
	
	//after the '.' every char must be a digit or + or - for the first char
	i--;	
	while (i != 0 && isdigit(input[i]))
		i--;
	return (i == 0 && (isdigit(input[0]) || input[0] == '+' || input[0] == '-'));
}

bool ScalarConverter::isInt(const std::string& input)
{
	std::string::size_type i = 1;

	//can start with + or -, can't be just + or -
	if (!isdigit(input[0]) && input[0] != '-' && input[0] != '+')
		return false;
	if ((input[0] == '-' || input[0] == '+') && input.length() == 1)
		return false;
	
	while (i < input.length())
	{
		if (!isdigit(input[i]))
			return false;
		i++;
	}
	return true;
}

void ScalarConverter::converter(const std::string& input)
{
	if (!validateInput(input))
		return ;

	std::cout << "|" << input << "|" << " " << "is " << (isChar(input) ? "" : "not ") << "a char" << std::endl;	
	std::cout << "|" << input << "|" << " " << "is " << (isFloat(input) ? "" : "not ") << "a float" << std::endl;	
	std::cout << "|" << input << "|" << " " << "is " << (isDouble(input) ? "" : "not ") << "a double" << std::endl;	
	std::cout << "|" << input << "|" << " " << "is " << (isInt(input) ? "" : "not ") << "a int" << std::endl;	
}
