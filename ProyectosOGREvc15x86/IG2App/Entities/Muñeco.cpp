#include "Muñeco.h"

Muñeco::Muñeco(Ogre::SceneNode* node) : EntityIG(node)
{
	meshCuerpo = mSM->createEntity("sphere.mesh");
	meshCuerpo->setMaterialName("Practica1/Cuerpo");
	
	meshCabeza = mSM->createEntity("sphere.mesh");
	meshCabeza->setMaterialName("Practica1/Cabeza");

	cuerpo = mNode->createChildSceneNode();
	cuerpo->attachObject(meshCuerpo);
	cabeza = mNode->createChildSceneNode();
	cabeza->attachObject(meshCabeza);

	cuerpo->setScale(2, 2, 2);

	cabeza->setPosition(0, 250, 0);
	cabeza->setScale(1, 1, 1);

	//Ogre::Entity* sph3 = mSM->createEntity("sphere.mesh");
	//sph3->setMaterialName("Practica1/Nariz");
	//Ogre::SceneNode* nariz = cabeza->createChildSceneNode();
	//nariz->attachObject(sph3);

	//nariz->setScale(0.05, 0.05, 0.05);
	//nariz->setPosition(0, 0, 100);

	Ogre::Entity* sph4 = mSM->createEntity("sphere.mesh");
	sph4->setMaterialName("Practica1/Ombligo");
	Ogre::SceneNode* ombligo = cuerpo->createChildSceneNode();
	ombligo->attachObject(sph4);

	ombligo->setScale(0.05, 0.05, 0.05);
	ombligo->setPosition(0, 0, 100);
}

Muñeco::~Muñeco()
{
}

void Muñeco::frameRendered(const Ogre::FrameEvent& evt)
{
	
}

void Muñeco::receiveEvent(EntityIG* entidad)
{
	rojo = !rojo;

	if (rojo) 
	{
		meshCabeza->setMaterialName("Practica1/CabezaRoja");
		meshCuerpo->setMaterialName("Practica1/CuerpoRojo");
	}

	else 
	{
		meshCabeza->setMaterialName("Practica1/Cabeza");
		meshCuerpo->setMaterialName("Practica1/Cuerpo");
	}
}

bool Muñeco::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (evt.keysym.sym == SDLK_UP)
	{
		mNode->translate(5, 0, 0);
	}
	else if (evt.keysym.sym == SDLK_DOWN)
	{
		mNode->translate(-5, 0, 0);
	}

	if (evt.keysym.sym == SDLK_LEFT)
	{
		mNode->yaw(Ogre::Degree(-5));
	}
	else if (evt.keysym.sym == SDLK_RIGHT)
	{
		mNode->yaw(Ogre::Degree(5));
	}

	return true;
}
