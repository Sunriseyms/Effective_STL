/**
 * @file EffectiveStlRule.cpp
 * Copyright (c) Huawei Technologies Co., Ltd. 2012-2018. All rights reserved.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#include "EffectiveStlRule.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <iterator>
#include <vector>
#include <list>


using namespace std;

class Widget {
public:
    string name;
    Widget(){
        cout << "this is Widget construct." << endl;
    }
    ~Widget(){
        cout << "this is Widget destruct." << endl;
    }

    Widget(const Widget& w){
        cout << "this is Widget copy construct." << endl;
    }
};

// 一元函数对象 使用该函数对象是，需要指定模版类型。
template<typename T>
struct DeleteObject : public unary_function<const T*, void>{
    void operator()(const T* ptr) const
    {
        delete ptr;
    }
};

// 函数对象，将模版类型下沉到operator方法上。
struct DeleteObject1 {
    template<typename T>
    void operator()(const T* ptr) const
    {
        delete ptr;
    }
};

/*
void doSomething()
{
    vector<int> v;
    cout << "v.capacity0:" << v.capacity() << endl;
    vector<Widget> vwp2;
    cout << "vwp2.capacity0:" << vwp2.capacity() << endl;
    vwp2.reserve(2);
    cout << "vwp2.capacity1:" << vwp2.capacity() << endl;
    for(int i=0; i < 3; ++i){
        Widget* w = new Widget();
        cout << "w2 address: " << w << endl;
        vwp2.push_back(*w);
    }
    cout << "doSomething end." << endl;
} // 内存泄露
*/


void doSomething()
{
    typedef std::shared_ptr<Widget> SPW;
    // new 在C++中返回的是指针，在java中返回的是引用
    vector<Widget*> vwp;
    //vector<SPW> vwp;
    for(int i=0; i < 3; ++i){
        vwp.push_back(new Widget);
        //vwp.push_back(SPW(new Widget));
    }

    // 添加此处的删除指针动作后，Widget不会被泄露。但在new和delete之间，若产生异常，还是导致内存泄露。此时推荐使用智能指针(79、82行代码)。
    //std::for_each(vwp.begin(), vwp.end(), DeleteObject<Widget>());
    std::for_each(vwp.begin(), vwp.end(), DeleteObject1());
}


// 尽量使用区间成员函数替代它们的单元素兄弟
void EffectiveStlRule::Rule5UseRangMethod()
{
    vector<int> v1{1,2,3};
    vector<int> v2{4,5,6,7};

    // 区间构造
    vector<int> v3(v1.begin(), v1.begin()+2);
    cout << "v3: ";
    for(const int elem : v3) {
        cout << elem << " ";
    }
    cout << endl;

    // 区间插入
    v1.insert(v1.end(), v2.begin(), v2.end());
    cout << "v1(insert v2 to v1 end): ";
    for(const int elem : v1) {
        cout << elem << " ";
    }
    cout << endl;

    // 区间删除
    v1.erase(v1.begin(), v1.begin()+2);
    cout << "v1(erase begin to begin+2): ";
    for(const int elem : v1) {
        cout << elem << " ";
    }
    cout << endl;

    // 区间赋值
    v1.assign(v3.begin(), v3.end());
    cout << "v1(v1.assign(v3.begin(), v3.end())): ";
    for(const int elem : v1) {
        cout << elem << " ";
    }
    cout << endl;

}

// 警惕C++最令人恼怒的解析
void EffectiveStlRule::Rule6AlerVexingParse()
{
    // int f(double d);     声明一个函数f,带有一个double而且返回一个int
    // int f(double (d));   同样的事情，名为d的参数左右的括号是多余的，被忽略
    // int f(double);       同样的事情，省略了参数名

    // int g(double (*pf)); 声明一个函数g,带有一个参数，参数指向一个没有参数、返回double的函数指针
    // int g(double pf());  同样的事情，唯一不同的是pf使用非指针语法来声明，pf其实是一个指针
    // int g(double());     同样的事情，参数名省略

    // 参数名左右的括号（就像f的第二种声明中的d）和单独的括号（g的声明）之间的区别。参数名左右的括号被忽略，但
    // 单独的括号指出存在一个参数列表：它们声明了存在指向函数指针的参数。

    // 例子:
    // 假设你有一个int的文件，你想要把那些int拷贝到一个list中。这看起来像是一个合理的方式：
    // ifstream dataFile("ints.dat");
    // list<int> data(istream_iterator<int>(dataFile), istream_iterator<int>()); // 警告！这完成的并不是像你想象的那样

    // 解析：第一个参数较dataFile，它的类型是isteam_iterator<int>, dataFile左右的括号是多余的被忽略,
    //     所以上述的dataFile是个参数名，不会拿ifstream的dataFile进行初始化。
    //     第二个参数没有名字，它的类型是指向一个没有参数而且返回istream_iterator<int>的函数指针。
    // 这符合C++里的一条通用规则——几乎任何东西都可能被分析成函数声明.

    // 正确的写法
    ifstream dataFile("D:/eclipse-c++-workspace/EffectiveStl/ints.dat");
    istream_iterator<int> dataBegin(dataFile);
    istream_iterator<int> dataEnd;
    list<int> data(dataBegin, dataEnd);
    int i = 0;
    for(int a : data){
        std::cout << "list[" << i << "]" << a << std::endl;
        i++;
    }
}

// 当使用new的指针的容器时，记得在销毁容器前delete那些指针
void EffectiveStlRule::Rule7DeletePointersBeforeContainerDestoryed()
{
    // 当容器自己被销毁时会自动销毁容纳的每个对象；但当一个指针的容器被销毁时，会销毁它包含的每个元素，但指针的“析构函数”是无操作，它肯定不会调用delete。
    doSomething();

    // 添加此处的删除指针动作后，Widget不会被泄露。但在new和delete之间，若产生异常，还是导致内存泄露。此时推荐使用智能指针(79、82行代码)。

}

void EffectiveStlRule::Rule8NerverCreateContainerOfAutoptrs()
{
    // 当拷贝一个auto_ptr时，auto_ptr所指向对象的所有权被转移到拷贝的auto_ptr，而被拷贝的auto_ptr被设为NULL；
    // 拷贝一个auto_ptr将改变它的值

}
