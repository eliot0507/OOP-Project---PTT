#pragma once
#include "Post.h"
class Board
{
	private:
		int boardID;
		string name;
		string description;
		bool deleted;
		vector<Post> posts;
	public:
		Board();
		Board(int id, bool del, string n, string des, vector<int> postIDs);
		int getBoardID();
		string getName();
		void setName(string s);
		string getDescription();
		void setDescription(string des);
		bool isDeleted();
		void setDeleted(bool del);
		int getPostNum();
		void push_back_Post(Post p);
		vector<Post> getPostVec();
		void writePostToFile(Post p);
		void writeToFile();
		Post& operator[](int index);
};