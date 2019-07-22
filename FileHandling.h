#pragma once
#include "Dictionary.h"
#include <fstream>

void SplitString(string word, Node_Dictionary& dict);
void ImportWord(HashTable*& dict, string word);
void ReadFile(HashTable*& dict);
void WriteFile(HashTable* dict);
void Output(HashTable dict);
