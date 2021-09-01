#include "Post.h"
Post::Post() :postID(0), boardID(0), title(""), content(vector<string>({ "" })),author(""), deleted(false), deleted_by_self(false), postTime(time(NULL)) //??
{

}
Post::Post(int pID,int bID, bool del, bool del_self, string by,string t, vector<string> c,vector<int>cmtID ,time_t tm):postID(pID),boardID(bID),author(by),title(t),content(c),deleted(del),deleted_by_self(del_self),comment_IDs(cmtID),postTime(tm)
{
	ifstream ifile;
	string path3 = ".\\DataBase\\Comments";
	cout << endl;
	for (int i : comment_IDs)
	{
		try
		{
			ifile.open(path3 + "\\" + to_string(i) + ".txt");
			if (ifile.fail())//if file open failed, skip this file.
				throw path3 + "\\" + to_string(i) + ".txt";

			int id, type, del, postID;
			string userID, content;
			time_t tm;
			ifile >> id;
			ifile >> del;
			ifile >> type;
			ifile >> postID;
			ifile >> userID;
			ifile >> tm;
			ifile >> ws;
			std::getline(ifile, content);
			comments.push_back(Comment(type, content, userID, id, postID, (del != 0 ? true : false), tm));
			ifile.close();
		}
		catch (string path)//if can't open this file, show the path and pause
		{
			cout << "Can't open " << path << ".\n";
			system("pause");
		}
	}
}
int Post::getPostID() 
{
	return postID;
}
void Post::setPostID(int pID) 
{
	postID = pID;
}
int Post::GetBoardID() 
{
	return boardID;
}
void Post::SetBoardID(int bID) 
{
	boardID = bID;
}
string Post::getTitle() 
{
	return title;
}
void Post::setTitle(string t) 
{
	title = t;
}
vector<string> Post::getContent() 
{
	return content;
}
void Post::setContent(vector<string> c) 
{
	content = c;
}
Comment& Post::getComment(int index)
{
	return comments[index];
}
vector<Comment>& Post::getCommentVec()
{
	return comments;
}
vector<int>& Post::getCommentIDVec()
{
	return comment_IDs;
}
void Post::newComment(Comment c)
{
	comments.push_back(c);
}
string Post::getAuthor()
{
	return author;
}
void Post::setAuthor(string auth)
{
	author = auth;
}
bool Post::isDeleted()
{
	return deleted;
}
void Post::setDeleted(bool del)
{
	deleted = del;
}
bool Post::isDeletedBySelf()
{
	return deleted_by_self;
}
void Post::setDeletedBySelf(bool d)
{
	deleted_by_self = d;
}
time_t& Post::getTime()
{
	return postTime;
}
void Post::setTime(time_t t)
{
	postTime = t;
}
Comment& Post::operator [](int n)
{
	return comments[n];
}
void Post::writeToFile()
{
	string path2 = ".\\DataBase\\Posts";
	ofstream ofile;
	try {
		ofile.open(path2 + "\\" + to_string(postID) + ".txt", ios::trunc);
		if (ofile.fail())//if file open failed, skip this file.
			throw path2 + "\\" + to_string(postID) + ".txt";
		ofile << postID << endl;
		ofile << (deleted ? 1 : 0) << endl;
		ofile << (deleted_by_self ? 1 : 0) << endl;
		ofile << boardID << endl;
		ofile << author << endl;
		ofile << title << endl;
		ofile << postTime << endl;
		ofile << content.size() << endl;
		for (string i : content)
		{
			ofile << i;
		}
		ofile << comments.size() << endl;
		for (int i : comment_IDs)
		{
			ofile << i << endl;
		}
		ofile.close();
	}
	catch (string path)//if can't open this file, show the path and pause
	{
		cout << "Can't open " << path << ".\n";
		system("pause");
	}
}