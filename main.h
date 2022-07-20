#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#ifndef BTREE_MAIN_H
#define BTREE_MAIN_H




struct tree_branch {
    int data;
    tree_branch *left;
    tree_branch *right;
};

void add_data(int d, tree_branch *&branch);

void print(tree_branch *branch, int spc);

void free_tree(tree_branch *branch);



#endif BTREE_MAIN_H
