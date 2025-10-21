#ifndef PAPER_H
#define PAPER_H

#include <string>
#include <vector>
#include <iostream>

/**
 * @brief 论文类 - 存储单篇学术论文的所有信息
 * 
 * 这是整个系统的核心数据类，所有其他功能模块都基于Paper对象工作
 * 类比：就像图书馆中一本书的信息卡片
 */
class Paper {
private:
    int paperId;                        // 论文ID（唯一标识）
    std::string title;                  // 论文标题
    std::vector<std::string> authors;   // 作者列表
    int year;                           // 发表年份
    int citations;                      // 被引用次数
    std::vector<std::string> keywords;  // 关键词列表（最多6个）
    std::string abstractSnippet;        // 摘要片段
    std::vector<int> references;        // 引用的论文ID列表（用于构建引用图）

public:
    // ==================== 构造函数和析构函数 ====================
    
    /**
     * @brief 默认构造函数
     */
    Paper();
    
    /**
     * @brief 带参数的构造函数
     * @param id 论文ID
     * @param title 论文标题
     * @param authors 作者列表
     * @param year 发表年份
     * @param citations 引用次数
     * @param keywords 关键词列表
     * @param abstract 摘要片段
     */
    Paper(int id, const std::string& title, const std::vector<std::string>& authors,
          int year, int citations, const std::vector<std::string>& keywords,
          const std::string& abstract);
    
    /**
     * @brief 析构函数
     */
    ~Paper();
    
    // ==================== Getter方法 ====================
    
    int getPaperId() const;
    std::string getTitle() const;
    std::vector<std::string> getAuthors() const;
    int getYear() const;
    int getCitations() const;
    std::vector<std::string> getKeywords() const;
    std::string getAbstractSnippet() const;
    std::vector<int> getReferences() const;
    
    // ==================== Setter方法 ====================
    
    void setPaperId(int id);
    void setTitle(const std::string& title);
    void setAuthors(const std::vector<std::string>& authors);
    void setYear(int year);
    void setCitations(int citations);
    void setKeywords(const std::vector<std::string>& keywords);
    void setAbstractSnippet(const std::string& abstract);
    void setReferences(const std::vector<int>& refs);
    
    // ==================== 功能方法 ====================
    
    /**
     * @brief 添加一个作者
     * @param author 作者姓名
     */
    void addAuthor(const std::string& author);
    
    /**
     * @brief 添加一个关键词
     * @param keyword 关键词
     */
    void addKeyword(const std::string& keyword);
    
    /**
     * @brief 添加一个引用的论文ID
     * @param refId 被引用论文的ID
     */
    void addReference(int refId);
    
    /**
     * @brief 检查是否与另一篇论文共享关键词
     * @param other 另一篇论文
     * @return 共享的关键词数量
     */
    int countSharedKeywords(const Paper& other) const;
    
    /**
     * @brief 打印论文的详细信息
     */
    void print() const;
    
    /**
     * @brief 打印论文的简要信息（用于列表显示）
     */
    void printBrief() const;
    
    /**
     * @brief 将论文信息转换为字符串（用于文件保存）
     * @return 格式化的字符串
     */
    std::string toString() const;
    
    // ==================== 运算符重载（用于排序和比较） ====================
    
    /**
     * @brief 按年份比较（降序）
     */
    bool operator<(const Paper& other) const;
    
    /**
     * @brief 相等比较（基于ID）
     */
    bool operator==(const Paper& other) const;
};

#endif // PAPER_H
