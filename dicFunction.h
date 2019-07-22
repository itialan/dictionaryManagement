#pragma once
#include "FileHandling.h"
#include "Constant.h"
#include "Lib.h"
#include "Display.h"

extern string typesWord[5];
extern int xType[5];

int checkType(string type);
void editWord(string a);
void switchType(string key[]);
int chooseType(bool& isMove);
void splitMean(string word, Data& dict);
void add_and_edit_word(string& result, bool& isMove, int distance, int& ordinal, bool& isSave);
void addWord(Node_Dictionary& dict);
bool check_data_is_empty(Data dict);
void addWord_toDic(HashTable*& ldict, Data& dict, bool isEdit);
void search_word(HashTable*& ldict, Node_Dictionary& curWord);