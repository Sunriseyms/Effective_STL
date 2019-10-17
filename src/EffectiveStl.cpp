//============================================================================
// Name        : EffectiveStl.cpp
// Author      : sunrise
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include "EffectiveStlRule.h"
#include "StlElementIsPoint.h"
#include "Knowledge_Surrounding/MethodObjectPointLearn.h"
using namespace std;

int main() {
    //StlElementIsPoint stlElementIsPoint;
    //stlElementIsPoint.ElementIsPointInVector();

    MethodObjectPointLearn methodObjectPointLearn;
    //methodObjectPointLearn.MethodPointLearn();
    //methodObjectPointLearn.RvlDemo();

    EffectiveStlRule effectiveStlRule;
    //effectiveStlRule.Rule5UseRangMethod();
    //effectiveStlRule.Rule6AlerVexingParse();
    effectiveStlRule.Rule7DeletePointersBeforeContainerDestoryed();
	return 0;
}
