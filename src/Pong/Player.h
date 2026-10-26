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


	EventHandler<Player, OnInputChangeEvent>* eventOnMoveChange;

	EventHandler<Player, UpdateEvent>* eventOnMoveUpdate;

	PositionComponent* posComponent = nullptr;
	RenderComponent* renderComponent = nullptr;

	float width =25.f;
	float height = 200.f;
	AEVec2 simplePos;

	AEVec2 velocity;
	AEVec2 speed = AEVec2(0,200);

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

	void OnMovementChange(OnInputChangeEvent* event)
	{
		velocity = AEVec2(speed.x,
			speed.y * ((int)event->MovingUp->IsActionHappening - (int)event->MovingDown->IsActionHappening));
	}

	void OnMovementUpdate(UpdateEvent* event)
	{
		
		Move();
	}




	~Player()
	{
		delete( eventOnMoveChange);
		delete(eventOnMoveUpdate);
	}


};