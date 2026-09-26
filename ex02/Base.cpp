/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 15:19:14 by pedde-so          #+#    #+#             */
/*   Updated: 2026/09/19 15:19:15 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base::~Base() {}

Base* generate(void)
{
	Base *b;

	int r = random();
	if (r == 0)
		b = new A();
	else if (r == 1)
		b = new B();
	else 
		b = new C();

	return b;
}

int random(void)
{
	char *c = new char;
	int i = *(int *)&c;

	delete c;
	return i % 3;
}

void identify(Base* p)
{
	A* a = dynamic_cast<A*>(p);
	B* b = dynamic_cast<B*>(p);
	C* c = dynamic_cast<C*>(p);

	if (a)
		std::cout << "Type: A" << std::endl;

	if (b)
		std::cout << "Type: B" << std::endl;

	if (c)
		std::cout << "Type: C" << std::endl;
}

void identify(Base& p)
{
	Base *pPtr = &p;
	identify(pPtr);
}


