#pragma once

#include "GameStateManager.hpp"
#include "GameStates/GameState.hpp"
#include "Game/ResourceIDs.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <TGUI/Core.hpp>
#include <TGUI/Backends/SFML.hpp>

#include <Thor/Resources.hpp>

class MainMenuState final : public zfge::GameState
{
public:
	MainMenuState(zfge::GameStateManager& gameStateManager, sf::RenderTarget& mainWindow);

	void update(float deltaTime) override;

	void handleEvent(sf::Event event) override;
	void draw(sf::RenderTarget& target) const override;

private:
	void handleKeyPress(sf::Keyboard::Key key);
	void handleKeyRelease(sf::Keyboard::Key key);

	void generateBlurredTexture();

	zfge::GameStateManager& m_gameStateManager;
	
	sf::RenderTarget& m_mainWindow;

	mutable tgui::GuiSFML m_gui;

	sf::Shader* m_blurShader {nullptr};
	float m_blurSigma = 5.0f;

	sf::Sprite m_rawSprite;
	sf::Sprite m_resultSprite;

	sf::RenderTexture m_shaderTarget1;
	sf::RenderTexture m_shaderTarget2;

	enum class ResultType
	{
		Original,
		OnePass,
		TwoPass
	};
	
	ResultType m_resultType {ResultType::Original};

	thor::ResourceHolder<sf::Shader, Shaders> m_shaders;
	thor::ResourceHolder<sf::Texture, std::string> m_textures;
};
