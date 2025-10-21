#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include <vector>
#include <map>
#include <string>
#include "Paper.h"

/**
 * @brief 推荐系统类 - 基于关键词的论文推荐和热门词分析
 * 
 * 【同学C实现】
 * 
 * 功能1：统计热门关键词（Top-N）
 * - 统计所有论文的关键词频率
 * - 返回出现次数最多的N个关键词
 * 
 * 功能2：基于关键词相似度的论文推荐
 * - 给定一篇起始论文
 * - 找出与它关键词最相似的Top-N篇论文
 * 
 * 相似度计算：
 * - 简单方法：共享关键词的数量
 * - 加权方法：稀有关键词权重更高
 * - 高级方法：TF-IDF、余弦相似度
 */
class Recommender {
private:
    std::vector<Paper> papers;  // 所有论文
    
    /**
     * 关键词频率统计
     * keyword -> 出现该关键词的论文数量
     */
    std::map<std::string, int> keywordFrequency;
    
    // ==================== 辅助数据结构 ====================
    
    /**
     * @brief 推荐项结构（用于Top-N推荐）
     * 
     * 存储论文ID和相似度分数
     */
    struct RecommendationItem {
        int paperId;           // 论文ID
        int similarityScore;   // 相似度分数（共享关键词数量）
        
        RecommendationItem(int id, int score) 
            : paperId(id), similarityScore(score) {}
    };
    
    /**
     * @brief 最小堆节点（用于Top-N算法）
     * 
     * 维护一个大小为N的最小堆，堆顶是当前Top-N中相似度最小的
     */
    struct MinHeapNode {
        int paperId;
        int score;
        
        bool operator>(const MinHeapNode& other) const {
            return score > other.score;  // 最小堆：父节点 < 子节点
        }
    };
    
    // ==================== 辅助函数（同学C实现） ====================
    
    /**
     * @brief 统计所有关键词的频率
     * 
     * 【同学C实现】
     * 
     * 遍历所有论文，统计每个关键词出现的次数
     * 
     * 伪代码：
     * for paper in papers:
     *     for keyword in paper.keywords:
     *         keywordFrequency[keyword]++
     */
    void buildKeywordFrequency();
    
    /**
     * @brief 计算两篇论文的关键词相似度
     * 
     * 【同学C实现】
     * 
     * 方法1：简单计数
     * - 返回共享关键词的数量
     * 
     * 方法2：加权计数（进阶）
     * - 稀有关键词（低频）权重更高
     * - similarity = Σ (1 / frequency[keyword]) for shared keywords
     * 
     * @param paper1 第一篇论文
     * @param paper2 第二篇论文
     * @param useWeighting 是否使用加权方法
     * @return 相似度分数
     */
    int calculateSimilarity(const Paper& paper1, const Paper& paper2, 
                           bool useWeighting = false) const;
    
    /**
     * @brief 堆的向上调整
     * 
     * 【同学C实现】
     * 
     * 当插入新元素时，将其与父节点比较并上浮
     * 
     * @param heap 堆数组
     * @param index 要调整的节点索引
     */
    void heapifyUp(std::vector<MinHeapNode>& heap, int index);
    
    /**
     * @brief 堆的向下调整
     * 
     * 【同学C实现】
     * 
     * 当替换堆顶元素时，将其与子节点比较并下沉
     * 
     * @param heap 堆数组
     * @param index 要调整的节点索引
     */
    void heapifyDown(std::vector<MinHeapNode>& heap, int index);

public:
    // ==================== 构造函数和析构函数 ====================
    
    /**
     * @brief 构造函数
     * 
     * 【同学C实现】
     * 
     * 初始化推荐系统，统计关键词频率
     * 
     * @param papers 所有论文的引用
     */
    Recommender(const std::vector<Paper>& papers);
    
    /**
     * @brief 析构函数
     */
    ~Recommender();
    
    // ==================== 核心功能 ====================
    
    /**
     * @brief 获取Top-N热门关键词
     * 
     * 【同学C实现】
     * 
     * 功能编号：13. 获取关键词推荐 (Top-N)
     * 
     * 算法选择：
     * 
     * 方法1：排序法（简单）
     * 1. 将keywordFrequency转换为vector
     * 2. 按频率降序排序
     * 3. 返回前N个
     * 时间复杂度：O(m log m)，m是关键词种类数
     * 
     * 方法2：堆排序（推荐）
     * 1. 建立一个大小为N的最小堆
     * 2. 遍历所有关键词：
     *    - 如果堆未满，直接插入
     *    - 如果堆已满且当前频率 > 堆顶频率，替换堆顶
     * 3. 堆中剩下的就是Top-N
     * 时间复杂度：O(m log N)，N通常远小于m
     * 
     * @param n 返回前N个关键词（默认10）
     * @return 关键词-频率对的向量，按频率降序
     * 
     * 返回格式：
     * [("Deep Learning", 15), ("Neural Networks", 12), ...]
     */
    std::vector<std::pair<std::string, int>> getTopKeywords(int n = 10);
    
    /**
     * @brief 为指定论文推荐相似论文（Top-N）
     * 
     * 【同学C实现】
     * 
     * 算法：使用最小堆维护Top-N相似论文
     * 
     * 步骤：
     * 1. 获取目标论文target
     * 2. 创建大小为N的最小堆
     * 3. 遍历所有其他论文：
     *    a. 计算与target的相似度
     *    b. 如果相似度 > 0：
     *       - 如果堆未满，插入
     *       - 如果堆已满且相似度 > 堆顶，替换堆顶
     * 4. 将堆中元素按相似度降序排序并返回
     * 
     * @param paperId 目标论文ID
     * @param n 推荐数量（默认10）
     * @param useWeighting 是否使用加权相似度
     * @return 推荐论文的ID和相似度分数，按相似度降序
     * 
     * 时间复杂度：O(n log N)，n是论文总数，N是推荐数量
     */
    std::vector<std::pair<int, int>> recommendSimilarPapers(
        int paperId, 
        int n = 10,
        bool useWeighting = false
    );
    
    /**
     * @brief 获取包含指定关键词的所有论文
     * 
     * 【同学C实现】
     * 
     * @param keyword 关键词
     * @return 包含该关键词的论文ID列表
     */
    std::vector<int> getPapersByKeyword(const std::string& keyword) const;
    
    /**
     * @brief 获取包含任一指定关键词的论文（OR查询）
     * 
     * 【同学C实现】
     * 
     * @param keywords 关键词列表
     * @return 包含任一关键词的论文ID列表
     */
    std::vector<int> getPapersByKeywordsOR(const std::vector<std::string>& keywords) const;
    
    /**
     * @brief 获取包含所有指定关键词的论文（AND查询）
     * 
     * 【同学C实现】
     * 
     * @param keywords 关键词列表
     * @return 包含所有关键词的论文ID列表
     */
    std::vector<int> getPapersByKeywordsAND(const std::vector<std::string>& keywords) const;
    
    // ==================== 辅助功能 ====================
    
    /**
     * @brief 打印关键词统计信息
     * 
     * 【同学C实现】（可选）
     * 
     * 显示内容：
     * - 总关键词种类数
     * - 最热门的10个关键词
     * - 只出现一次的关键词数量
     */
    void printKeywordStatistics() const;
    
    /**
     * @brief 显示推荐结果
     * 
     * 【同学C实现】
     * 
     * 格式化显示推荐论文列表
     * 
     * @param recommendations 推荐结果（论文ID和相似度）
     * @param papers 所有论文的引用（用于显示论文信息）
     */
    static void displayRecommendations(
        const std::vector<std::pair<int, int>>& recommendations,
        const std::vector<Paper>& papers
    );
};

// ==================== 实现建议（给同学C的提示） ====================

/*
 * 实现建议：
 * 
 * 1. Top-N关键词算法（堆方法）：
 *    // 创建最小堆（大小为N）
 *    vector<MinHeapNode> heap;
 *    
 *    for (auto& [keyword, frequency] : keywordFrequency) {
 *        if (heap.size() < n) {
 *            // 堆未满，直接插入
 *            heap.push_back({keyword, frequency});
 *            heapifyUp(heap, heap.size() - 1);
 *        } else if (frequency > heap[0].frequency) {
 *            // 堆已满，且当前频率大于堆顶
 *            heap[0] = {keyword, frequency};
 *            heapifyDown(heap, 0);
 *        }
 *    }
 *    
 *    // 将堆中元素排序（降序）
 *    sort(heap.begin(), heap.end(), ...);
 * 
 * 2. 最小堆的维护：
 *    向上调整（插入新元素）：
 *    void heapifyUp(vector<Node>& heap, int i) {
 *        while (i > 0) {
 *            int parent = (i - 1) / 2;
 *            if (heap[i].score < heap[parent].score) {
 *                swap(heap[i], heap[parent]);
 *                i = parent;
 *            } else break;
 *        }
 *    }
 *    
 *    向下调整（替换堆顶）：
 *    void heapifyDown(vector<Node>& heap, int i) {
 *        int n = heap.size();
 *        while (2*i + 1 < n) {
 *            int left = 2*i + 1;
 *            int right = 2*i + 2;
 *            int smallest = i;
 *            
 *            if (left < n && heap[left].score < heap[smallest].score)
 *                smallest = left;
 *            if (right < n && heap[right].score < heap[smallest].score)
 *                smallest = right;
 *            
 *            if (smallest != i) {
 *                swap(heap[i], heap[smallest]);
 *                i = smallest;
 *            } else break;
 *        }
 *    }
 * 
 * 3. 相似度计算：
 *    简单版本：
 *    int similarity = 0;
 *    for (auto& kw1 : paper1.keywords) {
 *        for (auto& kw2 : paper2.keywords) {
 *            if (kw1 == kw2) similarity++;
 *        }
 *    }
 *    
 *    优化版本（使用set）：
 *    set<string> keys1(paper1.keywords.begin(), ...);
 *    set<string> keys2(paper2.keywords.begin(), ...);
 *    for (auto& k : keys1) {
 *        if (keys2.count(k)) similarity++;
 *    }
 * 
 * 4. 加权相似度（进阶）：
 *    double similarity = 0.0;
 *    for (shared_keyword in intersection) {
 *        // 频率越低，权重越高（IDF思想）
 *        similarity += 1.0 / keywordFrequency[shared_keyword];
 *    }
 * 
 * 5. 性能优化：
 *    - 预先构建关键词索引：keyword -> [paperId1, paperId2, ...]
 *    - 这样getPapersByKeyword可以O(1)完成
 *    - 相似度计算可以只遍历有共同关键词的论文
 * 
 * 6. 测试用例：
 *    - 测试没有关键词的论文
 *    - 测试关键词完全相同的论文
 *    - 测试关键词完全不同的论文
 *    - 测试Top-N的边界情况（N=0, N=1, N>总关键词数）
 */

#endif // RECOMMENDER_H
