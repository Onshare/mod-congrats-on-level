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
#include "AccountMgr.h"
#include "Chat.h"

class CongratsOnLevel : public PlayerScript
{

public:
    CongratsOnLevel() : PlayerScript("CongratsOnLevel") { }

    // Level Up Rewards
    void OnLevelChanged(Player* player, uint8 oldLevel) override
    {
        // If enabled...
        if (sConfigMgr->GetOption<bool>("Congrats.Enable", true)) {

            std::string level;
            uint32 money, item1, item2, spell;

            if (oldLevel < 2 && player->getLevel() == 2)
            {
                // Level 2
                const uint32 L21 = sConfigMgr->GetOption<uint32>("Congrats.L21", 0);
                const uint32 L22 = sConfigMgr->GetOption<uint32>("Congrats.L22", 0);
                const uint32 L2M = sConfigMgr->GetOption<uint32>("Congrats.L2M", 0);
                const uint32 L2S = sConfigMgr->GetOption<uint32>("Congrats.L2S", 0);

                level = "2";
                item1 = L21;
                item2 = L22;
                money = L2M;
                spell = L2S;
            }
            else if (oldLevel < 10 && player->getLevel() == 10)
            {
                // Level 10
                const uint32 L101 = sConfigMgr->GetOption<uint32>("Congrats.L101", 0);
                const uint32 L102 = sConfigMgr->GetOption<uint32>("Congrats.L102", 0);
                const uint32 L10M = sConfigMgr->GetOption<uint32>("Congrats.L10M", 0);
                const uint32 L10S = sConfigMgr->GetOption<uint32>("Congrats.L10S", 0);

                level = "10";
                item1 = L101;
                item2 = L102;
                money = L10M;
                spell = L10S;
            }
            else if (oldLevel < 20 && player->getLevel() == 20)
            {
                // Level 20
                const uint32 L201 = sConfigMgr->GetOption<uint32>("Congrats.L201", 0);
                const uint32 L202 = sConfigMgr->GetOption<uint32>("Congrats.L202", 0);
                const uint32 L20M = sConfigMgr->GetOption<uint32>("Congrats.L20M", 0);
                const uint32 L20S = sConfigMgr->GetOption<uint32>("Congrats.L20S", 0);

                level = "20";
                item1 = L201;
                item2 = L202;
                money = L20M;
                spell = L20S;
            }
            else if (oldLevel < 30 && player->getLevel() == 30)
            {
                // Level 30
                const uint32 L301 = sConfigMgr->GetOption<uint32>("Congrats.L301", 0);
                const uint32 L302 = sConfigMgr->GetOption<uint32>("Congrats.L302", 0);
                const uint32 L30M = sConfigMgr->GetOption<uint32>("Congrats.L30M", 0);
                const uint32 L30S = sConfigMgr->GetOption<uint32>("Congrats.L30S", 0);

                level = "30";
                item1 = L301;
                item2 = L302;
                money = L30M;
                spell = L30S;
            }
            else if (oldLevel < 40 && player->getLevel() == 40)
            {
                // Level 40
                const uint32 L401 = sConfigMgr->GetOption<uint32>("Congrats.L401", 0);
                const uint32 L402 = sConfigMgr->GetOption<uint32>("Congrats.L402", 0);
                const uint32 L40M = sConfigMgr->GetOption<uint32>("Congrats.L40M", 0);
                const uint32 L40S = sConfigMgr->GetOption<uint32>("Congrats.L40S", 0);

                level = "40";
                item1 = L401;
                item2 = L402;
                money = L40M;
                spell = L40S;
            }
            else if (oldLevel < 50 && player->getLevel() == 50)
            {
                // Level 50
                const uint32 L501 = sConfigMgr->GetOption<uint32>("Congrats.L501", 0);
                const uint32 L502 = sConfigMgr->GetOption<uint32>("Congrats.L502", 0);
                const uint32 L50M = sConfigMgr->GetOption<uint32>("Congrats.L50M", 0);
                const uint32 L50S = sConfigMgr->GetOption<uint32>("Congrats.L50S", 0);

                level = "50";
                item1 = L501;
                item2 = L502;
                money = L50M;
                spell = L50S;
            }
            else if (oldLevel < 60 && player->getLevel() == 60)
            {
                // Level 60
                const uint32 L601 = sConfigMgr->GetOption<uint32>("Congrats.L601", 0);
                const uint32 L602 = sConfigMgr->GetOption<uint32>("Congrats.L602", 0);
                const uint32 L60M = sConfigMgr->GetOption<uint32>("Congrats.L60M", 0);
                const uint32 L60S = sConfigMgr->GetOption<uint32>("Congrats.L60S", 0);

                level = "60";
                item1 = L601;
                item2 = L602;
                money = L60M;
                spell = L60S;
            }
            else if (oldLevel < 70 && player->getLevel() == 70)
            {
                // Level 70
                const uint32 L701 = sConfigMgr->GetOption<uint32>("Congrats.L701", 0);
                const uint32 L702 = sConfigMgr->GetOption<uint32>("Congrats.L702", 0);
                const uint32 L70M = sConfigMgr->GetOption<uint32>("Congrats.L70M", 0);
                const uint32 L70S = sConfigMgr->GetOption<uint32>("Congrats.L70S", 0);

                level = "70";
                item1 = L701;
                item2 = L702;
                money = L70M;
                spell = L70S;
            }
            else if (oldLevel < 80 && player->getLevel() == 80)
            {
                // Level 80
                const uint32 L801 = sConfigMgr->GetOption<uint32>("Congrats.L801", 0);
                const uint32 L802 = sConfigMgr->GetOption<uint32>("Congrats.L802", 0);
                const uint32 L80M = sConfigMgr->GetOption<uint32>("Congrats.L80M", 0);
                const uint32 L80S = sConfigMgr->GetOption<uint32>("Congrats.L80S", 0);

                level = "80";
                item1 = L801;
                item2 = L802;
                money = L80M;
                spell = L80S;
            }

            // If level is defined, they hit a reward level.
            if (!level.empty())
            {
                // Give the items to the player
                if(item1 != 0) {
                    player->AddItem(item1, 1);				// Defined Item 1
                }
                if(item2 != 0) {
                    player->AddItem(item2, 1);				// Defined Item 2
                }

                // Give gold to the player
                player->ModifyMoney(money*GOLD);		// Defined Gold

                // Buff the player
                if(spell != 0) {
                    player->CastSpell(player, spell);		// Defined Spell
                }

                // Issue a raid warning to the player
                std::ostringstream msg;
                msg << "恭喜你达到 " << level << " 级！奖励" << money << "金币";
                if(item1 != 0 || item2 != 0) {
                    msg << "和一些特殊物品。";
                }
                ChatHandler(player->GetSession()).PSendSysMessage(msg.str().c_str());
            }
            checkPlayerRecruitment(player, level);
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
        player->AddItem(33809, 1);
        ChatHandler(player->GetSession()).PSendSysMessage("招募奖励领取成功");
    }
};

void AddCongratsOnLevelScripts()
{
    new CongratsOnLevel();
}
