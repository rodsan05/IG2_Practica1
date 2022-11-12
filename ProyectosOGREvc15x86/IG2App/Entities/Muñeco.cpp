#include "Muñeco.h"

Muñeco::Muñeco(Ogre::SceneNode* node) : EntityIG(node)
{
	meshCuerpo = mSM->createEntity("sphere.mesh");
	meshCuerpo->setMaterialName("Practica1/Cuerpo");
	
	meshCabeza = mSM->createEntity("sphere.mesh");
	meshCabeza->setMaterialName("Practica1/Cuerpo");

	cuerpo = mNode->createChildSceneNode();
	cuerpo->attachObject(meshCuerpo);
	cabeza = mNode->createChildSceneNode();
	cabeza->attachObject(meshCabeza);

	cuerpo->setScale(2, 2, 2);

	cabeza->setPosition(0, 250, 0);
	cabeza->setScale(1, 1, 1);

	Ogre::Entity* sph3 = mSM->createEntity("sphere.mesh");
	sph3->setMaterialName("Practica1/Nariz");
	Ogre::SceneNode* nariz = cabeza->createChildSceneNode();
	nariz->attachObject(sph3);

	nariz->setScale(0.05, 0.05, 0.05);
	nariz->setPosition(0, 0, 100);

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
	mAnimState->addTime(evt.timeSinceLastFrame);
}

void Muñeco::createAnim()
{
	mNode->setInitialState();

	float longDesplazamiento = 360;
	float duracion = 18;

	Ogre::Animation* animation = mSM->createAnimation("muñecoAnim", duracion);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(mNode);

	Ogre::Vector3 keyframePos(0, 0, 0);
	Ogre::Real durPaso = duracion / 5.0;

	Ogre::Quaternion quat = Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3(0, 1, 0));
	Ogre::TransformKeyFrame* kf;
	kf = track->createNodeKeyFrame(durPaso * 0);
	kf->setTranslate(keyframePos);
	kf->setRotation(quat);

	//quaternion para rotar de src a dest (ángulo menor)
	quat = Ogre::Quaternion(Ogre::Degree(-90), Ogre::Vector3(0, 1, 0));
	kf = track->createNodeKeyFrame(durPaso * 1); // Keyframe 1: mirando a plataforma
	kf->setTranslate(keyframePos);
	kf->setRotation(quat);

	kf = track->createNodeKeyFrame(durPaso * 2); // Keyframe 2: va a plataforma
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_X * longDesplazamiento;
	kf->setTranslate(keyframePos); // plataforma
	kf->setRotation(quat);

	quat = Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3(0, 1, 0));
	kf = track->createNodeKeyFrame(durPaso * 3); // Keyframe 3: mira a origen
	kf->setTranslate(keyframePos);
	kf->setRotation(quat);

	kf = track->createNodeKeyFrame(durPaso * 4); // Keyframe 4: vuelve a origen
	keyframePos += Ogre::Vector3::UNIT_X * longDesplazamiento;
	kf->setTranslate(keyframePos); // Origen
	kf->setRotation(quat);

	quat = Ogre::Quaternion(Ogre::Degree(0), Ogre::Vector3(0, 1, 0));
	kf = track->createNodeKeyFrame(durPaso * 5); // Keyframe 5: vuelve a mirar al eje Z
	kf->setTranslate(keyframePos);
	kf->setRotation(quat);

	mAnimState = mSM->createAnimationState("muñecoAnim");
	mAnimState->setLoop(true);
	mAnimState->setEnabled(true);
}
