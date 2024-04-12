#ifndef MEMBER_HPP
#define MEMBER_HPP
#include "Enemy.hpp"
#include "Skills.hpp"
#include <utility>
#include "Stone.hpp"
#include "Datas.hpp"
#include "AbilityStatus.hpp"
class Enchant;
class Member{
public:
    virtual void Skill()=0;
    Type::Element_type GetType(){return m_Etype;}
    Type::Race_type GetRace(){return m_Rtype;}
    std::vector<std::shared_ptr<LeaderSkill>> GetLeaderSkill(){return m_LeaderSkill;};
    int GetAtk(){return m_attack;}
    int GetLife(){return m_life;}
    int GetHeal(){return m_heal;}
    void Strike(bool onlyone,int damage,bool defence,DragingDatas datas);
    void SetEnemy(std::vector<std::shared_ptr<Enemy>> target){
        m_enemies = target;}
    Member(Type::Element_type e_type, Type::Race_type r_type ,int attack,int life,int heal,MemberSettingData data): m_Etype(e_type),m_Rtype(r_type),m_attack(attack),m_life(life),m_heal(heal),m_Enchant(data.m_Enchant){};
protected:
    std::vector<std::shared_ptr<LeaderSkill>> m_LeaderSkill;
    std::shared_ptr<Enchant> m_Enchant;
    std::vector<std::shared_ptr<Member>> m_team;
    std::vector<std::shared_ptr<Enemy>> m_enemies;
    Type::Element_type m_Etype;
    Type::Race_type m_Rtype;
    int m_attack;
    int m_life;
    int m_heal;
};

//skill
class Boom{
public:
    explicit Boom(std::shared_ptr<Enchant> target):m_Enchant(std::move(target)){};
    int StoneBreak(Type::Element_type Lvalue,bool powerup);
private:
    std::shared_ptr<Enchant> m_Enchant;
};

class StoneTurn{
public:
    explicit StoneTurn(std::shared_ptr<Enchant> target):m_Enchant(std::move(target)){};
    void Turn(Type::Element_type Lvalue,Type::Element_type Rvalue,bool powerup);
private:
    std::shared_ptr<Enchant> m_Enchant;
};

class Dio{
    Dio(std::shared_ptr<Enchant> target):m_Enchant(std::move(target)){};
    void TheWorld(int seconds);
private:
    std::shared_ptr<Enchant> m_Enchant;
};


//Charctor
//MainCharacter
class Mori:public Member,Boom{
public:
    explicit Mori(MemberSettingData data): Member(Type::Element_type::Water,Type::Race_type::Mortal,1035,1881,364,data),
          Boom(std::move(data.m_Enchant)){
            std::shared_ptr<PowerUp> token = std::make_shared<PowerUp>(data.m_FirstAddition,Type::Element_type::Water,2);
            m_LeaderSkill.push_back(token);
    };
    void Skill() override{

        float Addition = m_attack * StoneBreak(Type::Element_type::Grass,true);
        LOG_DEBUG("skill deals {} damage!!!",Addition);

        int Damage = (int)Addition;
        DragingDatas token;
        token.m_Attackertype = Type::Element_type::Water;
        Strike(false,Damage,true,token);
    }
};

class Sean:public Member,Boom{
public:
    explicit Sean(MemberSettingData data): Member(Type::Element_type::Fire,Type::Race_type::Mortal,1107,1980,324,data),
          Boom(std::move(data.m_Enchant)){
        std::shared_ptr<PowerUp> token = std::make_shared<PowerUp>(data.m_FirstAddition,Type::Element_type::Fire,2);
        m_LeaderSkill.push_back(token);
    };
    void Skill() override{
        float Addition = m_attack *  StoneBreak(Type::Element_type::Water,true);
        LOG_DEBUG("{} stones are erased",Addition);
        int Damage = (int)Addition;
        DragingDatas token;
        Strike(false,Damage,true,token);
    }
};
class Dunkan:public Member,Boom{
public:
    explicit Dunkan(MemberSettingData data): Member(Type::Element_type::Grass,Type::Race_type::Mortal,953,2176,340,data),
          Boom(std::move(data.m_Enchant)){
        std::shared_ptr<PowerUp> token = std::make_shared<PowerUp>(data.m_FirstAddition,Type::Element_type::Grass,2);
        m_LeaderSkill.push_back(token);
    };
    void Skill() override{
        float Addition = m_attack *  StoneBreak(Type::Element_type::Fire,true);
        LOG_DEBUG("{} stones are erased",Addition);
        int Damage = (int)Addition;
        DragingDatas token;
        Strike(false,Damage,true,token);
    }
};
class Nathaniel:public Member,Boom{
public:
    explicit Nathaniel(MemberSettingData data): Member(Type::Element_type::Light,Type::Race_type::Mortal,963,1960,374,data),
          Boom(std::move(data.m_Enchant)){
        std::shared_ptr<PowerUp> token = std::make_shared<PowerUp>(data.m_FirstAddition,Type::Element_type::Light,2);
        m_LeaderSkill.push_back(token);
          };
    void Skill() override{
        float Addition = m_attack *  StoneBreak(Type::Element_type::Dark,true);
        LOG_DEBUG("{} stones are erased",Addition);
        int Damage = (int)Addition;
        DragingDatas token;
        Strike(false,Damage,true,token);
    }
};
class Ando:public Member,Boom{
public:
    explicit Ando(MemberSettingData data): Member(Type::Element_type::Dark,Type::Race_type::Mortal,1137,1843,337,data),
          Boom(std::move(data.m_Enchant)){
        std::shared_ptr<PowerUp> token = std::make_shared<PowerUp>(data.m_FirstAddition,Type::Element_type::Dark,2);
        m_LeaderSkill.push_back(token);
          };
    void Skill() override{
        float Addition = m_attack *  StoneBreak(Type::Element_type::Light,true);
        LOG_DEBUG("{} stones are erased",Addition);
        int Damage = (int)Addition;
        DragingDatas token;
        Strike(false,Damage,true,token);
    }
};

//ChineseBeast
class WaterBeast:public Member,StoneTurn{
public:
    explicit WaterBeast(MemberSettingData data): Member(Type::Element_type::Water,Type::Race_type::Dragon,979,3199,78,data),
          StoneTurn(std::move(data.m_Enchant)){
            std::shared_ptr<RaceUp> token = std::make_shared<RaceUp>(data.m_FirstRaceAddition,Type::Race_type::Dragon,2.5);
            m_LeaderSkill.push_back(token);
          };
    void Skill() override{
        Turn(Type::Element_type::Heart,Type::Element_type::Water, false);
    }
};

class FireBeast:public Member,StoneTurn{
    explicit FireBeast(MemberSettingData data): Member(Type::Element_type::Fire,Type::Race_type::Beast,1105,2684,305,data),
          StoneTurn(std::move(data.m_Enchant)){
        std::shared_ptr<PowerUp> token = std::make_shared<PowerUp>(data.m_FirstAddition,Type::Element_type::Fire,2.5);
        m_LeaderSkill.push_back(token);
          };
    void Skill() override{
        Turn(Type::Element_type::Grass,Type::Element_type::Heart, false);
    }
};
class GrassBeast:public Member,StoneTurn{
    explicit GrassBeast(MemberSettingData data): Member(Type::Element_type::Grass,Type::Race_type::Beast,952,2949,322,data),
          StoneTurn(std::move(data.m_Enchant)){
        std::shared_ptr<PowerUp> token = std::make_shared<PowerUp>(data.m_FirstAddition,Type::Element_type::Grass,2.5);
        m_LeaderSkill.push_back(token);
          };
    void Skill() override{
        //todo
    }
};
class LightBeast:public Member,StoneTurn{
    explicit LightBeast(MemberSettingData data): Member(Type::Element_type::Light,Type::Race_type::Beast,874,2416,321,data),
          StoneTurn(std::move(data.m_Enchant)){
        std::shared_ptr<PowerUp> token = std::make_shared<PowerUp>(data.m_FirstAddition,Type::Element_type::Light,2.5);
        m_LeaderSkill.push_back(token);
          };
    void Skill() override{
        //Todo
    }
};
class DarkBeast:public Member,StoneTurn{
    explicit DarkBeast(MemberSettingData data): Member(Type::Element_type::Dark,Type::Race_type::Beast,1033,2271,289,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        Turn(Type::Element_type::Light,Type::Element_type::Heart, false);
    }
};

//DefentDragon
class WDefentDragon:public Member{
    explicit WDefentDragon(MemberSettingData data): Member(Type::Element_type::Water,Type::Race_type::Dragon,1068,3489,30,data){};
    void Skill() override{
        float Addition = (int)m_attack;
        int Damage = (int)Addition * 30;
        DragingDatas token;
        token.m_Attackertype = Type::Element_type::Water;
        Strike(false,Damage,true,token);
    }
};
class FDefentDragon:public Member{
    explicit FDefentDragon(MemberSettingData data): Member(Type::Element_type::Fire,Type::Race_type::Dragon,1142,3672,26,data){};
    void Skill() override{
        float Addition = (int)m_attack;
        int Damage = (int)Addition * 30;
        DragingDatas token;
        token.m_Attackertype = Type::Element_type::Fire;
        Strike(false,Damage,true,token);
    }
};
class GDefentDragon:public Member{
    explicit GDefentDragon(MemberSettingData data): Member(Type::Element_type::Grass,Type::Race_type::Dragon,983,4036,28,data){};
    void Skill() override{
        float Addition = (int)m_attack;
        int Damage = (int)Addition * 30;
        DragingDatas token;
        token.m_Attackertype = Type::Element_type::Fire;
        Strike(false,Damage,true,token);
    }
};
class LDefentDragon:public Member{
    explicit LDefentDragon(MemberSettingData data): Member(Type::Element_type::Light,Type::Race_type::Dragon,994,3635,30,data){};
    void Skill() override{
        float Addition = (int)m_attack;
        int Damage = (int)Addition * 30;
        DragingDatas token;
        token.m_Attackertype = Type::Element_type::Light;
        Strike(false,Damage,true,token);
    }
};
class DDefentDragon:public Member{
    explicit DDefentDragon(MemberSettingData data): Member(Type::Element_type::Dark,Type::Race_type::Dragon,1174,3417,28,data){};
    void Skill() override{
        float Addition = (int)m_attack;
        int Damage = (int)Addition * 30;
        DragingDatas token;
        token.m_Attackertype = Type::Element_type::Dark;
        Strike(false,Damage,true,token);
    }
};
//Titan
class WaterTitan:public Member,StoneTurn{
public:
    explicit WaterTitan(MemberSettingData data): Member(Type::Element_type::Water,Type::Race_type::Beast,799,1971,104,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        Turn(Type::Element_type::Fire,Type::Element_type::Water, false);
    }
};
class FireTitan:public Member,StoneTurn{
public:
    explicit FireTitan(MemberSettingData data): Member(Type::Element_type::Fire,Type::Race_type::Dragon,970,2471,21,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        Turn(Type::Element_type::Grass,Type::Element_type::Fire, false);
    }
};
class GrassTitan:public Member,StoneTurn{
public:
    explicit GrassTitan(MemberSettingData data): Member(Type::Element_type::Grass,Type::Race_type::Beast,810,1849,288,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        Turn(Type::Element_type::Water,Type::Element_type::Grass, false);
    }
};
class LightTitan:public Member,StoneTurn{
public:
    explicit LightTitan(MemberSettingData data): Member(Type::Element_type::Light,Type::Race_type::Beast,744,2053,107,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        Turn(Type::Element_type::Dark,Type::Element_type::Light, false);
    }
};
class DarkTitan:public Member,StoneTurn{
public:
    explicit DarkTitan(MemberSettingData data): Member(Type::Element_type::Dark,Type::Race_type::Dragon,831,2420,20,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        Turn(Type::Element_type::Light,Type::Element_type::Dark, false);
    }
};


//WestBeast
class Cthulhu:public Member,StoneTurn{
public:
    explicit Cthulhu(MemberSettingData data): Member(Type::Element_type::Water,Type::Race_type::Beast,940,2319,123,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        Turn(Type::Element_type::Fire,Type::Element_type::Heart, false);
    }
};
class Cerberus:public Member,StoneTurn{
public:
    explicit Cerberus(MemberSettingData data): Member(Type::Element_type::Fire,Type::Race_type::Beast,1005,2440,109,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        Turn(Type::Element_type::Heart,Type::Element_type::Fire, false);
    }
};
class Medusa:public Member,StoneTurn{
public:
    explicit Medusa(MemberSettingData data): Member(Type::Element_type::Grass,Type::Race_type::Beast,865,2681,115,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        //Todo
    }
};
class Griffin:public Member,StoneTurn{
public:
    explicit Griffin(MemberSettingData data): Member(Type::Element_type::Light,Type::Race_type::Beast,874,2416,126,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        Turn(Type::Element_type::Dark,Type::Element_type::Heart, false);
    }
};
class Baphomet:public Member,StoneTurn{
public:
    explicit Baphomet(MemberSettingData data): Member(Type::Element_type::Dark,Type::Race_type::Beast,1033,2271,114,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        Turn(Type::Element_type::Heart,Type::Element_type::Dark, false);
    }
};


//Norse Mythology
class Freyr:public Member,StoneTurn{
public:
    explicit Freyr(MemberSettingData data): Member(Type::Element_type::Water,Type::Race_type::Protoss,1402,3161,442,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        Turn(Type::Element_type::Water,Type::Element_type::Water, true);
    }
};
class Tyr:public Member,StoneTurn{
public:
    explicit Tyr(MemberSettingData data): Member(Type::Element_type::Fire,Type::Race_type::Protoss,1499,3326,392,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        Turn(Type::Element_type::Fire,Type::Element_type::Fire, true);
    }
};
class Freyja:public Member,StoneTurn{
public:
    explicit Freyja(MemberSettingData data): Member(Type::Element_type::Grass,Type::Race_type::Protoss,1291,3655,412,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        Turn(Type::Element_type::Grass,Type::Element_type::Grass, true);
    }
};
class Thor:public Member,StoneTurn{
public:
    explicit Thor(MemberSettingData data): Member(Type::Element_type::Light,Type::Race_type::Protoss,1305,3293,453,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        Turn(Type::Element_type::Light,Type::Element_type::Light, true);
    }
};
class Loki:public Member,StoneTurn{
public:
    explicit Loki(MemberSettingData data): Member(Type::Element_type::Dark,Type::Race_type::Protoss,1540,3096,409,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        Turn(Type::Element_type::Dark,Type::Element_type::Dark, true);
    }
};

//Slime
class WaterSlime:public Member,StoneTurn{
public:
    explicit WaterSlime(MemberSettingData data): Member(Type::Element_type::Water,Type::Race_type::Fairy,387,736,406,data),
          StoneTurn(std::move(data.m_Enchant)){
        std::shared_ptr<ComboUp> token = std::make_shared<ComboUp>(data.m_addCombo,0.25);
        m_LeaderSkill.push_back(token);
          };
    void Skill() override{
        Turn(Type::Element_type::Fire,Type::Element_type::Heart,true);
    }
};

class FireSlime:public Member,StoneTurn{
public:
    explicit FireSlime(MemberSettingData data): Member(Type::Element_type::Fire,Type::Race_type::Fairy,1107,1980,384,data),
          StoneTurn(std::move(data.m_Enchant)){
        std::shared_ptr<ComboUp> token = std::make_shared<ComboUp>(data.m_addCombo,0.25);
        m_LeaderSkill.push_back(token);
          };
    void Skill() override{
        Turn(Type::Element_type::Grass,Type::Element_type::Heart,true);
    }
};
class GrassSlime:public Member,StoneTurn{
public:
    explicit GrassSlime(MemberSettingData data): Member(Type::Element_type::Grass,Type::Race_type::Fairy,1107,1980,384,data),
          StoneTurn(std::move(data.m_Enchant)){
        std::shared_ptr<ComboUp> token = std::make_shared<ComboUp>(data.m_addCombo,0.25);
        m_LeaderSkill.push_back(token);
          };
    void Skill() override{
        Turn(Type::Element_type::Water,Type::Element_type::Heart,true);
    }
};
class LightSlime:public Member,StoneTurn{
public:
    explicit LightSlime(MemberSettingData data): Member(Type::Element_type::Light,Type::Race_type::Fairy,1107,1980,384,data),
          StoneTurn(std::move(data.m_Enchant)){
        std::shared_ptr<ComboUp> token = std::make_shared<ComboUp>(data.m_addCombo,0.25);
        m_LeaderSkill.push_back(token);
          };
    void Skill() override{
        Turn(Type::Element_type::Dark,Type::Element_type::Heart,true);
    }
};
class DarkSlime:public Member,StoneTurn{
public:
    explicit DarkSlime(MemberSettingData data): Member(Type::Element_type::Dark,Type::Race_type::Fairy,1107,1980,384,data),
          StoneTurn(std::move(data.m_Enchant)){
        std::shared_ptr<ComboUp> token = std::make_shared<ComboUp>(data.m_addCombo,0.25);
        m_LeaderSkill.push_back(token);
          };
    void Skill() override{
        Turn(Type::Element_type::Light,Type::Element_type::Dark,true);
    }
};
//Gnome
class WGnome:public Member,StoneTurn{
public:
    explicit WGnome(MemberSettingData data): Member(Type::Element_type::Water,Type::Race_type::Fairy,528,1064,372,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        Turn(Type::Element_type::Heart,Type::Element_type::Water, false);
    }
};
class FGnome:public Member,StoneTurn{
public:
    explicit FGnome(MemberSettingData data): Member(Type::Element_type::Fire,Type::Race_type::Fairy,564,1120,331,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        Turn(Type::Element_type::Heart,Type::Element_type::Fire, false);
    }
};
class GGnome:public Member,StoneTurn{
public:
    explicit GGnome(MemberSettingData data): Member(Type::Element_type::Grass,Type::Race_type::Fairy,486,1231,349,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        Turn(Type::Element_type::Heart,Type::Element_type::Grass, false);
    }
};
class LGnome:public Member,StoneTurn{
public:
    explicit LGnome(MemberSettingData data): Member(Type::Element_type::Light,Type::Race_type::Fairy,491,1108,383,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        Turn(Type::Element_type::Heart,Type::Element_type::Light, false);
    }
};
class DGnome:public Member,StoneTurn{
public:
    explicit DGnome(MemberSettingData data): Member(Type::Element_type::Dark,Type::Race_type::Fairy,580,1042,345,data),
          StoneTurn(std::move(data.m_Enchant)){};
    void Skill() override{
        Turn(Type::Element_type::Heart,Type::Element_type::Dark, false);
    }
};
//Matallic Beast
class WaterShark:public Member{
public:
    explicit WaterShark(MemberSettingData data): Member(Type::Element_type::Water,Type::Race_type::Beast,961,2430,296,data){};
    void Skill() override{
        float Addition = (int)m_attack;
        int Damage = (int)Addition * 15;
        DragingDatas token;
        token.m_Attackertype = Type::Element_type::Water;
        Strike(false,Damage,true,token);
    }
};
class FireLion:public Member{
public:
    explicit FireLion(MemberSettingData data): Member(Type::Element_type::Fire,Type::Race_type::Beast,1028,2556,263,data){};
    void Skill() override {
        float Addition = (int)m_attack;
        int Damage = (int)Addition * 15;
        DragingDatas token;
        token.m_Attackertype = Type::Element_type::Fire;
        Strike(false, Damage, true, token);
    }
};
class GrassRhino:public Member{
public:
    explicit GrassRhino(MemberSettingData data): Member(Type::Element_type::Grass,Type::Race_type::Beast,885,2809,278,data){};
    void Skill() override {
        float Addition = (int)m_attack;
        int Damage = (int)Addition * 15;
        DragingDatas token;
        token.m_Attackertype = Type::Element_type::Grass;
        Strike(false, Damage, true, token);
    }
};
class LightWolf:public Member{
public:
    explicit LightWolf(MemberSettingData data): Member(Type::Element_type::Light,Type::Race_type::Beast,895,2531,304,data){};
    void Skill() override {
        float Addition = (int)m_attack;
        int Damage = (int)Addition * 15;
        DragingDatas token;
        token.m_Attackertype = Type::Element_type::Light;
        Strike(false, Damage, true, token);
    }
};
class DarkCheetah:public Member{
public:
    explicit DarkCheetah(MemberSettingData data): Member(Type::Element_type::Dark,Type::Race_type::Beast,1057,2379,274,data){};
    void Skill() override {
        float Addition = (int)m_attack;
        int Damage = (int)Addition * 15;
        DragingDatas token;
        token.m_Attackertype = Type::Element_type::Dark;
        Strike(false, Damage, true, token);
    }
};

#endif
