#include "timer_muter.h"

int muter_interval;
int muter_enabled;

void Timer1_ISR() {
    if (muter_enabled) {
        printf("MUTER");
        // Mute the sound
        PauseResumeSound();
    }
}

void InitTimer() {
    /*
        * Initialize the timer
     */
    muter_interval = 1;
    muter_enabled = 0;

    // Timer 0 setup
    TIMER_CR(1) = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
    TIMER_DATA(1) = TIMER_FREQ_1024(muter_interval);

    // Interupt setup
    irqSet(IRQ_TIMER1, Timer1_ISR);
    irqEnable(IRQ_TIMER1);
}

void SetMuteInterval(int interval) {
    /*
        * Set the mute interval
        * @param interval : the new mute interval
     */
    muter_interval = MIN(MAX(interval, 0.5), 10);
}

int GetMuteInterval() {
    /*
        * Return the mute interval
        * @return the mute interval
     */
    return muter_interval;
}

void EnableDisableMuter() {
    /*
        * Enable or disable the muter
     */
    muter_enabled = !muter_enabled;
}
