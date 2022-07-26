#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#ifndef BTREE_MAIN_H
#define BTREE_MAIN_H

struct btree_branch {


    int data;
    btree_branch *left;
    btree_branch *right;


    int max_depth() const {
        const int left_depth = left ? left->max_depth() : 0;
        const int right_depth = right ? right->max_depth() : 0;
        return (left_depth > right_depth ? left_depth : right_depth) + 1;
    }
};

class btree_nodes {
    btree_branch *root;

public:
    btree_nodes() {
        root = NULL;
    }

    int isempty() {
        return (root == NULL);
    }

    int get_max_depth() const {
        return root ? root->max_depth() : 0;
    }

    void clear() {
        delete root;
        root = nullptr;
    }

    void insert(int item);




    struct cell_display {
        string valstr;
        bool present;

        cell_display() : present(false) {}

        cell_display(string valstr) : valstr(valstr), present(true) {}
    };

    using display_rows = vector<vector<cell_display>>;

    display_rows get_row_display() const {
        vector<btree_branch *> traversal_stack;
        vector<vector<btree_branch *> > rows;
        if (!root) return display_rows();

        btree_branch *p = root;
        const int max_depth = root->max_depth();
        rows.resize(max_depth);
        int depth = 0;
        for (;;) {
            if (depth == max_depth - 1) {
                rows[depth].push_back(p);
                if (depth == 0) break;
                --depth;
                continue;
            }

            if (traversal_stack.size() == depth) {
                rows[depth].push_back(p);
                traversal_stack.push_back(p);
                if (p) p = p->left;
                ++depth;
                continue;
            }

            if (rows[depth + 1].size() % 2) {
                p = traversal_stack.back();
                if (p) p = p->right;
                ++depth;
                continue;
            }


            if (depth == 0) break;

            traversal_stack.pop_back();
            p = traversal_stack.back();
            --depth;
        }


        display_rows rows_disp;
        stringstream ss;
        for (const auto &row: rows) {
            rows_disp.emplace_back();
            for (btree_branch *pn: row) {
                if (pn) {
                    ss << pn->data;
                    rows_disp.back().push_back(cell_display(ss.str()));
                    ss = stringstream();
                } else {
                    rows_disp.back().push_back(cell_display());
                }
            }
        }
        return rows_disp;
    }

    vector<string> row_formatter(const display_rows &rows_disp) const;

    static void trim_rows_left(vector<string> &rows) {
        if (!rows.size()) return;
        auto min_space = rows.front().length();
        for (const auto &row: rows) {
            auto i = row.find_first_not_of(' ');
            if (i == string::npos) i = row.length();
            if (i == 0) return;
            if (i < min_space) min_space = i;
        }
        for (auto &row: rows) {
            row.erase(0, min_space);
        }
    }

    void Dump() const;


};


#endif //BTREE_MAIN_H
