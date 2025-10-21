# 📚 GitHub团队协作指南 - 学术文献管理系统

> 专为本项目三人团队编写的Git/GitHub协作指南

**项目仓库**: https://github.com/SuiyiChang/paper-management-system.git

---

## 👥 团队成员与分工

|成员|负责模块|文件|功能|
|---|---|---|---|
|**同学A（Suiyi）**|数据层 + 主程序|`Paper.h/cpp`<br>`FileManager.h/cpp`<br>`main.cpp`|1-5号功能|
|**同学B**|查找与排序|`HashSearch.h/cpp`<br>`BSTSearch.h/cpp`<br>`Sorter.h/cpp`|6-10号功能|
|**同学C**|高级分析|`GraphAnalyzer.h/cpp`<br>`Recommender.h/cpp`|11-12号功能|

### 功能对应表

```
同学A负责（基础功能）：
├── 1. 加载论文数据
├── 2. 显示所有论文（简要信息）
├── 3. 添加新论文
├── 4. 删除论文
└── 5. 保存当前数据到文件

同学B负责（查找+排序）：
├── 6. 按ID查找论文（哈希表）
├── 7. 按标题查找论文（BST）
├── 8. 按内容模糊查找论文（KMP）
├── 9. 按年份降序排序并显示
├── 10. 按引用次数降序排序并显示
└── 11. 按标题字母顺序排序并显示

同学C负责（图+推荐）：
├── 12. 合并两个有序论文列表
├── 13. 查找相关论文（BFS）
└── 14. 获取关键词推荐（Top-N）
```

---

## 🚀 快速开始（5分钟）

### 第一步：获取项目代码

#### 同学A（Suiyi - 项目创建者）✅

你已经完成了！项目已在GitHub上：https://github.com/SuiyiChang/paper-management-system.git

#### 同学B和C（协作者）

**方法1：使用命令行（推荐）**

```bash
# 1. 克隆项目到本地
git clone https://github.com/SuiyiChang/paper-management-system.git

# 2. 进入项目目录
cd paper-management-system

# 3. 查看项目结构
ls -la

# 4. 查看所有分支（包括远程）
git branch -a
```

**方法2：使用GitHub Desktop（Windows用户友好）**

1. 下载并安装 [GitHub Desktop](https://desktop.github.com/)
2. 点击 File → Clone Repository
3. 输入仓库URL：`https://github.com/SuiyiChang/paper-management-system.git`
4. 选择本地保存位置
5. 点击 Clone

**Windows用户**如果没有Git：

1. 下载安装 [Git for Windows](https://git-scm.com/download/win)
2. 安装时选择默认设置即可

---

## 📁 项目结构

```
paper-management-system/
├── include/              # 头文件目录
│   ├── Paper.h          # 论文类（A实现）
│   ├── FileManager.h    # 文件管理（A实现）
│   ├── HashSearch.h     # 哈希查找（B实现）
│   ├── BSTSearch.h      # BST查找（B实现）
│   ├── Sorter.h         # 排序（B实现）
│   ├── GraphAnalyzer.h  # 图分析（C实现）
│   └── Recommender.h    # 推荐系统（C实现）
│
├── src/                 # 源文件目录
│   ├── Paper.cpp        # A实现
│   ├── FileManager.cpp  # A实现
│   ├── main.cpp         # A实现
│   ├── HashSearch.cpp   # B实现
│   ├── BSTSearch.cpp    # B实现
│   ├── Sorter.cpp       # B实现
│   ├── GraphAnalyzer.cpp # C实现
│   └── Recommender.cpp  # C实现
│
├── data/                # 数据文件
│   └── papers.txt       # 测试数据（A准备）
│
├── docs/                # 文档目录
│   ├── project_explanation.docx
│   ├── whole_project_design.docx
│   └── GitHub_Collaboration_Guide.md
│
├── Makefile             # 编译配置（A创建）
└── README.md            # 项目说明（A创建）
```

---

## 🌿 分支管理策略

### 我们采用的分支模型

```
main (主分支 - 稳定版本)
 ├── dev-A (同学A的开发分支)
 ├── dev-B (同学B的开发分支)
 └── dev-C (同学C的开发分支)
```

### 分支说明

- **main**: 稳定版本，只有测试通过的代码才能合并进来
- **dev-A**: Suiyi的开发分支（Paper、FileManager、main.cpp）
- **dev-B**: 同学B的开发分支（HashSearch、BSTSearch、Sorter）
- **dev-C**: 同学C的开发分支（GraphAnalyzer、Recommender）

---

## 📝 协作工作流程

### 第一次开始工作

#### 1. 克隆项目（只做一次）

```bash
git clone https://github.com/SuiyiChang/paper-management-system.git
cd paper-management-system
```

#### 2. 创建自己的开发分支

```bash
# 同学A (Suiyi)
git checkout -b dev-A

# 同学B
git checkout -b dev-B

# 同学C
git checkout -b dev-C
```

#### 3. 推送自己的分支到GitHub

```bash
# 同学A
git push -u origin dev-A

# 同学B
git push -u origin dev-B

# 同学C
git push -u origin dev-C
```

---

### 日常工作流程（重要！⭐）

#### 每天开始工作前：

```bash
# 1. 确保在自己的分支
git checkout dev-A  # 或 dev-B / dev-C

# 2. 拉取最新的 main 分支代码
git fetch origin
git merge origin/main

# 3. 如果有冲突，先解决冲突（见后文）
```

#### 编写代码：

根据你的分工编写对应的文件：

```bash
# 同学A: 
# - src/Paper.cpp
# - src/FileManager.cpp  
# - src/main.cpp

# 同学B:
# - src/HashSearch.cpp
# - src/BSTSearch.cpp
# - src/Sorter.cpp

# 同学C:
# - src/GraphAnalyzer.cpp
# - src/Recommender.cpp
```

#### 提交代码：

```bash
# 1. 查看修改了哪些文件
git status

# 2. 添加修改的文件
git add src/Paper.cpp src/Paper.h    # 添加单个文件
# 或
git add src/                          # 添加整个src目录
# 或
git add .                             # 添加所有修改

# 3. 提交（写清楚做了什么）
git commit -m "feat: 实现Paper类的构造函数和Getter方法"

# 4. 推送到GitHub
git push origin dev-A  # 或 dev-B / dev-C
```

---

### 合并代码到主分支（重要！⭐）

当你完成一个功能模块，想合并到主分支时：

#### 方法1：使用Pull Request（强烈推荐！）

**为什么要用PR？**

- ✅ 让队友review你的代码
- ✅ 发现潜在问题
- ✅ 记录每次合并的历史
- ✅ 避免直接修改main分支

**步骤：**

1. **推送你的分支到GitHub**
    
    ```bash
    git push origin dev-A  # 或你的分支名
    ```
    
2. **在GitHub网站上创建Pull Request**
    
    - 打开 https://github.com/SuiyiChang/paper-management-system
    - 点击 **"Pull requests"** 标签
    - 点击 **"New pull request"**
    - 选择：`base: main` ← `compare: dev-A`（你的分支）
    - 点击 **"Create pull request"**
    - 填写标题和描述：
        
        ```
        标题: [同学A] 实现Paper类和FileManager类描述:- ✅ 完成Paper类的所有方法- ✅ 完成FileManager的加载和保存功能- ✅ 测试通过，可以正常编译运行- 📝 请 @同学B @同学C review代码修改的文件：- src/Paper.cpp- include/Paper.h- src/FileManager.cpp- include/FileManager.h
        ```
        
3. **通知队友Review**
    
    - 在微信群里发消息："我提交了PR，请帮忙review一下"
    - 附上PR链接
4. **队友Review后合并**
    
    - 队友在PR页面查看代码
    - 点击 "Files changed" 查看修改
    - 如果有问题，在代码行上留comment
    - 如果没问题，点击 **"Approve"**
    - 项目负责人点击 **"Merge pull request"**
    - 点击 **"Confirm merge"**
5. **合并后更新本地代码**
    
    ```bash
    # 切换到main分支
    git checkout main
    
    # 拉取最新代码
    git pull origin main
    
    # 切回自己的分支
    git checkout dev-A
    
    # 合并main的最新代码
    git merge main
    ```
    

#### 方法2：直接合并（不推荐，但更快）

```bash
# 1. 切换到main分支
git checkout main

# 2. 拉取最新代码
git pull origin main

# 3. 合并你的分支
git merge dev-A  # 或你的分支名

# 4. 推送到GitHub
git push origin main
```

**⚠️ 注意**：方法2容易出问题，强烈建议使用方法1（PR）

---

## 🎯 具体协作场景

### 场景1：同学A先完成Paper类（项目启动）

```bash
# 同学A的操作
cd paper-management-system
git checkout dev-A

# 编写代码
# 在 include/Paper.h 中定义类
# 在 src/Paper.cpp 中实现方法

# 测试编译（如果有Makefile）
make clean
make

# 或者直接编译测试
g++ -c src/Paper.cpp -I include -o Paper.o

# 提交
git add include/Paper.h src/Paper.cpp
git commit -m "feat: 实现Paper类的完整功能

- 实现构造函数和析构函数
- 实现所有getter和setter方法
- 实现print()显示论文信息
- 添加比较运算符重载（用于排序）"

git push origin dev-A

# 在GitHub上创建PR
```

**通知队友（在微信群）**：

> 📢 **@全体成员**
> 
> 我已经完成Paper类和FileManager类，提交了PR #1。
> 
> **你们可以做的事情：**
> 
> 1. Review我的代码（https://github.com/SuiyiChang/paper-management-system/pull/1）
> 2. 如果approve了，我就合并到main
> 3. 合并后，你们pull最新的main分支
> 4. B和C可以开始基于Paper类实现你们的模块了！
> 
> **Paper类提供的接口：**
> 
> - `getPaperId()`, `getTitle()`, `getAuthors()` 等
> - `print()` 显示论文信息
> - 重载了比较运算符，可以直接比较

### 场景2：同学B开始实现HashSearch（依赖A的代码）

```bash
# 同学B的操作
cd paper-management-system
git checkout dev-B

# 更新主分支的代码（获取A提交的Paper类）
git fetch origin
git merge origin/main

# 现在可以看到Paper类了！
ls include/Paper.h     # 应该存在
ls src/Paper.cpp       # 应该存在

# 创建你的文件
touch include/HashSearch.h
touch src/HashSearch.cpp

# 编写代码
vim include/HashSearch.h
vim src/HashSearch.cpp

# 测试编译（确保能编译通过）
g++ -c src/HashSearch.cpp src/Paper.cpp -I include

# 提交
git add include/HashSearch.h src/HashSearch.cpp
git commit -m "feat: 实现HashSearch类的哈希查找功能

- 实现哈希表数据结构（链地址法）
- 实现构造函数，自动建立索引
- 实现findById()方法
- 平均查找时间O(1)"

git push origin dev-B

# 创建PR
```

### 场景3：两个人同时修改了main.cpp（冲突处理）

**问题**：同学A和同学B都修改了main.cpp，会产生冲突！

**解决方案：**

#### 预防冲突 - 提前沟通（最重要！）

在微信群里说：

> 📢 我要修改 `main.cpp` 的功能6-8部分，大概需要1小时。
> 
> 请其他人暂时不要修改这个文件！完成后我会通知。

#### 解决冲突（如果已经发生）

```bash
# 1. 尝试合并时出现冲突
git merge origin/main
# 输出: CONFLICT (content): Merge conflict in src/main.cpp

# 2. 查看冲突文件
git status
# 会显示：both modified: src/main.cpp

# 3. 打开main.cpp，找到冲突标记
vim src/main.cpp
```

文件中会看到：

```cpp
<<<<<<< HEAD
// 你的代码（当前分支）
case 6: { // 按ID查找论文
    int id;
    cout << "请输入论文ID: ";
    cin >> id;
    hashSearch.findById(id);
}
=======
// 队友的代码（main分支）
case 6: { // 按ID查找论文
    string id;
    cout << "输入ID: ";
    cin >> id;
    hashSearch.search(id);
}
>>>>>>> origin/main
```

**手动解决冲突的步骤：**

1. **阅读两段代码，理解差异**
2. **决定保留哪个版本，或合并两者的优点**
3. **删除冲突标记（`<<<<<<<`, `=======`, `>>>>>>>`）**
4. **保留正确的代码**

```cpp
// 解决后的代码（保留更好的实现）
case 6: { // 按ID查找论文
    int id;
    cout << "请输入论文ID: ";
    cin >> id;
    Paper* result = hashSearch.findById(id);
    if (result) {
        result->print();
    } else {
        cout << "未找到该论文" << endl;
    }
    break;
}
```

```bash
# 4. 标记冲突已解决
git add src/main.cpp

# 5. 完成合并
git commit -m "merge: 解决main.cpp的合并冲突

- 统一了功能6的实现
- 采用了更完善的错误处理"

# 6. 推送
git push origin dev-B
```

**最佳实践：**

- 🎯 尽量避免多人同时修改同一个文件
- 📞 修改前在群里打个招呼
- 🔄 频繁地合并main分支到自己的分支
- 💬 遇到冲突先沟通，再解决

---

## 🔍 常用Git命令速查

### 查看状态

```bash
git status                  # 查看当前状态（最常用）
git log                     # 查看提交历史
git log --oneline          # 简洁的历史记录
git log --graph --oneline  # 图形化显示分支
git branch                  # 查看本地分支
git branch -a               # 查看所有分支（包括远程）
git diff                    # 查看未暂存的修改
git diff --staged           # 查看已暂存的修改
```

### 分支操作

```bash
git checkout main           # 切换到main分支
git checkout dev-A          # 切换到dev-A分支
git checkout -b dev-A       # 创建并切换到dev-A分支
git branch -d dev-A         # 删除dev-A分支（本地）
git push origin --delete dev-A  # 删除远程分支
```

### 同步代码

```bash
git pull origin main        # 拉取main分支的最新代码（fetch + merge）
git fetch origin            # 获取所有远程更新（但不合并）
git merge origin/main       # 合并远程main分支到当前分支
```

### 提交相关

```bash
git add filename            # 添加单个文件
git add .                   # 添加所有修改
git commit -m "message"     # 提交并附带消息
git commit --amend          # 修改最后一次提交
git push origin branch-name # 推送到远程分支
```

### 撤销操作

```bash
git checkout -- file.cpp    # 撤销对file.cpp的修改
git reset HEAD file.cpp     # 取消暂存file.cpp
git reset --soft HEAD~1     # 撤销最后一次提交，保留修改
git reset --hard HEAD~1     # 撤销最后一次提交，丢弃修改（危险！）
git revert <commit-id>      # 撤销某个提交（更安全）
```

### 查看差异

```bash
git diff                    # 查看未暂存的修改
git diff --staged           # 查看已暂存的修改
git diff main dev-A         # 比较两个分支的差异
git diff HEAD~1 HEAD        # 比较最近两次提交
```

---

## 📋 提交信息规范

好的提交信息让团队协作更顺畅！

### 格式

```
<类型>(<范围>): <简短描述>

<详细说明>（可选）

<关联问题>（可选）
```

### 类型标签

|类型|说明|示例|
|---|---|---|
|`feat`|新功能|feat: 实现Paper类的构造函数|
|`fix`|修复bug|fix: 修复FileManager加载时的解析错误|
|`docs`|文档修改|docs: 更新README中的编译说明|
|`style`|代码格式|style: 统一代码缩进为4空格|
|`refactor`|代码重构|refactor: 优化HashSearch的哈希函数|
|`test`|测试相关|test: 添加Paper类的单元测试|
|`chore`|构建/工具|chore: 更新Makefile编译选项|

### 示例

```bash
# ✅ 好的提交信息
git commit -m "feat(Paper): 实现Paper类的所有Getter/Setter方法

- 添加getPaperId(), getTitle()等方法
- 添加setPaperId(), setTitle()等方法
- 实现print()方法，格式化输出论文信息"

git commit -m "fix(FileManager): 修复加载时关键词解析错误

问题：当关键词为空时，会导致程序崩溃
解决：添加空字符串检查"

git commit -m "docs: 更新README中的编译说明"

git commit -m "refactor(HashSearch): 优化哈希函数，减少冲突率"

# ❌ 不好的提交信息
git commit -m "update"
git commit -m "修改"
git commit -m "aaa"
git commit -m "test"
git commit -m "fix bug"  # 没说清楚修复了什么bug
```

---

## 🚨 紧急情况处理

### 情况1：不小心在main分支上修改了代码

```bash
# 1. 先保存当前修改
git stash save "不小心在main上的修改"

# 2. 切换到你的分支
git checkout dev-A

# 3. 恢复修改
git stash pop

# 4. 正常提交
git add .
git commit -m "feat: ..."
git push origin dev-A
```

### 情况2：想要撤销刚才的提交

```bash
# 方案1：撤销最后一次提交，但保留代码修改
git reset --soft HEAD~1

# 重新修改后再提交
git add .
git commit -m "正确的提交信息"

# 方案2：修改最后一次提交的信息
git commit --amend -m "新的提交信息"

# 方案3：已经push了，想撤销
git revert HEAD
git push origin dev-A
```

### 情况3：代码写错了，想要回到上次提交的状态

```bash
# ⚠️ 警告：会丢失所有未提交的修改
git reset --hard HEAD

# 或者只撤销某个文件
git checkout -- src/Paper.cpp

# 如果想保留修改但从暂存区移除
git reset HEAD src/Paper.cpp
```

### 情况4：push失败，提示"非快进"

```bash
# 错误信息：Updates were rejected because the remote contains work...

# 1. 先拉取远程代码
git pull origin dev-A

# 2. 如果有冲突，解决冲突
# 3. 再次推送
git push origin dev-A

# 如果确定要覆盖远程（危险！）
git push -f origin dev-A  # 慎用！
```

### 情况5：想要放弃某个分支，重新开始

```bash
# 1. 切换到main分支
git checkout main

# 2. 删除本地的开发分支
git branch -D dev-A

# 3. 重新创建
git checkout -b dev-A

# 4. 推送（覆盖远程）
git push -f origin dev-A
```

### 情况6：不小心删除了文件

```bash
# 如果还没有commit
git checkout -- deleted_file.cpp

# 如果已经commit了
git log  # 找到删除前的commit ID
git checkout <commit-id> -- deleted_file.cpp
```

---

## ✅ 协作检查清单

### 每天开始工作前 ☀️

- [ ] `git status` 确认当前分支
- [ ] `git checkout dev-A` 切换到自己的分支
- [ ] `git pull origin main` 拉取最新的主分支代码
- [ ] 解决可能的冲突
- [ ] 查看微信群是否有重要通知

### 编写代码时 💻

- [ ] 只修改自己负责的文件
- [ ] 修改公共文件（如main.cpp）前先在群里说一声
- [ ] 代码写好注释
- [ ] 遵循代码规范（命名、缩进等）

### 提交代码前 📤

- [ ] `make clean && make` 确保能编译通过
- [ ] 测试你的功能是否正常
- [ ] `git status` 检查修改了哪些文件
- [ ] 只add你负责的文件
- [ ] 写清楚的提交信息
- [ ] 确认没有提交临时文件（.o, .exe等）

### 提交代码后 ✅

- [ ] `git push origin dev-A` 推送到GitHub
- [ ] 在微信群通知队友
- [ ] 如果是重要功能，创建PR并请队友review

### 合并到主分支前 🔀

- [ ] 确保代码能编译
- [ ] 确保所有功能都测试通过
- [ ] 创建PR，写清楚修改内容
- [ ] 请至少一个队友review
- [ ] 等待approve后再合并
- [ ] 合并后通知队友

### 每周末检查 📅

- [ ] 查看是否有未解决的PR
- [ ] 查看是否有未合并的分支
- [ ] 整理代码，删除不需要的文件
- [ ] 更新README文档

---

## 🎯 推荐的工作节奏

### Week 1 - 基础搭建

**同学A (Suiyi)**

- [ ] Day 1-2: 设计并实现Paper类
    - 定义所有成员变量
    - 实现构造/析构函数
    - 实现getter/setter
    - 实现print()方法
    - 测试通过后创建PR
- [ ] Day 3-4: 实现FileManager类
    - 设计文件格式（CSV/自定义）
    - 实现loadPapers()
    - 实现savePapers()
    - 准备测试数据papers.txt
    - 测试通过后创建PR
- [ ] Day 5-7: 实现main.cpp基础框架
    - 实现菜单系统
    - 实现功能1-5
    - 为功能6-14预留接口
    - 创建编译配置（Makefile）
    - 创建PR

**同学B和C**

- [ ] Day 1-3: 学习Git/GitHub
    - 克隆项目
    - 创建自己的分支
    - 练习基本的Git操作
    - 阅读项目文档
- [ ] Day 4-7: 阅读A的代码
    - Review A的PR
    - 理解Paper类的接口
    - 理解FileManager的使用
    - 开始设计自己负责的类

### Week 2 - 并行开发

**同学A**

- [ ] Review B和C的代码
- [ ] 协调main.cpp的功能调用
- [ ] 解决集成中的问题
- [ ] 完善文档

**同学B**

- [ ] Day 1-2: 实现HashSearch类
    - 设计哈希表结构
    - 实现哈希函数
    - 实现findById()
    - 测试并创建PR
- [ ] Day 3-4: 实现BSTSearch类
    - 设计BST节点结构
    - 实现插入、查找
    - 实现findByTitle()
    - 测试并创建PR
- [ ] Day 5-7: 实现Sorter类
    - 实现sortByYear()
    - 实现sortByCitations()
    - 实现sortByTitle()
    - 测试并创建PR

**同学C**

- [ ] Day 1-3: 实现GraphAnalyzer类
    - 设计图的数据结构
    - 构建论文引用图
    - 实现BFS算法
    - 测试并创建PR
- [ ] Day 4-7: 实现Recommender类
    - 统计关键词频率
    - 实现Top-N算法
    - 可能用堆优化
    - 测试并创建PR

### Week 3 - 集成与测试

**全员任务**

- [ ] Day 1-2: 集成所有模块
    - 合并所有PR到main
    - 解决冲突
    - 确保整体编译通过
- [ ] Day 3-4: 功能测试
    - 测试每个功能
    - 记录bug
    - 修复bug
- [ ] Day 5-6: 性能优化
    - 测试大数据量
    - 优化算法
    - 优化内存使用
- [ ] Day 7: 完善文档
    - 更新README
    - 添加使用说明
    - 准备演示

### Week 4 - 收尾与展示

**全员任务**

- [ ] Day 1-2: 最后的bug修复
- [ ] Day 3-4: 代码清理
    - 删除调试代码
    - 统一代码风格
    - 添加必要注释
- [ ] Day 5-6: 准备展示
    - 制作PPT
    - 准备演示数据
    - 排练展示
- [ ] Day 7: 项目总结
    - 写项目总结报告
    - 归档所有文档

---

## 🛠️ 推荐工具

### 1. Git GUI客户端（可选）

**GitHub Desktop** - 最简单，适合新手

- 下载：https://desktop.github.com
- 优点：界面友好，可视化操作
- 适合：不习惯命令行的同学

**SourceTree** - 功能强大

- 下载：https://www.sourcetreeapp.com
- 优点：功能完整，支持Git Flow
- 适合：需要复杂操作的场景

**GitKraken** - 界面漂亮

- 下载：https://www.gitkraken.com
- 优点：图形化界面美观，易于理解
- 适合：喜欢图形化的同学

### 2. VS Code Git插件

**GitLens** - 查看代码历史

```
插件市场搜索：GitLens
功能：查看每行代码的修改历史
```

**Git Graph** - 可视化分支树

```
插件市场搜索：Git Graph
功能：图形化显示分支结构
```

**Git History** - 查看文件历史

```
插件市场搜索：Git History
功能：查看文件的修改历史
```

### 3. 命令行工具（进阶）

**tig** - 更好看的git log

```bash
# Ubuntu/Debian
sudo apt install tig

# 使用
tig  # 在项目目录下运行
```

**lazygit** - 图形化的命令行Git工具

```bash
# 安装
brew install lazygit  # macOS

# 使用
lazygit  # 在项目目录下运行
```

### 4. 编译工具

**Make** - 自动化编译

```bash
# Ubuntu/Debian
sudo apt install build-essential

# 使用
make        # 编译
make clean  # 清理
```

**CMake** - 跨平台编译

```bash
# Ubuntu/Debian
sudo apt install cmake

# 使用
mkdir build && cd build
cmake ..
make
```

---

## 💬 沟通协议

### 微信群约定

#### 1. 每天提交代码后通知

**格式：**

```
✅ [A] Paper类实现完成

已提交分支：dev-A
修改文件：
- include/Paper.h
- src/Paper.cpp

功能：完成Paper类的所有基础方法
状态：编译通过，测试通过
PR: https://github.com/SuiyiChang/paper-management-system/pull/1

请 @同学B @同学C review！
```

#### 2. 遇到问题时及时提问

**格式：**

```
❓ [B] 关于HashSearch的问题

问题：在main.cpp的功能6中，应该如何调用HashSearch？

目前想法：
HashSearch hs(papers);
Paper* result = hs.findById(id);

@同学A 这样对吗？
```

#### 3. 修改公共文件前提前声明

**格式：**

```
🔒 [A] 要修改main.cpp了

范围：main.cpp的菜单部分（约100行）
预计时间：1小时
内容：添加功能6-8的调用

请其他人暂时不要修改main.cpp！
完成后我会通知。
```

#### 4. 完成一个模块时创建PR

**格式：**

```
📢 [B] HashSearch模块完成！

PR链接：https://github.com/SuiyiChang/paper-management-system/pull/2

标题：[同学B] 实现HashSearch哈希查找功能

描述：
✅ 实现哈希表数据结构（链地址法）
✅ 实现findById()方法
✅ 平均查找时间O(1)
✅ 编译测试通过

@全体成员 请帮忙review！
```

#### 5. Review代码时的反馈

**格式：**

```
👍 [C] Review PR#2 (HashSearch)

整体：代码质量很好，逻辑清晰

建议：
1. Line 45: 建议添加边界检查
2. Line 67: 可以优化一下哈希函数

其他：LGTM（Looks Good To Me）

✅ Approved!
```

#### 6. 遇到merge冲突

**格式：**

```
⚠️ [A] main.cpp有冲突

情况：我和B都修改了main.cpp的case 6部分

建议：
@同学B 我们语音讨论一下，看保留哪个实现？
或者我把两个方案都说一下，大家投票？

方案A：...
方案B：...
```

#### 7. 里程碑完成

**格式：**

```
🎉 Week 1 完成！

进度：
✅ 同学A: Paper类、FileManager类、main.cpp框架
✅ 同学B: 已开始HashSearch
✅ 同学C: 已开始GraphAnalyzer

下周计划：
- A: Review BC的代码，协调集成
- B: 完成所有查找和排序功能
- C: 完成图分析和推荐功能

加油！💪
```

### 使用标签便于搜索

|标签|含义|示例|
|---|---|---|
|✅|完成|✅ [A] Paper类完成|
|❓|问题|❓ [B] 如何调用Paper类？|
|🔒|锁定文件|🔒 [C] 正在修改main.cpp|
|📢|重要通知|📢 PR已创建，请review|
|⚠️|警告/冲突|⚠️ 发现merge冲突|
|🎉|里程碑|🎉 所有功能完成！|
|💡|建议|💡 可以用堆优化Top-N|

---

## 📚 学习资源

### Git基础教程

**中文教程**

- [Git简明指南](https://rogerdudler.github.io/git-guide/index.zh.html) - 快速入门
- [廖雪峰的Git教程](https://www.liaoxuefeng.com/wiki/896043488029600) - 详细全面
- [Learn Git Branching](https://learngitbranching.js.org/?locale=zh_CN) - 互动游戏

**视频教程**

- B站：搜索"Git入门教程"
- B站：搜索"GitHub团队协作"

### GitHub使用

**官方文档**

- [GitHub官方文档（中文）](https://docs.github.com/cn)
- [GitHub Pull Request教程](https://docs.github.com/cn/pull-requests)
- [GitHub Issues使用](https://docs.github.com/cn/issues)

### 实用技巧

**Git Cheat Sheet**

```bash
# 下载PDF版本
wget https://education.github.com/git-cheat-sheet-education.pdf
```

**Pro Git书籍**

- 在线阅读：https://git-scm.com/book/zh/v2
- 免费下载PDF

---

## ❓ 常见问题FAQ

### Q1: 我clone项目后，看不到同学的分支？

```bash
# 查看所有远程分支
git branch -a

# 应该能看到：
# remotes/origin/dev-A
# remotes/origin/dev-B
# remotes/origin/dev-C

# 切换到同学的分支（本地没有时）
git checkout -b dev-B origin/dev-B

# 或者直接切换（Git 2.23+）
git switch dev-B
```

### Q2: 我的代码和同学的代码冲突了怎么办？

**步骤：**

1. 先在微信群里沟通
2. 商量好由谁的代码为准，或如何合并
3. 按照"解决冲突"部分的步骤操作
4. 测试确保没问题
5. 提交并通知队友

### Q3: 我不小心把同学的代码删了怎么办？

```bash
# 如果还没commit，立即恢复
git checkout -- filename

# 如果已经commit，回退到上一个版本
git reset --hard HEAD~1

# 如果已经push，需要立即通知队友
# 然后：
git revert HEAD
git push origin dev-A
```

### Q4: 我想看同学写的代码，但还没合并到main？

```bash
# 方法1：切换到同学的分支
git fetch origin
git checkout dev-B

# 方法2：在GitHub网站上查看
# 打开：https://github.com/SuiyiChang/paper-management-system
# 选择分支：点击"main" → 选择"dev-B"

# 方法3：查看PR中的代码
# 打开对应的Pull Request
# 点击"Files changed"查看所有修改
```

### Q5: 每次push都要输入密码很麻烦？

**方法1：使用SSH密钥（推荐）**

```bash
# 1. 生成SSH密钥
ssh-keygen -t ed25519 -C "your_email@example.com"
# 一路回车，使用默认设置

# 2. 复制公钥
cat ~/.ssh/id_ed25519.pub
# 复制输出的内容

# 3. 添加到GitHub
# 打开 https://github.com/settings/keys
# 点击"New SSH key"
# 粘贴公钥，保存

# 4. 修改远程仓库地址
git remote set-url origin git@github.com:SuiyiChang/paper-management-system.git

# 5. 测试
git push origin dev-A  # 不再需要密码
```

**方法2：使用Personal Access Token**

```bash
# 1. 生成Token
# 打开：https://github.com/settings/tokens
# 点击"Generate new token"
# 设置权限：repo（全选）
# 生成后复制token（只显示一次！）

# 2. 使用token作为密码
# 当git要求输入密码时，输入token（不是GitHub密码）

# 3. 保存凭据（避免重复输入）
git config --global credential.helper store
# 下次输入后会自动保存
```

### Q6: 我想撤销一个已经push的commit？

```bash
# 方法1：用revert（推荐，保留历史）
git revert <commit-id>
git push origin dev-A

# 方法2：用reset（危险，会改写历史）
git reset --hard HEAD~1
git push -f origin dev-A  # 强制推送

# ⚠️ 注意：
# - 如果别人已经pull了你的commit，不要用方法2
# - 建议在群里通知后再操作
```

### Q7: 如何查看某个文件的修改历史？

```bash
# 查看文件的所有修改记录
git log -- src/Paper.cpp

# 查看文件的详细修改内容
git log -p -- src/Paper.cpp

# 查看谁修改了某一行（blame）
git blame src/Paper.cpp

# 在VS Code中
# 安装GitLens插件，点击行号左侧可以看到修改历史
```

### Q8: 如何临时保存当前修改，切换到其他分支？

```bash
# 1. 保存当前修改
git stash save "正在开发的HashSearch功能"

# 2. 切换到其他分支
git checkout main

# 3. 做其他工作...

# 4. 切回原分支
git checkout dev-B

# 5. 恢复修改
git stash pop

# 查看所有stash
git stash list

# 应用特定的stash
git stash apply stash@{0}
```

### Q9: 如何找回被删除的分支？

```bash
# 1. 查看所有引用日志
git reflog

# 2. 找到被删除分支的最后一个commit
# 例如：abc1234 HEAD@{5}: commit: xxx

# 3. 恢复分支
git checkout -b dev-A-recovered abc1234
```

### Q10: 编译时出现"找不到头文件"错误？

```bash
# 错误示例：
# Paper.h: No such file or directory

# 解决方案1：检查include路径
g++ -c src/Paper.cpp -I include -o Paper.o

# 解决方案2：使用Makefile
make clean
make

# 解决方案3：检查文件是否存在
ls include/Paper.h  # 确认文件存在

# 解决方案4：检查是否在正确的目录
pwd  # 应该在paper-management-system目录下
```

---

## 🎉 协作成功的关键

### 1. **及时沟通** 📞

- ✅ 遇到问题马上在群里说
- ✅ 不要一个人闷头钻研半天
- ✅ 可能别人5分钟就能回答你的问题

### 2. **频繁提交** 🔄

- ✅ 不要等到最后才提交
- ✅ 每完成一个小功能就提交
- ✅ 提交信息写清楚

### 3. **写好注释** 📝

- ✅ 让队友能看懂你的代码
- ✅ 复杂逻辑要解释
- ✅ 接口要有文档注释

### 4. **互相Review** 👀

- ✅ 认真看队友的代码
- ✅ 提出建设性意见
- ✅ 学习别人的优点

### 5. **保持同步** 🔃

- ✅ 每天都pull最新代码
- ✅ 及时合并main分支
- ✅ 避免积累太多冲突

### 6. **遵守规范** 📋

- ✅ 统一的代码风格
- ✅ 统一的命名规范
- ✅ 统一的提交格式

### 7. **测试充分** ✅

- ✅ 提交前自己先测试
- ✅ 不要提交编译不过的代码
- ✅ 考虑边界情况

### 8. **文档完善** 📖

- ✅ README要详细
- ✅ 接口要有说明
- ✅ 复杂功能要有示例

---

## 📞 需要帮助？

### 遇到Git问题时的解决步骤

1. **先看本文档**
    
    - 查看"常见问题"部分
    - 查看"紧急情况处理"部分
2. **在微信群里问队友**
    
    - 描述清楚问题
    - 附上错误信息截图
    - 说明你尝试过什么方法
3. **Google搜索错误信息**
    
    - 复制错误信息
    - 添加"git"关键词
    - 通常能找到Stack Overflow的答案
4. **查看官方文档**
    
    - Git文档：https://git-scm.com/doc
    - GitHub文档：https://docs.github.com/cn
5. **实在解决不了**
    
    - 保存当前工作（git stash）
    - 克隆一份新的项目
    - 重新开始

### 常用调试命令

```bash
# 查看当前状态
git status

# 查看最近的提交
git log --oneline -10

# 查看远程仓库信息
git remote -v

# 查看所有分支
git branch -a

# 查看配置信息
git config --list

# 测试SSH连接
ssh -T git@github.com
```

---

## ✅ 开始协作吧！

现在你们已经准备好了！

### 第一步：每个人设置环境

```bash
# 1. 克隆项目
git clone https://github.com/SuiyiChang/paper-management-system.git
cd paper-management-system

# 2. 配置Git用户信息（重要！）
git config user.name "你的名字"
git config user.email "你的邮箱"

# 3. 创建自己的分支
git checkout -b dev-A  # 或 dev-B / dev-C

# 4. 推送分支
git push -u origin dev-A

# 5. 在群里报告
```

### 第二步：开始编写代码

- **同学A**: 先实现Paper类和FileManager类
- **同学B和C**: 等A的代码合并后，开始你们的模块

### 第三步：保持沟通

- 每天在群里同步进度
- 遇到问题及时讨论
- 互相帮助，共同进步

---

## 🎯 项目时间线（4周计划）

### Week 1: 基础搭建（同学A为主）

- Day 1-2: Paper类 ✅
- Day 3-4: FileManager类 ✅
- Day 5-7: main.cpp框架 ✅

### Week 2: 并行开发

- **A**: 协调集成，Review代码
- **B**: HashSearch + BSTSearch + Sorter
- **C**: GraphAnalyzer + Recommender

### Week 3: 集成测试

- 合并所有代码
- 解决冲突
- 功能测试
- Bug修复

### Week 4: 优化完善

- 性能优化
- 代码清理
- 文档完善
- 准备展示

---

## 📊 项目检查点

### Checkpoint 1: Week 1结束

- [ ] Paper类完成
- [ ] FileManager类完成
- [ ] main.cpp框架完成
- [ ] 所有人都能编译运行
- [ ] 测试数据准备好

### Checkpoint 2: Week 2结束

- [ ] 所有查找功能完成（B）
- [ ] 所有排序功能完成（B）
- [ ] 图分析功能完成（C）
- [ ] 推荐功能完成（C）
- [ ] 各自的PR都创建了

### Checkpoint 3: Week 3结束

- [ ] 所有代码合并到main
- [ ] 编译无错误
- [ ] 所有功能测试通过
- [ ] 主要bug已修复

### Checkpoint 4: Week 4结束

- [ ] 代码优化完成
- [ ] 文档完善
- [ ] README详细
- [ ] 准备好展示
- [ ] 项目完成！🎉

---

## 🌟 最后的话

**团队协作最重要的是：**

1. **沟通** - 有问题就说，不要憋着
2. **尊重** - 尊重队友的代码和意见
3. **负责** - 对自己的模块负责
4. **互助** - 帮助队友解决问题
5. **耐心** - 合并冲突时保持冷静

**记住：**

- 💪 你不是一个人在战斗
- 🤝 团队的力量大于个人
- 📈 一起进步，一起成长
- 🎯 目标是完成项目，不是个人英雄

**最后祝你们：**

- ✅ 协作愉快
- ✅ 项目顺利
- ✅ 学到知识
- ✅ 收获友谊

---

## 📮 反馈与更新

如果你发现这份指南有任何问题或建议：

1. **在GitHub上创建Issue**
    
    - 打开：https://github.com/SuiyiChang/paper-management-system/issues
    - 点击"New issue"
    - 描述问题或建议
2. **在微信群里讨论**
    
    - 大家一起改进这份文档
3. **直接修改**
    
    - Fork这个项目
    - 修改文档
    - 提交PR

---

**祝你们团队协作顺利！加油！** 💪🚀

_文档版本: v2.0_  
_更新日期: 2025-10-21_  
_维护者: Suiyi Chang_  
_适用项目: 学术文献管理与关联分析系统_  
_GitHub仓库: https://github.com/SuiyiChang/paper-management-system.git_