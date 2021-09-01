#include "BoardManager.h"
#include "Windows.h"
#define BASIC_HEADER
#include "Editor.h"

namespace {
	bool keyPressed(int key)
	{
		return GetAsyncKeyState(key) & 0x8000;
	}
}
BoardManager::BoardManager():current_user(0),current_board(0),current_post(0),state(MENU)
{
	ifstream ifile;
	//boards
		//read board files
	string path = ".\\DataBase\\Boards";
	for (const auto& file : fs::directory_iterator(path))
	{
		try {
			if (file.path() == ".\\DataBase\\Boards\\numbers.txt")
				continue;
			ifile.open(file.path());
			if (ifile.fail())//if file open failed, skip this file.
				throw file.path().string();
			//read data
			int id, del, posCount;
			string name, des;
			ifile >> id;
			ifile >> del;
			ifile >> name;
			ifile >> ws;
			getline(ifile, des);
			ifile >> posCount;
			vector<int> postIDs;
			for (int i = 0; i < posCount; i++)
			{
				int temp;
				ifile >> temp;
				postIDs.push_back(temp);
			}
			sort(postIDs.begin(), postIDs.end());
			//push back to boards
			boards.push_back(Board(id, (del != 0 ? true : false), name, des, postIDs));
			ifile.close();
		}
		catch (string path)//if can't open this file, show the path and pause
		{
			cout << "Can't open " << path << ".\n";
			system("pause");
		}
	}
	//users
		//create guest user
	users.push_back(new GuestUser());
		//read user files
	string path_user = ".\\DataBase\\Users";
	for (const auto& file : fs::directory_iterator(path_user))
	{
		try {
			ifile.open(file.path());
			if (ifile.fail())//if file open failed, skip this file.
				throw file.path().string();
			//read data
			int perm, postNum,mailNum;
			string uID, pw;
			ifile >> uID;
			ifile >> pw;
			ifile >> perm;
			ifile >> postNum;
			vector<int> postIDs;
			for (int i = 0; i < postNum; i++)
			{
				int temp;
				ifile >> temp;
				postIDs.push_back(temp);
			}
			ifile >> mailNum;
			vector<Mail> mails;
			for (int i = 0; i < mailNum; i++)
			{
				string from,to,msg;
				ifile >> from >> to;
				getline(ifile >> ws, msg);
				mails.push_back(Mail(from, to, msg));
			}
			//push back to users
			if (perm == 1)
				users.push_back(new ManagerUser(uID, pw, postIDs,mails));
			else if (perm == 2)
				users.push_back(new NormalUser(uID, pw, postIDs,mails));
			ifile.close();
		}
		catch (string path)
		{
			cout << "Can't open " << path << ".\n";
			system("pause");
		}
	}
}
BoardManager::~BoardManager()
{
	for (size_t i = 0; i < users.size(); i++)
		delete users[i];
}
void BoardManager::run()
{
	//SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	while(1){
		if (state == MENU) {
			BD_Menu();
		}
		else if (state == SELECT_BOARD) {
			BD_Select_Board();
		}
		else if (state == BOARD) {
			BD_Board();
		}
		else if (state == POST) {
			BD_Post();
		}
		else if (state == MAIL) {
			BD_Mail();
		}
		else if (state == EXIT)
			break;
		else
		{
			cout << "State error\n";
			break;
		}
		/*else if (state == EDIT_POST) {
			BD_Edit_Post();
		}*/
	}
}

void BoardManager::BD_Menu() {
	while (_kbhit())
	{
		_getch();
	}
	while (1) {
		viewer.view_menu();
		string input;
		cout << "Please enter your userID to log in\nEnter \"new\" to sign up \nEnter \"guest\" to log in as a guest\n";
		cout << "Enter EOF to exit:";
		if (!(cin >> input))
		{
			state = EXIT;
			break;
		}
		cin.ignore(INT_MAX,'\n');
		if (input == "new") {
			string tempid;
			string temppassword;
			//view create new user
			cout << "Enter your new user ID:";
			cin >> tempid;
			cin.ignore(INT_MAX, '\n');//clear cin
			bool suc;//check if creating new user is successful or not
			while (1)
			{
				suc = true;
				for (size_t i = 0; i < users.size(); i++) {
					if (users[i]->getUserID() == tempid) {
						cout << "This ID has been used, enter a new one:";
						suc = false;
						break;
					}
				}
				if (suc)
					break;
				cin >> tempid;
				cin.ignore(INT_MAX, '\n');//clear cin
			}
			cout << "Enter your passsword:";
			getline(cin >> ws, temppassword);
			//create account to this new user
			users.push_back(new NormalUser(tempid, temppassword, vector<int>(0),vector<Mail>(0)));
			users.back()->writeToFile();
			current_user = users.size() - 1;
			state = SELECT_BOARD;
			return;
		}
		else if (input == "guest") {
			state = SELECT_BOARD;
			current_user = 0;
			return;
		}
		else {
			string truePassword;
			bool no_one = true;
			size_t i;
			for (i = 1; i < users.size(); i++) {
				if (users[i]->getUserID() == input) {
					no_one = false;
					truePassword = users[i]->getPassword();
					break;
				}
			}
			if (no_one)
			{
				cout << "No such user ID called:";
				cout << input << endl;
				this_thread::sleep_for(chrono::milliseconds(1500));

				continue;//re-load menu again
			}
			string temppassword;
			cout << "Enter password:";
			getline(cin >> ws, temppassword);
			while (1)
			{
				if (truePassword == temppassword) {
					cout << "Login Success...";
					current_user = i;
					state = SELECT_BOARD;
					this_thread::sleep_for(chrono::milliseconds(1500));//wait for 1.5s
					while (_kbhit())//clear keyboard buffer
					{
						_getch();
					}
					return;
				}
				cout << "Wrong password, plesase try again:";
				getline(cin >> ws, temppassword);
			}
		}
	}
}
void BoardManager::BD_Mail()
{
	viewer.view_mail(users[current_user]->getMail(), users[current_user]->getUserID());
	while (1) {
		if (keyPressed(VK_LEFT) || keyPressed(VK_ESCAPE))
		{
			state = SELECT_BOARD;
			return;
		}
		else if (keyPressed(0x53))
		{
			string from= users[current_user]->getUserID(), to, msg;
			bool flag=true;
			while (flag)
			{
				cout << "Enter receiver:";
				cin >> to;
				for (User* i : users)
				{
					if (i->getUserID() == to)
					{
						flag = false;
						break;
					}
				}
				if (flag == false)
					break;
				else
					cout << "User doesn't exist, try again.\n";
			}
			cout << "Enter message:";
			getline(cin >> ws, msg);
			Mail m(from, to, msg);
			for (User* i : users)
			{
				if (i->getUserID() == to || i->getUserID() == from)
				{
					i->getMail().push_back(m);
					i->writeToFile();
				}
			}
			cout << "Message sent!\n";
			this_thread::sleep_for(chrono::milliseconds(1500));
			return;
		}
		this_thread::sleep_for(chrono::milliseconds(200));
	}

}
void BoardManager::BD_Select_Board(){
	int pos = current_board;
	int perm=users[current_user]->getPermission();
	viewer.view_select_board(boards, pos, perm);
	while(1){
		if (keyPressed(VK_UP)) {
			if (pos == 0)
				pos = 1;
			viewer.view_select_board(boards, --pos, perm);
		}
		else if (keyPressed(VK_DOWN)) {
			if (pos == boards.size() - 1)
				pos--;
			viewer.view_select_board(boards, ++pos, perm);
		}
		else if (keyPressed(VK_LEFT)|| keyPressed(VK_ESCAPE)) {
			cout << "Are your sure you want to leave?(Y/N):";
			char c;
			c = getchar();
			cin.ignore(INT_MAX, '\n');
			if (c == 'y' || c == 'Y')
			{
				state = MENU;	
				return;
			}
			else
			{
				this_thread::sleep_for(chrono::milliseconds(200));
				continue;
			}
				
		}
		else if (!boards[pos].isDeleted()&&(keyPressed(VK_RIGHT) || keyPressed(VK_RETURN))) {
			state = BOARD;
			current_board = pos;
			current_post = 0;
			return;
		}
		else if (keyPressed(0x4D) && perm!=0 )
		{
			state = MAIL;
			return;
		}
		if (perm == 1)
		{
			//check if it is create board or delete board both of them need manager power
			if (keyPressed(VK_DELETE) || keyPressed(0x44))	//press d or del -> delete board
			{
				string reason;
				cout << "Leave your reason here:";
				cin >> ws;
				getline(cin, reason);
				reason.insert(0, "<DELETED> ");
				boards[pos].setDeleted(true);
				boards[pos].setDescription(reason);
				boards[pos].writeToFile();
				return;//back to select_board again
			}
			else if (keyPressed(0x43)/*Press C*/){	//Create board
				string newName, newDes;
				cout << "Enter the name:";
				cin >> newName;
				cin.ignore(INT_MAX, '\n');
				cout << "Enter the description:";
				getline(cin, newDes);
				//write to boards folder
				boards.push_back(Board(boards.size(), false, newName, newDes, vector<int>(0)));
				boards.back().writeToFile();
				//update total number of boards
				ofstream ofile;
				ofile.open(".\\DataBase\\Boards\\numbers.txt",ios::trunc);
				ofile << boards.size();
				ofile.close();
				return;//back to select_board again
			}
		}
		this_thread::sleep_for(chrono::milliseconds(200));
	}
}

void BoardManager::BD_Board(){
	int pos = current_post;
	int perm = users[current_user]->getPermission();
	int postNum = boards[current_board].getPostNum();
	string uid = users[current_user]->getUserID();
	viewer.view_board(boards[current_board], pos, perm);
	//clear keyboard buffer
	while (_kbhit())
	{
		_getch();
	}
	while(1){
		if (keyPressed(VK_UP) && postNum > 0) {
			if (pos == 0)
				pos = 1;
			viewer.view_board(boards[current_board], --pos, perm);
		}
		else if (keyPressed(VK_DOWN) && postNum > 0) {
			if (pos == boards[current_board].getPostNum() - 1)
				pos--;
			viewer.view_board(boards[current_board], ++pos, perm);
		}
		else if (keyPressed(VK_LEFT) || keyPressed(VK_ESCAPE)) {
			state = SELECT_BOARD;
			return;
		}
		else if ((keyPressed(VK_RIGHT) || keyPressed(VK_RETURN)) && postNum > 0) {
			if (!boards[current_board][pos].isDeleted() )
			{
				state = POST;
				current_post = pos;
				return;
			}
		}
		else if ((keyPressed(VK_DELETE) || keyPressed(0x44)) && postNum > 0){ //Press D or Press Delete -> delete post
			if (perm == 1)
			{
				string reason;
				cout << "Leave your reason here:";
				cin >> ws;
				getline(cin, reason);
				reason.insert(0, "<DELETED> ");
				boards[current_board][pos].setDeleted(true);
				if(boards[current_board][pos].getAuthor()==uid)
					boards[current_board][pos].setDeletedBySelf(true);
				boards[current_board][pos].setTitle(reason);
				boards[current_board][pos].writeToFile();
				return;//back to board again
			}
			else if(boards[current_board][pos].getAuthor()==uid)
			{
				boards[current_board][pos].setDeleted(true);
				boards[current_board][pos].setDeletedBySelf(true);
				boards[current_board][pos].setTitle("[DELETED BY AUTHOR]");
				boards[current_board][pos].writeToFile();
				return;//back to board again
			}
		}
		else if (keyPressed(0x43) && perm != 0/*Press C*/){			//not guest, Create post
			int bid = boards[current_board].getBoardID();
			string title;
			vector<string> content;
			time_t time_stamp;
			cout << "Enter your title:";
			getline(cin >> ws, title);
			content = BD_Edit_Post({"\n"});
			time_stamp = time(NULL);
			int pid;
			ifstream getPid(".\\DataBase\\Posts\\numbers.txt");
			getPid >> pid;
			getPid.close();
			ofstream setPid(".\\DataBase\\Posts\\numbers.txt", ios::trunc);
			setPid << pid + 1 << endl;
			setPid.close();
			boards[current_board].push_back_Post(Post(pid, bid, false, false, uid, title, content, {}, time_stamp));
			boards[current_board].getPostVec().back().writeToFile();
			boards[current_board].writeToFile();
			users[current_user]->getPostIDVec().push_back(pid);
			users[current_user]->writeToFile();
			return;
		}
		else if (keyPressed(0x45) && perm != 0 && postNum > 0){	//not guest, Press E -> Edit post
			if (boards[current_board][pos].getAuthor() == uid)
			{
				//maybe edit title
				vector<string> content;
				content = BD_Edit_Post(boards[current_board][pos].getContent());
				boards[current_board][pos].setContent(content);
				boards[current_board][pos].writeToFile();
			}
			else
			{
				cout << "You can only edit your post.\n";
				this_thread::sleep_for(chrono::milliseconds(1500));
			}
			return;
		}


		this_thread::sleep_for(chrono::milliseconds(200));
	}
}

void BoardManager::BD_Post(){
	int perm = users[current_user]->getPermission();
	viewer.view_post(boards[current_board][current_post], perm,boards[current_board].getName());
	//clear keyboard buffer
	while (_kbhit())
	{
		_getch();
	}
	while(1){
		/*if (keyPressed(VK_UP)) {
			viewer.view_(boards[current_board], pos--, perm);
		}
		else if (keyPressed(VK_DOWN)) {
			viewer.view_board(boards[current_board], pos++, perm);
		}*/
		if (keyPressed(VK_LEFT) || keyPressed(VK_ESCAPE)) {
			state = BOARD;
			return;
		}
		else if (perm == 1 && (keyPressed(VK_DELETE) || keyPressed(0x44))/*Press D or Press Delete*/) { //delete comment
			int comment_num;
			cout << "Enter the comment number you want to delete:";
			cin >> comment_num;//which floor
			comment_num--;//transfer to index
			cin.ignore(INT_MAX, '\n');
			if (comment_num < 0 || comment_num >= boards[current_board][current_post].getCommentVec().size())
			{
				cout << "That comment doesn't exist.\n";
				this_thread::sleep_for(chrono::milliseconds(1500));
				return;//back to post
			}
			string reason;
			cout << "Leave your reason here:";
			getline(cin >> ws, reason);
			reason.insert(0, "<DELETED> ");
			boards[current_board][current_post].getComment(comment_num).setDeleted(true);
			boards[current_board][current_post].getComment(comment_num).setContent(reason);
			boards[current_board][current_post].getComment(comment_num).writeToFile();
			return;//back to post
		}
		else if (keyPressed(0x50) && perm != 0){		//not guest, Press P, push this post
			string uid = users[current_user]->getUserID();
			for (Comment i: boards[current_board][current_post].getCommentVec())
			{
				if (i.GetUserID() == uid && i.getType() == 1)
				{
					cout << "You already said GOOD to this post, you can't do it again.\n";
					this_thread::sleep_for(chrono::milliseconds(1500));
					return;//go back to post
				}
			}
			int pid = boards[current_board][current_post].getPostID();
			string comment_content;
			cout << "Enter your comment:";
			getline(cin >> ws, comment_content);
			ifstream getCid(".\\DataBase\\Comments\\numbers.txt");
			int cid;
			getCid >> cid;
			getCid.close();
			ofstream setCid(".\\DataBase\\Comments\\numbers.txt", ios::trunc);
			setCid << cid + 1 << endl;
			setCid.close();
			boards[current_board][current_post].getCommentVec().push_back(Comment(1, comment_content, uid, cid, pid, false, time(NULL)));
			boards[current_board][current_post].getCommentVec().back().writeToFile();
			boards[current_board][current_post].getCommentIDVec().push_back(cid);
			boards[current_board][current_post].writeToFile();
			return;//back to post
		}
		else if (keyPressed(0x53) && perm != 0){		//not guest, Press S, say bad to this post
			string uid = users[current_user]->getUserID();
			for (Comment i : boards[current_board][current_post].getCommentVec())
			{
				if (i.GetUserID() == uid && i.getType() == 2)
				{
					cout << "You already said BAD to this post, you can't do it again.\n";
					this_thread::sleep_for(chrono::milliseconds(1500));
					return;//go back to post
				}
			}
			int pid = boards[current_board][current_post].getPostID();
			string comment_content;
			cout << "Enter your comment:";
			cin >> ws;
			getline(cin, comment_content);
			ifstream getCid(".\\DataBase\\Comments\\numbers.txt");
			int cid;
			getCid >> cid;
			getCid.close();
			ofstream setCid(".\\DataBase\\Comments\\numbers.txt", ios::trunc);
			setCid << cid + 1 << endl;
			setCid.close();
			boards[current_board][current_post].getCommentVec().push_back(Comment(2, comment_content, uid, cid, pid, false, time(NULL)));
			boards[current_board][current_post].getCommentVec().back().writeToFile();
			boards[current_board][current_post].getCommentIDVec().push_back(cid);
			boards[current_board][current_post].writeToFile();
			return;//back to post
		}
		else if (keyPressed(0x52) && perm != 0){		//not guest, Press R, just commenting
			string uid = users[current_user]->getUserID();
			int pid = boards[current_board][current_post].getPostID();
			string comment_content;
			cout << "Enter your comment:";
			cin >> ws;
			getline(cin, comment_content);
			ifstream getCid(".\\DataBase\\Comments\\numbers.txt");
			int cid;
			getCid >> cid;
			getCid.close();
			ofstream setCid(".\\DataBase\\Comments\\numbers.txt", ios::trunc);
			setCid << cid + 1 << endl;
			setCid.close();
			boards[current_board][current_post].getCommentVec().push_back(Comment(0, comment_content, uid, cid, pid, false, time(NULL)));
			boards[current_board][current_post].getCommentVec().back().writeToFile();
			boards[current_board][current_post].getCommentIDVec().push_back(cid);
			boards[current_board][current_post].writeToFile();
			return;//back to post
		}		


		this_thread::sleep_for(chrono::milliseconds(200));
	}
}
vector<string> BoardManager::BD_Edit_Post(vector<string> content)
{
	Editor wordpad(content);
	return wordpad.mainly();
}
