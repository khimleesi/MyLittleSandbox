#pragma once

#include "mls/core.h"

typedef void* SDL_GLContext;

namespace mls_internal {

	class context : private mls::no_copy {

		MLS_INTERNAL;

		struct sr_context_attributes {

			bool vsync;
			float r, g, b, a;

		private:
			MLS_SERIALIZE(
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
		void enable_blending(bool blending);
		void enable_depth(bool depth);
		void enable_depth_writing(bool depth_writing);
		void cull_back_face(bool cull);

	private:
		context(const std::string& file_path, void* window);
		~context();

	private:
		bool initialize(const std::string& file_path, void* window);
		void shutdown();

	private:
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