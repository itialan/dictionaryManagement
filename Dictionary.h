#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include "Constant.h"
#include "Lib.h"
using namespace std;

struct MeanWord {
	string mean;
	MeanWord* next;
};
typedef struct MeanWord* MEAN_WORD;

struct Data {
	string word, type;
	MEAN_WORD first = NULL; // ds lien ket cua nghia viet
	string* example[MAXEX]; // de cho max vi du la 5
};

struct Dictionary {
	Data info;
	Dictionary *left, *right;
};
typedef struct Dictionary* Node_Dictionary;

struct HashTable {
	Dictionary *Head, *Tail;
};

void Init(Node_Dictionary& first);

int tapTuDien(string word);

MEAN_WORD makeMeanNode(string mean);
void Insert_First_MeanNode(MEAN_WORD& first, string mean);
void Insert_Last_MeanNode(MEAN_WORD& first, string mean);
void clearList(MEAN_WORD& first);

Node_Dictionary MakeNode(Data& x);
void Insert_First(Node_Dictionary& First, Node_Dictionary& Last, Data newWord);
void Insert_Left(Node_Dictionary& First, Node_Dictionary& Last, Node_Dictionary p, Data newWord);
void Insert_Last(Node_Dictionary& First, Node_Dictionary& Last, Data newWord);
void Insert_Order(Node_Dictionary& First, Node_Dictionary& Last, Data newWord);

bool compare(string wisfound, Node_Dictionary word);
bool list_Empty(HashTable ldict);
Node_Dictionary Find_Word(HashTable* ldict, string wisfound);
Node_Dictionary first_word(HashTable* ldict);
Node_Dictionary last_word(HashTable* ldict);
Node_Dictionary right_word(HashTable* ldict, Node_Dictionary curWord);
Node_Dictionary left_word(HashTable* ldict, Node_Dictionary curWord);

void Delete_Head(Node_Dictionary& head, Node_Dictionary& tail);
void Deleta_Tail(Node_Dictionary& head, Node_Dictionary& tail);
void Deleta_After(Node_Dictionary& head, Node_Dictionary& tail, Node_Dictionary dict);
void Del_General(Node_Dictionary& head, Node_Dictionary& tail, Node_Dictionary& wIsDel);
void Del_Word(HashTable*& ldict, Node_Dictionary& curWord);