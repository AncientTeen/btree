#include "main.h"

int main() {

    btree_nodes bt;

    random_device rd;
    mt19937 rng(rd());

    int MaxCount = 20;
    int MaxDepth = 20;
    const int Min = 1, Max = 1000;

    uniform_int_distribution<int> dist(Min, Max);

    while (MaxCount--) {
        bt.insert(dist(rng));
        if (bt.get_max_depth() >= MaxDepth) break;
    }

    cout << "Randomly generated tree:\n\n";
    bt.Dump();


    return 0;
}
