#pragma once
#include <AEEngine.h>
#include "../Components/position_component.hh"
#include "../Framework/entity.hh"
#include "../Components/render_component.hh"
#include "../Pong/CollisionEvents.hh"



//simple ballClass
class Ball : public Entity
{
public:
	PositionComponent* posComponent = nullptr;
	RenderComponent* renderComponent = nullptr;
	EventHandler<Ball, OnCollisionEvent>* EventHandlerOnCollisionRect;

	float Radius = 20.f;

	AEVec2 velocity = AEVec2 (-150,100);
	AEVec2 simplePos; //Don't pay attention to this, :)
	AEVec2 delta = AEVec2().ZERO;
	AEVec2 playableRange = AEVec2().ZERO;

	Ball();

	void Init();

	void Update() override;
	void Draw() override;
	void Move();
	void OnRectCollision(OnCollisionEvent* event);


};

