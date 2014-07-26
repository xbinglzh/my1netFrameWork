//
//  KeyConfigDef.h
//  motoGame
//
//  Created by xUanBing on 14-4-28.
//
//

#ifndef __motoGame__KeyConfigDef__
#define __motoGame__KeyConfigDef__

#define KKeyType                      "type"
#define KKeyFile                      "file"
#define KKeyScale                     "scale"
#define KKeyFlipX                     "flipx"
#define KKeyImagePlist                "image_plist"
#define KKeyImageTexture              "image_texture"
#define KKeyAnimation                 "animation"
#define KKeyskeleton                  "skeleton"
#define KKeyDefault                   "default"
#define KKeySize                      "size"
#define KKeyFont                      "font"
#define KKeyColor                     "color"
#define KKeyStrokeColor               "stroke_color" //描边字边框颜色

#define KKeyParam                     "param"
#define KKeyX                         "x"
#define KKeyY                         "y"
#define KKeySize                      "size"
#define KKeyColor                     "color"
#define KKeyScale                     "scale"
#define KKeyFlipX                     "flipx"
#define KKeyFont                      "font"
#define KKeyStrokeColor               "stroke_color" //描边字边框颜色
#define KKeyMonster                   "monster"
#define KKeyGeneral                   "general"
#define KKeyMonsterSendInterval       "monster_send_interval"
#define KKeyImage                     "image"
#define KKeyPlist                     "plist"
#define KKeyAudio                     "audio"
#define KKeyId                        "id"
#define KKeyRoleCardId                "role_card_id"

//Setting Key
#define KStrAudioEffectStatusClosed   "AudioEffectStatusClosed"
#define KStrBgMusicStatusClosed       "BgMusicStatusClosed"

//Anim Key
#define KKeyAction       "action"
#define KKeyState        "state"
#define KKeyAnimation    "animation"
#define KKeyskeleton     "skeleton"
#define KKeySpeed        "speed"
#define KKeyAttackEffect "attack_effect"
#define KKeyCurrentState "current_state"
#define KKeyCurrentStateOld "current_state_old"
#define KKeySkillNextState   "skill_next_state"
#define KKeyLifespan     "lifespan"
#define KKeyPieces       "pieces"
#define KKeyPiecesCount  "pieces_count"
#define KKeyEffect       "effect"
#define KKeyReduceHPEffect       "reduce_hp_effect"
#define KKeyDestoryEffect        "destory_effect"
#define KKeyRewardRatio          "reward_ratio"


#define KKeySkillHurtAdd      "skill_hurt_add" //伤害加成
#define KKeyHurt         "hurt"     //攻击基础伤害
#define KKeyHurtStep     "hurt_step"//攻击成长参数(领兵)
#define KKeyHurtType          "hurt_type"//攻击类型
#define KKeySkillHurt          "skill_hurt"//攻击类型
#define KKeyIgnoreImmuneSkill      "KKeyIgnoreImmuneSkill"//攻击类型
#define KKeyAtkTargetSize          "atk_target_size"//攻击目标数量
#define KKeyKillIntercept          "KKeyKillIntercept"
#define KKeyIntercept          "KKeyIntercept"
#define KKeyLevel        "level"
#define KKeyMaxLevel     "max_level"
#define KKeyNextLevelId  "next_level_id"
#define KKeyName                "name"
#define KKeyCardLimit           "cardUseLimit"
#define KKeyNameImage           "name_image"
#define KKeyTitleDisplayType       "title_display_type"
#define KKeySkillTitleDisplay      "skill_title_display"
#define KKeyDesc         "desc"
#define KKeyRace         "race"
#define KKeyRarity       "rarity"
#define KKeyAttackCT     "attack_ct"
#define KKeyAttackRange  "attack_range"
#define KKeyRecoverCT    "recover_ct"
#define KKeyRecoverHP    "recover_hp"
#define KKeyFile         "file"
#define KKeyMaskFile     "maskfile"

#define KKeyDisplayBg      "display_bg"

#define KDoCallFuncActId      "ACT_ID"
#define KDoCallFuncParams     "ACT_Params"
#define KActDestoryDef        "act_destory_default"
#define KActAttackDef         "act_attack_default"
#define KActAttackSlingDef     "act_attack_sling"
#define KActAttackSkillDef    "act_attack_skill"
#define KActAttackStormLikeDef   "act_attack_strom_like"
#define KActAttackBodyDef           "act_attack_body"
#define kActAttackPoisonDef     "act_attack_poison"   //剧毒攻击

#define KActAttackMartyrdom   "act_attack_martyrdom"
#define KActAttackContact     "act_attack_contact"


#define KActOnArrived         "act_arrived"
#define KActOnArrivedDef      "act_arrived_default"
#define KKeyActMoveToFinishedDef        "act_move_to_finished_default"

#define KActRevenge                         "act_revenge"
#define KActOnMsgDef                        "act_on_msg_default"
#define KKeyActOnRotateFinishedDef          "act_on_rotate_default"

#define KStrEffectBlinkOpacity    "blink_opacity"
#define KStrEffectToOpacity       "to_opacity"
#define KStrEffectBlinkColor      "blink_color"
#define KStrEffectToColor         "to_color"
#define KStrEffectDefaultRGBA     "def_rgba"
#define KStrEffectDict            "effect_dict"
#define KStrEffectFromToColor     "from_to_color"

#define KStrBattleId              "battleId"
#define KStrBattleZoneId          "battle_zone"

//x_pve_stage.plist
#define KKeyMap                   "map"
#define KKeyDifficulty            "difficulty"
#define KKeyTroop                 "troop"
#define KKeyTroopWaves            "troop_waves"
#define KKeyAttackTeam            "attack_team"

//Map.plist
#define KKeyMapBg                 "map_bg"
#define KKeyMapPic                "map_pic"
#define KKeyMapData               "map_data"

//x_map_pit.plist
#define KKeyPitImg                "pit_img"

//x_attacking_team.plist
#define KKeyTroop_1               "troop_1"
#define KKeyTroop_1_difficulty    "troop_1_difficulty"
#define KKeyTroop_2               "troop_2"
#define KKeyTroop_2_difficulty    "troop_2_difficulty"
#define KKeyTroop_3               "troop_3"
#define KKeyTroop_3_difficulty    "troop_3_difficulty"
#define KKeyTroop_4               "troop_4"
#define KKeyTroop_4_difficulty    "troop_4_difficulty"
#define KKeyTroop_intervals       "troop_intervals"
#define KKeyTroop_max_size        "troop_max_size"

//x_troop.plist
#define KKeyMonster_1_id          "monster_1_id"
#define KKeyMonster_1_num         "monster_1_num"
#define KKeyMonster_2_id          "monster_2_id"
#define KKeyMonster_2_num         "monster_2_num"
#define KKeyMonster_3_id          "monster_3_id"
#define KKeyMonster_3_num         "monster_3_num"
#define KKeyMonster_4_id          "monster_4_id"
#define KKeyMonster_4_num         "monster_4_num"
#define KKeyMonster_5_id          "monster_5_id"
#define KKeyMonster_5_num         "monster_5_num"
#define KKeyMonsterCount          "monster_count"

//x_monster
#define KKeyHp                    "hp"
#define KKeyHurt                  "hurt"
#define KKeyDisplay               "display"

//Duration Action
#define KKeyPrepareSkillDuration             "prepare_skill_duration"
#define KKeyDoSkillDuration             "do_skill_duration"
#define KKeyDestoryDuration             "destory_duration"
#define KKeyBeInjureDuration            "be_injure_duration"
#define KKeyArrivedDuration            "arrived_duration"

//Act 
#define KKeyActDestory             "act_destory"
#define KKeyActAttack              "act_attack"
#define KKeyActSkillAttack          "act_skill_attack"
#define KKeyActSkillAttackEnable    "act_skill_attack_enbale"
#define KKeyActSAttack              "act_s_attack"
#define KKeyActOnMsg               "act_on_msg"
#define KKeyActOnRotateFinished    "act_on_msg_rotate"
#define KKeyActMoveToFinished      "act_move_to_finished"
#define KKeyDropInterval      "drop_interval"
#define KKeyBackgroundImage     "bg_img"
#define KKeyRoleDialogInterval      "role_dialog_interval"
#define KKeyAntiAir                 "anti_air"



#endif /* defined(__motoGame__KeyConfigDef__) */
