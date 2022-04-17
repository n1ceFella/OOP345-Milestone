//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           17.04.2022
// I confirm that I am the only author of this file
// and the content was created entirely by me.
//==============================================

#ifndef LINEMANAGER_H
#define LINEMANAGER_H
#include "Workstation.h"

namespace sdds 
{
	class LineManager
	{
	private:
		std::vector<Workstation*> m_activeLine;
		size_t m_cntCustomerOrder{};
		Workstation* m_firstStation{};
	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void reorderStations();
		bool run(std::ostream& os);
		void display(std::ostream& os)const;
	};
}

#endif // !LINEMANAGER_H
