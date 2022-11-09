#include "Sinbad.h"

Sinbad::Sinbad(Ogre::SceneNode* node, float scale, float offsetNodoFict, bool runPlanet) : EntityIG(node)
{
	sinbadNode = mNode->createChildSceneNode();

	runningAroundPlanet = runPlanet;

	swordL = mSM->createEntity("Sword.mesh");
	swordR = mSM->createEntity("Sword.mesh");
	sinbadEntity = mSM->createEntity("Sinbad.mesh");
	sinbadNode->attachObject(sinbadEntity);

	mAnimStateBase = sinbadEntity->getAnimationState("RunBase");
	mAnimStateTop = sinbadEntity->getAnimationState("RunTop");
	danceState = sinbadEntity->getAnimationState("Dance");

	mAnimStateBase->setEnabled(true);
	mAnimStateBase->setLoop(true);
	mAnimStateTop->setEnabled(true);
	mAnimStateTop->setLoop(true);
	danceState->setEnabled(false);
	danceState->setLoop(true);

	sinbadNode->setScale(scale, scale, scale);
	sinbadNode->translate({ 0, offsetNodoFict, 0 });

	Ogre::AnimationStateSet* aux = sinbadEntity->getAllAnimationStates();
	auto it = aux->getAnimationStateIterator().begin();
	while (it != aux->getAnimationStateIterator().end())
	{
		auto s = it->first; ++it;
		std::cout << s << std::endl;
	}

	myTimer = new Ogre::Timer();
}

Sinbad::~Sinbad()
{
}

void Sinbad::frameRendered(const Ogre::FrameEvent& evt)
{
	mAnimStateBase->addTime(evt.timeSinceLastFrame);	
	mAnimStateTop->addTime(evt.timeSinceLastFrame);
	danceState->addTime(evt.timeSinceLastFrame);

	Ogre::Real time = evt.timeSinceLastFrame;

	if (!dancing && runningAroundPlanet)
	{
		if (rand() % 1 == 0)
		{
			dir = -1;
		}
		else dir = 1;

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
			mNode->yaw(Ogre::Degree(ROTATION_VEL * time * dir));

			if (myTimer->getMilliseconds() > randomWaitTime)
			{
				rotating = false;

				myTimer->reset();
			}
		}
	}
}

bool Sinbad::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_s)
	{
		arma();
	}
	else if (evt.keysym.sym == SDLK_a)
	{
		arma(true);
	}
	else if (evt.keysym.sym == SDLK_d)
	{
		arma(false);
	}
	else if (evt.keysym.sym == SDLK_w)
	{
		cambiaArma();
	}
	else if (evt.keysym.sym == SDLK_c) 
	{
		toggleDancing();
	}

	return true;
}

void Sinbad::arma()
{
	if (!swordR->isAttached()) 
		sinbadEntity->attachObjectToBone("Handle.R", swordR);
	
	if (!swordL->isAttached())
		sinbadEntity->attachObjectToBone("Handle.L", swordL);
}

void Sinbad::arma(bool manoDerecha)
{
	if (manoDerecha && !swordR->isAttached())
		sinbadEntity->attachObjectToBone("Handle.R", swordR);

	else if (!swordL->isAttached())
		sinbadEntity->attachObjectToBone("Handle.L", swordL);
}

void Sinbad::cambiaArma()
{
	if (swordL->isAttached() && !swordR->isAttached())
	{
		sinbadEntity->detachObjectFromBone(swordL);
		sinbadEntity->attachObjectToBone("Handle.R", swordR);
	}

	else if (swordR->isAttached() && !swordL->isAttached())
	{
		sinbadEntity->detachObjectFromBone(swordR);
		sinbadEntity->attachObjectToBone("Handle.L", swordL);
	}
}

void Sinbad::toggleDancing()
{
	dancing = !dancing;

	if (dancing) 
	{
		mAnimStateBase->setEnabled(false);
		mAnimStateTop->setEnabled(false);
		danceState->setEnabled(true);
	}

	else 
	{
		mAnimStateBase->setEnabled(true);
		mAnimStateTop->setEnabled(true);
		danceState->setEnabled(false);
	}
}
