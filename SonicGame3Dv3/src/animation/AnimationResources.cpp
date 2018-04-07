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
	while (animsHumanBody.size()         < animCount) { Animation filler; animsHumanBody.push_back(filler); }
	while (animsHumanHead.size()         < animCount) { Animation filler; animsHumanHead.push_back(filler); }
	while (animsHumanLeftHumerus.size()  < animCount) { Animation filler; animsHumanLeftHumerus.push_back(filler); }
	while (animsHumanLeftForearm.size()  < animCount) { Animation filler; animsHumanLeftForearm.push_back(filler); }
	while (animsHumanLeftHand.size()     < animCount) { Animation filler; animsHumanLeftHand.push_back(filler); }
	while (animsHumanRightHumerus.size() < animCount) { Animation filler; animsHumanRightHumerus.push_back(filler); }
	while (animsHumanRightForearm.size() < animCount) { Animation filler; animsHumanRightForearm.push_back(filler); }
	while (animsHumanRightHand.size()    < animCount) { Animation filler; animsHumanRightHand.push_back(filler); }
	while (animsHumanLeftThigh.size()    < animCount) { Animation filler; animsHumanLeftThigh.push_back(filler); }
	while (animsHumanLeftShin.size()     < animCount) { Animation filler; animsHumanLeftShin.push_back(filler); }
	while (animsHumanLeftFoot.size()     < animCount) { Animation filler; animsHumanLeftFoot.push_back(filler); }
	while (animsHumanRightThigh.size()   < animCount) { Animation filler; animsHumanRightThigh.push_back(filler); }
	while (animsHumanRightShin.size()    < animCount) { Animation filler; animsHumanRightShin.push_back(filler); }
	while (animsHumanRightFoot.size()    < animCount) { Animation filler; animsHumanRightFoot.push_back(filler); }

	//stand animation
	animsHumanBody[0].addKeyframe(0.0f, 3.35f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanBody[0].addKeyframe(50.0f, 3.7f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanBody[0].addKeyframe(100.0f, 3.35f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	//run animation
	animsHumanBody[1].addKeyframe(0.0f, 3.7f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -15.0f, 1.0f);
	animsHumanBody[1].addKeyframe(25.0f, 3.3f, -0.0f, 0.0f, 10.0f, 0.0f, 0.0f, -15.0f, 1.0f);
	animsHumanBody[1].addKeyframe(50.0f, 3.7f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -15.0f, 1.0f);
	animsHumanBody[1].addKeyframe(75.0f, 3.3f, -0.0f, 0.0f, -10.0f, 0.0f, 0.0f, -15.0f, 1.0f);
	animsHumanBody[1].addKeyframe(100.0f, 3.7f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -15.0f, 1.0f);

	//jump animation
	animsHumanBody[2].addKeyframe(0.0f, 3.7f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanBody[2].addKeyframe(100.0f, 3.7f, -0.0f, 0.0f, 45.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	//double jump , now a stomp at time == 100
	animsHumanBody[3].addKeyframe(0.0f, 3.7f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanBody[3].addKeyframe(100.0f, 3.7f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	//triple jump animation
	animsHumanBody[4].addKeyframe(0.0f, 3.7f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanBody[4].addKeyframe(100.0f, 3.7f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -720.0f, 1.0f);

	//side flip animation
	animsHumanBody[5].addKeyframe(0.0f, 3.7f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanBody[5].addKeyframe(100.0f, 3.7f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -360.0f, 1.0f);

	//dive animation
	animsHumanBody[6].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanBody[6].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	//rollout animation
	animsHumanBody[7].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 45.0f, 1.0f);
	animsHumanBody[7].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 45.0f, 1.0f);

	//skid animation
	animsHumanBody[8].addKeyframe(0.0f, 3.7f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanBody[8].addKeyframe(100.0f, 3.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	//ground pound animation
	animsHumanBody[9].addKeyframe(0.0f, 1.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanBody[9].addKeyframe(100.0f, 1.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	
	//long jump animation
	animsHumanBody[10].addKeyframe(0.0f, 3.7f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanBody[10].addKeyframe(100.0f, 3.7f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	//long jump animation
	animsHumanBody[11].addKeyframe(0.0f, 1.0f, -0.0f, 0.0f, 180.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanBody[11].addKeyframe(100.0f, 1.0f, -0.0f, 0.0f, 180.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	//crouch animation
	animsHumanBody[12].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -30.0f, 1.0f);
	animsHumanBody[12].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -30.0f, 1.0f);

	//high jump animation
	animsHumanBody[13].addKeyframe(0.0f, 2.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanBody[13].addKeyframe(100.0f, 2.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	//dab animation
	animsHumanBody[14].addKeyframe(0.0f,   3.54f,   0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanBody[14].addKeyframe(100.0f, 3.0385f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	//swim animation
	animsHumanBody[15].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanBody[15].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);

	//swim stroke animation
	animsHumanBody[16].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanBody[16].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);

	//t pose animation
	animsHumanBody[17].addKeyframe(0.0f, 4.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanBody[17].addKeyframe(100.0f, 4.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);




	animsHumanHead[0].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanHead[0].addKeyframe(33.0f, 0.0f, -0.0f, 0.0f, 60.0f, 0.0f, 0.0f, 10.0f, 1.0f);
	animsHumanHead[0].addKeyframe(66.0f, 0.0f, -0.0f, 0.0f, -60.0f, 0.0f, 0.0f, 10.0f, 1.0f);
	animsHumanHead[0].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanHead[1].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20.0f, 1.0f);
	animsHumanHead[1].addKeyframe(25.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15.0f, 1.0f);
	animsHumanHead[1].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20.0f, 1.0f);
	animsHumanHead[1].addKeyframe(75.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15.0f, 1.0f);
	animsHumanHead[1].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20.0f, 1.0f);
	animsHumanHead[2].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanHead[2].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -40.0f, 0.0f, 0.0f, 20.0f, 1.0f);
	animsHumanHead[3].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20.0f, 1.0f);
	animsHumanHead[3].addKeyframe(75.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 40.0f, 1.0f);
	animsHumanHead[3].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -45.0f, 1.0f);
	animsHumanHead[4].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -30.0f, 1.0f);
	animsHumanHead[4].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20.0f, 1.0f);
	animsHumanHead[5].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -30.0f, 1.0f);
	animsHumanHead[5].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20.0f, 1.0f);
	animsHumanHead[6].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 70.0f, 1.0f);
	animsHumanHead[6].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f, 1.0f);
	animsHumanHead[7].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -30.0f, 1.0f);
	animsHumanHead[7].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -30.0f, 1.0f);
	animsHumanHead[8].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanHead[8].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -20.0f, 1.0f);
	animsHumanHead[9].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -30.0f, 1.0f);
	animsHumanHead[9].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -30.0f, 1.0f);
	animsHumanHead[10].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 1.0f);
	animsHumanHead[10].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -20.0f, 1.0f);
	animsHumanHead[11].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -40.0f, 1.0f);
	animsHumanHead[11].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -40.0f, 1.0f);
	animsHumanHead[12].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 1.0f);
	animsHumanHead[12].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 1.0f);
	animsHumanHead[13].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 45.0f, 1.0f);
	animsHumanHead[13].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 45.0f, 1.0f);
	animsHumanHead[14].addKeyframe(0.0f,   0.0f, 0.0f, 0.0f,  0.0f,  0.0f, 0.0f, 0.0f,   1.0f);
	animsHumanHead[14].addKeyframe(100.0f, 0.0f, 0.0f, 0.0f, -34.1f, 0.0f, 0.0f, -20.9f, 1.0f);
	animsHumanHead[15].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 70.0f, 1.0f);
	animsHumanHead[15].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 70.0f, 1.0f);
	animsHumanHead[16].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 70.0f, 1.0f);
	animsHumanHead[16].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 70.0f, 1.0f);
	animsHumanHead[17].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanHead[17].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	animsHumanLeftHumerus[0].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 110.0f, 0.0f, 0.0f, -25.0f, 1.0f);
	animsHumanLeftHumerus[0].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 100.0f, 0.0f, 0.0f, -35.0f, 1.0f);
	animsHumanLeftHumerus[0].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 110.0f, 0.0f, 0.0f, -25.0f, 1.0f);
	animsHumanLeftHumerus[1].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 165.0f, 0.0f, 0.0f, -25.0f, 1.0f);
	animsHumanLeftHumerus[1].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 80.0f, 0.0f, 0.0f, -55.0f, 1.0f);
	animsHumanLeftHumerus[1].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 165.0f, 0.0f, 0.0f, -25.0f, 1.0f);
	animsHumanLeftHumerus[2].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 90.0f, 0.0f, 0.0f, -50.0f, 1.0f);
	animsHumanLeftHumerus[2].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 90.0f, 0.0f, 0.0f, -80.0f, 1.0f);
	animsHumanLeftHumerus[3].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 90.0f, 0.0f, 0.0f, -75.0f, 1.0f);
	animsHumanLeftHumerus[3].addKeyframe(75.0f, 0.0f, -0.0f, 0.0f, 90.0f, 0.0f, 0.0f, -75.0f, 1.0f);
	animsHumanLeftHumerus[3].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 140.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHumerus[4].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -70.0f, 1.0f);
	animsHumanLeftHumerus[4].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 60.0f, 1.0f);
	animsHumanLeftHumerus[5].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -70.0f, 1.0f);
	animsHumanLeftHumerus[5].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 60.0f, 1.0f);
	animsHumanLeftHumerus[6].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanLeftHumerus[6].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f, 1.0f);
	animsHumanLeftHumerus[7].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, -20.0f, 0.0f, 0.0f, 135.0f, 1.0f);
	animsHumanLeftHumerus[7].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -20.0f, 0.0f, 0.0f, 135.0f, 1.0f);
	animsHumanLeftHumerus[8].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 170.0f, 0.0f, 0.0f, 5.0f, 1.0f);
	animsHumanLeftHumerus[8].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 155.0f, 0.0f, 0.0f, 15.0f, 1.0f);
	animsHumanLeftHumerus[9].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 135.0f, 0.0f, 0.0f, 45.0f, 1.0f);
	animsHumanLeftHumerus[9].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 135.0f, 0.0f, 0.0f, 45.0f, 1.0f);
	animsHumanLeftHumerus[10].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 135.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanLeftHumerus[10].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 20.0f, 0.0f, 0.0f, -20.0f, 1.0f);
	animsHumanLeftHumerus[11].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 10.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanLeftHumerus[11].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 10.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanLeftHumerus[12].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 45.0f, 0.0f, 0.0f, 35.0f, 1.0f);
	animsHumanLeftHumerus[12].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 45.0f, 0.0f, 0.0f, 35.0f, 1.0f);
	animsHumanLeftHumerus[13].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 5.0f, 0.0f, 0.0f, -130.0f, 1.0f);
	animsHumanLeftHumerus[13].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 5.0f, 0.0f, 0.0f, -130.0f, 1.0f);
	animsHumanLeftHumerus[14].addKeyframe(0,   0, 0, 0, 110, 0, 0, -25, 1);
	animsHumanLeftHumerus[14].addKeyframe(100, 0, 0, 0, 100, 0, 0, 25.9f,  1);
	animsHumanLeftHumerus[15].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, -30.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanLeftHumerus[15].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -30.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanLeftHumerus[16].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, -150.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanLeftHumerus[16].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, -30.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanLeftHumerus[16].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -30.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanLeftHumerus[17].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 90.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHumerus[17].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 90.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	animsHumanLeftForearm[0].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, -120.0f, 0.0f, 0.0f, -25.0f, 1.0f);
	animsHumanLeftForearm[0].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, -120.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[0].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -120.0f, 0.0f, 0.0f, -25.0f, 1.0f);
	animsHumanLeftForearm[1].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -20.0f, 1.0f);
	animsHumanLeftForearm[1].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, -80.0f, 0.0f, 0.0f, 90.0f, 1.0f);
	animsHumanLeftForearm[1].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -20.0f, 1.0f);
	animsHumanLeftForearm[2].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[2].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[3].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[3].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[4].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[4].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[5].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[5].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[6].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f, 1.0f);
	animsHumanLeftForearm[6].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[7].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[7].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[8].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[8].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[9].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, -90.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanLeftForearm[9].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -90.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanLeftForearm[10].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[10].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[11].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[11].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[12].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, -20.0f, 0.0f, 0.0f, 20.0f, 1.0f);
	animsHumanLeftForearm[12].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -20.0f, 0.0f, 0.0f, 20.0f, 1.0f);
	animsHumanLeftForearm[13].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[13].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[14].addKeyframe(0,   0, 0, 0, -120, 0, 0, -25,   1);
	animsHumanLeftForearm[14].addKeyframe(100, 0, 0, 0, 0,    0, 0, -2.9f, 1);
	animsHumanLeftForearm[15].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[15].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[16].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[16].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[17].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftForearm[17].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	animsHumanLeftHand[0].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[0].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[1].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[1].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[2].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[2].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[3].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[3].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[4].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[4].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[5].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[5].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[6].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[6].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[7].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[7].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[8].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[8].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[9].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[9].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[10].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[10].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[11].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[11].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[12].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanLeftHand[12].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanLeftHand[13].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[13].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[14].addKeyframe(0,   0, 0, 0, 0, 0, 0, 0, 1);
	animsHumanLeftHand[14].addKeyframe(100, 0, 0, 0, 0, 0, 0, 0, 1);
	animsHumanLeftHand[15].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[15].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[16].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[16].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[17].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftHand[17].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	animsHumanRightHumerus[0].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, -110.0f, 0.0f, 0.0f, -25.0f, 1.0f);
	animsHumanRightHumerus[0].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, -100.0f, 0.0f, 0.0f, -35.0f, 1.0f);
	animsHumanRightHumerus[0].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -110.0f, 0.0f, 0.0f, -25.0f, 1.0f);
	animsHumanRightHumerus[1].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, -80.0f, 0.0f, 0.0f, -55.0f, 1.0f);
	animsHumanRightHumerus[1].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, -165.0f, 0.0f, 0.0f, -25.0f, 1.0f);
	animsHumanRightHumerus[1].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -80.0f, 0.0f, 0.0f, -55.0f, 1.0f);
	animsHumanRightHumerus[2].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, -90.0f, 0.0f, 0.0f, 50.0f, 1.0f);
	animsHumanRightHumerus[2].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -90.0f, 0.0f, 0.0f, 80.0f, 1.0f);
	animsHumanRightHumerus[3].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, -90.0f, 0.0f, 0.0f, -75.0f, 1.0f);
	animsHumanRightHumerus[3].addKeyframe(75.0f, 0.0f, -0.0f, 0.0f, -90.0f, 0.0f, 0.0f, -75.0f, 1.0f);
	animsHumanRightHumerus[3].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -140.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHumerus[4].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -70.0f, 1.0f);
	animsHumanRightHumerus[4].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 60.0f, 1.0f);
	animsHumanRightHumerus[5].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -70.0f, 1.0f);
	animsHumanRightHumerus[5].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 60.0f, 1.0f);
	animsHumanRightHumerus[6].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanRightHumerus[6].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f, 1.0f);
	animsHumanRightHumerus[7].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 20.0f, 0.0f, 0.0f, 135.0f, 1.0f);
	animsHumanRightHumerus[7].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 20.0f, 0.0f, 0.0f, 135.0f, 1.0f);
	animsHumanRightHumerus[8].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, -170.0f, 0.0f, 0.0f, 5.0f, 1.0f);
	animsHumanRightHumerus[8].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -155.0f, 0.0f, 0.0f, 15.0f, 1.0f);
	animsHumanRightHumerus[9].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, -135.0f, 0.0f, 0.0f, 45.0f, 1.0f);
	animsHumanRightHumerus[9].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -135.0f, 0.0f, 0.0f, 45.0f, 1.0f);
	animsHumanRightHumerus[10].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, -135.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanRightHumerus[10].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -20.0f, 0.0f, 0.0f, -20.0f, 1.0f);
	animsHumanRightHumerus[11].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, -10.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanRightHumerus[11].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -10.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanRightHumerus[12].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, -45.0f, 0.0f, 0.0f, 35.0f, 1.0f);
	animsHumanRightHumerus[12].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -45.0f, 0.0f, 0.0f, 35.0f, 1.0f);
	animsHumanRightHumerus[13].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, -5.0f, 0.0f, 0.0f, -130.0f, 1.0f);
	animsHumanRightHumerus[13].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -5.0f, 0.0f, 0.0f, -130.0f, 1.0f);
	animsHumanRightHumerus[14].addKeyframe(0,   0, 0, 0, -110,   0, 0, -25,  1);
	animsHumanRightHumerus[14].addKeyframe(100, 0, 0, 0, -65.3f, 0, 0, 4.5f, 1);
	animsHumanRightHumerus[15].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 30.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanRightHumerus[15].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 30.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanRightHumerus[16].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 150.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanRightHumerus[16].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 30.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanRightHumerus[16].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 30.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanRightHumerus[17].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, -90.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHumerus[17].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -90.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	animsHumanRightForearm[0].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 120.0f, 0.0f, 0.0f, -25.0f, 1.0f);
	animsHumanRightForearm[0].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 120.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[0].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 120.0f, 0.0f, 0.0f, -25.0f, 1.0f);
	animsHumanRightForearm[1].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 80.0f, 0.0f, 0.0f, 90.0f, 1.0f);
	animsHumanRightForearm[1].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -20.0f, 1.0f);
	animsHumanRightForearm[1].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 80.0f, 0.0f, 0.0f, 90.0f, 1.0f);
	animsHumanRightForearm[2].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[2].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[3].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[3].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[4].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[4].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[5].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[5].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[6].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f, 1.0f);
	animsHumanRightForearm[6].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[7].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[7].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[8].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[8].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[9].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 90.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanRightForearm[9].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 90.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanRightForearm[10].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[10].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[11].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[11].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[12].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 20.0f, 0.0f, 0.0f, 20.0f, 1.0f);
	animsHumanRightForearm[12].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 20.0f, 0.0f, 0.0f, 20.0f, 1.0f);
	animsHumanRightForearm[13].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[13].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[14].addKeyframe(0,   0, 0, 0, 120,   0, 0, -25,   1);
	animsHumanRightForearm[14].addKeyframe(100, 0, 0, 0, 88.5f, 0, 0, 20.8f, 1);
	animsHumanRightForearm[15].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[15].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[16].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[16].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[17].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightForearm[17].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	animsHumanRightHand[0].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[0].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[1].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[1].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[2].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[2].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[3].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[3].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[4].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[4].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[5].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[5].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[6].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[6].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[7].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[7].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[8].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[8].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[9].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[9].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[10].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[10].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[11].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[11].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[12].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanRightHand[12].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanRightHand[13].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[13].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[14].addKeyframe(0,   0, 0, 0, 0, 0, 0, 0, 1);
	animsHumanRightHand[14].addKeyframe(100, 0, 0, 0, 0, 0, 0, 0, 1);
	animsHumanRightHand[15].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[15].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[16].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[16].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[17].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightHand[17].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	animsHumanLeftThigh[0].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 50.0f, 0.0f, 0.0f, -55.0f, 1.0f);
	animsHumanLeftThigh[0].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 50.0f, 0.0f, 0.0f, -70.0f, 1.0f);
	animsHumanLeftThigh[0].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 50.0f, 0.0f, 0.0f, -55.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(5.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(10.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -50.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(15.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -55.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(20.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -60.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(25.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(30.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -100.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(35.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -120.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(40.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -130.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(45.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -130.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -135.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -135.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(55.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -130.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(60.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -125.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(65.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -115.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(70.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -70.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(75.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(80.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(85.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(90.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 1.0f);
	animsHumanLeftThigh[1].addKeyframe(95.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 12.0f, 1.0f);
	animsHumanLeftThigh[2].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftThigh[2].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -20.0f, 0.0f, 0.0f, 20.0f, 1.0f);
	animsHumanLeftThigh[3].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -80.0f, 1.0f);
	animsHumanLeftThigh[3].addKeyframe(75.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -80.0f, 1.0f);
	animsHumanLeftThigh[3].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -45.0f, 1.0f);
	animsHumanLeftThigh[4].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 45.0f, 1.0f);
	animsHumanLeftThigh[4].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanLeftThigh[5].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 45.0f, 1.0f);
	animsHumanLeftThigh[5].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanLeftThigh[6].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -45.0f, 1.0f);
	animsHumanLeftThigh[6].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanLeftThigh[7].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanLeftThigh[7].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanLeftThigh[8].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -45.0f, 1.0f);
	animsHumanLeftThigh[8].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanLeftThigh[9].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20.0f, 1.0f);
	animsHumanLeftThigh[9].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20.0f, 1.0f);
	animsHumanLeftThigh[10].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanLeftThigh[10].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -30.0f, 1.0f);
	animsHumanLeftThigh[11].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftThigh[11].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftThigh[12].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 20.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftThigh[12].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 20.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftThigh[13].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -130.0f, 1.0f);
	animsHumanLeftThigh[13].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -130.0f, 1.0f);
	animsHumanLeftThigh[14].addKeyframe(0,   0, 0, 0, 50, 0, 0, -55,    1);
	animsHumanLeftThigh[14].addKeyframe(100, 0, 0, 0, 50, 0, 0, -37.2f, 1);
	animsHumanLeftThigh[15].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -70.0f, 1.0f);
	animsHumanLeftThigh[15].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -110.0f, 1.0f);
	animsHumanLeftThigh[15].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -70.0f, 1.0f);
	animsHumanLeftThigh[16].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -70.0f, 1.0f);
	animsHumanLeftThigh[16].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -110.0f, 1.0f);
	animsHumanLeftThigh[16].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -110.0f, 1.0f);
	animsHumanLeftThigh[17].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanLeftThigh[17].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);

	animsHumanLeftShin[0].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -70.0f, 1.0f);
	animsHumanLeftShin[0].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -40.0f, 1.0f);
	animsHumanLeftShin[0].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -70.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -40.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(5.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -30.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(10.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -20.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(15.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -17.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(20.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -17.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(25.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -5.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(30.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(35.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(40.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(45.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -15.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -20.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -20.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(55.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -25.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(60.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -30.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(65.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -45.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(70.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(75.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -125.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(80.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -140.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(85.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -135.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(90.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -115.0f, 1.0f);
	animsHumanLeftShin[1].addKeyframe(95.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -80.0f, 1.0f);
	animsHumanLeftShin[2].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanLeftShin[2].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanLeftShin[3].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -20.0f, 1.0f);
	animsHumanLeftShin[3].addKeyframe(75.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -20.0f, 1.0f);
	animsHumanLeftShin[3].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanLeftShin[4].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -130.0f, 1.0f);
	animsHumanLeftShin[4].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftShin[5].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -130.0f, 1.0f);
	animsHumanLeftShin[5].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftShin[6].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanLeftShin[6].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftShin[7].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftShin[7].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftShin[8].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftShin[8].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -60.0f, 1.0f);
	animsHumanLeftShin[9].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanLeftShin[9].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanLeftShin[10].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanLeftShin[10].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanLeftShin[11].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftShin[11].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftShin[12].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -120.0f, 1.0f);
	animsHumanLeftShin[12].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -120.0f, 1.0f);
	animsHumanLeftShin[13].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftShin[13].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftShin[14].addKeyframe(0,   0, 0, 0, 0, 0, 0, -70,   1);
	animsHumanLeftShin[14].addKeyframe(100, 0, 0, 0, 0, 0, 0, -1.4f, 1);
	animsHumanLeftShin[15].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftShin[15].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftShin[16].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftShin[16].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftShin[17].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftShin[17].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	animsHumanLeftFoot[0].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 125.0f, 1.0f);
	animsHumanLeftFoot[0].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 110.0f, 1.0f);
	animsHumanLeftFoot[0].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 125.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 80.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(5.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 80.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(10.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 95.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(15.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 95.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(20.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(25.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 80.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(30.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 60.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(35.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(40.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(45.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(55.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(60.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(65.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 45.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(70.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(75.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(80.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(85.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(90.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 120.0f, 1.0f);
	animsHumanLeftFoot[1].addKeyframe(95.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 115.0f, 1.0f);
	animsHumanLeftFoot[2].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 45.0f, 1.0f);
	animsHumanLeftFoot[2].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 45.0f, 1.0f);
	animsHumanLeftFoot[3].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f, 1.0f);
	animsHumanLeftFoot[3].addKeyframe(75.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f, 1.0f);
	animsHumanLeftFoot[3].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f, 1.0f);
	animsHumanLeftFoot[4].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftFoot[4].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanLeftFoot[5].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftFoot[5].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanLeftFoot[6].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 45.0f, 1.0f);
	animsHumanLeftFoot[6].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanLeftFoot[7].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 70.0f, 1.0f);
	animsHumanLeftFoot[7].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 70.0f, 1.0f);
	animsHumanLeftFoot[8].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f, 1.0f);
	animsHumanLeftFoot[8].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 120.0f, 1.0f);
	animsHumanLeftFoot[9].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 60.0f, 1.0f);
	animsHumanLeftFoot[9].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 60.0f, 1.0f);
	animsHumanLeftFoot[10].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f, 1.0f);
	animsHumanLeftFoot[10].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 80.0f, 1.0f);
	animsHumanLeftFoot[11].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 120.0f, 1.0f);
	animsHumanLeftFoot[11].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 120.0f, 1.0f);
	animsHumanLeftFoot[12].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 150.0f, 1.0f);
	animsHumanLeftFoot[12].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 150.0f, 1.0f);
	animsHumanLeftFoot[13].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanLeftFoot[13].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanLeftFoot[14].addKeyframe(0,   0, 0, 0, 0, 0, 0, 125, 1);
	animsHumanLeftFoot[14].addKeyframe(100, 0, 0, 0, 0, 0, 0, 39,  1);
	animsHumanLeftFoot[15].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanLeftFoot[15].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanLeftFoot[16].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanLeftFoot[16].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanLeftFoot[17].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f, 1.0f);
	animsHumanLeftFoot[17].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f, 1.0f);

	animsHumanRightThigh[0].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, -50.0f, 0.0f, 0.0f, -55.0f, 1.0f);
	animsHumanRightThigh[0].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, -50.0f, 0.0f, 0.0f, -70.0f, 1.0f);
	animsHumanRightThigh[0].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -50.0f, 0.0f, 0.0f, -55.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -135.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(5.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -130.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(10.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -125.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(15.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -115.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(20.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -70.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(25.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(30.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(35.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(40.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(45.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 12.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(55.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(60.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -50.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(65.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -55.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(70.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -60.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(75.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(80.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -100.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(85.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -120.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(90.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -130.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(95.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -130.0f, 1.0f);
	animsHumanRightThigh[1].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -135.0f, 1.0f);
	animsHumanRightThigh[2].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, -20.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanRightThigh[2].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -50.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanRightThigh[3].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -95.0f, 1.0f);
	animsHumanRightThigh[3].addKeyframe(75.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -95.0f, 1.0f);
	animsHumanRightThigh[3].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -80.0f, 1.0f);
	animsHumanRightThigh[4].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 45.0f, 1.0f);
	animsHumanRightThigh[4].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanRightThigh[5].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 45.0f, 1.0f);
	animsHumanRightThigh[5].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanRightThigh[6].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -45.0f, 1.0f);
	animsHumanRightThigh[6].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanRightThigh[7].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanRightThigh[7].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanRightThigh[8].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -45.0f, 1.0f);
	animsHumanRightThigh[8].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanRightThigh[9].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20.0f, 1.0f);
	animsHumanRightThigh[9].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 20.0f, 1.0f);
	animsHumanRightThigh[10].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanRightThigh[10].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -30.0f, 1.0f);
	animsHumanRightThigh[11].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightThigh[11].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightThigh[12].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, -20.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightThigh[12].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, -20.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightThigh[13].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -130.0f, 1.0f);
	animsHumanRightThigh[13].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -130.0f, 1.0f);
	animsHumanRightThigh[14].addKeyframe(0,   0, 0, 0, -50, 0, 0, -55,    1);
	animsHumanRightThigh[14].addKeyframe(100, 0, 0, 0, -50, 0, 0, -22.3f, 1);
	animsHumanRightThigh[15].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -110.0f, 1.0f);
	animsHumanRightThigh[15].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -70.0f, 1.0f);
	animsHumanRightThigh[15].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -110.0f, 1.0f);
	animsHumanRightThigh[16].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -70.0f, 1.0f);
	animsHumanRightThigh[16].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -110.0f, 1.0f);
	animsHumanRightThigh[16].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -110.0f, 1.0f);
	animsHumanRightThigh[17].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanRightThigh[17].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);

	animsHumanRightShin[0].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -70.0f, 1.0f);
	animsHumanRightShin[0].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -40.0f, 1.0f);
	animsHumanRightShin[0].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -70.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -20.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(5.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -25.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(10.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -30.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(15.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -45.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(20.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(25.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -125.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(30.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -140.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(35.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -135.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(40.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -115.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(45.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -80.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -40.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(55.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -30.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(60.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -20.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(65.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -17.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(70.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -17.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(75.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -5.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(80.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(85.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(90.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(95.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -15.0f, 1.0f);
	animsHumanRightShin[1].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -20.0f, 1.0f);
	animsHumanRightShin[2].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[2].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[3].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[3].addKeyframe(75.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[3].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[4].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -130.0f, 1.0f);
	animsHumanRightShin[4].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[5].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -130.0f, 1.0f);
	animsHumanRightShin[5].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[6].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -90.0f, 1.0f);
	animsHumanRightShin[6].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[7].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[7].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[8].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[8].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -60.0f, 1.0f);
	animsHumanRightShin[9].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanRightShin[9].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanRightShin[10].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanRightShin[10].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanRightShin[11].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[11].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[12].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -120.0f, 1.0f);
	animsHumanRightShin[12].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -120.0f, 1.0f);
	animsHumanRightShin[13].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[13].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[14].addKeyframe(0,   0, 0, 0, 0, 0, 0, -70,    1);
	animsHumanRightShin[14].addKeyframe(100, 0, 0, 0, 0, 0, 0, -94.4f, 1);
	animsHumanRightShin[15].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[15].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[16].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[16].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[17].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightShin[17].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

	animsHumanRightFoot[0].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 125.0f, 1.0f);
	animsHumanRightFoot[0].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 110.0f, 1.0f);
	animsHumanRightFoot[0].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 125.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(5.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 15.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(10.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(15.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 45.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(20.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(25.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(30.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(35.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(40.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 120.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(45.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 115.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(50.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 80.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(55.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 80.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(60.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 95.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(65.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 95.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(70.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(75.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 80.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(80.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 60.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(85.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(90.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(95.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightFoot[1].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	animsHumanRightFoot[2].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanRightFoot[2].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanRightFoot[3].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanRightFoot[3].addKeyframe(75.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanRightFoot[3].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanRightFoot[4].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightFoot[4].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanRightFoot[5].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightFoot[5].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanRightFoot[6].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 45.0f, 1.0f);
	animsHumanRightFoot[6].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	animsHumanRightFoot[7].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 70.0f, 1.0f);
	animsHumanRightFoot[7].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 70.0f, 1.0f);
	animsHumanRightFoot[8].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f, 1.0f);
	animsHumanRightFoot[8].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 120.0f, 1.0f);
	animsHumanRightFoot[9].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 60.0f, 1.0f);
	animsHumanRightFoot[9].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 60.0f, 1.0f);
	animsHumanRightFoot[10].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f, 1.0f);
	animsHumanRightFoot[10].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 80.0f, 1.0f);
	animsHumanRightFoot[11].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 120.0f, 1.0f);
	animsHumanRightFoot[11].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 120.0f, 1.0f);
	animsHumanRightFoot[12].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 150.0f, 1.0f);
	animsHumanRightFoot[12].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 150.0f, 1.0f);
	animsHumanRightFoot[13].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanRightFoot[13].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanRightFoot[14].addKeyframe(0,   0, 0, 0, 0, 0, 0, 125, 1);
	animsHumanRightFoot[14].addKeyframe(100, 0, 0, 0, 0, 0, 0, 117, 1);
	animsHumanRightFoot[15].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanRightFoot[15].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanRightFoot[16].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanRightFoot[16].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 30.0f, 1.0f);
	animsHumanRightFoot[17].addKeyframe(0.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f, 1.0f);
	animsHumanRightFoot[17].addKeyframe(100.0f, 0.0f, -0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f, 1.0f);
}

void AnimationResources::assignAnimationsHuman(Body* body, Limb* head,
	Limb* leftHumerus, Limb* leftForearm, Limb* leftHand,
	Limb* rightHumerus, Limb* rightForearm, Limb* rightHand,
	Limb* leftThigh, Limb* leftShin, Limb* leftFoot,
	Limb* rightThigh, Limb* rightShin, Limb* rightFoot)
{
	body->animations         = &AnimationResources::animsHumanBody;
	head->animations         = &AnimationResources::animsHumanHead;
	leftHumerus->animations  = &AnimationResources::animsHumanLeftHumerus;
	leftForearm->animations  = &AnimationResources::animsHumanLeftForearm;
	leftHand->animations     = &AnimationResources::animsHumanLeftHand;
	rightHumerus->animations = &AnimationResources::animsHumanRightHumerus;
	rightForearm->animations = &AnimationResources::animsHumanRightForearm;
	rightHand->animations    = &AnimationResources::animsHumanRightHand;
	leftThigh->animations    = &AnimationResources::animsHumanLeftThigh;
	leftShin->animations     = &AnimationResources::animsHumanLeftShin;
	leftFoot->animations     = &AnimationResources::animsHumanLeftFoot;
	rightThigh->animations   = &AnimationResources::animsHumanRightThigh;
	rightShin->animations    = &AnimationResources::animsHumanRightShin;
	rightFoot->animations    = &AnimationResources::animsHumanRightFoot;
}