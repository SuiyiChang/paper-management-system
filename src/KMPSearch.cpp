// KMPSearch.cpp
// 【同学B实现】
// 功能：使用KMP算法实现内容模糊查找

#include "KMPSearch.h"
#include <iostream>
#include <algorithm>

// ==================== 计算next数组 ====================
std::vector<int> KMPSearch::computeNext(const std::string& pattern) {
    int m = pattern.length();
    std::vector<int> next(m, 0);

    if (m == 0) return next;

    // next[0] = 0（第一个字符的最长前后缀长度为0）
    next[0] = 0;

    // j表示当前最长相等前后缀的长度
    int j = 0;

    // 从第二个字符开始计算
    for (int i = 1; i < m; i++) {
        // 如果不匹配，回退j
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1];
        }

        // 如果匹配，j++
        if (pattern[i] == pattern[j]) {
            j++;
        }

        next[i] = j;
    }

    return next;
}

// ==================== KMP查找算法 ====================
int KMPSearch::kmpSearch(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();

    if (m == 0) return 0;  // 空模式串
    if (n < m) return -1;  // 文本比模式串短

    // 计算next数组
    std::vector<int> next = computeNext(pattern);

    // j表示当前匹配到模式串的位置
    int j = 0;

    // 遍历文本串
    for (int i = 0; i < n; i++) {
        // 如果不匹配，根据next数组回退j
        while (j > 0 && text[i] != pattern[j]) {
            j = next[j - 1];
        }

        // 如果匹配，j++
        if (text[i] == pattern[j]) {
            j++;
        }

        // 如果完全匹配，返回匹配位置
        if (j == m) {
            return i - m + 1;  // 返回匹配的起始位置
        }
    }

    return -1;  // 未找到
}

// ==================== 检查单篇论文是否包含关键词 ====================
bool KMPSearch::contains(const Paper& paper, const std::string& keyword) {
    // 转换为小写进行不区分大小写的查找
    std::string lowerKeyword = keyword;
    std::transform(lowerKeyword.begin(), lowerKeyword.end(),
                   lowerKeyword.begin(), ::tolower);

    // 1. 在标题中查找
    std::string title = paper.getTitle();
    std::transform(title.begin(), title.end(), title.begin(), ::tolower);
    if (kmpSearch(title, lowerKeyword) != -1) {
        return true;
    }

    // 2. 在摘要中查找
    std::string abstract = paper.getAbstractSnippet();
    std::transform(abstract.begin(), abstract.end(),
                   abstract.begin(), ::tolower);
    if (kmpSearch(abstract, lowerKeyword) != -1) {
        return true;
    }

    // 3. 在作者中查找
    std::vector<std::string> authors = paper.getAuthors();
    for (size_t i = 0; i < authors.size(); i++) {
        std::string author = authors[i];
        std::transform(author.begin(), author.end(), author.begin(), ::tolower);
        if (kmpSearch(author, lowerKeyword) != -1) {
            return true;
        }
    }

    // 4. 在关键词中查找
    std::vector<std::string> keywords = paper.getKeywords();
    for (size_t i = 0; i < keywords.size(); i++) {
        std::string kw = keywords[i];
        std::transform(kw.begin(), kw.end(), kw.begin(), ::tolower);
        if (kmpSearch(kw, lowerKeyword) != -1) {
            return true;
        }
    }

    return false;
}

// ==================== 在所有论文中查找 ====================
std::vector<Paper*> KMPSearch::searchByContent(std::vector<Paper>& papers,
                                               const std::string& keyword) {
    std::vector<Paper*> result;

    if (keyword.empty()) {
        std::cout << "警告：查找关键词为空" << std::endl;
        return result;
    }

    // 遍历所有论文，使用KMP算法查找
    for (size_t i = 0; i < papers.size(); i++) {
        if (contains(papers[i], keyword)) {
            result.push_back(&papers[i]);
        }
    }

    return result;
}
