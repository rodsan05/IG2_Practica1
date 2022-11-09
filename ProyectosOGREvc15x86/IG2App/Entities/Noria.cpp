#include "Noria.h"
#include "AspaNoria.h"

Noria::Noria(Ogre::SceneNode* node, int nBrazos, float longitud, float lCubo) : EntityIG(node)
{
	noriaPiv = mNode->createChildSceneNode();

	Ogre::SceneNode* barrel = mNode->createChildSceneNode(); 
	auto barrelEnt = mSM->createEntity("Barrel.mesh");
	barrelEnt->setMaterialName("Practica1/BarrilNoria");
	barrel->attachObject(barrelEnt);
	barrel->pitch(Ogre::Degree(90));
	barrel->setScale(lCubo * 25, lCubo * 25, lCubo * 25);

	float angle;

	for (int i = 0; i < nBrazos; i++) 
	{
		angle = 360 / nBrazos * i;

		Ogre::SceneNode* n = noriaPiv->createChildSceneNode();

		new AspaNoria(n, 10, 2);

		n->roll(Ogre::Degree(angle));
		n->translate(longitud * 50 / 2, 0, 0, Ogre::Node::TS_LOCAL);

		Ogre::Node* cubo = (*n->getChildIterator().begin());
		cubo->roll(Ogre::Degree(-angle));
	}
}

Noria::~Noria()
{
}

void Noria::frameRendered(const Ogre::FrameEvent& evt)
{
	if (!paused)
	{
		float angle = 20;

		Ogre::Real time = evt.timeSinceLastFrame;

		noriaPiv->roll(Ogre::Degree(angle * time));

		for (auto a : noriaPiv->getChildIterator())
		{
			Ogre::Node* n = (*a->getChildIterator().begin());
			n->roll(Ogre::Degree(-angle * time));
		}
	}
}

bool Noria::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_q)
	{
		if (paused)
		{
			float angle = 5;

			noriaPiv->roll(Ogre::Degree(angle));

			for (auto a : noriaPiv->getChildIterator())
			{
				Ogre::Node* n = (*a->getChildIterator().begin());
				n->roll(Ogre::Degree(-angle));
			}
		}
	}

	return true;
}

void Noria::receiveEvent(EntityIG* entidad)
{
	paused = !paused;
}
