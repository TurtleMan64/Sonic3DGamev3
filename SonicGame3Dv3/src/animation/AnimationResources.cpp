#include "animationresources.h"
#include "animation.h"
#include "body.h"
#include "limb.h"

std::vector<Animation> AnimationResources::animsHumanBody;
std::vector<Animation> AnimationResources::animsHumanHead;
std::vector<Animation> AnimationResources::animsHumanLeftHumerus;
std::vector<Animation> AnimationResources::animsHumanLeftForearm;
std::vector<Animation> AnimationResources::animsHumanLeftHand;
std::vector<Animation> AnimationResources::animsHumanRightHumerus;
std::vector<Animation> AnimationResources::animsHumanRightForearm;
std::vector<Animation> AnimationResources::animsHumanRightHand;
std::vector<Animation> AnimationResources::animsHumanLeftThigh;
std::vector<Animation> AnimationResources::animsHumanLeftShin;
std::vector<Animation> AnimationResources::animsHumanLeftFoot;
std::vector<Animation> AnimationResources::animsHumanRightThigh;
std::vector<Animation> AnimationResources::animsHumanRightShin;
std::vector<Animation> AnimationResources::animsHumanRightFoot;


void AnimationResources::createAnimations()
{
	unsigned int animCount = 18;
	while (animsHumanBody.size() < animCount) { Animation filler; animsHumanBody.push_back(filler); }
	while (animsHumanHead.size() < animCount) { Animation filler; animsHumanHead.push_back(filler); }
	while (animsHumanLeftHumerus.size() < animCount) { Animation filler; animsHumanLeftHumerus.push_back(filler); }
	while (animsHumanLeftForearm.size() < animCount) { Animation filler; animsHumanLeftForearm.push_back(filler); }
	while (animsHumanLeftHand.size() < animCount) { Animation filler; animsHumanLeftHand.push_back(filler); }
	while (animsHumanRightHumerus.size() < animCount) { Animation filler; animsHumanRightHumerus.push_back(filler); }
	while (animsHumanRightForearm.size() < animCount) { Animation filler; animsHumanRightForearm.push_back(filler); }
	while (animsHumanRightHand.size() < animCount) { Animation filler; animsHumanRightHand.push_back(filler); }
	while (animsHumanLeftThigh.size() < animCount) { Animation filler; animsHumanLeftThigh.push_back(filler); }
	while (animsHumanLeftShin.size() < animCount) { Animation filler; animsHumanLeftShin.push_back(filler); }
	while (animsHumanLeftFoot.size() < animCount) { Animation filler; animsHumanLeftFoot.push_back(filler); }
	while (animsHumanRightThigh.size() < animCount) { Animation filler; animsHumanRightThigh.push_back(filler); }
	while (animsHumanRightShin.size() < animCount) { Animation filler; animsHumanRightShin.push_back(filler); }
	while (animsHumanRightFoot.size() < animCount) { Animation filler; animsHumanRightFoot.push_back(filler); }


	//stand animation
	animsHumanBody[0].addKeyframe(0, 0, 3.35f, 0, 0, 0, 0, 1);
	animsHumanBody[0].addKeyframe(50, 0, 3.7f, 0, 0, 0, 0, 1);
	animsHumanBody[0].addKeyframe(100, 0, 3.35f, 0, 0, 0, 0, 1);

	//run animation
	animsHumanBody[1].addKeyframe(0, 1, 3.7f, 0, 0, 0, -15, 1);
	animsHumanBody[1].addKeyframe(25, 0, 3.3f, 0, 0, 10, -15, 1);
	animsHumanBody[1].addKeyframe(50, 1, 3.7f, 0, 0, 0, -15, 1);
	animsHumanBody[1].addKeyframe(75, 0, 3.3f, 0, 0, -10, -15, 1);
	animsHumanBody[1].addKeyframe(100, 1, 3.7f, 0, 0, 0, -15, 1);

	//jump animation
	animsHumanBody[2].addKeyframe(0, 0, 3.7f, 0, 0, 0, 0, 1);
	animsHumanBody[2].addKeyframe(100, 0, 3.7f, 0, 0, 45, 0, 1);

	//double jump , now a stomp at time == 100
	animsHumanBody[3].addKeyframe(0, 0, 3.7f, 0, 0, 0, 0, 1);
	animsHumanBody[3].addKeyframe(100, 0, 3.7f, 0, 0, 0, 0, 1);

	//triple jump animation
	animsHumanBody[4].addKeyframe(0, 0, 3.7f, 0, 0, 0, 0, 1);
	animsHumanBody[4].addKeyframe(100, 0, 3.7f, 0, 0, 0, -720, 1);

	//side flip animation
	animsHumanBody[5].addKeyframe(0, 0, 3.7f, 0, 0, 0, 0, 1);
	animsHumanBody[5].addKeyframe(100, 0, 3.7f, 0, 0, 0, -360, 1);

	//dive animation
	animsHumanBody[6].addKeyframe(0, 0, 0.0f, 0, 0, 0, 0, 1);
	animsHumanBody[6].addKeyframe(100, 0, 0.0f, 0, 0, 0, 0, 1);

	//rollout animation
	animsHumanBody[7].addKeyframe(0, 0, 0.0f, 0, 0, 0, 45, 1);
	animsHumanBody[7].addKeyframe(100, 0, 0.0f, 0, 0, 0, 45, 1);

	//skid animation
	animsHumanBody[8].addKeyframe(0, 0, 3.7f, 0, 0, 0, 0, 1);
	animsHumanBody[8].addKeyframe(100, 0, 3.0f, 0, 0, 0, 0, 1);

	//ground pound animation
	animsHumanBody[9].addKeyframe(0, 0, 1.0f, 0, 0, 0, 0, 1);//3.7
	animsHumanBody[9].addKeyframe(100, 0, 1.0f, 0, 0, 0, 0, 1);//3.7

	//long jump animation
	animsHumanBody[10].addKeyframe(0, 0, 3.7f, 0, 0, 0, 0, 1);
	animsHumanBody[10].addKeyframe(100, 0, 3.7f, 0, 0, 0, 0, 1);

	//long jump animation
	animsHumanBody[11].addKeyframe(0, 0, 1.0f, 0, 0, 180, 0, 1);
	animsHumanBody[11].addKeyframe(100, 0, 1.0f, 0, 0, 180, 0, 1);

	//crouch animation
	animsHumanBody[12].addKeyframe(0, 0, 2.0f, 0, 0, 0, -30, 1);
	animsHumanBody[12].addKeyframe(100, 0, 2.0f, 0, 0, 0, -30, 1);

	//high jump animation
	animsHumanBody[13].addKeyframe(0, 0, 2.0f, 0, 0, 0, 0, 1);
	animsHumanBody[13].addKeyframe(100, 0, 2.0f, 0, 0, 0, 0, 1);

	//pose animation
	animsHumanBody[14].addKeyframe(0, 0, 3.0f, 0, 15, 0, 0, 1);
	animsHumanBody[14].addKeyframe(100, 0, 3.0f, 0, 15, 0, 0, 1);

	//swim animation
	animsHumanBody[15].addKeyframe(0, 0, 0.0f, 0, 0, 0, -90, 1);
	animsHumanBody[15].addKeyframe(100, 0, 0.0f, 0, 0, 0, -90, 1);

	//swim stroke animation
	animsHumanBody[16].addKeyframe(0, 0, 0.0f, 0, 0, 0, -90, 1);
	animsHumanBody[16].addKeyframe(100, 0, 0.0f, 0, 0, 0, -90, 1);

	//t pose animation
	animsHumanBody[17].addKeyframe(0, 0, 4.0f, 0, 0, 0, 0, 1);
	animsHumanBody[17].addKeyframe(100, 0, 4.0f, 0, 0, 0, 0, 1);



	animsHumanHead[0].addKeyframe(0, 0, 0, 0, 1);
	animsHumanHead[0].addKeyframe(33, 0, 60, 10, 1);
	animsHumanHead[0].addKeyframe(66, 0, -60, 10, 1);
	animsHumanHead[0].addKeyframe(100, 0, 0, 0, 1);
	animsHumanHead[1].addKeyframe(0, 0, 0, 20, 1);
	animsHumanHead[1].addKeyframe(25, 0, 0, 15, 1);
	animsHumanHead[1].addKeyframe(50, 0, 0, 20, 1);
	animsHumanHead[1].addKeyframe(75, 0, 0, 15, 1);
	animsHumanHead[1].addKeyframe(100, 0, 0, 20, 1);
	animsHumanHead[2].addKeyframe(0, 0, 0, 0, 1);
	animsHumanHead[2].addKeyframe(100, 0, -40, 20, 1);
	animsHumanHead[3].addKeyframe(0, 0, 0, 20, 1);
	animsHumanHead[3].addKeyframe(75, 0, 0, 40, 1);
	animsHumanHead[3].addKeyframe(100, 0, 0, -45, 1);//edit
	animsHumanHead[4].addKeyframe(0, 0, 0, -30, 1);
	animsHumanHead[4].addKeyframe(100, 0, 0, 20, 1);
	animsHumanHead[5].addKeyframe(0, 0, 0, -30, 1);
	animsHumanHead[5].addKeyframe(100, 0, 0, 20, 1);
	animsHumanHead[6].addKeyframe(0, 0, 0, 70, 1);
	animsHumanHead[6].addKeyframe(100, 0, 0, 90, 1);
	animsHumanHead[7].addKeyframe(0, 0, 0, -30, 1);
	animsHumanHead[7].addKeyframe(100, 0, 0, -30, 1);
	animsHumanHead[8].addKeyframe(0, 0, 0, 0, 1);
	animsHumanHead[8].addKeyframe(100, 0, 0, -20, 1);
	animsHumanHead[9].addKeyframe(0, 0, 0, -30, 1);
	animsHumanHead[9].addKeyframe(100, 0, 0, -30, 1);
	animsHumanHead[10].addKeyframe(0, 0, 0, 10, 1);
	animsHumanHead[10].addKeyframe(100, 0, 0, -20, 1);
	animsHumanHead[11].addKeyframe(0, 0, 0, -40, 1);
	animsHumanHead[11].addKeyframe(100, 0, 0, -40, 1);
	animsHumanHead[12].addKeyframe(0, 0, 0, 5, 1);
	animsHumanHead[12].addKeyframe(100, 0, 0, 5, 1);
	animsHumanHead[13].addKeyframe(0, 0, 0, 45, 1);
	animsHumanHead[13].addKeyframe(100, 0, 0, 45, 1);
	animsHumanHead[14].addKeyframe(0, 0, 0, 45, 1);
	animsHumanHead[14].addKeyframe(100, 0, 0, 45, 1);
	animsHumanHead[15].addKeyframe(0, 0, 0, 70, 1);
	animsHumanHead[15].addKeyframe(100, 0, 0, 70, 1);
	animsHumanHead[16].addKeyframe(0, 0, 0, 70, 1);
	animsHumanHead[16].addKeyframe(100, 0, 0, 70, 1);
	animsHumanHead[17].addKeyframe(0, 0, 0, 0, 1);
	animsHumanHead[17].addKeyframe(100, 0, 0, 0, 1);

	animsHumanLeftHumerus[0].addKeyframe(0, 0, 90 + 20, -25, 1);//stand
	animsHumanLeftHumerus[0].addKeyframe(50, 0, 90 + 10, -35, 1);
	animsHumanLeftHumerus[0].addKeyframe(100, 0, 90 + 20, -25, 1);
	animsHumanLeftHumerus[1].addKeyframe(0, 0, 165, -25, 1);//run//-25 //45z for close
	animsHumanLeftHumerus[1].addKeyframe(50, 0, 80, -55, 1);
	animsHumanLeftHumerus[1].addKeyframe(100, 0, 165, -25, 1);
	animsHumanLeftHumerus[2].addKeyframe(0, 0, 90, -50, 1);
	animsHumanLeftHumerus[2].addKeyframe(100, 0, 90, -80, 1);
	animsHumanLeftHumerus[3].addKeyframe(0, 0, 90, -75, 1);
	animsHumanLeftHumerus[3].addKeyframe(75, 0, 90, -75, 1);
	animsHumanLeftHumerus[3].addKeyframe(100, 0, 140, 0, 1); //edit 25
	animsHumanLeftHumerus[4].addKeyframe(0, 0, 0, -70, 1);
	animsHumanLeftHumerus[4].addKeyframe(100, 0, 0, 60, 1);
	animsHumanLeftHumerus[5].addKeyframe(0, 0, 0, -70, 1);
	animsHumanLeftHumerus[5].addKeyframe(100, 0, 0, 60, 1);
	animsHumanLeftHumerus[6].addKeyframe(0, 0, 0, 30, 1);
	animsHumanLeftHumerus[6].addKeyframe(100, 0, 0, 90, 1);
	animsHumanLeftHumerus[7].addKeyframe(0, 0, -20, 135, 1);
	animsHumanLeftHumerus[7].addKeyframe(100, 0, -20, 135, 1);
	animsHumanLeftHumerus[8].addKeyframe(0, 0, 170, 5, 1);
	animsHumanLeftHumerus[8].addKeyframe(100, 0, 155, 15, 1);
	animsHumanLeftHumerus[9].addKeyframe(0, 0, 135, 45, 1);
	animsHumanLeftHumerus[9].addKeyframe(100, 0, 135, 45, 1);
	animsHumanLeftHumerus[10].addKeyframe(0, 0, 135, -10, 1);
	animsHumanLeftHumerus[10].addKeyframe(100, 0, 20, -20, 1);
	animsHumanLeftHumerus[11].addKeyframe(0, 0, 10, -10, 1);
	animsHumanLeftHumerus[11].addKeyframe(100, 0, 10, -10, 1);
	animsHumanLeftHumerus[12].addKeyframe(0, 0, 45, 35, 1);
	animsHumanLeftHumerus[12].addKeyframe(100, 0, 45, 35, 1);
	animsHumanLeftHumerus[13].addKeyframe(0, 0, 5, -130, 1);
	animsHumanLeftHumerus[13].addKeyframe(100, 0, 5, -130, 1);
	animsHumanLeftHumerus[14].addKeyframe(0, 0, 5, -130, 1);
	animsHumanLeftHumerus[14].addKeyframe(100, 0, 5, -130, 1);
	animsHumanLeftHumerus[15].addKeyframe(0, 0, -30, -90, 1);
	animsHumanLeftHumerus[15].addKeyframe(100, 0, -30, -90, 1);
	animsHumanLeftHumerus[16].addKeyframe(0, 0, -150, -90, 1);
	animsHumanLeftHumerus[16].addKeyframe(50, 0, -30, -90, 1);
	animsHumanLeftHumerus[16].addKeyframe(100, 0, -30, -90, 1);
	animsHumanLeftHumerus[17].addKeyframe(0, 0, 90, 0, 1);
	animsHumanLeftHumerus[17].addKeyframe(100, 0, 90, 0, 1);

	animsHumanRightHumerus[0].addKeyframe(0, 0, -(90 + 20), -25, 1);
	animsHumanRightHumerus[0].addKeyframe(50, 0, -(90 + 10), -35, 1);
	animsHumanRightHumerus[0].addKeyframe(100, 0, -(90 + 20), -25, 1);
	animsHumanRightHumerus[1].addKeyframe(0, 0, -80, -55, 1);
	animsHumanRightHumerus[1].addKeyframe(50, 0, -165, -25, 1);
	animsHumanRightHumerus[1].addKeyframe(100, 0, -80, -55, 1);
	animsHumanRightHumerus[2].addKeyframe(0, 0, -90, 50, 1);
	animsHumanRightHumerus[2].addKeyframe(100, 0, -90, 80, 1);
	animsHumanRightHumerus[3].addKeyframe(0, 0, -90, -75, 1);
	animsHumanRightHumerus[3].addKeyframe(75, 0, -90, -75, 1);
	animsHumanRightHumerus[3].addKeyframe(100, 0, -140, 0, 1); //edit
	animsHumanRightHumerus[4].addKeyframe(0, 0, 0, -70, 1);
	animsHumanRightHumerus[4].addKeyframe(100, 0, 0, 60, 1);
	animsHumanRightHumerus[5].addKeyframe(0, 0, 0, -70, 1);
	animsHumanRightHumerus[5].addKeyframe(100, 0, 0, 60, 1);
	animsHumanRightHumerus[6].addKeyframe(0, 0, 0, 30, 1);
	animsHumanRightHumerus[6].addKeyframe(100, 0, 0, 90, 1);
	animsHumanRightHumerus[7].addKeyframe(0, 0, 20, 135, 1);
	animsHumanRightHumerus[7].addKeyframe(100, 0, 20, 135, 1);
	animsHumanRightHumerus[8].addKeyframe(0, 0, -170, 5, 1);
	animsHumanRightHumerus[8].addKeyframe(100, 0, -155, 15, 1);
	animsHumanRightHumerus[9].addKeyframe(0, 0, -135, 45, 1);
	animsHumanRightHumerus[9].addKeyframe(100, 0, -135, 45, 1);
	animsHumanRightHumerus[10].addKeyframe(0, 0, -135, -10, 1);
	animsHumanRightHumerus[10].addKeyframe(100, 0, -20, -20, 1);
	animsHumanRightHumerus[11].addKeyframe(0, 0, -10, -10, 1);
	animsHumanRightHumerus[11].addKeyframe(100, 0, -10, -10, 1);
	animsHumanRightHumerus[12].addKeyframe(0, 0, -45, 35, 1);
	animsHumanRightHumerus[12].addKeyframe(100, 0, -45, 35, 1);
	animsHumanRightHumerus[13].addKeyframe(0, 0, -5, -130, 1);
	animsHumanRightHumerus[13].addKeyframe(100, 0, -5, -130, 1);
	animsHumanRightHumerus[14].addKeyframe(0, 0, -5, -130, 1);
	animsHumanRightHumerus[14].addKeyframe(100, 0, -5, -130, 1);
	animsHumanRightHumerus[15].addKeyframe(0, 0, 30, -90, 1);
	animsHumanRightHumerus[15].addKeyframe(100, 0, 30, -90, 1);
	animsHumanRightHumerus[16].addKeyframe(0, 0, 150, -90, 1);
	animsHumanRightHumerus[16].addKeyframe(50, 0, 30, -90, 1);
	animsHumanRightHumerus[16].addKeyframe(100, 0, 30, -90, 1);
	animsHumanRightHumerus[17].addKeyframe(0, 0, -90, 0, 1);
	animsHumanRightHumerus[17].addKeyframe(100, 0, -90, 0, 1);

	animsHumanLeftForearm[0].addKeyframe(0, 0, -120, -25, 1);//stand
	animsHumanLeftForearm[0].addKeyframe(50, 0, -120, 0, 1);
	animsHumanLeftForearm[0].addKeyframe(100, 0, -120, -25, 1);
	animsHumanLeftForearm[1].addKeyframe(0, 0, 0, -20, 1);//run//-20 //-90z for close
	animsHumanLeftForearm[1].addKeyframe(50, 0, -80, 90, 1);
	animsHumanLeftForearm[1].addKeyframe(100, 0, 0, -20, 1);
	animsHumanLeftForearm[2].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftForearm[2].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftForearm[3].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftForearm[3].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftForearm[4].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftForearm[4].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftForearm[5].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftForearm[5].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftForearm[6].addKeyframe(0, 0, 0, 90, 1);
	animsHumanLeftForearm[6].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftForearm[7].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftForearm[7].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftForearm[8].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftForearm[8].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftForearm[9].addKeyframe(0, 0, -90, -90, 1);
	animsHumanLeftForearm[9].addKeyframe(100, 0, -90, -90, 1);
	animsHumanLeftForearm[10].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftForearm[10].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftForearm[11].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftForearm[11].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftForearm[12].addKeyframe(0, 0, -20, 20, 1);
	animsHumanLeftForearm[12].addKeyframe(100, 0, -20, 20, 1);
	animsHumanLeftForearm[13].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftForearm[13].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftForearm[14].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftForearm[14].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftForearm[15].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftForearm[15].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftForearm[16].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftForearm[16].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftForearm[17].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftForearm[17].addKeyframe(100, 0, 0, 0, 1);

	animsHumanRightForearm[0].addKeyframe(0, 0, -(-120), -25, 1);
	animsHumanRightForearm[0].addKeyframe(50, 0, -(-120), 0, 1);
	animsHumanRightForearm[0].addKeyframe(100, 0, -(-120), -25, 1);
	animsHumanRightForearm[1].addKeyframe(0, 0, 80, 90, 1);//run//-20 //-90z for close
	animsHumanRightForearm[1].addKeyframe(50, 0, 0, -20, 1);
	animsHumanRightForearm[1].addKeyframe(100, 0, 80, 90, 1);
	animsHumanRightForearm[2].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightForearm[2].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightForearm[3].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightForearm[3].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightForearm[4].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightForearm[4].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightForearm[5].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightForearm[5].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightForearm[6].addKeyframe(0, 0, 0, 90, 1);
	animsHumanRightForearm[6].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightForearm[7].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightForearm[7].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightForearm[8].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightForearm[8].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightForearm[9].addKeyframe(0, 0, 90, -90, 1);
	animsHumanRightForearm[9].addKeyframe(100, 0, 90, -90, 1);
	animsHumanRightForearm[10].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightForearm[10].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightForearm[11].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightForearm[11].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightForearm[12].addKeyframe(0, 0, 20, 20, 1);
	animsHumanRightForearm[12].addKeyframe(100, 0, 20, 20, 1);
	animsHumanRightForearm[13].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightForearm[13].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightForearm[14].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightForearm[14].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightForearm[15].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightForearm[15].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightForearm[16].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightForearm[16].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightForearm[17].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightForearm[17].addKeyframe(100, 0, 0, 0, 1);

	animsHumanLeftHand[0].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftHand[0].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftHand[1].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftHand[1].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftHand[2].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftHand[2].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftHand[3].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftHand[3].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftHand[4].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftHand[4].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftHand[5].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftHand[5].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftHand[6].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftHand[6].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftHand[7].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftHand[7].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftHand[8].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftHand[8].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftHand[9].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftHand[9].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftHand[10].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftHand[10].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftHand[11].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftHand[11].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftHand[12].addKeyframe(0, 0, 10, 30, 1);
	animsHumanLeftHand[12].addKeyframe(100, 0, 10, 30, 1);
	animsHumanLeftHand[13].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftHand[13].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftHand[14].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftHand[14].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftHand[15].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftHand[15].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftHand[16].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftHand[16].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftHand[17].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftHand[17].addKeyframe(100, 0, 0, 0, 1);


	animsHumanRightHand[0].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightHand[0].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightHand[1].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightHand[1].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightHand[2].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightHand[2].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightHand[3].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightHand[3].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightHand[4].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightHand[4].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightHand[5].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightHand[5].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightHand[6].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightHand[6].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightHand[7].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightHand[7].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightHand[8].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightHand[8].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightHand[9].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightHand[9].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightHand[10].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightHand[10].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightHand[11].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightHand[11].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightHand[12].addKeyframe(0, 0, 10, 30, 1);
	animsHumanRightHand[12].addKeyframe(100, 0, 10, 30, 1);
	animsHumanRightHand[13].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightHand[13].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightHand[14].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightHand[14].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightHand[15].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightHand[15].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightHand[16].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightHand[16].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightHand[17].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightHand[17].addKeyframe(100, 0, 0, 0, 1);

	animsHumanLeftThigh[0].addKeyframe(0, 0, 50, -55, 1);
	animsHumanLeftThigh[0].addKeyframe(50, 0, 50, -70, 1);
	animsHumanLeftThigh[0].addKeyframe(100, 0, 50, -55, 1);
	animsHumanLeftThigh[1].addKeyframe((0 + 50) % 100, 0, 0, -135, 1);//run
	animsHumanLeftThigh[1].addKeyframe((5 + 50) % 100, 0, 0, -130, 1);
	animsHumanLeftThigh[1].addKeyframe((10 + 50) % 100, 0, 0, -125, 1);
	animsHumanLeftThigh[1].addKeyframe((15 + 50) % 100, 0, 0, -115, 1);
	animsHumanLeftThigh[1].addKeyframe((20 + 50) % 100, 0, 0, -70, 1);
	animsHumanLeftThigh[1].addKeyframe((25 + 50) % 100, 0, 0, -10, 1);
	animsHumanLeftThigh[1].addKeyframe((30 + 50) % 100, 0, 0, 10, 1);
	animsHumanLeftThigh[1].addKeyframe((35 + 50) % 100, 0, 0, 10, 1);
	animsHumanLeftThigh[1].addKeyframe((40 + 50) % 100, 0, 0, 10, 1);
	animsHumanLeftThigh[1].addKeyframe((45 + 50) % 100, 0, 0, 12, 1);
	animsHumanLeftThigh[1].addKeyframe((50 + 50) % 100, 0, 0, 15, 1);
	animsHumanLeftThigh[1].addKeyframe((55 + 50) % 100, 0, 0, 5, 1);
	animsHumanLeftThigh[1].addKeyframe((60 + 50) % 100, 0, 0, -50, 1);
	animsHumanLeftThigh[1].addKeyframe((65 + 50) % 100, 0, 0, -55, 1);
	animsHumanLeftThigh[1].addKeyframe((70 + 50) % 100, 0, 0, -60, 1);
	animsHumanLeftThigh[1].addKeyframe((75 + 50) % 100, 0, 0, -90, 1);
	animsHumanLeftThigh[1].addKeyframe((80 + 50) % 100, 0, 0, -100, 1);
	animsHumanLeftThigh[1].addKeyframe((85 + 50) % 100, 0, 0, -120, 1);
	animsHumanLeftThigh[1].addKeyframe((90 + 50) % 100, 0, 0, -130, 1);
	animsHumanLeftThigh[1].addKeyframe((95 + 50) % 100, 0, 0, -130, 1);
	animsHumanLeftThigh[1].addKeyframe((100 + 50) % 100, 0, 0, -135, 1);
	animsHumanLeftThigh[2].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftThigh[2].addKeyframe(100, 0, -20, 20, 1);
	animsHumanLeftThigh[3].addKeyframe(0, 0, 0, -80, 1);
	animsHumanLeftThigh[3].addKeyframe(75, 0, 0, -80, 1);
	animsHumanLeftThigh[3].addKeyframe(100, 0, 0, -45, 1);
	animsHumanLeftThigh[4].addKeyframe(0, 0, 0, 45, 1);
	animsHumanLeftThigh[4].addKeyframe(100, 0, 0, -90, 1);
	animsHumanLeftThigh[5].addKeyframe(0, 0, 0, 45, 1);
	animsHumanLeftThigh[5].addKeyframe(100, 0, 0, -90, 1);
	animsHumanLeftThigh[6].addKeyframe(0, 0, 0, -45, 1);
	animsHumanLeftThigh[6].addKeyframe(100, 0, 0, -90, 1);
	animsHumanLeftThigh[7].addKeyframe(0, 0, 0, -90, 1);
	animsHumanLeftThigh[7].addKeyframe(100, 0, 0, -90, 1);
	animsHumanLeftThigh[8].addKeyframe(0, 0, 0, -45, 1);
	animsHumanLeftThigh[8].addKeyframe(100, 0, 0, -10, 1);
	animsHumanLeftThigh[9].addKeyframe(0, 0, 0, 20, 1);
	animsHumanLeftThigh[9].addKeyframe(100, 0, 0, 20, 1);
	animsHumanLeftThigh[10].addKeyframe(0, 0, 0, -10, 1);
	animsHumanLeftThigh[10].addKeyframe(100, 0, 0, -30, 1);
	animsHumanLeftThigh[11].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftThigh[11].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftThigh[12].addKeyframe(0, 0, 20, 0, 1);
	animsHumanLeftThigh[12].addKeyframe(100, 0, 20, 0, 1);
	animsHumanLeftThigh[13].addKeyframe(0, 0, 0, -130, 1);
	animsHumanLeftThigh[13].addKeyframe(100, 0, 0, -130, 1);
	animsHumanLeftThigh[14].addKeyframe(0, 0, 0, -130, 1);
	animsHumanLeftThigh[14].addKeyframe(100, 0, 0, -130, 1);
	animsHumanLeftThigh[15].addKeyframe(0, 0, 0, -70, 1);
	animsHumanLeftThigh[15].addKeyframe(50, 0, 0, -110, 1);
	animsHumanLeftThigh[15].addKeyframe(100, 0, 0, -70, 1);
	animsHumanLeftThigh[16].addKeyframe(0, 0, 0, -70, 1);
	animsHumanLeftThigh[16].addKeyframe(50, 0, 0, -110, 1);
	animsHumanLeftThigh[16].addKeyframe(100, 0, 0, -110, 1);
	animsHumanLeftThigh[17].addKeyframe(0, 0, 0, -90, 1);
	animsHumanLeftThigh[17].addKeyframe(100, 0, 0, -90, 1);

	animsHumanRightThigh[0].addKeyframe(0, 0, -50, -55, 1);
	animsHumanRightThigh[0].addKeyframe(50, 0, -50, -70, 1);
	animsHumanRightThigh[0].addKeyframe(100, 0, -50, -55, 1);
	animsHumanRightThigh[1].addKeyframe(0, 0, 0, -135, 1);//run
	animsHumanRightThigh[1].addKeyframe(5, 0, 0, -130, 1);
	animsHumanRightThigh[1].addKeyframe(10, 0, 0, -125, 1);
	animsHumanRightThigh[1].addKeyframe(15, 0, 0, -115, 1);
	animsHumanRightThigh[1].addKeyframe(20, 0, 0, -70, 1);
	animsHumanRightThigh[1].addKeyframe(25, 0, 0, -10, 1);
	animsHumanRightThigh[1].addKeyframe(30, 0, 0, 10, 1);
	animsHumanRightThigh[1].addKeyframe(35, 0, 0, 10, 1);
	animsHumanRightThigh[1].addKeyframe(40, 0, 0, 10, 1);
	animsHumanRightThigh[1].addKeyframe(45, 0, 0, 12, 1);
	animsHumanRightThigh[1].addKeyframe(50, 0, 0, 15, 1);
	animsHumanRightThigh[1].addKeyframe(55, 0, 0, 5, 1);
	animsHumanRightThigh[1].addKeyframe(60, 0, 0, -50, 1);
	animsHumanRightThigh[1].addKeyframe(65, 0, 0, -55, 1);
	animsHumanRightThigh[1].addKeyframe(70, 0, 0, -60, 1);
	animsHumanRightThigh[1].addKeyframe(75, 0, 0, -90, 1);
	animsHumanRightThigh[1].addKeyframe(80, 0, 0, -100, 1);
	animsHumanRightThigh[1].addKeyframe(85, 0, 0, -120, 1);
	animsHumanRightThigh[1].addKeyframe(90, 0, 0, -130, 1);
	animsHumanRightThigh[1].addKeyframe(95, 0, 0, -130, 1);
	animsHumanRightThigh[1].addKeyframe(100, 0, 0, -135, 1);
	animsHumanRightThigh[2].addKeyframe(0, 0, -20, -90, 1);
	animsHumanRightThigh[2].addKeyframe(100, 0, -50, -90, 1);
	animsHumanRightThigh[3].addKeyframe(0, 0, 0, -95, 1);
	animsHumanRightThigh[3].addKeyframe(75, 0, 0, -95, 1);
	animsHumanRightThigh[3].addKeyframe(100, 0, 0, -80, 1);
	animsHumanRightThigh[4].addKeyframe(0, 0, 0, 45, 1);
	animsHumanRightThigh[4].addKeyframe(100, 0, 0, -90, 1);
	animsHumanRightThigh[5].addKeyframe(0, 0, 0, 45, 1);
	animsHumanRightThigh[5].addKeyframe(100, 0, 0, -90, 1);
	animsHumanRightThigh[6].addKeyframe(0, 0, 0, -45, 1);
	animsHumanRightThigh[6].addKeyframe(100, 0, 0, -90, 1);
	animsHumanRightThigh[7].addKeyframe(0, 0, 0, -90, 1);
	animsHumanRightThigh[7].addKeyframe(100, 0, 0, -90, 1);
	animsHumanRightThigh[8].addKeyframe(0, 0, 0, -45, 1);
	animsHumanRightThigh[8].addKeyframe(100, 0, 0, -10, 1);
	animsHumanRightThigh[9].addKeyframe(0, 0, 0, 20, 1);
	animsHumanRightThigh[9].addKeyframe(100, 0, 0, 20, 1);
	animsHumanRightThigh[10].addKeyframe(0, 0, 0, -10, 1);
	animsHumanRightThigh[10].addKeyframe(100, 0, 0, -30, 1);
	animsHumanRightThigh[11].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightThigh[11].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightThigh[12].addKeyframe(0, 0, -20, 0, 1);
	animsHumanRightThigh[12].addKeyframe(100, 0, -20, 0, 1);
	animsHumanRightThigh[13].addKeyframe(0, 0, 0, -130, 1);
	animsHumanRightThigh[13].addKeyframe(100, 0, 0, -130, 1);
	animsHumanRightThigh[14].addKeyframe(0, 0, 0, -130, 1);
	animsHumanRightThigh[14].addKeyframe(100, 0, 0, -130, 1);
	animsHumanRightThigh[15].addKeyframe(0, 0, 0, -110, 1);
	animsHumanRightThigh[15].addKeyframe(50, 0, 0, -70, 1);
	animsHumanRightThigh[15].addKeyframe(100, 0, 0, -110, 1);
	animsHumanRightThigh[16].addKeyframe(0, 0, 0, -70, 1);
	animsHumanRightThigh[16].addKeyframe(50, 0, 0, -110, 1);
	animsHumanRightThigh[16].addKeyframe(100, 0, 0, -110, 1);
	animsHumanRightThigh[17].addKeyframe(0, 0, 0, -90, 1);
	animsHumanRightThigh[17].addKeyframe(100, 0, 0, -90, 1);

	animsHumanLeftShin[0].addKeyframe(0, 0, 0, -35 * 2, 1);
	animsHumanLeftShin[0].addKeyframe(50, 0, 0, -20 * 2, 1);
	animsHumanLeftShin[0].addKeyframe(100, 0, 0, -35 * 2, 1);
	animsHumanLeftShin[1].addKeyframe((0 + 50) % 100, 0, 0, -20, 1);//run
	animsHumanLeftShin[1].addKeyframe((5 + 50) % 100, 0, 0, -25, 1);
	animsHumanLeftShin[1].addKeyframe((10 + 50) % 100, 0, 0, -30, 1);
	animsHumanLeftShin[1].addKeyframe((15 + 50) % 100, 0, 0, -45, 1);
	animsHumanLeftShin[1].addKeyframe((20 + 50) % 100, 0, 0, -90, 1);
	animsHumanLeftShin[1].addKeyframe((25 + 50) % 100, 0, 0, -125, 1);
	animsHumanLeftShin[1].addKeyframe((30 + 50) % 100, 0, 0, -140, 1);
	animsHumanLeftShin[1].addKeyframe((35 + 50) % 100, 0, 0, -135, 1);
	animsHumanLeftShin[1].addKeyframe((40 + 50) % 100, 0, 0, -115, 1);
	animsHumanLeftShin[1].addKeyframe((45 + 50) % 100, 0, 0, -80, 1);
	animsHumanLeftShin[1].addKeyframe((50 + 50) % 100, 0, 0, -40, 1);
	animsHumanLeftShin[1].addKeyframe((55 + 50) % 100, 0, 0, -30, 1);
	animsHumanLeftShin[1].addKeyframe((60 + 50) % 100, 0, 0, -20, 1);
	animsHumanLeftShin[1].addKeyframe((65 + 50) % 100, 0, 0, -17, 1);
	animsHumanLeftShin[1].addKeyframe((70 + 50) % 100, 0, 0, -17, 1);
	animsHumanLeftShin[1].addKeyframe((75 + 50) % 100, 0, 0, -5, 1);
	animsHumanLeftShin[1].addKeyframe((80 + 50) % 100, 0, 0, 0, 1);
	animsHumanLeftShin[1].addKeyframe((85 + 50) % 100, 0, 0, 0, 1);
	animsHumanLeftShin[1].addKeyframe((90 + 50) % 100, 0, 0, 0, 1);
	animsHumanLeftShin[1].addKeyframe((95 + 50) % 100, 0, 0, -15, 1);
	animsHumanLeftShin[1].addKeyframe((100 + 50) % 100, 0, 0, -20, 1);
	animsHumanLeftShin[2].addKeyframe(0, 0, 0, -90, 1);
	animsHumanLeftShin[2].addKeyframe(100, 0, 0, -90, 1);
	animsHumanLeftShin[3].addKeyframe(0, 0, 0, -20, 1);
	animsHumanLeftShin[3].addKeyframe(75, 0, 0, -20, 1);
	animsHumanLeftShin[3].addKeyframe(100, 0, 0, -90, 1);
	animsHumanLeftShin[4].addKeyframe(0, 0, 0, -130, 1);
	animsHumanLeftShin[4].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftShin[5].addKeyframe(0, 0, 0, -130, 1);
	animsHumanLeftShin[5].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftShin[6].addKeyframe(0, 0, 0, -90, 1);
	animsHumanLeftShin[6].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftShin[7].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftShin[7].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftShin[8].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftShin[8].addKeyframe(100, 0, 0, -60, 1);
	animsHumanLeftShin[9].addKeyframe(0, 0, 0, -10, 1);
	animsHumanLeftShin[9].addKeyframe(100, 0, 0, -10, 1);
	animsHumanLeftShin[10].addKeyframe(0, 0, 0, -10, 1);
	animsHumanLeftShin[10].addKeyframe(100, 0, 0, -10, 1);
	animsHumanLeftShin[11].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftShin[11].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftShin[12].addKeyframe(0, 0, 0, -120, 1);
	animsHumanLeftShin[12].addKeyframe(100, 0, 0, -120, 1);
	animsHumanLeftShin[13].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftShin[13].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftShin[14].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftShin[14].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftShin[15].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftShin[15].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftShin[16].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftShin[16].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftShin[17].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftShin[17].addKeyframe(100, 0, 0, 0, 1);

	animsHumanRightShin[0].addKeyframe(0, 0, 0, -35 * 2, 1);
	animsHumanRightShin[0].addKeyframe(50, 0, 0, -20 * 2, 1);
	animsHumanRightShin[0].addKeyframe(100, 0, 0, -35 * 2, 1);
	animsHumanRightShin[1].addKeyframe(0, 0, 0, -20, 1);//run
	animsHumanRightShin[1].addKeyframe(5, 0, 0, -25, 1);
	animsHumanRightShin[1].addKeyframe(10, 0, 0, -30, 1);
	animsHumanRightShin[1].addKeyframe(15, 0, 0, -45, 1);
	animsHumanRightShin[1].addKeyframe(20, 0, 0, -90, 1);
	animsHumanRightShin[1].addKeyframe(25, 0, 0, -125, 1);
	animsHumanRightShin[1].addKeyframe(30, 0, 0, -140, 1);
	animsHumanRightShin[1].addKeyframe(35, 0, 0, -135, 1);
	animsHumanRightShin[1].addKeyframe(40, 0, 0, -115, 1);
	animsHumanRightShin[1].addKeyframe(45, 0, 0, -80, 1);
	animsHumanRightShin[1].addKeyframe(50, 0, 0, -40, 1);
	animsHumanRightShin[1].addKeyframe(55, 0, 0, -30, 1);
	animsHumanRightShin[1].addKeyframe(60, 0, 0, -20, 1);
	animsHumanRightShin[1].addKeyframe(65, 0, 0, -17, 1);
	animsHumanRightShin[1].addKeyframe(70, 0, 0, -17, 1);
	animsHumanRightShin[1].addKeyframe(75, 0, 0, -5, 1);
	animsHumanRightShin[1].addKeyframe(80, 0, 0, 0, 1);
	animsHumanRightShin[1].addKeyframe(85, 0, 0, 0, 1);
	animsHumanRightShin[1].addKeyframe(90, 0, 0, 0, 1);
	animsHumanRightShin[1].addKeyframe(95, 0, 0, -15, 1);
	animsHumanRightShin[1].addKeyframe(100, 0, 0, -20, 1);
	animsHumanRightShin[2].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightShin[2].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightShin[3].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightShin[3].addKeyframe(75, 0, 0, 0, 1);
	animsHumanRightShin[3].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightShin[4].addKeyframe(0, 0, 0, -130, 1);
	animsHumanRightShin[4].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightShin[5].addKeyframe(0, 0, 0, -130, 1);
	animsHumanRightShin[5].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightShin[6].addKeyframe(0, 0, 0, -90, 1);
	animsHumanRightShin[6].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightShin[7].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightShin[7].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightShin[8].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightShin[8].addKeyframe(100, 0, 0, -60, 1);
	animsHumanRightShin[9].addKeyframe(0, 0, 0, -10, 1);
	animsHumanRightShin[9].addKeyframe(100, 0, 0, -10, 1);
	animsHumanRightShin[10].addKeyframe(0, 0, 0, -10, 1);
	animsHumanRightShin[10].addKeyframe(100, 0, 0, -10, 1);
	animsHumanRightShin[11].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightShin[11].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightShin[12].addKeyframe(0, 0, 0, -120, 1);
	animsHumanRightShin[12].addKeyframe(100, 0, 0, -120, 1);
	animsHumanRightShin[13].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightShin[13].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightShin[14].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightShin[14].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightShin[15].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightShin[15].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightShin[16].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightShin[16].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightShin[17].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightShin[17].addKeyframe(100, 0, 0, 0, 1);

	animsHumanLeftFoot[0].addKeyframe(0, 0, 0, 55 + 35 * 2, 1);
	animsHumanLeftFoot[0].addKeyframe(50, 0, 0, 70 + 20 * 2, 1);
	animsHumanLeftFoot[0].addKeyframe(100, 0, 0, 55 + 35 * 2, 1);
	animsHumanLeftFoot[1].addKeyframe((0 + 50) % 100, 0, 0, -10, 1);//run
	animsHumanLeftFoot[1].addKeyframe((5 + 50) % 100, 0, 0, 15, 1);
	animsHumanLeftFoot[1].addKeyframe((10 + 50) % 100, 0, 0, 30, 1);//was 60
	animsHumanLeftFoot[1].addKeyframe((15 + 50) % 100, 0, 0, 45, 1);
	animsHumanLeftFoot[1].addKeyframe((20 + 50) % 100, 0, 0, 30, 1);
	animsHumanLeftFoot[1].addKeyframe((25 + 50) % 100, 0, 0, 10, 1);
	animsHumanLeftFoot[1].addKeyframe((30 + 50) % 100, 0, 0, 0, 1);
	animsHumanLeftFoot[1].addKeyframe((35 + 50) % 100, 0, 0, 30, 1);
	animsHumanLeftFoot[1].addKeyframe((40 + 50) % 100, 0, 0, 120, 1);
	animsHumanLeftFoot[1].addKeyframe((45 + 50) % 100, 0, 0, 115, 1);
	animsHumanLeftFoot[1].addKeyframe((50 + 50) % 100, 0, 0, 80, 1);
	animsHumanLeftFoot[1].addKeyframe((55 + 50) % 100, 0, 0, 80, 1);
	animsHumanLeftFoot[1].addKeyframe((60 + 50) % 100, 0, 0, 95, 1);
	animsHumanLeftFoot[1].addKeyframe((65 + 50) % 100, 0, 0, 95, 1);
	animsHumanLeftFoot[1].addKeyframe((70 + 50) % 100, 0, 0, 90, 1);
	animsHumanLeftFoot[1].addKeyframe((75 + 50) % 100, 0, 0, 80, 1);
	animsHumanLeftFoot[1].addKeyframe((80 + 50) % 100, 0, 0, 60, 1);
	animsHumanLeftFoot[1].addKeyframe((85 + 50) % 100, 0, 0, 30, 1);
	animsHumanLeftFoot[1].addKeyframe((90 + 50) % 100, 0, 0, 10, 1);
	animsHumanLeftFoot[1].addKeyframe((95 + 50) % 100, 0, 0, 0, 1);
	animsHumanLeftFoot[1].addKeyframe((100 + 50) % 100, 0, 0, -10, 1);
	animsHumanLeftFoot[2].addKeyframe(0, 0, 0, 45, 1);
	animsHumanLeftFoot[2].addKeyframe(100, 0, 0, 45, 1);
	animsHumanLeftFoot[3].addKeyframe(0, 0, 0, 90, 1);
	animsHumanLeftFoot[3].addKeyframe(75, 0, 0, 90, 1);
	animsHumanLeftFoot[3].addKeyframe(100, 0, 0, 90, 1);
	animsHumanLeftFoot[4].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftFoot[4].addKeyframe(100, 0, 0, 30, 1);
	animsHumanLeftFoot[5].addKeyframe(0, 0, 0, 0, 1);
	animsHumanLeftFoot[5].addKeyframe(100, 0, 0, 30, 1);
	animsHumanLeftFoot[6].addKeyframe(0, 0, 0, 45, 1);
	animsHumanLeftFoot[6].addKeyframe(100, 0, 0, 0, 1);
	animsHumanLeftFoot[7].addKeyframe(0, 0, 0, 70, 1);
	animsHumanLeftFoot[7].addKeyframe(100, 0, 0, 70, 1);
	animsHumanLeftFoot[8].addKeyframe(0, 0, 0, 90, 1);
	animsHumanLeftFoot[8].addKeyframe(100, 0, 0, 120, 1);
	animsHumanLeftFoot[9].addKeyframe(0, 0, 0, 60, 1);
	animsHumanLeftFoot[9].addKeyframe(100, 0, 0, 60, 1);
	animsHumanLeftFoot[10].addKeyframe(0, 0, 0, 90, 1);
	animsHumanLeftFoot[10].addKeyframe(100, 0, 0, 80, 1);
	animsHumanLeftFoot[11].addKeyframe(0, 0, 0, 120, 1);
	animsHumanLeftFoot[11].addKeyframe(100, 0, 0, 120, 1);
	animsHumanLeftFoot[12].addKeyframe(0, 0, 0, 150, 1);
	animsHumanLeftFoot[12].addKeyframe(100, 0, 0, 150, 1);
	animsHumanLeftFoot[13].addKeyframe(0, 0, 0, 30, 1);
	animsHumanLeftFoot[13].addKeyframe(100, 0, 0, 30, 1);
	animsHumanLeftFoot[14].addKeyframe(0, 0, 0, 30, 1);
	animsHumanLeftFoot[14].addKeyframe(100, 0, 0, 30, 1);
	animsHumanLeftFoot[15].addKeyframe(0, 0, 0, 30, 1);
	animsHumanLeftFoot[15].addKeyframe(100, 0, 0, 30, 1);
	animsHumanLeftFoot[16].addKeyframe(0, 0, 0, 30, 1);
	animsHumanLeftFoot[16].addKeyframe(100, 0, 0, 30, 1);
	animsHumanLeftFoot[17].addKeyframe(0, 0, 0, 90, 1);
	animsHumanLeftFoot[17].addKeyframe(100, 0, 0, 90, 1);

	animsHumanRightFoot[0].addKeyframe(0, 0, 0, 55 + 35 * 2, 1);
	animsHumanRightFoot[0].addKeyframe(50, 0, 0, 70 + 20 * 2, 1);
	animsHumanRightFoot[0].addKeyframe(100, 0, 0, 55 + 35 * 2, 1);
	animsHumanRightFoot[1].addKeyframe(0, 0, 0, -10, 1);//run
	animsHumanRightFoot[1].addKeyframe(5, 0, 0, 15, 1);
	animsHumanRightFoot[1].addKeyframe(10, 0, 0, 30, 1);//was 60
	animsHumanRightFoot[1].addKeyframe(15, 0, 0, 45, 1);
	animsHumanRightFoot[1].addKeyframe(20, 0, 0, 30, 1);
	animsHumanRightFoot[1].addKeyframe(25, 0, 0, 10, 1);
	animsHumanRightFoot[1].addKeyframe(30, 0, 0, 0, 1);
	animsHumanRightFoot[1].addKeyframe(35, 0, 0, 30, 1);
	animsHumanRightFoot[1].addKeyframe(40, 0, 0, 120, 1);
	animsHumanRightFoot[1].addKeyframe(45, 0, 0, 115, 1);
	animsHumanRightFoot[1].addKeyframe(50, 0, 0, 80, 1);
	animsHumanRightFoot[1].addKeyframe(55, 0, 0, 80, 1);
	animsHumanRightFoot[1].addKeyframe(60, 0, 0, 95, 1);
	animsHumanRightFoot[1].addKeyframe(65, 0, 0, 95, 1);
	animsHumanRightFoot[1].addKeyframe(70, 0, 0, 90, 1);
	animsHumanRightFoot[1].addKeyframe(75, 0, 0, 80, 1);
	animsHumanRightFoot[1].addKeyframe(80, 0, 0, 60, 1);
	animsHumanRightFoot[1].addKeyframe(85, 0, 0, 30, 1);
	animsHumanRightFoot[1].addKeyframe(90, 0, 0, 10, 1);
	animsHumanRightFoot[1].addKeyframe(95, 0, 0, 0, 1);
	animsHumanRightFoot[1].addKeyframe(100, 0, 0, -10, 1);
	animsHumanRightFoot[2].addKeyframe(0, 0, 0, 30, 1);
	animsHumanRightFoot[2].addKeyframe(100, 0, 0, 30, 1);
	animsHumanRightFoot[3].addKeyframe(0, 0, 0, 30, 1);
	animsHumanRightFoot[3].addKeyframe(75, 0, 0, 30, 1);
	animsHumanRightFoot[3].addKeyframe(100, 0, 0, 30, 1);
	animsHumanRightFoot[4].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightFoot[4].addKeyframe(100, 0, 0, 30, 1);
	animsHumanRightFoot[5].addKeyframe(0, 0, 0, 0, 1);
	animsHumanRightFoot[5].addKeyframe(100, 0, 0, 30, 1);
	animsHumanRightFoot[6].addKeyframe(0, 0, 0, 45, 1);
	animsHumanRightFoot[6].addKeyframe(100, 0, 0, 0, 1);
	animsHumanRightFoot[7].addKeyframe(0, 0, 0, 70, 1);
	animsHumanRightFoot[7].addKeyframe(100, 0, 0, 70, 1);
	animsHumanRightFoot[8].addKeyframe(0, 0, 0, 90, 1);
	animsHumanRightFoot[8].addKeyframe(100, 0, 0, 120, 1);
	animsHumanRightFoot[9].addKeyframe(0, 0, 0, 60, 1);
	animsHumanRightFoot[9].addKeyframe(100, 0, 0, 60, 1);
	animsHumanRightFoot[10].addKeyframe(0, 0, 0, 90, 1);
	animsHumanRightFoot[10].addKeyframe(100, 0, 0, 80, 1);
	animsHumanRightFoot[11].addKeyframe(0, 0, 0, 120, 1);
	animsHumanRightFoot[11].addKeyframe(100, 0, 0, 120, 1);
	animsHumanRightFoot[12].addKeyframe(0, 0, 0, 150, 1);
	animsHumanRightFoot[12].addKeyframe(100, 0, 0, 150, 1);
	animsHumanRightFoot[13].addKeyframe(0, 0, 0, 30, 1);
	animsHumanRightFoot[13].addKeyframe(100, 0, 0, 30, 1);
	animsHumanRightFoot[14].addKeyframe(0, 0, 0, 30, 1);
	animsHumanRightFoot[14].addKeyframe(100, 0, 0, 30, 1);
	animsHumanRightFoot[15].addKeyframe(0, 0, 0, 30, 1);
	animsHumanRightFoot[15].addKeyframe(100, 0, 0, 30, 1);
	animsHumanRightFoot[16].addKeyframe(0, 0, 0, 30, 1);
	animsHumanRightFoot[16].addKeyframe(100, 0, 0, 30, 1);
	animsHumanRightFoot[17].addKeyframe(0, 0, 0, 90, 1);
	animsHumanRightFoot[17].addKeyframe(100, 0, 0, 90, 1);
}

void AnimationResources::assignAnimationsHuman(Body* body, Limb* head,
	Limb* leftHumerus, Limb* leftForearm, Limb* leftHand,
	Limb* rightHumerus, Limb* rightForearm, Limb* rightHand,
	Limb* leftThigh, Limb* leftShin, Limb* leftFoot,
	Limb* rightThigh, Limb* rightShin, Limb* rightFoot)
{
	body->animations = &AnimationResources::animsHumanBody;
	head->animations = &AnimationResources::animsHumanHead;
	leftHumerus->animations = &AnimationResources::animsHumanLeftHumerus;
	leftForearm->animations = &AnimationResources::animsHumanLeftForearm;
	leftHand->animations = &AnimationResources::animsHumanLeftHand;
	rightHumerus->animations = &AnimationResources::animsHumanRightHumerus;
	rightForearm->animations = &AnimationResources::animsHumanRightForearm;
	rightHand->animations = &AnimationResources::animsHumanRightHand;
	leftThigh->animations = &AnimationResources::animsHumanLeftThigh;
	leftShin->animations = &AnimationResources::animsHumanLeftShin;
	leftFoot->animations = &AnimationResources::animsHumanLeftFoot;
	rightThigh->animations = &AnimationResources::animsHumanRightThigh;
	rightShin->animations = &AnimationResources::animsHumanRightShin;
	rightFoot->animations = &AnimationResources::animsHumanRightFoot;
}