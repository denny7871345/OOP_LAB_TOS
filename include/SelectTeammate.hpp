//
// Created by fungp on 2024/5/24.
//
#ifndef SELECTTEAMMATE_HPP
#define SELECTTEAMMATE_HPP
#include "iostream"
#include "memory"
#include "vector"
#include <functional>
#include "Member.hpp"
#include "Datas.hpp"



class Team{
public:

    std::vector<std::shared_ptr<Member>>  GetTeam();
    int Size();
protected:
    std::vector<std::shared_ptr<Member>> m_MemberList;
    MemberSettingData m_Data;
};

class NorthTeam : public Team{
public:
    NorthTeam(MemberSettingData target);
};

class OlympianTeam : public Team{
public:
    OlympianTeam(MemberSettingData target);
};

class BeastTeam: public Team{
public:
    BeastTeam(MemberSettingData target);
};

class LoDaTeam: public Team{
public:
    LoDaTeam(MemberSettingData target);
};


#endif // SELECTTEAMMATE_HPP
