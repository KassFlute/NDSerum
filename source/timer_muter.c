#include "timer_muter.h"

int gate_speed; // Define the speed of the gate (in pixels because of the fader length: 0-95)
int gate_enabled;

//Interrupt handler of TIMER1
void Timer1_ISR() {
    printf("MUTER");
    // gate the sound
    PauseResumeSound();
    SetMuteButton(!IsPlaying());
}

void InitTimer() {

    gate_speed = 20;
    gate_enabled = 0;
    int gate_frequency = (int)((gate_speed * (40 - 1)) / 95) + 1;

    // Timer 1 setup (0 is used by the sound)
    TIMER_CR(1) = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
    TIMER_DATA(1) = TIMER_FREQ_1024(gate_frequency);

    // Interupt setup
    irqSet(IRQ_TIMER1, Timer1_ISR);

    if (gate_enabled) irqEnable(IRQ_TIMER1);
}

void EnableDisableMuter() {

    SetGate(!IsGated());
}

void SetGate(int enabled) {

    if (gate_enabled == enabled) return; // Nothing to change

    if (enabled) {
        // Enable the gate
        irqEnable(IRQ_TIMER1);
        gate_enabled = 1;
    } else {
        // Disable the gate
        irqDisable(IRQ_TIMER1);
        gate_enabled = 0;
        PauseSound();
        SetMuteButton(1);
    }
}

void SetGateSpeed(int speed) {

    gate_speed = MIN(MAX(speed, 0), 95);
    int gate_frequency = (int)((gate_speed * (40 - 1)) / 95) + 1;
    printf("Gate interval: %d\n", gate_frequency);
    TIMER_DATA(1) = TIMER_FREQ_1024(gate_frequency); // Set the new frequency

    // Apply the new frequency immediately
    TIMER_CR(1) = TIMER_CR(1) & ~TIMER_ENABLE;
    TIMER_CR(1) = TIMER_CR(1) | TIMER_ENABLE;
}

int GetGateSpeed() {

    return gate_speed;
}

int IsGated() {

    return gate_enabled;
}
