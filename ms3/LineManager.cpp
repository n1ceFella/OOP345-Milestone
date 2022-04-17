#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "LineManager.h"
#include "Workstation.h"
#include "Utilities.h"

using namespace std;
namespace sdds
{
	LineManager::LineManager(const string& file, const vector<Workstation*>& stations) {

		ifstream f(file);
		if (!f || file.empty()) {
			throw string("Something went wrong");
		}

		//if (file.empty()) {
		//	throw std::string("ERROR: No filename provided.");
		//}
		//if (!f)
		//	throw std::string("Unable to open [") + file + "] file.";
		Utilities util;
		string str;
		size_t next_pos;
		bool more;

		while (getline(f, str))
		{
			Workstation* firstStation_ptr{};
			Workstation* secondStation_ptr{};
			string firstWorkstation{};
			string secondWorkstation{};
			next_pos = 0;
			more = true;
			// the tokens from the record(line) 
			firstWorkstation = util.extractToken(str, next_pos, more);
			secondWorkstation = util.extractToken(str, next_pos, more);
			//string firstWorkstation = str.substr(0, str.find_first_of('|'));
			//string secondWorkstation = str.erase(0, firstWorkstation.size() + 1);

			//loop through stations, find the station witch the name match the record token "workstation"
			//push it into activeLine
			/*auto ws = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws1) {return ws1->getItemName() == firstWorkstation; });*/

			firstStation_ptr = *find_if(stations.begin(), stations.end(), [&](Workstation* ws) {return ws->getItemName() == firstWorkstation; });
			m_activeLine.push_back(firstStation_ptr);

			//if the string nextworkstaion is not empty
			//loop through stations agian, find the station wich the name mathc the record token "next workstation"
			//set this station as the next station of this record

			//else(nextworkstation string is empty), set the next station pointer point to nullptr	
			if (!secondWorkstation.empty()) {
				secondStation_ptr = *find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
					return ws->getItemName() == secondWorkstation; });
			}
			firstStation_ptr->setNextStation(secondStation_ptr);

			//if (!secondWorkstation.empty())
			//{
			//	for_each(stations.begin(), stations.end(), [&](Workstation* ws) {
			//		if (ws->getItemName() == secondWorkstation)
			//			firstStation_ptr->setNextStation(ws); //firstStation_ptr
			//		});
			//}
			//else
			//{
			//	firstStation_ptr->setNextStation(nullptr); //firstStation_ptr
			//}
		}

		//find the m_firstStation
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws1) {
			auto firstStation = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws2) {
				return ws1 == ws2->getNextStation();
				});
			if (firstStation == m_activeLine.end())
				m_firstStation = ws1;
			});

		//record the number of customer orders needs to be filled
		m_cntCustomerOrder = g_pending.size();
	}
	void LineManager::display(std::ostream& os)const {
		for_each(m_activeLine.begin(), m_activeLine.end(), [&os](const Workstation* ws) {ws->display(os); });
	}

	void LineManager::reorderStations() {
		std::vector<Workstation*> t = m_activeLine;
		m_activeLine[0] = m_firstStation;

		bool flag;
		for (size_t i = 0; i < m_activeLine.size() - 1; i++)
		{
			flag = false;
			for (size_t j = 0; j < t.size() && !flag; j++)
			{
				if (m_activeLine[i]->getNextStation() && m_activeLine[i]->getNextStation()->getItemName() == t[j]->getItemName())
				{
					m_activeLine[i + 1] = t[j];
					flag = true;
				}
			}
		}
	}

	bool LineManager::run(std::ostream& os) {
		//set a local variable for counting iterations
		//if there is orders in the pending vector, move the first one to the m_firstStation, remove this order from pending
		//loop through the line to fill
		//loop through the line to move the order(using attemptToMoveOrder())
		static size_t count{};
		os << "Line Manager Iteration: " << ++count << std::endl;

		if (!g_pending.empty())
		{
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();

		}
		for (auto line : m_activeLine) {
			line->fill(os);
			line->attemptToMoveOrder();
		}
		//for (size_t i = 0; i < m_activeLine.size(); i++)
		//{
		//	m_activeLine[i]->fill(os);

		//}
		//for (size_t i = 0; i < m_activeLine.size(); i++)
		//{
		//	m_activeLine[i]->attemptToMoveOrder();
		//}
		//check if all the orders are finished processing-- the sum of orders in complete and incomplete equals the number in the pending at the beginning
		return (g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder;
	}
}
