/**
 * @file MethodObjectPointLearn.cpp
 * Copyright (c) Huawei Technologies Co., Ltd. 2012-2018. All rights reserved.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#include "MethodObjectPointLearn.h"
#include <string>
#include <vector>
#include <iostream>

class ResourceDemo {
public:
    ResourceDemo(){
        std::cout << "构造函数" << std::endl;
    }

    ResourceDemo(const ResourceDemo& r ){
        std::cout << "复制构造函数" << std::endl;
    }

    ResourceDemo& operator=(const ResourceDemo& r) {
        std::cout << "赋值构造函数" << std::endl;
        return *this;
    }

    ResourceDemo(ResourceDemo&& b) noexcept{
        std::cout << "移动构造函数" << std::endl;
    }

    ~ResourceDemo() {
        std::cout << "析构构造函数" << std::endl;
    }

};

MethodObjectPointLearn::MethodObjectPointLearn()
{
    // TODO Auto-generated constructor stub

}

MethodObjectPointLearn::~MethodObjectPointLearn()
{
    // TODO Auto-generated destructor stub
}


bool lengthCompare(const std::string& str1, const std::string& str2)
{
    return str1.size() == str2.size();
}

void MethodObjectPointLearn::MethodPointLearn()
{
    // 函数指针指向的函数而非对象。和其他指针一样，函数指针指向某种特定类型。函数的类型由它的返回类型和形参类型共同决定，与函数名无关。
    /*
    // 比较两个string对象的长度
    bool lengthCompare(const string &, const string &);
            该函数的类型是bool(const string&, const string&). 要想声明一个可以指向该函数的指针，只需要用指针替换函数名即可。

    // pf 指向一个函数，该函数的参数是两个const string的引用，返回值是bool类型
    bool (*pf)(const string&, const string&);   // 未初始化

            思想：从声明的名字开始观察，pf前面有个*，因此pf是指针，右侧是形参列表，表示pf指向的是函数，再观察左侧，发现函数的返回类型是布尔值；
                        因此，pf就是一个指向函数的指针，其中该函数的参数是两个const string的引用，返回值是bool类型。

    *pf 两端的括号必不可少，如果不写这对括号，则pf是一个返回值为bool指针的函数。
    */

    bool (*pf)(const std::string&, const std::string&) = lengthCompare;  //当我们把函数名作为一个值使用时，该函数自动转换成指针;其他对象不会
    //bool (*pf)(const std::string&, const std::string&) = &lengthCompare; //等价

    bool b1 = pf("hello", "goodbye");
    bool b2 = (*pf)("hello", "goodbye");
    bool b3 = lengthCompare("hello", "goodbye");
    std::cout << "b1(pf(\"hello\", \"goodbye\")): " << b1 << std::endl;
    std::cout << "b2((*pf)(\"hello\", \"goodbye\")): " << b2 << std::endl;
    std::cout << "b3(lengthCompare(\"hello\", \"goodbye\")): " << b3 << std::endl;

}


void MethodObjectPointLearn::RvlDemo()
{
    std::vector<ResourceDemo> v;
    v.push_back(ResourceDemo());
    std::cout << "--------" << std::endl;
    v.push_back(ResourceDemo());
}
