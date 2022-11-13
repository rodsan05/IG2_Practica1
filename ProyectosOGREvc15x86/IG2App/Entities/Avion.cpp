#include "Avion.h"
#include "AspasNave.h"

Avion::Avion(Ogre::SceneNode* node, float scale, float offsetNodoFict) : EntityIG(node)
{
	nodoAvionParticulas = mNode->createChildSceneNode();
	nodoAvion = nodoAvionParticulas->createChildSceneNode();

	//Billboard
	Ogre::BillboardSet* bbSet = mSM->createBillboardSet("10pointsPlane", 1);
	bbSet->setDefaultDimensions(70 * scale, 50 * scale);
	bbSet->setMaterialName("Practica1/10points");

	auto nodoBB = nodoAvion->createChildSceneNode();
	nodoBB->attachObject(bbSet);
	bbSet->createBillboard(0, 0, -150 * scale);

	//ParticleSystem
	Ogre::ParticleSystem* pSys = mSM->createParticleSystem("psSmoke", "Practica1/SmokePlane");
	pSys->setEmitting(true);
	auto mPSNode = nodoAvionParticulas->createChildSceneNode();
	mPSNode->attachObject(pSys);

	//entidades
	Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");
	sphere->setMaterialName("Practica1/Rojo");

	Ogre::SceneNode* nBody = nodoAvion->createChildSceneNode();
	nBody->attachObject(sphere);
	nBody->setScale(scale * Ogre::Vector3(1));

	Ogre::SceneNode* barrel = nodoAvion->createChildSceneNode();
	Ogre::Entity* entBarrel = mSM->createEntity("Barrel.mesh");
	entBarrel->setMaterialName("Practica1/Naranja");

	barrel->attachObject(entBarrel);
	barrel->pitch(Ogre::Degree(90));
	barrel->setScale(scale * 10, scale * 3, scale * 10);
	barrel->translate(0, 0, scale * 3 * 35);

	Ogre::Entity* wingCubeL = mSM->createEntity("cube.mesh");
	wingCubeL->setMaterialName("Practica1/Checker");

	Ogre::SceneNode* nLeftWing = nodoAvion->createChildSceneNode();
	nLeftWing->attachObject(wingCubeL);
	nLeftWing->setScale(scale * 2, scale * 0.1, scale);
	nLeftWing->translate(scale * 50 * 3, 0, 0);

	Ogre::Entity* wingCubeR = mSM->createEntity("cube.mesh");
	wingCubeR->setMaterialName("Practica1/Checker");

	Ogre::SceneNode* nRightWing = nodoAvion->createChildSceneNode();
	nRightWing->attachObject(wingCubeR);
	nRightWing->setScale(scale * 2, scale * 0.1, scale);
	nRightWing->translate(-scale * 50 * 3, 0, 0);

	Ogre::SceneNode* nAspasL = nodoAvion->createChildSceneNode();
	aspaL = new AspasNave(nAspasL, 5, scale / 1.5);
	nAspasL->translate(scale * 50 * 3, 0, scale * 50);

	Ogre::SceneNode* nAspasR = nodoAvion->createChildSceneNode();
	aspaR = new AspasNave(nAspasR, 5, scale / 1.5);
	nAspasR->translate(-scale * 50 * 3, 0, scale * 50);

	Ogre::Entity* entNinja = mSM->createEntity("ninja.mesh");
	entNinja->setMaterialName("Practica1/Amarillo");

	Ogre::SceneNode* ninja = nodoAvion->createChildSceneNode();
	ninja->attachObject(entNinja);
	ninja->setScale(scale * Ogre::Vector3(0.7));
	ninja->yaw(Ogre::Degree(180));
	ninja->translate(0, scale * 30 / 2, 0);

	nodoAvionParticulas->translate(-offsetNodoFict, 0, 0);
	nodoAvionParticulas->roll(Ogre::Degree(-15));

	myTimer = new Ogre::Timer();
}

Avion::~Avion()
{
}

void Avion::frameRendered(const Ogre::FrameEvent& evt)
{
	float angle = 20;

	if (!stopped)
	{
		mNode->yaw(Ogre::Degree(angle * evt.timeSinceLastFrame));
		aspaL->rotate();
		aspaR->rotate();
	}
	else
	{
		if (myTimer->getMilliseconds() > 5000)
		{
			mNode->setVisible(false);
		}
	}
}

void Avion::explode()
{
	Ogre::ParticleSystem* pSys = mSM->createParticleSystem("psPlaneExplosion", "Practica1/SmokePlaneExplosion");
	pSys->setEmitting(true);
	auto mPSNode = nodoAvionParticulas->createChildSceneNode();
	mPSNode->attachObject(pSys);

	nodoAvion->setVisible(false);

	stopped = true;

	sendEvent(this, sinbadDie);
}