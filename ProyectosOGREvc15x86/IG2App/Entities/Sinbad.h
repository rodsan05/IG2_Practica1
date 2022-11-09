#pragma once
#include "EntitiesIncludes.h"
#include "EntityIG.h"

#include "AspasNave.h"
#include <iostream>
#include <OgreTimer.h>

class Sinbad : public EntityIG
{
public:
	Sinbad(Ogre::SceneNode* node, float scale, float offsetNodoFict, bool runPlanet);
	~Sinbad();

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;

	void arma();
	void arma(bool manoDerecha);
	void cambiaArma();

	void toggleDancing();

protected:

	const float ROTATION_VEL = 50;
	const float MOVEMENT_VEL = 50;

	Ogre::AnimationState* mAnimStateBase = nullptr;
	Ogre::AnimationState* mAnimStateTop = nullptr;
	Ogre::AnimationState* danceState = nullptr;

	Ogre::SceneNode* sinbadNode = nullptr;
	Ogre::Entity* sinbadEntity = nullptr;
	Ogre::Entity* swordR = nullptr;
	Ogre::Entity* swordL = nullptr;

	Ogre::Timer* myTimer;

	bool rotating = false;
	bool dancing = false;
	bool runningAroundPlanet = false;
	int dir = 1;
	int randomWaitTime = 1000;
};

