#include "FileHandling.h"

void SplitString(string word, Node_Dictionary& dict) {
	int i = 0;
	// split word
	string split = "";
	while (word[i] != '/') {
		split += word[i];
		i++;
	}
	i++;
	dict->info.word = split;
	// split type
	split = "";
	while (word[i] != '/') {
		split += word[i];
		i++;
	}
	i++;
	dict->info.type = split;
	// split mean
	split = "";
	while (word[i] != '/') {
		split += word[i];
		i++;
		if (word[i] == ';') {
			if (dict->info.first == NULL) {
				Insert_First_MeanNode(dict->info.first, split);
			}
			else {
				Insert_Last_MeanNode(dict->info.first, split);
			}
			split = "";
			i++;
		}
	}
	i++;
	// split example
	split = "";
	string stringEx[MAXEX]; int pos = 0;
	while (word[i] != '/') {
		split += word[i];
		i++;
		if (word[i] == ';') {
			stringEx[pos] = split;
			split = "";
			i++; pos++;
		}
	}
	if (pos < MAXEX) {
		for (int i = pos; i < MAXEX; i++) {
			stringEx[i] = "<trong>";
		}
	}
	for (int i = 0; i < MAXEX; i++) {
		dict->info.example[i] = new string;
		*dict->info.example[i] = stringEx[i];
	}
}

void ImportWord(HashTable *&dict, string word){
	int count = tapTuDien(word);
	Node_Dictionary tempWord = new Dictionary;
	SplitString(word, tempWord);
	Node_Dictionary newWord = MakeNode(tempWord->info);
	Insert_Order(dict[count].Head, dict[count].Tail, newWord->info);
}

void ReadFile(HashTable *&dict){
	ifstream fileIn("D:/Code/C++/CSDL v GT/Quan Ly Tu Dien/Project/data.txt");
	string line;
	if (fileIn.is_open()) {
		while (getline(fileIn, line)) {
			ImportWord(dict, line);
		}
	}
	fileIn.close();
}

void WriteFile(HashTable *dict){
	ofstream fileOut("D:/Code/C++/CSDL v GT/Quan Ly Tu Dien/Project/data.txt");
	if (fileOut.is_open()) {
		for (int i = 0; i < 26; i++) {
			Node_Dictionary p = dict[i].Head;
			if (p == NULL) {
				continue;
			}
			while (p != NULL) {
				// ghi tu va loai
				fileOut << p->info.word << "/" << p->info.type << "/";
				//ghi nghia
				MEAN_WORD Viet;
				for (Viet = p->info.first; Viet != NULL; Viet = Viet->next) {
					fileOut << Viet->mean << ";";
				}
				fileOut << "/";
				//ghi vi du
				for (int pos = 0; pos < MAXEX; pos++) {
					if (*p->info.example[pos] == "<trong>") continue;
					fileOut << *p->info.example[pos] << ";";
				}
				fileOut << "/\n";
				p = p->right;
			}
		}
	}
	fileOut.close();
}

void Output(HashTable dict) {
	Node_Dictionary p = dict.Head;
	while(p != dict.Tail->right) {
		cout << "Tu : "; cout << p->info.word;
		cout << "\nLoai : "; cout << p->info.type;
		cout << "\nNghia : ";
		MEAN_WORD Viet;
		for (Viet = p->info.first; Viet != NULL; Viet = Viet->next) {
			cout << Viet->mean << " ; ";
		}
		cout << "\nVi du : ";
		for (int i = 0; i < MAXEX; i++) {
			cout << *p->info.example[i] << " ; ";
		}
		cout << endl;
		p = p->right;
	}
}
