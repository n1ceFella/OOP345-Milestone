#include <iostream>
#include "Workstation.h"

using namespace std;
namespace sdds 
{
	deque<CustomerOrder> g_pending{};
	deque<CustomerOrder> g_completed{};
	deque<CustomerOrder> g_incomplete{};

	Workstation::Workstation(const string& record) : Station(record) {}

	void Workstation::fill(std::ostream& os) {
		if (m_orders.size() > 0){ // !=0
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder() {
		//bool moved = false;
		if (!m_orders.empty())
		{
			//CustomerOrder& order = m_orders.front();
			// if the order is filled at this station, or the invetory of this station is insufficent (==0)
			if (m_orders.front().isItemFilled(getItemName()) || !getQuantity()) //this->getQuantity() == 0
			{
				//if there is a nextStation, move to next station
				if (m_pNextStation)
				{
					*m_pNextStation += (std::move(m_orders.front()));

				}
				//if at the end of the managerLine
				//move ot complete que if all items in the order is filled
				//else move to incomplete que
				else 
					m_orders.front().isOrderFilled() ? 
						g_completed.push_back(std::move(m_orders.front())) : 
						g_incomplete.push_back(std::move(m_orders.front()));
				//{
				//	if (order.isOrderFilled())
				//	{
				//		completed.push_back(std::move(order));
				//	}
				//	else
				//	{
				//		incomplete.push_back(std::move(order));
				//	}
				//}
				m_orders.pop_front();
				//moved = true;
				return true;
				
			}
		}
		return false;
	}

	void Workstation::setNextStation(Workstation* station) {
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation()const {
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os) const {
		m_pNextStation ?
			os << getItemName() << " --> " << m_pNextStation->getItemName() << std::endl :
			os << getItemName() << " --> " << "End of Line" << std::endl;
		//if (!m_pNextStation)
		//{
		//	os << getItemName() << " --> " << "End of Line" << std::endl;
		//}
		//else
		//{
		//	os << getItemName() << " --> " << m_pNextStation->getItemName() << std::endl;
		//}
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(std::move(newOrder));
		return *this;
	} 
}