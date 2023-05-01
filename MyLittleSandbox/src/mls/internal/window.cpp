#include "mlspch.h"
#include <sdl/sdl.h>
#include "mls/internal/log.h"
#include "mls/internal/serializer.h"
#include "window.h"

namespace mls_internal {
		
	window::window(const std::string& file_path) :
		m_attributes(),
		m_window_handle(nullptr) {

		initialize(file_path);
	}

	window::~window() {
		
		shutdown();
	}

	bool window::initialize(const std::string& file_path) {

		serializer sr;
		if(!sr.load(file_path, m_attributes)) {
				return false;
			}

		if (SDL_Init(SDL_INIT_EVERYTHING) == -1) { 
			MLS_ERROR("SDL failed to initialize");
			return false; 
		}

		int screenFlag = (m_attributes.fullscreen) ? SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN : SDL_WINDOW_OPENGL;

		m_window_handle = SDL_CreateWindow(
			m_attributes.title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			m_attributes.width, m_attributes.height,
			screenFlag);

		if (!m_window_handle) {
			MLS_ERROR("Window could not be created!");
			return false;
		}
		
		//-- Initialize context
	
		//InitializePerspective();
		//m_perspective = glm::perspective(m_fieldOfView, GetAspectRatio(), NEAR_VIEW, FAR_VIEW);
		//m_defaultPerspective = glm::perspective(MAX_FIELD_OF_VIEW, GetAspectRatio(), NEAR_VIEW, FAR_VIEW);

		//InitializeOrthographic();
		//m_orthographic = glm::ortho(0.0f, (float)m_width, 0.0f, (float)m_height, NEAR_VIEW, FAR_VIEW);
		MLS_INFO("Window created successfully!");

		return true;
	}

	void window::shutdown() {

		SDL_DestroyWindow(m_window_handle);
		SDL_Quit();

		MLS_INFO("Window shut down successfully.");
	}

	void window::swap_buffers()
	{
		SDL_GL_SwapWindow(m_window_handle);
	}
}