#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "bmetalsonic.h"
#include "../../collision/collisionchecker.h"
#include "../../particles/particle.h"
#include "../../particles/particleresources.h"
#include "../../animation/body.h"
#include "../../animation/limb.h"
#include "../../animation/animationresources.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../controllableplayer.h"
#include "../../audio/audioplayer.h"
#include "../../audio/source.h"
#include "bprojectile.h"
#include "../../guis/guimanager.h"

#include <list>
#include <vector>
#include <iostream>

std::list<TexturedModel*> B_MetalSonic::modelBody;
std::list<TexturedModel*> B_MetalSonic::modelHead;
std::list<TexturedModel*> B_MetalSonic::modelLeftHumerus;
std::list<TexturedModel*> B_MetalSonic::modelLeftForearm;
std::list<TexturedModel*> B_MetalSonic::modelLeftHand;
std::list<TexturedModel*> B_MetalSonic::modelLeftThigh;
std::list<TexturedModel*> B_MetalSonic::modelLeftShin;
std::list<TexturedModel*> B_MetalSonic::modelLeftFoot;
std::list<TexturedModel*> B_MetalSonic::modelRightHumerus;
std::list<TexturedModel*> B_MetalSonic::modelRightForearm;
std::list<TexturedModel*> B_MetalSonic::modelRightHand;
std::list<TexturedModel*> B_MetalSonic::modelRightThigh;
std::list<TexturedModel*> B_MetalSonic::modelRightShin;
std::list<TexturedModel*> B_MetalSonic::modelRightFoot;

std::vector<Vector3f> B_MetalSonic::splineIntro;

B_MetalSonic::B_MetalSonic()
{
	position.x = 0;
	position.y = 2040;
	position.z = 0;
	xVel = 0;
	yVel = 0;
	zVel = 0;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scale = 1;
	visible = false;

	timer = 0;
	splineTimer = 0;
	iFrames = 0;
	hitTimer = 0;
	shouldFollowSpline = true;
	isTeleporting = false;
	teleportingTimer = 0;
	chargeTimer = 0;
	aheadOfSonicTimer = 0;
	shootTimer = 0;
	spinTimer = 0;
	behindSonicTimer = 0;
	mySource = nullptr;
	health = 5;
	deathTimer = 0;

	createLimbs();
	setLimbsVisibility(true);
}

void B_MetalSonic::step()
{
	timer++;

	iFrames          = std::max(iFrames         -1, 0);
	hitTimer         = std::max(hitTimer        -1, 0);
	teleportingTimer = std::max(teleportingTimer-1, 0);
	chargeTimer      = std::max(chargeTimer     -1, 0);
	shootTimer       = std::max(shootTimer      -1, 0);
	spinTimer        = std::max(spinTimer       -1, 0);

	if (teleportingTimer == 0)
	{
		isTeleporting = false;
	}

	if (shouldFollowSpline)
	{
		splineTimer+=0.105f;

		int indexBack = ((int)splineTimer)     % B_MetalSonic::splineIntro.size();
		int indexFwrd = (((int)splineTimer)+1) % B_MetalSonic::splineIntro.size();

		if (indexFwrd == 0)
		{
			shouldFollowSpline = false;
			xVel = 5.0f;
			position.z = 0;
		}
		else
		{
			Vector3f posBack = B_MetalSonic::splineIntro[indexBack];
			Vector3f posFwrd = B_MetalSonic::splineIntro[indexFwrd];

			float splitTimerMod = fmodf(splineTimer, 1);
			Vector3f diff = posFwrd - posBack;

			rotY = toDegrees(atan2f(-diff.z, diff.x));

			diff.scale(splitTimerMod);

			diff = diff+posBack;

			setPosition(&diff);
		}
	}
	else if (health > 0)
	{
		position.y = 2006;

		Vector3f playPos = Global::gamePlayer->getCenterPosition();

		float xDiff = getX() - playPos.x;
		float yDiff = getY() - playPos.y;
		float zDiff = getZ() - playPos.z;

		float diffSquared = xDiff*xDiff + yDiff*yDiff + zDiff*zDiff;

		if (xDiff < -200 || !CollisionChecker::checkCollision(getX(), getY(), getZ(), getX(), getY()-5, getZ()))
		{
			if (!isTeleporting)
			{
				isTeleporting = true;
				teleportingTimer = 300;
			}
		}

		if (!isTeleporting)
		{
			if (chargeTimer == 0)
			{
				if (xDiff < 100)
				{
					if (hitTimer == 0)
					{
						xVel += 0.1f;
					}
				}

				if (xDiff > 300 && shootTimer == 0)
				{
					shootTimer = 360;
				}

				if (behindSonicTimer > 60)
				{
					spinTimer = 100;
				}
			}
			else
			{
				if (xDiff < 40)
				{
					if (hitTimer == 0)
					{
						xVel += 0.1f;
					}
				}
			}

			if (xDiff > 0)
			{
				aheadOfSonicTimer++;
				behindSonicTimer = 0;
			}
			else
			{
				aheadOfSonicTimer = 0;
				behindSonicTimer++;
			}
		}

		if (teleportingTimer != 0)
		{
			shootTimer = 0;
			chargeTimer = 0;
			aheadOfSonicTimer = 0;
			spinTimer = 0;

			xVel = 0;

			position.z = 0;
			position.y = 2010;
			position.x = playPos.x + 150;

			int count = 8;

			while (count != 0)
			{
				Vector3f off = randomPointOnSphere();

				off.scale(4);
				Vector3f pos(position.x+off.x, position.y+off.y, position.z+off.z);
				off.scale(1/4.0f);
				new Particle(ParticleResources::textureSparkleYellow, &pos, &off,
						0, 5, 0, 3, -(3.0f / 5.0f), false);

				off.scale(-4);
				pos.set(position.x+off.x, position.y+off.y, position.z+off.z);
				off.scale(1/4.0f);
				new Particle(ParticleResources::textureSparkleWhite, &pos, &off,
						0, 5, 0, 3, -(3.0f / 5.0f), false);

				count--;
			}
		}

		if (teleportingTimer == 1)
		{
			xVel = Global::gamePlayer->getXVelGround() + Global::gamePlayer->getXVelAir();
			xVel +=1;
		}

		if (aheadOfSonicTimer % 360 == 359 && chargeTimer == 0)
		{
			chargeTimer = 240;
		}

		if (chargeTimer > 1)
		{
			shootTimer = 0;
			spinTimer = 0;
			
			int count = 24;

			while (count != 0)
			{
				Vector3f off = randomPointOnSphere();

				off.scale(16);
				Vector3f pos(position.x+off.x, position.y+off.y, position.z+off.z);
				off.scale(-1/16.0f);
				new Particle(ParticleResources::textureSparkleYellow, &pos, &off,
						0, 5, 0, 3, -(3.0f / 5.0f), false);

				off.scale(16);
				pos.set(position.x+off.x, position.y+off.y, position.z+off.z);
				off.scale(-1/16.0f);
				new Particle(ParticleResources::textureSparkleWhite, &pos, &off,
						0, 5, 0, 3, -(3.0f / 5.0f), false);

				count--;
			}
		}
		else if (chargeTimer == 1)
		{
			AudioPlayer::play(47, getPosition());
			aheadOfSonicTimer = 0;

			int count = 48;

			while (count != 0)
			{
				Vector3f off = randomPointOnSphere();

				off.scale(6);
				Vector3f pos(position.x+off.x, position.y+off.y, position.z+off.z);
				//off.scale(1/4.0f);
				new Particle(ParticleResources::textureSparkleYellow, &pos, &off,
						0, 35, 0, 16, -(16.0f / 30.0f), false);

				off.scale(-1);
				pos.set(position.x+off.x, position.y+off.y, position.z+off.z);
				//off.scale(1/4.0f);
				new Particle(ParticleResources::textureSparkleWhite, &pos, &off,
						0, 35, 0, 16, -(16.0f / 30.0f), false);

				count--;
			}

			if (diffSquared < 6400) //80*80
			{
				Global::gamePlayer->takeDamage(getPosition());
			}
		}

		if (hitTimer != 0)
		{
			shootTimer = 0;
			spinTimer = 0;
		}

		if (shootTimer > 300)
		{
			if (shootTimer % 5 == 0)
			{
				AudioPlayer::play(52, getPosition());
			}

			float spoutSpd = 3.0f;
			float anglH = (float)(M_PI * 2 * ((rand() % 1024) / 1024.0));
			float randNumber = Maths::nextGaussian();

			float anglV = (toRadians((randNumber * 80 + 90)));

			float yspd = spoutSpd*sinf(anglV);
			float hpt  = spoutSpd*cosf(anglV);

			float xspd = hpt*cosf(anglH);
			float zspd = hpt*sinf(anglH);

			B_Projectile* newProj = new B_Projectile(getX(), getY() + 10, getZ(), xspd, yspd, zspd); INCR_NEW
			Main_addEntity(newProj);
		}

		if (diffSquared < 81) //9*9
		{
			if (spinTimer != 0)
			{
				Global::gamePlayer->takeDamage(getPosition());
			}
			else if (iFrames == 0)
			{
				if (Global::gamePlayer->isVulnerable())
				{
					Global::gamePlayer->takeDamage(getPosition());
				}
				else
				{
					int ra = (int)(3*Maths::random());
					ra*=2;
					AudioPlayer::play(46+ra, getPosition()); //46, 48, or 50

					health--;

					iFrames  = 180;
					hitTimer = 100;
					chargeTimer = 0;
					shootTimer = 0;
					aheadOfSonicTimer = 0;

					xVel = Global::gamePlayer->getXVelGround() + Global::gamePlayer->getXVelAir();
					xVel +=3;
					//zVel = 0;

					Global::gamePlayer->rebound(getPosition());
					Global::gamePlayer->setGroundSpeed(Global::gamePlayer->getXVelGround()*0.5f, Global::gamePlayer->getZVelGround()*0.5f);
				}
			}
		}

		if (mySource == nullptr)
		{
			if (teleportingTimer != 0)
			{
				mySource = AudioPlayer::play(49, getPosition(), 1,true);
			}
			else if (spinTimer != 0)
			{
				mySource = AudioPlayer::play(51, getPosition(), 1,true);
			}
			else if (chargeTimer != 0)
			{
				mySource = AudioPlayer::play(53, getPosition(), 1,true);
			}
		}

		if (mySource != nullptr)
		{
			if (mySource->isPlaying() == false)
			{
				mySource = nullptr;
			}
			else if (teleportingTimer == 0 && mySource->getLastPlayedBufferID() == AudioPlayer::getSEBuffer(49))
			{
				mySource->stop();
				mySource = nullptr;
			}
			else if (spinTimer == 0 && mySource->getLastPlayedBufferID() == AudioPlayer::getSEBuffer(51))
			{
				mySource->stop();
				mySource = nullptr;
			}
			else if (chargeTimer == 0 && mySource->getLastPlayedBufferID() == AudioPlayer::getSEBuffer(53))
			{
				mySource->stop();
				mySource = nullptr;
			}
			else
			{
				mySource->setPosition(position.x, position.y, position.z);
			}
		}

		xVel = xVel*0.99f;
		zVel = zVel*0.99f;
	}
	else
	{
		deathTimer++;

		xVel = xVel*0.99f;
		zVel = zVel*0.99f;

		float mySpeed = xVel*xVel + zVel*zVel;

		if (deathTimer == 1)
		{
			if (mySource != nullptr && mySource->isPlaying())
			{
				mySource->stop();
				mySource = nullptr;
			}
		}

		if (deathTimer % 10 == 1 && mySpeed > 1.0f)
		{
			int ran = (int)(3*Maths::random());
			ran*=2;
			AudioPlayer::play(46+ran, getPosition()); //46, 48, or 50

			float height = 5.0f;
			float spread = 25.0f;

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
		}

		if (mySpeed < 0.75f)
		{
			xVel = xVel*0.9f;
			zVel = zVel*0.9f;
		}

		if (mySpeed < 0.05f && Global::finishStageTimer == -1)
		{
			GuiManager::stopTimer();
			Global::finishStageTimer = 0;
		}

		if (Global::finishStageTimer > 60)
		{
			setPosition(-885, 2006, 10);
		}
	}

	increasePosition(xVel, yVel, zVel);

	animate();
}

void B_MetalSonic::animate()
{
	if (iFrames % 4 == 0)
	{
		setLimbsVisibility(true);	
	}
	else if (iFrames % 4 == 2)
	{
		setLimbsVisibility(false);
	}

	if (shouldFollowSpline)
	{
		myBody->setBaseOrientation(&position, 0, getRotY(), 90, 0);
		updateLimbs(24, (float)((timer*5)%100));
	}
	else if (deathTimer != 0)
	{
		float mySpeed = xVel*xVel + zVel*zVel;
		rotY = toDegrees(atan2f(-zVel, xVel));

		if (mySpeed < 2.0f)
		{
			myBody->setBaseOrientation(&position, 0, getRotY(), 0, 0);
			updateLimbs(19, 0);
		}
		else
		{
			myBody->setBaseOrientation(&position, 0, getRotY(), 90, 0);
			updateLimbs(24, (float)((timer*2)%100));
		}
	}
	else if (isTeleporting)
	{
		setLimbsVisibility(false);
	}
	else if (hitTimer > 0)
	{
		Vector3f upPos(getX(), getY()+1, getZ());
		myBody->setBaseOrientation(&upPos, 0, getRotY(), 90, 0);
		updateLimbs(11, 0);
	}
	else if (chargeTimer > 0)
	{
		rotY = toDegrees(atan2f(-zVel, xVel));

		Vector3f upPos(getX(), getY()+2, getZ());
		myBody->setBaseOrientation(&upPos, 0, getRotY(), 90, 0);
		updateLimbs(12, 0);
	}
	else if (spinTimer > 0)
	{
		Vector3f upPos(getX(), getY()+5, getZ());
		myBody->setBaseOrientation(&upPos, timer*40.0f, getRotY(), 0, 0);
		updateLimbs(20, 0);
	}
	else if (shootTimer > 300)
	{
		rotY = toDegrees(atan2f(-zVel, xVel));

		myBody->setBaseOrientation(&position, 0, getRotY(), 90, 0);
		updateLimbs(17, 0);
	}
	else
	{
		float mySpeed = xVel*xVel + zVel*zVel;
		rotY = toDegrees(atan2f(-zVel, xVel));

		myBody->setBaseOrientation(&position, 0, getRotY(), 90, 0);
		if (mySpeed > 4.0f) //2 * 2
		{
			updateLimbs(24, (float)((timer*5)%100));
		}
		else if (mySpeed > 0.5f)
		{
			updateLimbs(1, (float)((timer*2)%100));
		}
		else
		{
			updateLimbs(0, (float)(timer%100));
		}
	}

	updateLimbsMatrix();
}

std::list<TexturedModel*>* B_MetalSonic::getModels()
{
	return nullptr;
}

void B_MetalSonic::loadStaticModels()
{
	if (B_MetalSonic::splineIntro.size() == 0)
	{
		B_MetalSonic::splineIntro.push_back(Vector3f(100.6817020f, -169.486145f+2000,  695.042847f));
		B_MetalSonic::splineIntro.push_back(Vector3f(200.2285160f, -150.560608f+2000,  686.647888f));
		B_MetalSonic::splineIntro.push_back(Vector3f(350.8870540f, -129.845917f+2000,  671.158447f));
		B_MetalSonic::splineIntro.push_back(Vector3f(500.6474300f, -108.024887f+2000,  649.853577f));
		B_MetalSonic::splineIntro.push_back(Vector3f(602.4998170f, -85.7803270f+2000,  624.012329f));
		B_MetalSonic::splineIntro.push_back(Vector3f(705.4342650f, -63.7950670f+2000,  594.913757f));
		B_MetalSonic::splineIntro.push_back(Vector3f(807.4409180f, -42.7519230f+2000,  563.836975f));
		B_MetalSonic::splineIntro.push_back(Vector3f(902.5098270f, -23.3337060f+2000,  532.060974f));
		B_MetalSonic::splineIntro.push_back(Vector3f(984.6311650f, -6.22324000f+2000,  500.864899f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1047.795044f,  7.89666000f+2000,  471.527771f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1085.991699f,  18.3431590f+2000,  445.328674f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1110.636475f,  22.8861710f+2000,  419.519775f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1152.489014f,  26.3216480f+2000,  374.791473f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1207.095581f,  28.7978150f+2000,  315.612274f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1270.002319f,  30.4629060f+2000,  246.450699f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1336.755493f,  31.4651470f+2000,  171.775223f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1402.901367f,  31.9527680f+2000,  96.0543820f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1463.986206f,  32.0740010f+2000,  23.7566890f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1515.556274f,  31.9770740f+2000, -40.6493450f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1553.157715f,  31.8102150f+2000, -92.6952130f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1572.336792f,  31.7216550f+2000, -127.912445f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1582.528076f,  30.2343370f+2000, -153.313629f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1598.637085f,  26.2401640f+2000, -187.414673f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1619.337769f,  20.4408110f+2000, -227.846756f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1643.303955f,  13.5379510f+2000, -272.241058f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1669.209595f,  6.23325700f+2000, -318.228760f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1695.728516f, -0.77159400f+2000, -363.441010f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1721.534546f, -6.77493000f+2000, -405.509033f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1745.301636f, -11.0750770f+2000, -442.063995f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1765.703613f, -12.9703600f+2000, -470.737061f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1781.414307f, -11.7591000f+2000, -489.159363f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1794.862061f, -8.71651600f+2000, -497.832581f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1815.419189f, -4.08620800f+2000, -505.852448f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1841.225830f,  1.84032400f+2000, -513.143860f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1870.421997f,  8.77158000f+2000, -519.631592f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1901.147827f,  16.4160540f+2000, -525.240601f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1931.543335f,  24.4822460f+2000, -529.895691f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1959.748657f,  32.6786580f+2000, -533.521729f));
		B_MetalSonic::splineIntro.push_back(Vector3f(1983.903931f,  40.7137760f+2000, -536.043518f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2002.149170f,  48.2961120f+2000, -537.385986f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2012.624756f,  55.1341550f+2000, -537.473938f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2028.988159f,  65.2324370f+2000, -526.017334f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2054.198975f,  71.7020030f+2000, -496.617004f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2086.315186f,  74.9421540f+2000, -453.525085f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2123.394775f,  75.3522030f+2000, -400.993744f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2163.495850f,  73.3314670f+2000, -343.275146f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2204.676758f,  69.2792590f+2000, -284.621460f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2244.995361f,  63.5948790f+2000, -229.284821f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2282.509766f,  56.6776500f+2000, -181.517426f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2315.278076f,  48.9268880f+2000, -145.571426f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2341.357666f,  40.7419050f+2000, -125.699005f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2363.396729f,  35.6017190f+2000, -116.850464f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2399.878418f,  30.4834020f+2000, -104.008873f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2447.300781f,  25.5104100f+2000, -88.4158860f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2502.161377f,  20.8061980f+2000, -71.3131410f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2560.958008f,  16.4942260f+2000, -53.9422950f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2620.188477f,  12.6979480f+2000, -37.5449940f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2676.350586f,  9.54082300f+2000, -23.3628900f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2755.941895f,  7.14630700f+2000, -12.2376260f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2800.460205f,  5.63785600f+2000, -5.01085200f));
		B_MetalSonic::splineIntro.push_back(Vector3f(2845.403076f,  5.13892700f+2000,  0.00000000f));
	}

	if (B_MetalSonic::modelBody.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading B_MetalSonic static models...\n");

	loadObjModel(&B_MetalSonic::modelBody,         "res/Models/MetalSonic/", "Body.obj");
	loadObjModel(&B_MetalSonic::modelHead,         "res/Models/MetalSonic/", "Head.obj");
	loadObjModel(&B_MetalSonic::modelLeftHumerus,  "res/Models/MetalSonic/", "Humerus.obj");
	loadObjModel(&B_MetalSonic::modelLeftForearm,  "res/Models/MetalSonic/", "Forearm.obj");
	loadObjModel(&B_MetalSonic::modelLeftHand,     "res/Models/MetalSonic/", "HandLeft.obj");
	loadObjModel(&B_MetalSonic::modelLeftThigh,    "res/Models/MetalSonic/", "Humerus.obj");
	loadObjModel(&B_MetalSonic::modelLeftShin,     "res/Models/MetalSonic/", "Forearm.obj");
	loadObjModel(&B_MetalSonic::modelLeftFoot,     "res/Models/MetalSonic/", "Shoe.obj");
	loadObjModel(&B_MetalSonic::modelRightHumerus, "res/Models/MetalSonic/", "Humerus.obj");
	loadObjModel(&B_MetalSonic::modelRightForearm, "res/Models/MetalSonic/", "Forearm.obj");
	loadObjModel(&B_MetalSonic::modelRightHand,    "res/Models/MetalSonic/", "HandRight.obj");
	loadObjModel(&B_MetalSonic::modelRightThigh,   "res/Models/MetalSonic/", "Humerus.obj");
	loadObjModel(&B_MetalSonic::modelRightShin,    "res/Models/MetalSonic/", "Forearm.obj");
	loadObjModel(&B_MetalSonic::modelRightFoot,    "res/Models/MetalSonic/", "Shoe.obj");
}

void B_MetalSonic::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting B_MetalSonic static models...\n");

	Entity::deleteModels(&B_MetalSonic::modelBody);
	Entity::deleteModels(&B_MetalSonic::modelHead);
	Entity::deleteModels(&B_MetalSonic::modelLeftHumerus);
	Entity::deleteModels(&B_MetalSonic::modelLeftForearm);
	Entity::deleteModels(&B_MetalSonic::modelLeftHand);
	Entity::deleteModels(&B_MetalSonic::modelLeftThigh);
	Entity::deleteModels(&B_MetalSonic::modelLeftShin);
	Entity::deleteModels(&B_MetalSonic::modelLeftFoot);
	Entity::deleteModels(&B_MetalSonic::modelRightHumerus);
	Entity::deleteModels(&B_MetalSonic::modelRightForearm);
	Entity::deleteModels(&B_MetalSonic::modelRightHand);
	Entity::deleteModels(&B_MetalSonic::modelRightThigh);
	Entity::deleteModels(&B_MetalSonic::modelRightShin);
	Entity::deleteModels(&B_MetalSonic::modelRightFoot);
}


void B_MetalSonic::createLimbs()
{
	//displayHeightOffset = 0.1f;

	const float s = 1.1f;

	myBody =         new Body(&modelBody);
	myHead =         new Limb(&modelHead,        s* 1.2f, s* -0.3f, s*  0,     myBody,   nullptr);        INCR_NEW
	myLeftHumerus =  new Limb(&modelLeftHumerus, s* 0.9f, s*  0,    s* -0.9f,  myBody,   nullptr);        INCR_NEW
	myLeftForearm =  new Limb(&modelLeftForearm, s* 0,    s* -1.3f, s*  0,     nullptr,  myLeftHumerus);  INCR_NEW
	myLeftHand =     new Limb(&modelLeftHand,    s* 0,	  s* -1.3f, s*  0,     nullptr,  myLeftForearm);  INCR_NEW
	myLeftThigh =    new Limb(&modelLeftThigh,   s*-0.9f, s*  0,    s* -0.3f,  myBody,   nullptr);        INCR_NEW
	myLeftShin =     new Limb(&modelLeftShin,    s* 0,	  s* -1.3f, s*  0,     nullptr,  myLeftThigh);    INCR_NEW
	myLeftFoot =     new Limb(&modelLeftFoot,    s* 0,	  s* -1.4f, s*  0,     nullptr,  myLeftShin);     INCR_NEW
	myRightHumerus = new Limb(&modelRightHumerus,s* 0.9f, s*  0,    s*  0.9f,  myBody,   nullptr);        INCR_NEW
	myRightForearm = new Limb(&modelRightForearm,s* 0,	  s* -1.3f, s*  0,     nullptr,  myRightHumerus); INCR_NEW
	myRightHand =    new Limb(&modelRightHand,   s* 0,	  s* -1.3f, s*  0,     nullptr,  myRightForearm); INCR_NEW
	myRightThigh =   new Limb(&modelRightThigh,  s*-0.9f, s*  0,    s*  0.3f,  myBody,   nullptr);        INCR_NEW
	myRightShin =    new Limb(&modelRightShin,   s* 0,	  s* -1.3f, s*  0,     nullptr,  myRightThigh);   INCR_NEW
	myRightFoot =    new Limb(&modelRightFoot,   s* 0,	  s* -1.4f, s*  0,     nullptr,  myRightShin);    INCR_NEW

	myBody        ->setScale(s);
	myHead        ->setScale(s);
	myLeftHumerus ->setScale(s);
	myLeftForearm ->setScale(s);
	myLeftHand    ->setScale(s);
	myLeftThigh   ->setScale(s);
	myLeftShin    ->setScale(s);
	myLeftFoot    ->setScale(s);
	myRightHumerus->setScale(s);
	myRightForearm->setScale(s);
	myRightHand   ->setScale(s);
	myRightThigh  ->setScale(s);
	myRightShin   ->setScale(s);
	myRightFoot   ->setScale(s);

	AnimationResources::assignAnimationsHuman(myBody, myHead,
		myLeftHumerus, myLeftForearm, myLeftHand,
		myRightHumerus, myRightForearm, myRightHand,
		myLeftThigh, myLeftShin, myLeftFoot,
		myRightThigh, myRightShin, myRightFoot);

	addLimbsToGame();
}

void B_MetalSonic::addLimbsToGame()
{
	Main_addEntity(myBody);
	Main_addEntity(myHead);
	Main_addEntity(myLeftHumerus);
	Main_addEntity(myLeftForearm);
	Main_addEntity(myLeftHand);
	Main_addEntity(myLeftThigh);
	Main_addEntity(myLeftShin);
	Main_addEntity(myLeftFoot);
	Main_addEntity(myRightHumerus);
	Main_addEntity(myRightForearm);
	Main_addEntity(myRightHand);
	Main_addEntity(myRightThigh);
	Main_addEntity(myRightShin);
	Main_addEntity(myRightFoot);
}

void B_MetalSonic::removeLimbsFromGame()
{
	Main_deleteEntity(myBody);         myBody         = nullptr;
	Main_deleteEntity(myHead);         myHead         = nullptr;
	Main_deleteEntity(myLeftHumerus);  myLeftHumerus  = nullptr;
	Main_deleteEntity(myLeftForearm);  myLeftForearm  = nullptr;
	Main_deleteEntity(myLeftHand);     myLeftHand     = nullptr;
	Main_deleteEntity(myLeftThigh);    myLeftThigh    = nullptr;
	Main_deleteEntity(myLeftShin);     myLeftShin     = nullptr;
	Main_deleteEntity(myLeftFoot);     myLeftFoot     = nullptr;
	Main_deleteEntity(myRightHumerus); myRightHumerus = nullptr;
	Main_deleteEntity(myRightForearm); myRightForearm = nullptr;
	Main_deleteEntity(myRightHand);    myRightHand    = nullptr;
	Main_deleteEntity(myRightThigh);   myRightThigh   = nullptr;
	Main_deleteEntity(myRightShin);    myRightShin    = nullptr;
	Main_deleteEntity(myRightFoot);    myRightFoot    = nullptr;
}

void B_MetalSonic::setLimbsVisibility(bool newVisible)
{
	myBody        ->setVisible(newVisible);
	myHead        ->setVisible(newVisible);
	myLeftHumerus ->setVisible(newVisible);
	myLeftForearm ->setVisible(newVisible);
	myLeftHand    ->setVisible(newVisible);
	myLeftThigh   ->setVisible(newVisible);
	myLeftShin    ->setVisible(newVisible);
	myLeftFoot    ->setVisible(newVisible);
	myRightHumerus->setVisible(newVisible);
	myRightForearm->setVisible(newVisible);
	myRightHand   ->setVisible(newVisible);
	myRightThigh  ->setVisible(newVisible);
	myRightShin   ->setVisible(newVisible);
	myRightFoot   ->setVisible(newVisible);
}

void B_MetalSonic::updateLimbs(int animIndex, float time)
{
	myBody        ->animationIndex = animIndex;
	myHead        ->animationIndex = animIndex;
	myLeftHumerus ->animationIndex = animIndex;
	myLeftForearm ->animationIndex = animIndex;
	myLeftHand    ->animationIndex = animIndex;
	myLeftThigh   ->animationIndex = animIndex;
	myLeftShin    ->animationIndex = animIndex;
	myLeftFoot    ->animationIndex = animIndex;
	myRightHumerus->animationIndex = animIndex;
	myRightForearm->animationIndex = animIndex;
	myRightHand   ->animationIndex = animIndex;
	myRightThigh  ->animationIndex = animIndex;
	myRightShin   ->animationIndex = animIndex;
	myRightFoot   ->animationIndex = animIndex;
	myBody        ->update(time);
	myHead        ->update(time);
	myLeftHumerus ->update(time);
	myLeftForearm ->update(time);
	myLeftHand    ->update(time);
	myLeftThigh   ->update(time);
	myLeftShin    ->update(time);
	myLeftFoot    ->update(time);
	myRightHumerus->update(time);
	myRightForearm->update(time);
	myRightHand   ->update(time);
	myRightThigh  ->update(time);
	myRightShin   ->update(time);
	myRightFoot   ->update(time);
}

void B_MetalSonic::updateLimbsMatrix()
{
	myBody        ->updateTransformationMatrix();
	myHead        ->updateTransformationMatrix();
	myLeftHumerus ->updateTransformationMatrix();
	myLeftForearm ->updateTransformationMatrix();
	myLeftHand    ->updateTransformationMatrix();
	myLeftThigh   ->updateTransformationMatrix();
	myLeftShin    ->updateTransformationMatrix();
	myLeftFoot    ->updateTransformationMatrix();
	myRightHumerus->updateTransformationMatrix();
	myRightForearm->updateTransformationMatrix();
	myRightHand   ->updateTransformationMatrix();
	myRightThigh  ->updateTransformationMatrix();
	myRightShin   ->updateTransformationMatrix();
	myRightFoot   ->updateTransformationMatrix();
}

bool B_MetalSonic::canHomingAttackOn()
{
	return true;
}

Vector3f B_MetalSonic::getHomingCenter()
{
	return Vector3f(position.x+xVel, position.y+2, position.z);
}