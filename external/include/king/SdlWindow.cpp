#include "SdlWindow.h"

#include <stdexcept>
#include <string>
#include <sdl/SDL.h>

namespace King {
	SdlWindow::SdlWindow(unsigned int width, unsigned int height)
		: mSDLWindow(SDL_CreateWindow("KingTest"
		, SDL_WINDOWPOS_UNDEFINED
		, SDL_WINDOWPOS_UNDEFINED
		, width
		, height
		, SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL), SDL_DestroyWindow) {
		if (mSDLWindow == false) {
			throw std::runtime_error(std::string("Error creating window: ") + SDL_GetError());
		}
	}
	void SdlWindow::Show() {
		SDL_ShowWindow(mSDLWindow.get());
	}
	SdlWindow::operator SDL_Window*() {
		return mSDLWindow.get();
	}
}