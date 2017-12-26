#include "PomodoroApp.h"

extern MicroBit uBit;
extern MicroBitDisplay display;

extern PomodoroApp app;

MicroBitImage statusImage(5, 5);

void onTiltUp(MicroBitEvent) {
	if(app.state != AppState::Running) {
		return;
	}
	statusImage.clear();
	for(int i = 0; i < app.minutesLeft; i++) {
		statusImage.setPixelValue((i % 10) % 5, (int)(i / 5), 1);
	}
	display.print(statusImage);
	uBit.sleep(ONE_SECOND * 3);
	display.clear();
}

void onQuit(MicroBitEvent) {
	app.state = AppState::Quitting;
}

void onShake(MicroBitEvent) {
	app.minutesLeft = 0;
}

void onButtonClick(MicroBitEvent ev) {
	uBit.messageBus.ignore(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonClick);
	uBit.messageBus.ignore(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButtonClick);
	display.stopAnimation();

	app.minutesLeft = ev.source == MICROBIT_ID_BUTTON_A ? SHORT_BREAK_MINS_LENGTH : LONG_BREAK_MINS_LENGTH;
	app.state = AppState::OnBreak;
}

void pomodoroMainLoop() {
	while(app.state != AppState::Quitting) {
		switch(app.state) {
			case AppState::Starting:
				display.scroll("Starting...");
				display.print("321");
				app.minutesLeft = POMODORO_INTERVAL_LENGTH_MINS;
				app.state = AppState::Running;
				break;
			case AppState::Running:
				display.scroll(app.minutesLeft);
				app.minutesLeft--;
				uBit.sleep(ONE_MINUTE);
				if(app.minutesLeft <= 0) {
					app.state = AppState::Waiting;
				}
				break;
			case AppState::Waiting:
				uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonClick);
				uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButtonClick);
				display.scroll("Short or long break? A/B");
				break;
			case AppState::OnBreak:
				display.scroll(app.minutesLeft);
				app.minutesLeft--;
				uBit.sleep(ONE_MINUTE);
				if(app.minutesLeft <= 0) {
					app.state = AppState::Starting;
				}
				break;
			case AppState::Quitting: break;
		}
	}
}

