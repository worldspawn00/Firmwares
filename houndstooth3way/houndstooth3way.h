#pragma once

#include "quantum.h"

#define LAYOUT( \
	K00, K01, K02, K03, K04, K05, K40, K41, K42, K43, K44, K45, K80, K81, K82, K83, K84, K85,\
	K10, K11, K12, K13, K14, K15, K50, K51, K52, K53, K54, K55, K90, K91, K92, K93, K94, K95,\
	K20, K21, K22, K23, K24, K25, K60, K61, K62, K63, K64, K65, Ka0, Ka1, Ka2, Ka3, Ka4, Ka5,\
	K30, K31, K32, K33, K34, K35, K70, K71, K72, K73, K74, K75, Kb0, Kb1, Kb2, Kb3, Kb4, Kb5 \
) { \
	{ K00,   K01,   K02,   K03,   K04,   K05 }, \
	{ K10,   K11,   K12,   K13,   K14,   K15 }, \
	{ K20,   K21,   K22,   K23,   K24,   K25 }, \
	{ K30,   K31,   K32,   K33,   K34,   K35 }, \
	{ K40,   K41,   K42,   K43,   K44,   K45 }, \
	{ K50,   K51,   K52,   K53,   K54,   K55 }, \
	{ K60,   K61,   K62,   K63,   K64,   K65 }, \
	{ K70,   K71,   K72,   K73,   K74,   K75 }, \
	{ K80,   K81,   K82,   K83,   K84,   K85 }, \
	{ K90,   K91,   K92,   K93,   K94,   K95 }, \
	{ Ka0,   Ka1,   Ka2,   Ka3,   Ka4,   Ka5 }, \
	{ Kb0,   Kb1,   Kb2,   Kb3,   Kb4,   Kb5 }  \
}

