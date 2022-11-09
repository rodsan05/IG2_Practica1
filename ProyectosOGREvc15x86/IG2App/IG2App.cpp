#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>

#include "Entities/AspaNoria.h"
#include "Entities/AspasNave.h"
#include "Entities/Noria.h"
#include "Entities/Plano.h"
#include "Entities/Muñeco.h"
#include "Entities/Avion.h"
#include "Entities/Dron.h"
#include "Entities/BrazoDron.h"
#include "Entities/Sinbad.h"
#include "Entities/Bomba.h"

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}
	else if (evt.keysym.sym == SDLK_g)
	{
		mSM->getSceneNode("Clock")->roll(Degree(-5));
	}
	else if (evt.keysym.sym == SDLK_p)
	{
		sceneNode->yaw(Degree(5));
	}
	else if (evt.keysym.sym == SDLK_h)
	{
		AxisAlignedBox colliderAvion;
		AxisAlignedBox colliderDron;

		auto it = drones.begin();
		while (it != drones.end())
		{
			auto dron = *it;

			colliderAvion = avion->_getWorldAABB();
			colliderDron = dron->_getWorldAABB();

			if (colliderAvion.intersects(colliderDron))
			{
				dron->getParent()->removeChild(dron);
				it = drones.erase(it);
			}
			else it++;
		}

		if (drones.size() == 0)
		{
			dronNod->changeColor();
		}
	}

	return true;
}

void IG2App::shutdown()
{
	mShaderGenerator->removeSceneManager(mSM);
	mSM->removeRenderQueueListener(mOverlaySystem);

	mRoot->destroySceneManager(mSM);

	delete mTrayMgr;  mTrayMgr = nullptr;
	delete mCamMgr; mCamMgr = nullptr;

	// do not forget to call the base 
	IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
	// do not forget to call the base first
	IG2ApplicationContext::setup();

	mSM = mRoot->createSceneManager();

	// register our scene with the RTSS
	mShaderGenerator->addSceneManager(mSM);

	mSM->addRenderQueueListener(mOverlaySystem);

	mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
	mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);

	addInputListener(mTrayMgr);

	addInputListener(this);
	setupScene();
}

void IG2App::setupScene(void)
{
	// create the camera
	Camera* cam = mSM->createCamera("Cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(10000);
	cam->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  

	// and tell it to render into the main window
	Viewport* vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	//------------------------------------------------------------------------

	// without light we would just get a black screen 

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(1, 1, 1);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(0, -1, -1).normalisedCopy());  //vec3.normalise();
	//lightNode->setPosition(0, 0, 1000);

	//------------------------------------------------------------------------

	sceneNode = mSM->getRootSceneNode()->createChildSceneNode();

	// finally something to render

	//mSinbadNode->setPosition(400, 100, -300);
	//mSinbadNode->yaw(Ogre::Degree(-45));
	//mSinbadNode->showBoundingBox(true);

	rio = sceneNode->createChildSceneNode();
	Plano* river = new Plano(rio, 2160.0f * 1.5, 1600.0f, "Practica1/Rio");

	planoRojo = sceneNode->createChildSceneNode();
	Plano* planoRoj = new Plano(planoRojo, 2160.0f / 3, 1600.0f / 2.5, "Practica1/Rojo");

	planoAmarillo = sceneNode->createChildSceneNode();
	Plano* planoAmar = new Plano(planoAmarillo, 2160.0f / 3, 1600.0f / 2.5, "Practica1/Amarillo");

	planoRojo->translate(2160.0f / 3, 1, -1600.0f / 3.35);
	planoAmarillo->translate(-2160.0f / 3, 1, 1600.0f / 3.35);

	mSinbadEscenaBomba = sceneNode->createChildSceneNode();
	sinbadBombScene = new Sinbad(mSinbadEscenaBomba, 20, 0, false);
	sinbadBombScene->arma();
	mSinbadEscenaBomba->translate(-2160.0f / 3, 1 + 5 * 20, 1600.0f / 3.35);

	noria = sceneNode->createChildSceneNode();
	Noria* n = new Noria(noria, 15, 20, 2);
	noria->translate(2160.0f / 3, 1, -1600.0f / 2);

	float planeCircleRadius = 1000;
	avion = sceneNode->createChildSceneNode();
	Avion* a = new Avion(avion, 1, planeCircleRadius);
	avion->translate(0, 1250, 0);
	addInputListener(a);

	bomba = sceneNode->createChildSceneNode();
	Bomba* bomb = new Bomba(bomba, 20);

	/*noria = plano->createChildSceneNode();
	Noria* n = new Noria(noria, 10, 10, 1.5);

	muñeco = plano->createChildSceneNode();
	Muñeco* m = new Muñeco(muñeco);

	muñeco->setPosition(600, 200, 600);
	muñeco->yaw(Degree(225));*/

	/*addInputListener(n);
	addInputListener(m);*/
	addInputListener(river);
	addInputListener(bomb);
	addInputListener(sinbadBombScene);

	//Escena Avion
	float planetScale = 3;
	Entity* planet = mSM->createEntity("sphere.mesh");
	planet->setMaterialName("Practica1/Cian");

	avionSceneNode = mSM->getRootSceneNode()->createChildSceneNode();

	planeta = avionSceneNode->createChildSceneNode();
	planeta->attachObject(planet);
	planeta->scale(planetScale * Vector3(1));

	mSinbadNode = avionSceneNode->createChildSceneNode("nSinbad");

	sinbad = new Sinbad(mSinbadNode, 10, 100 * planetScale + 5 * 10, true);
	addInputListener(sinbad);

	/*avion = avionSceneNode->createChildSceneNode();
	Avion* a = new Avion(avion, 0.2, 100 * planetScale + 100 * 0.2);
	addInputListener(a);

	dronNodriza = avionSceneNode->createChildSceneNode();
	dronNod = new Dron(dronNodriza, 3, 0.25, 100 * planetScale + 0.35 * 100 * 0.25, true);
	addInputListener(dronNod);

	dronNodriza->roll(Ogre::Degree(90));
	dronNodriza->pitch(Ogre::Degree(45));

	int angle = 0;
	int angle2 = 0;
	for (int i = 0; i < 200; i++)
	{
		angle = rand() % 360;
		angle2 = rand() % 360;

		Ogre::SceneNode* dronAvispa = avionSceneNode->createChildSceneNode();
		Dron* dA = new Dron(dronAvispa, 3, 0.1, 100 * planetScale + 0.35 * 100 * 0.25, false);
		addInputListener(dA);

		dir inicial
		dronAvispa->roll(Ogre::Degree(angle));
		pos inicial
		dronAvispa->pitch(Ogre::Degree(angle2));

		drones.push_back(dronAvispa);
	}*/

	avionSceneNode->setVisible(false);



	//------------------------------------------------------------------------

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);

	//mCamMgr->setTarget(mSinbadNode);  
	//mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

	//------------------------------------------------------------------------

}

