#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "Paper.h"

/**
 * @brief 文件管理类 - 负责论文数据的持久化
 * 
 * 职责：连接"硬盘"和"内存"，处理数据的加载和保存
 * 类比：就像游戏的"存档/读档"功能
 * 
 * 数据文件格式（papers.txt）：
 * 第一行：表头（ID|Title|AuthorsString|Keyword1|...|Keyword6|Year|Citations|AbstractSnippet）
 * 后续行：每行一篇论文，字段用 | 分隔
 *   - AuthorsString: 作者之间用 ; 分隔
 *   - Keywords: 最多6个，不足时留空
 */
class FileManager {
public:
    /**
     * @brief 从文件加载所有论文数据
     * 
     * @param filename 数据文件路径（默认为 "data/papers.txt"）
     * @return 论文对象的向量
     * @throws runtime_error 如果文件打开失败或格式错误
     * 
     * 工作流程：
     * 1. 打开文件
     * 2. 跳过表头行
     * 3. 逐行解析论文数据
     * 4. 创建Paper对象并添加到vector
     * 5. 返回所有论文
     */
    static std::vector<Paper> loadPapers(const std::string& filename = "data/papers.txt");
    
    /**
     * @brief 将论文数据保存到文件
     * 
     * @param papers 要保存的论文列表
     * @param filename 目标文件路径（默认为 "data/papers.txt"）
     * @return 是否保存成功
     * 
     * 工作流程：
     * 1. 创建/打开文件
     * 2. 写入表头行
     * 3. 遍历papers，每篇论文写成一行
     * 4. 关闭文件
     */
    static bool savePapers(const std::vector<Paper>& papers, 
                          const std::string& filename = "data/papers.txt");
    
    /**
     * @brief 追加一篇新论文到文件末尾
     *
     * @param paper 要追加的论文
     * @param filename 目标文件路径
     * @return 是否追加成功
     */
    static bool appendPaper(const Paper& paper,
                           const std::string& filename = "data/papers.txt");

    /**
     * @brief 将一个字符串按分隔符分割
     *
     * @param str 要分割的字符串
     * @param delimiter 分隔符
     * @return 分割后的字符串向量
     */
    static std::vector<std::string> split(const std::string& str, char delimiter);

private:
    /**
     * @brief 解析一行论文数据
     *
     * @param line 文件中的一行数据
     * @return Paper对象
     *
     * 解析格式：
     * ID|Title|Author1;Author2;Author3|Keyword1|...|Keyword6|Year|Citations|Abstract
     */
    static Paper parseLine(const std::string& line);
    
    /**
     * @brief 格式化论文数据为文件行
     * 
     * @param paper 论文对象
     * @return 格式化的字符串
     */
    static std::string formatPaper(const Paper& paper);
};

#endif // FILEMANAGER_H
