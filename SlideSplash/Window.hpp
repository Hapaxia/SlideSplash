//////////////////////////////////////////////////////////////////////////////
//
// Slide Splash
//
// Copyright(c) 2016 M.J.Silk
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions :
//
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software.If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
// M.J.Silk
// MJSilk2@gmail.com
//
//////////////////////////////////////////////////////////////////////////////

#ifndef SLIDESPLASH_WINDOW_HPP
#define SLIDESPLASH_WINDOW_HPP

#include "Standard.hpp"
#include <SFML/Window/WindowStyle.hpp>

// Slide Splash Window (Slide Splash v1.2)
class SlideSplashWindow
{
public:
	SlideSplashWindow(const sf::Vector2u& size = { 0u, 0u }, const std::string& name = "", const sf::Uint32& style = sf::Style::None);

	bool play();

	void setSize(const sf::Vector2u& size);
	void setName(const std::string& name);
	void setStyle(const sf::Uint32& style);

	bool addImage(const std::string& filename);
	bool addImages(const std::vector<std::string>& filenames);
	void setBackgroundColor(const sf::Color& color);
	void setSkipKey(const sf::Keyboard::Key& key);
	void setCloseKey(const sf::Keyboard::Key& key);

	std::vector<SlideSplash::Slide>& getSlides();

private:
	sf::RenderWindow m_window;
	sf::Vector2u m_size;
	std::string m_name;
	sf::Uint32 m_style;
	SlideSplash m_slideSplash;
};

#endif // SLIDESPLASH_WINDOW_HPP
