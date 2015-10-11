#include "pitch.h"

float getButtonFrequency(int buttonID){
	return OCTAVE(buttonID) * pitch_table[KEY_C][MODE_IONIAN][NOTE(buttonID)];
}
