#include "Enchant.hpp"
#include "Util/input.hpp"
#include "Util/Time.hpp"
#include "Util/SFX.hpp"
#include <cmath>
#include <utility>
class BattleSystem;
void Enchant::Start() {
    m_TypeGeneration = {20,20,20,20,20,20};
    m_mustFallbyNormal = {0,0,0,0,0,0};
    m_mustFallbyPowerup = {0,0,0,0,0,0};
    m_row = 6 , m_column = 5;
    m_unlimited = false;
    m_Array.resize(m_row);
    for (int i = 0; i < m_row; ++i) {
        m_Array[i].resize(m_column);
        for (int j = 0; j < m_column; ++j) {
            std::vector<std::string> paths = {"../assets/sprites/Stones/f.png"};
            m_Array[i][j] = std::make_shared<Stone>(paths); // 使用 make_shared 創建共享指標
            m_Array[i][j]->Start(i,j,m_TypeGeneration);
        }
    }
    m_state = state::Keeping;
    this->Draw();
}



void Enchant::Update() {
    m_battleSystem->Update();
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_column; ++j) {
            if(m_Array[i][j] != nullptr){
                m_Array[i][j]->Update();
            }
        }
    }
    switch (m_state) {
    case state::Keeping:
        KeepingStateUpdate();
        break;
    case state::Dragging:
        DraggingStateUpdate();
        break;
    case state::Moving:
        MovingStateUpdate();
        break;
    case state::Checking:
        CheckingStateUpdate();
        break;
    case state::Falling:
        FallingStateUpdate();
        break;
    case state::Explosing:
        ExplosingStateUpdate();
        break;
    case state::Unlimited:
        UnlimitedStateUpdate();
        break;
    }
}

void Enchant::Change(glm::vec2 pos1,glm::vec2 pos2){
    static auto SFX = Util::SFX("../assets/audio/moveGem.wav");
    SFX.Play();
    m_Array[pos1.x][pos1.y]->Change(m_Array[pos2.x][pos2.y]);
    std::swap(m_Array[int(pos1.x)][int(pos1.y)], m_Array[int(pos2.x)][int(pos2.y)]);
}

void Enchant::CheckMatch() {
    for(int i=0;i<m_row;i++){
        for(int j=0;j<m_column;j++){
            //LOG_DEBUG("Checking ({},{})",i+1,j+1);
            std::vector<std::shared_ptr<Stone>> RowList;
            RowList.push_back(m_Array[i][j]);
            while(j + RowList.size() < m_column ){
                if(m_Array[i][j]->GetType() == m_Array[i][j+RowList.size()]->GetType()){
                    RowList.push_back(m_Array[i][j+RowList.size()]);
                }else{
                    break;
                }
            }
            if(RowList.size() >= 3){
                m_explosionBar.push_back(RowList);
            }
            //LOG_DEBUG("Checking Rowlist(len):{}",RowList.size());
            std::vector<std::shared_ptr<Stone>> ColumnList;
            ColumnList.push_back(m_Array[i][j]);
            while(i + ColumnList.size() < m_row){
                if(m_Array[i][j]->GetType() == m_Array[i+ColumnList.size()][j]->GetType()){
                   // LOG_DEBUG("Add Stone to ({},{})pair",i+ColumnList.size()+1,j+1);
                    ColumnList.push_back(m_Array[i+ColumnList.size()][j]);
                }else{
                    break;
                }
            }
            if(ColumnList.size() >= 3){
                m_explosionBar.push_back(ColumnList);
            }
            //LOG_DEBUG("Checking Columnlist(len):{}",ColumnList.size());
        }
    }
}

void Enchant::DoFall() {
    for(int i=0;i<m_row;++i) {
        for(int loop=0;loop<4;loop++) {
            for (int j = 1; j < m_column; j++) {
                if (m_Array[i][j] != nullptr) {
                    if (m_Array[i][j - 1] == nullptr) {
                        m_Array[i][j - 1] = m_Array[i][j];
                        m_Array[i][j - 1]->SetPos(i, j - 1);
                        m_Array[i][j-1]->SetFalling();
                        m_Array[i][j].reset();
                    }
                }
            }
        }
    }
}

void Enchant::ShowEnchant() {
    for(int i=0;i<m_column;++i) {
        std::string lists = "";
        for (int j = 0; j < m_row; j++) {
            if(m_Array[j][4-i] != nullptr){
                lists += "V";
            }else{
                lists += "X";
            }
        }
        LOG_DEBUG("{}",lists);
    }
    LOG_DEBUG("-----------");
}

void Enchant::GenerateFall(bool powerup) {
    int checking = 0;
    std::vector<std::shared_ptr<Stone>> emptyList;
    std::default_random_engine rng(std::random_device{}());

    for(int i=0;i<m_row;i++){
        for(int j=0;j<m_column;j++){
            if(m_Array[i][j] == nullptr){
                std::vector<std::string> paths = {"../assets/sprites/Gray.png"};
                m_Array[i][j] = std::make_shared<Stone>(paths); // 使用 make_shared 創建共享指標
                m_Array[i][j]->Generate(i,j,m_TypeGeneration);
                if(powerup) m_Array[i][j]->TurnType(m_Array[i][j]->GetType(),true);
                emptyList.push_back(m_Array[i][j]);
            }
        }
    }
    std::shuffle(emptyList.begin(), emptyList.end(), rng);
    int count=0;
    while(checking < 6 && count < emptyList.size()){
        if(m_mustFallbyNormal[checking] > 0){
            emptyList[count]->TurnType(Type::TypeList(checking), false);
            m_mustFallbyNormal[checking] --;
            count ++;
           // LOG_DEBUG("still need to fall at least [{},{},{},{},{},{}]", m_mustFallbyNormal[0],m_mustFallbyNormal[1],m_mustFallbyNormal[2],m_mustFallbyNormal[3],m_mustFallbyNormal[4],m_mustFallbyNormal[5] );
        }else if(m_mustFallbyPowerup[checking] > 0){
            m_mustFallbyPowerup[checking]--;
            emptyList[count]->TurnType(Type::TypeList(checking), true);
            count ++;
        }else{
            checking++;
        }
    }
}
int Enchant::CountEmpty() {
    int count=0;
    for(int i=0;i<m_row;i++){
        for(int j=0;j<m_column;j++){
            if(m_Array[i][j] == nullptr){
                count++;
            }
        }
    }
    return count;
}
bool Enchant::CheckFall() {
    for(int i=0;i<m_row;i++) {
        for (int j = 0; j < m_column; j++) {
            if(m_Array[i][j]->GetState() != Stone::state::Keeping){
                return false;
            }
        }
    }
    return true;
}

bool Enchant::CheckFull(){
    for(int i=0;i<m_row;i++){
        for(int j=0;j<m_column;j++){
            if(m_Array[i][j] == nullptr){
                return false;
            }
        }
    }
    return true;
}

/*method*/
void Enchant::KeepingStateUpdate() {

    if (Util::Input::IsKeyDown(Util::Keycode::T)) {
        m_battleSystem->SkillTrigger(0);
    }
    if (Util::Input::IsKeyDown(Util::Keycode::Y)) {
        m_battleSystem->SkillTrigger(1);
    }
    if (Util::Input::IsKeyDown(Util::Keycode::U)) {
        m_battleSystem->SkillTrigger(2);
    }
    if (Util::Input::IsKeyDown(Util::Keycode::I)) {
        m_battleSystem->SkillTrigger(3);
    }
    if (Util::Input::IsKeyDown(Util::Keycode::O)) {
        m_battleSystem->SkillTrigger(4);
    }
    if (Util::Input::IsKeyDown(Util::Keycode::P)) {
        m_battleSystem->SkillTrigger(5);
    }
    if (Util::Input::IsKeyDown(Util::Keycode::SPACE)) {
        auto cursorPos = Util::Input::GetCursorPosition();
        LOG_DEBUG("[{},{}]",cursorPos.x,cursorPos.y);
    }
    if (Util::Input::IsKeyDown(Util::Keycode::M)) {
        SetDraggingTime(20);
        SetState(state::Unlimited);
    }
    if (Util::Input::IsKeyDown(Util::Keycode::E)) {
        auto cursorPos = Util::Input::GetCursorPosition();
        int i = std::clamp(static_cast<int>(std::floor((cursorPos.x + 225) / 75)), 0, 5);
        int j = std::clamp(static_cast<int>(std::floor((cursorPos.y + 350) / 78)), 0, 4);
        m_Array[i][j]->SetDragging(true);
        m_StartPos = glm::vec2(i, j);
        m_NowPos = m_StartPos;
        m_firstBreak = true;
       // LOG_DEBUG("you got the {} Stone", Type::TypeString(m_Array[i][j]->GetType()));
        m_state = state::Dragging;
    }

}

void Enchant::DraggingStateUpdate() {
    if (Util::Input::IsMouseMoving()) {
        auto cursorPos = Util::Input::GetCursorPosition();
        int i = std::clamp(static_cast<int>(std::floor((cursorPos.x + 225) / 75)), 0, 5);
        int j = std::clamp(static_cast<int>(std::floor((cursorPos.y + 350) / 78)), 0, 4);
        if (!(m_StartPos == glm::vec2(i, j))) {
           // LOG_DEBUG("Let's Moving to [{}, {}] from [{}, {}]", i + 1, j + 1, static_cast<int>(m_NowPos.x) + 1, static_cast<int>(m_NowPos.y) + 1);
            Change(m_StartPos, glm::vec2(i, j));
            m_NowPos = glm::vec2(i, j);
            if(! m_unlimited)m_DraggingTime = m_battleSystem->GetDraggingTime();

            m_state = state::Moving;
            return;
        }
    }
    if (Util::Input::IsKeyUp(Util::Keycode::E)) {
        m_Array[static_cast<int>(m_StartPos.x)][static_cast<int>(m_StartPos.y)]->SetDragging(false);
        if(m_unlimited){
            m_state = state::Unlimited;
        }else{
            m_state = state::Keeping;
        }

       // LOG_DEBUG("you put the {} row, {} column Stone", static_cast<int>(m_StartPos.x) + 1, static_cast<int>(m_StartPos.y) + 1);
    }
}

void Enchant::MovingStateUpdate() {
    if (Util::Input::IsMouseMoving()) {
        auto cursorPos = Util::Input::GetCursorPosition();
        int i = std::clamp(static_cast<int>(std::floor((cursorPos.x + 225) / 75)), 0, 5);
        int j = std::clamp(static_cast<int>(std::floor((cursorPos.y + 350) / 78)), 0, 4);
        if (!(m_NowPos == glm::vec2(i, j))) {
            Change(m_NowPos, glm::vec2(i, j));
            m_NowPos = glm::vec2(i, j);
           // LOG_DEBUG("You are now at [{}, {}]", static_cast<int>(m_NowPos.x) + 1, static_cast<int>(m_NowPos.y) + 1);
            return;
        }
    }
    if (Util::Input::IsKeyUp(Util::Keycode::E) || m_DraggingTime <= 0) {
        m_Array[static_cast<int>(m_StartPos.x)][static_cast<int>(m_StartPos.y)]->SetDragging(false);
        m_EndPos = m_NowPos;
        if(m_unlimited){
            auto cursorPos = Util::Input::GetCursorPosition();
            int i = std::clamp(static_cast<int>(std::floor((cursorPos.x + 225) / 75)), 0, 5);
            int j = std::clamp(static_cast<int>(std::floor((cursorPos.y + 350) / 78)), 0, 4);
            m_Array[i][j]->SetDragging(false);
            m_state = state::Unlimited;
        }else{
            m_state = state::Checking;
        }

    }
    auto delta = static_cast<float>(Util::Time::GetDeltaTime());
    m_DraggingTime -= delta;
    //LOG_DEBUG("U have {} S left",m_DraggingTime);
}
void Enchant::CheckingStateUpdate() {
    const int row = 6, column = 5;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            m_Array[i][j]->SetDragging(false);
        }
    }
    CheckMatch();
    organizePairs();
    ShowExplosionBar();

    if(! (m_explosionBar.empty())){
        m_state = state::Explosing;
        return;
    }

    if(CheckFull()){
        m_battleSystem->ShowData();
        m_battleSystem->DamageSettle();
        m_battleSystem->ResetRound();
        m_state = state::Keeping;
    }else{
        m_state = state::Falling;
    }

}

void Enchant::ExplosingStateUpdate() {
    if(! m_explosionBar.empty()){
        if(m_firstBreak){
            if(m_battleSystem->DealFirstPiar(m_explosionBar[0])){
                for(int i=0;i<m_explosionBar[0].size();i++){
                    m_Array[m_explosionBar[0][i]->GetRow()][m_explosionBar[0][i]->GetColumn()].reset();
                }
                m_explosionBar.erase(m_explosionBar.begin());
            }
        }else{
            if(m_battleSystem->DealPair(m_explosionBar[0])){
                for(int i=0;i<m_explosionBar[0].size();i++){
                    m_Array[m_explosionBar[0][i]->GetRow()][m_explosionBar[0][i]->GetColumn()].reset();
                }
                m_explosionBar.erase(m_explosionBar.begin());
            }
        }

    }

    if(m_explosionBar.empty()){
        m_state = state::Falling;
    }
}
void Enchant::ShowExplosionBar() {

    //LOG_DEBUG("there's {} pairs in m_explosionBar",m_explosionBar.size());
    for(int i=0;i<m_explosionBar.size();i++){
        std::string pairFor1 = "[";
        for (int j = 0; j < m_explosionBar[i].size(); ++j) {
            pairFor1 += ( "(" +  std::to_string(m_explosionBar[i][j]->GetRow())  + "," + std::to_string(m_explosionBar[i][j]->GetColumn()) + "),");
        }
        //LOG_DEBUG("{}] {} stones",pairFor1,m_explosionBar[i].size());
    }
}
void Enchant::FallingStateUpdate() {
    DoFall();
    GenerateFall(false);
    m_firstBreak = false;
    if(CheckFall()){
        /*if (Util::Input::IsKeyDown(Util::Keycode::SPACE)) {

        }*/
        m_state = state::Checking;
    }
}

void Enchant::UnlimitedStateUpdate() {
    auto delta = static_cast<float>(Util::Time::GetDeltaTime());
    m_DraggingTime -= delta;
    //LOG_DEBUG("U have {} S left",m_DraggingTime);
    if(m_DraggingTime <= 0){
        m_state = state::Checking;
        m_unlimited = false;
    }
    if (Util::Input::IsKeyDown(Util::Keycode::E)) {
        auto cursorPos = Util::Input::GetCursorPosition();
        int i = std::clamp(static_cast<int>(std::floor((cursorPos.x + 225) / 75)), 0, 5);
        int j = std::clamp(static_cast<int>(std::floor((cursorPos.y + 350) / 78)), 0, 4);
        m_Array[i][j]->SetDragging(true);
        m_StartPos = glm::vec2(i, j);
        m_NowPos = m_StartPos;
        m_firstBreak = true;
        // LOG_DEBUG("you got the {} Stone", Type::TypeString(m_Array[i][j]->GetType()));
        m_state = state::Dragging;
    }
}

bool Enchant::checkOverlap(const std::vector<std::shared_ptr<Stone>>& pair1, const std::vector<std::shared_ptr<Stone>>& pair2) {
    for (const auto& member : pair1) {
        if (std::find(pair2.begin(), pair2.end(), member) != pair2.end()) {
            return true;
        }
    }
    return false;
}

std::vector<std::shared_ptr<Stone>> Enchant::mergePairs(const std::vector<std::shared_ptr<Stone>>& pair1, const std::vector<std::shared_ptr<Stone>>& pair2) {
    std::vector<std::shared_ptr<Stone>> mergedPair = pair1;
    for(const auto& member : pair2){
        if (std::find(pair1.begin(), pair1.end(), member) == pair1.end()) {
            mergedPair.push_back(member);
        }
    }
    return mergedPair;
}


std::vector<std::vector<std::shared_ptr<Stone>>> Enchant::organizePairs(){
    bool merged;
    do {
        merged = false;
        for (size_t i = 0; i < m_explosionBar.size(); ++i) {
            for (size_t j = i + 1; j < m_explosionBar.size(); ++j) {
                if (checkOverlap(m_explosionBar[i], m_explosionBar[j])) {
                    m_explosionBar[i] = mergePairs(m_explosionBar[i], m_explosionBar[j]);
                    m_explosionBar.erase(m_explosionBar.begin() + j);
                    merged = true;
                    break;
                }
            }
            if (merged) {
                break;
            }
        }
    } while (merged);

    return m_explosionBar;
}

std::shared_ptr<Enchant> Enchant::getEnchant() {
    return shared_from_this();
}

void Enchant::SetSystem(std::shared_ptr<BattleSystem> target) {
    m_battleSystem = target;
}

void Enchant::SetDraggingTime(int time) {
    m_DraggingTime = time;
}


void Enchant::SetState(Enchant::state target) {
    m_state = target;
    if(m_state == state::Unlimited) m_unlimited = true;
}

void Enchant::MustFall(Type::Element_type type, bool powerup) {
    if(powerup){
        m_mustFallbyPowerup[Type::FindIndex(type)] ++;
    }else{
        m_mustFallbyNormal[Type::FindIndex(type)] ++;
    }
}