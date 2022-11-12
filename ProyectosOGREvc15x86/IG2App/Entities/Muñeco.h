#pragma once
#include "EntityIG.h"
class Muñeco : public EntityIG
{
public:
	Muñeco(Ogre::SceneNode* node);
	~Muñeco();

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

	void createAnim();

protected:
	bool rotating = false;
	bool keyPress = false;
	bool rojo = false;

	Ogre::Entity* meshCabeza = nullptr;
	Ogre::Entity* meshCuerpo = nullptr;
	Ogre::SceneNode* cabeza = nullptr;
	Ogre::SceneNode* cuerpo = nullptr;

	Ogre::AnimationState* mAnimState = nullptr;
};

