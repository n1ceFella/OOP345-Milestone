//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           02.04.2022
//==============================================

//#include <string>
//#include <iostream>
//#include <algorithm>
//#include "Station.h"
#include "CustomerOrder.h"

using namespace std;
namespace sdds
{
	CustomerOrder::CustomerOrder(const CustomerOrder& rightOperand) {
		throw std::string("Error, customer order cannot be copied");
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& rightOperand) noexcept {
		*this = std::move(rightOperand);
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
}