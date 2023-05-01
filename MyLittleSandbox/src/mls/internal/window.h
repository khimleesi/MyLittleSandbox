#pragma once

#include "mls/core.h"

struct SDL_Window;

namespace mls_internal {

	class window : private mls::no_copy {

		MLS_INTERNAL;
			
		struct sr_window_attributes {

			std::string title;
			unsigned int width;
			unsigned int height;
			bool fullscreen;

		private:
			MLS_SERIALIZE(
				MLS_NVP(title),
				MLS_NVP(width),
				MLS_NVP(height),
				MLS_NVP(fullscreen));
		};

	public:
		void swap_buffers();

		SDL_Window* get_window() const { return m_window_handle; }
		const unsigned int& get_height() const { return m_attributes.height; }
		const unsigned int& get_width() const { return m_attributes.width; }

	private:
		window(const std::string& file_path);
		~window();

	private:
		bool initialize(const std::string& file_path);
		void shutdown();

	private:
		sr_window_attributes m_attributes;
		SDL_Window* m_window_handle;
	};
}