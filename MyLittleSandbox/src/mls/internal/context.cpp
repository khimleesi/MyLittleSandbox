#include "mlspch.h"
#include <sdl/sdl.h>
#include <opengl/glew.h>
#include "mls/internal/window.h"
#include "mls/internal/log.h"
#include "mls/internal/serializer.h"
#include "context.h"

namespace mls_internal {

	context::context(const std::string& file_path, window* window) {
		
		initialize(file_path, window);
	}

	context::~context()
	{
		shutdown();
	}

	bool context::initialize(const std::string& file_path, window* window) {
			
		if (!window) {
			MLS_ERROR("OpenGL context has no window!");
			return false;
		}

		serializer sr;
		if (!sr.load(file_path, m_attributes)) {
			return false;
		}

		set_attributes();

		m_context = SDL_GL_CreateContext(static_cast<SDL_Window*>(window->get_window()));

		if (!m_context) {
			MLS_ERROR("OpenGL context could not be created!");
			return false;
		}

		set_vsync();

		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK) {
			MLS_ERROR("Could not initialize GLEW!");
			return false;
		}

		print_gpu_info();
			
		set_viewport(0, 0, window->get_width(), window->get_height());

		//--- Explicity set the winding order (default is counter-clockwise)
		glFrontFace(GL_CCW);

		set_anisotropy();

		//--- Exponential correction; increase gamma so colours appear brighter
		//--- Not currently enabled as I have not setup gamma properly in shaders yet
		//glEnable(GL_FRAMEBUFFER_SRGB);
			
		MLS_INFO("GL Context created successfully!");

		return true;
	}

	void context::shutdown() {

		SDL_GL_DeleteContext(m_context);
		MLS_INFO("Context shut down successfully.");
	}

	void context::set_clear_color(float r, float g, float b, float a) {

		m_attributes.r = r;
		m_attributes.g = g;
		m_attributes.b = b;
		m_attributes.a = a;
	}

	void context::clear() {
			
		glClearColor(m_attributes.r, m_attributes.g, m_attributes.b, m_attributes.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void context::set_viewport(int x, int y, int width, int height) {
		
		glViewport(x, y, width, height);
	}

	void context::set_attributes() {

		//--- Set our OpenGL attributes before creating window
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

		//---- Enable multisampling
		glEnable(GL_MULTISAMPLE);

		//--- Set double buffering
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		//--- Check if OpenGL profile is core or compatibility
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, (m_attributes.core) ? SDL_GL_CONTEXT_PROFILE_CORE : SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
		MLS_TRACE("OpenGL Profile Enabled:", (m_attributes.core) ? "Core" : "Compatibility");
			
		//--- Set OpenGL context version
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, m_attributes.version);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, m_attributes.subversion); 
		MLS_TRACE("OpenGL Version:", m_attributes.version, ":", m_attributes.subversion);
	}

	void context::set_vsync() {
			
		if (SDL_GL_SetSwapInterval((int)m_attributes.vsync) == -1) {
			MLS_TRACE("VSync not supported.");
		}

		if (SDL_GL_GetSwapInterval() != (int)m_attributes.vsync) {
			MLS_TRACE("VSync settings determined by your graphics card.");
		}

		MLS_TRACE("VSync:", m_attributes.vsync);
	}

	void context::set_anisotropy() {

		//--- If anisotropic filtering is supported then use it
		if (glewIsSupported("GL_EXT_texture_filter_anisotropic") || GLEW_EXT_texture_filter_anisotropic) {

			GLfloat maxAnisotropy = 0.0f;
			GLfloat desiredAnisotropy = 4.0f;

			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);

			m_anisotropy = std::min(desiredAnisotropy, maxAnisotropy);

			m_anisotropy_supported = true;

			MLS_TRACE("Anisotropic filtering is supported. Max anisotropy:", maxAnisotropy);
		}
		else {
			m_anisotropy_supported = false;
			MLS_TRACE("Anisotropic filtering is not supported on your GPU.");
		}
	}

	void context::print_gpu_info() {
			
		MLS_TRACE("GPU Manufacturer:", (const char*)glGetString(GL_VENDOR));
		MLS_TRACE("GPU Make and Model:", (const char*)glGetString(GL_RENDERER));
		MLS_TRACE("Current OpenGL Version and Mode:", (const char*)glGetString(GL_VERSION));
		MLS_TRACE("GLSL Language Supported:", (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

		GLint numExtensions = 0;

		std::vector <const GLubyte*> extensions;

		glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);

		extensions.reserve(numExtensions);

		for (GLint x = 0; x < numExtensions; x++) {
			extensions.emplace_back(glGetStringi(GL_EXTENSIONS, x));
		}

		MLS_TRACE("Supported Extensions on GPU:");
		for (GLuint x = 0; x < extensions.size(); x++) {
			MLS_TRACE("[EXT]", (const char*)extensions[x]);
		}
	}
}