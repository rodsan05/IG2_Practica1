#pragma once
#include "EntitiesIncludes.h"
#include "EntityIG.h"

#include "AspasNave.h"

class Avion : public EntityIG
{
public:
	Avion(Ogre::SceneNode* node, float scale, float offsetNodoFict);
	~Avion();

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

protected:
	Ogre::SceneNode* nodoAvion = nullptr;

	AspasNave* aspaL = nullptr;
	AspasNave* aspaR = nullptr;
};

