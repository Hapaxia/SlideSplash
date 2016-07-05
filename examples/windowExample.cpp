//////////////////////////////////////////////////////////////////////////////////////////////
//
//  SlideSplashWindow *EXAMPLE*
//
//  by Hapax (https://github.com/Hapaxia)
//
//
//    Controls:
//
//  Escape          Quit (closes window during initial slideshow and recalled slideshow but not the main application)
//  Mouse Button    Skips slide
//  Space           Skips slide / Recalls slideshow from "main application" (the empty window) - does not close main application
//  Return          Skips slideshow (skips to main application during initial slideshow and returns to main application from recalled slideshow)
//
//////////////////////////////////////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <SlideSplashWindow.hpp>

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

	// un-comment only one SlideSplashWindow declaration depending on your chosen SlideSplash window settings
	//SlideSplashWindow slideSplashWindow({ 480, 270 }, "Small", sf::Style::Titlebar);
	SlideSplashWindow slideSplashWindow({ 960, 540 }, "Medium", sf::Style::None);
	//SlideSplashWindow slideSplashWindow({ 1920, 1080 }, "Large", sf::Style::None);

	if (!slideSplashWindow.addImages(imageFilenames))
		return EXIT_FAILURE;
	for (auto& slide : slideSplashWindow.getSlides())
	{
		slide.sizing = SlideSplash::Slide::Sizing::Zoom;
		slide.texture.setSmooth(true);
		slide.key = sf::Keyboard::Space;
	}
	slideSplashWindow.getSlides()[0].transition = sf::seconds(0); // instant start-up and shut-down

	sf::RenderWindow window; // main window
	if (slideSplashWindow.play())
		window.create(sf::VideoMode(800, 600), "Main application");

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
					{
						window.setTitle("Slide Splash Window started");
						if (!slideSplashWindow.play())
							window.close();
						else
							window.setTitle("Main application returned");
					}
				}
			}
		}

		window.clear();
		window.display();
	}

	return EXIT_SUCCESS;
}
