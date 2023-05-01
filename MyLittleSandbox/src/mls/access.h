#pragma once
/*!
	@file access.h
	@brief Allows access to the mls namespace.
	@author khimleesi
	@date 01/05/2023
	@copyright Apache Licence 2.0

	@namespace mls
	@brief The main mls namespace.

	@namespace mls::ctx
	@brief Contains all context functionality.
	
	A context in game development is the "blank canvas" to which we draw graphics to. It can be stored within the window class,
	and will normally need a handle to the window.  The context is usually created after the window.

	@namespace mls::win
	@brief Contains all window functionality.

	A window in game development is the main application window.
*******************************************************************************************************************/
namespace mls {
	namespace ctx {

		/*!
			@brief
				Sets the clear color of the context.

			@param r,g,b,a
				The red, green, blue and alpha channel values, should be a float value between 0-1.
		*******************************************************************************************************************/
		void set_clear_color(float r, float g, float b, float a);
		/*!
			@brief
				Clears the context. This should be done at the beginning of every frame.
		*******************************************************************************************************************/
		void clear();
	}

	namespace win {

		/*!
			@brief
				Swaps the window buffers. This should be done at the end of every frame.
		*******************************************************************************************************************/
		void swap_buffers();
	}
}