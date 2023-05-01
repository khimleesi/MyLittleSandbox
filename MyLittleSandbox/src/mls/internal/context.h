#pragma once

#include "mls/core.h"

typedef void* SDL_GLContext;

namespace mls_internal {

	class window;

	class context : private mls::no_copy {

		MLS_INTERNAL;

		struct sr_context_attributes {

			unsigned int version;
			unsigned int subversion;
			bool core;
			bool vsync;
			float r, g, b, a;

		private:
			MLS_SERIALIZE(
				MLS_NVP(version),
				MLS_NVP(subversion),
				MLS_NVP(core),
				MLS_NVP(vsync),
				MLS_NVP(r),
				MLS_NVP(g),
				MLS_NVP(b),
				MLS_NVP(a));
		};

	public:
		void set_clear_color(float r, float g, float b, float a);
		void clear();
		void set_viewport(int x, int y, int width, int height);

	private:
		context(const std::string& file_path, window* window);
		~context();

	private:
		bool initialize(const std::string& file_path, window* window);
		void shutdown();

	private:
		void set_attributes();
		void set_vsync();
		void set_anisotropy();
		void print_gpu_info();
		
	private:
		sr_context_attributes m_attributes;
		SDL_GLContext m_context;
		float m_anisotropy;//do we need this?
		bool m_anisotropy_supported;//do we need this?
	};
}