#include "main.h"


/// old version

//void add_data(int d, btree_branch *&branch) {
//    if (!branch) {
//        branch = new btree_branch;
//        branch->data = d;
//        branch->left = 0;
//        branch->right = 0;
//
//    } else {
//        if (branch->data > d) {
//            add_data(d, branch->left);
//        }
//        if (branch->data < d) {
//            add_data(d, branch->right);
//        }
//    }
//}



/// new functions
//
//void add_data(vector<int> &vecdata, btree_branch *&branch) {
//    if (!branch)
//        branch = new btree_branch;
//
//    sort(vecdata.begin(), vecdata.end());
//
//    double mid = ceil(vecdata.size() / 2);
//
//    branch->data = vecdata[mid];
//
//
//
//    smaller_branches(vecdata, mid, branch->left);
//
//    bigger_branches(vecdata, mid, branch->right);
//
//
//
//
//}
//
//int smaller_branches(vector<int> &vecdata, double mid , btree_branch *&branch) {
//
//    if (!branch)
//        branch = new btree_branch;
//
//    //sort(vecdata.begin(), vecdata.end());
//    if (vecdata.size() == 1)
//        //branch->left->data = vecdata[0];
//        return 0;
//
//    vector<int> smllv;
//
//    for (int j = 0; j < mid; j++) {
//
//        //vector<int> smllv;
//        smllv.push_back(vecdata[j]);
//
//        // if (smllv.size() == 1)
//        // 	branch->left.data = smllv[0];
//
//
//        // double mid = ceil(smllv.size() / 2);
//
//        // branch->left.data = smllv[mid];
//    }
//
////    if (smllv.size() == 1)
////        branch->left->data = smllv[0];
////    return 0;
//
//    double sml_mid = ceil(smllv.size() / 2);
//
//    branch->data = smllv[sml_mid];
//
//    smaller_branches(smllv, sml_mid, branch->left);
//
//
//}
//
//int bigger_branches(vector<int> &vecdata, double mid, btree_branch *&branch) {
//    if (!branch)
//        branch = new btree_branch;
//
//    //sort(vecdata.begin(), vecdata.end());
//    if (vecdata.size() == 1)
//        //branch->right->data = vecdata[0];
//    return 0;
//
//    vector<int> bggr;
//
//    for (int j = mid; j < vecdata.size(); j++) {
//
//        //vector<int> smllv;
//        bggr.push_back(vecdata[j]);
//
//        // if (smllv.size() == 1)
//        // 	branch->left.data = smllv[0];
//
//
//        // double mid = ceil(smllv.size() / 2);
//
//        // branch->left.data = smllv[mid];
//    }
//
//
//
//    double bgr_mid = ceil(bggr.size() / 2);
//    branch->data = bggr[bgr_mid];
//
//    bigger_branches(bggr, bgr_mid, branch->right);
//}
//
//
//void print(btree_branch *branch, int spc) {
//
//    if (!branch)
//        return;
////    while(branch->data != NULL) {
////        for (int i = 0 ; i < spc; i++) {
////            cout << ' ';
////        }
////
////        cout << branch->data << endl;
////
////    }
//    for (int i = 0 ; i < spc; i++) {
//            cout << ' ';
//       }
//    cout << branch->data << endl;
////
////    spc--;
////    for (int i = 0 ; i < spc; i++) {
////        cout << ' ';
////    }
////    cout << '/' << endl;
////
////    for (int i = 0 ; i < spc - 1 ; i++) {
////        cout << ' ';
////    }
////    cout << branch->left->data;
////
////
//    spc++;
//    for (int i = 0 ; i < spc; i++) {
//        cout << ' ';
//    }
//    cout << '\\' << endl;
//    print(branch->right, spc);
//    spc--;
//
//
//
//    spc--;
//    for (int i = 0 ; i < spc; i++) {
//        cout << ' ';
//    }
//    cout << '/' << endl;
//    print(branch->left, spc);
//    //spc++;
//
////    spc++;
////    print(branch->right, spc);
//
//}
//
//
//void free_tree(btree_branch *branch) {
//    if (!branch)
//        return;
//    free_tree(branch->left);
//    free_tree(branch->right);
//
//    delete branch;
//
//}

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

//void btree_nodes::displayBinTree(){
//    printBinTree(root);
//}
//void btree_nodes::printBinTree(btree_branch *ptr){
//    if(ptr!=NULL){
//        printBinTree(ptr->left);
//        cout << "  " << ptr->data << "     ";
//        printBinTree(ptr->right);
//    }
//}

/// new funcs

vector<string> btree_nodes::row_formatter(const display_rows &rows_disp) const {
    using s_t = string::size_type;

    // First find the maximum value string length and put it in cell_width
    s_t cell_width = 0;
    for (const auto &row_disp: rows_disp) {
        for (const auto &cd: row_disp) {
            if (cd.present && cd.valstr.length() > cell_width) {
                cell_width = cd.valstr.length();
            }
        }
    }

    // make sure the cell_width is an odd number
    if (cell_width % 2 == 0) ++cell_width;

    // allows leaf nodes to be connected when they are
    // all with size of a single character
    if (cell_width < 3) cell_width = 3;


    // formatted_rows will hold the results
    vector<string> formatted_rows;

    // some of these counting variables are related,
    // so its should be possible to eliminate some of them.
    s_t row_count = rows_disp.size();

    // this row's element count, a power of two
    s_t row_elem_count = 1 << (row_count - 1);

    // left_pad holds the number of space charactes at the beginning of the bottom row
    s_t left_pad = 0;

    // Work from the level of maximum depth, up to the root
    // ("formatted_rows" will need to be reversed when done)
    for (s_t r = 0; r < row_count; ++r) {
        const auto &cd_row = rows_disp[row_count - r - 1]; // r reverse-indexes the row
        // "space" will be the number of rows of slashes needed to get
        // from this row to the next.  It is also used to determine other
        // text offsets.
        s_t space = (s_t(1) << r) * (cell_width + 1) / 2 - 1;
        // "row" holds the line of text currently being assembled
        string row;
        // iterate over each element in this row
        for (s_t c = 0; c < row_elem_count; ++c) {
            // add padding, more when this is not the leftmost element
            row += string(c ? left_pad * 2 + 1 : left_pad, ' ');
            if (cd_row[c].present) {
                // This position corresponds to an existing Node
                const string &valstr = cd_row[c].valstr;
                // Try to pad the left and right sides of the value string
                // with the same number of spaces.  If padding requires an
                // odd number of spaces, right-sided children get the longer
                // padding on the right side, while left-sided children
                // get it on the left side.
                s_t long_padding = cell_width - valstr.length();
                s_t short_padding = long_padding / 2;
                long_padding -= short_padding;
                row += string(c % 2 ? short_padding : long_padding, ' ');
                row += valstr;
                row += string(c % 2 ? long_padding : short_padding, ' ');
            } else {
                // This position is empty, Nodeless...
                row += string(cell_width, ' ');
            }
        }
        // A row of spaced-apart value strings is ready, add it to the result vector
        formatted_rows.push_back(row);

        // The root has been added, so this loop is finsished
        if (row_elem_count == 1) break;

        // Add rows of forward- and back- slash characters, spaced apart
        // to "connect" two rows' Node value strings.
        // The "space" variable counts the number of rows needed here.
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

    // Reverse the result, placing the root node at the beginning (top)
    std::reverse(formatted_rows.begin(), formatted_rows.end());

    return formatted_rows;
}



void btree_nodes:: Dump() const {
    const int d = get_max_depth();

    // If this tree is empty, tell someone
    if (d == 0) {
        cout << " <empty tree>\n";
        return;
    }

    // This tree is not empty, so get a list of node values...
    const auto rows_disp = get_row_display();
    // then format these into a text representation...
    auto formatted_rows = row_formatter(rows_disp);
    // then trim excess space characters from the left sides of the text...
    trim_rows_left(formatted_rows);
    // then dump the text to cout.
    for (const auto &row: formatted_rows) {
        std::cout << ' ' << row << '\n';
    }
}