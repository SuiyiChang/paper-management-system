# 数据结构与算法分析课程设计报告（草稿）

> 说明：以下内容按照用户提供的模板顺序编排，并结合仓库代码进行填充。姓名、学号等信息使用占位符，可自行替换。实际排版（字体、字号、行距）请在排版软件中设置，本草稿以 Markdown 形式保存便于后续编辑。

## 封面信息
- 课题名称：文献管理与分析系统
- 提交文档学生姓名：张三（可替换）
- 提交文档学生学号：2024123456（可替换）
- 同组成员名单：李四、王五（可替换，如无可写“无”）
- 指导教师姓名：李老师（可替换）
- 提交报告时间：2025 年 6 月 1 日（可替换）

## 目录（示意）
1. 引言  
   1.1 课程设计背景  
   1.2 课程设计目标  
   1.3 报告结构  
2. 需求分析  
   2.1 功能需求  
   2.2 数据源描述  
   2.3 非功能需求  
3. 系统设计  
   3.1 总体架构设计  
   3.2 数据结构设计  
   3.3 算法设计  
4. 系统实现  
   4.1 开发环境与工具  
   4.2 模块划分与接口  
   4.3 关键代码实现说明  
5. 系统测试与结果分析  
   5.1 功能测试与分析  
   5.2 性能测试与分析  
6. 额外任务与拓展  
7. 总结  
参考文献  
附录

## 正文草稿

### 1 引言
#### 1.1 课程设计背景
- 数据结构与算法在信息检索、推荐、知识图谱等场景中至关重要。文献管理需要高效的存取、查找和分析手段。
- 本系统面向学术文献管理与关联分析，支持数据加载、检索、排序、图关联与推荐等功能，旨在解决“如何快速查找、排序并关联分析大量论文”这一核心问题。【F:src/main.cpp†L64-L111】

#### 1.2 课程设计目标
- 构建涵盖顺序表、哈希表、二叉搜索树、图和堆等数据结构的综合实训项目。
- 实现按 ID（哈希）、标题（BST）、内容（KMP）、排序（快速排序）、关联分析（BFS）、推荐（Top-N）等功能。
- 提供可交互的命令行菜单，完成数据加载、增删查改、排序、合并与结果展示。【F:src/main.cpp†L64-L162】

#### 1.3 报告结构
- 第 2 章介绍需求与数据源；第 3 章给出架构、数据结构和算法设计；第 4 章说明具体实现；第 5 章给出测试与分析；第 6 章讨论拓展；第 7 章总结。

### 2 需求分析
#### 2.1 功能需求
- 数据加载/保存：从 `data/papers.txt` 读取或写回论文数据。【F:src/FileManager.cpp†L15-L82】【F:src/main.cpp†L165-L190】
- 论文浏览：分页展示论文简要信息。【F:src/main.cpp†L26-L61】
- 增删改：添加、删除论文并更新内存数据。【F:src/main.cpp†L192-L276】
- 查找：按 ID（哈希表）、标题（BST）、内容关键词（KMP）。【F:src/main.cpp†L201-L258】【F:src/HashSearch.cpp†L9-L79】【F:src/BSTSearch.cpp†L7-L76】【F:src/KMPSearch.cpp†L9-L74】
- 排序与合并：按年份/引用数/标题排序，合并有序列表。【F:src/main.cpp†L260-L353】【F:src/Sorter.cpp†L9-L116】【F:src/Sorter.cpp†L148-L187】
- 图分析：基于引用或关键词共享的 BFS 相关论文查找。【F:src/main.cpp†L355-L388】【F:src/GraphAnalyzer.cpp†L7-L78】
- 推荐：基于关键词的 Top-N 推荐与相似度计算。【F:src/main.cpp†L390-L409】【F:src/Recommender.cpp†L7-L68】

#### 2.2 数据源描述
- 文件路径：`data/papers.txt`，首行表头，字段以 `|` 分隔，作者用分号`;`分隔，最多 6 个关键词字段。【F:data/papers.txt†L1-L5】【F:src/FileManager.cpp†L32-L71】
- 字段：ID, Title, AuthorsString, Keyword1-6, Year, Citations, AbstractSnippet。
- 示例：`1001|Support-Vector Networks|Corinna Cortes;Vladimir Vapnik|Machine Learning|...|1995|22000|...`。【F:data/papers.txt†L1-L5】

#### 2.3 非功能需求
- 性能：哈希查找平均 O(1)，BST 平均 O(log n)，KMP O(n+m)，快速排序期望 O(n log n)。
- 易用性：菜单驱动交互，分页显示长列表；错误输入清理并提示。【F:src/main.cpp†L114-L164】
- 健壮性：文件解析异常捕获并继续；空数据检查与提示。【F:src/FileManager.cpp†L33-L74】【F:src/main.cpp†L165-L207】

### 3 系统设计
#### 3.1 总体架构设计
- 模块划分：文件管理(FileManager)→数据加载；数据结构层(Paper); 查找层(HashSearch/BSTSearch/KMPSearch); 排序合并(Sorter); 图分析(GraphAnalyzer); 推荐(Recommender); 交互层(main)负责菜单与流程控制。【F:src/main.cpp†L1-L112】【F:src/FileManager.cpp†L1-L115】【F:src/HashSearch.cpp†L9-L79】【F:src/BSTSearch.cpp†L7-L76】【F:src/KMPSearch.cpp†L9-L74】【F:src/Sorter.cpp†L9-L72】【F:src/GraphAnalyzer.cpp†L7-L46】【F:src/Recommender.cpp†L7-L35】
- 数据流：加载文件→`std::vector<Paper>`→构建哈希/BST/图→按需查找/排序/推荐→输出或写回文件。

#### 3.2 数据结构设计
- `Paper` 类：包含 ID、标题、作者列表、年份、引用次数、关键词向量、摘要、引用 ID 列表，并提供统计共享关键词等方法。【F:src/Paper.cpp†L1-L142】
- 顺序表：主存储采用 `std::vector<Paper>` 保存所有论文。【F:src/main.cpp†L20-L25】
- 哈希表：向量 + 链表（拉链法），表长 `TABLE_SIZE`，键为 paperId。【F:src/HashSearch.cpp†L9-L79】
- 二叉搜索树：节点存储标题与 Paper*，用于按标题有序查找。【F:src/BSTSearch.cpp†L7-L76】
- 图结构：`std::map<int, std::vector<int>>` 表示引用图与关键词共享图，节点为论文 ID，边基于引用或共享关键词。【F:src/GraphAnalyzer.cpp†L7-L46】
- 堆：Top-N 推荐中预留最小堆节点结构，用于维护最高相似度列表（当前提供暴力排序实现）。【F:src/Recommender.cpp†L82-L141】

#### 3.3 算法设计
- KMP：`computeNext` 构建部分匹配表，`kmpSearch` 在标题、摘要、作者、关键词中查找子串。【F:src/KMPSearch.cpp†L9-L74】【F:src/KMPSearch.cpp†L76-L142】
- 快速排序：按年份、引用数、标题分别实现分区与递归排序；支持降序参数。【F:src/Sorter.cpp†L21-L116】
- 有序表合并：`mergeSortedLists` 将两份按年份排序的列表合并（位于 main 中）。【F:src/main.cpp†L299-L353】
- BFS：在引用图或关键词共享图中按层遍历返回相关论文列表，支持深度限制。【F:src/GraphAnalyzer.cpp†L48-L119】【F:src/GraphAnalyzer.cpp†L121-L181】
- Top-N：统计关键词频率并排序；相似度基于共享关键词计数，保留堆扩展接口。【F:src/Recommender.cpp†L15-L106】【F:src/Recommender.cpp†L108-L181】

### 4 系统实现
#### 4.1 开发环境与工具
- 语言/标准：C++（使用 STL 容器、算法）。
- 主要文件：`src/*.cpp` 与对应头文件；数据文件位于 `data/` 目录。【F:src/main.cpp†L1-L23】【F:data/papers.txt†L1-L5】
- 构建：提供 `Makefile` 与脚本（如 `test_all_functions.sh`）可编译运行（可在报告中补充实际命令）。

#### 4.2 模块划分与接口
- `main.cpp`：菜单驱动，协调各模块；包含分页展示、输入校验、合并演示等辅助函数。【F:src/main.cpp†L26-L162】【F:src/main.cpp†L260-L409】
- `FileManager`：`loadPapers`/`savePapers`/`appendPaper`/`parseLine`/`formatPaper`，负责文件与 `Paper` 对象转换。【F:src/FileManager.cpp†L15-L116】
- `HashSearch`：构造时建表，`findById`、`insert`、`remove`、`printStatistics`、`rebuild`。【F:src/HashSearch.cpp†L9-L130】
- `BSTSearch`：构造时建树，`findByTitle` 及树遍历接口。【F:src/BSTSearch.cpp†L7-L118】
- `KMPSearch`：`kmpSearch`、`computeNext`、`contains`、`searchByContent`。【F:src/KMPSearch.cpp†L9-L142】
- `Sorter`：`sortByYear`、`sortByCitations`、`sortByTitle` 及对应快速排序内部函数。【F:src/Sorter.cpp†L9-L116】【F:src/Sorter.cpp†L148-L187】
- `GraphAnalyzer`：构建引用/关键词图，`findRelatedPapersByBFS`、`findRelatedPapersByKeywords` 等接口。【F:src/GraphAnalyzer.cpp†L7-L119】【F:src/GraphAnalyzer.cpp†L121-L181】
- `Recommender`：`getTopKeywords`、`recommendSimilarPapers`，以及堆调整函数。【F:src/Recommender.cpp†L7-L181】

#### 4.3 关键代码实现说明
- 文件解析：按 `|` 分割字段，作者再按 `;` 切分，构造 `Paper` 对象；保存时按相同顺序写回并保留 6 个关键词位。【F:src/FileManager.cpp†L32-L116】
- 哈希查找：除法哈希 + 链地址，`findById` 在桶链表中线性搜索，平均 O(1)。【F:src/HashSearch.cpp†L9-L79】
- BST 查找：递归插入与查找按标题字典序，提供高度计算与中序遍历以支持统计和排序输出。【F:src/BSTSearch.cpp†L19-L118】
- KMP 模糊查找：先计算 next 表，再在标题/摘要/作者/关键词中逐一匹配，忽略大小写。【F:src/KMPSearch.cpp†L9-L142】
- 快速排序：分别以年份、引用数为枢轴值分区；标题排序使用字符串比较；排序结果返回新向量，保持原数据不变。【F:src/Sorter.cpp†L21-L116】【F:src/Sorter.cpp†L148-L187】
- BFS 关联：优先基于引用图，否则基于关键词共享图（默认深度 2）保证有结果；使用队列记录节点与深度。【F:src/GraphAnalyzer.cpp†L48-L119】【F:src/GraphAnalyzer.cpp†L121-L181】
- 推荐：统计关键词频率，按共享关键词数计算相似度并排序取前 N；预留最小堆实现以优化大规模数据。【F:src/Recommender.cpp†L15-L106】【F:src/Recommender.cpp†L108-L181】

### 5 系统测试与结果分析（待补充示例）
- 功能测试：可针对菜单各项设计用例，如 ID=1001 查找、关键字“neural” KMP 搜索、年份/引用排序前后结果对比、BFS 关联路径展示等。
- 性能测试：对大数据集测哈希查找、BST 查找、KMP 与朴素匹配、快速排序的耗时对比；讨论哈希装填因子、BST 退化、KMP 优势等。

### 6 额外任务与拓展
- 可讨论加权相似度、堆优化 Top-N、DFS 关联分析、可视化界面等未来工作方向。【F:src/Recommender.cpp†L83-L141】【F:src/GraphAnalyzer.cpp†L83-L118】

### 7 总结
- 回顾需求完成度、数据结构/算法的应用体验、改进方向等。

### 参考文献
- 可列出数据结构教材、算法论文、C++ 文档等（此处留空待填写）。

### 附录
- 可粘贴核心代码或伪代码，或提供编译运行命令与截图位置。
