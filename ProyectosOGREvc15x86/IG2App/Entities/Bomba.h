#pragma once
#include "EntityIG.h"
#include <OgreTimer.h>
#include <OgreParticleSystem.h>

class Bomba : public EntityIG
{
public:
	Bomba(Ogre::SceneNode* node, float scale);
	~Bomba();

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

	void receiveEvent(EntityIG* entidad, MessageType message) override;

	void setStopTimer(float time);

	void explode();

protected:

	Ogre::AnimationState* animationState = nullptr;

	Ogre::SceneNode* nodoBomba = nullptr;

	Ogre::Timer* myTimer = nullptr;
	bool stopTimerActivated = false;
	bool stopped = false;
	float timeToStop = 0;
};

