#pragma once
/*!
	@file singleton.h
	@brief A thread safe singleton design pattern using Meyers method.
	@author khimleesi
	@date 01/05/2023
	@copyright Apache Licence 2.0
*******************************************************************************************************************/
#include "no_copy.h"

namespace mls {
	namespace utilities {
		/*!
			@brief
				Fully templated singleton class. Make the singleton a friend of your class to use.
				
			@warning
				See my blog post on the proper usage of the singleton design pattern [here](https://www.khimleesi.com/post/singleton-design-pattern-meyers-method)

			@code{.cpp}
				class InputManager {
			
				friend class singleton<InputManager>;

				private:
					InputManager() = default;
					~InputManager() = default;
				};

				using Input = singleton<InputManager>;
			@endcode

			## Usage
			@code{.cpp}
				Input::get().doSomething();
			@endcode
		*******************************************************************************************************************/
		template <class T>
		class singleton : private no_copy {

		public:
			static T& get() {

				static T instance;
				return instance;
			}

		private:
			singleton() = delete;
			~singleton() = delete;
		};
	}
}