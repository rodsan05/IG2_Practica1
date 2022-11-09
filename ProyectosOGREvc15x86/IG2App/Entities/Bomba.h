#pragma once
#include "EntityIG.h"
class Bomba : public EntityIG
{
public:
	Bomba(Ogre::SceneNode* node, float scale);
	~Bomba();

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

protected:

	Ogre::AnimationState* animationState = nullptr;
};

