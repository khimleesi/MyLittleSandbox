#include "mlspch.h"
#include "mls/internal/engine.h"
#include "access.h"

namespace mls {
	
	using engine = utilities::singleton<mls_internal::engine>;
	
	namespace ctx {

		void set_clear_color(float r, float g, float b, float a)
		{
			engine::get().get_context().set_clear_color(r, g, b, a);
		}
		
		void clear()
		{
			engine::get().get_context().clear();
		}
	}


	namespace win {

		void swap_buffers() {
			
			engine::get().get_window().swap_buffers();
		}
	}
}