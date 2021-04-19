#include "Game.hpp"

#include "Utility/Keyboard.hpp"
#include "GameStates/MainMenuState.hpp"

#include <TGUI/TGUI.hpp>

Game::Game()
	: m_window(sf::VideoMode(400, 600), "PianoTiles")
{
	tgui::setBackend(std::make_shared<tgui::BackendSFML>());

	if (!sf::Shader::isAvailable())
	{
		throw std::runtime_error("Shader is not available in your computer. Please do something.");
	}

	m_window.setKeyRepeatEnabled(false);
	m_window.setFramerateLimit(60);

	m_gameStateManager.push<MainMenuState>(m_gameStateManager, m_window);
}

void Game::run()
{
	m_gameStateManager.update();

	const sf::Time fixedUpdateInterval = sf::seconds(1.0f / 60.0f);

	sf::Clock timer;
	sf::Time elapsed = sf::Time::Zero;
	sf::Time lag = sf::Time::Zero;

	while (m_window.isOpen() && !m_gameStateManager.isEmpty())
	{
		zfge::GameState& currentState = m_gameStateManager.peek();
		
		elapsed = timer.restart();
		lag += elapsed;
	
		handleEvent();
		
		currentState.update(elapsed.asSeconds());

		while (lag >= fixedUpdateInterval)
		{
			lag -= fixedUpdateInterval;
			currentState.fixedUpdate(fixedUpdateInterval.asSeconds());
		}

		m_window.clear();
		currentState.draw(m_window);
		m_window.display();

		m_gameStateManager.update();
	}
}

void Game::handleEvent()
{
	zfge::GameState& currentState = m_gameStateManager.peek();

	for (sf::Event event; m_window.pollEvent(event);)
	{
		if (event.type == sf::Event::KeyPressed)
			zfge::Keyboard::setKey(event.key.code, true);
		else if (event.type == sf::Event::KeyReleased)
			zfge::Keyboard::setKey(event.key.code, false);

		currentState.handleEvent(event);
	}
}

Game::~Game()
{
	tgui::setBackend(nullptr);
}
