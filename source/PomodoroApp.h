#pragma once

#include "MicroBit.h"

const int SHORT_BREAK_MINS_LENGTH = 5;
const int LONG_BREAK_MINS_LENGTH = 15;

const int POMODORO_INTERVAL_LENGTH_MINS = 25;

const int ONE_SECOND = 1000;
const int ONE_MINUTE = ONE_SECOND * 60;

enum class AppState {
	Starting,
	Running,
	Waiting,
	OnBreak,
	Quitting
};

struct PomodoroApp {
	AppState state;
	int minutesLeft;
};

void onTiltUp(MicroBitEvent);
void onQuit(MicroBitEvent);
void onShake(MicroBitEvent);
void onButtonClick(MicroBitEvent);
void pomodoroMainLoop();


