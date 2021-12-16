#makfile core 

#下面是一个if else 语句用来表示gcc 编译是否要开启调试模式
#DEBUG 这边引用这个变量，
ifeq ($(DEBUG),true)  
CC =gcc -g
VERSION = debug
else
CC = gcc
VERSION = release
endif

#（wildCard * .c）表示扫描当前目录下所有的.c文件
SRCS = $(wildcard * .c)
 
#把字符串SRCS中的.c 文件替换为.o 文件给OBJS
OBJS = $(SRCS:.c=.o)

#把字符串SRCS 中的.c文件替换为.d 文件给DEPS
#.d 文件是代笔的依赖文件 
DEPS = $(SRCS:.c=.d)

#make 开始会首先执行这一句
#因为，会首先找带有下面格式的语句冒号(:)标识符的语句
#分析： 下面冒号前面代表要生成的目标是all可以随便自由填写，（理解圩go label）
#冒号后面是目标依赖【可以省略】，总的是all 目标需要依赖后面三个变量来生成all目标
#下行的是可执行的代码
 all:$(DEPS) $(OBJS) $(BIN) 
 ifneq()

