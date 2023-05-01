#pragma once
/*!
	@file utilities.h
	@brief Contains all miscellaneous helper methods.
	@author khimleesi
	@date 01/05/2023
	@copyright Apache Licence 2.0

	@namespace mls::utilities
	@brief Contains all helper utilities.
*******************************************************************************************************************/
namespace mls { 
	namespace utilities {
		/*!
			@brief
				A helper class for data types.
		*******************************************************************************************************************/
		class types {

		public:
			/*!
				@brief
					Templated function that converts an enumeration to its underlying type (int / unsigned int).

				@param value
					Enumeration type T.

				@returns
					The underlying value of the enumeration.
			*******************************************************************************************************************/
			template <typename T>
			static auto enum_to_type(T const value) -> typename std::underlying_type<T>::type {
				
				return static_cast<typename std::underlying_type<T>::type>(value);
			}

		};
	}
}