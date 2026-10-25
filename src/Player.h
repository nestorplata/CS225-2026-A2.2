#pragma once
#include "Framework/entity.hh"
#include "Components/position_component.hh"
#include "Components/render_component.hh"
#include <AEEngine.h>

class Player  : public Entity{
public:
	PositionComponent* posComponent = nullptr;
	RenderComponent* renderComponent = nullptr;

	Player()
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
	void Draw()
	{
	}

	~Player()
	{
		//delete(posComponent);
		//delete(renderComponent);
	}


};