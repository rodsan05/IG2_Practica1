#pragma once
#include "EntitiesIncludes.h"
#include "EntityIG.h"
class AspasNave : public EntityIG
{
public:
	AspasNave(Ogre::SceneNode* node, int nBrazos, float longitud);
	~AspasNave();

	void rotate();

protected:
	Ogre::SceneNode* aspasPiv = nullptr;
};

