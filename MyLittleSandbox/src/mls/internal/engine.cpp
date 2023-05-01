#include "mlspch.h"
#include "mls/internal/serializer.h"
#include "mls/internal/log.h"
#include "engine.h"

namespace mls_internal {

	engine::engine() {
			
		initialize();
	}

	engine::~engine() {

		shutdown();
	}

	void engine::initialize() {

		//the logger
		log logger;
		logger.initialize(spdlog::level::level_enum::warn);

		//the serializer
		serializer sr;
		sr.initialize("assets\\sr_extensions.ext");

		//the window
		m_window = new window("assets\\sr_window.attributes");
		
		//the context
		m_context = new context("assets\\sr_context.attributes", m_window);
	}

	void engine::shutdown() {

		//the context
		delete m_context;

		//the window
		delete m_window;

		//the serializer
		serializer sr;
		sr.shutdown("assets\\sr_extensions.ext");
	}


	window& engine::get_window() const
	{
		return *m_window;
	}

	context& engine::get_context() const
	{
		return *m_context;
	}

}