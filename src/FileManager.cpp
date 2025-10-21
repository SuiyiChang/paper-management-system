// FileManager.cpp
// 【同学A实现】
// 功能：文件管理类的实现，处理论文数据的加载和保存

#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

/**
 * 从文件加载所有论文
 */
std::vector<Paper> FileManager::loadPapers(const std::string& filename) {
    // TODO: 同学A实现
    std::vector<Paper> papers;
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "错误：无法打开文件 " << filename << std::endl;
        return papers;
    }
    
    std::string line;
    
    // 跳过表头行
    if (std::getline(file, line)) {
        std::cout << "跳过表头: " << line.substr(0, 50) << "..." << std::endl;
    }
    
    // 逐行读取论文数据
    int lineNumber = 1;
    while (std::getline(file, line)) {
        lineNumber++;
        
        if (line.empty()) {
            continue;  // 跳过空行
        }
        
        try {
            Paper paper = parseLine(line);
            papers.push_back(paper);
        } catch (const std::exception& e) {
            std::cerr << "警告：第" << lineNumber << "行解析失败: " 
                      << e.what() << std::endl;
        }
    }
    
    file.close();
    
    std::cout << "成功加载 " << papers.size() << " 篇论文" << std::endl;
    return papers;
}

/**
 * 保存所有论文到文件
 */
bool FileManager::savePapers(const std::vector<Paper>& papers, 
                            const std::string& filename) {
    // TODO: 同学A实现
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "错误：无法打开文件 " << filename << " 进行写入" << std::endl;
        return false;
    }
    
    // 写入表头
    file << "ID|Title|AuthorsString|Keyword1|Keyword2|Keyword3|Keyword4|Keyword5|Keyword6|Year|Citations|AbstractSnippet" << std::endl;
    
    // 写入每篇论文
    for (const auto& paper : papers) {
        file << formatPaper(paper) << std::endl;
    }
    
    file.close();
    
    std::cout << "成功保存 " << papers.size() << " 篇论文到 " << filename << std::endl;
    return true;
}

/**
 * 追加一篇论文到文件
 */
bool FileManager::appendPaper(const Paper& paper, const std::string& filename) {
    // TODO: 同学A实现（可选）
    std::ofstream file(filename, std::ios::app);  // 追加模式
    
    if (!file.is_open()) {
        std::cerr << "错误：无法打开文件 " << filename << std::endl;
        return false;
    }
    
    file << formatPaper(paper) << std::endl;
    
    file.close();
    return true;
}

/**
 * 解析一行数据为Paper对象
 */
Paper FileManager::parseLine(const std::string& line) {
    // TODO: 同学A实现
    std::vector<std::string> fields = split(line, '|');
    
    // 检查字段数量（至少12个字段）
    if (fields.size() < 12) {
        throw std::runtime_error("字段数量不足");
    }
    
    // 解析各个字段
    int paperId = std::stoi(fields[0]);
    std::string title = fields[1];
    
    // 解析作者（用分号分隔）
    std::vector<std::string> authors = split(fields[2], ';');
    
    // 解析关键词（fields[3]到fields[8]，最多6个）
    std::vector<std::string> keywords;
    for (int i = 3; i <= 8 && i < (int)fields.size(); i++) {
        if (!fields[i].empty()) {
            keywords.push_back(fields[i]);
        }
    }
    
    // 解析年份、引用次数
    int year = std::stoi(fields[9]);
    int citations = std::stoi(fields[10]);
    
    // 解析摘要
    std::string abstractSnippet = fields[11];
    
    // 创建Paper对象
    Paper paper(paperId, title, authors, year, citations, keywords, abstractSnippet);
    
    return paper;
}

/**
 * 分割字符串
 */
std::vector<std::string> FileManager::split(const std::string& str, char delimiter) {
    // TODO: 同学A实现
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

/**
 * 格式化Paper对象为文件行
 */
std::string FileManager::formatPaper(const Paper& paper) {
    // TODO: 同学A实现
    std::ostringstream oss;
    
    // ID
    oss << paper.getPaperId() << "|";
    
    // Title
    oss << paper.getTitle() << "|";
    
    // Authors (用分号分隔)
    std::vector<std::string> authors = paper.getAuthors();
    for (size_t i = 0; i < authors.size(); i++) {
        oss << authors[i];
        if (i < authors.size() - 1) {
            oss << ";";
        }
    }
    oss << "|";
    
    // Keywords (6个字段)
    std::vector<std::string> keywords = paper.getKeywords();
    for (int i = 0; i < 6; i++) {
        if (i < (int)keywords.size()) {
            oss << keywords[i];
        }
        oss << "|";
    }
    
    // Year
    oss << paper.getYear() << "|";
    
    // Citations
    oss << paper.getCitations() << "|";
    
    // Abstract
    oss << paper.getAbstractSnippet();
    
    return oss.str();
}
