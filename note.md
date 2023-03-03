重启虚拟机:<code>reboot</code>

共享文件夹位置: /mnt/hgfs/\*

下载: <code>#rx [文件名]</code>

### 目录

查询目录: <code>ls -l</code>
查询所有文件/目录:<code>ll</code>
访问目录:<code>cd [目录名]</code>
创建目录:<code>mkdir [目录名]</code>
返回目录:<code>cd</code>

> <code>cd .</code> 本层目录
>
> <code>cd ..</code> 上一层目录
>
> <code>cd</code> / <code>cd~</code> 返回根目录

 拷贝目录:<code>cp [原目录] [新目录] -rf</code> **注意<code>-rf</code>**

### 文件

创建文件:<code>touch [文件名]</code>
更改文件/目录名:<code>mv [文件名] [新名]</code>
编辑文件:<code>vim [文件名]</code>

><code>i</code> 当前光标前开始
>
><code>ctrl + i</code> 行首开始
>
><code>a</code> 当前光标后开始
>
><code>ctrl + a</code> 行末开始
>
><code>o</code> 下一行开始
>
><code>ctrl + o</code> 前一行开始

退出:

><code>:q</code> 正常退出，保留未编辑过的文件
>
><code>:q!</code> 放弃更改，强行退出
>
><code>:wq</code> / <code>shift+zz</code> 保存并退出

查看文件:<code>cat [文件名]</code>
多行查看:<code>more (行数) [文件名]</code>
文件权限:<code>chmod [ugoa] [+-=] [rwx] [文件名]</code>

- u:创建者
  g:同组用户（相同权限用户）
  o:其他用户
  a:全部用户

- +:赋予权限
  -:取消权限
  =:重新赋予

- r:读 w:写 x:执行

拷贝文件:<code>cp [原文件] [新文件]</code>
删除文件:<code>rm [文件名] -i</code> 其后回答y

查找路径:<code>find ./ -name "[文件/目录名]"</code>

帮助文档

- <code>help</code>

> 内建命令：<code>help 命令</code>
> 外部命令：<code>命令 --help</code>

- man手册 <code>man [页] 命令或函数</code>

- <code>info 命令或函数</code>

info命令功能与man命令类似，能够显示出命令的相关资料和信息。内容信息比man手册丰富。

gcc编译

1. 预编译 <code>gcc -E [\*.c] -o [\*.i]</code>
1. 编译 <code>gcc -S [\*.c] -o [\*.s]</code>
1. 汇编 <code>gcc [\*.c] -o [\*.s]</code>
1. 链接 <code>gcc [\*.c] -o [\*]</code>

### 系统IO

文件管理 头文件：<code>sys/types.h, sys/stat.h, fcntl.h, unistd.h</code>

#### 打开文件 open

头文件：sys/types.h, sys/stat.h. fcntl.h

<code>int open(const char*pathname, int flags, (mode_t mode))</code>

#### 关闭文件 close / 读取文件 read / 写入文件 write

头文件：unistd.h

<code>ssize_t read(int fd, void *buf, size_t count</code>

fd:文件描述符

*buf:读取数据存储地址

count:每次读取字节数



### 线程

函数库：<code>pthread.h</code>

#### ID

进程ID在整个系统中都是唯一的， 但线程ID 不同。每一个线程都有一个唯一ID，且只有在他所属的进程中才有意义。

表示法：进程ID {pid_t}为一个非负整数，线程ID {pthread_t}. 可通过<code>pthread_self()</code>查询自己线程的ID.

使用<code>pthread_equal()</code>检查两个线程ID是否相等。

#### 建立一个线程

函数：<code>int pthread_create(pthread_t \*thread,const pthread_attr_t \*attr, void \*(\*start_routine)
(void \*), void \*arg);</code>

><code>pthread_t \*thread</code>: 线程id，它是一个unsigned int类型
><code>const pthread_attr_t \*attr</code>: 设置线程属性，NULL为默认设置
>
><code>void \*(\*start_routine) (void *)</code>: 函数指针，新创建的线程从start_routine()函数开始执行，返回类型为void\*, 本质为第四个参数arg
>
><code>void *arg</code>: 传递给start_routine()的参数，也可设置成NULL，表示不需要传入参数给start_routine().

返回值：成功时返回0；失败时返回错误

示例代码：

```c
#include <stdio.h>
#include <pthread.h>
static void *new_thread_start(void *arg) {
	printf("新线程:进程ID<%d> 线程ID<%lu>\n", getpid(), pthread_self());//获取进程
	return (void *)0;
int main(void)
{
	pthread_t tid;
    int ret;
	ret = pthread_create(&tid,NULL,new_thread_start,NULL);
if (ret){
	fprintf(stderr,"Error: %s\n", strerror(ret));
    exit(-1);
	}
	printf("主线程:进程ID<%d> 线程ID<%lu>in", getpid(), pthread_self());
    sleep(1);
	exit(0);
}
```

在ubuntu中运行时注意添加-pthread连接

### 显示bmp图像

lcd位置：/dev/fd0

