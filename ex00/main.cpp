#include "ScalarConverter.hpp"

int main(int argc, char **argv)
{
	if (argc > 2)
	{
		std::cout << "Error: too many args" << std::endl;
		return 1;
	}
	if (argc < 2)
	{
		std::cout << "Error: too few args" << std::endl;
		return 1;
	}
	ScalarConverter::convert(argv[1]);
}
