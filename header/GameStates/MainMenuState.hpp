#pragma once

#include "GameStateManager.hpp"
#include "GameStates/GameState.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <TGUI/Core.hpp>
#include <TGUI/Backends/SFML.hpp>

class MainMenuState final : public zfge::GameState
{
public:
	MainMenuState(zfge::GameStateManager& gameStateManager, sf::RenderTarget& mainWindow);

	void update(float deltaTime) override;

	void handleEvent(sf::Event event) override;
	void draw(sf::RenderTarget& target) const override;

private:
	void handleKeyPress(sf::Keyboard::Key key);

	zfge::GameStateManager& m_gameStateManager;
	
	sf::RenderTarget& m_mainWindow;

	mutable tgui::GuiSFML m_gui;
};
