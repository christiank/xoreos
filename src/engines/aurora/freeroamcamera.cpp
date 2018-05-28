/* xoreos - A reimplementation of BioWare's Aurora engine
 *
 * xoreos is the legal property of its developers, whose names
 * can be found in the AUTHORS file distributed with this source
 * distribution.
 *
 * xoreos is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * xoreos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with xoreos. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file
 *  Engine utility class for free-roam camera handling.
 */

#include "src/common/configman.h"

#include "src/graphics/camera.h"

#include "src/engines/aurora/freeroamcamera.h"

DECLARE_SINGLETON(Engines::FreeRoamCamera)

namespace Engines {

bool FreeRoamCamera::handleCameraInput(const Events::Event &e) {
	if      (e.type == Events::kEventKeyDown)
		return handleCameraKeyboardInput(e);
	else if (e.type == Events::kEventMouseMove)
		return handleCameraMouseInput(e);

	return false;
}

bool FreeRoamCamera::handleCameraKeyboardInput(const Events::Event &e) {
	float multiplier = 1.0f;
	if (e.key.keysym.mod & KMOD_SHIFT)
		multiplier = 5.0f;

	if      (e.key.keysym.sym      == SDLK_UP)
		CameraMan.moveRelative(0.0f, 0.0f, multiplier * -0.5f);
	else if (e.key.keysym.sym      == SDLK_DOWN)
		CameraMan.moveRelative(0.0f, 0.0f, multiplier *  0.5f);
	else if (e.key.keysym.sym      == SDLK_RIGHT)
		CameraMan.turn( 0.0f, 0.0f, multiplier * -5.0f);
	else if (e.key.keysym.sym      == SDLK_LEFT)
		CameraMan.turn( 0.0f, 0.0f, multiplier *  5.0f);
	else if (e.key.keysym.scancode == SDL_SCANCODE_W)
		CameraMan.moveRelative(0.0f, 0.0f, multiplier * -0.5f);
	else if (e.key.keysym.scancode == SDL_SCANCODE_S)
		CameraMan.moveRelative(0.0f, 0.0f, multiplier *  0.5f);
	else if (e.key.keysym.scancode == SDL_SCANCODE_D)
		CameraMan.turn( 0.0f, 0.0f, multiplier * -5.0f);
	else if (e.key.keysym.scancode == SDL_SCANCODE_A)
		CameraMan.turn( 0.0f, 0.0f, multiplier *  5.0f);
	else if (e.key.keysym.scancode == SDL_SCANCODE_Q)
		CameraMan.moveRelative(multiplier * -0.5f, 0.0f, 0.0f);
	else if (e.key.keysym.scancode == SDL_SCANCODE_E)
		CameraMan.moveRelative(multiplier *  0.5f, 0.0f, 0.0f);
	else if (e.key.keysym.sym      == SDLK_INSERT)
		CameraMan.moveRelative(0.0f, multiplier *  0.5f, 0.0f);
	else if (e.key.keysym.sym      == SDLK_DELETE)
		CameraMan.moveRelative(0.0f, multiplier * -0.5f, 0.0f);
	else if (e.key.keysym.sym      == SDLK_PAGEUP) {
		if (ConfigMan.getBool("invertyaxis"))
			multiplier = -multiplier;
		CameraMan.turn(multiplier *  5.0f,	0.0f, 0.0f);
	} else if (e.key.keysym.sym    == SDLK_PAGEDOWN) {
		if (ConfigMan.getBool("invertyaxis"))
			multiplier = -multiplier;
		CameraMan.turn(multiplier * -5.0f,	0.0f, 0.0f);
	} else if (e.key.keysym.sym      == SDLK_END) {
		const float *orient = CameraMan.getOrientation();

		CameraMan.setOrientation(90.0f, orient[1], orient[2]);
	} else
		return false;

	return true;
}

bool FreeRoamCamera::handleCameraMouseInput(const Events::Event &e) {
	float x_multiplier = -0.5f;
	float y_multiplier = -0.5f;

	// Holding down the middle mouse button enables free look.
	if (e.motion.state & SDL_BUTTON(2)) {
		if (ConfigMan.getBool("invertxaxis"))
			x_multiplier = -x_multiplier;
		if (ConfigMan.getBool("invertyaxis"))
			y_multiplier = -y_multiplier;
		CameraMan.turn(y_multiplier * e.motion.yrel, 0.0f, x_multiplier * e.motion.xrel);
	} else {
		return false;
	}

	return true;
}

} // End of namespace Engines
