#ifndef BMETALSONIC_H
#define BMETALSONIC_H

class TexturedModel;
class Body;
class Limb;
class Source;

#include <list>
#include <vector>
#include "../entities.h"

class B_MetalSonic : public Entity
{
private:
	static std::list<TexturedModel*> modelBody;
	static std::list<TexturedModel*> modelHead;
	static std::list<TexturedModel*> modelLeftHumerus;
	static std::list<TexturedModel*> modelLeftForearm;
	static std::list<TexturedModel*> modelLeftHand;
	static std::list<TexturedModel*> modelLeftThigh;
	static std::list<TexturedModel*> modelLeftShin;
	static std::list<TexturedModel*> modelLeftFoot;
	static std::list<TexturedModel*> modelRightHumerus;
	static std::list<TexturedModel*> modelRightForearm;
	static std::list<TexturedModel*> modelRightHand;
	static std::list<TexturedModel*> modelRightThigh;
	static std::list<TexturedModel*> modelRightShin;
	static std::list<TexturedModel*> modelRightFoot;

	static std::vector<Vector3f> splineIntro;

	Body* myBody;
	Limb* myHead;
	Limb* myLeftHumerus;
	Limb* myLeftForearm;
	Limb* myLeftHand;
	Limb* myLeftThigh;
	Limb* myLeftShin;
	Limb* myLeftFoot;
	Limb* myRightHumerus;
	Limb* myRightForearm;
	Limb* myRightHand;
	Limb* myRightThigh;
	Limb* myRightShin;
	Limb* myRightFoot;

	float xVel;
	float yVel;
	float zVel;

	Source* mySource;

	int health;
	int deathTimer;

	int timer;
	int iFrames;
	int hitTimer;

	bool shouldFollowSpline;
	float splineTimer;

	bool isTeleporting;
	int teleportingTimer;

	int chargeTimer;
	int aheadOfSonicTimer;

	int shootTimer;

	int behindSonicTimer;
	int spinTimer;

	void createLimbs();

	void addLimbsToGame();

	void removeLimbsFromGame();

	void setLimbsVisibility(bool newVisible);

	void updateLimbs(int animIndex, float time);

	void updateLimbsMatrix();

	void animate();

public:
	B_MetalSonic();

	void step();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();

	bool canHomingAttackOn();

	Vector3f getHomingCenter();
};
#endif