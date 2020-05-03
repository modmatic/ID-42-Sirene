#ifndef INPUTS_H
#define INPUTS_H

#include <Arduino.h>
#include "globals.h"
#include "player.h"

void checkInputs()
{
  if (arduboy.pressed(DOWN_BUTTON) && (mermaid.y < GAME_BOTTOM - 12))
  {
    mermaid.y++;
  }
  if (arduboy.pressed(LEFT_BUTTON) && (mermaid.x > GAME_LEFT))
  {
    mermaid.x--;
  }
  if (arduboy.pressed(UP_BUTTON) && (mermaid.y > GAME_TOP))
  {
    mermaid.y--;
  }
  if (arduboy.pressed(RIGHT_BUTTON) && (mermaid.x < GAME_RIGHT - 16))
  {
    mermaid.x++;
  }

#if DOTMG_CART_SAMD51
  if (arduboy.justPressed(START_BUTTON))
#else
  if (arduboy.justPressed(A_BUTTON))
#endif
  {
    gameState = STATE_GAME_PAUSE;
  }

#if DOTMG_CART_SAMD51
  if (arduboy.justPressed(A_BUTTON) && (coolDown[mermaid.weaponType] == coolDownMax[mermaid.weaponType]))
#else
  if (arduboy.justPressed(B_BUTTON) && (coolDown[mermaid.weaponType] == coolDownMax[mermaid.weaponType]))
#endif
  {

    if (mermaid.weaponType == WEAPON_TYPE_TRIDENT)
    {
      coolDown[mermaid.weaponType]--;
      shootWeapon();
    }
    if ((mermaid.weaponType == WEAPON_TYPE_SEASHELL))
    {
      {
        coolDown[mermaid.weaponType]--;
        for (byte i = 0; i < 3; i++)
        {
          shootWeapon();
        }
      }
    }
  }
#if DOTMG_CART_SAMD51
  if (arduboy.pressed(A_BUTTON))
#else
  if (arduboy.pressed(B_BUTTON))
#endif
  {
    if ((mermaid.weaponType == WEAPON_TYPE_BUBBLES) && (coolDown[WEAPON_TYPE_BUBBLES] == coolDownMax[WEAPON_TYPE_BUBBLES]))
    {
      coolDown[mermaid.weaponType]--;
      shootWeapon();
    }
    if (mermaid.weaponType == WEAPON_TYPE_MAGIC)
    {
      mermaid.magicCharging = true;
      if (arduboy.everyXFrames(30)) mermaid.chargeBarFrame ++;
      if (mermaid.chargeBarFrame > 4) mermaid.chargeBarFrame = 4;
    }
  }
#if DOTMG_CART_SAMD51
  if (arduboy.notPressed(A_BUTTON) && (mermaid.weaponType == WEAPON_TYPE_MAGIC) && (mermaid.magicCharging == true))
#else
  if (arduboy.notPressed(B_BUTTON) && (mermaid.weaponType == WEAPON_TYPE_MAGIC) && (mermaid.magicCharging == true))
#endif
  {
    mermaid.magicCharging = false;
    coolDown[mermaid.weaponType]--;
    shootWeapon();
    mermaid.chargeBarFrame = 0;
  }
}


#endif
