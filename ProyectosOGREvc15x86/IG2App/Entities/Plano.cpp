#include "Plano.h"

Plano::Plano(Ogre::SceneNode* node, float h, float w, Ogre::String material) : EntityIG(node)
{
	Ogre::MeshManager::getSingleton().createPlane("mPlane/" + material, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), h, w, 100, 80, true, 1, 1.0, 1.0, Ogre::Vector3::UNIT_Z);

	plane = mSM->createEntity("mPlane/" + material);

	plane->setMaterialName(material);

	mNode->attachObject(plane);
}

Plano::~Plano()
{
}

bool Plano::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	/*if (evt.keysym.sym == SDLK_r)
	{
		sendEvent(this);

		moviendose = !moviendose;

		if (moviendose) plane->setMaterialName("Practica1/Rio");

		else plane->setMaterialName("Practica1/RioQuieto");
	}*/

	return true;
}
