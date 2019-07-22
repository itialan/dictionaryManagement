//Khi nhập chữ trong khung text box, bạn có thể nhập thoải mái số từ… khi nhập tràn khung nhập, 
//chữ sẽ tự động thụt về phía sau.
//Trong quá trình thêm từ, sửa từ, có nhiều field khác nhau, bạn có thể nhấn lên xuống để sửa lại 
//nếu thấy không đúng.
//Từ điển chia ra 26 danh sách liên kết kép, danh sách chữ A đầu, danh sách chữ B đầu…
//Chỉ nhận những chữ cái và khoảng trống, tự động fix chữ nếu nhập nhiều khoảng trống, một số 
//trường hợp như field ví dụ cho phép nhập thêm dấu chấm than, dấu hỏi chấm…

#include "FileHandling.h"
#include "Constant.h"
#include "Display.h"
#include "dicFunction.h"
#include "Lib.h"

int main() {
	resizeConsole(2000, 1000);
	HashTable* dict = new HashTable[MAXALPHABET];
	Node_Dictionary p;
	Data t;
	string arrExample[5];
	for (int i = 0; i < MAXALPHABET; i++) { // init hash table
		dict[i].Head = NULL;
		dict[i].Tail = NULL;
	}
	Init(p);

	ReadFile(dict);
	//addWord_toDic(dict, p);
	//mainMenu(sizeof(xMainMenu) / sizeof(int));
	string word;
	bool w = false;
	int a = 0;
	/*addMenu(sizeof(xAddMenu) / sizeof(int));
	addWord_toDic(dict, t, false);
	for (int i = 0; i < MAXALPHABET; i++) {
		if (dict[i].Head != NULL) {
			Output(dict[i]);
		}
	}*/
	search_word(dict, p);
	//add_and_edit_word(word, w, 6, a, w);
	WriteFile(dict);
	system("pause");
	return 0;
}