#ifndef ITEMCAPSULE_H
#define ITEMCAPSULE_H

class TexturedModel;
class Body;

#include <list>
#include "entities.h"


class ItemCapsule : public Entity
{
private:
	static std::list<TexturedModel*> modelsSolid;
	static std::list<TexturedModel*> modelsGlass;

	static std::list<TexturedModel*> modelsItem1Up;
	static std::list<TexturedModel*> modelsItemBomb;
	static std::list<TexturedModel*> modelsItemInvincible;
	static std::list<TexturedModel*> modelsItemBarrierG;
	static std::list<TexturedModel*> modelsItemRing5;
	static std::list<TexturedModel*> modelsItemRing10;
	static std::list<TexturedModel*> modelsItemRing20;
	static std::list<TexturedModel*> modelsItemSpeedUp;
	static std::list<TexturedModel*> modelsItemBarrierB;

	static float colHorizontal;
	static float colVertical;

	Vector3f centerPos;

	int itemType;
	Body* entityGlass;
	Body* entityItem;

public:
	ItemCapsule();
	ItemCapsule(float x, float y, float z, float yRot, float zRot, int type);

	void step();

	void die();

	std::list<TexturedModel*>* getModels();

	static void loadStaticModels();

	static void deleteStaticModels();

	bool canHomingAttackOn();

	Vector3f getHomingCenter();
};
#endif