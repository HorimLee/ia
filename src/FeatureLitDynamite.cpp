#include "FeatureLitDynamite.h"

#include "Engine.h"
#include "Explosion.h"
#include "Map.h"
#include "Fov.h"

void LitDynamite::newTurn() {
  turnsLeftToExplosion_--;
  if(turnsLeftToExplosion_ <= 0) {
    eng->explosionMaker->runExplosion(pos_);
    eng->gameTime->eraseFeatureMob(this, true);
  }
}

void LitFlare::newTurn() {
  life_--;
  if(life_ <= 0) {
    eng->gameTime->eraseFeatureMob(this, true);
  }
}

LitFlare::LitFlare(Feature_t id, coord pos, Engine* engine, DynamiteSpawnData* spawnData) :
  FeatureMob(id, pos, engine), life_(spawnData->turnsLeftToExplosion_) {
}

void LitFlare::addLight(bool light[MAP_X_CELLS][MAP_Y_CELLS]) const {
  bool myLight[MAP_X_CELLS][MAP_Y_CELLS];
  eng->basicUtils->resetBoolArray(myLight, false);
  const int RADI = getLightRadius();
  int x0 = pos_.x - RADI;
  int y0 = pos_.y - RADI;
  int x1 = pos_.x + RADI;
  int y1 = pos_.y + RADI;
  x0 = max(0, x0);
  y0 = max(0, y0);
  x1 = min(MAP_X_CELLS - 1, x1);
  y1 = min(MAP_Y_CELLS - 1, y1);
  bool visionBlockers[MAP_X_CELLS][MAP_Y_CELLS];
  for(int y = y0; y <= y1; y++) {
    for(int x = x0; x <= x1; x++) {
      visionBlockers[x][y] = !eng->map->featuresStatic[x][y]->isVisionPassable();
    }
  }

  eng->fov->runFovOnArray(visionBlockers, pos_, myLight, false);
  for(int y = y0; y <= y1; y++) {
    for(int x = x0; x <= x1; x++) {
      if(myLight[x][y]) {
        light[x][y] = true;
      }
    }
  }
}



