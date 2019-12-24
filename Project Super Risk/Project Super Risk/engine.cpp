#include "engine.h"

GameController::GameController(const std::string& name) :
	_close{ false },
	_window{},
	_deltaClock{},
	_phAccumulator{},
	_phUps{ sf::seconds(1.f / 60.f) },
	_name{ name },
	_vmode{ 640, 480 },
	_wstyle{ WindowStyle::Default }
{}
GameController::~GameController()
{
	_close = true;
	if (_window.isOpen())
		_window.close();
	if (!_objs.empty())
		destroyAllGameObjects();
}

void GameController::start()
{
	init();
	loop();
}

void GameController::close()
{

}

void GameController::setVideoMode(const sf::VideoMode& mode, bool apply)
{
	_vmode = mode;
	if (apply)
		resetWindow();
}
void GameController::setWindowStyle(const uint32_t style, bool apply)
{
	_wstyle = style;
	if (apply)
		resetWindow();
}
void GameController::resetWindow()
{
	if (_close)
		return;

	if (_window.isOpen())
		_window.close();
	_window.create(_vmode, _name.c_str(), _wstyle);
}

bool GameController::isFullscreen() { return (_wstyle & WindowStyle::Fullscreen) != 0; }

void GameController::init()
{
	resetWindow();
}

void GameController::loop()
{
	while (!_close)
	{
		processEvents();

		while (_phAccumulator > _phUps)
		{
			delta_t delta = _deltaClock.getElapsedTime().asSeconds();
			_phAccumulator -= _phUps;
			update(delta);
		}

		render();
	}
}

void GameController::update(const delta_t delta)
{

}

void GameController::render()
{

}

void GameController::processEvents()
{

}
