#pragma once
#include "../Framework/entity.hh"
#include "../Components/position_component.hh"
#include "../Components/render_component.hh"
#include "../Framework/event_handlers.hh"
#include "../Pong/InputEvents.hh"
#include "../Pong/CollisionEvents.hh"

#include <AEEngine.h>

//Player class
//didn't want to implement Enemy Class
class Player  : public Entity{
private:
	int playableRange;
	PositionComponent* positionToFollow;

public:

	// simplifiers.
	PositionComponent* posComponent = nullptr;
	RenderComponent* renderComponent = nullptr;

	//A controller would have been perfect to implement 

	//Rect
	float width =25.f;
	float height = 200.f;
	AEVec2 simplePos;

	//Movement
	AEVec2 velocity;
	const AEVec2 MaxVelocity = AEVec2(0, 200);
	double dy = 0; // counter Changel;



public:

	Player();

	void  Init();
	void Update() override;
	void Draw() override;
	
	//generic apply movement Formula
	void Move();

	void OnMovementSet(OnSetEvent* event);

	void OnMovementUpdate(UpdateOnEvent* event);

	//Sets the characther to follow
	void OnFollowSet(SetLoopFunctionEvent* loopEvent);

	//Follows "positionToFollow"
	void OnFollowUpdate(LoopFunctionEvent* loopEvent);

	~Player();


};