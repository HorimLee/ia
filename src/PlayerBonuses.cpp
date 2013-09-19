#include "PlayerBonuses.h"

#include <cassert>
#include <algorithm>

#include "Engine.h"
#include "TextFormatting.h"
#include "ActorPlayer.h"
#include "DungeonMaster.h"

using namespace std;

void PlayerBonHandler::pickBon(const PlayerBon_t bon) {
  bons_[bon].isPicked_ = true;

  switch(bon) {
    case playerBon_tough: {
      eng->player->changeMaxHp(3, false);
    } break;

    case playerBon_selfAware: {
      eng->player->getPropHandler()->tryApplyProp(
        new PropRConfusion(eng, propTurnsIndefinite), true, true, true);
    } break;

    case playerBon_fearless: {
      eng->player->getPropHandler()->tryApplyProp(
        new PropRFear(eng, propTurnsIndefinite), true, true, true);
    } break;

    default: {} break;
  }
}

PlayerBonHandler::PlayerBonHandler(Engine* engine) : eng(engine) {
  string descr = "";

  descr  = "+25% chance to evade attacks and traps, ";
  descr += "every fourth move is a free action";
  addBon(playerBon_dexterous, "Dexterous", playerBonType_trait, descr);

  descr  = "You occasionally spot clues about hidden passages, ";
  descr += "your attentiveness is higher when examining objects ";
  descr += "(for example when searching a chest for traps)";
  addBon(playerBon_observant, "Observant", playerBonType_trait, descr);

  descr  = "You cannot be backstabbed - hidden monsters gets no ";
  descr += "melee attack bonus against you, and their attacks can be dodged";
  addBon(playerBon_vigilant, "Vigilant", playerBonType_trait, descr);

  descr  = "You cannot become terrified, +5% shock resistance";
  addBon(playerBon_fearless, "Fearless", playerBonType_trait, descr);

  descr  = "+20% shock resistance";
  addBon(playerBon_coolHeaded, "Cool-headed", playerBonType_trait, descr);

  descr  = "You cannot become confused, the number of remaining turns ";
  descr += "for status effects are displayed";
  addBon(playerBon_selfAware, "Self-aware", playerBonType_trait, descr);

  descr  = "+3 hit points, +10% carry weight limit, ";
  descr += "better results for object interactions requiring strength ";
  descr += "(such as bashing doors, or moving the lid from a stone coffin)";
  addBon(playerBon_tough, "Tough", playerBonType_trait, descr);

//  addBon(playerBon_swiftRetaliator, "Swift retaliator", "Dodging causes retaliation attacks if melee weapon is wielded");

//  addBon(playerBon_elusive, "Elusive", "+30% chance to evade attacks while moving", playerBon_dexterous);

//  addBon(playerBon_tumbler, "Tumbler", "Can evade explosions", playerBon_athletic);

  descr  = "+15% hit chance with melee weapons";
  addBon(playerBon_adeptMeleeCombatant, "Adept melee combatant",
         playerBonType_skill, descr);

//  addBon(playerBon_swiftAssailant, "Swift assailant", "Killing a monster with a melee weapon is considered a free turn");

//  addBon(playerBon_aggressive, "Aggressive", "+X melee dmg when attacking in same direction as previous move");

  descr  = "+15% hit chance with firearms and thrown weapons, ";
  descr += "standing still for a turn gives another 10% hit chance";
  addBon(playerBon_marksman, "Marksman", playerBonType_skill, descr);

//  addBon(playerBon_steadyAimer, "Steady aimer", playerBonType_skill,
//         "Waiting a turn gives +20% hit chance with firearms and thrown weapons");

//  addBon(playerBon_deadlyThrower, "Deadly thrower", "X% chance for 2x max dmg with thrown weapons", playerBon_adeptRangedCombatant);

//  addBon(playerBon_nimbleHanded, "Nimble-handed", "Can disarm mechanical traps, can use lockpicks, X% chance to reload or swap weapons instantly", playerBon_dexterous);

  descr  = "You tend to find more items";
  addBon(playerBon_treasureHunter, "Treasure hunter",
         playerBonType_skill, descr);

  descr  = "All potions are identified, you start with three random potions";
  addBon(playerBon_alchemist, "Alchemist", playerBonType_skill, descr);

  descr  = "You are more likely to avoid detection";
  addBon(playerBon_stealthy, "Stealthy", playerBonType_skill, descr);

  descr  = "When casting a spell from an identified manuscript, you gain ";
  descr += "the ability to cast this spell intrinsically";
  addBon(playerBon_occultist, "Occultist", playerBonType_skill, descr);

  descr  = "Healing takes half the normal time and resources, you can treat diseases";
  addBon(playerBon_healer, "Healer",
         playerBonType_skill, descr);

//  descr  = "Can heal disease";
//  addBon(playerBon_curer, "Curer", playerBonType_skill, descr);

  descr  = "Greatly increased hit point regeneration rate";
  addBon(playerBon_rapidRecoverer, "Rapid recoverer",
         playerBonType_skill, descr);

  descr  = "+30% carry weight limit";
  addBon(playerBon_strongBacked, "Strong-backed", playerBonType_trait, descr);
}

void PlayerBonHandler::getAllPickedBonTitlesList(vector<string>& titles) {
  titles.resize(0);
  for(unsigned int i = 0; i < endOfPlayerBons; i++) {
    const PlayerBon& bon = bons_[i];
    if(bon.isPicked_) {
      titles.push_back(bon.title_);
    }
  }
}

void PlayerBonHandler::getAllPickedBonTitlesLine(string& str) {
  str = "";
  for(unsigned int i = 0; i < endOfPlayerBons; i++) {
    const PlayerBon& bon = bons_[i];
    if(bon.isPicked_) {
      const string title = "\"" + bon.title_ + "\"";
      str += str == "" ? title : (", " + title);
    }
  }
}
