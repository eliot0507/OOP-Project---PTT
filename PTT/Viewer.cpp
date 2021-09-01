#include "Viewer.h"
#include "Post.h"
#include <map>
#define TEXT_ESC "\033[38;5;"
#define COLOR_ESC ";48;5;"
#define ESC "\033[48;5;"
#define RESET "\033[m"
/*
tm* lctm = localtime(&post.postTime); 
cout << "post time: " << put_time(lctm, "%y/%m/%d %H:%M:%S")*/
void showCoverPic();
void showBoardBanner();
void showBoardContent();
void showBoardFooter_0();
void showBoardFooter_1();
void showBoardFooter_2();
void showArticleBanner();
void showArticleContent();
void showArticleFooter_0();
void showArticleFooter_1();
void showArticleFooter_2();
void showPostBanner(); 
void showPostContent(); 
void showPostComment();
void showPostFooter_0();
void showPostFooter_1();
void showPostFooter_2();
void Viewer::view_menu() 
{
	showCoverPic();
}
void Viewer::view_mail(vector<Mail> mails,string uid)
{
    system("CLS");
    cout << "*** Press \"s\" to send message. ***\n";
    cout << "Messages to Me:\n";
    cout << "From\t" << "Message\n";
    for (Mail i : mails)
    {
        if (i.to == uid)
            cout << i.from << '\t' << i.message << endl;
    }
}
void Viewer::view_select_board(vector<Board> boardList, int pos, int permission)
{
    system("CLS");
    showBoardBanner();
    for (int i = 0 ; i < boardList.size() ; i++) 
    {
        if (pos == i) 
        {
            cout << TEXT_ESC << 1 << COLOR_ESC << 228 << "m" << " > " << RESET;
        }
        else 
        {
            cout << ESC << 0 << "m" << "   " << RESET;
        }

        if (i < 9) 
        {
            cout << ESC << 0 << "m" << "      " << RESET;
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << i+1 << RESET;
        }
        else 
        {
            cout << ESC << 0 << "m" << "     " << RESET;
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << i+1 << RESET;
        }
        cout << ESC << 0 << "m" << "     " << RESET;
        cout << TEXT_ESC << 30 << COLOR_ESC << 0 << "m" << boardList[i].getName() << RESET;
        int space = 22 - boardList[i].getName().length();
        for (int i = 0 ; i < space ; i++) 
        {
            cout << ESC << 0 << "m" << " " << RESET;
        }
        cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << boardList[i].getDescription() << RESET; //boardDiscription
        cout << endl;
    }
    if (permission == 0) 
    {
        showBoardFooter_0();
    }
    else if (permission == 1) 
    {
        showBoardFooter_1();
    }
    else if (permission == 2)
    {
        showBoardFooter_2();
    }
}
void Viewer::view_board(Board board, int pos, int permission)
{
    system("CLS");
    //Banner
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 19 << "m" << "  【文章列表】                        " << RESET;
    cout << TEXT_ESC << 226 << COLOR_ESC << 19 << "m" << "  " << RESET;
    cout << TEXT_ESC << 226 << COLOR_ESC << 19 << "m" << board.getName() << RESET;
    cout << TEXT_ESC << 226 << COLOR_ESC << 19 << "m" << "                                     " << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "   [↑]往上        [↓]往下        [←]/[Esc]離開        [→]/[return]選擇看板" << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "   編號     日 期  作  者           文   章   標   題                                " << RESET;
    //Content
    if (board.getPostNum() == 0) //沒有post的board
    {
        cout << endl;
        cout << endl;
        cout << ESC << 0 << "m" << "   " << RESET;
        cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "This board is empty." << RESET;
        cout << endl;
        cout << endl;
        cout << ESC << 0 << "m" << "   " << RESET;
        cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "Be the first user to post!" << RESET;
        cout << endl;
    }
    for (int i = 0 ; i < board.getPostNum() ; i++) 
    {
        tm* lctm = localtime(&(board.getPostVec()[i].getTime()));
        int goodCount = 0; //推的數量
        for (int j = 0 ; j < board.getPostVec()[i].getCommentVec().size() ; j++) 
        {
            if (board.getPostVec()[i].getCommentVec()[j].getType() == 1) 
            {
                goodCount = goodCount + 1;
            }
        }
        cout << endl;
        if (pos == i) 
        {
            cout << TEXT_ESC << 1 << COLOR_ESC << 228 << "m" << " > " << RESET;
            cout << ESC << 0 << "m" << "      " << RESET;
        }
        else 
        {
            cout << ESC << 0 << "m" << "         " << RESET;
        }
        if (i < 9) 
        {
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << i+1 << RESET; //1位數
        }
        else if (board.getPostVec()[i].getPostID() < 100) 
        {
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << i+1 << RESET; //2位數
        }
        else if (board.getPostVec()[i].getPostID() < 1000) 
        {
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << i+1; //3位數
        }
        if (goodCount == 0) //no goodCount
        {
            //沒推的文章
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "     " << RESET;
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << put_time(lctm, "%m/%d") << RESET; //日期
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  " << RESET;
            int a_space = 17 - board.getPostVec()[i].getAuthor().length();
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << board.getPostVec()[i].getAuthor() << RESET; //作者
            for (int k = 0 ; k < a_space ; k++) 
            {
                cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << " " << RESET;
            }
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << board.getPostVec()[i].getTitle() << RESET; //標題
        }
        else if (goodCount<10) //1位數
        {
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << " + " << RESET;
            cout << TEXT_ESC << 28 << COLOR_ESC << 0 << "m" << goodCount << RESET; //推文數
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << " " << RESET;
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << put_time(lctm, "%m/%d") << RESET; //日期
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  " << RESET;
            int a_space = 17 - board.getPostVec()[i].getAuthor().length();
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << board.getPostVec()[i].getAuthor() << RESET; //作者
            for (int k = 0 ; k < a_space ; k++) 
            {
                cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << " " << RESET;
            }
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << board.getPostVec()[i].getTitle() << RESET; //標題
        }
        else if (goodCount <100)//2位數
        {
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << " +" << RESET;
            cout << TEXT_ESC << 28 << COLOR_ESC << 0 << "m" << goodCount << RESET; //推文數
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << " " << RESET;
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << put_time(lctm, "%m/%d") << RESET; //日期
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  " << RESET;
            int a_space = 17 - board.getPostVec()[i].getAuthor().length();
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << board.getPostVec()[i].getAuthor() << RESET; //作者
            for (int k = 0 ; k < a_space ; k++) 
            {
                cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << " " << RESET;
            }
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << board.getPostVec()[i].getTitle() << RESET; //標題
        }
        else if (board.getPostVec()[i].isDeleted()) //deleted 
        {
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "     " << RESET;
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << put_time(lctm, "%m/%d") << RESET; //日期
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  " << RESET;
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "-                " << RESET;//作者
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << board.getPostVec()[i].getAuthor() << RESET; //原作者欄
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "(本文章已刪除) [" << RESET; //標題
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << board.getPostVec()[i].getAuthor() << RESET; //作者
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "]" << RESET;
        }
    }
    if(permission == 0)
    {
        showArticleFooter_0();
    }
    else if (permission == 1) 
    {
        showArticleFooter_1();
    }
    else if(permission == 2)
    {
        showArticleFooter_2();
    }
}
void Viewer::view_editor()
{
    
    
}
void Viewer::view_post(Post post, int permission, string boardName)
{
    system("CLS");
    tm* lctm = localtime(&(post.getTime())); 
    //Banner
    int space1 = 61 - post.getAuthor().length();
    int space2 = 76 - post.getTitle().length();
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 246 << "m" << " 作者 " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << post.getAuthor() << RESET;//作者
    for (int i = 0 ; i < space1 ; i++) 
    {   
        cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    }
    cout << TEXT_ESC << 19 << COLOR_ESC << 246 << "m" << " 看板 " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << boardName << RESET;//看板
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << "   " << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 246 << "m" << " 標題 " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << post.getTitle() << RESET;//標題
    for (int i = 0 ; i < space2 ; i++) 
    {   
        cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    }
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 246 << "m" << " 日期 " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << put_time(lctm, "%y/%m/%d %H:%M:%S") << RESET;//日期
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << "                                                           " << RESET;
    cout << endl;
    //Content
    cout << endl;
    for (int i = 0 ; i < post.getContent().size(); i++) 
    {
        cout << ESC << 0 << "m" << "   " << RESET;
        cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << post.getContent()[i] << RESET;//內文
    }
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "--" << RESET;
    //Comment
    for (int i = 0 ; i < post.getCommentVec().size() ; i++) 
    {
        tm* lctm = localtime(&(post.getComment(i).getTime()));
        if (post.getComment(i).getType() == 0) //normal
        {
            cout << endl;
            cout << TEXT_ESC << 1 << COLOR_ESC << 0 << "m" << "   → " << RESET;
            int space1 = 12 - post.getComment(i).GetUserID().length();
            cout << TEXT_ESC << 226 << COLOR_ESC << 0 << "m" << post.getComment(i).GetUserID() << RESET;//留言者
            for (int j = 0 ; j < space1 ; j++) 
            {
                cout << TEXT_ESC << 226 << COLOR_ESC << 0 << "m" << " " << RESET;
            }
            cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << ": " << RESET;
            cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << post.getComment(i).getContent() << RESET;//留言
            int space2 = 60 - post.getComment(i).getContent().length();
            for (int j = 0 ; j < space2 ; j++) 
            {
                cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << " " << RESET;
            }
            cout << ESC << 0 << "m" << put_time(lctm, "%m/%d %H:%M") << RESET;//日期
        }
        else if (post.getComment(i).getType() == 1) //good
        {
            cout << endl;//推
            cout << ESC << 0 << "m" << "   推 " << RESET;
            int space1 = 12 - post.getComment(i).GetUserID().length();
            cout << TEXT_ESC << 226 << COLOR_ESC << 0 << "m" << post.getComment(i).GetUserID() << RESET;//留言者
            for (int j = 0 ; j < space1 ; j++) 
            {
                cout << TEXT_ESC << 226 << COLOR_ESC << 0 << "m" << " " << RESET;
            }
            cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << ": " << RESET;
            cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << post.getComment(i).getContent() << RESET;//留言
            int space2 = 60 - post.getComment(i).getContent().length();
            for (int j = 0 ; j < space2 ; j++) 
            {
                cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << " " << RESET;
            }
            cout << ESC << 0 << "m" << put_time(lctm, "%m/%d %H:%M") << RESET;//日期
        }
        else if (post.getComment(i).getType() == 2) //bad
        {
            cout << endl;//噓
            cout << TEXT_ESC << 1 << COLOR_ESC << 0 << "m" << "   噓 " << RESET;
            int space1 = 12 - post.getComment(i).GetUserID().length();
            cout << TEXT_ESC << 226 << COLOR_ESC << 0 << "m" << post.getComment(i).GetUserID() << RESET;//留言者
            for (int j = 0 ; j < space1 ; j++) 
            {
                cout << TEXT_ESC << 226 << COLOR_ESC << 0 << "m" << " " << RESET;
            }
            cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << ": " << RESET;
            cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << post.getComment(i).getContent() << RESET;//留言
            int space2 = 60 - post.getComment(i).getContent().length();
            for (int j = 0 ; j < space2 ; j++) 
            {
                cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << " " << RESET;
            }
            cout << ESC << 0 << "m" << put_time(lctm, "%m/%d %H:%M") << RESET;//日期
        }
    }
    if  (permission == 0) 
    {
        showPostFooter_0();
    }
    else if (permission == 1) 
    {
        showPostFooter_1();
    }
    else if(permission == 2)
    {
        showPostFooter_2();
    }
}
void showCoverPic() 
{
    system("CLS");
    std::cout << std::endl;
    std::cout << ESC << 15 << "m" << "     " << RESET; //bg only
    std::cout << ESC << 0 << "m" << "  " << RESET;
    std::cout << ESC << 15 << "m" << "        " << RESET;
    std::cout << ESC << 0 << "m" << "  " << RESET;
    std::cout << ESC << 15 << "m" << "        " << RESET;
    std::cout << ESC << 0 << "m" << "      " << RESET;
    std::cout << TEXT_ESC << 255 << COLOR_ESC << 37 << "m" << "      看板 EarthDay2021      " << RESET;
    std::cout << ESC << 0 << "m" << "      " << RESET;
    std::cout << ESC << 15 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "  " << RESET;
    std::cout << ESC << 15 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "  " << RESET;
    std::cout << ESC << 15 << "m" << "   " << RESET;
    std::cout << ESC << 0 << "m" << "    " << RESET;
    std::cout << ESC << 15 << "m" << "   " << RESET;
    std::cout << ESC << 0 << "m" << "  " << RESET;
    std::cout << std::endl;
    std::cout << ESC << 15 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "  " << RESET;
    std::cout << ESC << 15 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "    " << RESET;
    std::cout << ESC << 15 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "        " << RESET;
    std::cout << ESC << 15 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "      " << RESET;
    std::cout << ESC << 37 << "m" << "                   " << RESET;
    std::cout << ESC << 2 << "m" << "  " << RESET;
    std::cout << ESC << 37 << "m" << "            " << RESET;
    std::cout << ESC << 2 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "   " << RESET;
    std::cout << ESC << 15 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "  " << RESET;
    std::cout << ESC << 15 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "     " << RESET;
    std::cout << ESC << 15 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "     " << RESET;
    std::cout << ESC << 15 << "m" << "  " << RESET;
    std::cout << std::endl;
    std::cout << ESC << 15 << "m" << "    " << RESET;
    std::cout << ESC << 0 << "m" << "      " << RESET;
    std::cout << ESC << 15 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "        " << RESET;
    std::cout << ESC << 15 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "    " << RESET;
    std::cout << ESC << 2 << "m" << "           " << RESET;
    std::cout << ESC << 37 << "m" << "                    " << RESET;
    std::cout << ESC << 2 << "m" << "  " << RESET;
    std::cout << ESC << 37 << "m" << "  " << RESET;
    std::cout << ESC << 2 << "m" << " " << RESET;
    std::cout << ESC << 37 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "  " << RESET;
    std::cout << ESC << 15 << "m" << "      " << RESET;
    std::cout << ESC << 0 << "m" << "  " << RESET;
    std::cout << ESC << 15 << "m" << "   " << RESET;
    std::cout << ESC << 0 << "m" << "    " << RESET;
    std::cout << ESC << 15 << "m" << "   " << RESET;
    std::cout << std::endl;
    std::cout << ESC << 15 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "        " << RESET;
    std::cout << ESC << 15 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "        " << RESET;
    std::cout << ESC << 15 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "   " << RESET;
    std::cout << ESC << 2 << "m" << "            " << RESET;
    std::cout << ESC << 37 << "m" << "           " << RESET;
    std::cout << ESC << 2 << "m" << "    " << RESET;
    std::cout << ESC << 37 << "m" << "       " << RESET;
    std::cout << ESC << 2 << "m" << "   " << RESET;
    std::cout << ESC << 37 << "m" << " " << RESET;
    std::cout << ESC << 2 << "m" << " " << RESET;
    std::cout << ESC << 37 << "m" << " " << RESET;
    std::cout << ESC << 0 << "m" << "     " << RESET;
    std::cout << ESC << 15 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "  " << RESET;
    std::cout << ESC << 15 << "m" << " " << RESET;
    std::cout << ESC << 0 << "m" << "      " << RESET;
    std::cout << ESC << 15 << "m" << " " << RESET;
    std::cout << std::endl;
    std::cout << ESC << 15 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "        " << RESET;
    std::cout << ESC << 15 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "        " << RESET;
    std::cout << ESC << 15 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "  " << RESET;
    std::cout << ESC << 2 << "m" << "             " << RESET;
    std::cout << ESC << 37 << "m" << "         " << RESET;
    std::cout << ESC << 2 << "m" << "    " << RESET;
    std::cout << ESC << 37 << "m" << " " << RESET;
    std::cout << ESC << 2 << "m" << " " << RESET;
    std::cout << ESC << 37 << "m" << "   " << RESET;
    std::cout << ESC << 2 << "m" << "           " << RESET;
    std::cout << ESC << 0 << "m" << "    " << RESET;
    std::cout << ESC << 15 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "   " << RESET;
    std::cout << ESC << 15 << "m" << "    " << RESET;
    std::cout << ESC << 0 << "m" << "   " << RESET;
    std::cout << ESC << 15 << "m" << "    " << RESET;
    std::cout << std::endl;
    std::cout << ESC << 0 << "m" << "                       " << RESET;
    std::cout << ESC << 2 << "m" << "              " << RESET;
    std::cout << ESC << 37 << "m" << "       " << RESET;
    std::cout << ESC << 2 << "m" << "     " << RESET;
    std::cout << ESC << 37 << "m" << "  " << RESET;
    std::cout << ESC << 2 << "m" << "                " << RESET;
    std::cout << std::endl;
    std::cout << ESC << 0 << "m" << "                      " << RESET;
    std::cout << ESC << 37 << "m" << "    " << RESET;
    std::cout << ESC << 2 << "m" << "    " << RESET;
    std::cout << ESC << 37 << "m" << "  " << RESET;
    std::cout << ESC << 2 << "m" << "     " << RESET;
    std::cout << ESC << 37 << "m" << "      " << RESET;
    std::cout << ESC << 2 << "m" << "     " << RESET;
    std::cout << ESC << 37 << "m" << "  " << RESET;
    std::cout << ESC << 2 << "m" << "                  " << RESET;
    std::cout << std::endl;
    std::cout << ESC << 0 << "m" << "                     " << RESET;
    std::cout << ESC << 2 << "m" << "   " << RESET;
    std::cout << ESC << 37 << "m" << "      " << RESET;
    std::cout << ESC << 2 << "m" << "    " << RESET;
    std::cout << ESC << 37 << "m" << " " << RESET;
    std::cout << ESC << 2 << "m" << " " << RESET;
    std::cout << ESC << 37 << "m" << "        " << RESET;
    std::cout << ESC << 2 << "m" << "   " << RESET;
    std::cout << ESC << 37 << "m" << "   " << RESET;
    std::cout << ESC << 2 << "m" << "                   " << RESET;
    std::cout << std::endl;
    std::cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  走向自然          " << RESET;
    std::cout << ESC << 2 << "m" << "     " << RESET;
    std::cout << ESC << 37 << "m" << "     " << RESET;
    std::cout << ESC << 2 << "m" << "   " << RESET;
    std::cout << ESC << 37 << "m" << "     " << RESET;
    std::cout << ESC << 2 << "m" << " " << RESET;
    std::cout << ESC << 37 << "m" << "  " << RESET;
    std::cout << ESC << 2 << "m" << "  " << RESET;
    std::cout << ESC << 37 << "m" << "       " << RESET;
    std::cout << ESC << 2 << "m" << "                   " << RESET;
    std::cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "        愛護地球" << RESET;
    std::cout << std::endl;
    std::cout << ESC << 0 << "m" << "                   " << RESET;
    std::cout << ESC << 2 << "m" << "    " << RESET;
    std::cout << ESC << 37 << "m" << "       " << RESET;
    std::cout << ESC << 2 << "m" << "  " << RESET;
    std::cout << ESC << 37 << "m" << "          " << RESET;
    std::cout << ESC << 2 << "m" << " " << RESET;
    std::cout << ESC << 37 << "m" << " " << RESET;
    std::cout << ESC << 2 << "m" << "                          " << RESET;
    std::cout << std::endl;
    std::cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "      珍愛環境     " << RESET;
    std::cout << ESC << 2 << "m" << "      " << RESET;
    std::cout << ESC << 37 << "m" << "                  " << RESET;
    std::cout << ESC << 2 << "m" << "                           " << RESET;
    std::cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "   從PTT開始" << RESET;
    std::cout << std::endl;
    std::cout << ESC << 0 << "m" << "                   " << RESET;
    std::cout << ESC << 2 << "m" << "     " << RESET;
    std::cout << ESC << 37 << "m" << "                 " << RESET;
    std::cout << ESC << 2 << "m" << "   " << RESET;
    std::cout << ESC << 37 << "m" << "  " << RESET;
    std::cout << ESC << 2 << "m" << "                         " << RESET;
    std::cout << std::endl;
    std::cout << ESC << 0 << "m" << "                  " << RESET;
    std::cout << ESC << 2 << "m" << "     " << RESET;
    std::cout << ESC << 37 << "m" << "     " << RESET;
    std::cout << ESC << 2 << "m" << " " << RESET;
    std::cout << ESC << 37 << "m" << "                      " << RESET;
    std::cout << ESC << 2 << "m" << "  " << RESET;
    std::cout << ESC << 37 << "m" << " " << RESET;
    std::cout << ESC << 2 << "m" << "      " << RESET;
    std::cout << ESC << 37 << "m" << "  " << RESET;
    std::cout << ESC << 2 << "m" << "         " << RESET;
    std::cout << std::endl;
    std::cout << ESC << 0 << "m" << "                  " << RESET;
    std::cout << ESC << 2 << "m" << "    " << RESET;
    std::cout << ESC << 37 << "m" << "                    " << RESET;
    std::cout << ESC << 2 << "m" << "     " << RESET;
    std::cout << ESC << 37 << "m" << "       " << RESET;
    std::cout << ESC << 2 << "m" << "       " << RESET;
    std::cout << ESC << 37 << "m" << " " << RESET;
    std::cout << ESC << 2 << "m" << "         " << RESET;
    std::cout << std::endl;
    std::cout << ESC << 0 << "m" << "                   " << RESET;
    std::cout << ESC << 2 << "m" << "  " << RESET;
    std::cout << ESC << 37 << "m" << " " << RESET;
    std::cout << ESC << 2 << "m" << " " << RESET;
    std::cout << ESC << 37 << "m" << "                 " << RESET;
    std::cout << ESC << 2 << "m" << "             " << RESET;
    std::cout << ESC << 37 << "m" << "    " << RESET;
    std::cout << ESC << 2 << "m" << "   " << RESET;
    std::cout << ESC << 37 << "m" << "   " << RESET;
    std::cout << ESC << 2 << "m" << "        " << RESET;
    std::cout << std::endl;
    std::cout << ESC << 0 << "m" << "        " << RESET;
    std::cout << ESC << 136 << "m" << "    " << RESET;
    std::cout << ESC << 0 << "m" << " " << RESET;
    std::cout << ESC << 136 << "m" << "   " << RESET;
    std::cout << ESC << 0 << "m" << "   " << RESET;
    std::cout << ESC << 2 << "m" << "  " << RESET;
    std::cout << ESC << 37 << "m" << "                   " << RESET;
    std::cout << ESC << 2 << "m" << "              " << RESET;
    std::cout << ESC << 37 << "m" << "    " << RESET;
    std::cout << ESC << 2 << "m" << "  " << RESET;
    std::cout << ESC << 37 << "m" << "    " << RESET;
    std::cout << ESC << 2 << "m" << "      " << RESET;
    std::cout << ESC << 0 << "m" << "    " << RESET;
    std::cout << ESC << 136 << "m" << "   " << RESET;
    std::cout << ESC << 0 << "m" << " " << RESET;
    std::cout << ESC << 136 << "m" << "    " << RESET;
    std::cout << std::endl;
    std::cout << ESC << 0 << "m" << "       " << RESET;
    std::cout << ESC << 136 << "m" << "     " << RESET;
    std::cout << ESC << 0 << "m" << " " << RESET;
    std::cout << ESC << 136 << "m" << "    " << RESET;
    std::cout << ESC << 0 << "m" << "   " << RESET;
    std::cout << ESC << 37 << "m" << "                     " << RESET;
    std::cout << ESC << 2 << "m" << "              " << RESET;
    std::cout << ESC << 37 << "m" << "         " << RESET;
    std::cout << ESC << 2 << "m" << "  " << RESET;
    std::cout << ESC << 37 << "m" << "  " << RESET;
    std::cout << ESC << 2 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << "   " << RESET;
    std::cout << ESC << 136 << "m" << "    " << RESET;
    std::cout << ESC << 0 << "m" << " " << RESET;
    std::cout << ESC << 136 << "m" << "     " << RESET;
    std::cout << std::endl;
    std::cout << ESC << 0 << "m" << "       " << RESET;
    std::cout << ESC << 136 << "m" << "      " << RESET;
    std::cout << ESC << 0 << "m" << " " << RESET;
    std::cout << ESC << 136 << "m" << "    " << RESET;
    std::cout << ESC << 0 << "m" << " " << RESET;
    std::cout << ESC << 136 << "m" << "  " << RESET;
    std::cout << ESC << 37 << "m" << "                    " << RESET;
    std::cout << ESC << 2 << "m" << "               " << RESET;
    std::cout << ESC << 37 << "m" << "         " << RESET;
    std::cout << ESC << 2 << "m" << " " << RESET;
    std::cout << ESC << 37 << "m" << "  " << RESET;
    std::cout << ESC << 2 << "m" << " " << RESET;
    std::cout << ESC << 136 << "m" << "  " << RESET;
    std::cout << ESC << 0 << "m" << " " << RESET;
    std::cout << ESC << 136 << "m" << "    " << RESET;
    std::cout << ESC << 0 << "m" << " " << RESET;
    std::cout << ESC << 136 << "m" << "      " << RESET;
    std::cout << std::endl;
    std::cout << ESC << 0 << "m" << "        " << RESET;
    std::cout << ESC << 136 << "m" << "              " << RESET;
    std::cout << ESC << 37 << "m" << "                   " << RESET;
    std::cout << ESC << 2 << "m" << "              " << RESET;
    std::cout << ESC << 37 << "m" << "             " << RESET;
    std::cout << ESC << 136 << "m" << "              " << RESET;
    std::cout << std::endl;
    std::cout << ESC << 0 << "m" << "         " << RESET;
    std::cout << ESC << 136 << "m" << "              " << RESET;
    std::cout << ESC << 2 << "m" << "    " << RESET;
    std::cout << ESC << 37 << "m" << "                 " << RESET;
    std::cout << ESC << 2 << "m" << "         " << RESET;
    std::cout << ESC << 37 << "m" << "             " << RESET;
    std::cout << ESC << 136 << "m" << "               " << RESET;
    std::cout << std::endl;
}
void showBoardBanner() 
{
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 19 << "m" << "  【看板列表】                  " << RESET;
    cout << TEXT_ESC << 226 << COLOR_ESC << 19 << "m" << "      批踢踢實業坊                                   " << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "   [↑]往上 [↓]往下    [m]Mail    [←]/[Esc]離開        [→]/[return]選擇看板" << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "   編號     看   板                 中   文   敘   述                                " << RESET;
    cout << endl;
}
void showBoardFooter_0() //guest
{
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 30 << "m" << "  選擇看板  " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << " Guest" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "                                                                   " << RESET;
    cout << endl;
}
void showBoardFooter_1() //manager
{
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 30 << "m" << "  選擇看板  " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << " Manager" << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (c)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "建立看板" << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (d/delete)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "刪除看板" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "                                " << RESET;
    cout << endl;
}
void showBoardFooter_2() //user
{
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 30 << "m" << "  選擇看板  " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << " User " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "                                                                   " << RESET;
    cout << endl;
}
void showBoardContent() 
{
    map<int, string>Number = { {0,"    HOT"}, {1,"      1"},{2,"      2"},{3,"      3"},{4,"      4"},{5,"      5"},{6,"      6"},{7,"      7"},{8,"      8"},{9,"      9"},{10,"      10"},{100,"    爆!"} };
    map<string, string>BoardName = { {"SYSOP","     SYSOP          "},{"ID_Problem","     ID_Problem     "},{"PttNewhand","     PttNewhand     "} };
    map<char, int>TypeColor = { {'y',136} ,{'p',5} ,{'g',28} ,{'w',255} ,{'r',196} };
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << Number[1] << RESET;
    cout << TEXT_ESC << 30 << COLOR_ESC << 0 << "m" << BoardName["SYSOP"] << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "       ◎非站務問題請洽AskBoard板/新手板" << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << Number[2] << RESET;
    cout << TEXT_ESC << 30 << COLOR_ESC << 0 << "m" << BoardName["ID_Problem"] << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "       ◎帳號部 問題回報處 #先讀置底/頂#" << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << Number[3] << RESET;
    cout << TEXT_ESC << 30 << COLOR_ESC << 0 << "m" << BoardName["PttNewhand"] << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "       ◎批踢踢新手客服中心 …〞非test板" << RESET;
    cout << endl;
}
void showArticleBanner() 
{
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 19 << "m" << "  【文章列表】                        " << RESET;
    cout << TEXT_ESC << 226 << COLOR_ESC << 19 << "m" << "  看板名稱                                     " << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "[←]離開  [→]閱讀  [Ctrl-P]發表文章  [d]刪除  [z]精華區  [i]看板資訊/設定  [h]說明" << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "   編號     日 期  作  者           文   章   標   題                                " << RESET;
}
void showArticleContent() 
{
    cout << endl; // 有推的文章
    cout << ESC << 0 << "m" << "     " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "79003" << RESET; //編號
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << " +" << RESET;
    cout << TEXT_ESC << 28 << COLOR_ESC << 0 << "m" << " 8" << RESET; //推文數
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "5/17" << RESET; //日期
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "Nymphadora       " << RESET; //作者(長度要固定)
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "[無言] 我的白痴姊姊" << RESET; //標題
    cout << endl;//沒推的文章
    cout << ESC << 0 << "m" << "     " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "79003" << RESET; //編號
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "      " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "5/17" << RESET; //日期
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "v6v69            " << RESET; //作者
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "[無言] 老弟的車" << RESET; //標題
    cout << endl;//刪除的文章
    cout << ESC << 0 << "m" << "     " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "79003" << RESET; //編號
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "      " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "5/17" << RESET; //日期
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "-                " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "(本文章已刪除) " << RESET; //標題
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "[royant399]" << RESET; //作者
    cout << endl;//板規
    cout << ESC << 0 << "m" << "     " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  *  " << RESET; //編號
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "      " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "7/01" << RESET; //日期
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "F7               " << RESET; //作者
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "[公告] 本版板規" << RESET; //標題
}
void showArticleFooter_0() 
{
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 30 << "m" << "  文章選讀  " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << " Guest " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "                                                                  " << RESET;
    cout << endl;
}
void showArticleFooter_1()
{
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 30 << "m" << "  文章選讀  " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << " Manager " << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (d)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "刪文" << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (c)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "新增文章" << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (e)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "編輯文章" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "                             " << RESET;
    cout << endl;
}
void showArticleFooter_2()
{
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 30 << "m" << "  文章選讀  " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << " User " << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (c)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "新增文章" << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (e)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "編輯文章" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "                                         " << RESET;
    cout << endl;
}
void showPostBanner() 
{
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 246 << "m" << " 作者 " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << "Stanley0928" << RESET;//作者
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << "                                                  " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 246 << "m" << " 看板 " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << "Gossiping" << RESET;//看板
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 246 << "m" << " 標題 " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << "[問卦] 有沒有文章網址的八卦?" << RESET;//標題
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << "                                                  " << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 246 << "m" << " 日期 " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << "05/16" << RESET;//日期
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << "                                                                         " << RESET;
    cout << endl;
}
void showPostContent()
{
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "123123456456789789" << RESET;//內文
    cout << endl;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "--" << RESET;
}
void showPostComment() 
{
    cout << endl;//推
    cout << ESC << 0 << "m" << "   推 " << RESET;
    cout << TEXT_ESC << 226 << COLOR_ESC << 0 << "m" << "tyrande     " << RESET;//留言者
    cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << ": " << RESET;
    cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << "123123123123123123                                            " << RESET;//留言
    cout << ESC << 0 << "m" << "05/16" << RESET;//日期
    cout << endl;//噓
    cout << TEXT_ESC << 1 << COLOR_ESC << 0 << "m" << "   → " << RESET;
    cout << TEXT_ESC << 226 << COLOR_ESC << 0 << "m" << "csyow       " << RESET;//留言者
    cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << ": " << RESET;
    cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << "123123456456456                                               " << RESET;//留言
    cout << ESC << 0 << "m" << "05/17" << RESET;//日期
}
void showPostFooter_0() 
{
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 30 << "m" << "  返回看板  " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << " Guest " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "                                                                  " << RESET;
    cout << endl;
}
void showPostFooter_1()
{
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 30 << "m" << "  返回看板  " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << " Manager " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "           " << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (D/delete)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "刪除回應" << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (P)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "推文" << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (S)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "噓文" << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (R)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "回覆" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "      " << RESET;
    cout << endl;
}
void showPostFooter_2()
{
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 30 << "m" << "  返回看板  " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << " User " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "                                  " << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (P)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "推文" << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (S)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "噓文" << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (R)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "回覆" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "      " << RESET;
    cout << endl;
}