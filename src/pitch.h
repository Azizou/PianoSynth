/*
 * pitch.h
 *
 *  Created on: Sep 22, 2015
 *      Author: Poon Donohoe
 */

#ifndef PITCH_H_
#define PITCH_H_
//#include "main.h"


float getButtonFrequency(int buttonID);


#define 	KEY_C				0
#define 	KEY_D				1
#define 	KEY_E				2
#define 	KEY_F				3
#define 	KEY_G				4
#define 	KEY_A				5
#define 	KEY_B				6

#define		MODE_IONIAN			0
#define		MODE_DORIAN			1
#define		MODE_PHRYGIAN		2
#define		MODE_LYDIAN			3
#define		MODE_MIXOLYDIAN		4
#define		MODE_AEOLIAN		5
#define		MODE_LOCRIAN		6


#define 	OCTAVE_MULTIPLIER 	4

// Macros for indexing the pitch table with more than 7 buttons
#define 	OCTAVE(x) 	((int)(x/7) + 1 + OCTAVE_MULTIPLIER)
#define 	NOTE(x) 	(x%7)

// Fundamental frequency definitions
#define 	C0 			16.35f
#define 	C0sharp		17.32f
#define 	D0			18.35f
#define 	D0sharp		19.45f
#define 	E0			20.60f
#define 	F0			21.83f
#define 	F0sharp		23.12f
#define 	G0			24.50f
#define 	G0sharp 	25.96f
#define 	A0			27.50f
#define 	A0sharp 	29.14f
#define 	B0			30.87f

static float pitch_table[7][7][7]=		// Indexed by OCTAVE(button_index) * pitch_table[KEY][MODE][NOTE(button_index)]
{
					// Key of C
	{{C0, D0, E0, F0, G0, A0, B0							},	// Ionian  		1st Mode
	 {C0, D0, D0sharp, F0, G0, A0, A0sharp					},	// Dorian  		2nd Mode
	 {C0, C0sharp, D0sharp, F0, G0, G0sharp, A0sharp		},	// Phrygian  	3rd Mode
	 {C0, D0, E0, F0sharp, G0, A0, B0						},	// Lydian		4th Mode
	 {C0, D0, E0, F0, G0, A0, A0sharp						},	// Mixolydian	5th Mode
	 {C0, D0, D0sharp, F0, G0, G0sharp, A0sharp				},	// Aeolian		6th Mode
	 {C0, C0sharp, D0sharp, F0, F0sharp, G0sharp, A0sharp	}},	// Locrian		7th Mode
					// Key of D 
	{{D0, E0, F0sharp, G0, A0, B0, C0sharp					},	// Ionian  		1st Mode
	 {D0, E0, F0, G0, A0, B0, C0							},	// Dorian  		2nd Mode
	 {D0, D0sharp, F0, G0, A0, A0sharp, C0					},	// Phrygian  	3rd Mode
	 {D0, E0, F0sharp, G0sharp, A0, B0, C0sharp				},	// Lydian		4th Mode
	 {D0, E0, F0sharp, G0, A0, B0, C0						},	// Mixolydian	5th Mode
	 {D0, E0, F0, G0, A0, A0sharp, C0						},	// Aeolian		6th Mode
	 {D0, D0sharp, F0, G0, G0sharp, A0sharp, C0				}},	// Locrian		7th Mode
					// Key of E
	{{E0, F0sharp, G0sharp, A0, B0, C0sharp, D0sharp		},	// Ionian  		1st Mode
	 {E0, F0sharp, G0, A0, B0, C0sharp, E0					},	// Dorian  		2nd Mode
	 {E0, F0, G0, A0, B0, C0, D0							},	// Phrygian  	3rd Mode
	 {E0, F0sharp, G0sharp, A0sharp, B0, C0sharp, D0sharp	},	// Lydian		4th Mode
	 {E0, F0sharp, G0sharp, A0, B0, C0sharp, D0				},	// Mixolydian	5th Mode
	 {E0, F0sharp, G0, A0, B0, C0, D0						},	// Aeolian		6th Mode
	 {E0, F0, G0, A0, A0sharp, C0, D0						}},	// Locrian		7th Mode
					// Key of F
	{{F0, G0, A0, A0sharp, C0, D0, E0						},	// Ionian  		1st Mode
	 {F0, G0, G0sharp, A0sharp, C0, D0, D0sharp				},	// Dorian  		2nd Mode
	 {F0, F0sharp, G0sharp, A0sharp, C0, C0sharp, D0sharp	},	// Phrygian  	3rd Mode
	 {F0, G0, A0, B0, C0, D0, E0							},	// Lydian		4th Mode
	 {F0, G0, A0, A0sharp, C0, D0, D0sharp					},	// Mixolydian	5th Mode
	 {F0, G0, G0sharp, A0sharp, C0, C0sharp, D0sharp		},	// Aeolian		6th Mode
	 {F0, F0sharp, G0sharp, A0sharp, B0, C0sharp, D0sharp	}},	// Locrian		7th Mode
					// Key of G
	{{G0, A0, B0, C0, D0, E0, F0sharp						},	// Ionian  		1st Mode
	 {G0, A0, A0sharp, C0, D0, E0, F0						},	// Dorian  		2nd Mode
	 {G0, G0sharp, A0sharp, C0, D0, D0sharp, F0				},	// Phrygian  	3rd Mode
	 {G0, A0, B0, C0sharp, D0, E0, F0sharp					},	// Lydian		4th Mode
	 {G0, A0, B0, C0, D0, E0, F0							},	// Mixolydian	5th Mode
	 {G0, A0, A0sharp, C0, D0, D0sharp						},	// Aeolian		6th Mode
	 {G0, G0sharp, A0sharp, C0, C0sharp, D0sharp, F0		}},	// Locrian		7th Mode
					// Key of A
	{{A0, B0, C0sharp, D0, E0, F0sharp, G0sharp				},	// Ionian  		1st Mode
	 {A0, B0, C0, D0, E0, F0sharp, G0						},	// Dorian  		2nd Mode
	 {A0, A0sharp, C0, D0, E0, F0, G0						},	// Phrygian  	3rd Mode
	 {A0, B0, C0sharp, D0sharp, E0, F0sharp, G0sharp		},	// Lydian		4th Mode
	 {A0, B0, C0sharp, D0, E0, F0sharp, G0					},	// Mixolydian	5th Mode
	 {A0, B0, C0, D0, E0, F0, G0							},	// Aeolian		6th Mode
	 {A0, A0sharp, C0, D0, D0sharp, G0						}},	// Locrian		7th Mode
					// Key of B
	{{B0, C0sharp, D0sharp, E0, F0sharp, G0sharp, A0sharp	},	// Ionian  		1st Mode
	 {B0, C0sharp, D0, E0, F0sharp, G0sharp, A0				},	// Dorian  		2nd Mode
	 {B0, C0, D0, E0, F0sharp, G0, A0						},	// Phrygian  	3rd Mode
	 {B0, C0sharp, D0sharp, F0, F0sharp, G0sharp, A0sharp	},	// Lydian		4th Mode
	 {B0, C0sharp, D0sharp, E0, F0sharp, G0sharp, A0		},	// Mixolydian	5th Mode
	 {B0, C0sharp, D0, E0, F0sharp, G0, A0					},	// Aeolian		6th Mode
	 {B0, C0, D0, E0, F0, G0, A0							}},	// Locrian		7th Mode
};

#endif /* PITCH_H_ */
