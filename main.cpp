#include "main.h"

int main() {

    btree_nodes bt;
    //8, 5, 2, 6, 10, 9, 11
    bt.insert(8);
    bt.insert(5);
    bt.insert(2);
    bt.insert(6);
    bt.insert(10);
    bt.insert(9);
    bt.insert(11);


    cout << "Tree from OP:\n\n";
    bt.Dump();
    cout << "\n\n";



    return 0;
}
