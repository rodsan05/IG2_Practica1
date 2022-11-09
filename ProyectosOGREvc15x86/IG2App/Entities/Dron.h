#pragma once
#include "EntitiesIncludes.h"
#include "EntityIG.h"
#include "BrazoDron.h"

#include <OgreTimer.h>
#include <vector>

class Dron : public EntityIG
{
public:
	Dron(Ogre::SceneNode* node, int nBrazos, float scale, float offset, bool nodriza);
	~Dron();

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

	void changeColor();

protected:

	const float ROTATION_VEL = 50;
	const float MOVEMENT_VEL = 50;

	Ogre::Entity* entBody = nullptr;

	Ogre::SceneNode* dron = nullptr;

	std::vector<BrazoDron*> brazos;

	Ogre::Timer* myTimer;

	bool rotating = false;
	int dir = 1;
	int randomWaitTime = 1000;
};

