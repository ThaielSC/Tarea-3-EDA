#pragma once

#include "ADT/list.hpp"
#include "ADT/tree.hpp"

class TreeBuilder {
public:
    TreeBuilder() = default;
    Tree* buildTree(const LinkedList* postfix_list);
};
