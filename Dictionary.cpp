#include "Dictionary.h"

void Init(Node_Dictionary& first) {
	first = NULL;
}

Node_Dictionary MakeNode(Data& x) {
	Node_Dictionary p = new Dictionary;
	if (p == NULL) return NULL;
	p->info = x;
	p->left = NULL;
	p->right = NULL;
	return p;
}

void Insert_First(Node_Dictionary& First, Node_Dictionary& Last, Data newWord){
	Node_Dictionary p = MakeNode(newWord);
	if (First == NULL) {
		First = Last = p;
	}
	else {
		p->right = First;
		First->left = p;
	}
	First = p;
	p->left = NULL;
}

void Insert_Left(Node_Dictionary& First, Node_Dictionary& Last, Node_Dictionary p, Data newWord){
	Node_Dictionary q = MakeNode(newWord);
	if (p == NULL) {
		cout << "Khong ton tai nut !";
	}
	else if (First == p) {
		Insert_First(First, Last, newWord);
	}
	else {
		Node_Dictionary l = p->left;
		l->right = q;
		q->left = l;
		q->right = p;
		p->left = q;
	}
}

void Insert_Last(Node_Dictionary& First, Node_Dictionary& Last, Data newWord) {
	Node_Dictionary x = MakeNode(newWord);
	if (First == NULL)
		First = Last = x;
	else
	{
		Last->right = x;
		x->left = Last;
		Last = x;
	}
}

void Insert_Order(Node_Dictionary& First, Node_Dictionary& Last, Data newWord) {
	if (First == NULL) {
		Insert_First(First, Last, newWord);
	}
	else {
		Node_Dictionary p;
		for (p = First; p->right != NULL && p->info.word < newWord.word; p = p->right);
		if (p->info.word > newWord.word) {
			Insert_Left(First, Last, p, newWord);
		}
		else {
			Insert_Last(First, Last, newWord);
		}
	}
}

int tapTuDien(string word) {
	int count;
	for (int i = 97; i < 123; i++) {
		if (word[0] == char(i)) {
			count = i;
			return count - 97;
		}
	}
	return -1;
}

MEAN_WORD makeMeanNode(string mean) {
	MEAN_WORD p = new MeanWord;
	if (p == NULL) return NULL;
	p->mean = mean;
	p->next = NULL;
	return p;
}

void Insert_First_MeanNode(MEAN_WORD& first, string mean) {
	MEAN_WORD p = makeMeanNode(mean);
	if (first == NULL) {
		first = p;
	}
	else {
		p->next = first;
		first = p;
	}
}

void Insert_Last_MeanNode(MEAN_WORD& first, string mean) {
	MEAN_WORD p = makeMeanNode(mean);
	if (first == NULL) {
		first = p;
	}
	else {
		MEAN_WORD m;
		for (m = first; m->next != NULL; m = m->next);
		m->next = p;
	}
}

void clearList(MEAN_WORD& first) {
	MEAN_WORD p;
	while (first != NULL) {
		p = first;
		first = first->next;
		delete p;
	}
}

bool compare(string wisfound, Node_Dictionary word) {
	if (wisfound.length() > word->info.word.length()) {
		return false;
	}
	else {
		for (int i = 0; i < wisfound.length(); i++) { // so sánh tới độ dài của ký tự cần tìm. vd "ir" vs "iron" 
			if (wisfound[i] != word->info.word[i]) {// giống nhau "ir" nên xuất ra những chữ bắt đầu bằng "ir"
				return false;
			}
		}
		return true;
	}
}

Node_Dictionary Find_Word(HashTable* ldict, string wisfound) {
	int count = tapTuDien(wisfound);
	if (count < 0) {
		return NULL;
	}
	else {
		Node_Dictionary p = ldict[count].Head;
		while (p != NULL) {
			if (compare(wisfound, p)) {
				return p;
			}
			p = p->right;
		}
		return NULL;
	}
}

Node_Dictionary first_word(HashTable* ldict) {
	for (int i = 0; i < 26; i++) {
		if (ldict[i].Head != NULL) {
			return ldict[i].Head;
		}
	}
}

Node_Dictionary last_word(HashTable* ldict) {
	for (int i = 25; i >= 0; i--) {
		if (ldict[i].Tail != NULL) {
			return ldict[i].Tail;
		}
	}
}

Node_Dictionary right_word(HashTable* ldict, Node_Dictionary curWord) {
	if (curWord != NULL) {
		Node_Dictionary rightWord = curWord->right;
		if (rightWord != NULL) {
			return rightWord;
		}
		else {
			int x = tapTuDien(curWord->info.word);
			if (x < 25) {
				while (x != 26) {
					if (ldict[x + 1].Head != NULL) {
						return ldict[x + 1].Head;
					}
					x++;
					/*if (x == 26) {
						return first_word(ldict);
					}*/
				}
				return NULL;
			}
			else {
				return NULL;
			}
		}
	}
	else return NULL;
}

Node_Dictionary left_word(HashTable* ldict, Node_Dictionary curWord) {
	if (curWord != NULL) {
		Node_Dictionary leftWord = curWord->left;
		if (leftWord != NULL) {
			return leftWord;
		}
		else {
			int x = tapTuDien(curWord->info.word);
			if (x > 0) {
				while (x > 0) {
					if (ldict[x - 1].Tail != NULL) {
						return ldict[x - 1].Tail;
					}
					x--;
				}
				return NULL;
				/*if (x == 0) {
					return last_word(ldict);*/
			}
			else {
				return NULL;
			}
		}
	}
	else return NULL;
}

bool list_Empty(HashTable ldict) {
	return ldict.Head == NULL;
}

void Delete_Head(Node_Dictionary& head, Node_Dictionary& tail) {
	if (head == NULL) return;
	Node_Dictionary p = head;
	if (head == tail) // trường hợp danh sách có 1 node
		head = tail = NULL;
	else {
		head = p->right;
		head->left = NULL;
	}
	delete p;
}

void Deleta_Tail(Node_Dictionary& head, Node_Dictionary& tail) {
	if (head == NULL) return;
	Node_Dictionary p = tail;
	if (head == tail) // trường hợp danh sách có 1 node
		head = tail = NULL;
	else {
		tail = p->left;
		tail->right = NULL;
	}
	delete p;
}

void Deleta_After(Node_Dictionary& head, Node_Dictionary& tail, Node_Dictionary dict) {
	if (dict == NULL) return;
	if (head == NULL) return;
	if (dict == head) {
		Delete_Head(head, tail);
	}
	else if (dict == tail) {
		Deleta_Tail(head, tail);
	}
	else {
		dict->left->right = dict->right;
		dict->right->left = dict->left;
	}
	delete dict;
}

void Del_General(Node_Dictionary& head, Node_Dictionary& tail, Node_Dictionary& wIsDel) {
	if (head == NULL) return;
	else {
		Node_Dictionary p = head;
		while (p != NULL && p->info.word != wIsDel->info.word) {
			p = p->right;
		}
		if (p == NULL) return;
		else {
			if (p == head) {
				Delete_Head(head, tail);
			}
			else if (p == tail) {
				Deleta_Tail(head, tail);
			}
			else {
				Deleta_After(head, tail, p);
			}
		}
	}
}

void Del_Word(HashTable*& ldict, Node_Dictionary& curWord) {
	if (curWord != NULL) {
		Node_Dictionary wordIsDeled = curWord;
		if (left_word(ldict, curWord) == NULL) {
			if (right_word(ldict, curWord) == NULL) {
				curWord = NULL;
				Gotoxy(17, 15); cout << "<khong co du lieu>";
			}
			else {
				curWord = right_word(ldict, curWord);
			}
		}
		else {
			curWord = left_word(ldict, curWord);
		}
		int count = tapTuDien(wordIsDeled->info.word);
		Del_General(ldict[count].Head, ldict[count].Tail, wordIsDeled);
	}
}