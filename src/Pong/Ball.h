#pragma once
#include <AEEngine.h>
#include "../Components/position_component.hh"
#include "../Framework/entity.hh"
#include "../Components/render_component.hh"
#include "../Pong/CollisionEventManager.h"

class Ball : public Entity
{
public:
	PositionComponent* posComponent = nullptr;
	RenderComponent* renderComponent = nullptr;

	float Radius = 20.f;

	AEVec2 velocity;
	AEVec2 speed = AEVec2(100, 200);

	double dy = 0; // counter Changel;
	double dx = 0;

	Ball()
	{
		Init();

	}

	void Init()
	{
		posComponent = new PositionComponent(0, 0);

		renderComponent = new RenderComponent();

		attach(posComponent);
		attach(renderComponent);
	}

	void Update() override
	{

		Entity::Update();
		
		//check Collision

	}
	void Draw() override
	{
		AEGfxCircle(posComponent->getX(), posComponent->getY(), Radius, AE_COLORS_BLUE, 12);



	}

	void OnCollision(OnCollisionEvent event)
	{

	}

};

