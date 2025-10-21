// HashSearch.cpp
// 【同学B实现】
// 功能：使用哈希表实现按ID的快速查找

#include "HashSearch.h"
#include <iostream>

// ==================== 构造函数 ====================
HashSearch::HashSearch(std::vector<Paper>& papers) {
    // TODO: 同学B实现
    // 1. 初始化哈希表（TABLE_SIZE个空链表）
    // 2. 遍历papers，为每篇论文计算哈希值并插入
    
    std::cout << "HashSearch: 构造函数待实现" << std::endl;
}

// ==================== 析构函数 ====================
HashSearch::~HashSearch() {
    // TODO: 同学B实现
    // 清理哈希表（如果使用指针）
}

// ==================== 哈希函数 ====================
int HashSearch::hashFunction(int paperId) const {
    // TODO: 同学B实现
    // 建议使用除法哈希：return paperId % TABLE_SIZE;
    return paperId % TABLE_SIZE;
}

// ==================== 核心查找功能 ====================
Paper* HashSearch::findById(int paperId) {
    // TODO: 同学B实现
    // 1. 计算哈希值：int index = hashFunction(paperId)
    // 2. 在hashTable[index]的链表中查找
    // 3. 找到返回Paper*，否则返回nullptr
    
    std::cout << "HashSearch::findById: 待实现，查找ID=" << paperId << std::endl;
    return nullptr;
}

// ==================== 插入功能（可选） ====================
bool HashSearch::insert(Paper* paper) {
    // TODO: 同学B实现（可选）
    return false;
}

// ==================== 删除功能（可选） ====================
bool HashSearch::remove(int paperId) {
    // TODO: 同学B实现（可选）
    return false;
}

// ==================== 统计信息（可选） ====================
void HashSearch::printStatistics() const {
    // TODO: 同学B实现（可选）
    std::cout << "HashSearch统计信息：待实现" << std::endl;
}

// ==================== 重建哈希表（可选） ====================
void HashSearch::rebuild(std::vector<Paper>& papers) {
    // TODO: 同学B实现（可选）
}
