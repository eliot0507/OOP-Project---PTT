#include "User.h"
User::User():userID(),postID(),permission() //??
{

}
User::User(string id, string pw, int p, vector<int>pID,vector<Mail> mls):userID(id),password(pw),permission(p),postID(pID),mails(mls) //??
{
}
string User::getUserID()
{
	return userID;
}
int User::getPermission() 
{
	return permission;
}
void User::setPermission(int p) 
{
	permission = p;
}
vector<int>& User::getPostIDVec()
{
	return postID;
}
vector<Mail>& User::getMail()
{
	return mails;
}
void User::writeToFile()
{
	string path_user = ".\\DataBase\\Users";
	ofstream ofile;
	try {
		ofile.open(path_user + "\\" + userID + ".txt", ios::trunc);
		if (ofile.fail())//if file open failed, skip this file.
			throw path_user + userID + ".txt";
		//write data
		ofile << userID << endl;
		ofile << password << endl;
		ofile << permission << endl;
		ofile << postID.size() << endl;
		for (int i :postID)
		{
			ofile << i << endl;
		}
		ofile << mails.size() << endl;
		for (Mail i : mails)
		{
			ofile << i.from << endl;
			ofile << i.to << endl;
			ofile << i.message << endl;
		}
		ofile.close();
	}
	catch (string path)
	{
		cout << "Can't open " << path << ".\n";
		system("pause");
	}
}
//normal user
NormalUser::NormalUser():User("","", 2,vector<int>(0),vector<Mail>(0))
{
}
NormalUser::NormalUser(string id, string pw, vector<int>pID, vector<Mail> mails):User(id,pw,2,pID,mails)
{
}
int NormalUser::getPostID(int index) 
{
	return postID[index];
}
void NormalUser::setUserID(string uID)
{
	userID = uID;
}
string NormalUser::getPassword()
{
	return password;
}
void NormalUser::setPassword(string pw)
{
	password = pw;
}
//manager
ManagerUser::ManagerUser():User("","", 1, vector<int>(0), vector<Mail>(0))
{
}
ManagerUser::ManagerUser(string id, string pw, vector<int>pID, vector<Mail> mails) :User(id, pw, 1,pID,mails)
{
}
int ManagerUser::getPostID(int index)
{
	return postID[index];
}
void ManagerUser::setUserID(string uID)
{
	userID = uID;
}
string ManagerUser::getPassword()
{
	return password;
}
void ManagerUser::setPassword(string pw)
{
	password = pw;
}
//guest
GuestUser::GuestUser():User("guest","",0,vector<int>(0),vector<Mail>(0))
{
}
string GuestUser::getPassword()
{
	return "";
}