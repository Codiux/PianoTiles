#include "GameStates/MainMenuState.hpp"

#include <SFML/Graphics.hpp>

#include <TGUI/Widgets/Button.hpp>

MainMenuState::MainMenuState(zfge::GameStateManager& gameStateManager, sf::RenderTarget& target)
	: m_gameStateManager{gameStateManager}
	, m_mainWindow{target}
	, m_gui{target}
{
	auto button = tgui::Button::create("Test");
	button->setSize("50%", "50%");
	button->setPosition("(&.width - width) / 2", "(&.height - height) / 2");
	m_gui.add(button);
}

void MainMenuState::update(float deltaTime)
{

}

void MainMenuState::handleEvent(sf::Event event)
{
	m_gui.handleEvent(event);

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
	m_gui.draw();
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
