#pragma once

#include "mls/core.h"

#include <codeanalysis/warnings.h>
#pragma warning(push)
#pragma warning (disable : ALL_CODE_ANALYSIS_WARNINGS)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace mls_internal {
		
	class log : private mls::no_copy {

		MLS_INTERNAL;

	private:
		void initialize(spdlog::level::level_enum log_level);

	private:
		log() = default;
		~log() = default;

	public:
		template <typename... Args>
		static inline void print(spdlog::source_loc src, spdlog::level::level_enum level, Args&&... args) {
				
			constexpr auto size = sizeof...(Args);
			
			std::string buffer;
			const std::string_view token = "{} ";

			buffer.reserve(size * token.size());

			for (int i = 0; i < size; ++i) {
				buffer.append(token);
			}
	
			spdlog::log(src, level, buffer, std::forward<Args>(args)...);
		}
	};
}

#if defined(MLS_DEBUG)
	#define MLS_TRACE(...)  ::mls_internal::log::print(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::trace, __VA_ARGS__)
	#define MLS_INFO(...)	::mls_internal::log::print(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::info, __VA_ARGS__)
	#define MLS_WARN(...)	::mls_internal::log::print(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::warn, __VA_ARGS__)
	#define MLS_ERROR(...)	::mls_internal::log::print(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::err, __VA_ARGS__)
	#define MLS_FATAL(...)  ::mls_internal::log::print(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::critical, __VA_ARGS__)
	#define MLS_ASSERT(condition, message) if (condition) { MLS_FATAL(message); __debugbreak(); }

	#define MLS_SET_LOG_LEVEL_TRACE ::spdlog::set_level(spdlog::level::trace)
	#define MLS_SET_LOG_LEVEL_INFO ::spdlog::set_level(spdlog::level::info)
	#define MLS_SET_LOG_LEVEL_WARN ::spdlog::set_level(spdlog::level::warn)
	#define MLS_SET_LOG_LEVEL_ERROR ::spdlog::set_level(spdlog::level::err)
	#define MLS_SET_LOG_LEVEL_FATAL ::spdlog::set_level(spdlog::level::critical)
#else
	#define MLS_TRACE(...)
	#define MLS_INFO(...)
	#define MLS_WARN(...)
	#define MLS_ERROR(...)
	#define MLS_FATAL(...)
	#define MLS_ASSERT(condition, message)

	#define MLS_SET_LOG_LEVEL_TRACE
	#define MLS_SET_LOG_LEVEL_INFO
	#define MLS_SET_LOG_LEVEL_WARN 
	#define MLS_SET_LOG_LEVEL_ERROR
	#define MLS_SET_LOG_LEVEL_FATAL
#endif