#include <iostream>
#include <string>
#include <vector>
#include <limits> // For numeric_limits
#include "Paper.h"
#include "FileManager.h"


//使用模块化编程的思想，每个功能都应被视为一个独立的模块，
//实现在不同的源文件和头文件中，并通过 include 语句引入

// 全局变量：存储所有论文的vector
std::vector<Paper> papers;

// 默认数据文件路径
const std::string DEFAULT_DATA_FILE = "data/papers.txt";

void displayMenu() {
    std::cout << "\n--- 学术文献管理与关联分析系统 ---" << std::endl;
    std::cout << "1. 加载论文数据" << std::endl;
    std::cout << "2. 显示所有论文 (简要信息)" << std::endl;
    std::cout << "3. 添加新论文" << std::endl;
    std::cout << "4. 删除论文" << std::endl;
    std::cout << "5. 保存当前数据到文件" << std::endl;
    std::cout << "6. 按ID查找论文" << std::endl;
    std::cout << "7. 按标题查找论文 (BST)" << std::endl;
    std::cout << "8. 按内容模糊查找论文 (KMP)" << std::endl; 
    std::cout << "9. 按年份降序排序并显示" << std::endl;
    std::cout << "10. 按引用次数降序排序并显示" << std::endl;
    std::cout << "11. 按标题字母顺序排序并显示" << std::endl;
    std::cout << "12. 合并两个有序论文列表" << std::endl;      
    std::cout << "13. 查找相关论文 (BFS)" << std::endl;
    std::cout << "14. 获取关键词推荐 (Top-N)" << std::endl;


    std::cout << "0. 退出" << std::endl;
    std::cout << "请输入您的选择: ";
}

int main() {//主函数中可以自由添加局部变量、交互输入信息
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

                    for (size_t i = 0; i < papers.size(); i++) {
                        papers[i].printBrief();
                        std::cout << std::endl;
                    }

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
                    
                    //ToDo: 在此处调用按ID查找论文的功能函数
                    std::cout << "按ID查找论文功能待实现，查找ID: " << std::endl;

                } else {
                    std::cout << "请先加载论文数据。" << std::endl;
                }
                break;
            }
            case 7: { // 按标题查找论文 (BST)
                if (dataLoaded) {
                    //ToDo: 在此处调用按标题查找论文的功能函数
                    std::cout << "按标题查找论文功能待实现，查找标题: " << std::endl;

                } else {
                    std::cout << "请先加载论文数据。" << std::endl;
                }
                break;
            }
            case 8: { // 按内容模糊查找论文 (KMP)
                if (dataLoaded) {
                    //ToDo: 在此处调用按内容模糊查找论文的功能函数 (KMP)
                    std::cout << "按内容模糊查找论文 (KMP) 功能待实现。" << std::endl;
                } else {
                    std::cout << "请先加载论文数据。" << std::endl;
                }
                break;
            }
            case 9: // 按年份降序排序并显示
                if (dataLoaded) {
                    //ToDo: 在此处调用按年份降序排序并显示的功能函数
                    std::cout << "按年份降序排序并显示功能待实现。" << std::endl;
                } else {
                    std::cout << "请先加载论文数据。" << std::endl;
                }
                break;
            case 10: // 按引用次数降序排序并显示
                if (dataLoaded) {
                   //ToDo: 在此处调用按引用次数排序并显示的功能函数
                   std::cout << "按引用次数降序排序并显示功能待实现。" << std::endl;
                } else {
                    std::cout << "请先加载论文数据。" << std::endl;
                }
                break;
            case 11: // 按标题字母顺序排序并显示
                if (dataLoaded) {
                    //ToDo: 在此处调用按标题字母顺序排序并显示的功能函数
                    std::cout << "按标题字母顺序排序并显示功能待实现。" << std::endl;
                } else {
                    std::cout << "请先加载论文数据。" << std::endl;
                }
                break;
            case 12: { // 合并两个有序论文列表
                if (dataLoaded) {
                    //ToDo: 在此处调用合并两个有序论文列表的功能函数
                    std::cout << "合并两个有序论文列表功能待实现。" << std::endl;
                } else {
                    std::cout << "请先加载论文数据。" << std::endl;
                }
                break;
            }
            case 13: { // 查找相关论文 (BFS)
                if (dataLoaded) {
                    //ToDo: 在此处调用查找相关论文的功能函数
                    std::cout << "查找相关论文 (BFS) 功能待实现。" << std::endl;
                } else {
                    std::cout << "请先加载论文数据。" << std::endl;
                }
                break;
            }
            case 14: { // 获取关键词推荐 (Top-N)
                if (dataLoaded) {
                    //ToDo: 在此处调用获取关键词推荐的功能函数
                    std::cout << "获取关键词推荐 (Top-N) 功能待实现。" << std::endl;
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