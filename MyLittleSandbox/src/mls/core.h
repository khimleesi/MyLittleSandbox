#pragma once
/*!
	@file core.h
	@brief Contains core functionality of the engine.
	@author khimleesi
	@date 01/05/2023
	@copyright Apache Licence 2.0
*******************************************************************************************************************/
#include "mls/no_copy.h"

#include <codeanalysis/warnings.h>
#pragma warning(push)
#pragma warning (disable : ALL_CODE_ANALYSIS_WARNINGS)
#include <cereal/includes.hpp>
#pragma warning(pop)

#if !defined(MLS_PLATFORM_WINDOWS)
	#error MyLittleSandbox only supports Windows!
#endif

#if defined(MLS_DEBUG)
	#define VLD_FORCE_ENABLE
	#include <vleak/vld.h>
#endif
/*!
	@brief
		Creates a name-value pair of a passed in variable.

	@param variable
		The POD variable.
*******************************************************************************************************************/
#define MLS_NVP(variable) ::cereal::make_nvp(#variable, variable)
/*!
	@brief
		To be defined in the class header that is serializable.

	@param ...
		The POD types to be serialized.

	@code{.cpp}
		class player : private no_copy {

			struct sr_player_attributes {

				std::string tag;
				int x;
				int y;
				bool isJumping;

			private:
				MLS_SERIALIZE(
					MLS_NVP(tag),
					MLS_NVP(x),
					MLS_NVP(y),
					MLS_NVP(isJumping));
			};

		private:
			sr_player_attributes m_attributes;
	@endcode
*******************************************************************************************************************/
#define MLS_SERIALIZE(...) friend class cereal::access; template <class Archive> void serialize(Archive& ar) { ar(__VA_ARGS__); }

#define MLS_INTERNAL friend class engine