#ifndef BSTSEARCH_H
#define BSTSEARCH_H

#include <vector>
#include <string>
#include "Paper.h"

/**
 * @brief 二叉搜索树查找类 - 使用BST实现按标题的有序查找
 * 
 * 【同学B实现】
 * 
 * 功能：根据论文标题进行O(log n)时间复杂度的查找
 * 类比：就像"字典查字"，利用有序性加速查找
 * 
 * BST性质：
 * - 左子树所有节点的标题 < 根节点的标题
 * - 右子树所有节点的标题 > 根节点的标题
 * - 左右子树也都是二叉搜索树
 * 
 * 性能要求：
 * - 查找时间：O(log n) 平均情况，O(n) 最坏情况
 * - 空间复杂度：O(n)
 */
class BSTSearch {
private:
    // ==================== 数据结构（同学B设计） ====================
    
    /**
     * BST节点结构
     * 
     * 【同学B实现】
     * 
     * 建议包含：
     * - title: 论文标题（作为键）
     * - paper: 指向Paper对象的指针
     * - left: 左子节点指针
     * - right: 右子节点指针
     * 
     * 也可以只存储Paper指针，通过paper->getTitle()获取标题
     */
    struct BSTNode {
        std::string title;      // 标题（键值）
        Paper* paper;           // 论文指针
        BSTNode* left;          // 左子树
        BSTNode* right;         // 右子树
        
        // 构造函数
        BSTNode(const std::string& t, Paper* p) 
            : title(t), paper(p), left(nullptr), right(nullptr) {}
    };
    
    BSTNode* root;  // 根节点指针
    
    // ==================== 辅助函数（同学B实现） ====================
    
    /**
     * @brief 递归插入节点
     * 
     * 【同学B实现】
     * 
     * 算法步骤：
     * 1. 如果当前节点为空，创建新节点返回
     * 2. 比较title与当前节点的title（使用strcmp或string比较）
     * 3. 如果title < 当前title，递归插入到左子树
     * 4. 如果title > 当前title，递归插入到右子树
     * 5. 如果title == 当前title，忽略或更新（标题重复）
     * 
     * @param node 当前节点
     * @param title 标题
     * @param paper 论文指针
     * @return 插入后的子树根节点
     */
    BSTNode* insertNode(BSTNode* node, const std::string& title, Paper* paper);
    
    /**
     * @brief 递归查找节点
     * 
     * 【同学B实现】
     * 
     * 算法步骤：
     * 1. 如果当前节点为空，返回nullptr
     * 2. 如果title == 当前title，返回当前节点的paper
     * 3. 如果title < 当前title，在左子树中查找
     * 4. 如果title > 当前title，在右子树中查找
     * 
     * @param node 当前节点
     * @param title 要查找的标题
     * @return 论文指针，找不到返回nullptr
     */
    Paper* searchNode(BSTNode* node, const std::string& title) const;
    
    /**
     * @brief 递归删除整棵树
     * 
     * 【同学B实现】
     * 
     * 后序遍历删除：先删除左右子树，再删除根节点
     * 注意：只删除BSTNode，不删除Paper对象
     * 
     * @param node 当前节点
     */
    void destroyTree(BSTNode* node);
    
    /**
     * @brief 中序遍历（用于打印所有论文）
     * 
     * 【同学B实现】（可选功能）
     * 
     * 中序遍历BST会按标题字母顺序访问所有节点
     * 
     * @param node 当前节点
     * @param result 存储遍历结果的向量
     */
    void inorderTraversal(BSTNode* node, std::vector<Paper*>& result) const;
    
    /**
     * @brief 计算树的高度
     * 
     * 【同学B实现】（可选，用于性能分析）
     * 
     * @param node 当前节点
     * @return 树的高度
     */
    int getHeight(BSTNode* node) const;

public:
    // ==================== 构造函数和析构函数 ====================
    
    /**
     * @brief 构造函数 - 从论文列表构建BST
     * 
     * 【同学B实现】
     * 
     * 工作流程：
     * 1. 初始化root为nullptr
     * 2. 遍历papers中的每篇论文
     * 3. 调用insertNode插入每篇论文
     * 
     * 注意：插入顺序会影响树的平衡性
     *       如果按标题有序插入，会退化成链表（最坏情况）
     * 
     * @param papers 所有论文的引用
     */
    BSTSearch(std::vector<Paper>& papers);
    
    /**
     * @brief 析构函数
     * 
     * 【同学B实现】
     * 
     * 调用destroyTree(root)删除所有节点
     */
    ~BSTSearch();
    
    // ==================== 核心功能 ====================
    
    /**
     * @brief 按标题查找论文（精确匹配）
     * 
     * 【同学B实现】
     * 
     * 调用searchNode(root, title)进行递归查找
     * 
     * @param title 要查找的标题
     * @return 论文指针，找不到则返回nullptr
     * 
     * 时间复杂度：O(log n) 平均，O(n) 最坏
     */
    Paper* findByTitle(const std::string& title);
    
    /**
     * @brief 按标题前缀查找（模糊匹配）
     * 
     * 【同学B实现】（可选功能）
     * 
     * 查找所有标题以prefix开头的论文
     * 
     * @param prefix 标题前缀
     * @return 匹配的论文列表
     */
    std::vector<Paper*> findByTitlePrefix(const std::string& prefix);
    
    /**
     * @brief 插入新论文
     * 
     * 【同学B实现】（可选功能）
     * 
     * @param paper 要插入的论文指针
     * @return 是否插入成功
     */
    bool insert(Paper* paper);
    
    /**
     * @brief 删除论文
     * 
     * 【同学B实现】（可选，BST删除较复杂）
     * 
     * BST删除需要考虑三种情况：
     * 1. 删除叶子节点
     * 2. 删除只有一个子节点的节点
     * 3. 删除有两个子节点的节点（找前驱或后继替换）
     * 
     * @param title 要删除的论文标题
     * @return 是否删除成功
     */
    bool remove(const std::string& title);
    
    // ==================== 辅助功能 ====================
    
    /**
     * @brief 获取所有论文（按标题字母顺序）
     * 
     * 【同学B实现】（可选）
     * 
     * 使用中序遍历获取有序列表
     * 
     * @return 按标题排序的论文列表
     */
    std::vector<Paper*> getAllSorted() const;
    
    /**
     * @brief 打印树的统计信息
     * 
     * 【同学B实现】（可选，用于性能分析）
     * 
     * 显示内容：
     * - 节点总数
     * - 树的高度
     * - 是否平衡
     * - 最长路径
     */
    void printStatistics() const;
    
    /**
     * @brief 检查树是否平衡
     * 
     * 【同学B实现】（可选）
     * 
     * 平衡定义：任意节点的左右子树高度差不超过1
     * 
     * @return 是否平衡
     */
    bool isBalanced() const;
};

// ==================== 实现建议（给同学B的提示） ====================

/*
 * 实现建议：
 * 
 * 1. 字符串比较：
 *    - 使用std::string的比较运算符（<, >, ==）
 *    - C风格字符串可以用strcmp()
 * 
 * 2. 树的平衡性：
 *    - 如果按标题有序插入，树会退化成链表
 *    - 可以考虑先打乱papers再插入
 *    - 或者实现AVL树/红黑树（进阶）
 * 
 * 3. 内存管理：
 *    - BSTNode是自己创建的，需要在析构函数中释放
 *    - Paper对象由main.cpp管理，不要释放
 * 
 * 4. 递归实现：
 *    - BST的操作天然适合递归
 *    - 注意递归终止条件（node == nullptr）
 * 
 * 5. 测试用例：
 *    - 测试标题完全匹配
 *    - 测试标题不存在
 *    - 测试标题大小写敏感性
 *    - 测试树的平衡性
 */

#endif // BSTSEARCH_H
