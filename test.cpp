#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;

/* 
string这个容器是管理字符的顺序表  ---> basic_string<char> (相当于是类模板实例化的一个具体的类)
	特点: 
		1. 以'\0'结束
		2. +=操作 (字符串可以拼接) 字符串由特殊的特点 所以把string专门拿出来作为一个管理字符的
	网页(其实就是字符串)
vector: 管理各种数据的顺序表 ---> 类模板  (不代表一个具体的类) 没有+=/+法操作
vector<char> ---> 就是管理字符串的顺序表
提供什么类型 就生成什么顺序表

vector接口:
	增容逻辑:
		1. 如果初始为空, 则容量为0
		2. PJ版增容大约是1.5倍, SGI版增容大约是2倍
	迭代器失效: 迭代器指向的位置已经释放或者越界
		只要空间发生了辩护a,迭代器一定会失效(insert ,push_back,reserve,resize,assign,emplace_back)
		erase可能会导致迭代器越界访问, 故此接口也会导致迭代器失效

如何避免迭代器失效?????????????????
	如果发生了空间变化, 重新获取迭代器, 如果是删除操作, 获取删除操作的返回值

	find: 不是vector的成员函数, 属于alogrithm库的函数模板
		如果存放的数据类型是自定义类型, 则需要重载==运算符(判等)
		如果找不到元素, 则返回待查找区间的结束位置

*/

class A{
public:
	A(int a = 100)
		:_a(a){}
private:
	int _a;
};

void test4(){

	// 构造
	vector<int> vec; // 没有数据

	vector<char> vec2(10, 'c');  // 10个'c'

	vector<char> vec3(10); // 10个'0'

	vector<A> vec4(10);

	A a(-1);
	vector<A> vec5(10, a);

	//迭代器初始化
	vector<char> vec6(vec2.begin(), vec2.end());

	char str[] = "123456789";
	//迭代器初始化
	vector<char> vec7(str, str + sizeof(str) / sizeof(str[0]));

	//拷贝构造
	vector<char> copy(vec7);
}

void test5(){
	char str[] = "123456789";
	vector<char> vec(str, str + sizeof(str) / sizeof(str[0]));
	//vector<char>迭代器遍历
	vector<char>::iterator it = vec.begin();
	//非const迭代器： 可读可写
	while (it != vec.end()){
		cout << *it << " ";
		*it = 'a';
		++it;
	}
	cout << endl;

	vector<char>::reverse_iterator rit = vec.rbegin();
	while (rit != vec.rend()){
		cout << *rit << " ";
		*rit = 'b';
		++rit;
	}
	cout << endl;

	vector<char>::const_iterator cit = vec.cbegin();
	while (cit != vec.cend()){
		cout << *cit << " ";
		//const迭代器不能修改内容
		//*cit = 'c';
		++cit;
	}
	cout << endl;
	vector<char>::const_reverse_iterator crit = vec.crbegin();
	while (crit != vec.crend()){
		cout << *crit << " ";
		++crit;
	}
	cout << endl;

	//范围for: 可读可写
	for (char& ch : vec){
		cout << ch << " ";
		ch = 'c';
	}
	cout << endl;
	for (const char& ch : vec){
		cout << ch << " ";
		//ch = 'c';
	}
	cout << endl;
	//operator[]：可读可写
	for (int i = 0; i < vec.size(); ++i){
		cout << vec[i] << " ";
		vec[i] = 'd';
	}
	cout << endl;
}

void test6(){
	vector<int> v;
	//PJ版vector增容逻辑： 大概是1.5倍， 如果vector初始化为空，初始容量为0
	size_t cap = v.capacity();
	cout << cap << endl;
	for (int i = 0; i < 200; ++i){
		v.push_back(i);
		if (cap != v.capacity()){
			cap = v.capacity();
			cout << cap << endl;
		}
	}
}

void test7(){
	vector<int> v;
	v.assign(10, 9);
	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	v.assign(arr, arr + 10);
	v.assign(arr + 2, arr + 7);
}

void test8(){
	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	vector<int> v(arr, arr + 10);
	//insert: 位置参数为迭代器，不是整形值
	v.insert(v.begin(), 100);  // 10 ....
	v.insert(v.end(), 200);   // ..... 200
	v.insert(v.begin() + 5, 300);  // .... 300, 6.....

	v.insert(v.begin(), 5, 99); // 99 99 99 99 99 10 .....

	v.insert(v.end(), arr + 3, arr + 5); //  .....  4, 5
	//位置越界，end位置没有元素
	//v.erase(v.end());
	v.erase(v.end() - 1);
	v.erase(v.begin());
	//删除区间为左闭右开
	v.erase(v.begin(), v.end());
}
void test9(){
	//迭代器失效：迭代器指向的位置不可访问/非法访问（位置释放，或者越界)
	// insert, push_back , resize, reserve, assign都有迭代器失效的问题
	vector<int> v;
	v.reserve(100);

	v.push_back(1);
	vector<int>::iterator it = v.begin();

	//push_back: 插入数据，增容时，导致原来的迭代器失效
	/*v.push_back(1);
	vector<int>::iterator it = v.begin();
	cout << *it << endl;
	v.push_back(2);
	cout << *it << endl;
	v.push_back(3);
	cout << *it << endl;*/

	//resize: 修改元素个数，增容时，导致原来的迭代器失效
	/*cout << *it << endl;
	v.resize(10);
	cout << *it << endl;*/

	//resize: 增容时，导致原来的迭代器失效
	/*v.reserve(5);
	cout << *it << endl;*/

	//assign:增容时，导致原来的迭代器失效
	/*v.assign(3, 5);
	cout << *it << endl;*/

	//insert:增容时，导致原来的迭代器失效
	v.insert(it, 10);
	it = v.begin();
	cout << *it << endl;
	//总结：只要接口导致空间发生了变化，就会引起迭代器失效

	//删除会导致迭代器的指向错位，有可能导致越界访问
	/*it = v.end() - 1;
	v.erase(it);
	cout << *it << endl;
	*/
	//解决迭代器失效：重新获取迭代器
	//erase接口返回值： 迭代器--->指向被删除元素的下一个元素的位置
	it = v.erase(it);
	cout << *it << endl;

	//string的迭代器也存在失效的问题
	string str("1");
	string::iterator sit = str.begin();
	cout << *sit << endl;
	str.resize(30, 'a');
	cout << *sit << endl;
}

class B{
public:
	B(int a = 1, int b = 2)
		:_a(a)
		, _b(b){}

	bool operator==(const B& b){
		return _a == b._a
			&& _b == b._b;
	}

private:
	int _a;
	int _b;
};

void test10(){
	vector<B> v;
	//在起始位置插入一个B对象， 成员变量的值为10，20
	v.insert(v.begin(), B(10, 20));

	//在起始位置插入一个B对象， 成员变量的值为30， 40
	//emplace: 功能类似于insert, 但是也支持构造对象，然后进行插入的操作
	v.emplace(v.begin(), 30, 40);
	v.emplace(v.begin(), B(50, 60));

	//emplace_back:功能类似于push_back,但是也支持构造对象，然后进行插入的操作
	v.emplace_back(70, 80);
	v.push_back(B(90, 100));

	vector<B>::iterator it2 = v.end();
	//find： 如果找到，返回元素的对应位置，如果找不到，返回搜索区间的结束位置
	//如果是自定义类型，需要自定义类型支持==操作，如果不支持，需要进行==运算符重载
	vector<B>::iterator it = find(v.begin(), v.end() - 2, B(90, 80));
}
int main(){
	//test4();
	//test5();
	//test6();
	//test7();
	//test8();
	//test9();
	test10();
	return 0;
}
