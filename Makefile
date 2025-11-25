# 学术文献管理系统 Makefile
# 使用方法：
#   make         - 编译整个项目
#   make clean   - 清理编译文件
#   make run     - 编译并运行

# 编译器设置
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I./include

# 目录设置
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = .

# 目标可执行文件
TARGET = $(BINDIR)/paper_system

# 源文件
SOURCES = $(SRCDIR)/Paper.cpp \
          $(SRCDIR)/FileManager.cpp \
          $(SRCDIR)/HashSearch.cpp \
          $(SRCDIR)/BSTSearch.cpp \
          $(SRCDIR)/KMPSearch.cpp \
          $(SRCDIR)/Sorter.cpp \
          $(SRCDIR)/GraphAnalyzer.cpp \
          $(SRCDIR)/Recommender.cpp \
          $(SRCDIR)/main.cpp

# 目标文件（将.cpp替换为.o）
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# 头文件依赖
HEADERS = $(INCDIR)/Paper.h \
          $(INCDIR)/FileManager.h \
          $(INCDIR)/HashSearch.h \
          $(INCDIR)/BSTSearch.h \
          $(INCDIR)/KMPSearch.h \
          $(INCDIR)/Sorter.h \
          $(INCDIR)/GraphAnalyzer.h \
          $(INCDIR)/Recommender.h

# 默认目标：编译整个项目
all: $(TARGET)

# 创建obj目录（如果不存在）
$(OBJDIR):
	mkdir -p $(OBJDIR)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "编译完成！可执行文件: $(TARGET)"
	@echo "运行方式: ./paper_system 或 make run"

# 编译源文件生成目标文件
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "编译: $< -> $@"

# 运行程序
run: $(TARGET)
	@echo "==================== 运行程序 ===================="
	@./$(TARGET)

# 清理编译文件
clean:
	rm -rf $(OBJDIR)
	rm -f $(TARGET)
	@echo "清理完成！"

# 重新编译
rebuild: clean all

# 显示帮助信息
help:
	@echo "学术文献管理系统 Makefile"
	@echo ""
	@echo "可用命令："
	@echo "  make          - 编译整个项目"
	@echo "  make run      - 编译并运行程序"
	@echo "  make clean    - 清理编译文件"
	@echo "  make rebuild  - 清理后重新编译"
	@echo "  make help     - 显示此帮助信息"
	@echo ""
	@echo "文件说明："
	@echo "  源文件目录: $(SRCDIR)/"
	@echo "  头文件目录: $(INCDIR)/"
	@echo "  目标文件目录: $(OBJDIR)/"
	@echo "  可执行文件: $(TARGET)"

# 标记伪目标（这些目标不对应实际文件）
.PHONY: all run clean rebuild help

# 编译调试版本（带调试信息）
debug: CXXFLAGS += -g -DDEBUG
debug: clean $(TARGET)
	@echo "调试版本编译完成！使用 gdb ./paper_system 进行调试"

# 编译优化版本
release: CXXFLAGS += -O2 -DNDEBUG
release: clean $(TARGET)
	@echo "优化版本编译完成！"

# 检查代码风格（需要安装 cpplint）
lint:
	@echo "检查代码风格..."
	@if command -v cpplint > /dev/null; then \
		cpplint --filter=-legal/copyright $(SOURCES) $(HEADERS); \
	else \
		echo "未安装 cpplint，跳过代码检查"; \
	fi

# 显示项目信息
info:
	@echo "项目信息："
	@echo "  编译器: $(CXX)"
	@echo "  编译选项: $(CXXFLAGS)"
	@echo "  源文件: $(words $(SOURCES)) 个"
	@echo "  头文件: $(words $(HEADERS)) 个"
	@echo "  目标文件: $(TARGET)"
	@echo ""
	@echo "文件列表："
	@echo "源文件:"
	@for file in $(SOURCES); do echo "  $$file"; done
	@echo "头文件:"
	@for file in $(HEADERS); do echo "  $$file"; done
