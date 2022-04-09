//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           02.04.2022
//==============================================

#include <string>
#include <iostream>
//#include <algorithm>
#include "Station.h"
#include "Utilities.h"
#include "CustomerOrder.h"

using namespace std;
namespace sdds
{
	size_t CustomerOrder::m_widthField = 0u;

	CustomerOrder::CustomerOrder(const std::string& str) {
		size_t next_pos = 0;
		Utilities util;
		bool more;
		m_name = util.extractToken(str, next_pos, more);
		m_product = util.extractToken(str, next_pos, more);
		for (size_t i = 0; i < str.size(); i++)
		{
			//count the delimiter number to get the items number in this order
			if (str[i] == util.getDelimiter())
			{
				m_cntItem++;
			}
		}
		m_cntItem--;

		//create new Iems objects for each object in the order
		m_lstItem = new Item* [m_cntItem];
		for (size_t i = 0; i < m_cntItem; i++)
		{
			m_lstItem[i] = new Item(util.extractToken(str, next_pos, more));
		}

		//set the field width for displaying
		m_widthField = m_widthField > util.getFieldWidth() ? m_widthField : util.getFieldWidth();
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& rightOperand) {
		throw std::string("Error, customer order cannot be copied");
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& rightOperand) noexcept {
		*this = std::move(rightOperand);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& rightOperand) noexcept {
		if (this != &rightOperand)
		{
			for (size_t i = 0; i < m_cntItem; i++)
			{
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			
			m_lstItem = rightOperand.m_lstItem;

			m_name = rightOperand.m_name;
			m_product = rightOperand.m_product;
			m_cntItem = rightOperand.m_cntItem;

			rightOperand.m_lstItem = nullptr;
			//rightOperand.m_name = "";
			//rightOperand.m_product = "";
			//rightOperand.m_cntItem = 0u;
		}
		return *this;
	}
	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++)
		{
				delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}
	bool CustomerOrder::isOrderFilled() const {
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (!m_lstItem[i]->m_isFilled)
				return false;
		}
		return true;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
			{
				if (!m_lstItem[i]->m_isFilled) return false;
			}
		}
		return true;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if ( m_lstItem[i]->m_itemName == station.getItemName())
			{
				if (station.getQuantity() > 0)
				{
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os.width(4);
					os.setf(ios::right);
					os << "Filled ";
					os.unsetf(ios::right);
					os << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
				else
				{
					os.setf(ios::right);
					os << "Unable to fill ";
					os.unsetf(ios::right);
					os << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
		}
	}
	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[";
			os.width(6);
			os.fill('0');
			os.setf(ios::right);
			os << m_lstItem[i]->m_serialNumber;
			os << "] ";
			os.fill(' ');
			os.width(m_widthField);
			os.setf(ios::left);
			os << m_lstItem[i]->m_itemName;
			os << " - ";
			m_lstItem[i]->m_isFilled ? os << "FILLED" << std::endl : os << "TO BE FILLED" << std::endl;
		}
	}
}