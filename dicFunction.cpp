#include "dicFunction.h"

string typesWord[5] = { "dong tu", "trang tu", "danh tu", "tinh tu", "pho tu" };
int xType[5] = { 104, 113, 123, 132, 141 };
int currentIndex = 0;
int previousIndex = 0;

void editWord(string a)
{
	a[0] = toupper(a[0]); // ham toupper(x) in hoa x
	int length = a.length();
	for (int i = 1; i < length; ++i)
	{
		if (a[i - 1] == ' ' && a[i] != ' ') a[i] = toupper(a[i]);
		else a[i] = tolower(a[i]); // in thuong
	}
}

int checkType(string type) {
	for (int i = 0; i < 5; i++) {
		if (type == typesWord[i])
		{
			return i;
		}
	}
}

void switchType(string key[]) { // change color each index
	Gotoxy(xType[currentIndex], Y_ADD + 2);
	SetBGColor(8);
	cout << key[currentIndex];
	SetBGColor(0);
	Gotoxy(xType[previousIndex], Y_ADD + 2);
	cout << key[previousIndex];
	previousIndex = currentIndex;
}

int chooseType(bool& isMove) {
	ShowCur(false);
	int keyboard = 0;
	SetBGColor(8);
	Gotoxy(xType[currentIndex], Y_ADD + 2); cout << typesWord[currentIndex];
	SetBGColor(0);
	while (true) {
		keyboard = _getch();
		if (keyboard == 0) {
			keyboard = _getch();
		}
		switch (keyboard) {
		case KEY_LEFT:
			Gotoxy(xType[currentIndex], Y_ADD + 2); cout << typesWord[currentIndex];
			if (currentIndex > 0)
			{
				currentIndex -= 1;
			}
			else
			{
				currentIndex = 4;
			}
			switchType(typesWord);
			break;
		case KEY_RIGHT:
			Gotoxy(xType[currentIndex], Y_ADD + 2); cout << typesWord[currentIndex];
			if (currentIndex < 4)
			{
				currentIndex += 1;
			}
			else
			{
				currentIndex = 0;
			}
			switchType(typesWord);
			break;
		case KEY_UP:
			isMove = true;
			Gotoxy(X_ADD, Y_ADD + 2); cout << "Dong Tu  Trang Tu  Danh Tu  Tinh Tu  Pho Tu";
			ShowCur(true);
			return -1;
			break;
		case KEY_DOWN:
			isMove = false;
			Gotoxy(X_ADD, Y_ADD + 2); cout << "Dong Tu  Trang Tu  Danh Tu  Tinh Tu  Pho Tu";
			ShowCur(true);
			return -1;
			break;
		case ESC:
			ShowCur(true);
			return -1;
			break;
		case ENTER:
			ShowCur(true);
			return currentIndex;
			break;
		}
	}
}

void splitMean(string word, Data& dict) { // for split mean to node dic
	string split = "";
	int i = 0;
	int length = word.length();
	while(i < length) {
		split += word[i];
		i++;
		if (word[i] == ';' || i == length) {
			if (dict.first == NULL) {
				Insert_First_MeanNode(dict.first, split);
			}
			else {
				Insert_Last_MeanNode(dict.first, split);
			}
			split = "";
			i++;
		}
	}
}

void add_and_edit_word(string& result, bool& isMove, int distance, int& ordinal, bool& isSave) {
	int count = result.length();
	Gotoxy(X_ADD + distance + 2, Y_ADD + ordinal * 2);
	if (count < MAX_LENGTH) {
		cout << result;
	}
	else {
		for (int i = count - MAX_LENGTH; i < count; i++) {
			cout << result[i];
		}
	}
	while (true) {
		int key = _getch();
		if (key != 224 && key != 0) {
			if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122) || key == 59 || key == 63 || key == 33 || key == SPACE) {
				count++;
				result += char(key);
				if (count < MAX_LENGTH) {
					cout << char(key);
				}
				else {
					Gotoxy(X_ADD + distance + 2, Y_ADD + ordinal * 2);
					for (int i = count - MAX_LENGTH; i < count; i++) {
						cout << result[i];
					}
				}
			}
			else if (key == ENTER) {
				result = fix_Text(result);
				del_main_word(X_ADD + distance + 2, Y_ADD + ordinal * 2, 1);
				Gotoxy(X_ADD + distance + 2, Y_ADD + ordinal * 2);
				if (result.length() < MAX_LENGTH)
				{
					cout << result;
				}
				else {
					for (int i = result.length() - MAX_LENGTH; i < result.length(); i++) {
						cout << result[i];
					}
				}
				return;
			}
			else if (key == BACKSPACE && count > 0) {
				result.erase(result.length() - 1, 1);
				if (count <= MAX_LENGTH) {
					cout << "\b" << " " << "\b";
				}
				else {
					Gotoxy(X_ADD + distance + 2, Y_ADD + ordinal * 2);
					for (int i = count - MAX_LENGTH - 1; i < count - 1; i++) {
						cout << result[i];
					}
				}
				count--;
			}
		}
		else if (key == 224) {
			key = _getch();
			if (key == KEY_UP) {
				isMove = true;
				return;
			}
			else {
				isMove = false;
				return;
			}
		}
		else if (key == 0) {
			key = _getch();
			if (key == F10) {
				isSave = true;
				return;
			}
		}
	}
}

void addWord(Node_Dictionary& dict) {
	string mean, ex[MAXEX];
	char temp; int i = 0, pos = 0;
	cout << "Tu : ";
	getline(cin, dict->info.word);
	fflush(stdin);
	cout << "Loai : ";
	getline(cin, dict->info.type);
	cout << "Nghia : ";
	while (true) {
		mean = "";
		cout << "+ ";
		getline(cin, mean);
		if (dict->info.first == NULL) {
			Insert_First_MeanNode(dict->info.first, mean);
		}
		else {
			Insert_Last_MeanNode(dict->info.first, mean);
		}
		cout << "\nC neu muon tiep tuc : "; cin >> temp;
		cin.ignore();
		if (temp != 'c')
			break;
	}
	cout << "\nVi du : ";
	while (i < MAXEX) {
		cout << "+ ";
		getline(cin, ex[i]);
		i++; pos++;
		cout << "\nC neu muon tiep tuc : "; cin >> temp;
		cin.ignore();
		if (temp != 'c')
			break;
	}
	if (pos < MAXEX) {
		for (int j = pos; j < MAXEX; j++) {
			ex[j] = "<trong>";
		}
	}
	for (int k = 0; k < MAXEX; k++) {
		dict->info.example[k] = new string;
		*dict->info.example[k] = ex[k];
	}
}

bool check_data_is_empty(Data dict) { // if each field in 1 node of dic are NULL then error and otherwise
	if (dict.word.length() == 0) return true;
	if (dict.type.length() == 0) return true;
	if (dict.first == NULL) return true;
	for (int i = 0; i < MAXEX; i++) {
		if (*dict.example[i] != "<trong>")
			return false;
	}
	return true;
}

void addWord_toDic(HashTable*& ldict, Data& dict, bool isEdit) {
	//dict = new Dictionary; // không khởi tạo sẽ bị lỗi
	int ordinal = 0;
	bool isMoveUp = false;
	bool isSave = false;
	bool wordIsExist = false;
	string word, mean, example[MAXEX], type;
	int intType = -1;

	// EDIT
	if (isEdit) {
		// gán giá trị
		word = dict.word;
		type = dict.type;
		currentIndex = checkType(type);
		MEAN_WORD Viet;
		for (Viet = dict.first; Viet != NULL; Viet = Viet->next) {
			mean += Viet->mean;
			if (Viet->next != NULL)
			{
				mean += ";";
			}
		}
		clearList(dict.first); // xóa toàn bộ danh sách liên kết đơn của nghĩa việt, nếu không thì 
		for (int i = 0; i < MAXEX; i++) { //khi thêm hay sửa dữ liệu sẽ bị dư
			if (*dict.example[i] == "") {
				example[i] = "<trong>";
			}
			else {
				example[i] = *dict.example[i];
			}
		}

		Gotoxy(X_ADD + 6 + 2, Y_ADD + 0 * 2); cout << word;
		SetBGColor(8);
		Gotoxy(xType[currentIndex], Y_ADD + 1 * 2); cout << type;
		SetBGColor(0);
		Gotoxy(X_ADD + 6 + 2, Y_ADD + 2 * 2);
		if (mean.length() < MAX_LENGTH) {
			cout << mean;
		}
		else {
			for (int i = mean.length() - MAX_LENGTH; i < mean.length(); i++) {
				cout << mean[i];
			}
		}
		for (int i = 0; i < MAXEX; i++) {
				Gotoxy(X_ADD + 6 + 4, Y_ADD + 6 + i * 2);
				cout << example[i];
		}
	}

	while (true) {
		// ADD AND EDIT WORD
		switch (ordinal) {
		case 0: // word
		{
			add_and_edit_word(word, isMoveUp, 6, ordinal, isSave);
			if (Find_Word(ldict, word) == NULL) {
				wordIsExist = false;
				break;
			}
			wordIsExist = true;
			break;
		}
		case 1: // type
		{
			intType = chooseType(isMoveUp);
			break;
		}
		case 2: // mean
		{
			add_and_edit_word(mean, isMoveUp, 6, ordinal, isSave);
			break;
		}
		case 3: // ex 1
		{
			add_and_edit_word(example[0], isMoveUp, 8, ordinal, isSave);
			break;
		}
		case 4: // ex 2
		{
			add_and_edit_word(example[1], isMoveUp, 8, ordinal, isSave);
			break;
		}
		case 5: // ex 3
		{
			add_and_edit_word(example[2], isMoveUp, 8, ordinal, isSave);
			break;
		}
		case 6: // ex 4
		{
			add_and_edit_word(example[3], isMoveUp, 8, ordinal, isSave);
			break;
		}
		case 7: // ex 5
		{
			add_and_edit_word(example[4], isMoveUp, 8, ordinal, isSave);
			break;
		}
		}
		
		// move the cursor mouse
		if (isMoveUp) {
			if (ordinal == 0)
				isMoveUp = false;
			ordinal--;
		}
		else {
			if (ordinal == 7)
				isMoveUp = true;
			ordinal++;
		}

		// f10 SAVE
		if (isSave) {
			dict.word = word;
			if (intType != -1) 
			{
				dict.type = typesWord[intType];
			}
			else
			{
				dict.type = "<trong>";
			}
			splitMean(mean, dict);
			mean = "";
			for (int i = 0; i < MAXEX; i++)
			{
				if (example[i] == "")
				{
					example[i] = "<trong>";
				}
				dict.example[i] = new string;
				*dict.example[i] = example[i];
			}

			if (wordIsExist && !isEdit) {
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Tu vung khong duoc trung !           ";
			}
			else if (dict.type == "<trong>") {
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << " Vui long chon tu loai !             ";
			}
			else if (check_data_is_empty(dict)) {
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Cac truong du lieu khong duoc trong !";
			}
			else 
			{
				//editWord(dict.word);
				if (isEdit) {
					Node_Dictionary p = Find_Word(ldict, dict.word);
					p->info = dict;
				}
				else
				{
					int count = tapTuDien(dict.word);
					Insert_Order(ldict[count].Head, ldict[count].Tail, dict);
				}
				return;
			}
			isSave = false;
		}
	}
	//addWord(dict);
}

void search_word(HashTable*& ldict, Node_Dictionary& curWord) {
	string word = "";
	bool isChanged = false;
	int count = 0;
	curWord = first_word(ldict);
	int key = 0;
	mainMenu(sizeof(xMainMenu) / sizeof(int));

	while (true) {
		if (isChanged) {
			if (fix_Text(word) != "") curWord = Find_Word(ldict, fix_Text(word));
			else curWord = first_word(ldict);
		}
		output_word(ldict, curWord);

		// dời vị trí con trỏ chuột lại
		if (count < MAX_LENGTH + 30) Gotoxy(25 + count, Y_DISPLAY + 1);
		else Gotoxy(89, Y_DISPLAY + 1);

		// key
		key = _getch();
		if (key == 224) {
			key = _getch();
			if (key == KEY_UP) {
				if (left_word(ldict, curWord) != NULL) curWord = left_word(ldict, curWord);
			}
			else if (key == KEY_DOWN) {
				if (right_word(ldict, curWord) != NULL) curWord = right_word(ldict, curWord);
			}
			isChanged = false;
		}
		else if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122) || key == 59 || key == 63 || key == 33 || key == SPACE) {
			count++;
			word += char(key);
			if (count < MAX_LENGTH + 30) {
				cout << char(key);
			}
			else {
				Gotoxy(25, Y_DISPLAY + 1);
				for (int i = count - MAX_LENGTH - 30; i < count; i++) {
					cout << word[i];
				}
			}
			isChanged = true;
		}
		else if (key == BACKSPACE && count > 0) {
			word.erase(word.length() - 1, 1);
			if (count <= MAX_LENGTH + 30) {
				cout << "\b" << " " << "\b";
			}
			else {
				Gotoxy(25, Y_DISPLAY + 1);
				for (int i = count - MAX_LENGTH - 30 - 1; i < count - 1; i++) {
					cout << word[i];
				}
			}
			count--;
			isChanged = true;
		}
		else if (key == F2) {
			Data temp;
			addMenu(sizeof(xAddMenu) / sizeof(int));
			addWord_toDic(ldict, temp, false);
			del_add_word(100, 12, 22);
		}
		else if (key == F3) {
			addMenu(sizeof(xAddMenu) / sizeof(int));
			addWord_toDic(ldict, curWord->info, true);
			del_add_word(100, 12, 22);
		}
		else if (key == F4) {
			Del_Word(ldict, curWord);
		}
		else if (key == ESC) {
			return;
		}
	//}
	}
}