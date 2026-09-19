/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 12:34:50 by pedde-so          #+#    #+#             */
/*   Updated: 2026/09/19 12:34:53 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

Data::Data(): _data("no data") {};

Data::~Data() {};

Data::Data(const Data& other)
{
	(void)other;
}

Data& Data::operator=(const Data& other)
{
	(void)other;
	return *this;
}

Data::Data(const std::string& data): _data(data) {}

std::string Data::getData()
{
	return _data;
}
