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
    cout << TEXT_ESC << 255 << COLOR_ESC << 19 << "m" << "  �i�峹�C��j                        " << RESET;
    cout << TEXT_ESC << 226 << COLOR_ESC << 19 << "m" << "  " << RESET;
    cout << TEXT_ESC << 226 << COLOR_ESC << 19 << "m" << board.getName() << RESET;
    cout << TEXT_ESC << 226 << COLOR_ESC << 19 << "m" << "                                     " << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "   [��]���W        [��]���U        [��]/[Esc]���}        [��]/[return]��ܬݪO" << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "   �s��     �� ��  �@  ��           ��   ��   ��   �D                                " << RESET;
    //Content
    if (board.getPostNum() == 0) //�S��post��board
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
        int goodCount = 0; //�����ƶq
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
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << i+1 << RESET; //1���
        }
        else if (board.getPostVec()[i].getPostID() < 100) 
        {
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << i+1 << RESET; //2���
        }
        else if (board.getPostVec()[i].getPostID() < 1000) 
        {
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << i+1; //3���
        }
        if (goodCount == 0) //no goodCount
        {
            //�S�����峹
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "     " << RESET;
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << put_time(lctm, "%m/%d") << RESET; //���
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  " << RESET;
            int a_space = 17 - board.getPostVec()[i].getAuthor().length();
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << board.getPostVec()[i].getAuthor() << RESET; //�@��
            for (int k = 0 ; k < a_space ; k++) 
            {
                cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << " " << RESET;
            }
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << board.getPostVec()[i].getTitle() << RESET; //���D
        }
        else if (goodCount<10) //1���
        {
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << " + " << RESET;
            cout << TEXT_ESC << 28 << COLOR_ESC << 0 << "m" << goodCount << RESET; //�����
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << " " << RESET;
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << put_time(lctm, "%m/%d") << RESET; //���
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  " << RESET;
            int a_space = 17 - board.getPostVec()[i].getAuthor().length();
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << board.getPostVec()[i].getAuthor() << RESET; //�@��
            for (int k = 0 ; k < a_space ; k++) 
            {
                cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << " " << RESET;
            }
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << board.getPostVec()[i].getTitle() << RESET; //���D
        }
        else if (goodCount <100)//2���
        {
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << " +" << RESET;
            cout << TEXT_ESC << 28 << COLOR_ESC << 0 << "m" << goodCount << RESET; //�����
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << " " << RESET;
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << put_time(lctm, "%m/%d") << RESET; //���
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  " << RESET;
            int a_space = 17 - board.getPostVec()[i].getAuthor().length();
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << board.getPostVec()[i].getAuthor() << RESET; //�@��
            for (int k = 0 ; k < a_space ; k++) 
            {
                cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << " " << RESET;
            }
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << board.getPostVec()[i].getTitle() << RESET; //���D
        }
        else if (board.getPostVec()[i].isDeleted()) //deleted 
        {
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "     " << RESET;
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << put_time(lctm, "%m/%d") << RESET; //���
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  " << RESET;
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "-                " << RESET;//�@��
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << board.getPostVec()[i].getAuthor() << RESET; //��@����
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "(���峹�w�R��) [" << RESET; //���D
            cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << board.getPostVec()[i].getAuthor() << RESET; //�@��
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
    cout << TEXT_ESC << 19 << COLOR_ESC << 246 << "m" << " �@�� " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << post.getAuthor() << RESET;//�@��
    for (int i = 0 ; i < space1 ; i++) 
    {   
        cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    }
    cout << TEXT_ESC << 19 << COLOR_ESC << 246 << "m" << " �ݪO " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << boardName << RESET;//�ݪO
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << "   " << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 246 << "m" << " ���D " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << post.getTitle() << RESET;//���D
    for (int i = 0 ; i < space2 ; i++) 
    {   
        cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    }
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 246 << "m" << " ��� " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << put_time(lctm, "%y/%m/%d %H:%M:%S") << RESET;//���
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << "                                                           " << RESET;
    cout << endl;
    //Content
    cout << endl;
    for (int i = 0 ; i < post.getContent().size(); i++) 
    {
        cout << ESC << 0 << "m" << "   " << RESET;
        cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << post.getContent()[i] << RESET;//����
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
            cout << TEXT_ESC << 1 << COLOR_ESC << 0 << "m" << "   �� " << RESET;
            int space1 = 12 - post.getComment(i).GetUserID().length();
            cout << TEXT_ESC << 226 << COLOR_ESC << 0 << "m" << post.getComment(i).GetUserID() << RESET;//�d����
            for (int j = 0 ; j < space1 ; j++) 
            {
                cout << TEXT_ESC << 226 << COLOR_ESC << 0 << "m" << " " << RESET;
            }
            cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << ": " << RESET;
            cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << post.getComment(i).getContent() << RESET;//�d��
            int space2 = 60 - post.getComment(i).getContent().length();
            for (int j = 0 ; j < space2 ; j++) 
            {
                cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << " " << RESET;
            }
            cout << ESC << 0 << "m" << put_time(lctm, "%m/%d %H:%M") << RESET;//���
        }
        else if (post.getComment(i).getType() == 1) //good
        {
            cout << endl;//��
            cout << ESC << 0 << "m" << "   �� " << RESET;
            int space1 = 12 - post.getComment(i).GetUserID().length();
            cout << TEXT_ESC << 226 << COLOR_ESC << 0 << "m" << post.getComment(i).GetUserID() << RESET;//�d����
            for (int j = 0 ; j < space1 ; j++) 
            {
                cout << TEXT_ESC << 226 << COLOR_ESC << 0 << "m" << " " << RESET;
            }
            cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << ": " << RESET;
            cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << post.getComment(i).getContent() << RESET;//�d��
            int space2 = 60 - post.getComment(i).getContent().length();
            for (int j = 0 ; j < space2 ; j++) 
            {
                cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << " " << RESET;
            }
            cout << ESC << 0 << "m" << put_time(lctm, "%m/%d %H:%M") << RESET;//���
        }
        else if (post.getComment(i).getType() == 2) //bad
        {
            cout << endl;//�N
            cout << TEXT_ESC << 1 << COLOR_ESC << 0 << "m" << "   �N " << RESET;
            int space1 = 12 - post.getComment(i).GetUserID().length();
            cout << TEXT_ESC << 226 << COLOR_ESC << 0 << "m" << post.getComment(i).GetUserID() << RESET;//�d����
            for (int j = 0 ; j < space1 ; j++) 
            {
                cout << TEXT_ESC << 226 << COLOR_ESC << 0 << "m" << " " << RESET;
            }
            cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << ": " << RESET;
            cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << post.getComment(i).getContent() << RESET;//�d��
            int space2 = 60 - post.getComment(i).getContent().length();
            for (int j = 0 ; j < space2 ; j++) 
            {
                cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << " " << RESET;
            }
            cout << ESC << 0 << "m" << put_time(lctm, "%m/%d %H:%M") << RESET;//���
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
    std::cout << TEXT_ESC << 255 << COLOR_ESC << 37 << "m" << "      �ݪO EarthDay2021      " << RESET;
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
    std::cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  ���V�۵M          " << RESET;
    std::cout << ESC << 2 << "m" << "     " << RESET;
    std::cout << ESC << 37 << "m" << "     " << RESET;
    std::cout << ESC << 2 << "m" << "   " << RESET;
    std::cout << ESC << 37 << "m" << "     " << RESET;
    std::cout << ESC << 2 << "m" << " " << RESET;
    std::cout << ESC << 37 << "m" << "  " << RESET;
    std::cout << ESC << 2 << "m" << "  " << RESET;
    std::cout << ESC << 37 << "m" << "       " << RESET;
    std::cout << ESC << 2 << "m" << "                   " << RESET;
    std::cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "        �R�@�a�y" << RESET;
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
    std::cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "      �÷R����     " << RESET;
    std::cout << ESC << 2 << "m" << "      " << RESET;
    std::cout << ESC << 37 << "m" << "                  " << RESET;
    std::cout << ESC << 2 << "m" << "                           " << RESET;
    std::cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "   �qPTT�}�l" << RESET;
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
    cout << TEXT_ESC << 255 << COLOR_ESC << 19 << "m" << "  �i�ݪO�C��j                  " << RESET;
    cout << TEXT_ESC << 226 << COLOR_ESC << 19 << "m" << "      �����~�{                                   " << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "   [��]���W [��]���U    [m]Mail    [��]/[Esc]���}        [��]/[return]��ܬݪO" << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "   �s��     ��   �O                 ��   ��   ��   �z                                " << RESET;
    cout << endl;
}
void showBoardFooter_0() //guest
{
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 30 << "m" << "  ��ܬݪO  " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << " Guest" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "                                                                   " << RESET;
    cout << endl;
}
void showBoardFooter_1() //manager
{
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 30 << "m" << "  ��ܬݪO  " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << " Manager" << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (c)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "�إ߬ݪO" << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (d/delete)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "�R���ݪO" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "                                " << RESET;
    cout << endl;
}
void showBoardFooter_2() //user
{
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 30 << "m" << "  ��ܬݪO  " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << " User " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "                                                                   " << RESET;
    cout << endl;
}
void showBoardContent() 
{
    map<int, string>Number = { {0,"    HOT"}, {1,"      1"},{2,"      2"},{3,"      3"},{4,"      4"},{5,"      5"},{6,"      6"},{7,"      7"},{8,"      8"},{9,"      9"},{10,"      10"},{100,"    �z!"} };
    map<string, string>BoardName = { {"SYSOP","     SYSOP          "},{"ID_Problem","     ID_Problem     "},{"PttNewhand","     PttNewhand     "} };
    map<char, int>TypeColor = { {'y',136} ,{'p',5} ,{'g',28} ,{'w',255} ,{'r',196} };
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << Number[1] << RESET;
    cout << TEXT_ESC << 30 << COLOR_ESC << 0 << "m" << BoardName["SYSOP"] << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "       ���D���Ȱ��D�Ь�AskBoard�O/�s��O" << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << Number[2] << RESET;
    cout << TEXT_ESC << 30 << COLOR_ESC << 0 << "m" << BoardName["ID_Problem"] << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "       ���b���� ���D�^���B #��Ū�m��/��#" << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << Number[3] << RESET;
    cout << TEXT_ESC << 30 << COLOR_ESC << 0 << "m" << BoardName["PttNewhand"] << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "       ������s��ȪA���� �K���Dtest�O" << RESET;
    cout << endl;
}
void showArticleBanner() 
{
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 19 << "m" << "  �i�峹�C��j                        " << RESET;
    cout << TEXT_ESC << 226 << COLOR_ESC << 19 << "m" << "  �ݪO�W��                                     " << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "[��]���}  [��]�\Ū  [Ctrl-P]�o��峹  [d]�R��  [z]��ذ�  [i]�ݪO��T/�]�w  [h]����" << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "   �s��     �� ��  �@  ��           ��   ��   ��   �D                                " << RESET;
}
void showArticleContent() 
{
    cout << endl; // �������峹
    cout << ESC << 0 << "m" << "     " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "79003" << RESET; //�s��
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << " +" << RESET;
    cout << TEXT_ESC << 28 << COLOR_ESC << 0 << "m" << " 8" << RESET; //�����
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "5/17" << RESET; //���
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "Nymphadora       " << RESET; //�@��(���׭n�T�w)
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "[�L��] �ڪ��շ��n�n" << RESET; //���D
    cout << endl;//�S�����峹
    cout << ESC << 0 << "m" << "     " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "79003" << RESET; //�s��
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "      " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "5/17" << RESET; //���
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "v6v69            " << RESET; //�@��
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "[�L��] �ѧ̪���" << RESET; //���D
    cout << endl;//�R�����峹
    cout << ESC << 0 << "m" << "     " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "79003" << RESET; //�s��
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "      " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "5/17" << RESET; //���
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "-                " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "(���峹�w�R��) " << RESET; //���D
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "[royant399]" << RESET; //�@��
    cout << endl;//�O�W
    cout << ESC << 0 << "m" << "     " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  *  " << RESET; //�s��
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "      " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "7/01" << RESET; //���
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "  " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "F7               " << RESET; //�@��
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "[���i] �����O�W" << RESET; //���D
}
void showArticleFooter_0() 
{
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 30 << "m" << "  �峹��Ū  " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << " Guest " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "                                                                  " << RESET;
    cout << endl;
}
void showArticleFooter_1()
{
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 30 << "m" << "  �峹��Ū  " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << " Manager " << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (d)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "�R��" << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (c)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "�s�W�峹" << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (e)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "�s��峹" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "                             " << RESET;
    cout << endl;
}
void showArticleFooter_2()
{
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 30 << "m" << "  �峹��Ū  " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << " User " << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (c)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "�s�W�峹" << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (e)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "�s��峹" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "                                         " << RESET;
    cout << endl;
}
void showPostBanner() 
{
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 246 << "m" << " �@�� " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << "Stanley0928" << RESET;//�@��
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << "                                                  " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 246 << "m" << " �ݪO " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << "Gossiping" << RESET;//�ݪO
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 246 << "m" << " ���D " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << "[�ݨ�] ���S���峹���}���K��?" << RESET;//���D
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << "                                                  " << RESET;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 246 << "m" << " ��� " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << " " << RESET;
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << "05/16" << RESET;//���
    cout << TEXT_ESC << 246 << COLOR_ESC << 19 << "m" << "                                                                         " << RESET;
    cout << endl;
}
void showPostContent()
{
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "123123456456789789" << RESET;//����
    cout << endl;
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 255 << COLOR_ESC << 0 << "m" << "--" << RESET;
}
void showPostComment() 
{
    cout << endl;//��
    cout << ESC << 0 << "m" << "   �� " << RESET;
    cout << TEXT_ESC << 226 << COLOR_ESC << 0 << "m" << "tyrande     " << RESET;//�d����
    cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << ": " << RESET;
    cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << "123123123123123123                                            " << RESET;//�d��
    cout << ESC << 0 << "m" << "05/16" << RESET;//���
    cout << endl;//�N
    cout << TEXT_ESC << 1 << COLOR_ESC << 0 << "m" << "   �� " << RESET;
    cout << TEXT_ESC << 226 << COLOR_ESC << 0 << "m" << "csyow       " << RESET;//�d����
    cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << ": " << RESET;
    cout << TEXT_ESC << 100 << COLOR_ESC << 0 << "m" << "123123456456456                                               " << RESET;//�d��
    cout << ESC << 0 << "m" << "05/17" << RESET;//���
}
void showPostFooter_0() 
{
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 30 << "m" << "  ��^�ݪO  " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << " Guest " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "                                                                  " << RESET;
    cout << endl;
}
void showPostFooter_1()
{
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 30 << "m" << "  ��^�ݪO  " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << " Manager " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "           " << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (D/delete)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "�R���^��" << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (P)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "����" << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (S)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "�N��" << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (R)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "�^��" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "      " << RESET;
    cout << endl;
}
void showPostFooter_2()
{
    cout << endl;
    cout << ESC << 0 << "m" << "   " << RESET;
    cout << TEXT_ESC << 19 << COLOR_ESC << 30 << "m" << "  ��^�ݪO  " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << " User " << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "                                  " << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (P)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "����" << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (S)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "�N��" << RESET;
    cout << TEXT_ESC << 88 << COLOR_ESC << 255 << "m" << "  (R)" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "�^��" << RESET;
    cout << TEXT_ESC << 0 << COLOR_ESC << 255 << "m" << "      " << RESET;
    cout << endl;
}