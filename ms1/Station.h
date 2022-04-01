//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           31.03.2022
//==============================================

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>
#include <vector>
#include <list>
namespace sdds
{

	class Station
	{
	private:
		int m_id;
		std::string m_itemName;
		std::string m_description;
		size_t m_nextSerial;
		size_t itemsNum;
		static int m_widthField; //default 0;
		static int id_generator; //default 0;
	public:
		Station(const std::string& record);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}
#endif