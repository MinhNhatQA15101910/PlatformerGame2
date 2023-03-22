#include "Player.h"

Player::Player(float x, float y, float width, float height)
    : Entity(x, y, width, height)
{
    LoadAnimations();
    InitHitbox(x, y, (int)(20 * SCALE), (int)(27 * SCALE));
}

Player::~Player()
{
    delete texture;
    delete level;
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

void Player::LoadLvlData(Level* level)
{
    this->level = level;
    if (!HelpMethods::IsEntityOnFloor(hitbox, level))
    {
        inAir = true;
    }
}

void Player::SetLeft(bool left)
{
    this->left = left;
}

void Player::SetRight(bool right)
{
    this->right = right;
}

void Player::SetJump(bool jump)
{
    this->jump = jump;
}

void Player::SetAttacking(bool attacking)
{
    this->attacking = attacking;
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

void Player::UpdatePos()
{
    moving = false;

    if (jump)
    {
        Jump();
    }

    if (!inAir)
    {
        if ((!left && !right) || (right && left))
        {
            return;
        }
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
        if (!HelpMethods::IsEntityOnFloor(hitbox, level))
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
            level
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
        level
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

void Player::Render(sf::RenderTarget* renderTarget, float lvlOffset)
{
    animations[playerAction][aniIndex]->setPosition(
        sf::Vector2f(
            hitbox->getPosition().x - xDrawOffset - lvlOffset,
            hitbox->getPosition().y - yDrawOffset
        )
    );
    //animations[playerAction][aniIndex]->setScale(sf::Vector2f(scaleX, scaleY));
    animations[playerAction][aniIndex]->setScale(sf::Vector2f(
        width / ((texture->getSize().x) / spriteSize), 
        height / ((texture->getSize().y) / animationSize)
    ));
    renderTarget->draw(*animations[playerAction][aniIndex]);
    //DrawHitbox(renderTarget);
}
