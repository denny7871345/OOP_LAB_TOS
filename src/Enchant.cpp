#include "Enchant.hpp"

void Enchant::Start() {
    int row = 6 , column = 5;
    m_Array.resize(row);
    for (int i = 0; i < row; ++i) {
        m_Array[i].resize(column);
        for (int j = 0; j < column; ++j) {
            m_Array[i][j] = std::make_shared<Stone>(); // 使用 make_shared 創建共享指標
            m_Array[i][j]->Start(i,j);
        }
    }
}

void Enchant::Update() {
    int row = 6 , column = 5;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            m_Array[i][j]->Update();
        }
    }
}