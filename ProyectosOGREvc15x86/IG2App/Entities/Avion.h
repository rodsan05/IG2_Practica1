#pragma once
#include "EntitiesIncludes.h"
#include "EntityIG.h"
#include <OgreBillboardSet.h>
#include <OgreParticleSystem.h>
#include <OgreTimer.h>

#include "AspasNave.h"

class Avion : public EntityIG
{
public:
	Avion(Ogre::SceneNode* node, float scale, float offsetNodoFict);
	~Avion();

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

	void explode();

protected:
	Ogre::SceneNode* nodoAvion = nullptr;
	Ogre::SceneNode* nodoAvionParticulas = nullptr;

	AspasNave* aspaL = nullptr;
	AspasNave* aspaR = nullptr;

	bool stopped = false;
	bool eventSent = false;

	Ogre::Timer* myTimer = nullptr;
};

