#include <string>
#include "Utilities.h"
using namespace std;
namespace sdds
{
	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
	
		size_t pos = str.find(m_delimiter, next_pos);
		if (pos == next_pos)
			throw "pos = next_pos";
		string token = str.substr(next_pos, pos); // might include delimiter (deduct -1)
		if (m_widthField < token.size()) {
			//update ??????????????????????????????????????
		}
		if (pos != std::string::npos) {
			next_pos = pos;
			more = true;
		}
		else more = false;
		return token;
	}
	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter() {
		return m_delimiter;
	}
}

