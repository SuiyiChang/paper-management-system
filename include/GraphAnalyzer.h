#ifndef GRAPHANALYZER_H
#define GRAPHANALYZER_H

#include <vector>
#include <map>
#include <queue>
#include <string>
#include "Paper.h"

/**
 * @brief 图分析类 - 分析论文引用关系网络
 * 
 * 【同学C实现】
 * 
 * 功能：构建论文引用图，并进行图遍历分析
 * - 根据引用关系构建有向图
 * - 根据关键词共享构建无向图
 * - 使用BFS查找相关论文
 * 
 * 应用场景：
 * "我在研究深度学习，帮我找所有相关的论文"
 * → 从一篇深度学习论文出发
 * → 找它引用的所有论文（向外引用）
 * → 找引用它的所有论文（被引用）
 * → 找共享关键词的论文
 * → 形成一个研究主题的"论文网络"
 * 
 * 图的表示：
 * - 节点：论文（用paperId标识）
 * - 边：引用关系或关键词共享关系
 */
class GraphAnalyzer {
private:
    // ==================== 数据结构（同学C设计） ====================
    
    /**
     * 图的表示方式（建议使用邻接表）
     * 
     * 方式1：使用map存储邻接表
     * std::map<int, std::vector<int>> adjacencyList;
     * adjacencyList[1001] = {1002, 1003}  // 论文1001引用了1002和1003
     * 
     * 方式2：使用Paper指针
     * std::map<Paper*, std::vector<Paper*>> adjacencyList;
     * 
     * 方式3：同时维护两个图
     * - citationGraph: 引用关系图（有向图）
     * - keywordGraph: 关键词共享图（无向图）
     */
    
    std::map<int, std::vector<int>> citationGraph;  // 引用关系图（有向）
    std::map<int, std::vector<int>> keywordGraph;   // 关键词共享图（无向）
    std::map<int, Paper*> paperMap;                 // paperId -> Paper*的映射
    
    /**
     * @brief 检查两篇论文是否共享关键词
     * 
     * 【同学C实现】
     * 
     * @param paper1 第一篇论文
     * @param paper2 第二篇论文
     * @return 是否至少共享一个关键词
     */
    bool hasSharedKeywords(const Paper* paper1, const Paper* paper2) const;
    
    /**
     * @brief 广度优先搜索辅助函数
     * 
     * 【同学C实现】
     * 
     * @param startId 起始论文ID
     * @param graph 要遍历的图（引用图或关键词图）
     * @param maxDepth 最大搜索深度（-1表示无限制）
     * @return 按BFS顺序访问的论文ID列表
     */
    std::vector<int> bfs(int startId, 
                         const std::map<int, std::vector<int>>& graph,
                         int maxDepth = -1) const;

public:
    // ==================== 构造函数和析构函数 ====================
    
    /**
     * @brief 构造函数 - 从论文列表构建图
     * 
     * 【同学C实现】
     * 
     * 工作流程：
     * 1. 遍历所有论文，建立paperMap（paperId -> Paper*）
     * 2. 构建引用关系图：
     *    - 遍历每篇论文的references字段
     *    - 添加有向边：paper -> referenced_paper
     * 3. 构建关键词共享图：
     *    - 对于任意两篇论文(i, j)，如果共享关键词
     *    - 添加无向边：i <-> j
     * 
     * 注意：关键词图的构建是O(n²)，需要优化或限制规模
     * 
     * @param papers 所有论文的引用
     */
    GraphAnalyzer(std::vector<Paper>& papers);
    
    /**
     * @brief 析构函数
     * 
     * 【同学C实现】
     */
    ~GraphAnalyzer();
    
    // ==================== 核心功能 ====================
    
    /**
     * @brief 查找相关论文（基于引用关系的BFS）
     * 
     * 【同学C实现】
     * 
     * 功能编号：12. 查找相关论文 (BFS)
     * 
     * BFS算法步骤：
     * 1. 创建队列queue，将起始论文加入队列
     * 2. 创建visited数组，标记起始论文已访问
     * 3. 当队列不为空时：
     *    a. 取出队首论文current
     *    b. 将current加入结果列表
     *    c. 遍历current的所有邻居（它引用的论文）
     *    d. 如果邻居未访问，标记为已访问并加入队列
     * 4. 返回结果列表
     * 
     * @param paperId 起始论文ID
     * @return 相关论文的ID列表（按BFS顺序）
     * 
     * 时间复杂度：O(V + E)，V是论文数，E是引用关系数
     */
    std::vector<int> findRelatedPapersByBFS(int paperId);
    
    /**
     * @brief 查找相关论文（基于关键词共享的BFS）
     * 
     * 【同学C实现】
     * 
     * 与findRelatedPapersByBFS类似，但使用keywordGraph
     * 
     * @param paperId 起始论文ID
     * @param maxDepth 最大搜索深度（避免搜索整个图）
     * @return 相关论文的ID列表
     */
    std::vector<int> findRelatedPapersByKeywords(int paperId, int maxDepth = 2);
    
    /**
     * @brief 深度优先搜索（可选功能）
     * 
     * 【同学C实现】（可选）
     * 
     * 使用DFS遍历图，对比BFS的行为差异
     * 
     * @param paperId 起始论文ID
     * @return 相关论文的ID列表（按DFS顺序）
     */
    std::vector<int> findRelatedPapersByDFS(int paperId);
    
    /**
     * @brief 找出论文的直接引用（出度邻居）
     * 
     * 【同学C实现】
     * 
     * @param paperId 论文ID
     * @return 该论文直接引用的所有论文ID
     */
    std::vector<int> getDirectReferences(int paperId) const;
    
    /**
     * @brief 找出引用该论文的所有论文（入度邻居）
     * 
     * 【同学C实现】
     * 
     * 需要反向遍历图
     * 
     * @param paperId 论文ID
     * @return 引用该论文的所有论文ID
     */
    std::vector<int> getCitedBy(int paperId) const;
    
    // ==================== 图统计功能 ====================
    
    /**
     * @brief 计算论文的出度（引用了多少篇论文）
     * 
     * 【同学C实现】
     * 
     * @param paperId 论文ID
     * @return 出度
     */
    int getOutDegree(int paperId) const;
    
    /**
     * @brief 计算论文的入度（被多少篇论文引用）
     * 
     * 【同学C实现】
     * 
     * @param paperId 论文ID
     * @return 入度
     */
    int getInDegree(int paperId) const;
    
    /**
     * @brief 找出最有影响力的论文（入度最高）
     * 
     * 【同学C实现】（可选）
     * 
     * @param topN 返回前N篇
     * @return 论文ID列表，按入度降序
     */
    std::vector<int> getMostInfluentialPapers(int topN = 10) const;
    
    /**
     * @brief 检测图中的环（可选功能）
     * 
     * 【同学C实现】（可选，较难）
     * 
     * 使用DFS检测有向图中是否存在环
     * 
     * @return 是否存在环
     */
    bool hasCycle() const;
    
    /**
     * @brief 打印图的统计信息
     * 
     * 【同学C实现】（可选）
     * 
     * 显示内容：
     * - 节点数（论文数）
     * - 边数（引用关系数）
     * - 平均出度/入度
     * - 最大出度/入度
     */
    void printGraphStatistics() const;
};

// ==================== 实现建议（给同学C的提示） ====================

/*
 * 实现建议：
 * 
 * 1. 图的构建：
 *    - 引用图是有向图：paper1 -> paper2 表示paper1引用paper2
 *    - 关键词图是无向图：如果两篇论文共享关键词，双向连接
 *    - 使用邻接表比邻接矩阵更节省空间（稀疏图）
 * 
 * 2. BFS实现：
 *    - 使用std::queue<int>作为队列
 *    - 使用std::set<int>或bool数组标记已访问节点
 *    - 伪代码：
 *      queue.push(startId)
 *      visited.insert(startId)
 *      while (!queue.empty()) {
 *          current = queue.front()
 *          queue.pop()
 *          result.push_back(current)
 *          for (neighbor : graph[current]) {
 *              if (!visited.count(neighbor)) {
 *                  visited.insert(neighbor)
 *                  queue.push(neighbor)
 *              }
 *          }
 *      }
 * 
 * 3. 关键词共享判断：
 *    - 方法1：双重循环比较两个关键词列表
 *    - 方法2：使用set交集
 *      set<string> keys1(paper1->getKeywords().begin(), ...);
 *      set<string> keys2(paper2->getKeywords().begin(), ...);
 *      vector<string> intersection;
 *      set_intersection(keys1.begin(), keys1.end(), 
 *                       keys2.begin(), keys2.end(),
 *                       back_inserter(intersection));
 *      return !intersection.empty();
 * 
 * 4. 性能优化：
 *    - 关键词图的构建是O(n²)，对于大数据集可能很慢
 *    - 可以只连接共享2个以上关键词的论文
 *    - 或者限制每篇论文的邻居数量
 * 
 * 5. 图遍历的应用：
 *    - BFS：找最短路径、层次关系
 *    - DFS：找连通分量、检测环
 * 
 * 6. 测试用例：
 *    - 测试单个节点（无引用）
 *    - 测试线性引用链：A->B->C->D
 *    - 测试环状引用：A->B->C->A
 *    - 测试星形引用：A引用B,C,D,E...
 */

#endif // GRAPHANALYZER_H
