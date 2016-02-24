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

#ifndef SLIDESPLASH_STANDARD_HPP
#define SLIDESPLASH_STANDARD_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>

// Slide Splash v1.2.1
class SlideSplash
{
public:
	struct Slide
	{
		enum class Sizing
		{
			Stretch,
			Zoom
		};

		sf::Texture texture;
		sf::Time delay{ sf::seconds(5.f) };
		sf::Time transition{ sf::seconds(2.f) };
		sf::Keyboard::Key key{ sf::Keyboard::Key::KeyCount }; // "Unknown" represents no key allowed. "KeyCount" represents any key allowed.
		bool mouseButton{ true };
		Sizing sizing{ Sizing::Stretch };
	};

	std::vector<Slide> slides;

	SlideSplash(sf::RenderWindow& window);
	bool play();
	bool addImage(const std::string& filename);
	bool addImages(const std::vector<std::string>& filenames);
	void setBackgroundColor(const sf::Color& color);
	void setSkipKey(const sf::Keyboard::Key& key);
	void setCloseKey(const sf::Keyboard::Key& key);

private:
	sf::RenderWindow* m_window;
	sf::Color m_backgroundColor;
	sf::Keyboard::Key m_skipKey;
	sf::Keyboard::Key m_closeKey;
};

#endif // SLIDESPLASH_STANDARD_HPP
