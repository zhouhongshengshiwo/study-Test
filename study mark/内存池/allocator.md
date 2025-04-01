vector类的push_back函数的一种可能实现方式：
``` c++
template <class T>
void Vector<T>::push_back(const T& t)
{
// are we out of space?
	if (first_free == end)
		reallocate(); // gets more space and copies existing elements to it
	alloc.construct(first_free, t);
	++first_free;
}
```
first_free指向容器中第一个空闲的块，如果已经没有空闲块了，则通过reallocate函数重新分配。alloc是Alloctor<T>类的一个对象，调用其construct方法可在一个指定的区域构建对象，调用的是类型T的拷贝构造函数。在构造完成之后，让first_free指向下一个空闲块。

# C++模板类Vector的一个成员函数reallocate()的实现。
这个函数的主要功能是为Vector类重新分配内存空间，使其容量加倍
first_fress:指向当前已使用元素的末尾
elements:指向当前数组的起始位置
end:指向数组的末尾

``` c++
template <class T> void Vector<T>::reallocate() {
// compute size of current array and allocate space for twice as many elements
	std::ptrdiff_t size = first_free - elements;
	std::ptrdiff_t newcapacity = 2 * max(size, 1);//双倍内存分配
// allocate space to hold newcapacity number of elements of type T
	T* newelements = alloc.allocate(newcapacity);//新的内存空间分配
// construct copies of the existing elements in the new space
	uninitialized_copy(elements, first_free, newelements);//复制拷贝到新的内存
// destroy the old elements in reverse order
	for (T *p = first_free; p != elements; /* empty */ )//销毁原内存空间元素
		alloc.destroy(--p);//destroy方法会调用元素类型的析构函数来清理资源。
// deallocate cannot be called on a 0 pointer
	if (elements)
// return the memory that held the elements
		alloc.deallocate(elements, end - elements);//则使用分配器alloc的deallocate方法释放旧内存空间
        //注意，这里只进行内存回收，而不会进行对象的销毁
// make our data structure point to the new elements
	elements = newelements;
	first_free = elements + size;
	end = elements + newcapacity;
}
```
Alloctor<T>类的allocate成员函数的使用，它的作用是向系统申请指定个数的长度为sizeof(T)的连续空间，其底层实现是：

return operator new[](newcapacity * sizeof(T));