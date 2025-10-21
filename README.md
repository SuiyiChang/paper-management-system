# 学术文献管理与关联分析系统

## 项目简介

这是一个基于C++的学术文献管理系统，实现了论文的存储、查询、排序和关联分析等功能。本项目采用模块化设计，综合运用了多种数据结构和算法。

## 功能列表

### 基础数据管理功能（同学A负责）
1. ✅ 加载论文数据 - 从文件读取论文数据库
2. ✅ 显示所有论文 - 显示论文简要信息
3. ✅ 添加新论文 - 手动添加论文
4. ✅ 删除论文 - 根据ID删除论文
5. ✅ 保存数据到文件 - 持久化存储

### 查找功能（同学B负责）
6. 🔲 按ID查找论文 - 使用**哈希表**实现O(1)查找
7. 🔲 按标题查找论文 - 使用**二叉搜索树**实现有序查找
8. 🔲 按内容模糊查找 - 使用**KMP算法**实现字符串匹配

### 排序功能（同学B负责）
9. 🔲 按年份降序排序 - 快速排序
10. 🔲 按引用次数降序排序 - 快速排序
11. 🔲 按标题字母顺序排序 - 快速排序

### 高级功能（同学C负责）
12. 🔲 合并有序列表 - 双指针法
13. 🔲 查找相关论文 - **BFS**广度优先搜索
14. 🔲 关键词推荐 - **Top-N堆算法**

## 团队分工

### 同学A（你）- 数据层
**文件：** `Paper.h`, `Paper.cpp`, `FileManager.h`, `FileManager.cpp`, `main.cpp`

**职责：**
- 定义Paper类（论文数据结构）
- 实现FileManager类（文件读写）
- 实现主程序和菜单系统
- 实现功能1-5（加载、显示、添加、删除、保存）
- 创建接口头文件给BC同学
- 编写项目文档和编译配置

**预计工作量：** 10-14小时

### 同学B - 查找与排序层
**文件：** `HashSearch.cpp`, `BSTSearch.cpp`, `Sorter.cpp`

**职责：**
- 实现哈希表查找（链地址法处理冲突）
- 实现二叉搜索树查找
- 实现三种排序算法（按年份、引用次数、标题）
- 实现有序列表合并

**预计工作量：** 10-15小时

### 同学C - 高级分析层
**文件：** `GraphAnalyzer.cpp`, `Recommender.cpp`

**职责：**
- 构建论文引用关系图（邻接表表示）
- 实现BFS图遍历算法
- 实现关键词统计和Top-N推荐（堆算法）

**预计工作量：** 10-15小时

## 项目结构

```
paper-management-system/
├── include/                    # 头文件目录
│   ├── Paper.h                # 论文类（A实现）
│   ├── FileManager.h          # 文件管理类（A实现）
│   ├── HashSearch.h           # 哈希查找（B实现）
│   ├── BSTSearch.h            # BST查找（B实现）
│   ├── Sorter.h               # 排序类（B实现）
│   ├── GraphAnalyzer.h        # 图分析（C实现）
│   └── Recommender.h          # 推荐系统（C实现）
│
├── src/                       # 源文件目录
│   ├── Paper.cpp              # A实现
│   ├── FileManager.cpp        # A实现
│   ├── main.cpp               # A实现
│   ├── HashSearch.cpp         # B实现
│   ├── BSTSearch.cpp          # B实现
│   ├── Sorter.cpp             # B实现
│   ├── GraphAnalyzer.cpp      # C实现
│   └── Recommender.cpp        # C实现
│
├── data/                      # 数据文件
│   └── papers.txt             # 论文数据
│
├── Makefile                   # 编译配置
└── README.md                  # 本文件
```

## 数据文件格式

`data/papers.txt` 格式：
```
ID|Title|AuthorsString|Keyword1|Keyword2|Keyword3|Keyword4|Keyword5|Keyword6|Year|Citations|AbstractSnippet
1001|Support-Vector Networks|Corinna Cortes;Vladimir Vapnik|Machine Learning|Support Vector Machines|...|1995|22000|Introduced the SVM...
```

**字段说明：**
- 字段用 `|` 分隔
- 作者之间用 `;` 分隔
- 关键词最多6个，不足时留空
- 第一行是表头，需要跳过

## 编译方法

### 使用Makefile编译
```bash
# 编译整个项目
make

# 清理编译文件
make clean

# 运行程序
make run
```

### 手动编译
```bash
# 编译所有源文件
g++ -std=c++11 -I./include \
    src/Paper.cpp \
    src/FileManager.cpp \
    src/HashSearch.cpp \
    src/BSTSearch.cpp \
    src/Sorter.cpp \
    src/GraphAnalyzer.cpp \
    src/Recommender.cpp \
    src/main.cpp \
    -o paper_system

# 运行程序
./paper_system
```

## 运行说明

程序启动后会显示菜单：

```
--- 学术文献管理与关联分析系统 ---
1. 加载论文数据
2. 显示所有论文 (简要信息)
3. 添加新论文
4. 删除论文
5. 保存当前数据到文件
6. 按ID查找论文
7. 按标题查找论文 (BST)
8. 按内容模糊查找论文 (KMP)
9. 按年份降序排序并显示
10. 按引用次数降序排序并显示
11. 按标题字母顺序排序并显示
12. 合并两个有序论文列表
13. 查找相关论文 (BFS)
14. 获取关键词推荐 (Top-N)
0. 退出
请输入您的选择:
```

**使用流程：**
1. 首先选择 `1` 加载论文数据
2. 然后可以使用其他功能
3. 修改数据后记得选择 `5` 保存

## 核心数据结构与算法

| 功能 | 数据结构 | 算法 | 时间复杂度 |
|------|---------|------|-----------|
| 按ID查找 | 哈希表（链地址法） | 哈希查找 | O(1) 平均 |
| 按标题查找 | 二叉搜索树 | BST查找 | O(log n) 平均 |
| 模糊查找 | - | KMP算法 | O(n+m) |
| 排序 | - | 快速排序 | O(n log n) 平均 |
| 合并有序列表 | - | 双指针 | O(n) |
| 查找相关论文 | 图（邻接表） | BFS | O(V+E) |
| Top-N关键词 | 最小堆 | 堆排序 | O(m log N) |

## 接口说明

### 给同学B的接口

#### HashSearch类
```cpp
HashSearch(std::vector<Paper>& papers);  // 构造函数：构建哈希表
Paper* findById(int paperId);             // 按ID查找
```

#### BSTSearch类
```cpp
BSTSearch(std::vector<Paper>& papers);   // 构造函数：构建BST
Paper* findByTitle(const std::string& title);  // 按标题查找
```

#### Sorter类
```cpp
Sorter(const std::vector<Paper>& papers);
std::vector<Paper> sortByYear(bool descending = true);
std::vector<Paper> sortByCitations(bool descending = true);
std::vector<Paper> sortByTitle();
```

### 给同学C的接口

#### GraphAnalyzer类
```cpp
GraphAnalyzer(std::vector<Paper>& papers);  // 构造函数：构建图
std::vector<int> findRelatedPapersByBFS(int paperId);  // BFS查找
```

#### Recommender类
```cpp
Recommender(const std::vector<Paper>& papers);
std::vector<std::pair<std::string, int>> getTopKeywords(int n = 10);
std::vector<std::pair<int, int>> recommendSimilarPapers(int paperId, int n = 10);
```

## 开发注意事项

### 内存管理
- `Paper`对象由`main.cpp`中的`vector<Paper>`管理
- 其他类只存储`Paper*`指针，不负责释放
- 自己创建的节点（BSTNode、HashNode等）需要在析构函数中释放

### 编码规范
- 使用驼峰命名法
- 类名首字母大写
- 函数名首字母小写
- 常量全大写

### 错误处理
- 文件操作需要检查是否成功
- 查找失败返回`nullptr`
- 数组访问注意边界检查

## 测试建议

### 功能测试
1. 测试空数据库
2. 测试单个论文
3. 测试大量论文（1000+）
4. 测试边界情况

### 性能测试
1. 记录查找时间
2. 记录排序时间
3. 记录BFS遍历时间
4. 比较不同算法的性能

## 进阶功能（可选）

- [ ] 实现AVL树或红黑树（平衡BST）
- [ ] 实现多关键词AND/OR查询
- [ ] 实现论文引用网络可视化
- [ ] 实现TF-IDF相似度计算
- [ ] 实现持久化索引（不用每次重建）

## 常见问题

**Q: 如何添加新的排序标准？**  
A: 在Sorter类中添加新的比较函数和排序方法。

**Q: 如何优化哈希表性能？**  
A: 调整TABLE_SIZE大小，或实现动态扩容。

**Q: 如何处理标题重复的论文？**  
A: 在BST插入时可以选择忽略或更新。

**Q: 如何测试BFS是否正确？**  
A: 创建简单的测试数据，手动验证遍历顺序。

## 联系方式

如有问题，请联系：
- 同学A（项目负责人）：xxx@example.com
- 同学B：xxx@example.com
- 同学C：xxx@example.com

## 版本历史

- v1.0 (2025-01) - 初始版本，基础功能实现
- v1.1 (待定) - 添加高级查询功能
- v2.0 (待定) - 图形界面版本

---

**祝开发顺利！** 🚀
