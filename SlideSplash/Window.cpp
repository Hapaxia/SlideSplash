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

#include "Window.hpp"

SlideSplashWindow::SlideSplashWindow(const sf::Vector2u& size, const std::string& name, const sf::Uint32& style)
	: m_size(size)
	, m_name(name)
	, m_style(style)
	, m_window()
	, m_slideSplash(m_window)
{
}

bool SlideSplashWindow::play()
{
	auto& slides = getSlides();
	if (slides.size() == 0)
		return true;
	if (m_size == sf::Vector2u(0u, 0u))
		m_size = slides[0].texture.getSize();

	const sf::VideoMode desktopMode{ sf::VideoMode::getDesktopMode() };
	m_window.create(sf::VideoMode(m_size.x, m_size.y), m_name, m_style);
	m_window.setPosition(sf::Vector2i((static_cast<int>(desktopMode.width) - m_size.x) / 2, (static_cast<int>(desktopMode.height) - m_size.y) / 2));
	m_window.setVerticalSyncEnabled(true);

	bool result{ m_slideSplash.play() };

	m_window.close();
	return result;
}

void SlideSplashWindow::setSize(const sf::Vector2u& size)
{
	m_size = size;
}

void SlideSplashWindow::setName(const std::string& name)
{
	m_name = name;
}

void SlideSplashWindow::setStyle(const sf::Uint32& style)
{
	m_style = style;
}

bool SlideSplashWindow::addImage(const std::string& filename)
{
	return m_slideSplash.addImage(filename);
}

bool SlideSplashWindow::addImages(const std::vector<std::string>& filenames)
{
	return m_slideSplash.addImages(filenames);
}

void SlideSplashWindow::setBackgroundColor(const sf::Color& color)
{
	m_slideSplash.setBackgroundColor(color);
}

void SlideSplashWindow::setSkipKey(const sf::Keyboard::Key& key)
{
	m_slideSplash.setSkipKey(key);
}

void SlideSplashWindow::setCloseKey(const sf::Keyboard::Key& key)
{
	m_slideSplash.setCloseKey(key);
}

std::vector<SlideSplash::Slide>& SlideSplashWindow::getSlides()
{
	return m_slideSplash.slides;
}
