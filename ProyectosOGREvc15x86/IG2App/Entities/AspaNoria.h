#pragma once

#include "EntitiesIncludes.h"
#include "EntityIG.h"

class AspaNoria : public EntityIG { //#include <OgreInput.h>
public:
	AspaNoria(Ogre::SceneNode* node, float longitud, float lCubo); // #include <OgreSceneNode.h>
	~AspaNoria();

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

protected:
	Ogre::SceneNode* tableroI;
	Ogre::SceneNode* tableroD;
	Ogre::SceneNode* cubo;
};