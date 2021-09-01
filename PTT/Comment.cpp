#include "Comment.h"
Comment::Comment():type(0),content(""),userID(""),deleted(false),postTime(time(NULL))
{
}
Comment::Comment(int t, string con, string uid, int cid, int pid, bool del,time_t tm):type(t),content(con),userID(uid),commentID(cid),postID(pid),deleted(del),postTime(tm)
{
}
Comment::Comment(int t, string id) : type(t), userID(id),deleted(false)
{
	//input content
}
bool Comment::idDeleted()
{
	return deleted;
}
void Comment::setDeleted(bool del)
{
	deleted = del;
}
int Comment::getType()
{
	return type;
}
void Comment::setType(int t)
{
	type = t;
}
string Comment::getContent()
{
	return content;
}
void Comment::setContent(string c)
{
	content = c;
}
string Comment::GetUserID()
{
	return userID;
}
void Comment::SetUserID(string id)
{
	userID = id;
}
time_t& Comment::getTime()
{
	return postTime;
}
void Comment::setTime(time_t t)
{
	postTime = t;
}
void Comment::writeToFile()
{
	string path3 = ".\\DataBase\\Comments";
	ofstream ofile;
	try {
		ofile.open(path3 + "\\" + to_string(commentID) + ".txt", ios::trunc);
		if (ofile.fail())//if file open failed, skip this file.
			throw path3 + "\\" + to_string(commentID) + ".txt";
		ofile << commentID << endl;
		ofile << (deleted ? 1 : 0) << endl;
		ofile << type << endl;
		ofile << postID << endl;
		ofile << userID << endl;
		ofile << postTime << endl;
		ofile << content << endl;
		ofile.close();
	}
	catch (string path)//if can't open this file, show the path and pause
	{
		cout << "Can't open " << path << ".\n";
		system("pause");
	}
}