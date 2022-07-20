#include "main.h"

int main() {

    tree_branch *tee = nullptr;
    int s[] = {5, 8, 4, 1, 2, 10, 20};

    int space = sizeof(s) / sizeof(s[0]);

    for (int i = 0; i < space; i++) {
        add_data(s[i], tee);
    }

    print(tee,space);
    free_tree(tee);
    /*balbla bla piskunov ochen krutoy pchel*/
    return 0;
}
