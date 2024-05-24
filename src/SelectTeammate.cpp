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
    //std::shared_ptr<Member> Loki = std::make_shared<Loki>();
}