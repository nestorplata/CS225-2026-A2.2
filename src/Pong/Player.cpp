#include "Player.h"

Player::Player()
{
	playableRange = AEGetSysWindowHeight() / 2 - height / 2;

	posComponent = new PositionComponent(100, 100);
	renderComponent = new RenderComponent();
	Init();

}

void Player::Init()
{
	//dy = posComponent->getY();
	attach(posComponent);
	attach(renderComponent);
}

void Player::Update() 
{
	Entity::Update();


}
void Player::Draw() 
{
	//renderComponent->Draw();
	AEGfxRect(posComponent->getX(), posComponent->getY(), 0, width, height, AE_COLORS_RED);
}

//generic apply movement Formula
void Player::Move()
{

	dy += AEGetFrameTime() * velocity.y;
	if (!(playableRange > posComponent->getY() + dy && -playableRange < posComponent->getY() + dy))
	{
		dy = 0;
	}
	else if ((int)dy != 0)
	{
		posComponent->setPosition(posComponent->getX(), posComponent->getY() + (int)dy);
		dy = 0;
	}

}

void Player::OnMovementSet(OnSetEvent* event)
{
	velocity = AEVec2(MaxVelocity.x,
		MaxVelocity.y * ((int)event->MovingUp->IsActionHappening - (int)event->MovingDown->IsActionHappening));
}

void Player::OnMovementUpdate(UpdateOnEvent* event)
{

	Move();
}

//Sets the characther to follow
void Player::OnFollowSet(SetLoopFunctionEvent* loopEvent)
{
	if (loopEvent->getEntityToFollow())
	{
		positionToFollow = dynamic_cast<PositionComponent*>(loopEvent->getEntityToFollow()->
			getComponent("Position"));
	}
	else { positionToFollow = nullptr; }

}

//Follows "positionToFollow"
void Player::OnFollowUpdate(LoopFunctionEvent* loopEvent)
{
	velocity.y = AEVec2::Lerp(AEVec2(0, posComponent->getY()), AEVec2(0, positionToFollow->getY()), 5.0f).y;
	if (velocity.y > MaxVelocity.y)velocity.y = MaxVelocity.y;
	if (velocity.y < -MaxVelocity.y)velocity.y = -MaxVelocity.y;

	Move();
}

Player::~Player()
{

}
