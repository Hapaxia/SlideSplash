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

#include "Standard.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>



namespace
{

inline bool isCorrectKey(const sf::Keyboard::Key& keyCode, const sf::Keyboard::Key& keyControl)
{
	if (keyControl == sf::Keyboard::Key::Unknown) // no keys accepted
		return false;
	if (keyControl == sf::Keyboard::Key::KeyCount) // any key accepted
		return true;
	return keyCode == keyControl;
}

inline void setSprite(sf::Sprite& sprite, const SlideSplash::Slide& slide, sf::RenderWindow* window)
{
	sprite.setTexture(slide.texture, true);
	const sf::Vector2f windowSize(window->getSize());
	const sf::Vector2f imageSize(slide.texture.getSize());
	if (slide.sizing == SlideSplash::Slide::Sizing::Zoom)
	{
		const float windowRatio{ windowSize.x / windowSize.y };
		const float imageRatio{ imageSize.x / imageSize.y };
		float scale;
		if (imageRatio > windowRatio)
		{
			scale = windowSize.y / imageSize.y;
			sprite.setPosition({ -(scale * imageSize.x - windowSize.x) / 2.f, 0.f });
		}
		else
		{
			scale = windowSize.x / imageSize.x;
			sprite.setPosition({ 0.f, -(scale * imageSize.y - windowSize.y) / 2.f });
		}
		sprite.setScale(scale, scale);
	}
	else // Stretch
	{
		sprite.setPosition({ 0, 0 });
		sprite.setScale({ windowSize.x / imageSize.x, windowSize.y / imageSize.y });
	}
}

inline bool nextSlide(unsigned int& slideNumber, sf::Clock& clock, const std::vector<SlideSplash::Slide>& slides, sf::Sprite& previousSprite, sf::RenderWindow* window)
{
	setSprite(previousSprite, slides[slideNumber], window);
	clock.restart();
	return (++slideNumber < slides.size());
}

} // namespace



SlideSplash::SlideSplash(sf::RenderWindow& window)
	: m_window(&window)
	, m_backgroundColor(sf::Color::Black)
	, m_skipKey(sf::Keyboard::Key::Return)
	, m_closeKey(sf::Keyboard::Key::Escape)
{
}

bool SlideSplash::addImage(const std::string& filename)
{
	slides.emplace_back();
	return slides.back().texture.loadFromFile(filename);
}

bool SlideSplash::addImages(const std::vector<std::string>& filenames)
{
	for (auto& filename : filenames)
	{
		if (!addImage(filename))
			return false;
	}
	return true;
}

void SlideSplash::setBackgroundColor(const sf::Color& color)
{
	m_backgroundColor = color;
}

void SlideSplash::setSkipKey(const sf::Keyboard::Key& key)
{
	m_skipKey = key;
}

void SlideSplash::setCloseKey(const sf::Keyboard::Key& key)
{
	m_closeKey = key;
}

bool SlideSplash::play()
{
	sf::Sprite mainSprite;
	sf::Sprite previousSprite;
	unsigned int slideNumber{ 0u };
	sf::Clock clock;
	bool inTransition{ true };
	setSprite(mainSprite, slides.front(), m_window);
	while (true)
	{
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				return false;
			else if (event.type == sf::Event::KeyPressed)
			{
				if (isCorrectKey(event.key.code, m_closeKey))
					return false;
				if (isCorrectKey(event.key.code, m_skipKey))
					return true;
				if (isCorrectKey(event.key.code, slides[slideNumber].key) && !inTransition)
				{
					if (nextSlide(slideNumber, clock, slides, previousSprite, m_window))
						setSprite(mainSprite, slides[slideNumber], m_window);
					else
						goto FINAL_TRANSITION;
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed && !inTransition)
			{
				if (slides[slideNumber].mouseButton)
				{
					if (nextSlide(slideNumber, clock, slides, previousSprite, m_window))
						setSprite(mainSprite, slides[slideNumber], m_window);
					else
						goto FINAL_TRANSITION;
				}
			}
		}
		if (clock.getElapsedTime() > slides[slideNumber].delay)
		{
			if (nextSlide(slideNumber, clock, slides, previousSprite, m_window))
				setSprite(mainSprite, slides[slideNumber], m_window);
			else
				goto FINAL_TRANSITION;
		}
		inTransition = clock.getElapsedTime() < slides[slideNumber].transition;
		m_window->clear(m_backgroundColor);
		if (inTransition)
		{
			float ratio{ clock.getElapsedTime() / slides[slideNumber].transition };
			mainSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(255 * ratio)));
			m_window->draw(previousSprite);
		}
		m_window->draw(mainSprite);
		m_window->display();
	}

FINAL_TRANSITION:

	setSprite(previousSprite, slides.back(), m_window);
	clock.restart();
	while (clock.getElapsedTime() < slides[0].transition)
	{
		float ratio{ 1.f - (clock.getElapsedTime() / slides[0].transition) };
		previousSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(255 * ratio)));
		m_window->clear(m_backgroundColor);
		m_window->draw(previousSprite);
		m_window->display();
	}
	return true;
}
