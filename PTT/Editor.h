#pragma once
#ifndef BASIC_HEADER
#include<iostream>
#include<string>
#include<vector>
#include<Windows.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono> 
#endif
#include<iterator>

using namespace std;

class Editor
{
private:
	vector<string> bruh;
	vector<unsigned int> cursor;		//0 for line 0 for column
	bool caps_lock_state;
public:
	Editor() :bruh{ "\n" }, cursor{ 0,0 }, caps_lock_state(false){};
	Editor(vector<string>& content) :cursor{ 0,0 }, caps_lock_state(false){
		if(content.empty()){
			string temp = "\n";
			content.push_back(temp);
		}
		else{
			bruh = content;
		}
	};
	vector<string> mainly();
	void print();
	void backspace_delete_c();
	//void delete_delete_c();
	void move_cursor(int);
	void enter_pressed();
	void insert_key(char a);
};