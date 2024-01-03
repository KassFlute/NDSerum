#include <nds.h>

extern int16_t main_buffer[4800]; // main buffer storing the sound (to be copied to the stream buffer)
extern int main_buffer_length;    // à passer aux méthodes de remplissage pour quelle disent combien elles ont écrit (en bytes)