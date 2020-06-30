#include "Box.h"

Box::Box(int dim) {
    value = 0;
    for (int i = 1; i <= dim; i++) choices.insert(i);
}

Box::Box(int dim, int val) {
    value = val;
    choices.insert(val);
}

Box::getValue() {
    return value;
}