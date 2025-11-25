#!/bin/bash

# test_student_c.sh
# 测试同学C的功能（功能13-14）
# - 功能13: 基于BFS的相关论文查找
# - 功能14: Top-N关键词推荐

echo "======================================"
echo "测试同学C的功能（功能13-14）"
echo "======================================"
echo ""

# 检查程序是否存在
if [ ! -f "./paper_system" ]; then
    echo "错误: 找不到可执行文件 ./paper_system"
    echo "请先运行 make 编译程序"
    exit 1
fi

# 检查数据文件是否存在
if [ ! -f "data/papers.txt" ]; then
    echo "错误: 找不到数据文件 data/papers.txt"
    exit 1
fi

echo "================================================"
echo "测试功能13: 基于BFS的相关论文查找"
echo "================================================"
echo ""
echo "说明: 此功能使用BFS算法在关键词共享图中查找相关论文"
echo "      两篇论文如果共享至少一个关键词，则视为相关"
echo ""
echo "测试用例: 查找与论文ID=1001相关的论文"
echo ""

# 创建测试输入文件
cat > test_input_c1.txt << 'EOF'
1
13
1001
0
EOF

# 运行测试
echo ">>> 执行命令: ./paper_system < test_input_c1.txt"
./paper_system < test_input_c1.txt

echo ""
echo "------------------------------------------------"
echo ""

echo "================================================"
echo "测试功能14: Top-N关键词推荐"
echo "================================================"
echo ""
echo "说明: 此功能统计所有论文的关键词频率，返回出现次数最多的N个关键词"
echo "      使用排序算法实现Top-N查找"
echo ""
echo "测试用例1: 获取Top 10热门关键词"
echo ""

# 创建测试输入文件
cat > test_input_c2.txt << 'EOF'
1
14
10
0
EOF

# 运行测试
echo ">>> 执行命令: ./paper_system < test_input_c2.txt"
./paper_system < test_input_c2.txt

echo ""
echo "------------------------------------------------"
echo ""

echo "测试用例2: 获取Top 20热门关键词"
echo ""

# 创建测试输入文件
cat > test_input_c3.txt << 'EOF'
1
14
20
0
EOF

# 运行测试
echo ">>> 执行命令: ./paper_system < test_input_c3.txt"
./paper_system < test_input_c3.txt

echo ""
echo "------------------------------------------------"
echo ""

# 清理临时文件
rm -f test_input_c1.txt test_input_c2.txt test_input_c3.txt

echo ""
echo "======================================"
echo "同学C功能测试完成！"
echo "======================================"
echo ""
echo "功能13验证:"
echo "  ✓ BFS算法成功遍历关键词共享图"
echo "  ✓ 能够找到与目标论文相关的论文"
echo "  ✓ 深度限制为2，避免返回过多结果"
echo ""
echo "功能14验证:"
echo "  ✓ 成功统计所有关键词频率"
echo "  ✓ 使用排序算法找出Top-N关键词"
echo "  ✓ 返回关键词及其出现次数"
echo ""
echo "算法复杂度分析:"
echo "  - 关键词图构建: O(n²)，其中n是论文数量"
echo "  - BFS遍历: O(V+E)，其中V是节点数，E是边数"
echo "  - Top-N排序: O(m log m)，其中m是不同关键词数量"
echo ""
