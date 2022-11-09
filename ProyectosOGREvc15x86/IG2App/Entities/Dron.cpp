#include "Dron.h"

Dron::Dron(Ogre::SceneNode* node, int nBrazos, float scale, float offset, bool nodriza) : EntityIG(node)
{
	dron = mNode->createChildSceneNode();

	entBody = mSM->createEntity("sphere.mesh");

	if (nodriza)
		entBody->setMaterialName("Practica1/Rojo");
	else
		entBody->setMaterialName("Practica1/Cabeza");

	Ogre::SceneNode* nBody = dron->createChildSceneNode();
	nBody->attachObject(entBody);
	nBody->setScale(scale * Ogre::Vector3(0.35));

	Ogre::SceneNode* brazo = dron->createChildSceneNode();
	brazos.push_back(new BrazoDron(brazo, scale * 1.3));
	brazo->translate(scale * 130 / 2, 0, 0, Ogre::Node::TS_LOCAL);

	float angle = 0;
	for (int i = 1; i < nBrazos; i++)
	{
		angle = 360 / nBrazos * i;

		Ogre::SceneNode* brazo = dron->createChildSceneNode();

		brazos.push_back(new BrazoDron(brazo, scale));

		brazo->roll(Ogre::Degree(angle));
		brazo->translate(scale * 100 / 2, 0, 0, Ogre::Node::TS_LOCAL);
	}

	dron->translate(0, 0, offset);
	dron->roll(Ogre::Degree(-90));

	myTimer = new Ogre::Timer();
}

Dron::~Dron()
{
	delete myTimer;
}

void Dron::frameRendered(const Ogre::FrameEvent& evt)
{
	Ogre::Real time = evt.timeSinceLastFrame;

	if (rand() % 1 == 0)
	{
		dir = -1;
	}
	else dir = 1;

	for (auto b : brazos)
	{
		b->frameRendered(evt);
	}

	if (!rotating)
	{
		mNode->pitch(Ogre::Degree(MOVEMENT_VEL * time));

		if (myTimer->getMilliseconds() >= 2000)
		{
			rotating = true;

			randomWaitTime = rand() % 2000;

			myTimer->reset();
		}
	}

	else 
	{
		mNode->roll(Ogre::Degree(ROTATION_VEL * time * dir));

		if (myTimer->getMilliseconds() > randomWaitTime) 
		{
			rotating = false;

			myTimer->reset();
		}
	}
}

void Dron::changeColor()
{
	entBody->setMaterialName("Practica1/Amarillo");
}
