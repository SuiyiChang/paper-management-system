// Sorter.cpp
// 【同学B实现】
// 功能：提供多种排序功能（按年份、引用次数、标题）

#include "Sorter.h"
#include <iostream>
#include <algorithm>

// ==================== 构造函数 ====================
Sorter::Sorter(const std::vector<Paper>& papers) {
    // 复制papers到成员变量
    this->papers = papers;
}

// ==================== 析构函数 ====================
Sorter::~Sorter() {
    // 无需特殊处理
}

// ==================== 快速排序辅助函数 - 按年份 ====================
void Sorter::quickSortByYear(std::vector<Paper>& arr, int low, int high, bool descending) {
    // TODO: 同学B实现
    // 快速排序递归实现
    
    if (low >= high) return;
    
    int pivotIndex = partitionByYear(arr, low, high, descending);
    quickSortByYear(arr, low, pivotIndex - 1, descending);
    quickSortByYear(arr, pivotIndex + 1, high, descending);
}

// ==================== 分区函数 - 按年份 ====================
int Sorter::partitionByYear(std::vector<Paper>& arr, int low, int high, bool descending) {
    // TODO: 同学B实现
    // 选择枢轴，分区，返回枢轴位置
    
    int pivot = arr[high].getYear();
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        bool condition = descending ? 
            (arr[j].getYear() > pivot) : (arr[j].getYear() < pivot);
        
        if (condition) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// ==================== 快速排序辅助函数 - 按引用次数 ====================
void Sorter::quickSortByCitations(std::vector<Paper>& arr, int low, int high, bool descending) {
    // TODO: 同学B实现
    
    if (low >= high) return;
    
    int pivotIndex = partitionByCitations(arr, low, high, descending);
    quickSortByCitations(arr, low, pivotIndex - 1, descending);
    quickSortByCitations(arr, pivotIndex + 1, high, descending);
}

// ==================== 分区函数 - 按引用次数 ====================
int Sorter::partitionByCitations(std::vector<Paper>& arr, int low, int high, bool descending) {
    // TODO: 同学B实现
    
    int pivot = arr[high].getCitations();
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        bool condition = descending ? 
            (arr[j].getCitations() > pivot) : (arr[j].getCitations() < pivot);
        
        if (condition) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// ==================== 快速排序辅助函数 - 按标题 ====================
void Sorter::quickSortByTitle(std::vector<Paper>& arr, int low, int high) {
    // TODO: 同学B实现
    
    if (low >= high) return;
    
    int pivotIndex = partitionByTitle(arr, low, high);
    quickSortByTitle(arr, low, pivotIndex - 1);
    quickSortByTitle(arr, pivotIndex + 1, high);
}

// ==================== 分区函数 - 按标题 ====================
int Sorter::partitionByTitle(std::vector<Paper>& arr, int low, int high) {
    // TODO: 同学B实现
    // 使用string的<运算符比较
    
    std::string pivot = arr[high].getTitle();
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j].getTitle() < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// ==================== 归并排序（可选） ====================
void Sorter::mergeSortByYear(std::vector<Paper>& arr, int left, int right, bool descending) {
    // TODO: 同学B实现（可选）
    (void)arr; (void)left; (void)right; (void)descending;  // 避免未使用参数警告
    std::cout << "Sorter::mergeSortByYear: 待实现" << std::endl;
}

void Sorter::mergeByYear(std::vector<Paper>& arr, int left, int mid, int right, bool descending) {
    // TODO: 同学B实现（可选）
    (void)arr; (void)left; (void)mid; (void)right; (void)descending;  // 避免未使用参数警告
    std::cout << "Sorter::mergeByYear: 待实现" << std::endl;
}

// ==================== 核心排序功能 ====================

/**
 * 按年份排序
 */
std::vector<Paper> Sorter::sortByYear(bool descending) {
    // TODO: 同学B实现
    std::vector<Paper> sortedPapers = papers;
    
    if (sortedPapers.empty()) {
        return sortedPapers;
    }
    
    quickSortByYear(sortedPapers, 0, sortedPapers.size() - 1, descending);
    
    return sortedPapers;
}

/**
 * 按引用次数排序
 */
std::vector<Paper> Sorter::sortByCitations(bool descending) {
    // TODO: 同学B实现
    std::vector<Paper> sortedPapers = papers;
    
    if (sortedPapers.empty()) {
        return sortedPapers;
    }
    
    quickSortByCitations(sortedPapers, 0, sortedPapers.size() - 1, descending);
    
    return sortedPapers;
}

/**
 * 按标题排序
 */
std::vector<Paper> Sorter::sortByTitle() {
    // TODO: 同学B实现
    std::vector<Paper> sortedPapers = papers;
    
    if (sortedPapers.empty()) {
        return sortedPapers;
    }
    
    quickSortByTitle(sortedPapers, 0, sortedPapers.size() - 1);
    
    return sortedPapers;
}

// ==================== 显示排序结果 ====================
void Sorter::displaySorted(const std::vector<Paper>& sortedPapers) {
    // TODO: 同学B实现
    std::cout << "\n==================== 排序结果 ====================" << std::endl;
    std::cout << "共 " << sortedPapers.size() << " 篇论文\n" << std::endl;
    
    for (size_t i = 0; i < sortedPapers.size(); i++) {
        std::cout << "[" << (i + 1) << "] ";
        sortedPapers[i].printBrief();
        std::cout << std::endl;
    }
}

// ==================== 合并有序列表 ====================
std::vector<Paper> Sorter::mergeSortedLists(
    const std::vector<Paper>& list1,
    const std::vector<Paper>& list2,
    const std::string& sortKey,
    bool descending) {
    
    // TODO: 同学B实现
    // 使用双指针法合并两个有序列表
    
    std::vector<Paper> result;
    size_t i = 0, j = 0;
    
    while (i < list1.size() && j < list2.size()) {
        bool compare = false;
        
        // 根据sortKey选择比较字段
        if (sortKey == "year") {
            compare = descending ? 
                (list1[i].getYear() > list2[j].getYear()) :
                (list1[i].getYear() < list2[j].getYear());
        } else if (sortKey == "citations") {
            compare = descending ?
                (list1[i].getCitations() > list2[j].getCitations()) :
                (list1[i].getCitations() < list2[j].getCitations());
        } else if (sortKey == "title") {
            compare = list1[i].getTitle() < list2[j].getTitle();
        }
        
        if (compare) {
            result.push_back(list1[i]);
            i++;
        } else {
            result.push_back(list2[j]);
            j++;
        }
    }
    
    // 添加剩余元素
    while (i < list1.size()) {
        result.push_back(list1[i]);
        i++;
    }
    
    while (j < list2.size()) {
        result.push_back(list2[j]);
        j++;
    }
    
    return result;
}
