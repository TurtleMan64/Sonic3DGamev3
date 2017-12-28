#ifndef GUIMANAGER_H
#define GUIMANAGER_H

class FontType;
class GUIText;


class GuiManager
{
private:
	static GUIText* textTimer;

	static bool timerIsRunning;
	static int centiseconds;
	static int seconds;
	static int minutes;

	static GUIText* textRings;

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
};

#endif