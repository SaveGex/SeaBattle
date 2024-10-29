#pragma once

#include <array>

using namespace System::Collections::Generic;

ref class Field{
private:
	List<List<int>^>^ where_hits;
	List<List<int>^>^ marks;
public:
	Field() {
		where_hits = gcnew List<List<int>^>;
		for (int i = 0; i < where_hits->Count; i++) {
			where_hits[i] = gcnew List<int>{};
		}
	}
	void add_hit(int X, int Y) {

		//always first is X second is Y. Its declaration
		List<int>^ buffer = gcnew List<int>;
		buffer->Add(X);
		buffer->Add(Y);

		where_hits->Add(buffer);
	}
	//void add_mark(int X, int Y) {
	//	//always first is X second is Y. Its declaration
	//	marks.push_back({ X,Y });
	//}
	//void reset_mark(int X, int Y) {
	//	for (int i = 0; i < marks.size(); i++) {
	//		for (int j = 0; j < marks[i].size(); j++) {
	//			if (marks[i][j] == X && marks[i][j + 1] == Y) {
	//				marks.erase(marks.begin() + i);
	//				return;
	//			}
	//		}
	//	}
	//}
	//bool operator==(std::array<int, 2> mark) {
	//	if (marks.empty()) {
	//		return false;
	//	}
	//	for (int i = 0; i < marks.size(); i++) {
	//		if (marks[i][0] == mark[0] && marks[i][1] == mark[1]) {
	//			return true;
	//		}
	//	}
	//}
};

