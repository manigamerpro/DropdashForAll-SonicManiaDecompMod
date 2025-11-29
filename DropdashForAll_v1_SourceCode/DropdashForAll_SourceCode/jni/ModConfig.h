#ifndef MOD_CONFIG_H
#define MOD_CONFIG_H

#include "GameAPI/Game.h"

/* ======================================== */
/* CONFIGURATION STRUCTURE                  */
/* ======================================== */

typedef struct {
    bool32 allowDropdashTails;
    bool32 allowDropdashKnuckles;
#if MANIA_USE_PLUS
    bool32 allowDropdashMighty;
    bool32 allowDropdashRay;
    bool32 mightyHammerDash;
#endif
} DropdashConfig;

/* ======================================== */
/* GLOBAL CONFIGURATION INSTANCE            */
/* ======================================== */

extern DropdashConfig gDropdashConfig;

/* ======================================== */
/* CONFIGURATION FUNCTIONS                  */
/* ======================================== */

void DropdashConfig_InitDefaults(void);
void DropdashConfig_LoadFromSettings(void);

#endif