#include "Player.h"

Player::Player(float x, float y, float scaleX, float scaleY)
	: Entity(x, y, scaleX, scaleY)
{
	event = new sf::Event();

    LoadAnimations();
    InitHitbox(x, y, 20 * SCALE, 27 * SCALE);
}

Player::~Player()
{
	delete event;
    delete texture;
    delete lvlData;
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

void Player::LoadLvlData(int** lvlData)
{
    this->lvlData = lvlData;
    if (!HelpMethods::IsEntityOnFloor(hitbox, lvlData))
    {
        inAir = true;
    }
}

void Player::Jump()
{
    if (inAir)
    {
        return;
    }
    inAir = true;
    airSpeed = jumpSpeed;
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

void Player::ResetInAir()
{
    inAir = false;
    airSpeed = 0;
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

    if (jump)
    {
        Jump();
    }
    if (!left && !right && !inAir)
    {
        return;
    }

    float xSpeed = 0;

    if (left)
    {
        xSpeed -= playerSpeed;
    }
    if (right)
    {
        xSpeed += playerSpeed;
    }

    if (!inAir)
    {
        if (!HelpMethods::IsEntityOnFloor(hitbox, lvlData))
        {
            inAir = true;
        }
    }

    if (inAir)
    {
        if (HelpMethods::CanMoveHere(
            hitbox->getPosition().x,
            hitbox->getPosition().y + airSpeed,
            hitbox->getSize().x,
            hitbox->getSize().y,
            lvlData
        ))
        {
            hitbox->setPosition(
                hitbox->getPosition().x, 
                hitbox->getPosition().y + airSpeed
            );
            airSpeed += gravity;
            UpdateXPos(xSpeed);
        }
        else 
        {
            hitbox->setPosition(
                hitbox->getPosition().x,
                HelpMethods::GetEntityYPosUnderRoofOrAboveFloor(hitbox, airSpeed)
            );

            if (airSpeed > 0)
            {
                ResetInAir();
            }
            else
            {
                airSpeed = fallSpeedAfterCollision;
            }

            UpdateXPos(xSpeed);
        }
    }
    else
    {
        UpdateXPos(xSpeed);
    }

    moving = true;
}

void Player::UpdateXPos(float xSpeed)
{
    if (HelpMethods::CanMoveHere(
        hitbox->getPosition().x + xSpeed,
        hitbox->getPosition().y,
        hitbox->getSize().x,
        hitbox->getSize().y,
        lvlData
    ))
    {
        hitbox->setPosition(
            hitbox->getPosition().x + xSpeed,
            hitbox->getPosition().y
        );
    }
    else
    {
        hitbox->setPosition(
            HelpMethods::GetEntityXPosNextToWall(hitbox, xSpeed),
            hitbox->getPosition().y
        );
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

    if (inAir)
    {
        if (airSpeed < 0)
        {
            playerAction = Constants::PlayerConstants::PlayerStates::JUMP;
        }
        else 
        {
            playerAction = Constants::PlayerConstants::PlayerStates::FALLING;
        }
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
    animations[playerAction][aniIndex]->setPosition(
        sf::Vector2f(
            hitbox->getPosition().x - xDrawOffset, 
            hitbox->getPosition().y - yDrawOffset
        )
    );
    animations[playerAction][aniIndex]->setScale(sf::Vector2f(scaleX, scaleY));
    renderTarget->draw(*animations[playerAction][aniIndex]);
    std::cout << std::to_string(animations[playerAction][aniIndex]->getPosition().x) << " : " << std::to_string(animations[playerAction][aniIndex]->getPosition().y) << "\n";
    //DrawHitbox(renderTarget);
}

void Player::KeyReleased()
{
    switch (event->key.code)
    {
    /*case sf::Keyboard::W:
        up = false;
        break;*/
    case sf::Keyboard::A:
        left = false;
        break;
    /*case sf::Keyboard::S:
        down = false;
        break;*/
    case sf::Keyboard::D:
        right = false;
        break;
    case sf::Keyboard::Space:
        jump = false;
        break;
    }
}

void Player::KeyPressed()
{
    switch (event->key.code) 
    {
    /*case sf::Keyboard::W:
        up = true;
        break;*/
    case sf::Keyboard::A:
        left = true;
        break;
    /*case sf::Keyboard::S:
        down = true;
        break;*/
    case sf::Keyboard::D:
        right = true;
        break;
    case sf::Keyboard::Space:
        jump = true;
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
