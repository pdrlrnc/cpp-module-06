/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 15:30:58 by pedde-so          #+#    #+#             */
/*   Updated: 2026/09/19 15:30:59 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

int main(void)
{
	Base* abc = generate();

	identify(abc);

	delete abc;

	abc = generate();

	identify(*abc);

	delete abc;
}
