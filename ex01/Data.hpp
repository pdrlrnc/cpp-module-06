/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedde-so <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 12:22:38 by pedde-so          #+#    #+#             */
/*   Updated: 2026/09/19 12:22:40 by pedde-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
#define DATA_H

#include <string>

class Data {

	private:
		std::string _data;
	public:
		Data();
		~Data();
		Data(const Data& other);
		Data& operator=(const Data& other);
		Data(const std::string& data);
		
		std::string getData();
};

#endif
