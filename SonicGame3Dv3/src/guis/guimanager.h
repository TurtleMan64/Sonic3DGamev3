#ifndef GUIMANAGER_H
#define GUIMANAGER_H

class FontType;
class GUIText;
class GuiTexture;

#include <list>

class GuiManager
{
private:
	//static GUIText* textTimer;
	static GUIText* timerColon;
	static GUIText* timerPeriod;
	static GUIText* timerMin1[10];
	static GUIText* timerMin2[10];
	static GUIText* timerSec1[10];
	static GUIText* timerSec2[10];
	static GUIText* timerCen1[10];
	static GUIText* timerCen2[10];

	static bool timerIsRunning;
	static int centiseconds;
	static int seconds;
	static int minutes;

	static GUIText* textRings;
	static GUIText* textScore;
	static GUIText* textLives;

	static int previousRings;
	static int previousScore;
	static int previousLives;

	static std::list<GuiTexture*> guisToRender;

	static GUIText* textHorVel;
	static GUIText* textVerVel;
	static GUIText* textTotalVel;
	static GUIText* textHoverCount;
	static GUIText* textStoredSpindashSpeed;

	static GUIText* textA;
	static GUIText* textB;
	static GUIText* textX;
	static GUIText* textY;

	static float horVel;
	static float verVel;
	static float totalVel;
	static int hoverCount;
	static float storedSpindashSpeed;

	static void setTimerInvisible();

public:
	static FontType* fontVip;

	static void init();

	static void refresh();

	static void increaseTimer();

	static void setTimer(int minutes, int seconds, int centiseconds);

	static void startTimer();

	static void stopTimer();

	static int getMinutes();

	static int getSeconds();

	static int getCentiseconds();

	//Total time on timer in seconds
	static float getTotalTimerInSeconds();

	//Total time on timer in frames
	static int getTotalTimerInFrames();

	static void addGuiToRender(GuiTexture* newImage);

	static void removeGui(GuiTexture* newImage);

	static void clearGuisToRender();
};

#endif