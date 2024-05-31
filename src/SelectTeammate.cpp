//
// Created by fungp on 2024/5/24.
//

#include "iostream"
#include "memory"
#include "vector"
#include <functional>
#include <utility>
#include "Member.hpp"
#include "SelectTeammate.hpp"

std::vector<std::shared_ptr<Member>> Team::GetTeam() {
    return m_MemberList;
}


NorthTeam::NorthTeam(MemberSettingData target) {
    m_Data = std::move(target);
    std::shared_ptr<Member> token = std::make_shared<Loki>(m_Data);
    m_MemberList.push_back(token);
    token = std::make_shared<DarkBeast>(m_Data);
    m_MemberList.push_back(token);
    token = std::make_shared<Baphomet>(m_Data);
    m_MemberList.push_back(token);
    token = std::make_shared<DaJi>(m_Data);
    m_MemberList.push_back(token);
    token = std::make_shared<Artemis>(m_Data);
    m_MemberList.push_back(token);
    token = std::make_shared<Loki>(m_Data);
    m_MemberList.push_back(token);
}

OlympianTeam::OlympianTeam(MemberSettingData target) {
    m_Data = std::move(target);
    std::shared_ptr<Member> token = std::make_shared<Athana>(m_Data);
    m_MemberList.push_back(token);
    token = std::make_shared<GrassBeast>(m_Data);
    m_MemberList.push_back(token);
    token = std::make_shared<Dunkan>(m_Data);
    m_MemberList.push_back(token);
    token = std::make_shared<Eduard>(m_Data);
    m_MemberList.push_back(token);
    token = std::make_shared<GrassTitan>(m_Data);
    m_MemberList.push_back(token);
    token = std::make_shared<Athana>(m_Data);
    m_MemberList.push_back(token);
}

BeastTeam::BeastTeam(MemberSettingData target) {
    m_Data = std::move(target);
    std::shared_ptr<Member> token = std::make_shared<DarkBeast>(m_Data);
    m_MemberList.push_back(token);
    token = std::make_shared<GrassBeast>(m_Data);
    m_MemberList.push_back(token);
    token = std::make_shared<WaterBeast>(m_Data);
    m_MemberList.push_back(token);
    token = std::make_shared<LightBeast>(m_Data);
    m_MemberList.push_back(token);
    token = std::make_shared<FireBeast>(m_Data);
    m_MemberList.push_back(token);
    token = std::make_shared<DarkBeast>(m_Data);
    m_MemberList.push_back(token);
}

LoDaTeam::LoDaTeam(MemberSettingData target) {
    m_Data = std::move(target);
    std::shared_ptr<Member> token = std::make_shared<Loki>(m_Data);
    m_MemberList.push_back(token);
    token = std::make_shared<DarkBeast>(m_Data);
    m_MemberList.push_back(token);
    token = std::make_shared<Baphomet>(m_Data);
    m_MemberList.push_back(token);
    token = std::make_shared<Artemis>(m_Data);
    m_MemberList.push_back(token);
    token = std::make_shared<DarkRanger>(m_Data);
    m_MemberList.push_back(token);
    token = std::make_shared<DaJi>(m_Data);
    m_MemberList.push_back(token);
}