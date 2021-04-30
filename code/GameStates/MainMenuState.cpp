#include "GameStates/MainMenuState.hpp"

#include "Utility/Keyboard.hpp"

#include <SFML/Graphics.hpp>

#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/Panel.hpp>

MainMenuState::MainMenuState(zfge::GameStateManager& gameStateManager, sf::RenderTarget& target)
	: m_gameStateManager{gameStateManager}
	, m_mainWindow{target}
	, m_gui{target}
{
	m_shaders.acquire(Shaders::GaussianBlur,
		thor::Resources::fromFile<sf::Shader>(
			"assets/shaders/gaussian_blur.frag",
			sf::Shader::Fragment
			)
		);

	m_textures.acquire("hello_world", thor::Resources::fromFile<sf::Texture>("assets/images/hello_world.png"));

	m_rawSprite.setTexture(m_textures["hello_world"], true);

	// Scale m_rawSprite to fit the window
	float scaleFactor = m_mainWindow.getView().getSize().x / m_textures["hello_world"].getSize().x;
	m_rawSprite.setScale(scaleFactor, scaleFactor);
	m_rawSprite.setRotation(10);
	m_rawSprite.setPosition(20.f, 20.0f);

	// Set up blurTarget render texture sizes
	sf::Vector2u shaderTargetSize(m_textures["hello_world"].getSize());
	m_shaderTarget1.create(shaderTargetSize.x, shaderTargetSize.y);
	m_shaderTarget2.create(shaderTargetSize.x, shaderTargetSize.y);

	// Set up blurShader
	m_blurShader = &m_shaders[Shaders::GaussianBlur];
	m_blurShader->setUniform("texture", sf::Shader::CurrentTexture);
	m_blurShader->setUniform("textureSize", static_cast<sf::Vector2f>(shaderTargetSize));
	m_blurShader->setUniform("sigma", m_blurSigma);

	generateBlurredTexture();
}

void MainMenuState::generateBlurredTexture()
{
	m_blurShader->setUniform("direction", sf::Vector2f(1, 0));

	sf::Sprite tmpSprite1(*m_rawSprite.getTexture());

	m_shaderTarget1.clear();
	m_shaderTarget1.draw(tmpSprite1, m_blurShader);
	m_shaderTarget1.display();

	m_blurShader->setUniform("direction", sf::Vector2f(0, 1));
	sf::Sprite tmpSprite2(m_shaderTarget1.getTexture());

	m_shaderTarget2.clear();
	m_shaderTarget2.draw(tmpSprite2, m_blurShader);
	m_shaderTarget2.display();
}

void MainMenuState::update([[maybe_unused]] float deltaTime)
{
	if (zfge::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		m_blurShader->setUniform("sigma", m_blurSigma = std::min(m_blurSigma + 0.009f, 1.0f));
		generateBlurredTexture();
	}
	else if (zfge::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_blurShader->setUniform("sigma", m_blurSigma = std::max(m_blurSigma - 0.009f, 0.0f));
		generateBlurredTexture();
	}
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
		case sf::Event::KeyReleased:
			handleKeyRelease(event.key.code);
			break;
		default:
			break;
	}
}

void MainMenuState::draw(sf::RenderTarget& target) const
{
	m_gui.draw();

	if (m_resultType == ResultType::Original)
		target.draw(m_rawSprite);
	else
		target.draw(m_resultSprite, m_rawSprite.getTransform());
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

void MainMenuState::handleKeyRelease(sf::Keyboard::Key key)
{
	using Key = sf::Keyboard::Key;

	switch (key)
	{
		case Key::S:
			m_resultType = ResultType::OnePass;
			m_resultSprite.setTexture(m_shaderTarget1.getTexture(), true);
			break;
		case Key::D:
			m_resultType = ResultType::TwoPass;
			m_resultSprite.setTexture(m_shaderTarget2.getTexture(), true);
			break;
		case Key::A:
			m_resultType = ResultType::Original;
			break;
		default:
			break;
	}
}
