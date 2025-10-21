// Paper.cpp
// 【同学A实现】
// 功能：论文数据类的实现

#include "Paper.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// ==================== 构造函数 ====================

/**
 * 默认构造函数
 */
Paper::Paper() {
    // TODO: 同学A实现
    // 初始化所有成员变量为默认值
    paperId = 0;
    title = "";
    year = 0;
    citations = 0;
    abstractSnippet = "";
}

/**
 * 带参数的构造函数
 */
Paper::Paper(int id, const std::string& title, const std::vector<std::string>& authors,
             int year, int citations, const std::vector<std::string>& keywords,
             const std::string& abstract) {
    // TODO: 同学A实现
    // 将参数赋值给成员变量
    this->paperId = id;
    this->title = title;
    this->authors = authors;
    this->year = year;
    this->citations = citations;
    this->keywords = keywords;
    this->abstractSnippet = abstract;
}

/**
 * 析构函数
 */
Paper::~Paper() {
    // 使用vector，无需手动释放内存
}

// ==================== Getter方法 ====================

int Paper::getPaperId() const {
    // TODO: 同学A实现
    return paperId;
}

std::string Paper::getTitle() const {
    // TODO: 同学A实现
    return title;
}

std::vector<std::string> Paper::getAuthors() const {
    // TODO: 同学A实现
    return authors;
}

int Paper::getYear() const {
    // TODO: 同学A实现
    return year;
}

int Paper::getCitations() const {
    // TODO: 同学A实现
    return citations;
}

std::vector<std::string> Paper::getKeywords() const {
    // TODO: 同学A实现
    return keywords;
}

std::string Paper::getAbstractSnippet() const {
    // TODO: 同学A实现
    return abstractSnippet;
}

std::vector<int> Paper::getReferences() const {
    // TODO: 同学A实现
    return references;
}

// ==================== Setter方法 ====================

void Paper::setPaperId(int id) {
    // TODO: 同学A实现
    this->paperId = id;
}

void Paper::setTitle(const std::string& title) {
    // TODO: 同学A实现
    this->title = title;
}

void Paper::setAuthors(const std::vector<std::string>& authors) {
    // TODO: 同学A实现
    this->authors = authors;
}

void Paper::setYear(int year) {
    // TODO: 同学A实现
    this->year = year;
}

void Paper::setCitations(int citations) {
    // TODO: 同学A实现
    this->citations = citations;
}

void Paper::setKeywords(const std::vector<std::string>& keywords) {
    // TODO: 同学A实现
    this->keywords = keywords;
}

void Paper::setAbstractSnippet(const std::string& abstract) {
    // TODO: 同学A实现
    this->abstractSnippet = abstract;
}

void Paper::setReferences(const std::vector<int>& refs) {
    // TODO: 同学A实现
    this->references = refs;
}

// ==================== 功能方法 ====================

/**
 * 添加一个作者
 */
void Paper::addAuthor(const std::string& author) {
    // TODO: 同学A实现
    authors.push_back(author);
}

/**
 * 添加一个关键词
 */
void Paper::addKeyword(const std::string& keyword) {
    // TODO: 同学A实现
    if (keywords.size() < 6) {  // 最多6个关键词
        keywords.push_back(keyword);
    }
}

/**
 * 添加一个引用
 */
void Paper::addReference(int refId) {
    // TODO: 同学A实现
    references.push_back(refId);
}

/**
 * 统计与另一篇论文共享的关键词数量
 */
int Paper::countSharedKeywords(const Paper& other) const {
    // TODO: 同学A实现
    int count = 0;
    
    for (const auto& kw1 : keywords) {
        if (kw1.empty()) continue;
        
        for (const auto& kw2 : other.keywords) {
            if (kw1 == kw2) {
                count++;
                break;  // 同一个关键词只计数一次
            }
        }
    }
    
    return count;
}

/**
 * 打印论文详细信息
 */
void Paper::print() const {
    // TODO: 同学A实现
    std::cout << "==================== 论文详情 ====================" << std::endl;
    std::cout << "ID: " << paperId << std::endl;
    std::cout << "标题: " << title << std::endl;
    
    // 打印作者
    std::cout << "作者: ";
    for (size_t i = 0; i < authors.size(); i++) {
        std::cout << authors[i];
        if (i < authors.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    
    std::cout << "年份: " << year << std::endl;
    std::cout << "引用次数: " << citations << std::endl;
    
    // 打印关键词
    std::cout << "关键词: ";
    for (size_t i = 0; i < keywords.size(); i++) {
        if (!keywords[i].empty()) {
            std::cout << keywords[i];
            if (i < keywords.size() - 1 && !keywords[i+1].empty()) {
                std::cout << ", ";
            }
        }
    }
    std::cout << std::endl;
    
    std::cout << "摘要: " << abstractSnippet << std::endl;
    std::cout << "=================================================" << std::endl;
}

/**
 * 打印论文简要信息
 */
void Paper::printBrief() const {
    // TODO: 同学A实现
    std::cout << "[" << paperId << "] " << title 
              << " (" << year << ") - Citations: " << citations;
}

/**
 * 将论文转换为字符串（用于文件保存）
 */
std::string Paper::toString() const {
    // TODO: 同学A实现
    std::ostringstream oss;
    
    // ID
    oss << paperId << "|";
    
    // Title
    oss << title << "|";
    
    // Authors (用分号分隔)
    for (size_t i = 0; i < authors.size(); i++) {
        oss << authors[i];
        if (i < authors.size() - 1) oss << ";";
    }
    oss << "|";
    
    // Keywords (最多6个)
    for (int i = 0; i < 6; i++) {
        if (i < (int)keywords.size()) {
            oss << keywords[i];
        }
        oss << "|";
    }
    
    // Year
    oss << year << "|";
    
    // Citations
    oss << citations << "|";
    
    // Abstract
    oss << abstractSnippet;
    
    return oss.str();
}

// ==================== 运算符重载 ====================

/**
 * 按年份比较（降序）
 */
bool Paper::operator<(const Paper& other) const {
    // TODO: 同学A实现
    // 用于排序，年份大的排前面（降序）
    return year > other.year;
}

/**
 * 相等比较（基于ID）
 */
bool Paper::operator==(const Paper& other) const {
    // TODO: 同学A实现
    return paperId == other.paperId;
}
