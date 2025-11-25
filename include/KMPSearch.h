#ifndef KMPSEARCH_H
#define KMPSEARCH_H

#include <string>
#include <vector>
#include "Paper.h"

/**
 * @brief KMP字符串匹配类 - 用于按内容模糊查找论文
 *
 * 【同学B实现】
 *
 * 功能：使用KMP算法在论文的标题、摘要等内容中查找关键词
 * 类比：就像Word文档的"查找"功能
 *
 * 算法特点：
 * - 时间复杂度：O(n+m)，其中n是文本长度，m是模式串长度
 * - 空间复杂度：O(m)
 * - 不会回溯主串指针，效率高
 */
class KMPSearch {
private:
    /**
     * @brief 计算KMP算法的next数组（部分匹配表）
     *
     * 【同学B实现】
     *
     * next数组的含义：
     * next[i] 表示 pattern[0...i] 中最长相等前后缀的长度
     *
     * 例如：pattern = "ABABC"
     * - next[0] = 0  (A)
     * - next[1] = 0  (AB)
     * - next[2] = 1  (ABA, 前缀A = 后缀A)
     * - next[3] = 2  (ABAB, 前缀AB = 后缀AB)
     * - next[4] = 0  (ABABC)
     *
     * @param pattern 模式串
     * @return next数组
     */
    static std::vector<int> computeNext(const std::string& pattern);

    /**
     * @brief 使用KMP算法在文本中查找模式串
     *
     * 【同学B实现】
     *
     * @param text 文本串
     * @param pattern 模式串
     * @return 第一次出现的位置，找不到返回-1
     */
    static int kmpSearch(const std::string& text, const std::string& pattern);

public:
    /**
     * @brief 在所有论文中按内容模糊查找
     *
     * 【同学B实现】
     *
     * 查找范围：
     * - 论文标题
     * - 论文摘要
     * - （可选）作者名、关键词
     *
     * @param papers 所有论文
     * @param keyword 查找关键词
     * @return 包含关键词的论文列表
     */
    static std::vector<Paper*> searchByContent(std::vector<Paper>& papers,
                                               const std::string& keyword);

    /**
     * @brief 检查单篇论文是否包含关键词
     *
     * @param paper 论文
     * @param keyword 关键词
     * @return 是否包含
     */
    static bool contains(const Paper& paper, const std::string& keyword);
};

#endif // KMPSEARCH_H
