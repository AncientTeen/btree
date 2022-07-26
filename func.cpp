#include "main.h"


/// btree_nodes class functions
void btree_nodes::insert(int item) {
    btree_branch *p = new btree_branch;
    btree_branch *parent;
    p->data = item;
    p->left = NULL;
    p->right = NULL;
    parent = NULL;
    if (isempty())
        root = p;
    else {
        btree_branch *ptr;
        ptr = root;
        while (ptr != NULL) {
            parent = ptr;
            if (item > ptr->data)
                ptr = ptr->right;
            else
                ptr = ptr->left;
        }
        if (item < parent->data)
            parent->left = p;
        else
            parent->right = p;
    }
}


vector<string> btree_nodes::row_formatter(const display_rows &rows_disp) const {
    using s_t = string::size_type;

    s_t cell_width = 0;
    for (const auto &row_disp: rows_disp) {
        for (const auto &cd: row_disp) {
            if (cd.present && cd.valstr.length() > cell_width) {
                cell_width = cd.valstr.length();
            }
        }
    }

    if (cell_width % 2 == 0) ++cell_width;


    if (cell_width < 3) cell_width = 3;


    vector<string> formatted_rows;


    s_t row_count = rows_disp.size();

    s_t row_elem_count = 1 << (row_count - 1);

    s_t left_pad = 0;


    for (s_t r = 0; r < row_count; ++r) {
        const auto &cd_row = rows_disp[row_count - r - 1];

        s_t space = (s_t(1) << r) * (cell_width + 1) / 2 - 1;

        string row;

        for (s_t c = 0; c < row_elem_count; ++c) {

            row += string(c ? left_pad * 2 + 1 : left_pad, ' ');
            if (cd_row[c].present) {

                const string &valstr = cd_row[c].valstr;

                s_t long_padding = cell_width - valstr.length();
                s_t short_padding = long_padding / 2;
                long_padding -= short_padding;
                row += string(c % 2 ? short_padding : long_padding, ' ');
                row += valstr;
                row += string(c % 2 ? long_padding : short_padding, ' ');
            } else {

                row += string(cell_width, ' ');
            }
        }

        formatted_rows.push_back(row);

        if (row_elem_count == 1) break;


        s_t left_space = space + 1;
        s_t right_space = space - 1;
        for (s_t sr = 0; sr < space; ++sr) {
            string row;
            for (s_t c = 0; c < row_elem_count; ++c) {
                if (c % 2 == 0) {
                    row += string(c ? left_space * 2 + 1 : left_space, ' ');
                    row += cd_row[c].present ? '/' : ' ';
                    row += string(right_space + 1, ' ');
                } else {
                    row += string(right_space, ' ');
                    row += cd_row[c].present ? '\\' : ' ';
                }
            }
            formatted_rows.push_back(row);
            ++left_space;
            --right_space;
        }
        left_pad += space + 1;
        row_elem_count /= 2;
    }

    reverse(formatted_rows.begin(), formatted_rows.end());

    return formatted_rows;
}


void btree_nodes::Dump() const {
    const int d = get_max_depth();

    if (d == 0) {
        cout << " <empty tree>\n";
        return;
    }


    const auto rows_disp = get_row_display();

    auto formatted_rows = row_formatter(rows_disp);

    trim_rows_left(formatted_rows);

    for (const auto &row: formatted_rows) {
        cout << ' ' << row << '\n';
    }
}