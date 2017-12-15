#ifndef MAIN_H
#define MAIN_H

class Entity;
class Camera;
class Player;
class Stage;


void Main_addEntity(Entity* entityToAdd);
void Main_deleteEntity(Entity* entityToDelete);
void Main_deleteAllEntites();

class Global
{
public:
	static Camera* gameCamera;
	static Player* gamePlayer;
	static Stage* gameStage;
	static int countNew;
	static int countDelete;
};
#endif