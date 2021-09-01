#pragma once
#include "Board.h"
#include "User.h"
#include "Viewer.h"
enum BoardState
{
    MENU,
    SELECT_BOARD,
    BOARD,
    POST,
    EDIT_POST,
    MAIL,
    EXIT
};
class BoardManager {
	private:
        vector <User*> users;
        vector <Board> boards;
        int current_user;
        int current_board;
        int current_post;
        BoardState state;
        Viewer viewer;
	public:
        BoardManager();
        ~BoardManager();
        void run();
        void BD_Menu();
        void BD_Select_Board();
        void BD_Mail();
        void BD_Board();
        void BD_Post();
        vector<string> BD_Edit_Post(vector<string> content);
};