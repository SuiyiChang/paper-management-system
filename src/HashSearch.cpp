// HashSearch.cpp
// 【同学B实现】
// 功能：使用哈希表实现按ID的快速查找

#include "HashSearch.h"
#include <iostream>

// ==================== 构造函数 ====================
HashSearch::HashSearch(std::vector<Paper>& papers) {
    // 1. 初始化哈希表（TABLE_SIZE个空链表）
    hashTable.resize(TABLE_SIZE);

    // 2. 遍历papers，为每篇论文计算哈希值并插入
    for (size_t i = 0; i < papers.size(); i++) {
        int index = hashFunction(papers[i].getPaperId());
        hashTable[index].push_back(&papers[i]);
    }

    std::cout << "HashSearch: 已构建哈希表，共 " << papers.size() << " 篇论文" << std::endl;
}

// ==================== 析构函数 ====================
HashSearch::~HashSearch() {
    // 不需要删除Paper对象（它们由main.cpp的vector管理）
    // 只需清理哈希表结构本身
    hashTable.clear();
}

// ==================== 哈希函数 ====================
int HashSearch::hashFunction(int paperId) const {
    // 使用除法哈希：简单但有效
    return paperId % TABLE_SIZE;
}

// ==================== 核心查找功能 ====================
Paper* HashSearch::findById(int paperId) {
    // 1. 计算哈希值
    int index = hashFunction(paperId);

    // 2. 在hashTable[index]的链表中查找
    for (std::list<Paper*>::iterator it = hashTable[index].begin();
         it != hashTable[index].end(); ++it) {
        if ((*it)->getPaperId() == paperId) {
            // 3. 找到返回Paper*
            return *it;
        }
    }

    // 4. 找不到返回nullptr
    return nullptr;
}

// ==================== 插入功能（可选） ====================
bool HashSearch::insert(Paper* paper) {
    if (paper == nullptr) {
        return false;
    }

    int index = hashFunction(paper->getPaperId());

    // 检查是否已存在
    for (std::list<Paper*>::iterator it = hashTable[index].begin();
         it != hashTable[index].end(); ++it) {
        if ((*it)->getPaperId() == paper->getPaperId()) {
            return false;  // 已存在，不重复插入
        }
    }

    // 插入到链表头部
    hashTable[index].push_back(paper);
    return true;
}

// ==================== 删除功能（可选） ====================
bool HashSearch::remove(int paperId) {
    int index = hashFunction(paperId);

    // 在链表中查找并删除
    for (std::list<Paper*>::iterator it = hashTable[index].begin();
         it != hashTable[index].end(); ++it) {
        if ((*it)->getPaperId() == paperId) {
            hashTable[index].erase(it);
            return true;
        }
    }

    return false;  // 未找到
}

// ==================== 统计信息（可选） ====================
void HashSearch::printStatistics() const {
    std::cout << "\n========== 哈希表统计信息 ==========" << std::endl;

    int totalPapers = 0;
    int nonEmptyBuckets = 0;
    int maxChainLength = 0;

    for (int i = 0; i < TABLE_SIZE; i++) {
        int chainLength = hashTable[i].size();
        totalPapers += chainLength;

        if (chainLength > 0) {
            nonEmptyBuckets++;
        }

        if (chainLength > maxChainLength) {
            maxChainLength = chainLength;
        }
    }

    int emptyBuckets = TABLE_SIZE - nonEmptyBuckets;
    double loadFactor = (double)totalPapers / TABLE_SIZE;

    std::cout << "总论文数: " << totalPapers << std::endl;
    std::cout << "哈希表大小: " << TABLE_SIZE << std::endl;
    std::cout << "装填因子: " << loadFactor << std::endl;
    std::cout << "非空桶数: " << nonEmptyBuckets << std::endl;
    std::cout << "空桶数: " << emptyBuckets << std::endl;
    std::cout << "最长链长度: " << maxChainLength << std::endl;
    std::cout << "====================================" << std::endl;
}

// ==================== 重建哈希表（可选） ====================
void HashSearch::rebuild(std::vector<Paper>& papers) {
    // 清空当前哈希表
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i].clear();
    }

    // 重新插入所有论文
    for (size_t i = 0; i < papers.size(); i++) {
        int index = hashFunction(papers[i].getPaperId());
        hashTable[index].push_back(&papers[i]);
    }

    std::cout << "哈希表已重建" << std::endl;
}
