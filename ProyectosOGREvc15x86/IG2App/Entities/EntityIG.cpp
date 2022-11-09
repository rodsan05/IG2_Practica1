#include "AspaNoria.h"
#include "EntityIG.h"

std::vector<EntityIG*> EntityIG::appListeners =std::vector<EntityIG*>(0, nullptr);

EntityIG::EntityIG(Ogre::SceneNode* node)
{
	//La constructora pasa el nodo asociado al objeto
	//creado, como parámetro
	mNode = node;
	mSM = mNode->getCreator();
}

EntityIG::~EntityIG()
{
	delete mNode;
}

void EntityIG::frameRendered(const Ogre::FrameEvent& evt)
{
}

bool EntityIG::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	return false;
}

bool EntityIG::keyReleased(const OgreBites::KeyboardEvent& evt)
{
	return false;
}

bool EntityIG::mousePressed(const OgreBites::MouseButtonEvent& evt)
{
	return false;
}

bool EntityIG::mouseRelease(const OgreBites::MouseButtonEvent& evt)
{
	return false;
}

bool EntityIG::mouseMoved(const OgreBites::MouseMotionEvent& evt)
{
	return false;
}

bool EntityIG::mouseWheelRolled(const OgreBites::MouseWheelEvent& evt)
{
	return false;
}

void EntityIG::sendEvent(EntityIG* entidad)
{
	for (EntityIG* e : appListeners)
		e->receiveEvent(this);
}
