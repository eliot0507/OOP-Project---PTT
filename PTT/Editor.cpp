#include "Editor.h"

namespace {
	bool keyPressed(int key)
	{
		return GetAsyncKeyState(key) & 0x8000;
	}
}

vector<string> Editor::mainly(){
	print();
	while (!keyPressed(VK_ESCAPE)) {
		if (keyPressed(VK_UP)) {
			move_cursor(1);
			print();
		}
		else if (keyPressed(VK_DOWN)) {
			move_cursor(2);
			print();
		}
		else if (keyPressed(VK_LEFT)) {
			move_cursor(3);
			print();
		}
		else if (keyPressed(VK_RIGHT)) {
			move_cursor(4);
			print();
		}
		else if (keyPressed(VK_BACK)) {
			backspace_delete_c();
			print();
		}
		else if (keyPressed(VK_DELETE)) {
			//delete_delete_c();
			print();
		}
		else if (keyPressed(VK_RETURN)) {
			enter_pressed();
			print();
		}
		//a to z

		else if (keyPressed(0x41)) {	//a
			insert_key('a');
		}
		else if (keyPressed(0x42)) {	//b
			insert_key('b');
		}
		else if (keyPressed(0x43)) {	//c
			insert_key('c');
		}
		else if (keyPressed(0x44)) {	//d
			insert_key('d');
		}
		else if (keyPressed(0x45)) {	//e
			insert_key('e');
		}
		else if (keyPressed(0x46)) {	//f
			insert_key('f');
		}
		else if (keyPressed(0x47)) {	//g
			insert_key('g');
		}
		else if (keyPressed(0x48)) {	//h
			insert_key('h');
		}
		else if (keyPressed(0x49)) {	//i
			insert_key('i');
		}
		else if (keyPressed(0x4a)) {	//j
			insert_key('j');
		}
		else if (keyPressed(0x4b)) {	//k
			insert_key('k');
		}
		else if (keyPressed(0x4c)) {	//l
			insert_key('l');
		}
		else if (keyPressed(0x4d)) {	//m
			insert_key('m');
		}
		else if (keyPressed(0x4e)) {	//n
			insert_key('n');
		}
		else if (keyPressed(0x4f)) {	//o
			insert_key('o');
		}
		else if (keyPressed(0x50)) {	//p
			insert_key('p');
		}
		else if (keyPressed(0x51)) {	//q
			insert_key('q');
		}
		else if (keyPressed(0x52)) {	//r
			insert_key('r');
		}
		else if (keyPressed(0x53)) {	//s
			insert_key('s');
		}
		else if (keyPressed(0x54)) {	//t
			insert_key('t');
		}
		else if (keyPressed(0x55)) {	//u
			insert_key('u');
		}
		else if (keyPressed(0x56)) {	//v
			insert_key('v');
		}
		else if (keyPressed(0x57)) {	//w
			insert_key('w');
		}
		else if (keyPressed(0x58)) {	//x
			insert_key('x');
		}
		else if (keyPressed(0x59)) {	//y
			insert_key('y');
		}
		else if (keyPressed(0x5a)) {	//z
			insert_key('z');
		}
		//numbers
		
		else if (keyPressed(0x30)) {	//0
			insert_key('0');
		}
		else if (keyPressed(0x31)) {	//1
			insert_key('1');
		}
		else if (keyPressed(0x32)) {	//2
			insert_key('2');
		}
		else if (keyPressed(0x33)) {	//3
			insert_key('3');
		}
		else if (keyPressed(0x34)) {	//4
			insert_key('4');
		}
		else if (keyPressed(0x35)) {	//5
			insert_key('5');
		}
		else if (keyPressed(0x36)) {	//6
			insert_key('6');
		}
		else if (keyPressed(0x37)) {	//7
			insert_key('7');
		}
		else if (keyPressed(0x38)) {	//8
			insert_key('8');
		}
		else if (keyPressed(0x39)) {	//9
			insert_key('9');
		}
		//other keys
		else if (keyPressed(VK_CAPITAL)) {
			caps_lock_state = !caps_lock_state;
			print();
		}
		else if (keyPressed(VK_SPACE)) {
			insert_key(' ');
		}
		//other keys...
		this_thread::sleep_for(chrono::milliseconds(75));
	}
	return bruh;
}

void Editor::insert_key(char a) {
	if (a >= 'a' && a <= 'z') {
		if (caps_lock_state) {
			bruh[cursor[0]].insert(bruh[cursor[0]].begin() + cursor[1], a - 32);
		}
		else {
			bruh[cursor[0]].insert(bruh[cursor[0]].begin() + cursor[1], a);
		}
	}
	else {
		bruh[cursor[0]].insert(bruh[cursor[0]].begin() + cursor[1], a);
	}
	move_cursor(4);
	print();
}

void Editor::print() {
	system("cls");
	for (unsigned int i = 0; i < bruh.size(); i++) {
		cout << i << "\t" << bruh[i];
	}
	cout << "\n\n\n\n";
	cout << "Line" << cursor[0] << "\tColumn" << cursor[1];
	if (caps_lock_state) {
		cout << "\tCaps lock on";
	}
}

void Editor::enter_pressed() {
	string temp;
	for (int i = cursor[1]; i < bruh[cursor[0]].size() - 1; i++) {
		temp.push_back(bruh[cursor[0]][i]);
	}
	temp.push_back('\n');
	for (int i = 0; i < temp.size(); i++) {
		bruh[cursor[0]].pop_back();
	}
	bruh.insert(bruh.begin() + cursor[0] + 1, temp);
	bruh[cursor[0]].insert(cursor[1], "\n");
	cursor[0]++;
	cursor[1] = 0;
}

void Editor::backspace_delete_c() {
	if (cursor[1] == 0) {	//delete line
		if (cursor[0] == 0) {
			return;
		}
		bruh[cursor[0] - 1].pop_back();//delete \n character;
		string temp = bruh[cursor[0]];
		bruh.erase(bruh.begin() + cursor[0]);
		bruh[cursor[0] - 1].insert(bruh[cursor[0] - 1].size(), temp);
		move_cursor(1);
		return;
	}
	else {					//delete character
		bruh[cursor[0]].erase(bruh[cursor[0]].begin() + cursor[1] - 1);
		move_cursor(3);
	}
	return;
}

void Editor::move_cursor(int mode) {
	if (mode == 1) {	//up
		if (cursor[0] == 0) {
			return;
		}
		else if (cursor[1] > bruh[cursor[0] - 1].size() - 1) {
			cursor[1] = bruh[cursor[0] - 1].size() - 1;
			cursor[0]--;
			return;
		}
		cursor[0]--;
	}
	else if (mode == 2) {	//down
		if (bruh.size() - 1 == cursor[0]) {
			return;
		}
		else if (cursor[1] > bruh[cursor[0] + 1].size() - 1) {
			cursor[1] = bruh[cursor[0] + 1].size() - 1;
			cursor[0]++;
			return;
		}
		cursor[0]++;
	}
	else if (mode == 3) {	//left
		if (cursor[1] == 0) {
			return;
		}
		cursor[1]--;
	}
	else if (mode == 4) {	//right
		if (bruh[cursor[0]].size() - 1 == cursor[1]) {
			return;
		}
		cursor[1]++;
	}
	return;
}
