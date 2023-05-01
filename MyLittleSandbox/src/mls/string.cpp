#include "mlspch.h"
#include "string.h"

namespace mls {
	namespace utilities {

		std::string string::remove_special_characters(const std::string& string) {
			
			std::string result(string);
			result.erase(std::remove_if((result.begin()), result.end(), [](unsigned char c) {
				return (!std::isalnum(c) && !std::isspace(c)); //changed this line
				}), result.end());

			return result;
		}

		bool string::contains(const std::string& string, const std::string& chars) {
			
			return string.find(chars) != std::string::npos;
		}
	}
}