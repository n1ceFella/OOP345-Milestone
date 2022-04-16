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
		size_t next_pos = 0;
		bool more = true;
		Station* firstStation_ptr{};
		Workstation* secondStation_ptr{};
		while (getline(f, str))
		{
			// the tokens from the record(line) 
			string firstWorkstation = util.extractToken(str,next_pos,more);
			string secondWorkstation = util.extractToken(str, next_pos, more);
			//string firstWorkstation = str.substr(0, str.find_first_of('|'));
			//string secondWorkstation = str.erase(0, firstWorkstation.size() + 1);

			//loop through stations, find the station witch the name match the record token "workstation"
			//push it into activeLine
			/*auto ws = std::find_if(stations.begin(), stations.end(), [&](Workstation* ws1) {return ws1->getItemName() == firstWorkstation; });*/
			
			firstStation_ptr = find_if(stations.begin(), stations.end(), [&](Workstation* ws) {return ws->getItemName() == firstWorkstation; });
			m_activeLine.push_back(firstStation_ptr);

			//if the string nextworkstaion is not empty
			//loop through stations agian, find the station wich the name mathc the record token "next workstation"
			//set this station as the next station of this record

			//else(nextworkstation string is empty), set the next station pointer point to nullptr			
			if (!secondWorkstation.empty())
			{
				for_each(stations.begin(), stations.end(), [&](Workstation* ws) {
					if (ws->getItemName() == secondWorkstation)
						secondStation_ptr->setNextStation(ws);
					});
			}
			else
			{
				firstStation_ptr->setNextStation(nullptr);
			}
		}

		//find the m_firstStation
		for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws1) {
			auto first = std::find_if(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* ws2) {
				return ws1 == ws2->getNextStation();
				});
			if (first == m_activeLine.end())
				m_firstStation = ws1;
			});

		//record the number of customer orders needs to be filled
		m_cntCustomerOrder = m_pending.size();
	}
	void LineManager::display(std::ostream& os)const {
		for_each(m_activeLine.begin(), m_activeLine.end(), [&os](const Workstation* ws) {ws->display(os); });
	}
}
