#pragma once
#include "EntitiesIncludes.h"
#include "EntityIG.h"

class Noria : public EntityIG { //#include <OgreInput.h>
public:
	Noria(Ogre::SceneNode* node, int nBrazos, float longitud, float lCubo); // #include <OgreSceneNode.h>
	~Noria();
	// Métodos de InputListener que pueden redefinirse
	virtual void frameRendered(const Ogre::FrameEvent& evt) override;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) override;

	virtual void receiveEvent(EntityIG* entidad) override;

protected:
	Ogre::SceneNode* noriaPiv = nullptr;

	bool paused = false;
};