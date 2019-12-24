#pragma once

#include <SFML/Graphics.hpp>
#include <cinttypes>

#include "game_objects.h"

namespace WindowStyle = sf::Style;

class GameController : public GameObjectContainer
{
private:
	bool _close;
	sf::RenderWindow _window;

	sf::Clock _deltaClock;
	sf::Time _phAccumulator;
	sf::Time _phUps;

	std::string _name;
	sf::VideoMode _vmode;
	uint32_t _wstyle;

public:
	GameController(const std::string& name);
	~GameController();

	void start();

	void close();

	void setVideoMode(const sf::VideoMode& mode, bool apply = true);
	void setWindowStyle(const uint32_t style, bool apply = true);
	void resetWindow();

	bool isFullscreen();

private:
	void init();
	void loop();
	void update(const delta_t delta);
	void render();
	void processEvents();
};
