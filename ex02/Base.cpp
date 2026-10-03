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

	int r = randomIndex();
	if (r == 0)
		b = new A();
	else if (r == 1)
		b = new B();
	else 
		b = new C();

	return b;
}

int randomIndex(void)
{
	return std::rand() % 3;
}

void identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown type" << std::endl;
}

void identify(Base& p)
{
    try { 
	    (void)dynamic_cast<A&>(p);
	    std::cout << "A" << std::endl;
	    return ;
    } catch (...) {}

    try {
	    (void)dynamic_cast<B&>(p);
	    std::cout << "B" << std::endl;
	    return ;
    } catch (...) {}
    
    try {
	    (void)dynamic_cast<C&>(p);
	    std::cout << "C" << std::endl;
	    return;
    } catch (...) {}

    std::cout << "Unknown type" << std::endl;
}
