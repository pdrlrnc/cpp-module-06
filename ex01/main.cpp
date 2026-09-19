/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 14:02:15 by pedde-so          #+#    #+#             */
/*   Updated: 2026/09/19 14:02:16 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"
#include "Serializer.hpp"

#include <iostream>
#include <stdint.h> 

int main(void)
{
	Data *dataPtr = new Data("Hello world");

	std::cout << "data_ptr value: |" << dataPtr->getData() << "|" << std::endl;

	uintptr_t raw = Serializer::serialize(dataPtr);

	std::cout << "Serializing result: " << raw << std::endl;

	Data *unserializedDataPtr = Serializer::deserialize(raw);

	std::cout << "Deserialization, userialized_data_ptr value: |" << unserializedDataPtr->getData() << "|" << std::endl;

}
