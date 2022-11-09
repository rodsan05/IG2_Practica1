#include "AspaNoria.h"

AspaNoria::AspaNoria(Ogre::SceneNode* node, float longitud, float lCubo) : EntityIG(node)
{
	Ogre::Entity* cube1 = mSM->createEntity("cube.mesh");
	cube1->setMaterialName("Practica1/TablaNoria");
	Ogre::Entity* cube2 = mSM->createEntity("cube.mesh");
	cube2->setMaterialName("Practica1/TablaNoria");
	Ogre::Entity* cube3 = mSM->createEntity("cube.mesh");
	cube3->setMaterialName("Practica1/CajaNoria");

	cubo = mNode->createChildSceneNode();
	cubo->attachObject(cube3);

	cubo->setScale(lCubo, lCubo, lCubo);
	cubo->setPosition(longitud * 50, 0, 0);

	tableroD = mNode->createChildSceneNode();
	tableroD->attachObject(cube1);

	tableroD->setScale(longitud, 1, 0.1);
	tableroD->setPosition(0, 0, -lCubo * 50);

	tableroI = mNode->createChildSceneNode();
	tableroI->attachObject(cube2);

	tableroI->setScale(longitud, 1, 0.1);
	tableroI->setPosition(0, 0, lCubo * 50);
}

AspaNoria::~AspaNoria()
{
}

void AspaNoria::frameRendered(const Ogre::FrameEvent& evt)
{
}
