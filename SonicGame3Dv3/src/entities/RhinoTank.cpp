#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "rhinotank.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/playersonic.h"
#include "../toolbox/maths.h"
#include "../animation/body.h"
#include "../entities/camera.h"
#include "../audio/audioplayer.h"
#include "../particles/particleresources.h"
#include "../particles/particle.h"
#include "../collision/triangle3d.h"
#include "../collision/collisionchecker.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <cmath>

std::list<TexturedModel*> RhinoTank::models;

float RhinoTank::colHorizontal = 5;
float RhinoTank::colVertical = 10;

RhinoTank::RhinoTank()
{

}

RhinoTank::RhinoTank(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scale = 1;
	visible = true;
	updateTransformationMatrix();

	furyTimer = 0;
	furyTimerMax = 150;
	triCol = nullptr;
	inAir = true;
	clock = 0;
	animIndex = 0;
}

void RhinoTank::step()
{
	if (abs(getX() - Global::gameCamera->getPosition()->x) > ENTITY_RENDER_DIST)
	{
		setVisible(false);
	}
	else
	{
		if (abs(getZ() - Global::gameCamera->getPosition()->z) > ENTITY_RENDER_DIST)
		{
			setVisible(false);
		}
		else
		{
			setVisible(true);

			clock++;
			furyTimer = std::max(0, furyTimer-1);
		
		
			yVel = std::fmaxf(-2, yVel-0.1f);

			ControllablePlayer* p = Global::gamePlayer;
		
			float xDiff = p->getX()-getX();
			float zDiff = p->getZ()-getZ();
			float angleRad = toRadians(getRotY());
			float newZ = ((xDiff)*-sinf(angleRad) - (zDiff)*cosf(angleRad));
			float mag = sqrtf((xDiff*xDiff)+(zDiff*zDiff));

			applyFriction(1.3f);

			if (!inAir && triCol->normal.y >= 0.5f)
			{
				float pushUpValue = -getY()+(((-triCol->A*(getX()+xVel))+
													 (-triCol->C*(getZ()+zVel))-
													  (triCol->D))/triCol->B);
				yVel = pushUpValue;
			}

			if (mag < 64)
			{
				if (furyTimer == 0)
				{
					furyTimer = furyTimerMax;
					setRotY(toDegrees(atan2f(-zDiff, xDiff)));
					//AudioRes.playSound(27, 1, getPosition());
					xVel = 0;
					zVel = 0;
					yVel = 0.25f;
					increasePosition(0, 1, 0);
				}
			}
			else
			{
				if (mag < 500 && furyTimer == 0)
				{
					float ran = Maths::random();
					if (ran < 0.01f)
					{
						if (ran < 0.003f && clock > 30)
						{
							xVel = 0;
							zVel = 0;
							yVel = 1;
							setRotY(Maths::random()*360);
							clock = 0;
						}
						else
						{
							increaseRotation(0, (Maths::random()*120-60), 0);
						}
					}
				
					if (clock > 30 && furyTimer == 0)
					{
						moveMeSlow();
					}
				}
			}

			if (furyTimer > 30)
			{
				if (newZ >= 2.8f)
				{
					increaseRotation(0, 2.8f, 0);
				}
				else if (newZ <= -2.8f)
				{
					increaseRotation(0, -2.8f, 0);
				}
			
				if (furyTimer < furyTimerMax-45)
				{
					moveMe();
				}
			}

			if (mag < 500)
			{
				if (p->getX() > getX()-RhinoTank::colHorizontal-p->getHitboxHorizontal() && p->getX() < getX()+RhinoTank::colHorizontal+p->getHitboxHorizontal() &&
						   p->getZ() > getZ()-RhinoTank::colHorizontal-p->getHitboxHorizontal() && p->getZ() < getZ()+RhinoTank::colHorizontal+p->getHitboxHorizontal())
				{
					if (p->getY() > getY()-p->getHitboxVertical() && p->getY() < getY()+RhinoTank::colVertical)
					{
						if (p->isVulnerable() == false)
						{
							xVel = 0;
							zVel = 0;
							p->rebound(getPosition());
							die();
							//AudioSources.play(28, getPosition());
						}
						else
						{
							//damage player
							p->takeDamage(getPosition());
						}
					}
				}
			
				if (CollisionChecker::checkCollision(getX(), getY(), getZ(), getX()+xVel, getY()+yVel, getZ()+zVel) == false)
				{
					if (CollisionChecker::checkCollision(getX()+xVel, getY()+yVel, getZ()+zVel, getX()+xVel, getY()+yVel-1.0f, getZ()+zVel) == true)
					{
						Triangle3D* savedTri = CollisionChecker::getCollideTriangle();
						Vector3f triColPosition(CollisionChecker::getCollidePosition());

						float xTest =  10*cosf(toRadians(getRotY()));
						float zTest = -10*sinf(toRadians(getRotY()));
						if (CollisionChecker::checkCollision(getX()+xTest, getY(), getZ()+zTest, getX()+xTest, getY()-10.0f, getZ()+zTest) == true)
						{
							inAir = false;
							triCol = savedTri;
							//Vector3f* triColPosition = CollisionChecker::getCollidePosition();
					
							//yVel = 0;
					
							float colXNormal = triCol->normal.x;
							float colYNormal = triCol->normal.y;
							float colZNormal = triCol->normal.z;
					
							if (colYNormal >= 0.75f)
							{
								setX(triColPosition.x);
								setY(triColPosition.y+colYNormal*0.5f);
								setZ(triColPosition.z);
							}
							else
							{
								if (colYNormal >= 0.5f)
								{
									setX(triColPosition.x);
									setY(triColPosition.y+colYNormal*0.5f);
									setZ(triColPosition.z);
									xVel+=colXNormal*0.05f;
									zVel+=colZNormal*0.05f;
								}
								else
								{
									setX(triColPosition.x+colXNormal*0.5f);
									setY(triColPosition.y+colYNormal*0.5f);
									setZ(triColPosition.z+colZNormal*0.5f);
									xVel = 0;
									zVel = 0;
									setRotY(getRotY()+180);
								}
							}
						}
						else
						{
							setRotY(getRotY()+180);
						}
					}
					else
					{
						if (inAir)
						{
							increasePosition(xVel, yVel, zVel);
						}
						else if (furyTimer > 0)
						{
							inAir = true;
							increasePosition(xVel, yVel, zVel);
						}
						//else //if we are about to walk off a ledge
						//{
							//turn around 180? doesnt work well
						//}
					}
				}
				else
				{
					inAir = false;
					triCol = CollisionChecker::getCollideTriangle();
					Vector3f* triColPosition = CollisionChecker::getCollidePosition();
				
					float colXNormal = triCol->normal.x;
					float colYNormal = triCol->normal.y;
					float colZNormal = triCol->normal.z;
				
					//yVel = 0;
				
					if(colYNormal >= 0.75f)
					{
						setX(triColPosition->x);
						setY(triColPosition->y+colYNormal*0.5f);
						setZ(triColPosition->z);
					}
					else
					{
						if(colYNormal >= 0.5f)
						{
							setX(triColPosition->x);
							setY(triColPosition->y+colYNormal*0.5f);
							setZ(triColPosition->z);
							xVel+=colXNormal*0.05f;
							zVel+=colZNormal*0.05f;
						}
						else
						{
							setX(triColPosition->x+colXNormal*0.5f);
							setY(triColPosition->y+colYNormal*0.5f);
							setZ(triColPosition->z+colZNormal*0.5f);
							xVel = 0;
							zVel = 0;
							setRotY(getRotY()+180);
						}
					}
				}
			}

			if (getY() < -50)
			{
				die();
			}
		
			float speed = sqrtf((xVel*xVel)+(zVel*zVel));
			float increaseValue = speed*9+1;
			//if (animIndex % 50 < 25 && (animIndex % 50)+increaseValue >= 25)
			{
				//AudioRes.playSound(28, 1+speed*0.1f, getPosition()); //goomba step
			}
		
			animIndex+=increaseValue;
			if (speed == 0)
			{
				animIndex = 25;
			}

			updateTransformationMatrix();
		}
	}
}

void RhinoTank::die()
{
	AudioPlayer::play(3, getPosition());

	Global::gamePlayer->increaseCombo();

	Main_deleteEntity(this);

	float height = 10.0f;
	float spread = 20.0f;

	for (int i = 7; i != 0; i--)
	{
		Vector3f pos(
			getX() + spread*(Maths::random() - 0.5f),
			getY() + spread*(Maths::random() - 0.5f) + height,
			getZ() + spread*(Maths::random() - 0.5f));

		Vector3f vel(0, 0, 0);

		new Particle(ParticleResources::textureExplosion1, &pos, &vel,
			0, 45, 0, 3 * Maths::random() + 6, 0, false);
	}

	Vector3f pos(
		getX(),
		getY() + height,
		getZ());

	Vector3f vel(0, 0, 0);
	
	new Particle(ParticleResources::textureExplosion2, &pos, &vel,
		0, 55, 0, 20, 0, false);

	Global::gameScore += 200;
}

void RhinoTank::moveMe()
{
	xVel += (0.7f*cosf(toRadians(-getRotY())));
	zVel += (0.7f*sinf(toRadians(-getRotY())));
}
	
void RhinoTank::moveMeSlow()
{
	xVel += (0.08f*cosf(toRadians(-getRotY())));
	zVel += (0.08f*sinf(toRadians(-getRotY())));
}
	
void RhinoTank::applyFriction(float frictionToApply)
{
	xVel = xVel/frictionToApply;
	zVel = zVel/frictionToApply;
}
	

std::list<TexturedModel*>* RhinoTank::getModels()
{
	return &RhinoTank::models;
}

void RhinoTank::loadStaticModels()
{
	if (RhinoTank::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading RhinoTank static models...\n");
	#endif

	loadObjModel(&RhinoTank::models,   "res/Models/RhinoTank/", "RhinoTank.obj");
}

void RhinoTank::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting RhinoTank static models...\n");
	#endif

	Entity::deleteModels(&RhinoTank::models);
}

bool RhinoTank::canHomingAttackOn()
{
	return true;
}

Vector3f RhinoTank::getHomingCenter()
{
	return Vector3f(getX(), getY()+7, getZ());
}

bool RhinoTank::isEnemy()
{
	return true;
}