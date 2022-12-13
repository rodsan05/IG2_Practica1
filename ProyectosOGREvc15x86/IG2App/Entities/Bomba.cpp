#include "Bomba.h"

Bomba::Bomba(Ogre::SceneNode* node, float scale) : EntityIG(node)
{
	nodoBomba = mNode->createChildSceneNode();

	auto ent = mSM->createEntity("uv_sphere.mesh");
	ent->setMaterialName("Practica2/SpotLight");

	nodoBomba->attachObject(ent);
	nodoBomba->setScale(scale, scale, scale);

	nodoBomba->setInitialState();

	float longDesplazamiento = 100 * scale;
	float duracion = 16;

	float angle = 45;

	Ogre::Animation* animation = mSM->createAnimation("animVV", duracion);
	Ogre::NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(nodoBomba);

	Ogre::Vector3 keyframePos(0.0, 0.0, 0.0);
	Ogre::Real durPaso = duracion / 4.0;

	Ogre::Quaternion quat = Ogre::Quaternion(Ogre::Degree(angle * 0), Ogre::Vector3(0, 1, 0));
	Ogre::TransformKeyFrame* kf;
	kf = track->createNodeKeyFrame(durPaso * 0);
	kf->setTranslate(keyframePos);
	kf->setRotation(quat);

	quat = Ogre::Quaternion(Ogre::Degree(angle * 1), Ogre::Vector3(0, 1, 0));
	kf = track->createNodeKeyFrame(durPaso * 1); // Keyframe 1: arriba
	keyframePos += Ogre::Vector3::UNIT_Y * longDesplazamiento;
	kf->setTranslate(keyframePos); // Arriba
	kf->setRotation(quat);

	quat = Ogre::Quaternion(Ogre::Degree(angle * 0), Ogre::Vector3(0, 1, 0));
	kf = track->createNodeKeyFrame(durPaso * 2); // Keyframe 2: origen
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y * longDesplazamiento;
	kf->setTranslate(keyframePos); // Origen
	kf->setRotation(quat);

	quat = Ogre::Quaternion(Ogre::Degree(angle * -1), Ogre::Vector3(0, 1, 0));
	kf = track->createNodeKeyFrame(durPaso * 3); // Keyframe 3: abajo
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y * longDesplazamiento;
	kf->setTranslate(keyframePos); // Abajo
	kf->setRotation(quat);

	quat = Ogre::Quaternion(Ogre::Degree(angle * 0), Ogre::Vector3(0, 1, 0));
	kf = track->createNodeKeyFrame(durPaso * 4); // Keyframe 4: origen
	keyframePos += Ogre::Vector3::UNIT_Y * longDesplazamiento;
	kf->setTranslate(keyframePos); // Origen
	kf->setRotation(quat);

	animationState = mSM->createAnimationState("animVV");
	animationState->setLoop(true);
	animationState->setEnabled(true);

	myTimer = new Ogre::Timer();
}

Bomba::~Bomba()
{
}

void Bomba::frameRendered(const Ogre::FrameEvent& evt)
{
	if (!stopped && (!stopTimerActivated || myTimer->getMilliseconds() <= timeToStop))
	{
		animationState->addTime(evt.timeSinceLastFrame);
	}
}

void Bomba::receiveEvent(EntityIG* entidad, MessageType message)
{
	if (message == bombExplode)
		explode();
}

void Bomba::setStopTimer(float time)
{
	if (!stopTimerActivated)
	{
		stopTimerActivated = true;

		timeToStop = time;
		myTimer->reset();
	}
}

void Bomba::explode()
{
	Ogre::ParticleSystem* pSys = mSM->createParticleSystem("psBombExplosion", "Practica1/Smoke");
	pSys->setEmitting(true);
	auto mPSNode = mNode->createChildSceneNode();
	mPSNode->attachObject(pSys);

	nodoBomba->setVisible(false);

	stopped = true;
}
