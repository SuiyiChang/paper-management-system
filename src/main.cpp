#include <iostream>
#include <string>
#include <vector>
#include <limits> // For numeric_limits
#include "Paper.h"
#include "FileManager.h"
#include "HashSearch.h"
#include "BSTSearch.h"
#include "KMPSearch.h"
#include "Sorter.h"
#include "GraphAnalyzer.h"
#include "Recommender.h"

#ifdef _WIN32
#include <windows.h>
#endif

//使用模块化编程的思想，每个功能都应被视为一个独立的模块，
//实现在不同的源文件和头文件中，并通过 include 语句引入

// 全局变量：存储所有论文的vector
std::vector<Paper> papers;

// 默认数据文件路径
const std::string DEFAULT_DATA_FILE = "data/papers.txt";

// 分页显示常量
const int PAGE_SIZE = 20;

// 分页显示论文列表的辅助函数
void displayPapersWithPagination(const std::vector<Paper>& paperList) {
    if (paperList.empty()) {
        return;
    }

    size_t totalCount = paperList.size();
    size_t displayed = 0;

    while (displayed < totalCount) {
        // 计算本次显示的数量
        size_t remaining = totalCount - displayed;
        size_t toDisplay = (remaining > PAGE_SIZE) ? PAGE_SIZE : remaining;

        // 显示论文
        for (size_t i = 0; i < toDisplay; i++) {
            std::cout << "[" << (displayed + i + 1) << "] ";
            paperList[displayed + i].printBrief();
            std::cout << std::endl;
        }

        displayed += toDisplay;

        // 如果还有未显示的论文，询问用户
        if (displayed < totalCount) {
            std::cout << "\n当前已显示 " << displayed << " 篇论文，还有 "
                      << (totalCount - displayed) << " 篇论文未显示。" << std::endl;
            std::cout << "是否继续显示？(y/n): ";

            char response;
            std::cin >> response;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (response != 'y' && response != 'Y') {
                std::cout << "已停止显示。" << std::endl;
                break;
            }
            std::cout << std::endl;
        }
    }
}

// 分页显示论文指针列表的辅助函数
void displayPaperPointersWithPagination(const std::vector<Paper*>& paperList) {
    if (paperList.empty()) {
        return;
    }

    size_t totalCount = paperList.size();
    size_t displayed = 0;

    while (displayed < totalCount) {
        // 计算本次显示的数量
        size_t remaining = totalCount - displayed;
        size_t toDisplay = (remaining > PAGE_SIZE) ? PAGE_SIZE : remaining;

        // 显示论文
        for (size_t i = 0; i < toDisplay; i++) {
            std::cout << "[" << (displayed + i + 1) << "] ";
            paperList[displayed + i]->printBrief();
            std::cout << std::endl;
        }

        displayed += toDisplay;

        // 如果还有未显示的论文，询问用户
        if (displayed < totalCount) {
            std::cout << "\n当前已显示 " << displayed << " 篇论文，还有 "
                      << (totalCount - displayed) << " 篇论文未显示。" << std::endl;
            std::cout << "是否继续显示？(y/n): ";

            char response;
            std::cin >> response;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (response != 'y' && response != 'Y') {
                std::cout << "已停止显示。" << std::endl;
                break;
            }
            std::cout << std::endl;
        }
    }
}

void displayMenu() {
    std::cout << "\n--- 学术文献管理与关联分析系统 ---" << std::endl;
    std::cout << "1. 加载论文数据" << std::endl;
    std::cout << "2. 显示所有论文 (简要信息)" << std::endl;
    std::cout << "3. 添加新论文" << std::endl;
    std::cout << "4. 删除论文" << std::endl;
    std::cout << "5. 保存当前数据到文件" << std::endl;
    std::cout << "6. 按ID查找论文 (Hash表)" << std::endl;
    std::cout << "7. 按标题查找论文 (BST)" << std::endl;
    std::cout << "8. 按内容模糊查找论文 (KMP)" << std::endl;
    std::cout << "9. 论文排序 (年份/引用次数/标题)" << std::endl;
    std::cout << "10. 合并两个有序论文列表" << std::endl;
    std::cout << "11. 查找相关论文 (BFS)" << std::endl;
    std::cout << "12. 获取关键词推荐 (Top-N)" << std::endl;
    std::cout << "0. 退出" << std::endl;
    std::cout << "请输入您的选择: ";
}

int main() {//主函数中可以自由添加局部变量、交互输入信息
    #ifdef _WIN32
    // 设置 Windows 控制台为 UTF-8
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    #endif
    int choice;
    bool dataLoaded = false;

    do {
        displayMenu();
        std::cin >> choice;

        // --- 输入验证和错误处理 ---
        if (std::cin.fail()) { // 如果输入失败（例如输入了非数字字符）
            std::cout << "无效的输入，请输入一个数字选项。" << std::endl;
            std::cin.clear(); // 清除错误标志
            // 忽略并丢弃当前行中所有剩余的无效输入，直到遇到换行符
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = -1; // 将 choice 设置为一个无效值，以便循环继续
            continue;    // 跳过本次循环的剩余部分，重新显示菜单
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: { // 加载论文数据，数据文件名默认为 papers.txt
                std::cout << "开始加载论文数据..." << std::endl;
                papers = FileManager::loadPapers(DEFAULT_DATA_FILE);

                if (!papers.empty()) {
                    dataLoaded = true;
                    std::cout << "论文数据加载成功！" << std::endl;
                } else {
                    dataLoaded = false;
                    std::cout << "论文数据加载失败或文件为空。" << std::endl;
                }
                break;
            }
            case 2: {// 显示所有论文 (简要信息)
                if (dataLoaded) {
                    std::cout << "\n========== 论文列表 ==========" << std::endl;
                    std::cout << "共 " << papers.size() << " 篇论文：" << std::endl;
                    std::cout << "------------------------------" << std::endl;

                    displayPapersWithPagination(papers);

                    std::cout << "==============================" << std::endl;
                } else {
                    std::cout << "请先加载论文数据。" << std::endl;
                }
                break;
            }
            case 3: { // 添加新论文
                if (dataLoaded) {
                    std::cout << "\n=== 添加新论文 ===" << std::endl;

                    int paperId, year, citations;
                    std::string title, authorsStr, keywordsStr, abstractSnippet;

                    // 输入论文ID
                    std::cout << "请输入论文ID: ";
                    std::cin >> paperId;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    // 检查ID是否已存在
                    bool idExists = false;
                    for (const auto& paper : papers) {
                        if (paper.getPaperId() == paperId) {
                            idExists = true;
                            break;
                        }
                    }

                    if (idExists) {
                        std::cout << "错误：论文ID " << paperId << " 已存在！" << std::endl;
                        break;
                    }

                    // 输入标题
                    std::cout << "请输入论文标题: ";
                    std::getline(std::cin, title);

                    // 输入作者（用分号分隔）
                    std::cout << "请输入作者（多个作者用分号;分隔）: ";
                    std::getline(std::cin, authorsStr);
                    std::vector<std::string> authors = FileManager::split(authorsStr, ';');

                    // 输入年份
                    std::cout << "请输入发表年份: ";
                    std::cin >> year;

                    // 输入引用次数
                    std::cout << "请输入引用次数: ";
                    std::cin >> citations;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    // 输入关键词（用分号分隔，最多6个）
                    std::cout << "请输入关键词（多个关键词用分号;分隔，最多6个）: ";
                    std::getline(std::cin, keywordsStr);
                    std::vector<std::string> keywords = FileManager::split(keywordsStr, ';');

                    // 限制关键词数量为6个
                    if (keywords.size() > 6) {
                        keywords.resize(6);
                        std::cout << "注意：只保留前6个关键词。" << std::endl;
                    }

                    // 输入摘要
                    std::cout << "请输入论文摘要: ";
                    std::getline(std::cin, abstractSnippet);

                    // 创建新论文对象并添加到列表
                    Paper newPaper(paperId, title, authors, year, citations, keywords, abstractSnippet);
                    papers.push_back(newPaper);

                    std::cout << "论文添加成功！当前共有 " << papers.size() << " 篇论文。" << std::endl;
                } else {
                    std::cout << "请先加载论文数据。" << std::endl;
                }
                break;
            }
            case 4: { // 删除论文
                if (dataLoaded) {
                    std::cout << "\n=== 删除论文 ===" << std::endl;

                    int deleteId;
                    std::cout << "请输入要删除的论文ID: ";
                    std::cin >> deleteId;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    // 查找并删除论文
                    bool found = false;
                    for (auto it = papers.begin(); it != papers.end(); ++it) {
                        if (it->getPaperId() == deleteId) {
                            std::cout << "找到论文：" << std::endl;
                            it->print();

                            // 确认删除
                            std::string confirm;
                            std::cout << "\n确认删除？(y/n): ";
                            std::getline(std::cin, confirm);

                            if (confirm == "y" || confirm == "Y") {
                                papers.erase(it);
                                std::cout << "论文删除成功！当前共有 " << papers.size() << " 篇论文。" << std::endl;
                            } else {
                                std::cout << "取消删除。" << std::endl;
                            }

                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        std::cout << "错误：未找到ID为 " << deleteId << " 的论文。" << std::endl;
                    }
                } else {
                    std::cout << "请先加载论文数据。" << std::endl;
                }
                break;
            }
            case 5: { // 保存当前数据到文件
                if (dataLoaded) {
                    std::cout << "\n=== 保存数据 ===" << std::endl;

                    bool success = FileManager::savePapers(papers, DEFAULT_DATA_FILE);

                    if (success) {
                        std::cout << "数据保存成功！" << std::endl;
                    } else {
                        std::cout << "数据保存失败。" << std::endl;
                    }
                } else {
                    std::cout << "请先加载论文数据。" << std::endl;
                }
                break;
            }
            case 6: { // 按ID查找论文
                if (dataLoaded) {
                    std::cout << "\n=== 按ID查找论文 (哈希表) ===" << std::endl;

                    int searchId;
                    std::cout << "请输入要查找的论文ID: ";
                    std::cin >> searchId;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    // 构建哈希表并查找
                    HashSearch hashSearch(papers);
                    Paper* foundPaper = hashSearch.findById(searchId);

                    if (foundPaper != nullptr) {
                        std::cout << "\n找到论文：" << std::endl;
                        foundPaper->print();
                    } else {
                        std::cout << "未找到ID为 " << searchId << " 的论文。" << std::endl;
                    }
                } else {
                    std::cout << "请先加载论文数据。" << std::endl;
                }
                break;
            }
            case 7: { // 按标题查找论文 (BST)
                if (dataLoaded) {
                    std::cout << "\n=== 按标题查找论文 (二叉搜索树) ===" << std::endl;

                    std::string searchTitle;
                    std::cout << "请输入要查找的论文标题（完整标题）: ";
                    std::getline(std::cin, searchTitle);

                    // 构建BST并查找
                    BSTSearch bstSearch(papers);
                    Paper* foundPaper = bstSearch.findByTitle(searchTitle);

                    if (foundPaper != nullptr) {
                        std::cout << "\n找到论文：" << std::endl;
                        foundPaper->print();
                    } else {
                        std::cout << "未找到标题为 \"" << searchTitle << "\" 的论文。" << std::endl;
                        std::cout << "提示：请输入完整的标题，标题区分大小写。" << std::endl;
                    }
                } else {
                    std::cout << "请先加载论文数据。" << std::endl;
                }
                break;
            }
            case 8: { // 按内容模糊查找论文 (KMP)
                if (dataLoaded) {
                    std::cout << "\n=== 按内容模糊查找论文 (KMP算法) ===" << std::endl;

                    std::string keyword;
                    std::cout << "请输入查找关键词: ";
                    std::getline(std::cin, keyword);

                    // 使用KMP算法查找
                    std::vector<Paper*> results = KMPSearch::searchByContent(papers, keyword);

                    if (!results.empty()) {
                        std::cout << "\n找到 " << results.size() << " 篇包含 \"" << keyword << "\" 的论文：" << std::endl;
                        std::cout << "------------------------------" << std::endl;
                        displayPaperPointersWithPagination(results);
                        std::cout << "------------------------------" << std::endl;
                    } else {
                        std::cout << "未找到包含 \"" << keyword << "\" 的论文。" << std::endl;
                    }
                } else {
                    std::cout << "请先加载论文数据。" << std::endl;
                }
                break;
            }
            case 9: { // 论文排序
                if (dataLoaded) {
                    std::cout << "\n=== 论文排序 (快速排序) ===" << std::endl;
                    std::cout << "请选择排序方式：" << std::endl;
                    std::cout << "1. 按年份降序排序" << std::endl;
                    std::cout << "2. 按引用次数降序排序" << std::endl;
                    std::cout << "3. 按标题字母顺序排序" << std::endl;
                    std::cout << "请输入选择 (1-3): ";

                    int sortChoice;
                    std::cin >> sortChoice;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (sortChoice < 1 || sortChoice > 3) {
                        std::cout << "无效的选择。" << std::endl;
                        break;
                    }

                    Sorter sorter(papers);
                    std::vector<Paper> sortedPapers;

                    switch (sortChoice) {
                        case 1:
                            std::cout << "\n正在按年份降序排序..." << std::endl;
                            sortedPapers = sorter.sortByYear(true);
                            break;
                        case 2:
                            std::cout << "\n正在按引用次数降序排序..." << std::endl;
                            sortedPapers = sorter.sortByCitations(true);
                            break;
                        case 3:
                            std::cout << "\n正在按标题字母顺序排序..." << std::endl;
                            sortedPapers = sorter.sortByTitle();
                            break;
                    }

                    std::cout << "\n==================== 排序结果 ====================" << std::endl;
                    std::cout << "共 " << sortedPapers.size() << " 篇论文" << std::endl;
                    std::cout << "------------------------------" << std::endl;

                    displayPapersWithPagination(sortedPapers);

                    std::cout << "=====================================================" << std::endl;
                } else {
                    std::cout << "请先加载论文数据。" << std::endl;
                }
                break;
            }
            case 10: { // 合并两个有序论文列表
                if (dataLoaded) {
                    std::cout << "\n=== 合并两个有序论文列表 (双指针法) ===" << std::endl;

                    // 将当前论文列表分成两部分进行演示
                    if (papers.size() < 2) {
                        std::cout << "论文数量太少，无法演示合并功能。" << std::endl;
                        break;
                    }

                    std::cout << "将论文列表分成两半，分别排序后再合并..." << std::endl;

                    // 分成两半
                    size_t mid = papers.size() / 2;
                    std::vector<Paper> list1(papers.begin(), papers.begin() + mid);
                    std::vector<Paper> list2(papers.begin() + mid, papers.end());

                    // 分别排序
                    Sorter sorter1(list1);
                    Sorter sorter2(list2);
                    std::vector<Paper> sortedList1 = sorter1.sortByYear(true);
                    std::vector<Paper> sortedList2 = sorter2.sortByYear(true);

                    std::cout << "列表1: " << sortedList1.size() << " 篇论文" << std::endl;
                    std::cout << "列表2: " << sortedList2.size() << " 篇论文" << std::endl;

                    // 合并
                    std::vector<Paper> merged = Sorter::mergeSortedLists(
                        sortedList1, sortedList2, "year", true);

                    std::cout << "\n==================== 合并后的列表 ====================" << std::endl;
                    std::cout << "共 " << merged.size() << " 篇论文" << std::endl;
                    std::cout << "------------------------------" << std::endl;

                    displayPapersWithPagination(merged);

                    std::cout << "======================================================" << std::endl;
                } else {
                    std::cout << "请先加载论文数据。" << std::endl;
                }
                break;
            }
            case 11: { // 查找相关论文 (BFS)
                if (dataLoaded) {
                    std::cout << "\n=== 查找相关论文 (BFS图遍历) ===" << std::endl;

                    int searchId;
                    std::cout << "请输入起始论文ID: ";
                    std::cin >> searchId;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    // 构建图并执行BFS
                    GraphAnalyzer analyzer(papers);
                    std::vector<int> relatedIds = analyzer.findRelatedPapersByBFS(searchId);

                    if (!relatedIds.empty()) {
                        std::cout << "\n找到 " << relatedIds.size() << " 篇相关论文（基于关键词共享）：" << std::endl;
                        std::cout << "------------------------------" << std::endl;

                        // 构建相关论文列表用于分页显示
                        std::vector<Paper> relatedPapers;
                        for (size_t i = 0; i < relatedIds.size(); i++) {
                            for (size_t j = 0; j < papers.size(); j++) {
                                if (papers[j].getPaperId() == relatedIds[i]) {
                                    relatedPapers.push_back(papers[j]);
                                    break;
                                }
                            }
                        }

                        displayPapersWithPagination(relatedPapers);
                        std::cout << "------------------------------" << std::endl;
                    } else {
                        std::cout << "未找到相关论文。" << std::endl;
                    }
                } else {
                    std::cout << "请先加载论文数据。" << std::endl;
                }
                break;
            }
            case 12: { // 获取关键词推荐 (Top-N)
                if (dataLoaded) {
                    std::cout << "\n=== 获取关键词推荐 (Top-N算法) ===" << std::endl;

                    int topN;
                    std::cout << "请输入要显示的Top-N数量: ";
                    std::cin >> topN;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    if (topN <= 0) {
                        std::cout << "N必须大于0" << std::endl;
                        break;
                    }

                    // 构建推荐器并获取Top-N关键词
                    Recommender recommender(papers);
                    std::vector<std::pair<std::string, int>> topKeywords = recommender.getTopKeywords(topN);

                    if (!topKeywords.empty()) {
                        std::cout << "\n==================== Top-" << topN << " 热门关键词 ====================" << std::endl;
                        for (size_t i = 0; i < topKeywords.size(); i++) {
                            std::cout << "  [" << (i + 1) << "] "
                                      << topKeywords[i].first
                                      << " - 出现次数: " << topKeywords[i].second << std::endl;
                        }
                        std::cout << "=====================================================" << std::endl;
                    } else {
                        std::cout << "未找到关键词数据。" << std::endl;
                    }
                } else {
                    std::cout << "请先加载论文数据。" << std::endl;
                }
                break;
            }
            case 0:
                std::cout << "感谢使用，再见！" << std::endl;
                break;
            default:
                std::cout << "无效的选择，请重新输入。" << std::endl;
                break;
        }
    } while (choice != 0);

    return 0;
}