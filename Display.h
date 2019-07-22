#pragma once
#include "Dictionary.h"

extern int xMainMenu[3]; // nếu không có extern thì xMainMenu không thể sử dụng được ở cpp khác
extern int xAddMenu[2];

void mainMenu(int nkey);
void addMenu(int nkey);
string fix_Text(string text);
void del_add_word(int x, int y, int rowNumber);
void del_main_word(int x, int y, int rowNumber);
void output_mean(Node_Dictionary dict);
void output_detail_word(Node_Dictionary curWord);
void output_word(HashTable* ldict, Node_Dictionary curWord);

