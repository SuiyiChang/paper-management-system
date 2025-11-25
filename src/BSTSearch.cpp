// BSTSearch.cpp
// 【同学B实现】
// 功能：使用二叉搜索树实现按标题的有序查找

#include "BSTSearch.h"
#include <iostream>
#include <cstring>

// ==================== 构造函数 ====================
BSTSearch::BSTSearch(std::vector<Paper>& papers) : root(nullptr) {
    // 1. 初始化root为nullptr（已在初始化列表中完成）
    // 2. 遍历papers，逐个插入到BST中
    for (size_t i = 0; i < papers.size(); i++) {
        root = insertNode(root, papers[i].getTitle(), &papers[i]);
    }

    std::cout << "BSTSearch: 已构建二叉搜索树，共 " << papers.size()
              << " 篇论文，树高度: " << getHeight(root) << std::endl;
}

// ==================== 析构函数 ====================
BSTSearch::~BSTSearch() {
    // TODO: 同学B实现
    // 调用destroyTree释放所有节点
    destroyTree(root);
}

// ==================== 辅助函数：递归插入 ====================
BSTSearch::BSTNode* BSTSearch::insertNode(BSTNode* node, 
                                          const std::string& title, 
                                          Paper* paper) {
    // TODO: 同学B实现
    // 1. 如果node为空，创建新节点返回
    // 2. 比较title与node->title
    // 3. 小于则插入左子树，大于则插入右子树
    
    if (node == nullptr) {
        return new BSTNode(title, paper);
    }
    
    // 字符串比较：使用string的<运算符
    if (title < node->title) {
        node->left = insertNode(node->left, title, paper);
    } else if (title > node->title) {
        node->right = insertNode(node->right, title, paper);
    }
    // 如果title == node->title，忽略（标题重复）
    
    return node;
}

// ==================== 辅助函数：递归查找 ====================
Paper* BSTSearch::searchNode(BSTNode* node, const std::string& title) const {
    // TODO: 同学B实现
    // 1. 如果node为空，返回nullptr
    // 2. 如果title匹配，返回node->paper
    // 3. 小于则在左子树找，大于则在右子树找
    
    if (node == nullptr) {
        return nullptr;
    }
    
    if (title == node->title) {
        return node->paper;
    } else if (title < node->title) {
        return searchNode(node->left, title);
    } else {
        return searchNode(node->right, title);
    }
}

// ==================== 辅助函数：销毁树 ====================
void BSTSearch::destroyTree(BSTNode* node) {
    // TODO: 同学B实现
    // 后序遍历删除节点
    
    if (node == nullptr) return;
    
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

// ==================== 辅助函数：中序遍历（可选） ====================
void BSTSearch::inorderTraversal(BSTNode* node, 
                                 std::vector<Paper*>& result) const {
    // TODO: 同学B实现（可选）
    // 中序遍历：左 -> 根 -> 右
    
    if (node == nullptr) return;
    
    inorderTraversal(node->left, result);
    result.push_back(node->paper);
    inorderTraversal(node->right, result);
}

// ==================== 辅助函数：计算树高（可选） ====================
int BSTSearch::getHeight(BSTNode* node) const {
    // TODO: 同学B实现（可选）
    
    if (node == nullptr) return 0;
    
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// ==================== 核心查找功能 ====================
Paper* BSTSearch::findByTitle(const std::string& title) {
    // TODO: 同学B实现
    // 调用searchNode从根节点开始查找
    
    return searchNode(root, title);
}

// ==================== 前缀查找（可选） ====================
std::vector<Paper*> BSTSearch::findByTitlePrefix(const std::string& prefix) {
    // TODO: 同学B实现（可选）
    (void)prefix;  // 避免未使用参数警告
    std::vector<Paper*> result;
    std::cout << "BSTSearch::findByTitlePrefix: 待实现" << std::endl;
    return result;
}

// ==================== 插入功能（可选） ====================
bool BSTSearch::insert(Paper* paper) {
    // TODO: 同学B实现（可选）
    if (paper == nullptr) return false;
    
    root = insertNode(root, paper->getTitle(), paper);
    return true;
}

// ==================== 删除功能（可选） ====================
bool BSTSearch::remove(const std::string& title) {
    // TODO: 同学B实现（可选，BST删除较复杂）
    (void)title;  // 避免未使用参数警告
    std::cout << "BSTSearch::remove: 待实现" << std::endl;
    return false;
}

// ==================== 获取所有论文（有序）（可选） ====================
std::vector<Paper*> BSTSearch::getAllSorted() const {
    // TODO: 同学B实现（可选）
    std::vector<Paper*> result;
    inorderTraversal(root, result);
    return result;
}

// ==================== 统计信息（可选） ====================
void BSTSearch::printStatistics() const {
    // TODO: 同学B实现（可选）
    std::cout << "BST统计信息：" << std::endl;
    std::cout << "  树高度: " << getHeight(root) << std::endl;
}

// ==================== 检查平衡性（可选） ====================
bool BSTSearch::isBalanced() const {
    // TODO: 同学B实现（可选）
    return false;
}
