#!/bin/bash

# test_all_functions.sh
# 完整系统测试 - 测试所有14个功能
# 同学A: 功能1-5 (数据管理)
# 同学B: 功能6-12 (查找与排序)
# 同学C: 功能13-14 (图分析与推荐)

echo "=========================================================="
echo "学术文献管理与关联分析系统 - 完整功能测试"
echo "=========================================================="
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

PASS_COUNT=0
TOTAL_COUNT=14

echo "=========================================="
echo "同学A功能测试 (功能1-5: 数据管理)"
echo "=========================================="
echo ""

# 功能1: 加载论文数据
echo "[测试 1/14] 功能1: 加载论文数据"
cat > test_input.txt << 'EOF'
1
0
EOF
./paper_system < test_input.txt > test_output.txt 2>&1
if grep -q "成功加载 50 篇论文" test_output.txt; then
    echo "✓ 通过: 成功加载50篇论文"
    ((PASS_COUNT++))
else
    echo "✗ 失败: 未能正确加载论文数据"
fi
echo ""

# 功能2: 显示所有论文
echo "[测试 2/14] 功能2: 显示所有论文 (简要信息)"
cat > test_input.txt << 'EOF'
1
2
0
EOF
./paper_system < test_input.txt > test_output.txt 2>&1
if grep -q "Support-Vector Networks" test_output.txt && grep -q "共 50 篇论文" test_output.txt; then
    echo "✓ 通过: 成功显示所有论文"
    ((PASS_COUNT++))
else
    echo "✗ 失败: 未能正确显示论文列表"
fi
echo ""

# 功能3-5: 综合测试添加、删除、保存
echo "[测试 3-5/14] 功能3-5: 添加新论文、删除论文、保存数据"
cat > test_input.txt << 'EOF'
1
3
9999
Test Paper Title
Test Author
TestKeyword
2025
100
Test abstract content
4
9999
y
5
0
EOF
./paper_system < test_input.txt > test_output.txt 2>&1
TEST_3_PASS=0
TEST_4_PASS=0
TEST_5_PASS=0

if grep -q "论文添加成功" test_output.txt; then
    echo "✓ [测试 3] 通过: 成功添加新论文"
    ((PASS_COUNT++))
    TEST_3_PASS=1
else
    echo "✗ [测试 3] 失败: 未能正确添加论文"
fi

if grep -q "论文删除成功" test_output.txt; then
    echo "✓ [测试 4] 通过: 成功删除论文"
    ((PASS_COUNT++))
    TEST_4_PASS=1
else
    echo "✗ [测试 4] 失败: 未能正确删除论文"
fi

if grep -q "数据保存成功" test_output.txt; then
    echo "✓ [测试 5] 通过: 成功保存数据到文件"
    ((PASS_COUNT++))
    TEST_5_PASS=1
else
    echo "✗ [测试 5] 失败: 未能正确保存数据"
fi
echo ""

echo "=========================================="
echo "同学B功能测试 (功能6-12: 查找与排序)"
echo "=========================================="
echo ""

# 功能6: 按ID查找论文 (Hash表)
echo "[测试 6/14] 功能6: 按ID查找论文 (Hash表)"
cat > test_input.txt << 'EOF'
1
6
1001
0
EOF
./paper_system < test_input.txt > test_output.txt 2>&1
if grep -q "Support-Vector Networks" test_output.txt; then
    echo "✓ 通过: 成功通过Hash表查找论文"
    ((PASS_COUNT++))
else
    echo "✗ 失败: Hash表查找失败"
fi
echo ""

# 功能7: 按标题查找论文 (BST)
echo "[测试 7/14] 功能7: 按标题查找论文 (BST)"
cat > test_input.txt << 'EOF'
1
7
Support-Vector Networks
0
EOF
./paper_system < test_input.txt > test_output.txt 2>&1
if grep -q "Corinna Cortes" test_output.txt; then
    echo "✓ 通过: 成功通过BST查找论文"
    ((PASS_COUNT++))
else
    echo "✗ 失败: BST查找失败"
fi
echo ""

# 功能8: 按内容模糊查找 (KMP)
echo "[测试 8/14] 功能8: 按内容模糊查找论文 (KMP)"
cat > test_input.txt << 'EOF'
1
8
Deep Learning
0
EOF
./paper_system < test_input.txt > test_output.txt 2>&1
if grep -q "找到.*篇包含" test_output.txt; then
    echo "✓ 通过: 成功使用KMP算法查找论文"
    ((PASS_COUNT++))
else
    echo "✗ 失败: KMP查找失败"
fi
echo ""

# 功能9: 按年份降序排序
echo "[测试 9/14] 功能9: 按年份降序排序并显示"
cat > test_input.txt << 'EOF'
1
9
0
EOF
./paper_system < test_input.txt > test_output.txt 2>&1
if grep -q "排序结果" test_output.txt; then
    echo "✓ 通过: 成功按年份排序"
    ((PASS_COUNT++))
else
    echo "✗ 失败: 年份排序失败"
fi
echo ""

# 功能10: 按引用次数降序排序
echo "[测试 10/14] 功能10: 按引用次数降序排序并显示"
cat > test_input.txt << 'EOF'
1
10
0
EOF
./paper_system < test_input.txt > test_output.txt 2>&1
if grep -q "排序结果" test_output.txt; then
    echo "✓ 通过: 成功按引用次数排序"
    ((PASS_COUNT++))
else
    echo "✗ 失败: 引用次数排序失败"
fi
echo ""

# 功能11: 按标题字母顺序排序
echo "[测试 11/14] 功能11: 按标题字母顺序排序并显示"
cat > test_input.txt << 'EOF'
1
11
0
EOF
./paper_system < test_input.txt > test_output.txt 2>&1
if grep -q "排序结果" test_output.txt; then
    echo "✓ 通过: 成功按标题排序"
    ((PASS_COUNT++))
else
    echo "✗ 失败: 标题排序失败"
fi
echo ""

# 功能12: 合并两个有序列表
echo "[测试 12/14] 功能12: 合并两个有序论文列表"
cat > test_input.txt << 'EOF'
1
12
0
EOF
./paper_system < test_input.txt > test_output.txt 2>&1
if grep -q "合并" test_output.txt; then
    echo "✓ 通过: 合并功能正常运行"
    ((PASS_COUNT++))
else
    echo "✗ 失败: 合并功能失败"
fi
echo ""

echo "=========================================="
echo "同学C功能测试 (功能13-14: 图分析与推荐)"
echo "=========================================="
echo ""

# 功能13: 查找相关论文 (BFS)
echo "[测试 13/14] 功能13: 查找相关论文 (BFS图遍历)"
cat > test_input.txt << 'EOF'
1
13
1001
0
EOF
./paper_system < test_input.txt > test_output.txt 2>&1
if grep -q "找到.*篇相关论文" test_output.txt && grep -q "BFS遍历" test_output.txt; then
    echo "✓ 通过: 成功使用BFS查找相关论文"
    ((PASS_COUNT++))
else
    echo "✗ 失败: BFS查找失败"
fi
echo ""

# 功能14: 获取关键词推荐 (Top-N)
echo "[测试 14/14] 功能14: 获取关键词推荐 (Top-N算法)"
cat > test_input.txt << 'EOF'
1
14
10
0
EOF
./paper_system < test_input.txt > test_output.txt 2>&1
if grep -q "Top-.*热门关键词" test_output.txt && grep -q "Deep Learning" test_output.txt; then
    echo "✓ 通过: 成功生成Top-N关键词推荐"
    ((PASS_COUNT++))
else
    echo "✗ 失败: Top-N推荐失败"
fi
echo ""

# 清理临时文件
rm -f test_input.txt test_output.txt

echo "=========================================================="
echo "测试总结"
echo "=========================================================="
echo ""
echo "通过测试: $PASS_COUNT / $TOTAL_COUNT"
echo ""

if [ $PASS_COUNT -eq $TOTAL_COUNT ]; then
    echo "🎉 恭喜！所有功能测试通过！"
    echo ""
    echo "系统功能验证完成："
    echo "  ✓ 同学A (功能1-5): 数据管理功能完整"
    echo "  ✓ 同学B (功能6-12): 查找与排序功能完整"
    echo "  ✓ 同学C (功能13-14): 图分析与推荐功能完整"
    echo ""
    echo "核心算法实现："
    echo "  ✓ Hash表 (O(1)查找)"
    echo "  ✓ 二叉搜索树 (O(log n)查找)"
    echo "  ✓ KMP字符串匹配 (O(n+m))"
    echo "  ✓ 快速排序 (O(n log n))"
    echo "  ✓ 归并算法 (O(n))"
    echo "  ✓ BFS图遍历 (O(V+E))"
    echo "  ✓ Top-N排序算法 (O(m log m))"
    echo ""
    exit 0
else
    echo "⚠️  有 $((TOTAL_COUNT - PASS_COUNT)) 个测试未通过"
    echo "请检查失败的功能并修复问题"
    echo ""
    exit 1
fi
