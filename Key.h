#pragma once
#include "PlacableActor.h"
class Key : public PlacableActor {
public: 
	Key(int x, int y, ActorColor color) : PlacableActor(x, y, color) {

	}
	virtual void Draw() override;
	virtual ActorType GeType() override { return ActorType::Key; }
};