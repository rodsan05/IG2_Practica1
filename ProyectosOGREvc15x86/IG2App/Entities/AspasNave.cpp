#include "AspasNave.h"

AspasNave::AspasNave(Ogre::SceneNode* node, int nBrazos, float longitud) : EntityIG(node)
{
	Ogre::SceneNode* barrel = mNode->createChildSceneNode();
	Ogre::Entity* entBarrel = mSM->createEntity("Barrel.mesh");
	entBarrel->setMaterialName("Practica1/Dirt01");

	barrel->attachObject(entBarrel);
	barrel->pitch(Ogre::Degree(90));
	barrel->setScale(longitud * 3, longitud, longitud * 3);

	aspasPiv = mNode->createChildSceneNode();

	float angle;
	for (int i = 0; i < nBrazos; i++)
	{
		Ogre::Entity* cube1 = mSM->createEntity("cube.mesh");
		cube1->setMaterialName("Practica1/TablaNoria");

		angle = 360 / nBrazos * i;

		Ogre::SceneNode* aspa = aspasPiv->createChildSceneNode();
		Ogre::SceneNode* n = aspa->createChildSceneNode();

		n->attachObject(cube1);
		n->setScale(longitud * 0.7, longitud * 0.1, longitud * 0.01);

		n->translate(longitud * 100 * 0.7 / 2, 0, 0, Ogre::Node::TS_LOCAL);

		Ogre::Entity* cilindro = mSM->createEntity("Barrel.mesh");
		cilindro->setMaterialName("Practica1/Rojo");
		Ogre::SceneNode* nCilindro = aspa->createChildSceneNode();
		nCilindro->attachObject(cilindro);
		nCilindro->translate(longitud * 100 * 0.7 * 0.9, 0, 0);

		nCilindro->scale(longitud * 0.6, longitud * 1.8, longitud * 0.6);
		
		aspa->roll(Ogre::Degree(angle));
		nCilindro->roll(Ogre::Degree(-angle), Ogre::Node::TS_WORLD);
	}
}

AspasNave::~AspasNave()
{
}

void AspasNave::rotate()
{
	float angle = -20;

	mNode->roll(Ogre::Degree(angle));

	for (auto a : aspasPiv->getChildIterator())
	{
		//cogemos el segundo nodo hijo (cilindro rojo)
		auto it = a->getChildIterator().begin(); it++;
		Ogre::Node* n = (*it);
		n->roll(Ogre::Degree(-angle));
	}
}
