//
// Created by fungp on 2024/5/24.
//

#include "iostream"
#include "memory"
#include "vector"
#include <functional>
#include "Member.hpp"
#include "SelectTeammate.hpp"

std::vector<std::shared_ptr<Member>> Team::GetTeam() {
    return m_MemberList;
}

void Team::LoadMemberFile(MemberSettingData target) {
    m_Data = target;
}

NorthTeam::NorthTeam() {
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