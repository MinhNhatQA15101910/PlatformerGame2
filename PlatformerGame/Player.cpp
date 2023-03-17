#include "Player.h"

Player::Player(float x, float y, float scaleX, float scaleY)
	: Entity(x, y, scaleX, scaleY)
{
	event = new sf::Event();

    LoadAnimations();
}

Player::~Player()
{
	delete event;
    delete texture;
    for (int j = 0; j < animationSize; j++)
    {
        for (int i = 0; i < spriteSize; i++)
        {
            delete animations[j][i];
        }
    }
}

void Player::ResetDirBools()
{
    left = false;
    right = false;
    up = false;
    down = false;
}

void Player::KeyEventHandler()
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

void Player::MouseButtonEventHandler()
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

void Player::MouseMoveEventHandler()
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

void Player::LoadAnimations()
{
    texture = LoadSave::GetTextureAtlas(PLAYER_ATLAS);

    for (int j = 0; j < animationSize; j++)
    {
        for (int i = 0; i < spriteSize; i++) 
        {
            animations[j][i] = new sf::Sprite();
            animations[j][i]->setTexture(*texture);
            animations[j][i]->setTextureRect(sf::IntRect(i * 64, j * 40, 64, 40));
        }
    }
}

void Player::UpdateEvents(sf::Event* event)
{
    this->event = event;

    KeyEventHandler();
    MouseButtonEventHandler();
    MouseMoveEventHandler();
}

void Player::UpdatePos()
{
    moving = false;

    if (left && !right)
    {
        x -= playerSpeed;
        moving = true;
    }
    else if (right && !left)
    {
        x += playerSpeed;
        moving = true;
    }

    if (up && !down)
    {
        y -= playerSpeed;
        moving = true;
    }
    else if (down && !up)
    {
        y += playerSpeed;
        moving = true;
    }
}

void Player::UpdateAnimationTick()
{
    aniTick++;
    if (aniTick >= aniSpeed)
    {
        aniTick = 0;
        aniIndex++;
        if (aniIndex >= Constants::PlayerConstants::GetSpriteAmount(playerAction))
        {
            aniIndex = 0;
            attacking = false;
        }
    }
}

void Player::ResetAniTick()
{
    aniTick = 0;
    aniIndex = 0;
}

void Player::SetAnimation()
{
    int startAni = playerAction;

    if (moving)
    {
        playerAction = Constants::PlayerConstants::PlayerStates::RUNNING;
    }
    else
    {
        playerAction = Constants::PlayerConstants::PlayerStates::IDLE;
    }

    if (attacking)
    {
        playerAction = Constants::PlayerConstants::PlayerStates::ATTACK_1;
    }
    
    if (startAni != playerAction)
    {
        ResetAniTick();
    }
}

void Player::UpdateProperties()
{
    UpdatePos();
    UpdateAnimationTick();
    SetAnimation();
}

void Player::Render(sf::RenderTarget* renderTarget)
{
    animations[playerAction][aniIndex]->setPosition(sf::Vector2f(x, y));
    animations[playerAction][aniIndex]->setScale(sf::Vector2f(scaleX, scaleY));

    renderTarget->draw(*animations[playerAction][aniIndex]);
}

void Player::KeyReleased()
{
    switch (event->key.code)
    {
    case sf::Keyboard::W:
        up = false;
        break;
    case sf::Keyboard::A:
        left = false;
        break;
    case sf::Keyboard::S:
        down = false;
        break;
    case sf::Keyboard::D:
        right = false;
        break;
    }
}

void Player::KeyPressed()
{
    switch (event->key.code) 
    {
    case sf::Keyboard::W:
        up = true;
        break;
    case sf::Keyboard::A:
        left = true;
        break;
    case sf::Keyboard::S:
        down = true;
        break;
    case sf::Keyboard::D:
        right = true;
        break;
    }
}

void Player::MouseButtonPressed()
{
    if (event->mouseButton.button == sf::Mouse::Button::Left)
    {
        attacking = true;
    }
}

void Player::MouseButtonReleased()
{
}

void Player::MouseEntered()
{
}

void Player::MouseLeft()
{
}

void Player::MouseMoved()
{
}
