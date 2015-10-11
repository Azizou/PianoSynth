/*
 * pitch.c
 *
 *  Created on: Sep 22, 2015
 *      Author: Poon Donohoe
 */
#include "pitch.h"

// TODO: Implement variable keys and modes
float getButtonFrequency(int buttonID){
	return OCTAVE(buttonID) * pitch_table[KEY_C][MODE_IONIAN][NOTE(buttonID)];
}