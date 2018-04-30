#ifndef GUIMANAGER_H
#define GUIMANAGER_H

class FontType;
class GUIText;
class GuiTexture;

#include <list>

class GuiManager
{
private:
	static GUIText* textTimer;

	static bool timerIsRunning;
	static int centiseconds;
	static int seconds;
	static int minutes;

	static GUIText* textRings;

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

	//Total time on timer in seconds
	static float getTotalTimer();

	static void addGuiToRender(GuiTexture* newImage);

	static void removeGui(GuiTexture* newImage);

	static void clearGuisToRender();
};

#endif