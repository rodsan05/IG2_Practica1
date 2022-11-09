#include "Avion.h"
#include "AspasNave.h"

Avion::Avion(Ogre::SceneNode* node, float scale, float offsetNodoFict) : EntityIG(node)
{
	nodoAvion = mNode->createChildSceneNode();

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

	nodoAvion->translate(-offsetNodoFict, 0, 0);
	nodoAvion->roll(Ogre::Degree(-15));
}

Avion::~Avion()
{
}

void Avion::frameRendered(const Ogre::FrameEvent& evt)
{
	float angle = 20;

	mNode->yaw(Ogre::Degree(angle * evt.timeSinceLastFrame));
	aspaL->rotate();
	aspaR->rotate();
}
