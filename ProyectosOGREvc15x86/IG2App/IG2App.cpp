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
	else if (evt.keysym.sym == SDLK_t)
	{
		river->changeToRock();
		bomba->setStopTimer(5000);
	}
	else if (evt.keysym.sym == SDLK_r)
	{
		avion->explode();
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
	vp->setBackgroundColour(Ogre::ColourValue(0.6, 0.7, 0.8));

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
	river = new Plano(rio, 2160.0f * 1.5, 1600.0f, "Practica1/Rio");

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

	auto posPlatRoja = planoRojo->getPosition();
	sinbadBombScene->createRunningPlatformsAnim(posPlatRoja);

	noria = sceneNode->createChildSceneNode();
	Noria* n = new Noria(noria, 15, 20, 2);
	noria->translate(2160.0f / 3, 1, -1600.0f / 2);

	float planeCircleRadius = 1000;
	avionNode = sceneNode->createChildSceneNode();
	avion = new Avion(avionNode, 1, planeCircleRadius);
	avionNode->translate(0, 1250, 0);
	addInputListener(avion);
	avion->addListener(sinbadBombScene);

	bombaNode = sceneNode->createChildSceneNode();
	bomba = new Bomba(bombaNode, 20);
	sinbadBombScene->addListener(bomba);

	munecoNode = sceneNode->createChildSceneNode();
	muneco = new Muñeco(munecoNode);

	munecoNode->translate(2160 / 2.5, 100, -300);
	munecoNode->setScale(0.5 * Vector3(1));
	muneco->createAnim();

	addInputListener(n);
	addInputListener(muneco);
	addInputListener(river);
	addInputListener(bomba);
	addInputListener(sinbadBombScene);

	//nubes
	BillboardSet* bbSet = mSM->createBillboardSet("bsNubes", 20);
	bbSet->setDefaultDimensions(1000, 1000);
	bbSet->setMaterialName("Practica1/WhiteSmoke");

	auto bbNode = sceneNode->createChildSceneNode();
	bbNode->attachObject(bbSet);
	bbNode->translate(0, 200, 0);

	bbSet->createBillboard(Vector3(300, 700, 0));
	bbSet->createBillboard(Vector3(300, 400, 0));
	bbSet->createBillboard(Vector3(300, 100, 0));

	bbSet->createBillboard(Vector3(600, 900, 100));
	bbSet->createBillboard(Vector3(600, 600, 100));
	bbSet->createBillboard(Vector3(600, 300, 100));
	bbSet->createBillboard(Vector3(600, 0, 100));
	
	bbSet->createBillboard(Vector3(900, 900, 200));
	bbSet->createBillboard(Vector3(900, 600, 200));
	bbSet->createBillboard(Vector3(900, 300, 200));
	bbSet->createBillboard(Vector3(900, 0, 200));
	
	bbSet->createBillboard(Vector3(1200, 900, 300));
	bbSet->createBillboard(Vector3(1200, 600, 300));
	bbSet->createBillboard(Vector3(1200, 300, 300));
	bbSet->createBillboard(Vector3(1200, 0, 300));

	bbSet->createBillboard(Vector3(1500, 700, 400));
	bbSet->createBillboard(Vector3(1500, 400, 400));
	bbSet->createBillboard(Vector3(1500, 100, 400));


	//--------------------------------------------------------
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

	avionSceneNode->setVisible(false);



	//------------------------------------------------------------------------

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);

	//mCamMgr->setTarget(mSinbadNode);  
	//mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

	//------------------------------------------------------------------------

}

