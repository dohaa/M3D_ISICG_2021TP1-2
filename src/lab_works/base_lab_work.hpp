#ifndef __BASE_LAB_WORK_HPP__
#define __BASE_LAB_WORK_HPP__

#include "SDL.h"

namespace M3D_ISICG
{
	class BaseLabWork
	{
	  public:
		BaseLabWork()		   = default;
		virtual ~BaseLabWork() = default;

		// Initialization.
		virtual bool init() = 0;
		// Animation according to p_deltaTime (time since last frame).
		virtual void animate( const float p_deltaTime ) = 0;
		// Render one frame.
		virtual void render() = 0;
		// Handle events (keyboard, mouse).
		virtual void handleEvents( const SDL_Event & p_event ) = 0;
		// Display user interface.
		virtual void displayUI() = 0;
	};
} // namespace M3D_ISICG

#endif // __BASE_LAB_WORK_HPP__
