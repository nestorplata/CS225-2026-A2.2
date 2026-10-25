#pragma once
#include <AEEngine.h>
#include "../Components/position_component.hh"
#include "../Framework/entity.hh"
#include "../Components/render_component.hh"

class Ball : public Entity
{
public:
	PositionComponent* posComponent = nullptr;
	RenderComponent* renderComponent = nullptr;

	float Radius = 100.f;
	Ball()
	{
		Init();

	}

	void  Init()
	{
		posComponent = new PositionComponent(0, 0);

		renderComponent = new RenderComponent();

		attach(posComponent);
		attach(renderComponent);
	}

	void Update() override
	{
		Entity::Update();

	}
	void Draw() override
	{
		AEGfxCircle(posComponent->getX(), posComponent->getY(), Radius, AE_COLORS_BLUE, 5);



	}

};

