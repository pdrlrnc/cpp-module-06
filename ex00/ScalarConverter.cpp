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

//check before delivery: can i use those amazing functions? i am leaning to no but lets discuss it
std::string ScalarConverter::trim(const std::string& input)
{
	// size_type is just a typedef for an unsigned interger type (in practice almost always size_t)
	// std::string uses it for lengths, indices and positions
	std::string::size_type start = input.find_first_not_of(" \t\n\r\f\v");

	// npos is a special constant defined as static const size_type npos = -1
	// it is used by find_first_not_of and other methods as a sentinel for not found
	if (start == std::string::npos) return "";

	std::string::size_type end = input.find_last_not_of(" \t\n\r\f\v");
	return input.substr(start, end - start + 1);
}

std::string ScalarConverter::convertToChar(std::string input)
{
	if (input == "")
		return "impossible";
	return "possible";
}

bool ScalarConverter::validateInput(std::string& input)
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

bool ScalarConverter::isChar(std::string& input)
{
	if (input.length() == 1 && !isdigit(input[0]))
		return true;
	return false;
}

bool ScalarConverter::isFloat(std::string& input)
{

	std::string::size_type i = input.length();

	//at least 4 characters, the "simplest" valid float is 1.0f, 4 chars long
	if (i < 4)
		return false;

	//last char has to be a 'f'
	i--;
	if (input[i] != 'f')
		return false;

	//after the 'f', we require at least one digit, then followed by a '.'
	i--;
	while (isdigit(input[i]) && i > 0)
		i--;
	if (input[i] != '.' || (i == input.length() - 2))
		return false;
	
	//after the '.' every char must be a digit
	i--;	
	while (isdigit(input[i]) && i > 0)
		i--;
	return (i == 0);
}

bool ScalarConverter::isDouble(std::string& input)
{

	std::string::size_type i = input.length();

	//at least 3 characters, the "simplest" valid double is 1.0, 3 chars long
	if (i < 3)
		return false;

	//we require at least one digit, then followed by a '.'
	i--;
	while (isdigit(input[i]) && i > 0)
		i--;
	if (input[i] != '.' || (i == input.length() - 1))
		return false;
	
	//after the '.' every char must be a digit
	i--;	
	while (isdigit(input[i]) && i > 0)
		i--;
	return (i == 0);
}

bool ScalarConverter::isInt(std::string& input)
{
	std::string::size_type i = 0;

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
	std::string trimedInput = trim(input);

	if (!validateInput(trimedInput))
		return ;

	std::cout << "|" << input << "|" << " " << "is " << (isChar(trimedInput) ? "" : "not ") << "a char" << std::endl;	
	std::cout << "|" << input << "|" << " " << "is " << (isFloat(trimedInput) ? "" : "not ") << "a float" << std::endl;	
	std::cout << "|" << input << "|" << " " << "is " << (isDouble(trimedInput) ? "" : "not ") << "a double" << std::endl;	
	std::cout << "|" << input << "|" << " " << "is " << (isInt(trimedInput) ? "" : "not ") << "a int" << std::endl;	
}
