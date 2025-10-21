#ifndef HASHSEARCH_H
#define HASHSEARCH_H

#include <vector>
#include <list>
#include "Paper.h"

/**
 * @brief 哈希查找类 - 使用哈希表实现按ID的快速查找
 * 
 * 【同学B实现】
 * 
 * 功能：根据论文ID进行O(1)时间复杂度的快速查找
 * 类比：就像图书馆的"书号索引卡片柜"
 * 
 * 数据结构要求：
 * - 使用哈希表存储 (paperId -> Paper*)
 * - 冲突解决：链地址法（拉链法）
 * - 哈希函数：可以使用简单的除法哈希或乘法哈希
 * 
 * 性能要求：
 * - 查找时间：O(1) 平均情况
 * - 空间复杂度：O(n)
 */
class HashSearch {
private:
    // ==================== 数据结构（同学B设计） ====================
    
    static const int TABLE_SIZE = 1000;  // 哈希表大小（可调整）
    
    /**
     * 哈希表结构建议：
     * - 使用vector<list<Paper*>>作为哈希表
     * - 或者自己实现链表节点
     * 
     * 例如：
     * std::vector<std::list<Paper*>> hashTable;
     * 
     * 或者自定义节点：
     * struct HashNode {
     *     int paperId;
     *     Paper* paper;
     *     HashNode* next;
     * };
     * std::vector<HashNode*> hashTable;
     */
    
    std::vector<std::list<Paper*>> hashTable;  // 示例声明，同学B可以修改
    
    /**
     * @brief 哈希函数 - 将论文ID映射到哈希表索引
     * 
     * 【同学B实现】
     * 
     * 建议实现方式：
     * 1. 除法哈希：hash(key) = key % TABLE_SIZE
     * 2. 乘法哈希：hash(key) = floor(TABLE_SIZE * (key * A % 1))
     *    其中 A = 0.6180339887...（黄金分割比例）
     * 
     * @param paperId 论文ID
     * @return 哈希表索引 [0, TABLE_SIZE-1]
     */
    int hashFunction(int paperId) const;

public:
    // ==================== 构造函数和析构函数 ====================
    
    /**
     * @brief 构造函数 - 从论文列表构建哈希表
     * 
     * 【同学B实现】
     * 
     * 工作流程：
     * 1. 初始化哈希表（TABLE_SIZE个空链表）
     * 2. 遍历papers中的每篇论文
     * 3. 计算哈希值：index = hashFunction(paper.getPaperId())
     * 4. 将论文指针插入到hashTable[index]的链表中
     * 
     * @param papers 所有论文的引用
     */
    HashSearch(std::vector<Paper>& papers);
    
    /**
     * @brief 析构函数
     * 
     * 【同学B实现】
     * 
     * 注意：不需要删除Paper对象（它们由main.cpp的vector管理）
     *       只需清理哈希表结构本身
     */
    ~HashSearch();
    
    // ==================== 核心功能 ====================
    
    /**
     * @brief 按ID查找论文
     * 
     * 【同学B实现】
     * 
     * 算法步骤：
     * 1. 计算哈希值：index = hashFunction(paperId)
     * 2. 在hashTable[index]的链表中查找
     * 3. 比较链表中每个节点的paperId
     * 4. 找到返回指针，否则返回nullptr
     * 
     * @param paperId 要查找的论文ID
     * @return 论文指针，找不到则返回nullptr
     * 
     * 时间复杂度：O(1 + α)，其中α是装填因子
     */
    Paper* findById(int paperId);
    
    /**
     * @brief 插入新论文到哈希表
     * 
     * 【同学B实现】（可选功能）
     * 
     * @param paper 要插入的论文指针
     * @return 是否插入成功
     */
    bool insert(Paper* paper);
    
    /**
     * @brief 从哈希表中删除论文
     * 
     * 【同学B实现】（可选功能）
     * 
     * @param paperId 要删除的论文ID
     * @return 是否删除成功
     */
    bool remove(int paperId);
    
    // ==================== 辅助功能 ====================
    
    /**
     * @brief 打印哈希表的统计信息
     * 
     * 【同学B实现】（可选，用于性能分析）
     * 
     * 显示内容：
     * - 总论文数
     * - 哈希表大小
     * - 装填因子（load factor）
     * - 每个桶的链表长度分布
     * - 最长链表长度
     * - 空桶数量
     */
    void printStatistics() const;
    
    /**
     * @brief 重建哈希表（可选功能）
     * 
     * 【同学B实现】（可选）
     * 
     * 用途：当装填因子过高时，可以扩大哈希表并重新哈希
     * 
     * @param papers 所有论文的引用
     */
    void rebuild(std::vector<Paper>& papers);
};

// ==================== 性能分析建议（给同学B的提示） ====================

/*
 * 性能优化建议：
 * 
 * 1. 哈希函数选择：
 *    - 确保哈希值分布均匀
 *    - 可以测试不同哈希函数的冲突率
 * 
 * 2. 装填因子控制：
 *    - 装填因子 α = n / TABLE_SIZE
 *    - 当 α > 0.75 时考虑重建哈希表
 * 
 * 3. 冲突处理：
 *    - 链地址法简单但空间利用率可能不高
 *    - 可以考虑开放地址法（线性探测、二次探测）
 * 
 * 4. 测试数据：
 *    - 测试最好情况（无冲突）
 *    - 测试最坏情况（所有ID映射到同一个桶）
 *    - 测试平均情况（真实数据）
 */

#endif // HASHSEARCH_H
