#ifndef OBJ_PLAYER_H
#define OBJ_PLAYER_H

#include "GameAPI/Game.h"

/* ======================================== */
/* ANIMATION IDENTIFIERS                   */
/* ======================================== */

typedef enum {
    ANI_IDLE,
    ANI_BORED_1,
    ANI_BORED_2,
    ANI_LOOK_UP,
    ANI_CROUCH,
    ANI_WALK,
    ANI_AIR_WALK,
    ANI_JOG,
    ANI_RUN,
    ANI_DASH,
    ANI_JUMP,
    ANI_SPRING_TWIRL,
    ANI_SPRING_DIAGONAL,
    ANI_SKID,
    ANI_SKID_TURN,
    ANI_SPINDASH,
    ANI_ABILITY_0,
    ANI_PUSH,
    ANI_HURT,
    ANI_DIE,
    ANI_DROWN,
    ANI_BALANCE_1,
    ANI_BALANCE_2,
    ANI_SPRING_CS,
    ANI_STAND_CS,
    ANI_FAN,
    ANI_VICTORY,
    ANI_OUTTA_HERE,
    ANI_HANG,
    ANI_HANG_MOVE,
    ANI_POLE_SWING_V,
    ANI_POLE_SWING_H,
    ANI_SHAFT_SWING,
    ANI_TURNTABLE,
    ANI_TWISTER,
    ANI_SPIRAL_RUN,
    ANI_STICK,
    ANI_PULLEY_HOLD,
    ANI_SHIMMY_IDLE,
    ANI_SHIMMY_MOVE,
    ANI_BUBBLE,
    ANI_BREATHE,
    ANI_RIDE,
    ANI_CLING,
    ANI_BUNGEE,
    ANI_TWIST_RUN,
#if MANIA_USE_PLUS
    ANI_FLUME,
#endif
    ANI_TRANSFORM,
    ANI_ABILITY_1,
    ANI_ABILITY_2,
    ANI_ABILITY_3,
    ANI_ABILITY_4,
    ANI_ABILITY_5,
    ANI_ABILITY_6,
    ANI_ABILITY_7,
    ANI_DROPDASH = ANI_ABILITY_0,
#if MANIA_USE_PLUS
    ANI_HAMMERDROP = ANI_ABILITY_0,
#endif
} PlayerAnimationIDs;

/* ======================================== */
/* GAMEPLAY ENUMS                          */
/* ======================================== */

typedef enum {
    SHIELD_NONE,
    SHIELD_BLUE,
    SHIELD_BUBBLE,
    SHIELD_FIRE,
    SHIELD_LIGHTNING,
} ShieldTypes;

typedef enum {
    SUPERSTATE_NONE,
    SUPERSTATE_FADEIN,
    SUPERSTATE_SUPER,
    SUPERSTATE_FADEOUT,
    SUPERSTATE_DONE,
} SuperStates;

/* ======================================== */
/* PLAYER STRUCTURES                        */
/* ======================================== */

typedef struct EntityCamera EntityCamera;

typedef struct {
    RSDK_OBJECT
    int32 playerCount;
} ObjectPlayer;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(nextAirState);
    StateMachine(nextGroundState);
    EntityCamera *camera;
    Animator animator;
    Animator tailAnimator;
    int32 maxWalkSpeed;
    int32 maxJogSpeed;
    int32 maxRunSpeed;
    int32 unused;
    int32 tailRotation;
    int32 tailDirection;
    uint16 aniFrames;
    uint16 tailFrames;
    uint16 animationReserve;
    uint16 playerID;
    Hitbox *outerbox;
    Hitbox *innerbox;
    int32 characterID;
    int32 rings;
    int32 ringExtraLife;
    int32 shield;
    int32 lives;
    int32 score;
    int32 score1UP;
    bool32 hyperRing;
    int32 timer;
    int32 outtaHereTimer;
    int32 abilityTimer;
    int32 spindashCharge;
    int32 abilityValue;
    int32 drownTimer;
    int32 invincibleTimer;
    int32 speedShoesTimer;
    int32 blinkTimer;
    int32 scrollDelay;
    int32 skidding;
    int32 pushing;
    int32 underwater;
    bool32 groundedStore;
    bool32 invertGravity;
    bool32 isChibi;
    bool32 isTransforming;
    int32 superState;
    int32 superRingLossTimer;
    int32 superBlendAmount;
    int32 superBlendState;
    bool32 sidekick;
    int32 scoreBonus;
    int32 jumpOffset;
    int32 collisionFlagH;
    int32 collisionFlagV;
    int32 topSpeed;
    int32 acceleration;
    int32 deceleration;
    int32 airAcceleration;
    int32 airDeceleration;
    int32 skidSpeed;
    int32 rollingFriction;
    int32 rollingDeceleration;
    int32 gravityStrength;
    int32 abilitySpeed;
    int32 jumpStrength;
    int32 jumpCap;
    int32 flailing;
    int32 sensorX[5];
    int32 sensorY;
    Vector2 moveLayerPosition;
    StateMachine(stateInputReplay);
    StateMachine(stateInput);
    int32 controllerID;
    int32 controlLock;
    bool32 up;
    bool32 down;
    bool32 left;
    bool32 right;
    bool32 jumpPress;
    bool32 jumpHold;
    bool32 applyJumpCap;
    int32 jumpAbilityState;
    StateMachine(stateAbility);
    StateMachine(statePeelout);
    int32 flyCarryTimer;
    Vector2 flyCarrySidekickPos;
    Vector2 flyCarryLeaderPos;
    uint8 deathType;
    bool32 forceJumpIn;
#if MANIA_USE_PLUS
    bool32 isGhost;
#endif
    int32 abilityValues[8];
    void *abilityPtrs[8];
#if MANIA_USE_PLUS
    int32 uncurlTimer;
#endif
} EntityPlayer;

/* ======================================== */
/* GLOBAL PLAYER OBJECT                    */
/* ======================================== */

extern ObjectPlayer *Player;

/* ======================================== */
/* FUNCTION POINTER DECLARATIONS            */
/* ======================================== */

extern StateMachine(Player_Action_Jump);
extern StateMachine(Player_State_Air);
extern StateMachine(Player_State_Ground);
extern StateMachine(Player_Input_P2_Player);
extern StateMachine(Player_State_DropDash);

#if MANIA_USE_PLUS
extern StateMachine(Player_State_MightyHammerDrop);
#endif

/* ======================================== */
/* CHARACTER ABILITY DECLARATIONS           */
/* ======================================== */

extern StateMachine(Player_JumpAbility_Tails);
extern StateMachine(Player_JumpAbility_Knux);

#if MANIA_USE_PLUS
extern StateMachine(Player_JumpAbility_Mighty);
extern StateMachine(Player_JumpAbility_Ray);
#endif

/* ======================================== */
/* DROPDASH FUNCTION DECLARATIONS          */
/* ======================================== */

bool32 Player_State_DropDash_KeepHold(bool32 skipped);
bool32 Player_State_Ground_Block(bool32 skipped);
void Player_GroundActionControls(void);

/* ======================================== */
/* CONFIGURATION FUNCTIONS                  */
/* ======================================== */

void DropdashConfig_InitDefaults(void);
void DropdashConfig_LoadFromSettings(void);

#endif