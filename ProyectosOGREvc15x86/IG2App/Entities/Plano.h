#pragma once
#include "EntityIG.h"

class Plano : public EntityIG
{
public:
	Plano(Ogre::SceneNode* node, float h, float w, Ogre::String material);
	~Plano();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;

protected:
	bool moviendose = true;

	Ogre::Entity* plane = nullptr;
};

