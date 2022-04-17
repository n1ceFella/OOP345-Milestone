//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           17.04.2022
// I confirm that I am the only author of this file
// and the content was created entirely by me.
//==============================================

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

			firstWorkstation = util.extractToken(str, next_pos, more);
			secondWorkstation = util.extractToken(str, next_pos, more);

			firstStation_ptr = *find_if(stations.begin(), stations.end(), [&](Workstation* ws) {return ws->getItemName() == firstWorkstation; });
			m_activeLine.push_back(firstStation_ptr);

			if (!secondWorkstation.empty()) {
				secondStation_ptr = *find_if(stations.begin(), stations.end(), [&](Workstation* ws) {
					return ws->getItemName() == secondWorkstation; });
			}
			firstStation_ptr->setNextStation(secondStation_ptr);
		}
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws1) {
			auto firstStation = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws2) {
				return ws1 == ws2->getNextStation();
				});
			if (firstStation == m_activeLine.end())
				m_firstStation = ws1;
			});

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

		static size_t count{};
		os << "Line Manager Iteration: " << ++count << std::endl;

		if (!g_pending.empty())
		{
			*m_firstStation += std::move(g_pending.front());
			g_pending.pop_front();

		}
		for (auto line : m_activeLine) {
			line->fill(os);
		}
		for (auto line : m_activeLine) {
			line->attemptToMoveOrder();
		}

		return (g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder;
	}
}
