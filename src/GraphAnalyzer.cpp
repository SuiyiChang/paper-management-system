// GraphAnalyzer.cpp
// 【同学C实现】
// 功能：构建论文引用关系图，进行BFS遍历分析

#include "GraphAnalyzer.h"
#include <iostream>
#include <set>
#include <algorithm>

// ==================== 构造函数 ====================
GraphAnalyzer::GraphAnalyzer(std::vector<Paper>& papers) {
    // TODO: 同学C实现
    // 1. 建立paperMap（paperId -> Paper*）
    // 2. 构建引用关系图（有向图）
    // 3. 构建关键词共享图（无向图，可选）
    
    std::cout << "GraphAnalyzer: 构造函数待实现" << std::endl;
    std::cout << "需要构建论文引用图和关键词共享图" << std::endl;
    
    // 示例代码框架：
    // 建立ID到Paper的映射
    for (auto& paper : papers) {
        paperMap[paper.getPaperId()] = &paper;
    }
    
    // TODO: 构建引用图
    // for (auto& paper : papers) {
    //     int paperId = paper.getPaperId();
    //     for (int refId : paper.getReferences()) {
    //         citationGraph[paperId].push_back(refId);
    //     }
    // }
    
    // TODO: 构建关键词共享图（注意：O(n²)复杂度）
    // for (size_t i = 0; i < papers.size(); i++) {
    //     for (size_t j = i + 1; j < papers.size(); j++) {
    //         if (hasSharedKeywords(&papers[i], &papers[j])) {
    //             // 添加无向边
    //             keywordGraph[papers[i].getPaperId()].push_back(papers[j].getPaperId());
    //             keywordGraph[papers[j].getPaperId()].push_back(papers[i].getPaperId());
    //         }
    //     }
    // }
}

// ==================== 析构函数 ====================
GraphAnalyzer::~GraphAnalyzer() {
    // 无需特殊处理（使用STL容器会自动清理）
}

// ==================== 辅助函数：检查关键词共享 ====================
bool GraphAnalyzer::hasSharedKeywords(const Paper* paper1, const Paper* paper2) const {
    // TODO: 同学C实现
    // 检查两篇论文是否至少共享一个关键词
    
    std::vector<std::string> keywords1 = paper1->getKeywords();
    std::vector<std::string> keywords2 = paper2->getKeywords();
    
    for (const auto& kw1 : keywords1) {
        for (const auto& kw2 : keywords2) {
            if (kw1 == kw2 && !kw1.empty()) {
                return true;
            }
        }
    }
    
    return false;
}

// ==================== 辅助函数：BFS ====================
std::vector<int> GraphAnalyzer::bfs(int startId, 
                                    const std::map<int, std::vector<int>>& graph,
                                    int maxDepth) const {
    // TODO: 同学C实现
    // BFS算法实现
    
    std::vector<int> result;
    std::set<int> visited;
    std::queue<std::pair<int, int>> q;  // <paperId, depth>
    
    q.push({startId, 0});
    visited.insert(startId);
    
    while (!q.empty()) {
        auto [currentId, depth] = q.front();
        q.pop();
        
        result.push_back(currentId);
        
        // 如果达到最大深度，不再扩展
        if (maxDepth != -1 && depth >= maxDepth) {
            continue;
        }
        
        // 遍历邻居
        auto it = graph.find(currentId);
        if (it != graph.end()) {
            for (int neighborId : it->second) {
                if (visited.find(neighborId) == visited.end()) {
                    visited.insert(neighborId);
                    q.push({neighborId, depth + 1});
                }
            }
        }
    }
    
    return result;
}

// ==================== 核心功能：基于引用关系的BFS ====================
std::vector<int> GraphAnalyzer::findRelatedPapersByBFS(int paperId) {
    // TODO: 同学C实现
    std::cout << "GraphAnalyzer::findRelatedPapersByBFS: 待实现" << std::endl;
    std::cout << "起始论文ID: " << paperId << std::endl;
    
    // 检查论文是否存在
    if (paperMap.find(paperId) == paperMap.end()) {
        std::cout << "错误：论文ID " << paperId << " 不存在" << std::endl;
        return std::vector<int>();
    }
    
    // 调用BFS遍历引用图
    return bfs(paperId, citationGraph, -1);
}

// ==================== 基于关键词共享的BFS ====================
std::vector<int> GraphAnalyzer::findRelatedPapersByKeywords(int paperId, int maxDepth) {
    // TODO: 同学C实现
    std::cout << "GraphAnalyzer::findRelatedPapersByKeywords: 待实现" << std::endl;
    
    if (paperMap.find(paperId) == paperMap.end()) {
        return std::vector<int>();
    }
    
    return bfs(paperId, keywordGraph, maxDepth);
}

// ==================== DFS（可选） ====================
std::vector<int> GraphAnalyzer::findRelatedPapersByDFS(int paperId) {
    // TODO: 同学C实现（可选）
    std::cout << "GraphAnalyzer::findRelatedPapersByDFS: 待实现" << std::endl;
    return std::vector<int>();
}

// ==================== 获取直接引用 ====================
std::vector<int> GraphAnalyzer::getDirectReferences(int paperId) const {
    // TODO: 同学C实现
    
    auto it = citationGraph.find(paperId);
    if (it != citationGraph.end()) {
        return it->second;
    }
    
    return std::vector<int>();
}

// ==================== 获取被引用情况 ====================
std::vector<int> GraphAnalyzer::getCitedBy(int paperId) const {
    // TODO: 同学C实现
    // 需要反向遍历图
    
    std::vector<int> result;
    
    for (const auto& [id, refs] : citationGraph) {
        // 如果refs中包含paperId，说明id引用了paperId
        if (std::find(refs.begin(), refs.end(), paperId) != refs.end()) {
            result.push_back(id);
        }
    }
    
    return result;
}

// ==================== 计算出度 ====================
int GraphAnalyzer::getOutDegree(int paperId) const {
    // TODO: 同学C实现
    
    auto it = citationGraph.find(paperId);
    if (it != citationGraph.end()) {
        return it->second.size();
    }
    
    return 0;
}

// ==================== 计算入度 ====================
int GraphAnalyzer::getInDegree(int paperId) const {
    // TODO: 同学C实现
    
    return getCitedBy(paperId).size();
}

// ==================== 找出最有影响力的论文（可选） ====================
std::vector<int> GraphAnalyzer::getMostInfluentialPapers(int topN) const {
    // TODO: 同学C实现（可选）
    std::cout << "GraphAnalyzer::getMostInfluentialPapers: 待实现" << std::endl;
    return std::vector<int>();
}

// ==================== 检测环（可选） ====================
bool GraphAnalyzer::hasCycle() const {
    // TODO: 同学C实现（可选）
    std::cout << "GraphAnalyzer::hasCycle: 待实现" << std::endl;
    return false;
}

// ==================== 打印统计信息 ====================
void GraphAnalyzer::printGraphStatistics() const {
    // TODO: 同学C实现（可选）
    
    std::cout << "\n==================== 图统计信息 ====================" << std::endl;
    std::cout << "节点数（论文数）: " << paperMap.size() << std::endl;
    
    int totalEdges = 0;
    for (const auto& [id, refs] : citationGraph) {
        totalEdges += refs.size();
    }
    std::cout << "边数（引用关系数）: " << totalEdges << std::endl;
    
    if (!paperMap.empty()) {
        double avgOutDegree = (double)totalEdges / paperMap.size();
        std::cout << "平均出度: " << avgOutDegree << std::endl;
    }
}
