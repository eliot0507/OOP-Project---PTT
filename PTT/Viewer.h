#pragma once
#include "Board.h"
#include <thread>
#include <conio.h>
class Viewer
{
	private:
	public:
		void view_menu();
		void view_select_board(vector<Board> boardList, int pos,int permission);
		void view_board(Board board,int pos,int permission);
		void view_editor();
		void view_post(Post post, int permission,string boardName);
		void view_mail(vector<Mail> mails,string uid);
};