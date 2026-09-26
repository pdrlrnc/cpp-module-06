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
