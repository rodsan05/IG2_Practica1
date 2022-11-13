#pragma once

#include "EntitiesIncludes.h"

class EntityIG : public OgreBites::InputListener { //#include <OgreInput.h>
public:
	enum MessageType { sinbadDie, bombExplode };

	EntityIG(Ogre::SceneNode* node); // #include <OgreSceneNode.h>
	~EntityIG();

	//Vector estático de listeners
	static std::vector<EntityIG*> appListeners;
	//Añadir entidad como listener al vector con push_back()
	static void addListener(EntityIG* entidad)
	{
		appListeners.push_back(entidad);
	};

	virtual void frameRendered(const Ogre::FrameEvent& evt);

protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;

	// Métodos de InputListener que pueden redefinirse
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual bool keyReleased(const OgreBites::KeyboardEvent& evt);
	virtual bool mousePressed(const OgreBites::MouseButtonEvent& evt);
	virtual bool mouseRelease(const OgreBites::MouseButtonEvent& evt);
	virtual bool mouseMoved(const OgreBites::MouseMotionEvent& evt);
	virtual bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt);

	void sendEvent(EntityIG* entidad);
	void sendEvent(EntityIG* entidad, MessageType message);
	virtual void receiveEvent(EntityIG* entidad) {};
	virtual void receiveEvent(EntityIG* entidad, MessageType message) {};
};