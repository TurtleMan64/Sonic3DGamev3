#ifndef INPUT_H
#define INPUT_H

struct InputStruct
{
	volatile int uniqueVar;

	volatile float INPUT_X;
	volatile float INPUT_Y;
	volatile float INPUT_X2;
	volatile float INPUT_Y2;

	volatile bool INPUT_JUMP;
	volatile bool INPUT_ACTION;
	volatile bool INPUT_ACTION2;
	volatile bool INPUT_SHOULDER;
	volatile bool INPUT_SELECT;
	volatile bool INPUT_SPECIAL;
	volatile bool INPUT_START;
	volatile bool INPUT_GRAVE;
	volatile bool INPUT_SEMICOLON;
	volatile bool INPUT_APOSTROPHE;

	volatile bool INPUT_PREVIOUS_JUMP;
	volatile bool INPUT_PREVIOUS_ACTION;
	volatile bool INPUT_PREVIOUS_ACTION2;
	volatile bool INPUT_PREVIOUS_SHOULDER;
	volatile bool INPUT_PREVIOUS_SELECT;
	volatile bool INPUT_PREVIOUS_SPECIAL;
	volatile bool INPUT_PREVIOUS_START;
	volatile bool INPUT_PREVIOUS_GRAVE;
	volatile bool INPUT_PREVIOUS_SEMICOLON;
	volatile bool INPUT_PREVIOUS_APOSTROPHE;

	volatile int MENU_X;
	volatile int MENU_Y;

	volatile float INPUT_ZOOM;

	volatile bool tabInput;
	volatile bool tabInputPrevious;

	volatile int approxXLeft;
	volatile int approxXLeftPrevious;
	volatile int approxYLeft;
	volatile int approxYLeftPrevious;
};

void Input_pollInputs();
void Input_init();
#endif