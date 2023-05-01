#pragma once
/*!
	@file string.h
	@brief Contains all string helper methods.
	@author khimleesi
	@date 01/05/2023
	@copyright Apache Licence 2.0
*******************************************************************************************************************/
namespace mls {
	namespace utilities {
		/*!
			@brief
				The main string helper class.
		*******************************************************************************************************************/
		class string {

		public:
			/*!
				@brief
					Removes all special characters (whitespaces and numbers) in a string.

				@params string
					The string to remove all special characters from.

				@returns
					A copy of the newly formatted string.
			*******************************************************************************************************************/
			static std::string remove_special_characters(const std::string& string);
			/*!
				@brief
					Searches a string for contained characters.

				@param string
					The string to search.

				@param chars
					The characters to search for.

				@returns
					True if characters found, false otherwise.
			*******************************************************************************************************************/
			static bool contains(const std::string& string, const std::string& chars);
		};
		
	}
}

