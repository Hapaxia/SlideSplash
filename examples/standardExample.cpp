//////////////////////////////////////////////////////////////////////////////////////////////
//
//  SlideSplash *EXAMPLE*
//
//  by Hapax (https://github.com/Hapaxia)
//
//
//    Controls:
//
//  Escape          Quit (closes window during initial slideshow and recalled slideshow but not the main application)
//  Space           Recalls slideshow from "main application" (the empty window) - does not close main application
//  Return          Skips slideshow (skips to main application during initial slideshow and returns to main application from recalled slideshow)
//  Any other key   Skips slide
//  Mouse Button    Skips slide
//
//////////////////////////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <SlideSplash.hpp>

int main()
{
	const std::string imagePath{ "images/" };
	const std::vector<std::string> imageFilenames
	{
		imagePath + "landscape-1436382_1920.jpg",
		imagePath + "cat-1455468_1920.jpg",
		imagePath + "mountain-1209533_1920.jpg",
		imagePath + "binary-1282366_1920.jpg",
		imagePath + "piano-1396970_1920.jpg",
		imagePath + "adler-62588_1920.jpg",
		imagePath + "street-1209401_1920.jpg",
		imagePath + "tiger-165039_1280.jpg",
		imagePath + "sea-1209607_1920.jpg"
	};

	sf::RenderWindow window(sf::VideoMode(960, 540), "Slide Splash");

	SlideSplash slideSplash(window);
	if (!slideSplash.addImages(imageFilenames))
		return EXIT_FAILURE;
	for (auto& slide : slideSplash.slides)
	{
		slide.sizing = SlideSplash::Slide::Sizing::Zoom;
		slide.texture.setSmooth(true);
	}
	slideSplash.setBackgroundColor(sf::Color::White);

	if (!slideSplash.play())
		window.close();
	else
		window.setTitle("Main application");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					window.setTitle("Slide Splash started inside window loop");
					if (!slideSplash.play())
						window.close();
					else
						window.setTitle("Main application returned");
				}
			}
		}

		window.clear(sf::Color::White);
		window.display();
	}

	return EXIT_SUCCESS;
}
