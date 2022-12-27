//
// Created by MrsRo on 27.12.2022.
//

#ifndef CONSOLE_GAME_LAYOUT_H
#define CONSOLE_GAME_LAYOUT_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class Layout {

private:
    vector<char> layout;
    int x_l_size;
    int y_l_size;

public:

    Layout(int x, int y, char c) {
        x_l_size = x;
        y_l_size = y;

        for (int a = 0; a < y_l_size; a++) {
            for (int b = 0; b < x_l_size; b++) {
                if ((a == 0 || a == y_l_size - 1) || (b == 0 || b == x_l_size - 1)) layout.push_back(c);
                else layout.push_back(' ');
            }
        }
    }

    ~Layout() { layout.clear(); }

    void PrintLayout() {
        for (int a = 0; a < y_l_size; a++) {
            for (int b = 0; b < x_l_size; b++) cout << (layout[b + a * x_l_size]);
            cout << '\n';
        }
    }

    void ResetLayout() {
        for (int a = 0; a < y_l_size; a++) {
            for (int b = 0; b < x_l_size; b++) {
                if ((a == 0 || a == y_l_size - 1) || (b == 0 || b == x_l_size - 1)) continue;
                else layout[b + a * x_l_size] = ' ';
            }
        }
    }

    void DrawOnLayout(int x_start, int y_start, int x_size, int y_size, vector<char> window) {
        for (int a = y_start, a_counter = 0; a < (y_start + y_size); a++, a_counter++) {
            for (int b = x_start, b_counter = 0; b < (x_start + x_size); b++, b_counter++) {
                layout[b + a * x_l_size] = window[b_counter + a_counter * x_size];
            }
        }
    }

    void AddText(int x_start, int y_start, string text) {
        vector<char> text_vector;
        for (int a = 0; text[a] != '\0'; a++) text_vector.push_back(text[a]);
        Layout::DrawOnLayout(x_start, y_start, (int) text_vector.size(), 1, text_vector);
    }

    virtual vector<char> GetVector() { return layout; }

};

#endif //CONSOLE_GAME_LAYOUT_H
