#pragma once
#include "EntitiesIncludes.h"
#include "EntityIG.h"
#include "AspasNave.h"

class BrazoDron : public EntityIG
{
public:
	BrazoDron(Ogre::SceneNode* node, float scale);
	~BrazoDron();

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

protected:
	AspasNave* aspasDron = nullptr;
};

