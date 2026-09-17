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

bool ScalarConverter::checkOverflow(const std::string& input)
{
	char *end = NULL;
	double val = std::strtod(input.c_str(), &end);

	//double is way bigger than int and float so if it overflows, everything is "overflown" 
	if (errno == ERANGE)
	{
		printOverflow();
		return true;
	}
	//next in size is float
	else if (val > FLT_MAX || val < -FLT_MAX)
	{
		printCharOverflow();
		printIntOverflow();
		printFloatOverflow();
		printDouble(val);
		return true;
	}
	//finally, int
	else if (val > INT_MAX || val < INT_MIN)
	{
		printCharOverflow();
		printIntOverflow();
		printFloat(static_cast<float>(val));
		printDouble(val);
		return true;
	}
	//no overflow yayy
	return false;
}

void ScalarConverter::printOverflow()
{
	printCharOverflow();
	printIntOverflow();
	printFloatOverflow();
	printDoubleOverflow();
}

void ScalarConverter::printCharOverflow()
{
	std::cout << "char: impossible" << std::endl;
}


void ScalarConverter::printIntOverflow()
{
	std::cout << "int: impossible" << std::endl;
}

void ScalarConverter::printFloatOverflow()
{
	std::cout << "float: impossible" << std::endl;
}


void ScalarConverter::printDoubleOverflow()
{
	std::cout << "double: impossible" << std::endl;
}

void ScalarConverter::printChar(const std::string& input)
{
	char c = input[0];
	int i = static_cast<int>(c);
	float f = static_cast<float>(c);
	double d = static_cast<double>(c);

	std::cout << "'" << c << "'" << std::endl;
	printInt(i);
	printFloat(f);
	printDouble(d);
}

void ScalarConverter::printChar(int c)
{
	std::cout << "char: ";

	if (c < 0 || c > 127)
		std::cout << "impossible";
	else if ((c >= 0 && c <= 31) || c == 127)
		std::cout << "Non displayable";
	else
		std::cout << "'" << static_cast<char>(c) << "'";
	std::cout << std::endl;
}

void ScalarConverter::printInt(const std::string& input)
{
	int i = std::atoi(input.c_str());
	float f = static_cast<float>(i);
	double d = static_cast<double>(i);

	printChar(i);
	printInt(i);
	printFloat(f);
	printDouble(d);
}

void ScalarConverter::printInt(int i)
{
	std::cout << "int: " << i << std::endl;
}

void ScalarConverter::printFloat(const std::string& input)
{
	char *end = NULL;
	double val = std::strtod(input.c_str(), &end);

	float f = static_cast<float>(val);
	int i = static_cast<int>(f);
	double d = static_cast<double>(f);

	printChar(i);
	printInt(i);
	printFloat(f);
	printDouble(d);
}

void ScalarConverter::printFloat(float f)
{
	std::cout << "float: " << f;
	if (isIntegral(f))
		std::cout << ".0";
	std::cout << "f" << std::endl;
}

void ScalarConverter::printDouble(const std::string& input)
{
	char *end = NULL;
	double val = std::strtod(input.c_str(), &end);

	double d = val;
	int i = static_cast<int>(d);
	float f = static_cast<float>(d);

	printChar(i);
	printInt(i);
	printFloat(f);
	printDouble(d);
}

void ScalarConverter::printDouble(double d)
{
	std::cout << "double: " << d;
	if (isIntegral(d))
		std::cout << ".0";
	std::cout << std::endl;
}

bool ScalarConverter::isIntegral(double d)
{
    double intPart;
    double fracPart = std::modf(d, &intPart);
    return fracPart == 0.0;
}

bool ScalarConverter::isIntegral(float f)
{
    float intPart;
    float fracPart = std::modf(f, &intPart);
    return fracPart == 0.0f;
}

bool ScalarConverter::isPseudo(const std::string& input)
{
	if (input == "-inff" || input == "+inff")
	{
		std::cout << "char: impossible" << std::endl << "int: impossible" << std::endl;
		std::cout << "float: " << input << std::endl;
		std::cout << "double: " << input[0] << "inf" << std::endl;
		return true;
	}
	if (input == "-inf" || input == "+inf")
	{
		std::cout << "char: impossible" << std::endl << "int: impossible" << std::endl;
		std::cout << "float: " << input << "f" << std::endl;
		std::cout << "double: " << input << std::endl;
		return true;
	}
	if (input == "nan" || input == "nanf")
	{
		std::cout << "char: impossible" << std::endl << "int: impossible" << std::endl;
		std::cout << "float: " << "nanf" << std::endl;
		std::cout << "double: " << "nan" << std::endl;
		return true;
	}
	return false;

}

void ScalarConverter::converter(const std::string& input)
{
	if (!validateInput(input))
		return ;

	if (isPseudo(input))
		return ;

	if (isChar(input))
	{
		printChar(input);
		return ;
	}
	
	if (checkOverflow(input))
		return ;
	else if (isInt(input))
		printInt(input);
	else if (isFloat(input))
		printFloat(input);
	else if (isDouble(input))
		printDouble(input);
	else
		std::cout << "Invalid/unknown primitive data type. Accepted types: char, int, float and double" << std::endl;
}
