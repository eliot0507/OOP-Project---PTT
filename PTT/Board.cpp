#include "Board.h"
Board::Board():name(""),deleted(false),boardID(0)
{
}
Board::Board(int id, bool del, string n, string des, vector<int> postIDs):boardID(id), deleted(del), name(n), description(des)
{
	ifstream ifile;
	string path2 = ".\\DataBase\\Posts";
	for (int i: postIDs)
	{
		try {
			ifile.open(path2 + "\\" + to_string(i) + ".txt");
			if (ifile.fail())//if file open failed, skip this file.
				throw path2 + "\\" + to_string(i) + ".txt";

			int id, boardId, del, delSelf, contentLineLen, comCount;
			string author, title;
			time_t tm;
			ifile >> id;
			ifile >> del;
			ifile >> delSelf;
			ifile >> boardId;
			ifile >> author;
			ifile >> ws;
			getline(ifile, title);
			ifile >> tm;
			ifile >> contentLineLen;
			vector<string> content;
			for (int i = 0; i < contentLineLen; i++)
			{
				string temp;
				ifile >> ws;
				getline(ifile, temp);
				temp.push_back('\n');
				content.push_back(temp);
			}
			ifile >> comCount;
			vector<int> commentIDs;
			for (int i = 0; i < comCount; i++)
			{
				int temp;
				ifile >> temp;
				commentIDs.push_back(temp);
			}
			sort(commentIDs.begin(), commentIDs.end());
			posts.push_back(Post(id, boardId, (del != 0 ? true : false), (delSelf != 0 ? true : false), author, title, content, commentIDs, tm));
			ifile.close();
		}
		catch (string path)//if can't open this file, show the path and pause
		{
			cout << "Can't open " << path << ".\n";
			system("pause");
		}
		
	}
}
bool Board::isDeleted()
{
	return deleted;
}
void Board::setDeleted(bool del)
{
	deleted = del;
}
string Board::getDescription()
{
	return description;
}
void Board::setDescription(string des)
{
	description = des;
}
string Board::getName()
{
	return name;
}
void Board::setName(string s)
{
	name = s;
}
int Board::getBoardID()
{
	return boardID;
}
int Board::getPostNum()
{
	return posts.size();
}
vector<Post> Board::getPostVec()
{
	return posts;
}
void Board::push_back_Post(Post p)
{
	posts.push_back(p);
}
void Board::writePostToFile(Post p)
{
	/*ofstream postList("PostList.dat", ios::app | ios::binary);
	int data_len;
	int postID = p.getPostID();
	char deleted = p.isDeleted() ? 1 : 0;
	char deleted_by_self = p.isDeletedBySelf() ? 1 : 0;
	int boardID;
	int author_len;
	string author;
	int title_len;
	string title;
	int content_len;
	string content;
	*/
}
void Board::writeToFile()
{
	ofstream ofile;
	string path = ".\\DataBase\\Boards";
	try 
	{
		ofile.open(path + "\\" + to_string(boardID) + ".txt", ios::trunc);
		if (ofile.fail())
			throw path + "\\" + to_string(boardID) + ".txt";
		ofile << boardID << endl;
		ofile << (deleted ? 1 : 0) << endl;
		ofile << name << endl;
		ofile << description << endl;
		ofile << posts.size() << endl;
		for (Post i:posts)
		{
			ofile << i.getPostID() << endl;
		}
		ofile.close();
	}
	catch (string path)//if can't open this file, show the path and pause
	{
		cout << "Can't open " << path << ".\n";
		system("pause");
	}
}
Post& Board::operator[](int index)
{
	return posts[index];
}