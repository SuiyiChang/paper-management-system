#ifndef SORTER_H
#define SORTER_H

#include <vector>
#include "Paper.h"

/**
 * @brief 排序类 - 提供多种排序标准和算法
 * 
 * 【同学B实现】
 * 
 * 功能：对论文列表进行排序
 * - 按年份排序（降序）
 * - 按引用次数排序（降序）
 * - 按标题排序（字母升序）
 * 
 * 算法选择：
 * - 快速排序（推荐）- 平均O(n log n)
 * - 归并排序 - 稳定排序O(n log n)
 * - 堆排序 - O(n log n)，原地排序
 * 
 * 可以为不同的排序标准实现不同的算法
 */
class Sorter {
private:
    std::vector<Paper> papers;  // 论文列表的副本
    
    // ==================== 快速排序辅助函数 ====================
    
    /**
     * @brief 快速排序 - 按年份
     * 
     * 【同学B实现】
     * 
     * @param arr 论文数组
     * @param low 起始索引
     * @param high 结束索引
     * @param descending 是否降序
     */
    void quickSortByYear(std::vector<Paper>& arr, int low, int high, bool descending);
    
    /**
     * @brief 快速排序分区函数 - 按年份
     * 
     * 【同学B实现】
     * 
     * 选择枢轴元素，将小于枢轴的放左边，大于的放右边
     * 
     * @param arr 论文数组
     * @param low 起始索引
     * @param high 结束索引
     * @param descending 是否降序
     * @return 枢轴最终位置
     */
    int partitionByYear(std::vector<Paper>& arr, int low, int high, bool descending);
    
    /**
     * @brief 快速排序 - 按引用次数
     * 
     * 【同学B实现】
     */
    void quickSortByCitations(std::vector<Paper>& arr, int low, int high, bool descending);
    
    /**
     * @brief 快速排序分区函数 - 按引用次数
     * 
     * 【同学B实现】
     */
    int partitionByCitations(std::vector<Paper>& arr, int low, int high, bool descending);
    
    /**
     * @brief 快速排序 - 按标题
     * 
     * 【同学B实现】
     */
    void quickSortByTitle(std::vector<Paper>& arr, int low, int high);
    
    /**
     * @brief 快速排序分区函数 - 按标题
     * 
     * 【同学B实现】
     * 
     * 使用字符串比较：strcmp()或std::string的<运算符
     */
    int partitionByTitle(std::vector<Paper>& arr, int low, int high);
    
    // ==================== 归并排序辅助函数（可选） ====================
    
    /**
     * @brief 归并排序 - 按年份
     * 
     * 【同学B实现】（可选）
     * 
     * 归并排序是稳定排序，适合需要保持相对顺序的情况
     */
    void mergeSortByYear(std::vector<Paper>& arr, int left, int right, bool descending);
    
    /**
     * @brief 合并两个有序数组
     * 
     * 【同学B实现】（可选）
     */
    void mergeByYear(std::vector<Paper>& arr, int left, int mid, int right, bool descending);

public:
    // ==================== 构造函数 ====================
    
    /**
     * @brief 构造函数
     * 
     * 【同学B实现】
     * 
     * 将传入的papers复制一份，避免修改原数据
     * 
     * @param papers 论文列表的引用
     */
    Sorter(const std::vector<Paper>& papers);
    
    /**
     * @brief 析构函数
     */
    ~Sorter();
    
    // ==================== 核心排序功能 ====================
    
    /**
     * @brief 按年份排序
     * 
     * 【同学B实现】
     * 
     * 工作流程：
     * 1. 复制papers到临时数组
     * 2. 调用quickSortByYear或其他排序算法
     * 3. 返回排序后的数组
     * 
     * @param descending 是否降序（默认true，最新的在前）
     * @return 排序后的论文列表
     * 
     * 功能编号：8. 按年份降序排序并显示
     */
    std::vector<Paper> sortByYear(bool descending = true);
    
    /**
     * @brief 按引用次数排序
     * 
     * 【同学B实现】
     * 
     * @param descending 是否降序（默认true，引用最多的在前）
     * @return 排序后的论文列表
     * 
     * 功能编号：9. 按引用次数降序排序并显示
     */
    std::vector<Paper> sortByCitations(bool descending = true);
    
    /**
     * @brief 按标题字母顺序排序
     * 
     * 【同学B实现】
     * 
     * @return 排序后的论文列表（字母升序）
     * 
     * 功能编号：10. 按标题字母顺序排序并显示
     */
    std::vector<Paper> sortByTitle();
    
    // ==================== 辅助功能 ====================
    
    /**
     * @brief 显示排序后的论文列表
     * 
     * 【同学B实现】
     * 
     * 用于在main.cpp中统一显示格式
     * 
     * @param sortedPapers 排序后的论文列表
     */
    static void displaySorted(const std::vector<Paper>& sortedPapers);
    
    /**
     * @brief 合并两个已排序的论文列表
     * 
     * 【同学B实现】
     * 
     * 使用双指针法合并两个有序列表
     * 
     * 应用场景：
     * - 合并两个按年份排序的文献库
     * - 归并排序的核心操作
     * 
     * @param list1 第一个有序列表
     * @param list2 第二个有序列表
     * @param sortKey 排序依据（"year", "citations", "title"）
     * @param descending 是否降序
     * @return 合并后的有序列表
     * 
     * 功能编号：11. 合并两个有序论文列表
     */
    static std::vector<Paper> mergeSortedLists(
        const std::vector<Paper>& list1,
        const std::vector<Paper>& list2,
        const std::string& sortKey,
        bool descending = true
    );
};

// ==================== 实现建议（给同学B的提示） ====================

/*
 * 实现建议：
 * 
 * 1. 快速排序实现：
 *    - 枢轴选择：可以选择第一个、最后一个或随机元素
 *    - 三数取中法可以优化性能
 *    - 注意降序和升序的比较逻辑
 * 
 * 2. 比较函数：
 *    - 年份：直接用整数比较
 *    - 引用次数：直接用整数比较
 *    - 标题：使用std::string的<运算符或strcmp()
 * 
 * 3. 性能测试：
 *    - 最好情况：已经有序
 *    - 最坏情况：逆序
 *    - 平均情况：随机顺序
 *    - 记录比较次数和交换次数
 * 
 * 4. 稳定性：
 *    - 快速排序不稳定
 *    - 归并排序稳定
 *    - 如果需要稳定排序，选择归并排序
 * 
 * 5. 原地排序 vs 额外空间：
 *    - 快速排序：原地排序，O(log n)栈空间
 *    - 归并排序：需要O(n)额外空间
 * 
 * 6. 双指针合并算法：
 *    vector<Paper> result;
 *    int i = 0, j = 0;
 *    while (i < list1.size() && j < list2.size()) {
 *        if (compare(list1[i], list2[j])) {
 *            result.push_back(list1[i++]);
 *        } else {
 *            result.push_back(list2[j++]);
 *        }
 *    }
 *    // 添加剩余元素
 */

#endif // SORTER_H
