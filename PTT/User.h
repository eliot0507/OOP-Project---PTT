#pragma once
#include "Post.h"
class User
{
	protected:
		string userID;
		string password;
		vector < int > postID;
		int permission;		//0->guest 1->Manager 2->User
		vector<Mail> mails;
	public:
		User();
		User(string id,string pw,int p,vector<int>pID,vector<Mail> mls);
		string getUserID();
		virtual void setUserID(string uID) = 0;
		virtual string getPassword() = 0;
		virtual void setPassword(string pw) = 0;
		int getPermission();
		void setPermission(int p);
		virtual int getPostID(int index) = 0;
		vector<int>& getPostIDVec();
		void writeToFile();
		vector<Mail>& getMail();
};
class NormalUser :public User
{
public:
	NormalUser();
	NormalUser(string id, string pw, vector<int>pID, vector<Mail> mails);
	int getPostID(int index);
	void setUserID(string uID);
	string getPassword();
	void setPassword(string pw);
};
class ManagerUser :public User
{
public:
	ManagerUser();
	ManagerUser(string id, string pw, vector<int>pID, vector<Mail> mails);
	int getPostID(int index);
	void setUserID(string uID);
	string getPassword();
	void setPassword(string pw);
};
class GuestUser :public User
{
public:
	GuestUser();
	string getPassword();
	void setUserID(string uID) {}
	void setPassword(string pw) {}
	int getPostID(int index) { return -1; }
};
struct UserData
{
	string userID;
	vector < int > postID;
	int permission;
	int post_num;
};