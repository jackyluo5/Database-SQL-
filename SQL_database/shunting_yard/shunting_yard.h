#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include <vector>
#include <string>
#include <iostream>
#include "../../!includes/Operator/operator.h"
#include "../../!includes/Operator_relational/relational_operator.h"
//#include <stack>
#include "../../../CS3A/!inludes/Stack/stack_iterator_Copy.h"
#include "../../../CS3A/!inludes/Queue/queue_iterator_Copy.h"
#include "../../../CS3A/!inludes/Vector/vector.h"

using namespace std;

class shunting_yard
{
public:
    shunting_yard();
    shunting_yard(vector<string> in);

    Vector<Operator> infixtopostfix(vector<string> infix);

private:
    vector<string> _in;

};

#endif // SHUNTING_YARD_H
