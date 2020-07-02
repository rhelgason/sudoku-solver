#include "Box.h"

Box::Box(int dim) {
    value = 0;
    for (int i = 1; i <= dim; i++) choices.insert(i);
}

Box::Box(int dim, int val) {
    value = val;
    choices.insert(val);
}

int Box::getValue() {
    return value;
}

void Box::setValue(int val) {
    value = val;
}

set<int> Box::getChoices() {
    return choices;
}