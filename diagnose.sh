#!/bin/bash
echo "=== 诊断开始 ==="

echo "1. 检查磁盘空间："
df -h /d

echo -e "\n2. 检查目录权限："
ls -la .

echo -e "\n3. 检查是否有进程占用："
tasklist | grep paper_system

echo -e "\n4. 尝试创建测试文件："
if touch test_write.exe 2>/dev/null; then
    echo "✓ 可以创建 .exe 文件"
    rm test_write.exe
else
    echo "✗ 无法创建 .exe 文件 - 可能是权限或杀毒软件问题"
fi

echo -e "\n5. 检查 .o 文件："
ls -lh obj/

echo -e "\n6. 尝试简单链接："
g++ -o simple_test.exe obj/main.o obj/Paper.o 2>&1 | head -20
rm -f simple_test.exe

echo -e "\n=== 诊断完成 ==="