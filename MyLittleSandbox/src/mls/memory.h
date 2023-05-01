#pragma once
/*!
	@file memory.h
	@brief Contains all memory functionality.
	@author khimleesi
	@date 01/05/2023
	@copyright Apache Licence 2.0

	@namespace mls::alloc
	@brief Provides access to all memory allocation functionality.
*******************************************************************************************************************/
namespace mls {
	namespace alloc {

		/*!
			@brief
				Unique pointer wrapper.
		*******************************************************************************************************************/
		template<typename T>
		using scope = std::unique_ptr<T>;
		/*!
			@brief
				Creates a unique (scoped) pointer.

			@returns
				The unique pointer.

			@code{.cpp}
				mls::alloc::scope<mls::application> sandbox = mls::alloc::create_scope<Sandbox>();
			@endcode
		*******************************************************************************************************************/
		template<typename T, typename ... Args>
		constexpr scope<T> create_scope(Args&& ... args)
		{
			return std::make_unique<T>(std::forward<Args>(args)...);
		}
		/*!
			@brief
				Shared pointer wrapper.
		*******************************************************************************************************************/
		template<typename T>
		using ref = std::shared_ptr<T>;
		/*!
			@brief
				Creates a shared (referenced) pointer.

			@returns
				The shared pointer.

			@code{.cpp}
				mls::alloc::ref<mls::application> sandbox = mls::alloc::create_ref<Sandbox>();
			@endcode
		*******************************************************************************************************************/
		template<typename T, typename ... Args>
		constexpr ref<T> create_ref(Args&& ... args)
		{
			return std::make_shared<T>(std::forward<Args>(args)...);
		}
	}
}