#pragma once
#include "../Framework/entity.hh"
#include "../Components/position_component.hh"
#include "../Components/render_component.hh"
#include "../Framework/event_handlers.hh"
#include "../Pong/InputEventManager.h"
#include "../Pong/CollisionEventManager.h"

#include <AEEngine.h>


class Player  : public Entity{
private:
	int playableRange;


public:




	PositionComponent* posComponent = nullptr;
	RenderComponent* renderComponent = nullptr;
	//ControllerComponent* controllerCompoent = nullptr;
	float width =25.f;
	float height = 200.f;
	AEVec2 simplePos;

	AEVec2 velocity;
	const AEVec2 MaxVelocity = AEVec2(0,200);

	double dy = 0; // counter Changel;



public:

	Player()
	{
		playableRange = AEGetSysWindowHeight() / 2 - height/2;

		posComponent = new PositionComponent(100, 100);
		renderComponent = new RenderComponent();
		Init();
		
	}

	void  Init()
	{
		//dy = posComponent->getY();
		attach(posComponent);
		attach(renderComponent);
	}

	void Update() override
	{
		Entity::Update();
		

	}
	void Draw() override
	{
		//renderComponent->Draw();
		AEGfxRect(posComponent->getX(), posComponent->getY(), 0, width, height, AE_COLORS_RED);
	}
	
	void Move()
	{

		dy += AEGetFrameTime() * velocity.y;
		if (!(playableRange > posComponent->getY() + dy && -playableRange < posComponent->getY() + dy))
		{
			dy = 0;
		}
		else if ((int)dy  !=0)
		{
			posComponent->setPosition(posComponent->getX(), posComponent->getY() + (int)dy);
			dy = 0;
		}

	}

	void OnMovementChange(OnChangeEvent* event)
	{
		velocity = AEVec2(MaxVelocity.x,
			MaxVelocity.y * ((int)event->MovingUp->IsActionHappening - (int)event->MovingDown->IsActionHappening));
	}

	void OnMovementUpdate(UpdateOnEvent* event)
	{
		
		Move();
	}

	float naive_lerp(float a, float b, float t)
	{
		return a + t * (b - a);
	}
	void OnFollowEvent(SetLoopFunctionEvent *loopEvent)
	{
		PositionComponent* positionToFollow = static_cast<PositionComponent*>(loopEvent->getEntityToFollow()->
			getComponent("Position"));
		float velocityY = posComponent->getY() - positionToFollow->getY();
		if (velocityY < posComponent->getY()) velocity.y = velocityY;
		else velocity.y = MaxVelocity.y;
		Move();
	}




	~Player()
	{

	}


};