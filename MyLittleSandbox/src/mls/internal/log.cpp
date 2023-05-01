#include "mlspch.h"
#include "log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace mls_internal {
		
	void log::initialize(spdlog::level::level_enum log_level) {
		//Colour start, [T], [Log Name, Log Level], Message, [Filename, Line, Func], Colour end.
		spdlog::set_pattern("%^[%T] [MLS : %l] %v[%s : %# : %!()]%$");
		spdlog::set_level(log_level);
	}
}