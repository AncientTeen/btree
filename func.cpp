#include "main.h"



void add_data(int d, tree_branch *&branch) {
    if (!branch) {
        branch = new tree_branch;
        branch->data = d;
        branch->left = 0;
        branch->right = 0;

    } else {
        if (branch->data > d) {
            add_data(d, branch->left);
        }
        if (branch->data < d) {
            add_data(d, branch->right);
        }
    }
}

void print(tree_branch *branch, int spc) {

    if (!branch)
        return;

    for (int i = 0 ; i < spc; i++) {
        cout << ' ';
    }
    cout << branch->data << endl;

    spc++;
    print(branch->right, spc);
    spc--;



    spc--;
    print(branch->left, spc);
    //spc++;

//    spc++;
//    print(branch->right, spc);

}


void free_tree(tree_branch *branch) {
    if (!branch)
        return;
    free_tree(branch->left);
    free_tree(branch->right);

    delete branch;

}