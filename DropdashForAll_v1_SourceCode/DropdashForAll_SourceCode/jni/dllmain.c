#include "GameAPI/Game.h"
#include "Player.h"
#include "ModConfig.h"

/* ======================================== */
/* GLOBAL VARIABLES                         */
/* ======================================== */

ObjectPlayer *Player = NULL;
DropdashConfig gDropdashConfig;

static uint16 sfxDropdashCached = 0;
static uint8 ddPrevDown[PLAYER_COUNT] = { 0 };
static uint8 ddDownBuf[PLAYER_COUNT] = { 0 };
static uint8 ddJumpBuf[PLAYER_COUNT] = { 0 };
static uint8 ddActive[PLAYER_COUNT]  = { 0 };
static uint8 canDropdash[PLAYER_COUNT] = { 0 };

#if MANIA_USE_PLUS
static uint8 mightyHammerTransition[PLAYER_COUNT] = { 0 };
static uint8 mightyShouldHammerdash[PLAYER_COUNT] = { 0 };
static uint8 hammerdashCooldownTimer[PLAYER_COUNT] = { 0 };
#endif

/* ======================================== */
/* FUNCTION POINTERS                        */
/* ======================================== */

StateMachine(Player_Action_Jump) = NULL;
StateMachine(Player_State_Air) = NULL;
StateMachine(Player_State_Ground) = NULL;
StateMachine(Player_Input_P1) = NULL;
StateMachine(Player_Input_P2_Player) = NULL;
StateMachine(Player_State_DropDash) = NULL;

#if MANIA_USE_PLUS
StateMachine(Player_State_MightyHammerDrop) = NULL;
#endif

/* ======================================== */
/* CONFIGURATION FUNCTIONS                  */
/* ======================================== */

void DropdashConfig_InitDefaults(void)
{
    gDropdashConfig.allowDropdashTails    = true;
    gDropdashConfig.allowDropdashKnuckles = true;
#if MANIA_USE_PLUS
    gDropdashConfig.allowDropdashMighty   = true;
    gDropdashConfig.allowDropdashRay      = true;
    gDropdashConfig.mightyHammerDash      = true;
#endif
}

void DropdashConfig_LoadFromSettings(void)
{
#if RETRO_USE_MOD_LOADER
    bool32 enableTails    = Mod.GetSettingsBool("", "Config:EnableDropdashTails", true);
    bool32 enableKnuckles = Mod.GetSettingsBool("", "Config:EnableDropdashKnuckles", true);
#if MANIA_USE_PLUS
    bool32 enableMighty   = Mod.GetSettingsBool("", "Config:EnableDropdashMighty", true);
    bool32 enableRay      = Mod.GetSettingsBool("", "Config:EnableDropdashRay", true);
    bool32 fixHammerDash  = Mod.GetSettingsBool("", "Config:MightyHammerDash", true);
#endif

    gDropdashConfig.allowDropdashTails    = enableTails;
    gDropdashConfig.allowDropdashKnuckles = enableKnuckles;
#if MANIA_USE_PLUS
    gDropdashConfig.allowDropdashMighty = enableMighty;
    gDropdashConfig.allowDropdashRay    = enableRay;
    gDropdashConfig.mightyHammerDash = fixHammerDash;
#endif

    Mod.SetSettingsBool("Config:EnableDropdashTails", gDropdashConfig.allowDropdashTails);
    Mod.SetSettingsBool("Config:EnableDropdashKnuckles", gDropdashConfig.allowDropdashKnuckles);
#if MANIA_USE_PLUS
    Mod.SetSettingsBool("Config:EnableDropdashMighty", gDropdashConfig.allowDropdashMighty);
    Mod.SetSettingsBool("Config:EnableDropdashRay", gDropdashConfig.allowDropdashRay);
    Mod.SetSettingsBool("Config:MightyHammerDash", gDropdashConfig.mightyHammerDash);
#endif
    
    Mod.SaveSettings();
#endif
}

/* ======================================== */
/* DEFINES AND ENUMS                       */
/* ======================================== */

#define DROPDASH_STATE(player)        ((player)->abilityValues[6])
#define DROPDASH_INPUT_TIMER(player)  ((player)->abilityValues[7])
#define DROPDASH_COOLDOWN 30
#define INPUT_BUFFER_FRAMES 6

#if MANIA_USE_PLUS
#define HAMMERDASH_COOLDOWN 90
#endif

typedef enum {
    DROPDASH_NONE,
    DROPDASH_CHARGING,
    DROPDASH_READY,
} DropdashState;

/* ======================================== */
/* UTILITY FUNCTIONS                        */
/* ======================================== */

static inline bool32 IsDropdashEnabledFor(EntityPlayer *self)
{
    switch (self->characterID) {
        case ID_TAILS:    return gDropdashConfig.allowDropdashTails;
        case ID_KNUCKLES: return gDropdashConfig.allowDropdashKnuckles;
#if MANIA_USE_PLUS
        case ID_MIGHTY:   return gDropdashConfig.allowDropdashMighty;
        case ID_RAY:      return gDropdashConfig.allowDropdashRay;
#endif
        default:          return false;
    }
}

static inline bool32 Player_CanTriggerDropdash(EntityPlayer *self)
{
    uint16 pid = self->playerID;

    if (!canDropdash[pid]) {
        return false;
    }
    
    if (DROPDASH_INPUT_TIMER(self) > 0) {
        return false;
    }

#if MANIA_USE_PLUS
    if (hammerdashCooldownTimer[pid] > 0) {
        return false;
    }
#endif

    if (self->onGround)
        return false;
    if (self->sidekick && self->stateInput != Player_Input_P2_Player)
        return false;
    if (!IsDropdashEnabledFor(self))
        return false;

    bool32 haveDown  = self->down || (ddDownBuf[pid] > 0);
    bool32 haveJumpP = self->jumpPress || (ddJumpBuf[pid] > 0);
    return haveDown && haveJumpP;
}

static inline void Player_StartDropdash(EntityPlayer *self)
{
    if (!Player_State_DropDash)
        return;
    uint16 pid = self->playerID;
    self->state           = Player_State_DropDash;
    self->nextGroundState = StateMachine_None;
    self->nextAirState    = StateMachine_None;

    if (!sfxDropdashCached)
        sfxDropdashCached = RSDK.GetSfx("Global/DropDash.wav");
    if (sfxDropdashCached) {
        RSDK.PlaySfx(sfxDropdashCached, false, 255);
    }

    DROPDASH_STATE(self) = DROPDASH_CHARGING;
    DROPDASH_INPUT_TIMER(self) = DROPDASH_COOLDOWN;
}

/* ======================================== */
/* INPUT HANDLERS                           */
/* ======================================== */

bool32 Player_Input_P1_Hook(bool32 skipped)
{
    RSDK_THIS(Player);
    
    uint16 pid = self->playerID;
    
    if (self->jumpPress && !self->onGround) {
        canDropdash[pid] = 1;
    }
    
    return false;
}

bool32 Player_Input_P2_Hook(bool32 skipped)
{
    RSDK_THIS(Player);
    
    uint16 pid = self->playerID;
    
    if (self->jumpPress && !self->onGround) {
        canDropdash[pid] = 1;
    }
    
    return false;
}

/* ======================================== */
/* STATE HANDLERS                          */
/* ======================================== */

bool32 Player_State_Ground_ResetDropdash(bool32 skipped)
{
    RSDK_THIS(Player);
    if (DROPDASH_STATE(self) != DROPDASH_NONE)
        DROPDASH_STATE(self) = DROPDASH_NONE;
    ddActive[self->playerID] = 0;
    canDropdash[self->playerID] = 0;
    
#if MANIA_USE_PLUS
    if (self->characterID == ID_MIGHTY) {
        mightyHammerTransition[self->playerID] = 0;
        mightyShouldHammerdash[self->playerID] = 0;
    }
#endif
    
    return false;
}

bool32 Player_State_Air_HandleDropdashInput(bool32 skipped)
{
    RSDK_THIS(Player);
    
    uint16 pid = self->playerID;

#if MANIA_USE_PLUS
    if (self->characterID == ID_MIGHTY && gDropdashConfig.mightyHammerDash) {
        if (ddDownBuf[pid] > 0)
            ddDownBuf[pid]--;
        if (ddJumpBuf[pid] > 0)
            ddJumpBuf[pid]--;
        if (self->jumpPress)
            ddJumpBuf[pid] = INPUT_BUFFER_FRAMES;
            
        if (hammerdashCooldownTimer[pid] > 0) {
            hammerdashCooldownTimer[pid]--;
        }
            
        bool32 haveDown  = self->down || (ddDownBuf[pid] > 0);
        bool32 haveJumpP = self->jumpPress || (ddJumpBuf[pid] > 0);
        
        if (haveDown && haveJumpP) {
            mightyShouldHammerdash[pid] = 1;
        } else {
            mightyShouldHammerdash[pid] = 0;
        }
        
        if (!mightyShouldHammerdash[pid]) {
            if (Player_CanTriggerDropdash(self)) {
                Player_StartDropdash(self);
                return true;
            }
        }
        
        return false;
    }
#endif
    
    if (self->characterID == ID_SONIC)
        return false;
    if (!IsDropdashEnabledFor(self))
        return false;

    uint8 wasDown = ddPrevDown[pid];

    if (ddDownBuf[pid] > 0)
        ddDownBuf[pid]--;
    if (ddJumpBuf[pid] > 0)
        ddJumpBuf[pid]--;
    if (self->jumpPress)
        ddJumpBuf[pid] = INPUT_BUFFER_FRAMES;

    if (DROPDASH_INPUT_TIMER(self) > 0) {
        DROPDASH_INPUT_TIMER(self)--;
    }

    bool32 haveDown  = self->down || (ddDownBuf[pid] > 0);
    bool32 haveJumpP = self->jumpPress || (ddJumpBuf[pid] > 0);

    if (haveDown && haveJumpP) {
        if (Player_CanTriggerDropdash(self)) {
            Player_StartDropdash(self);
            return true;
        }
    }

    ddPrevDown[pid] = self->down;
    return false;
}

#if MANIA_USE_PLUS
bool32 Player_State_MightyHammerDrop_TransitionHook(bool32 skipped)
{
    RSDK_THIS(Player);
    
    if (self->characterID != ID_MIGHTY)
        return false;
        
    uint16 pid = self->playerID;
    
    if (mightyHammerTransition[pid] && ddActive[pid]) {
        self->state = Player_State_DropDash;
        return true;
    }
    
    return false;
}
#endif

/* ======================================== */
/* CHARACTER ABILITIES                      */
/* ======================================== */

bool32 Player_TryDropdash_Generic(bool32 skipped)
{
    RSDK_THIS(Player);

    bool32 isCorrectCharacter = (self->characterID == ID_TAILS || self->characterID == ID_KNUCKLES);

#if MANIA_USE_PLUS
    isCorrectCharacter = isCorrectCharacter || (self->characterID == ID_RAY);
    
    if (self->characterID == ID_MIGHTY && !gDropdashConfig.mightyHammerDash) {
        isCorrectCharacter = true;
    }
#endif

    if (isCorrectCharacter) {
        if (Player_CanTriggerDropdash(self)) {
            Player_StartDropdash(self);
            return true;
        }
    }

    return false;
}

#if MANIA_USE_PLUS
bool32 Player_JumpAbility_Mighty_Hammerdash(bool32 skipped)
{
    RSDK_THIS(Player);
    
    if (self->characterID != ID_MIGHTY)
        return false;
        
    uint16 pid = self->playerID;
    
    if (gDropdashConfig.mightyHammerDash && mightyShouldHammerdash[pid]) {
        if (Player_State_MightyHammerDrop) {
            self->state            = Player_State_MightyHammerDrop;
            self->nextAirState     = StateMachine_None;
            self->nextGroundState  = StateMachine_None;
            RSDK.SetSpriteAnimation(self->aniFrames, ANI_HAMMERDROP, &self->animator, false, 2);
            
            mightyHammerTransition[pid] = 1;
            ddActive[pid] = 1;
            self->jumpHold = true;
            
            DROPDASH_STATE(self) = DROPDASH_CHARGING;
            DROPDASH_INPUT_TIMER(self) = DROPDASH_COOLDOWN;
            hammerdashCooldownTimer[pid] = HAMMERDASH_COOLDOWN;

            mightyShouldHammerdash[pid] = 0;
            
            return true;
        }
    }
    
    return false;
}
#endif

/* ======================================== */
/* MOD INITIALIZATION                       */
/* ======================================== */

static void InitModAPI(void)
{
    DropdashConfig_InitDefaults();
    DropdashConfig_LoadFromSettings();

    Player_Action_Jump = Mod.GetPublicFunction(NULL, "Player_Action_Jump");
    Player_State_Air       = Mod.GetPublicFunction(NULL, "Player_State_Air");
    Player_State_Ground    = Mod.GetPublicFunction(NULL, "Player_State_Ground");
    Player_Input_P1        = Mod.GetPublicFunction(NULL, "Player_Input_P1");
    Player_Input_P2_Player = Mod.GetPublicFunction(NULL, "Player_Input_P2_Player");
    Player_State_DropDash  = Mod.GetPublicFunction(NULL, "Player_State_DropDash");

#if MANIA_USE_PLUS
    Player_State_MightyHammerDrop = Mod.GetPublicFunction(NULL, "Player_State_MightyHammerDrop");
#endif

    if (Player_Input_P1) {
        Mod.RegisterStateHook(Player_Input_P1, Player_Input_P1_Hook, false);
    }
    
    if (Player_Input_P2_Player) {
        Mod.RegisterStateHook(Player_Input_P2_Player, Player_Input_P2_Hook, false);
    }

    if (Player_State_Air)
        Mod.RegisterStateHook(Player_State_Air, Player_State_Air_HandleDropdashInput, true);
    
    if (Player_State_Ground)
        Mod.RegisterStateHook(Player_State_Ground, Player_State_Ground_ResetDropdash, false);

    StateMachine(Player_JumpAbility_Tails) = Mod.GetPublicFunction(NULL, "Player_JumpAbility_Tails");
    StateMachine(Player_JumpAbility_Knux) = Mod.GetPublicFunction(NULL, "Player_JumpAbility_Knux");

    if (Player_JumpAbility_Tails)
        Mod.RegisterStateHook(Player_JumpAbility_Tails, Player_TryDropdash_Generic, false);
    
    if (Player_JumpAbility_Knux)
        Mod.RegisterStateHook(Player_JumpAbility_Knux, Player_TryDropdash_Generic, false);
    
#if MANIA_USE_PLUS
    StateMachine(Player_JumpAbility_Mighty) = Mod.GetPublicFunction(NULL, "Player_JumpAbility_Mighty");
    StateMachine(Player_JumpAbility_Ray) = Mod.GetPublicFunction(NULL, "Player_JumpAbility_Ray");

    if (Player_JumpAbility_Mighty) {
        Mod.RegisterStateHook(Player_JumpAbility_Mighty, Player_JumpAbility_Mighty_Hammerdash, false);
    }

    if (Player_JumpAbility_Ray)
        Mod.RegisterStateHook(Player_JumpAbility_Ray, Player_TryDropdash_Generic, false);
        
    if (Player_State_MightyHammerDrop && gDropdashConfig.mightyHammerDash) {
        Mod.RegisterStateHook(Player_State_MightyHammerDrop, Player_State_MightyHammerDrop_TransitionHook, false);
    }
#endif

    MOD_REGISTER_OBJECT_HOOK(Player);
}

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id)
{
#if MANIA_USE_PLUS
    LinkGameLogicDLL(info);
#else
    LinkGameLogicDLL(*info);
#endif

    globals = Mod.GetGlobals();
    modID = id;

    InitModAPI();

    return true;
}
#endif