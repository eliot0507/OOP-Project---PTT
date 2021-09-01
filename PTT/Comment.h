#pragma once
#define _HAS_STD_BYTE 0
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;
struct Mail {
	Mail() :from(""), to(""), message("") {}
	Mail(string f, string t, string msg) :from(f), to(t), message(msg) {}
	string from;
	string to;
	string message;
};
class Comment
{
	private:
		bool deleted;
		int commentID;
		int type;//0 normal 1 good 2 bad
		int postID;
		string content;
		string userID;
		time_t postTime;
	public:
		Comment();
		Comment(int t, string con, string uid,int cid,int pid,bool del,time_t tm);
		Comment(int t, string id);
		bool idDeleted();
		void setDeleted(bool del);
		int getType();
		void setType(int t);
		string getContent();
		void setContent(string c);
		string GetUserID();
		void SetUserID(string id);
		time_t& getTime();
		void setTime(time_t t);
		void writeToFile();
};
struct CommentData {
	int commentID;
	int type;
	int postID;
	string content;
	string userID;
};