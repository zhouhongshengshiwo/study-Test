1、虚函数是什么
虚函数是用于实现多态的机制，允许在基类的的函数命名，然后在派生内对该函数进行重写，用来实现多态。
2、指针与引用的区别
3、你学了数据结构随便说几个排序算法给我（说了堆排序算法和快排）
冒泡排序：一次对比两个相邻元素，按照给定的排序规则进行交换。
选择排序：一次将一个最大或者最小的元素放到序列的初始位置。
插入排序：有一段有序的序列，然后每次将一个元素插入到序列里面。
快速排序：通过一趟排序将原序列分成两个序列，一个序列中元素比另一个序列元素都小，然后递归地排序两个子序列。
4、C++里如何申请和释放空间（malloc和new的区别）
通过new和malloc申请的内存，需要通过delete和free来释放，但是两者的区别在于：
malloc只负责分配内存，不负责初始化内存，因此分配的内存中的内容是未定义的。
malloc和free返回和接受的是void*类型的指针，这意味着你需要手动进行类型转换。
void* void_ptr = malloc(sizeof(int)); 
int* int_ptr = static_cast<int*>(void_ptr);

用于动态分配内存并初始化对象

5、内存泄漏是什么
使用new分配内存后，如果没有使用delete来释放它，就会发生内存泄漏。内存泄漏会导致程序占用的内存越来越多，
解决方式：智能指针管理动态内存，避免内存泄漏。

6、 C++写过\实现过哪些项目

7、操作系统的了解
操作系统是管理计算机硬件与软件资源的计算机程序，是用户和计算机硬件之间的桥梁。它的主要功能包括：

进程管理：创建、暂停、终止进程，并且在多个进程中进行调度。
内存管理：管理主存和交换区，分配内存给进程，回收不再使用的内存。
文件系统管理：提供文件和目录的创建、读取、更新、删除等功能。
输入输出设备管理：协调和管理计算机的输入输出设备，如键盘、鼠标、打印机等。
网络管理：通过网络协议栈支持网络通信，实现进程间通信。
安全性管理：控制用户对系统资源的访问权限，保护系统和用户数据的安全。
用户界面：提供用户与计算机交互的界面，可以是图形界面（GUI）或命令行界面（CLI）。
8、Linux的了解
Linux支持Shell脚本编程，用户可以通过编写脚本来简化重复性的任务，提高工作效率。
Linux是一个开源项目，它的源代码可以免费获取和使用。
Linux使用软件包管理系统来安装、更新和删除软件。例如apt、yum、pacman等。
Linux提供了强大的命令行界面（CLI），用户可以通过命令行进行系统管理、软件安装、文件操作等。常见的命令行工具包括bash、ls、cd、cp、mv、rm、cat、grep等。
9· 菱形继承

10.右值引用和完美转发
左值可以取地址，右值不可以，所有左值可以引用，右值不行，右值只能使用右值引用。左值相当于变量，右值是字面量
右值只能引用字面量，能够通过move转发，将原先的值送给另一个变量

虚基础类指针指向的是一个共享的实例，而不是每个派生类中都包含一个基类的实例。

# 类和对象
类是抽象的定义，而对象是具体的实现。通过类，你可以创建多个对象，每个对象都可以有不同的状态（成员变量的值），但共享相同的行为（成员函数）。这种机制促进了代码的重用和模块化设计。

# 水平触发和边缘触发
水平触发：当状态改变时，立即执行回调函数。
当一个文件描述符上有可读写事件时，epoll会持续通知该事件，直到你读取或写入数据，使该文件描述符不再满足可读写条件。
边缘触发：当状态改变时，仅执行一次回调函数。
只有在文件描述符状态从不可读写变为可读写的时候，epoll才会通知你一次。

区别：
水平：即使你没有立即处理该事件，下次epoll_wait调用时，该事件仍然会被报告。
边缘：一旦通知后，即使文件描述符仍然满足可读写条件，也不会再通知，直到状态变化。

# c++网络编程中依次用到哪些函数
shared_from_this()：返回智能指针，指向当前对象的共享指针。
server:
socekt(),
server(){startaccept()};
_acceptor(ioc,boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),port))
startaccept(){new session,acceptor.async_accept(socket(),std::bind(&session::handleaccept))}
handleaccept(){session->start()}
session:
start(asio::asyny_read(),std::bind(&session::handleread))
handleread(err,bytes){asio::async_write(socket(),buffer(),std::bind(&session::handlewrite))}
handlewrite(err,bytes){handleread()}
clinet:
socket()
endpoint(ip,port)
_socket.connect(_endpoint, err);
boost::asio::write(socket，buffer());
boost::asio::read(socket，buffer());

# 动态链接和静态链接
静态链接：在编译和链接阶段，将所有使用的库的代码直接复制到生成的可执行文件中。
动态链接：在编译时，只将库的引用信息（如函数名、地址）放入可执行文件中。在运行时，操作系统加载动态链接库（如.dll或.so文件），并将其链接到程序中。
静态链接的优点：编译时链接，节省内存，运行速度快。

# 关联容器（Associative Containers）和序列容器（Sequence Containers）。
## 序列容器（Sequence Containers）
序列容器中的元素按顺序存储，可以像数组一样通过索引访问。序列容器允许在其任何位置插入和删除元素。
std::vector：类似于动态数组，支持快速的随机访问，但在中间插入或删除元素开销较大。
std::deque：双端队列，支持两端快速的插入和删除操作。
std::list：双向链表，支持高效的插入和删除操作，但无法随机访问元素。
std::forward_list：单向链表，支持高效的单向插入和删除操作，但无法随机访问元素。
std::array（C++11起）：固定大小数组，支持随机访问，开销较小。

# 关联容器（Associative Containers）
关联容器中的元素按某种特定方式自动排序，通常支持快速查找、插入和删除操作。
std::set：无重复元素的集合，元素按升序排列。
std::multiset：允许重复元素的集合，元素也按升序排列。
std::map：类似于字典的数据结构，键值对按键的升序排列。
std::multimap：类似于std::map，但允许重复键。
std::unordered_set（C++11起）：基于哈希表的无重复元素集合，查找、插入和删除操作平均时间为常数。
std::unordered_multiset（C++11起）：基于哈希表的允许重复元素的集合。
std::unordered_map（C++11起）：基于哈希表的无重复键值对集合。
std::unordered_multimap（C++11起）：基于哈希表的允许重复键的键值对集合。

#  std::vector 和 std::list 的区别
存储方式：
std::vector 是一种动态数组，它将元素存储在连续的内存空间中。
std::list 是一种双向链表，它的元素分散在内存中，每个元素（节点）包含数据以及指向前后节点的指针。

内存管理：
std::vector 在需要时会自动扩大容量。扩容机制通常是分配一个新的更大的数组，并将旧数组中的元素复制到新数组中。
std::list 不需要考虑扩容问题，因为它是动态分配的，并且通过指针链接不同的节点。


# makefile
在编写Makefile时，"跑道"并不是一个标准的术语。你可能是指Makefile的执行流程或构建依赖关系的部分。Makefile的基本原理是描述如何构建一个目标文件或可执行文件，以及这个目标文件或可执行文件依赖于哪些文件。下面是Makefile的一些基本概念和结构，帮助你更好地理解：

目标和依赖：Makefile的核心是描述目标文件和它们的依赖关系。目标可以是最终生成的可执行文件，也可以是中间生成的文件。

规则：每个目标都有一个规则，规则告诉Makefile如何生成目标文件。规则包括了命令，命令在目标需要更新时被执行。

变量：Makefile中可以使用变量来存储一些常用的值，如编译器选项、源文件列表等，这使得Makefile更灵活和易于维护。

隐式规则：Makefile提供了许多隐式规则，可以自动处理一些常见的构建过程，如C++源文件编译为对象文件。

自动变量：Makefile中有一些自动变量，如$@表示目标文件名，$<表示第一个依赖文件名等。

顺序：Makefile中的规则顺序是有意义的。当Makefile中有多个规则可以构建同一个目标时，Makefile会使用第一个找到的规则。

依赖关系：正确的描述依赖关系是Makefile编写的关键。如果一个目标文件依赖于多个源文件，只要其中一个源文件更新了，Makefile就会重新构建这个目标文件

# new的原理
ew 运算符用于动态分配内存，并调用对象的构造函数来初始化该内存
内存分配：new 首先会调用 operator new 函数来分配足够的内存空间，以存储指定类型的对象。
对象构造：在分配的内存上，new 会调用对象的构造函数来初始化这块内存。
返回指针：new 最终返回一个指向该对象的指针。
```c++
#include <iostream>
#include <cstdlib>

class MyClass {
public:
    MyClass() {
        std::cout << "MyClass constructed!" << std::endl;
    }

    ~MyClass() {
        std::cout << "MyClass destroyed!" << std::endl;
    }
};

void* operator new(size_t size) {
    std::cout << "Allocating " << size << " bytes" << std::endl;
    void* p = malloc(size);
    if (!p) {
        throw std::bad_alloc();
    }
    return p;
}

void operator delete(void* p) noexcept {
    std::cout << "Deallocating memory" << std::endl;
    free(p);
}

int main() {
    MyClass* obj = new MyClass(); // 使用 new 分配内存并构造对象
    delete obj; // 使用 delete 销毁对象并释放内存

    return 0;
}

```
# operator 重载运算符
operator 重载运算符是一种特殊的成员函数，它允许用户自定义操作符的行为。
下面是一些常见的运算符重载及其参数识别方式：

单目运算符重载（如前置/后置递增运算符 ++, --）：

前置递增/递减运算符：T& T::operator++() 或 T& T::operator--()。这类运算符重载函数不接受额外的参数，其操作数是调用该函数的对象本身。
后置递增/递减运算符：T T::operator++(int) 或 T T::operator--(int)。这里的int参数是用于区分后置递增/递减运算符和前置运算符的占位符，实际上并不使用这个参数的值。操作数依然是调用该函数的对象。
双目运算符重载（如加法运算符 +, 减法运算符 -）：

作为成员函数重载：T T::operator+(const T& other)。这里的other参数是右操作数，而左操作数是调用该函数的对象。
作为非成员函数重载：T operator+(const T& lhs, const T& rhs)。lhs（left-hand side）和rhs（right-hand side）分别是左操作数和右操作数。
赋值运算符重载：

T& T::operator=(const T& other)。other参数是要赋值的对象，而调用该函数的对象是赋值运算符的左操作数。
关系运算符重载（如等于 ==, 不等于 !=）：

bool T::operator==(const T& other)。other参数是右操作数，而左操作数是调用该函数的对象。
同样，也可以作为非成员函数重载：bool operator==(const T& lhs, const T& rhs)。
输入输出运算符重载（如 <<, >>）：

std::istream& operator>>(std::istream& is, T& obj)。is是输入流，obj是要从流中读取数据的对象。
std::ostream& operator<<(std::ostream& os, const T& obj)。os是输出流，obj是要输出到流中的对象。
函数调用运算符重载（()）：

T& T::operator()(Args... args)。这种重载允许对象像函数一样被调用，args...代表可以传递给对象的参数列表。
也可以重载为返回其他类型的函数调用运算符。