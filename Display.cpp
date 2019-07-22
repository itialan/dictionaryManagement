#include "Display.h"
#include "Dictionary.h"
#include "Lib.h"

int xMainMenu[3] = { 10, 46, 92 };
int xAddMenu[2] = { 100, 149 };

void mainMenu(int nkey) {
	int Mid, Mid2;
	Gotoxy(13, Y_DISPLAY + 1); cout << "TIM KIEM : ";

	Mid = (xMainMenu[0] + xMainMenu[1]) / 2;
	Gotoxy(Mid - 5, Y_DISPLAY + 3); cout << "DANH SACH TU";

	Mid2 = (xMainMenu[1] + xMainMenu[2]) / 2;
	Gotoxy(Mid2 - 5, Y_DISPLAY + 3); cout << "NGHIA CUA TU";

	//Gotoxy(54, Y_DISPLAY + 10); cout << "VI DU : ";

	for (int i = Y_DISPLAY; i < Y_DISPLAY + 27; i++) {
		for (int j = 0; j < nkey; j++) {
			Gotoxy(xMainMenu[j], i); cout << char(179); // cột thẳng
		}
	}

	Gotoxy(xMainMenu[1], Y_DISPLAY + 1); cout << char(0);

	for (int i = xMainMenu[0]; i <= xMainMenu[nkey - 1]; i++) {
		Gotoxy(i, Y_DISPLAY);
		if (i == xMainMenu[0]) {
			cout << char(218); // móc phải
		}
		else if (i == xMainMenu[2]) {
			cout << char(191); // móc trái
		}
		else {
			cout << char(196); // đường thằng ngang
		}

		Gotoxy(i, Y_DISPLAY + 2);
		if (i == xMainMenu[0]) {
			cout << char(195); // ngã ba sang phải
		}
		else if (i == xMainMenu[1]) {
			cout << char(194); // ngã ba hướng xuông
		}
		else if (i == xMainMenu[2]) {
			cout << char(180); // ngã ba sang trái
		}
		else {
			cout << char(196); // đường thẳng ngang
		}

		Gotoxy(i, Y_DISPLAY + 4);
		if (i == xMainMenu[0]) {
			cout << char(195); // ngã ba sang phải
		}
		else if (i == xMainMenu[1]) {
			cout << char(197); // ngã tư
		}
		else if (i == xMainMenu[2]) {
			cout << char(180); // ngã ba sang trái
		}
		else {
			cout << char(196); // đường thẳng ngang
		}

		Gotoxy(i, Y_DISPLAY + 25);
		if (i == xMainMenu[0]) {
			cout << char(195); // sang phải
		}
		else if (i == xMainMenu[1]) {
			cout << char(193); // ngã ba hướng lên
		}
		else if (i == xMainMenu[2]) {
			cout << char(180); //  ngã ba sang trái
		}
		else {
			cout << char(196);
		}

		Gotoxy(i, Y_DISPLAY + 27);
		if (i == xMainMenu[0]) {
			cout << char(192); // móc phải
		}
		else if (i == xMainMenu[2]) {
			cout << char(217); // móc trái
		}
		else {
			cout << char(196); // đường thằng ngang
		}
	}
	Gotoxy(20, Y_DISPLAY + 26); cout << "F2: THEM TU    F3: HIEU CHINH    F4: XOA TU    F10: LUU";
}

void addMenu(int nkey) {
	int Mid;
	Mid = (xAddMenu[0] + xAddMenu[1]) / 2;
	Gotoxy(Mid - 5, Y_DISPLAY + 3); cout << "THEM TU MOI";

	Gotoxy(X_ADD, Y_ADD); cout << "TU : ";
	Gotoxy(X_ADD, Y_ADD + 2); cout << "dong tu  trang tu  danh tu  tinh tu  pho tu";
	Gotoxy(X_ADD, Y_ADD + 4); cout << "NGHIA : ";
	Gotoxy(X_ADD, Y_ADD + 6); cout << "VI DU : ";
	Gotoxy(X_ADD + 8, Y_ADD + 6); cout << "+";
	Gotoxy(X_ADD + 8, Y_ADD + 8); cout << "+";
	Gotoxy(X_ADD + 8, Y_ADD + 10); cout << "+";
	Gotoxy(X_ADD + 8, Y_ADD + 12); cout << "+";
	Gotoxy(X_ADD + 8, Y_ADD + 14); cout << "+";

	for (int i = Y_DISPLAY + 2; i < Y_DISPLAY + 22; i++) {
		for (int j = 0; j < nkey; j++) {
			Gotoxy(xAddMenu[j], i); cout << char(179); // cột thẳng
		}
	}

	for (int i = xAddMenu[0]; i <= xAddMenu[nkey - 1]; i++) {
		Gotoxy(i, Y_DISPLAY + 2);
		if (i == xAddMenu[0]) { 
			cout << char(218); // móc phải
		}
		else if (i == xAddMenu[1]) {
			cout << char(191); // móc trái
		}
		else {
			cout << char(196); // đường thẳng ngang
		}

		Gotoxy(i, Y_DISPLAY + 4);
		if (i == xAddMenu[0]) {
			cout << char(195); // ngã ba sang phải
		}
		else if (i == xAddMenu[1]) {
			cout << char(180); // ngã ba sang trái
		}
		else {
			cout << char(196); // đường thẳng ngang
		}

		Gotoxy(i, Y_DISPLAY + 22);
		if (i == xAddMenu[0]) {
			cout << char(192); // sang phải
		}
		else if (i == xAddMenu[1]) {
			cout << char(217); // sang trái
		}
		else {
			cout << char(196);
		}
	}
}

string fix_Text(string text) {
	if (text != "") {
		while (text[0] == ' ') {
			text.erase(0, 1);
		}
		while (text[text.length() - 1] == ' ') {
			text.erase(text.length() - 1, 1);
		}
		if (text.length() > 3) { //Xoa khoang trang thua o giua
			for (short i = 1; i < text.length() - 2; i++) {
				if (text[i] == ' ' && text[i + 1] == ' ') {
					text.erase(i, 1);  i--;
				}
			}
		}
		return text;
	}
	else return text;
}

void del_add_word(int x, int y, int rowNumber) {
	for (int i = 0; i < rowNumber; i++) {
		Gotoxy(x, y + i); cout << "                                                  ";
	}
}

void del_main_word(int x, int y, int rowNumber) {
	for (int i = 0; i < rowNumber; i++) {
		Gotoxy(x, y + i); cout << "                                   ";
	}
}

void output_mean(Node_Dictionary dict) {
	int distance = MAX_LENGTH2; // khoảng cách từ lúc bắt đầu nhập đến khi xuống dòng
	int i = 0;
	MEAN_WORD Viet;
	Gotoxy(58, Y_DISPLAY + 8);
	for (Viet = dict->info.first; Viet != NULL; Viet = Viet->next) {
		if (Viet->mean.length() < distance + 1) {
			cout << Viet->mean;
			if (Viet->next != NULL) 
				cout << "; ";
			distance = distance - Viet->mean.length() - 2; // -1 là tính thêm cả dấu "; "
		}
		else {
			distance = MAX_LENGTH2;
			i++;
			Gotoxy(58, Y_DISPLAY + 8 + i); cout << Viet->mean;
			if (Viet->next != NULL) cout << "; ";
		}
	}
}

void output_detail_word(Node_Dictionary curWord) {
	del_main_word(57, Y_DISPLAY + 6, 19);
	Gotoxy(49, Y_DISPLAY + 6); cout << "LOAI : ";
	Gotoxy(49, Y_DISPLAY + 8); cout << "NGHIA : ";
	Gotoxy(49, Y_DISPLAY + 15); cout << "VI DU : ";
	Gotoxy(58, Y_DISPLAY + 6); cout << curWord->info.type;
	output_mean(curWord);
	for (int i = 0; i < MAXEX; i++) {
		if (*curWord->info.example[i] != "") {
			Gotoxy(57, Y_DISPLAY + 15 + 2 * i);
			cout << "+ " << *curWord->info.example[i];
		}
	}
}

void output_word(HashTable* ldict, Node_Dictionary curWord) {
	ShowCur(false);
	del_main_word(X_MAIN - 3, 15, 20);
	if (curWord == NULL) {
		Gotoxy(15, 15); cout << "<khong co tu can tim !>";
		del_main_word(49, Y_DISPLAY + 6, 19);
	}
	if (curWord != NULL) {
		for (int i = 0; i < 20; i++) {
			if (i == 0) {
				Gotoxy(11, 15);
				SetBGColor(8);
				cout << "   " << curWord->info.word;
				for (int j = curWord->info.word.length(); j < 32; j++) cout << " ";
				SetBGColor(0);
				output_detail_word(curWord);
			}
			else {
				if (curWord != NULL){
					Gotoxy(X_MAIN, 15 + i);
					cout << curWord->info.word;
				}
			}
			curWord = right_word(ldict, curWord);
		}
	}
	ShowCur(true);
}