#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::string;

/* 
string��������ǹ����ַ���˳���  ---> basic_string<char> (�൱������ģ��ʵ������һ���������)
	�ص�: 
		1. ��'\0'����
		2. +=���� (�ַ�������ƴ��) �ַ�����������ص� ���԰�stringר���ó�����Ϊһ�������ַ���
	��ҳ(��ʵ�����ַ���)
vector: ����������ݵ�˳��� ---> ��ģ��  (������һ���������) û��+=/+������
vector<char> ---> ���ǹ����ַ�����˳���
�ṩʲô���� ������ʲô˳���

vector�ӿ�:
	�����߼�:
		1. �����ʼΪ��, ������Ϊ0
		2. PJ�����ݴ�Լ��1.5��, SGI�����ݴ�Լ��2��
	������ʧЧ: ������ָ���λ���Ѿ��ͷŻ���Խ��
		ֻҪ�ռ䷢���˱绤a,������һ����ʧЧ(insert ,push_back,reserve,resize,assign,emplace_back)
		erase���ܻᵼ�µ�����Խ�����, �ʴ˽ӿ�Ҳ�ᵼ�µ�����ʧЧ

��α��������ʧЧ?????????????????
	��������˿ռ�仯, ���»�ȡ������, �����ɾ������, ��ȡɾ�������ķ���ֵ

	find: ����vector�ĳ�Ա����, ����alogrithm��ĺ���ģ��
		�����ŵ������������Զ�������, ����Ҫ����==�����(�е�)
		����Ҳ���Ԫ��, �򷵻ش���������Ľ���λ��

*/

class A{
public:
	A(int a = 100)
		:_a(a){}
private:
	int _a;
};

void test4(){

	// ����
	vector<int> vec; // û������

	vector<char> vec2(10, 'c');  // 10��'c'

	vector<char> vec3(10); // 10��'0'

	vector<A> vec4(10);

	A a(-1);
	vector<A> vec5(10, a);

	//��������ʼ��
	vector<char> vec6(vec2.begin(), vec2.end());

	char str[] = "123456789";
	//��������ʼ��
	vector<char> vec7(str, str + sizeof(str) / sizeof(str[0]));

	//��������
	vector<char> copy(vec7);
}

void test5(){
	char str[] = "123456789";
	vector<char> vec(str, str + sizeof(str) / sizeof(str[0]));
	//vector<char>����������
	vector<char>::iterator it = vec.begin();
	//��const�������� �ɶ���д
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
		//const�����������޸�����
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

	//��Χfor: �ɶ���д
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
	//operator[]���ɶ���д
	for (int i = 0; i < vec.size(); ++i){
		cout << vec[i] << " ";
		vec[i] = 'd';
	}
	cout << endl;
}

void test6(){
	vector<int> v;
	//PJ��vector�����߼��� �����1.5���� ���vector��ʼ��Ϊ�գ���ʼ����Ϊ0
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
	//insert: λ�ò���Ϊ����������������ֵ
	v.insert(v.begin(), 100);  // 10 ....
	v.insert(v.end(), 200);   // ..... 200
	v.insert(v.begin() + 5, 300);  // .... 300, 6.....

	v.insert(v.begin(), 5, 99); // 99 99 99 99 99 10 .....

	v.insert(v.end(), arr + 3, arr + 5); //  .....  4, 5
	//λ��Խ�磬endλ��û��Ԫ��
	//v.erase(v.end());
	v.erase(v.end() - 1);
	v.erase(v.begin());
	//ɾ������Ϊ����ҿ�
	v.erase(v.begin(), v.end());
}
void test9(){
	//������ʧЧ��������ָ���λ�ò��ɷ���/�Ƿ����ʣ�λ���ͷţ�����Խ��)
	// insert, push_back , resize, reserve, assign���е�����ʧЧ������
	vector<int> v;
	v.reserve(100);

	v.push_back(1);
	vector<int>::iterator it = v.begin();

	//push_back: �������ݣ�����ʱ������ԭ���ĵ�����ʧЧ
	/*v.push_back(1);
	vector<int>::iterator it = v.begin();
	cout << *it << endl;
	v.push_back(2);
	cout << *it << endl;
	v.push_back(3);
	cout << *it << endl;*/

	//resize: �޸�Ԫ�ظ���������ʱ������ԭ���ĵ�����ʧЧ
	/*cout << *it << endl;
	v.resize(10);
	cout << *it << endl;*/

	//resize: ����ʱ������ԭ���ĵ�����ʧЧ
	/*v.reserve(5);
	cout << *it << endl;*/

	//assign:����ʱ������ԭ���ĵ�����ʧЧ
	/*v.assign(3, 5);
	cout << *it << endl;*/

	//insert:����ʱ������ԭ���ĵ�����ʧЧ
	v.insert(it, 10);
	it = v.begin();
	cout << *it << endl;
	//�ܽ᣺ֻҪ�ӿڵ��¿ռ䷢���˱仯���ͻ����������ʧЧ

	//ɾ���ᵼ�µ�������ָ���λ���п��ܵ���Խ�����
	/*it = v.end() - 1;
	v.erase(it);
	cout << *it << endl;
	*/
	//���������ʧЧ�����»�ȡ������
	//erase�ӿڷ���ֵ�� ������--->ָ��ɾ��Ԫ�ص���һ��Ԫ�ص�λ��
	it = v.erase(it);
	cout << *it << endl;

	//string�ĵ�����Ҳ����ʧЧ������
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
	//����ʼλ�ò���һ��B���� ��Ա������ֵΪ10��20
	v.insert(v.begin(), B(10, 20));

	//����ʼλ�ò���һ��B���� ��Ա������ֵΪ30�� 40
	//emplace: ����������insert, ����Ҳ֧�ֹ������Ȼ����в���Ĳ���
	v.emplace(v.begin(), 30, 40);
	v.emplace(v.begin(), B(50, 60));

	//emplace_back:����������push_back,����Ҳ֧�ֹ������Ȼ����в���Ĳ���
	v.emplace_back(70, 80);
	v.push_back(B(90, 100));

	vector<B>::iterator it2 = v.end();
	//find�� ����ҵ�������Ԫ�صĶ�Ӧλ�ã�����Ҳ�����������������Ľ���λ��
	//������Զ������ͣ���Ҫ�Զ�������֧��==�����������֧�֣���Ҫ����==���������
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
