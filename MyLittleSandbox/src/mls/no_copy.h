#pragma once
/*!
	@file no_copy.h
	@brief Disables copying and assignment in any classes that derive from no_copy.
	@author khimleesi
	@date 01/05/2023
	@copyright Apache Licence 2.0
*******************************************************************************************************************/
namespace mls {
	/*!
		@brief
			Derive from no_copy to automatically disable copying and assignment of classes.
	*******************************************************************************************************************/
	class no_copy {

	protected:
		no_copy() = default;
		~no_copy() = default;
		no_copy(const no_copy&) = delete;
		no_copy& operator=(const no_copy&) = delete;
	};
}