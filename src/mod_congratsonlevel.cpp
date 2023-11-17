/*

# Congrats On Level #

#### A module for AzerothCore (https://github.com/azerothcore/mod-congrats-on-level)
#### Originally by [StygianTheBest](https://github.com/StygianTheBest/AzerothCore-Content/tree/master/Modules)
------------------------------------------------------------------------------------------------------------------


### Description ###
------------------------------------------------------------------------------------------------------------------
This module rewards players when they reach specific levels. It has the option to reward gold, two items, and a
buff or any combination. It also announces to the world when a player levels up. All rewards can be set in the
config file for quick modifications.


### Features ###
------------------------------------------------------------------------------------------------------------------
- Announces player level up to world
- Awards the player for gaining new levels
- The player forfeits the rewards if their bags are full


### Data ###
------------------------------------------------------------------------------------------------------------------
- Type: Player/Server
- Script: CongratsOnLevel
- Config: Yes
    - Enable Module
    - Enable Module Announce
    - Set Items/Gold/Buffs Given At Each Level
- SQL: No


### Version ###
------------------------------------------------------------------------------------------------------------------
- v2022.04.09 - Fixed deprecation warnings
- v2017.08.06 - Release
- v2017.09.30 - Fix Level Display Bug. Update Strings.


### Credits ###
------------------------------------------------------------------------------------------------------------------
- [SoulSeekkor](https://github.com/SoulSeekkor)
- [LordPsyan](https://bitbucket.org/lordpsyan/lordpsyan-patches)
- [Blizzard Entertainment](http://blizzard.com)
- [TrinityCore](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/THANKS)
- [SunwellCore](http://www.azerothcore.org/pages/sunwell.pl/)
- [AzerothCore](https://github.com/AzerothCore/azerothcore-wotlk/graphs/contributors)
- [AzerothCore Discord](https://discord.gg/gkt4y2x)
- [EMUDevs](https://youtube.com/user/EmuDevs)
- [AC-Web](http://ac-web.org/)
- [ModCraft.io](http://modcraft.io/)
- [OwnedCore](http://ownedcore.com/)
- [OregonCore](https://wiki.oregon-core.net/)
- [Wowhead.com](http://wowhead.com)
- [AoWoW](https://wotlk.evowow.com/)


### License ###
------------------------------------------------------------------------------------------------------------------
- This code and content is released under the [GNU AGPL v3](https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3).

*/

#include "Configuration/Config.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"

struct COL
{
    uint32 acoreMessageId;
    bool congratsAnnounce, congratsEnable;
    bool CongratsPerLevelEnable;
};

COL col;

uint32 giveAward(Player* player)
{
    QueryResult result = WorldDatabase.Query("SELECT * FROM `mod_congrats_on_level_items` WHERE `level`={} AND (`race`={} OR `race`=0) AND (`class`={} OR `class`=0)", player->getLevel(), player->getRace(), player->getClass());

    uint32 money = 0;

    if (result)
    {
        do
        {
            Field* fields = result->Fetch();
            if (fields[1].Get<uint32>() > 0)
            {
                player->ModifyMoney(fields[1].Get<uint32>() * GOLD);
                money += fields[1].Get<uint32>() * GOLD;
            }
            if (fields[2].Get<uint32>() > 0)
            {
                if (fields[3].Get<uint32>() == 0)
                    player->CastSpell(player, fields[2].Get<uint32>());
                else
                    player->learnSpell(fields[2].Get<uint32>());
            }
            if (fields[4].Get<uint32>() > 0)
                player->AddItem(fields[4].Get<uint32>(), 1);
            if (fields[5].Get<uint32>())
                player->AddItem(fields[5].Get<uint32>(), 1);
        }
        while (result->NextRow());

        return money;
    }
    return money;
}

class CongratsAnnounce : public PlayerScript
{

public:

    CongratsAnnounce() : PlayerScript("CongratsAnnounce") {}

    void OnLogin(Player* player)
    {
        // Announce Module
        if (col.congratsAnnounce)
        {
            ChatHandler(player->GetSession()).SendSysMessage(col.acoreMessageId);
        }
    }
};

class CongratsOnLevel : public PlayerScript
{

public:
    CongratsOnLevel() : PlayerScript("CongratsOnLevel") { }

    // Level Up Rewards
    void OnLevelChanged(Player* player, uint8 oldLevel) override
    {
        // If enabled...
        if (col.congratsEnable)
        {
            uint8 level = player->getLevel();
            uint32 money = 0;
            std::string rewardLevel;

            switch (level)
            {
                case 2:
                {
                    if (oldLevel < 2)
                    {
                        money = giveAward(player);
                        rewardLevel = "2";
                    }
                }
                case 10:
                {
                    if (oldLevel < 10)
                    {
                        money = giveAward(player);
                        rewardLevel = "10";
                    }
                }
                break;

                case 20:
                {
                    if (oldLevel < 20)
                    {
                        money = giveAward(player);
                        rewardLevel = "20";
                    }
                }
                break;

                case 30:
                {
                    if (oldLevel < 30)
                    {
                        money = giveAward(player);
                        rewardLevel = "30";
                    }
                }
                break;

                case 40:
                {
                    if (oldLevel < 40)
                    {
                        money = giveAward(player);
                        rewardLevel = "40";
                    }
                }
                break;

                case 50:
                {
                    if (oldLevel < 50)
                    {
                        money = giveAward(player);
                        rewardLevel = "50";
                    }
                }
                break;

                case 60:
                {
                    if (oldLevel < 60)
                    {
                        money = giveAward(player);
                        rewardLevel = "60";
                    }
                }
                break;

                case 70:
                {
                    if (oldLevel < 70)
                    {
                        money = giveAward(player);
                        rewardLevel = "70";
                    }
                }
                break;

                case 80:
                {
                    if (oldLevel < 80)
                    {
                        money = giveAward(player);
                        rewardLevel = "80";
                    }
                }
                break;

                default:
                    break;
            }

            // If level is defined, they hit a reward level.
            if (!rewardLevel.empty() && col.CongratsPerLevelEnable)
            {
                // Issue a raid warning to the player
                std::ostringstream msg;
                msg << "恭喜你达到 " << level << " 级！奖励" << money << "金币和一些特殊物品。";
                ChatHandler(player->GetSession()).PSendSysMessage(msg.str().c_str());
                checkPlayerRecruitment(player, level);
            }
        }
    }

    void checkPlayerRecruitment(Player* player, std::string level) {
        if(level != "80") {
            return ;
        }
        uint32 guid = player->GetSession()->GetAccountId();
        QueryResult accountResult = LoginDatabase.Query("SELECT email FROM account WHERE id={}", guid);
        if(!accountResult) {
            return ;
        }
        Field* fields = accountResult->Fetch();
        std::string email = fields[0].Get<std::string>();
        if(email.empty()) {
            return ;
        }
        QueryResult result = LoginDatabase.Query("SELECT * FROM recruitment WHERE friend='{}' AND status = {}", email.c_str(), 0);
        if(!result) {
            return ;
        }
        LoginDatabase.Query("UPDATE recruitment SET status={} WHERE friend='{}'", 1, email.c_str());
        player->AddItem(69999, 50);
        player->AddItem(38082, 4);
        ChatHandler(player->GetSession()).PSendSysMessage("招募奖励领取成功");
    }
};

class ModCongratsLevelWorldScript : public WorldScript
{
public:
    ModCongratsLevelWorldScript() : WorldScript("ModCongratsLevelWorldScript") { }

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload)
        {
            sConfigMgr->LoadModulesConfigs();
            col.acoreMessageId = sConfigMgr->GetOption<uint32>("Congrats.Acore.String.ID", 60000);
            col.congratsAnnounce = sConfigMgr->GetOption<uint32>("Congrats.Announce", 1);
            col.congratsEnable = sConfigMgr->GetOption<uint32>("Congrats.Enable", 1);
            col.CongratsPerLevelEnable = sConfigMgr->GetOption<uint32>("CongratsPerLevel.Enable", 1);
        }
    }
};

void AddCongratsOnLevelScripts()
{
    new CongratsAnnounce();
    new CongratsOnLevel();
    new ModCongratsLevelWorldScript();
}
