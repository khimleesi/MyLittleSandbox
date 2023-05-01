#pragma once

#include "mls/core.h"
#include "mls/internal/context.h"
#include "mls/internal/window.h"
#include "mls/singleton.h"

namespace mls_internal {

	class engine : private mls::no_copy {

		friend class mls::utilities::singleton<engine>;

	public:
		window& get_window() const;
		context& get_context() const;

	private:
		engine();
		~engine();

	private:
		void initialize();
		void shutdown();
	
	public:
		//input
		//renderer
		//audio
		//api /sdl/opengl
		//interface
	private:
		window* m_window;
		context* m_context;
	};
}