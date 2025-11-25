// Recommender.cpp
// 【同学C实现】
// 功能：基于关键词的推荐系统，Top-N算法

#include "Recommender.h"
#include <iostream>
#include <algorithm>
#include <set>

// ==================== 构造函数 ====================
Recommender::Recommender(const std::vector<Paper>& papers) {
    // 复制论文列表
    this->papers = papers;
    
    // TODO: 同学C实现
    // 统计关键词频率
    buildKeywordFrequency();
    
    std::cout << "Recommender: 构造完成，已统计 " 
              << keywordFrequency.size() << " 个不同关键词" << std::endl;
}

// ==================== 析构函数 ====================
Recommender::~Recommender() {
    // 无需特殊处理
}

// ==================== 辅助函数：统计关键词频率 ====================
void Recommender::buildKeywordFrequency() {
    // TODO: 同学C实现
    
    keywordFrequency.clear();
    
    for (const auto& paper : papers) {
        std::vector<std::string> keywords = paper.getKeywords();
        for (const auto& keyword : keywords) {
            if (!keyword.empty()) {
                keywordFrequency[keyword]++;
            }
        }
    }
}

// ==================== 辅助函数：计算相似度 ====================
int Recommender::calculateSimilarity(const Paper& paper1, 
                                     const Paper& paper2,
                                     bool useWeighting) const {
    // TODO: 同学C实现
    
    std::vector<std::string> keywords1 = paper1.getKeywords();
    std::vector<std::string> keywords2 = paper2.getKeywords();
    
    int similarity = 0;
    
    if (!useWeighting) {
        // 简单方法：统计共享关键词数量
        for (const auto& kw1 : keywords1) {
            if (kw1.empty()) continue;
            for (const auto& kw2 : keywords2) {
                if (kw1 == kw2) {
                    similarity++;
                    break;  // 同一个关键词只计数一次
                }
            }
        }
    } else {
        // 加权方法：稀有关键词权重更高（进阶）
        // TODO: 同学C实现加权算法
        std::cout << "加权相似度计算：待实现" << std::endl;
    }
    
    return similarity;
}

// ==================== 辅助函数：堆调整 ====================
void Recommender::heapifyUp(std::vector<MinHeapNode>& heap, int index) {
    // TODO: 同学C实现
    // 向上调整堆
    
    while (index > 0) {
        int parent = (index - 1) / 2;
        
        if (heap[index].score < heap[parent].score) {
            std::swap(heap[index], heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void Recommender::heapifyDown(std::vector<MinHeapNode>& heap, int index) {
    // TODO: 同学C实现
    // 向下调整堆
    
    int n = heap.size();
    
    while (2 * index + 1 < n) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;
        
        if (left < n && heap[left].score < heap[smallest].score) {
            smallest = left;
        }
        
        if (right < n && heap[right].score < heap[smallest].score) {
            smallest = right;
        }
        
        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

// ==================== 核心功能：获取Top-N关键词 ====================
std::vector<std::pair<std::string, int>> Recommender::getTopKeywords(int n) {
    // 使用排序算法找出频率最高的N个关键词
    // 时间复杂度：O(m log m)，其中m是不同关键词的数量

    std::cout << "正在统计关键词频率..." << std::endl;
    std::cout << "总关键词种类数: " << keywordFrequency.size() << std::endl;

    std::vector<std::pair<std::string, int>> result;
    
    // 方法1：排序法（简单但不够高效）
    for (std::map<std::string, int>::const_iterator it = keywordFrequency.begin();
         it != keywordFrequency.end(); ++it) {
        result.push_back({it->first, it->second});
    }

    // 按频率降序排序
    std::sort(result.begin(), result.end(),
              [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                  return a.second > b.second;
              });
    
    // 只返回前N个
    if (result.size() > (size_t)n) {
        result.resize(n);
    }
    
    // TODO: 方法2：堆方法（推荐，更高效）
    // 维护一个大小为N的最小堆
    // std::vector<MinHeapNode> heap;
    // ...
    
    return result;
}

// ==================== 核心功能：推荐相似论文 ====================
std::vector<std::pair<int, int>> Recommender::recommendSimilarPapers(
    int paperId, 
    int n,
    bool useWeighting) {
    
    // TODO: 同学C实现
    std::cout << "Recommender::recommendSimilarPapers: 待完善实现" << std::endl;
    std::cout << "为论文 " << paperId << " 推荐 " << n << " 篇相似论文" << std::endl;
    
    std::vector<std::pair<int, int>> result;
    
    // 找到目标论文
    Paper* targetPaper = nullptr;
    for (auto& paper : papers) {
        if (paper.getPaperId() == paperId) {
            targetPaper = &paper;
            break;
        }
    }
    
    if (targetPaper == nullptr) {
        std::cout << "错误：未找到论文ID " << paperId << std::endl;
        return result;
    }
    
    // TODO: 使用堆算法维护Top-N
    // 1. 创建最小堆（大小为N）
    // 2. 遍历所有其他论文，计算相似度
    // 3. 维护堆：如果堆未满直接插入，如果堆满且相似度>堆顶则替换
    
    // 临时实现：暴力排序法
    std::vector<std::pair<int, int>> allSimilarities;
    
    for (const auto& paper : papers) {
        if (paper.getPaperId() == paperId) continue;
        
        int similarity = calculateSimilarity(*targetPaper, paper, useWeighting);
        
        if (similarity > 0) {
            allSimilarities.push_back({paper.getPaperId(), similarity});
        }
    }
    
    // 按相似度降序排序
    std::sort(allSimilarities.begin(), allSimilarities.end(),
              [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                  return a.second > b.second;
              });
    
    // 返回前N个
    for (int i = 0; i < n && i < (int)allSimilarities.size(); i++) {
        result.push_back(allSimilarities[i]);
    }
    
    return result;
}

// ==================== 按关键词查找论文 ====================
std::vector<int> Recommender::getPapersByKeyword(const std::string& keyword) const {
    // TODO: 同学C实现
    
    std::vector<int> result;
    
    for (const auto& paper : papers) {
        std::vector<std::string> keywords = paper.getKeywords();
        
        for (const auto& kw : keywords) {
            if (kw == keyword) {
                result.push_back(paper.getPaperId());
                break;
            }
        }
    }
    
    return result;
}

// ==================== OR查询 ====================
std::vector<int> Recommender::getPapersByKeywordsOR(
    const std::vector<std::string>& keywords) const {
    
    // TODO: 同学C实现
    std::cout << "Recommender::getPapersByKeywordsOR: 待实现" << std::endl;
    
    std::set<int> resultSet;  // 使用set去重
    
    for (const auto& keyword : keywords) {
        std::vector<int> papers = getPapersByKeyword(keyword);
        for (int id : papers) {
            resultSet.insert(id);
        }
    }
    
    return std::vector<int>(resultSet.begin(), resultSet.end());
}

// ==================== AND查询 ====================
std::vector<int> Recommender::getPapersByKeywordsAND(
    const std::vector<std::string>& keywords) const {
    
    // TODO: 同学C实现
    std::cout << "Recommender::getPapersByKeywordsAND: 待实现" << std::endl;
    
    std::vector<int> result;
    
    for (const auto& paper : papers) {
        std::vector<std::string> paperKeywords = paper.getKeywords();
        
        bool hasAllKeywords = true;
        for (const auto& keyword : keywords) {
            bool found = false;
            for (const auto& kw : paperKeywords) {
                if (kw == keyword) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                hasAllKeywords = false;
                break;
            }
        }
        
        if (hasAllKeywords) {
            result.push_back(paper.getPaperId());
        }
    }
    
    return result;
}

// ==================== 打印关键词统计 ====================
void Recommender::printKeywordStatistics() const {
    // TODO: 同学C实现（可选）
    
    std::cout << "\n==================== 关键词统计 ====================" << std::endl;
    std::cout << "总关键词种类数: " << keywordFrequency.size() << std::endl;
    
    // 统计只出现一次的关键词
    int onceCount = 0;
    for (std::map<std::string, int>::const_iterator it = keywordFrequency.begin();
         it != keywordFrequency.end(); ++it) {
        if (it->second == 1) onceCount++;
    }
    std::cout << "只出现一次的关键词数: " << onceCount << std::endl;
}

// ==================== 显示推荐结果 ====================
void Recommender::displayRecommendations(
    const std::vector<std::pair<int, int>>& recommendations,
    const std::vector<Paper>& papers) {
    
    // TODO: 同学C实现
    
    std::cout << "\n==================== 推荐结果 ====================" << std::endl;
    std::cout << "共推荐 " << recommendations.size() << " 篇论文\n" << std::endl;
    
    for (size_t i = 0; i < recommendations.size(); i++) {
        int paperId = recommendations[i].first;
        int similarity = recommendations[i].second;
        
        // 找到对应的论文
        for (const auto& paper : papers) {
            if (paper.getPaperId() == paperId) {
                std::cout << "[" << (i + 1) << "] 相似度: " << similarity << std::endl;
                paper.printBrief();
                std::cout << std::endl;
                break;
            }
        }
    }
}
