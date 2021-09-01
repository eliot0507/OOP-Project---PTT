#pragma once
#include "Comment.h"
class Post
{
	private:
		int postID;
		int boardID;
		string author;
		string title;
		vector<string> content;
		bool deleted;
		bool deleted_by_self;
		vector < Comment > comments;
		vector < int > comment_IDs;
		time_t postTime;
	public:
		Post();
		Post(int pID,int bID,bool del,bool del_self,string by,string t,vector<string> c, vector<int>cmtID, time_t tm);
		int getPostID();
		void setPostID(int pID);
		string getTitle();
		void setTitle(string t);
		vector<string> getContent();
		void setContent(vector<string> c);
		Comment& getComment(int index);
		vector<Comment>& getCommentVec();
		vector<int>& getCommentIDVec();
		void newComment(Comment c);
		int GetBoardID();
		void SetBoardID(int bID);
		string getAuthor();
		void setAuthor(string auth);
		bool isDeleted();
		void setDeleted(bool del);
		bool isDeletedBySelf();
		void setDeletedBySelf(bool d);
		time_t& getTime();
		void setTime(time_t t);
		void writeToFile();
		Comment& operator [](int n);
};
struct PostData
{
	int postID;
	int boardID;
	string title;
	string content;
	int comment_num;
};