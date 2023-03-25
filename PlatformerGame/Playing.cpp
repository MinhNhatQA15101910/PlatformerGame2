#include "Playing.h"

void Playing::InitClasses()
{
	levelManager = new LevelManager();
	enemyManager = new EnemyManager();
	player = new Player(200, 200, 64 * SCALE, 40 * SCALE);

	player->LoadLvlData(levelManager->GetCurrentLevel());
	pauseOverlay = new PauseOverlay(gamestate, &paused);
}

void Playing::CheckCloseToBorder()
{
	float playerX = player->GetHitbox()->getPosition().x;
	float diff = playerX - xLvlOffset;

	if (diff > rightBorder)
	{
		xLvlOffset += diff - rightBorder;
	}
	else if (diff < leftBorder)
	{
		xLvlOffset += diff - leftBorder;
	}

	if (xLvlOffset > maxLvlOffsetX)
	{
		xLvlOffset = maxLvlOffsetX;
	}
	else if (xLvlOffset < 0)
	{
		xLvlOffset = 0;
	}
}

void Playing::KeyReleased()
{
	switch (event->key.code)
	{
	case sf::Keyboard::A:
		player->SetLeft(false);
		break;
	case sf::Keyboard::D:
		player->SetRight(false);
		break;
	case sf::Keyboard::Space:
		player->SetJump(false);
		break;
	}
}

void Playing::KeyPressed()
{
	switch (event->key.code)
	{
	case sf::Keyboard::A:
		player->SetLeft(true);
		break;
	case sf::Keyboard::D:
		player->SetRight(true);
		break;
	case sf::Keyboard::Space:
		player->SetJump(true);
		break;
	case sf::Keyboard::Escape:
		paused = !paused;
		break;
	}
}

void Playing::MouseButtonPressed()
{
	if (event->mouseButton.button == sf::Mouse::Button::Left)
	{
		player->SetAttacking(true);
	}

	if (paused)
	{
		pauseOverlay->MouseButtonPressed(event);
	}
}

void Playing::MouseButtonReleased()
{
	if (paused)
	{
		pauseOverlay->MouseButtonReleased(event);
	}
}

void Playing::MouseEntered()
{
}

void Playing::MouseLeft()
{
}

void Playing::MouseMoved()
{
	if (paused)
	{
		pauseOverlay->MouseMoved(event);
	}
}

Playing::Playing(int* gamestate)
	: State(gamestate)
{
	event = new sf::Event();

	InitClasses();

	backgroundTexture = LoadSave::GetTextureAtlas(PLAYING_BG_IMG);
	backgroundSprite = new sf::Sprite();
	backgroundSprite->setTexture(*backgroundTexture);

	bigCloudTexture = LoadSave::GetTextureAtlas(BIG_CLOUDS);
	for (int i = 0; i < 3; i++)
	{
		bigCloudSprites[i] = new sf::Sprite();
		bigCloudSprites[i]->setTexture(*bigCloudTexture);
	}

	smallCloudTexture = LoadSave::GetTextureAtlas(SMALL_CLOUDS);
	for (int i = 0; i < 8; i++)
	{
		smallCloudSprites[i] = new sf::Sprite();
		smallCloudSprites[i]->setTexture(*smallCloudTexture);
	}

	for (int i = 0; i < 8; i++)
	{
		smallCloudsPos[i] = (90 * SCALE) + (rand() % (int)(100 * SCALE));
	}
}

Playing::~Playing()
{
	State::~State();
	delete event;
	delete player;
	delete levelManager;
	delete enemyManager;
	delete pauseOverlay;
	delete backgroundSprite;
	for (int i = 0; i < 3; i++)
	{
		delete bigCloudSprites[i];
	}
	for (int i = 0; i < 8; i++)
	{
		delete smallCloudSprites[i];
	}
	delete backgroundTexture;
	delete bigCloudTexture;
	delete smallCloudTexture;
}

Player* Playing::GetPlayer()
{
	return player;
}

void Playing::UpdateProperties()
{
	if (!paused)
	{
		levelManager->UpdateProperties();
		player->UpdateProperties();
		enemyManager->UpdateProperties(levelManager->GetCurrentLevel());
		CheckCloseToBorder();
	}
	else
	{
		pauseOverlay->UpdateProperties();
	}
}

void Playing::UpdateEvents(sf::Event* event)
{
	this->event = event;

	KeyEventHandler();
	MouseButtonEventHandler();
	MouseMoveEventHandler();
}

void Playing::RenderClouds(sf::RenderTarget* renderTarget)
{
	for (int i = 0; i < 3; i++)
	{
		bigCloudSprites[i]->setPosition(
			i * BIG_CLOUD_WIDTH - xLvlOffset * 0.3f,
			204 * SCALE
		);
		bigCloudSprites[i]->setScale(sf::Vector2f(SCALE, SCALE));
		renderTarget->draw(*bigCloudSprites[i]);
	}

	for (int i = 0; i < 8; i++)
	{
		smallCloudSprites[i]->setPosition(
			SMALL_CLOUD_WIDTH * 4 * i - xLvlOffset * 0.7f, 
			smallCloudsPos[i]
		);
		smallCloudSprites[i]->setScale(sf::Vector2f(SCALE, SCALE));
		renderTarget->draw(*smallCloudSprites[i]);
	}
}

void Playing::Render(sf::RenderTarget* renderTarget)
{
	backgroundSprite->setPosition(0, 0);
	backgroundSprite->setScale(sf::Vector2f(
		GAME_WIDTH / backgroundTexture->getSize().x, 
		GAME_HEIGHT / backgroundTexture->getSize().y
	));
	renderTarget->draw(*backgroundSprite);

	RenderClouds(renderTarget);

	levelManager->Render(renderTarget, xLvlOffset);
	player->Render(renderTarget, xLvlOffset);
	enemyManager->Render(renderTarget, xLvlOffset);

	if (paused)
	{
		sf::RectangleShape rectangle;
		rectangle.setFillColor(sf::Color(0, 0, 0, 150));
		rectangle.setPosition(0, 0);
		rectangle.setSize(sf::Vector2f(GAME_WIDTH, GAME_HEIGHT));
		renderTarget->draw(rectangle);

		pauseOverlay->Render(renderTarget);
	}
}

void Playing::KeyEventHandler()
{
	switch (event->type)
	{
	case sf::Event::KeyPressed:
		KeyPressed();
		break;
	case sf::Event::KeyReleased:
		KeyReleased();
		break;
	}
}

void Playing::MouseButtonEventHandler()
{
	switch (event->type)
	{
	case sf::Event::MouseButtonPressed:
		MouseButtonPressed();
		break;
	case sf::Event::MouseButtonReleased:
		MouseButtonReleased();
		break;
	}
}

void Playing::MouseMoveEventHandler()
{
	switch (event->type)
	{
	case sf::Event::MouseEntered:
		MouseEntered();
		break;
	case sf::Event::MouseLeft:
		MouseLeft();
		break;
	case sf::Event::MouseMoved:
		MouseMoved();
		break;
	}
}

void Playing::WindowFocusLost()
{
	if (event->type == sf::Event::LostFocus)
	{
		player->ResetDirBools();
	}
}
