#ifndef MAIN_H
#define MAIN_H

class Entity;
class Camera;
class Player;
class Stage;
class SkySphere;
class Light;

void Main_addEntity(Entity* entityToAdd);
void Main_deleteEntity(Entity* entityToDelete);
void Main_deleteAllEntites();

class Global
{
public:
	static Camera* gameCamera;
	static Player* gamePlayer;
	static Stage* gameStage;
	static SkySphere* gameSkySphere;
	static Light* gameLightSun;
	static Light* gameLightMoon;
	static int countNew;
	static int countDelete;
};
#endif