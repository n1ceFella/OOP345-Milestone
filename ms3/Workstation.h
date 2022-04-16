#ifndef WORKSTATION_H
#define WORKSTATION_H
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds 
{
	extern std::deque<CustomerOrder> m_pending;
	extern std::deque<CustomerOrder> m_completed;
	extern std::deque<CustomerOrder> m_incomplete;

	class Workstation : public Station
	{
	private:
		std::deque<CustomerOrder> m_orders;
		Workstation* m_pNextStation{};
	public:
		Workstation(const std::string& record);
		Workstation(const Workstation& rightOperand) = delete;
		Workstation& operator=(const Workstation& rightOperand) = delete;
		Workstation(Workstation&& rightOperand) = delete;
		Workstation& operator=(Workstation&& rightOperand) = delete;
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station = nullptr);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
	};

}

#endif // !WORKSTATION_H
