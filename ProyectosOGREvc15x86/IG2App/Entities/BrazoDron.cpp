#include "BrazoDron.h"
#include "AspasNave.h"

BrazoDron::BrazoDron(Ogre::SceneNode* node, float scale) : EntityIG(node)
{
	Ogre::SceneNode* barrel = mNode->createChildSceneNode();
	Ogre::Entity* entBarrel = mSM->createEntity("Barrel.mesh");
	entBarrel->setMaterialName("Practica1/BumpyMetalAmarillo");

	barrel->attachObject(entBarrel);
	barrel->roll(Ogre::Degree(90));
	barrel->setScale(scale * 2, scale * 10, scale * 2);

	Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");
	sphere->setMaterialName("Practica1/Naranja");

	Ogre::SceneNode* nSphere = mNode->createChildSceneNode();
	nSphere->attachObject(sphere);
	nSphere->setScale(scale/8 * Ogre::Vector3(1));
	nSphere->translate(scale * 30, 0, 0);

	Ogre::SceneNode* aspas = mNode->createChildSceneNode();
	aspasDron = new AspasNave(aspas, 3, scale / 5);
	aspas->translate(scale * 30, 0, scale * 15);
}

BrazoDron::~BrazoDron()
{
}

void BrazoDron::frameRendered(const Ogre::FrameEvent& evt)
{
	aspasDron->frameRendered(evt);
}
