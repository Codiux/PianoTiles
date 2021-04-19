#include "GameStates/MainMenuState.hpp"

#include <SFML/Graphics.hpp>

MainMenuState::MainMenuState(zfge::GameStateManager& gameStateManager, sf::RenderTarget& target)
	: m_gameStateManager(gameStateManager)
	, m_mainWindow(target)
{

}

void MainMenuState::update(float deltaTime)
{

}

void MainMenuState::handleEvent(sf::Event event)
{
	switch (event.type)
	{
		case sf::Event::Closed:
			m_gameStateManager.clear();
			break;
		case sf::Event::KeyPressed:
			handleKeyPress(event.key.code);
			break;
		default:
			break;
	}
}

void MainMenuState::draw(sf::RenderTarget& target) const
{
	
}

void MainMenuState::handleKeyPress(sf::Keyboard::Key key)
{
	using Key = sf::Keyboard::Key;

	switch (key)
	{
		case Key::Escape:
			m_gameStateManager.pop();
			break;
		default:
			break;
	}
}
