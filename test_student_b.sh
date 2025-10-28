#!/bin/bash
# 测试同学B的功能实现

echo "=== 测试同学B的功能实现 ==="
echo ""

# 测试1: 加载数据并按ID查找
echo "测试1: 按ID查找论文（哈希表）"
echo "查找ID=1001的论文（Support-Vector Networks）"
echo ""

cat << 'EOF' | ./paper_system
1
6
1001
0
EOF

echo ""
echo "✓ 测试1完成"
echo "================================"
echo ""

# 测试2: 按标题查找
echo "测试2: 按标题查找论文（BST）"
echo "查找标题='Deep Learning'"
echo ""

cat << 'EOF' | ./paper_system
1
7
Deep Learning
0
EOF

echo ""
echo "✓ 测试2完成"
echo "================================"
echo ""

# 测试3: 按内容模糊查找
echo "测试3: 按内容模糊查找（KMP算法）"
echo "查找关键词='learning'"
echo ""

cat << 'EOF' | ./paper_system
1
8
learning
0
EOF

echo ""
echo "✓ 测试3完成"
echo "================================"
echo ""

# 测试4: 按年份排序（只显示前5篇）
echo "测试4: 按年份降序排序"
echo "（应该显示最新的论文在前）"
echo ""

cat << 'EOF' | ./paper_system
1
9
0
EOF

echo ""
echo "✓ 测试4完成"
echo "================================"
echo ""

echo "=== B同学功能测试完成 ==="
echo ""
echo "已测试的功能："
echo "✓ 功能6: 按ID查找（哈希表）"
echo "✓ 功能7: 按标题查找（BST）"
echo "✓ 功能8: 按内容模糊查找（KMP）"
echo "✓ 功能9: 按年份排序"
echo ""
echo "可以手动测试的功能："
echo "- 功能10: 按引用次数排序"
echo "- 功能11: 按标题字母顺序排序"
echo "- 功能12: 合并有序列表"
