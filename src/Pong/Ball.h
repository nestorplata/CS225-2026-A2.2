#pragma once
#include <AEEngine.h>
#include "../Components/position_component.hh"
#include "../Framework/entity.hh"
#include "../Components/render_component.hh"
#include "../Pong/CollisionEventManager.h"

static AEVec2 multiply(AEVec2 first, AEVec2 second)
{
	return AEVec2(first.x * second.x, first.y * second.y);
}


class Ball : public Entity
{
public:
	PositionComponent* posComponent = nullptr;
	RenderComponent* renderComponent = nullptr;
	EventHandler<Ball, OnCollisionEvent>* EventHandlerOnCollisionRect;

	float Radius = 20.f;

	AEVec2 velocity = AEVec2 (100,200);
	AEVec2 simplePos;
	AEVec2 speed = AEVec2(100, 200);

	AEVec2 delta = AEVec2().ZERO;
	AEVec2 playableRange = AEVec2().ZERO;

	Ball()
	{
		Init();

	}

	void Init()
	{
		playableRange = AEVec2(AEGetSysWindowWidth(), AEGetSysWindowHeight())/2;

		posComponent = new PositionComponent(0, 0);

		renderComponent = new RenderComponent();

		EventHandlerOnCollisionRect = new EventHandler<Ball, OnCollisionEvent>(this, &Ball::OnRectCollision);


		attach(posComponent);
		attach(renderComponent);
	}

	void Update() override
	{

		Entity::Update();
		Move();
		
		//check Collision

	}
	void Draw() override
	{
		AEGfxCircle(posComponent->getX(), posComponent->getY(), Radius, AE_COLORS_BLUE, 12);



	}

	void Move()
	{

		delta += velocity* AEGetFrameTime();
		
		if (!(playableRange.y > posComponent->getY() + delta.y && -playableRange.y < posComponent->getY() + delta.y))
		{
			velocity.y *= -1;
			return;
		}
		if (!(playableRange.x > posComponent->getX() + delta.x && -playableRange.x < posComponent->getX() + delta.x))
		{
			AESetGameStateNext(AE_GS_RESTART);
			return;
		}

		if ((int)delta.x != 0 && (int)delta.y !=0)
		{
			posComponent->setPosition(posComponent->getX()+ (int)delta.x, posComponent->getY() + (int)delta.y);
			delta -= AEVec2((int)delta.x, (int)delta.y);
		}



	}


	void OnRectCollision(OnCollisionEvent* event)
	{
			velocity -= event->pResult->mNormal*2*(velocity.Dot(event->pResult->mNormal));
			Move();

	}

};

