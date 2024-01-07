#include "timer_muter.h"

int gate_speed; // Define the speed of the gate (in pixels because of the fader length: 0-95)
int muter_enabled;

void Timer1_ISR() {
    if (muter_enabled) {
        printf("MUTER");
        // Mute the sound
        PauseResumeSound();
        SetMuteButton(!IsPlaying());
    }
}

void InitTimer() {
    /*
        * Initialize the timer
     */
    gate_speed = 20;
    muter_enabled = 0;
    int gate_frequency = (int)((gate_speed * (100 - 1)) / 95) + 1;

    // Timer 0 setup
    TIMER_CR(1) = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
    TIMER_DATA(1) = TIMER_FREQ_1024(gate_frequency);

    // Interupt setup
    irqSet(IRQ_TIMER1, Timer1_ISR);
    irqEnable(IRQ_TIMER1);
}

void EnableDisableMuter() {
    /*
        * Enable or disable the muter
     */
    if (muter_enabled) {
        // Disable the muter
        muter_enabled = 0;
        PauseSound();
        SetMuteButton(1);
    } else {
        // Enable the muter
        muter_enabled = 1;
    }
}

void SetGate(int enabled) {
    /*
        * Enable or disable the gate
        * @param enabled : 1 to enable the gate, 0 to disable it
     */
    if (enabled) {
        // Enable the gate
        muter_enabled = 1;
    } else {
        // Disable the gate
        muter_enabled = 0;
        PauseSound();
        SetMuteButton(1);
    }
}

void SetGateSpeed(int speed) {
    /*
        * Set the speed of the gate
        * @param speed : the new speed of the gate
     */
    gate_speed = MIN(MAX(speed, 0), 95);
    int gate_frequency = (int)((gate_speed * (100 - 1)) / 95) + 1;
    printf("Gate interval: %d\n", gate_frequency);
    TIMER_DATA(1) = TIMER_FREQ_1024(gate_frequency);
}

int GetGateSpeed() {
    /*
        * Return the speed of the gate
        * @return the speed of the gate
     */
    return gate_speed;
}

int IsGated() {
    /*
        * Return if the muter is enabled
        * @return 1 if the muter is enabled, 0 otherwise
     */
    return muter_enabled;
}