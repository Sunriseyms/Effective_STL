/**
 * @file StlElementIsPoint.cpp
 * Copyright (c) Huawei Technologies Co., Ltd. 2012-2018. All rights reserved.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#include "StlElementIsPoint.h"
#include <string>
#include <vector>
#include <iostream>

StlElementIsPoint::StlElementIsPoint()
{
    // TODO Auto-generated constructor stub

}

StlElementIsPoint::~StlElementIsPoint()
{
    // TODO Auto-generated destructor stub
}

class Application{
public:
    Application(std::string name):name(name){

    }
    std::string name;
};

// 将vector v1的元素的指针存储到另外一个vector v2中
void StlElementIsPoint::ElementIsPointInVector()
{
    std::vector<Application*> allApplicationPoint;
    std::vector<Application> allApplicationObject;
    Application app1("app1");
    Application app2("app2");
    Application app3("app3");
    allApplicationObject.push_back(app1);
    allApplicationObject.push_back(app2);
    allApplicationObject.push_back(app3);

    /* 此方法中allApplicationPoint存储的始终是app对象的地址(只有一个)；所以元素都相同，指向同一个对象。；
    for(Application app : allApplicationObject) {
        std::cout << "1app name" << app.name << std::endl;
        std::cout << "1app point" << &app << std::endl;
        allApplicationPoint.push_back(&app);
    }
    */

    // 将allApplicationObject每个元素的指针存储到allApplicationPoint，没有经过中间元素的中转。
    for(std::vector<Application>::iterator it = allApplicationObject.begin(); it != allApplicationObject.end(); ++it) {
        allApplicationPoint.push_back(&*it);
    }

    for(Application* app : allApplicationPoint) {
        std::cout << "2app name" << app->name << std::endl;
    }
}

