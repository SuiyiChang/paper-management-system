#!/bin/bash
# 测试同学A的功能实现

echo "=== 测试同学A的功能实现 ==="
echo ""

# 测试1: 加载论文数据并显示
echo "测试1: 加载论文数据并显示前10篇"
echo ""

# 创建测试输入
cat << 'EOF' | ./paper_system
1
2
0
EOF

echo ""
echo "✓ 测试1完成"
echo ""
echo "================================"
echo ""

# 检查数据文件是否存在
if [ -f "data/papers.txt" ]; then
    echo "✓ 数据文件 data/papers.txt 存在"
    echo "  文件大小: $(wc -c < data/papers.txt) 字节"
    echo "  论文数量: $(($(wc -l < data/papers.txt) - 1)) 篇（不含表头）"
else
    echo "✗ 数据文件不存在"
fi

echo ""
echo "=== 所有测试完成 ==="
