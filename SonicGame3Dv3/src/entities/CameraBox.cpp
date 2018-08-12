#include "camerabox.h"
#include "controllableplayer.h"
#include "camera.h"
#include "../engineTester/main.h"
#include "../models/models.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../toolbox/maths.h"

#include <algorithm>

std::list<TexturedModel*> CameraBox::models;

CameraBox::CameraBox()
{

}

CameraBox::CameraBox(
		float rotationY, float panSpeed,
		float x, float y, float z,
		float scaleX, float scaleY, float scaleZ,
		float p1X, float p1Y, float p1Z,
		float p2X, float p2Y, float p2Z,
		int flags)
{
	position.x = x;
	position.y = y;
	position.z = z;
	this->panSpeed = panSpeed;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
	this->scaleZ = scaleZ;
	this->p1X    = p1X;
	this->p1Y    = p1Y;
	this->p1Z    = p1Z;
	this->p2X    = p2X;
	this->p2Y    = p2Y;
	this->p2Z    = p2Z;
	this->flags  = flags;
	rotX = 0;
	rotY = rotationY;
	rotZ = 0;

	sinT = sinf(toRadians(rotY));
	cosT = cosf(toRadians(rotY));
	float xDiff = p2X-p1X;
	float yDiff = p2Y-p1Y;
	float zDiff = p2Z-p1Z;
	float hDist = sqrtf(xDiff*xDiff + zDiff*zDiff);

	camTargetYaw   = -toDegrees(atan2f(-zDiff, xDiff))-90;
	camTargetPitch =  toDegrees(atan2f(yDiff, hDist));

	scale = 1;
	visible = false;
	updateTransformationMatrix(scaleX, scaleY, scaleZ);
}

void CameraBox::step()
{
	if (Global::isAutoCam && Global::finishStageTimer == -1 && abs(Global::gamePlayer->getY()+6 - getY()) <= scaleY)
	{
		//Rotate player coords by negative yrot to get in box coordinate system
		float xDiff = Global::gamePlayer->getX() - getX();
		float zDiff = Global::gamePlayer->getZ() - getZ();
		
		float newX = xDiff*cosT - zDiff*sinT;
		float newZ = zDiff*cosT + xDiff*sinT;

		if (abs(newX) <= scaleX &&
			abs(newZ) <= scaleZ)
		{
			//std::fprintf(stdout, "nice\n");
			//Global::gamePlayer->setCameraAngles(camTargetYaw, camTargetPitch);
			//Global::gamePlayer->setCameraTargetPitch(camTargetPitch);

			//float xDiffCam = Global::gameCamera->getPosition()->x - p1X;
			//float zDiffCam = Global::gameCamera->getPosition()->z - p1Z;
			//float yDiffCam = Global::gameCamera->getPosition()->y - p1Y;
			//float hDistCam = sqrtf(xDiffCam*xDiffCam + zDiffCam*zDiffCam);

			//float toTargetYaw   = -toDegrees(atan2f(-zDiffCam, xDiffCam))-90;
			//float toTargetPitch =  toDegrees(atan2f(yDiffCam, hDistCam));

			//Global::gameCamera->setTarget(p1X, p1Y, p1Z);

			//Global::gamePlayer->setCameraAngles(toTargetYaw, toTargetPitch);

			//float diffPitch = 0.125f*(Global::gameCamera->getPitch() - camTargetPitch);
			//Global::gamePlayer->setCameraTargetPitch(camTargetPitch);

			//float diffYaw = 0.125f*(Global::gameCamera->getYaw() - camTargetYaw);
			//Global::gamePlayer->setCameraTargetYaw(camTargetYaw);

			//Global::gamePlayer->setCameraAngles(Global::gameCamera->getYaw() - diffYaw, Global::gameCamera->getPitch() - diffPitch);



			//float xDiffCam = Global::gamePlayer->getPosition()->x - p1X;
			//float zDiffCam = Global::gamePlayer->getPosition()->z - p1Z;
			//float toTargetYaw   = -toDegrees(atan2f(-zDiffCam, xDiffCam))-90;
			//float diffYaw   = 0.125f*compareTwoAngles(toTargetYaw,   Global::gameCamera->getYaw());

			//Global::gamePlayer->setCameraTargetYaw(Global::gameCamera->getYaw() + diffYaw);


			switch (flags)
			{
				case 0:
				{
					float xDiffCam = Global::gamePlayer->getPosition()->x - p1X;
					float zDiffCam = Global::gamePlayer->getPosition()->z - p1Z;
					float toTargetYaw   = -toDegrees(atan2f(-zDiffCam, xDiffCam))-90;
					float diffYaw   = 0.125f*compareTwoAngles(toTargetYaw,   Global::gameCamera->getYaw());

					Global::gamePlayer->setCameraTargetYaw(Global::gameCamera->getYaw() + diffYaw);
					break;
				}

				case 1:
				{
					float xDiffCam = Global::gamePlayer->getPosition()->x - p1X;
					float zDiffCam = Global::gamePlayer->getPosition()->z - p1Z;
					float toTargetYaw   = -toDegrees(atan2f(-zDiffCam, xDiffCam))-90;
					float diffYaw   = 0.125f*compareTwoAngles(toTargetYaw,   Global::gameCamera->getYaw());

					Global::gamePlayer->setCameraTargetYaw(Global::gameCamera->getYaw() + diffYaw);

					float yDiffCam = Global::gamePlayer->getPosition()->y - p1Y + 60; //60 offset to look a bit more downward
					float hDistCam = sqrtf(xDiffCam*xDiffCam + zDiffCam*zDiffCam);
					float toTargetPitch =  toDegrees(atan2f(yDiffCam, hDistCam));
					float diffPitch = 0.125f*compareTwoAngles(toTargetPitch, Global::gameCamera->getPitch());

					Global::gamePlayer->setCameraTargetPitch(Global::gameCamera->getPitch() + diffPitch);
					break;
				}

				case 2:
				{
					float xDiffCam = Global::gamePlayer->getPosition()->x - p1X;
					float zDiffCam = Global::gamePlayer->getPosition()->z - p1Z;
					float toTargetYaw   = -toDegrees(atan2f(-zDiffCam, xDiffCam)) + p2X;
					float diffYaw   = 0.125f*compareTwoAngles(toTargetYaw,   Global::gameCamera->getYaw());

					Global::gamePlayer->setCameraTargetYaw(Global::gameCamera->getYaw() + diffYaw);
					break;
				}

				case 3:
				{
					float xDiffCam = Global::gamePlayer->getPosition()->x - p1X;
					float zDiffCam = Global::gamePlayer->getPosition()->z - p1Z;
					float toTargetYaw   = -toDegrees(atan2f(-zDiffCam, xDiffCam))-180 + p2X;
					float diffYaw   = 0.125f*compareTwoAngles(toTargetYaw,   Global::gameCamera->getYaw());

					Global::gamePlayer->setCameraTargetYaw(Global::gameCamera->getYaw() + diffYaw);
					break;
				}

				default:
				{
					
				}
						
			}
		}
	}
}

std::list<TexturedModel*>* CameraBox::getModels()
{
	return &CameraBox::models;
}

void CameraBox::loadStaticModels()
{
	if (CameraBox::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading CameraBox static models...\n");
	#endif

	loadObjModel(&CameraBox::models, "res/Models/Box/", "CamBox.obj");
}

void CameraBox::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting CameraBox static models...\n");
	#endif

	Entity::deleteModels(&CameraBox::models);
}
