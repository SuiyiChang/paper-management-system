#!/bin/bash
echo "=== 检查对象文件符号 ==="

# 重新编译
make clean
make 2>&1 | grep -E "(error|warning|collect2)"

if [ -d obj ]; then
    echo -e "\n=== 生成的 .o 文件 ==="
    ls -lh obj/
    
    echo -e "\n=== 检查 main.o 中未定义的符号 ==="
    nm obj/main.o 2>/dev/null | grep " U " | head -10
    
    echo -e "\n=== 检查所有 .o 文件的导出符号 ==="
    for f in obj/*.o; do
        echo "--- $f ---"
        nm "$f" 2>/dev/null | grep " T " | wc -l
    done
    
    echo -e "\n=== 尝试分步链接 ==="
    echo "步骤1: 只链接 Paper 相关"
    g++ -c src/Paper.cpp -o obj/test_paper.o -std=c++11 -I./include 2>&1 | head -5
    
    echo -e "\n步骤2: 尝试最小链接"
    cat > test_minimal.cpp << 'EOF'
#include <iostream>
int main() {
    std::cout << "Test" << std::endl;
    return 0;
}
EOF
    g++ test_minimal.cpp -o test_minimal.exe 2>&1
    if [ -f test_minimal.exe ]; then
        echo "✓ 最小程序链接成功"
        rm test_minimal.exe test_minimal.cpp
    else
        echo "✗ 最小程序链接失败 - g++ 工具链可能有问题"
    fi
else
    echo "✗ obj 目录未创建，编译失败"
fi