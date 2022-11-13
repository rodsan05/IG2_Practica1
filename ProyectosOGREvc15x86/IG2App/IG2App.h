#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <vector>
#include <string>
#include <iostream>

#include <OgreBillboardSet.h>
#include <OgreParticleSystem.h>

class Plano;
class Mu�eco;
class Bomba;
class Sinbad;
class Avion;
class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener
{
public:
	explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
	virtual ~IG2App() { };   // delete -> shutdown()  

protected:
	virtual void setup();
	virtual void shutdown();
	virtual void setupScene();

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener

	Ogre::SceneManager* mSM = nullptr;
	OgreBites::TrayManager* mTrayMgr = nullptr;
	Ogre::SceneNode* mLightNode = nullptr;
	Ogre::SceneNode* mCamNode = nullptr;
	Ogre::SceneNode* mSinbadNode = nullptr;
	Ogre::SceneNode* mSinbadEscenaBomba = nullptr;
	OgreBites::CameraMan* mCamMgr = nullptr;

	Ogre::SceneNode* sceneNode = nullptr;

	Ogre::SceneNode* noria = nullptr;
	
	Ogre::SceneNode* rio = nullptr;
	Ogre::SceneNode* planoRojo = nullptr;
	Ogre::SceneNode* planoAmarillo = nullptr;

	Ogre::SceneNode* bombaNode = nullptr;
	Ogre::SceneNode* munecoNode = nullptr;

	Ogre::SceneNode* avionSceneNode = nullptr;

	Ogre::SceneNode* avionNode = nullptr;
	Ogre::SceneNode* dronNodriza = nullptr;
	std::vector<Ogre::SceneNode*> drones;
	Ogre::SceneNode* planeta = nullptr;
	Sinbad* sinbad = nullptr;
	Sinbad* sinbadBombScene = nullptr;
	Plano* river = nullptr;
	Mu�eco* muneco = nullptr;
	Bomba* bomba = nullptr;
	Avion* avion = nullptr;
};

#endif
