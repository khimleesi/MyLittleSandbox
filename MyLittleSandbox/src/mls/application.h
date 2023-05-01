#pragma once
/*!
	@file application.h
	@brief The abstract class of an application, to be derived and implemented by user.
	@author khimleesi
	@date 01/05/2023
	@copyright Apache Licence 2.0
*******************************************************************************************************************/
#include "core.h"

namespace mls {
	/*!
		@brief
			The abstract class of an application, to be derived and implemented by user.
	*******************************************************************************************************************/
	class application : private no_copy {
		
	protected:
		application();

	public:
		virtual ~application();

	public:
		/*!
			@brief
				Pure virtual function to be overriden by user.
				Responsible for initial setup of the game environment.

			@returns
				true or false
		*******************************************************************************************************************/
		virtual bool initialize() = 0;
		/*!
			@brief
				Pure virtual function to be overriden by user.
				The main game loop.
		*******************************************************************************************************************/
		virtual void run() = 0;
		/*!
			@brief
				Pure virtual function to be overriden by user.
				Responsible for destroying any memory allocated and calling any relevant shutdown functions upon game close.
		*******************************************************************************************************************/
		virtual void shutdown() = 0;
	};
}