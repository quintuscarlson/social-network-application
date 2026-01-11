#ifndef SOCIALNETWORKWINDOW_H
#define SOCIALNETWORKWINDOW_H

#include <QMainWindow>
#include "network.h"
#include "user.h"
#include "post.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class SocialNetworkWindow;
}
QT_END_NAMESPACE

class SocialNetworkWindow : public QMainWindow
{
    Q_OBJECT

public:
    SocialNetworkWindow(QWidget *parent = nullptr);
    ~SocialNetworkWindow();
    void loginButtonClick();
    void backButtonClick();
    void addFriend();
    void addPost();
    void Post();
    void displayPage(User* curUser);
    void seeReactions();
    void b1Click();
    void b2Click();
    void b3Click();
    void b4Click();
    void b5Click();
    void rDoneClick();
    void addReactionClick();
    void b11Click();
    void b22Click();
    void b33Click();
    void b44Click();
    void b55Click();
    void likeButtonClick();
    void heartButtonClick();
    void laughButtonClick();

private:
    Ui::SocialNetworkWindow *ui;
    User* loggedInUser;
    User* userDisplayed;
    Network* currentNetwork;
    class Post* curPost;

};
#endif // SOCIALNETWORKWINDOW_H
