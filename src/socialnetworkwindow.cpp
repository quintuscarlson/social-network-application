#include "socialnetworkwindow.h"
#include "ui_socialnetworkwindow.h"

SocialNetworkWindow::SocialNetworkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SocialNetworkWindow)
{
    ui->setupUi(this);
    ui->addFriendButton->hide();
    ui->postButton->hide();
    ui->seeReactionsButton->hide();
    ui->addReactionButton->hide();
    ui->invalidUserLabel->hide();
    ui->profileLabel->hide();
    ui->postsLabel->hide();
    ui->postTextEdit->hide();
    ui->backToOwnProfile->hide();
    ui->recentPostsLabel->hide();
    ui->friendsTable->hide();
    ui->suggestTable->hide();
    ui->addPostButton->hide();
    ui->choosePostLabel->hide();
    ui->button1->hide();
    ui->button2->hide();
    ui->button3->hide();
    ui->button4->hide();
    ui->button5->hide();
    ui->button11->hide();
    ui->button22->hide();
    ui->button33->hide();
    ui->button44->hide();
    ui->button55->hide();
    ui->chooseReactionLabel->hide();
    ui->reactionsDoneButton->hide();
    ui->likeButton->hide();
    ui->heartButton->hide();
    ui->laughButton->hide();
    ui->reactionsLabel->hide();
    currentNetwork = new Network();
    currentNetwork->readUsers("users.txt");
    currentNetwork->readPosts("posts.txt");
    connect(ui->loginPushButton, &QPushButton::clicked, this, &SocialNetworkWindow::loginButtonClick);
    connect(ui->backToOwnProfile, &QPushButton::clicked, this, &SocialNetworkWindow::backButtonClick);
    connect(ui->addFriendButton, &QPushButton::clicked, this, &SocialNetworkWindow::addFriend);
    connect(ui->addPostButton, &QPushButton::clicked, this, &SocialNetworkWindow::addPost);
    connect(ui->postButton, &QPushButton::clicked, this, &SocialNetworkWindow::Post);
    connect(ui->seeReactionsButton, &QPushButton::clicked, this, &SocialNetworkWindow::seeReactions);
    connect(ui->button1, &QPushButton::clicked, this, &SocialNetworkWindow::b1Click);
    connect(ui->button2, &QPushButton::clicked, this, &SocialNetworkWindow::b2Click);
    connect(ui->button3, &QPushButton::clicked, this, &SocialNetworkWindow::b3Click);
    connect(ui->button4, &QPushButton::clicked, this, &SocialNetworkWindow::b4Click);
    connect(ui->button5, &QPushButton::clicked, this, &SocialNetworkWindow::b5Click);
    connect(ui->reactionsDoneButton, &QPushButton::clicked, this, &SocialNetworkWindow::rDoneClick);
    connect(ui->addReactionButton, &QPushButton::clicked, this, &SocialNetworkWindow::addReactionClick);
    connect(ui->button11, &QPushButton::clicked, this, &SocialNetworkWindow::b11Click);
    connect(ui->button22, &QPushButton::clicked, this, &SocialNetworkWindow::b22Click);
    connect(ui->button33, &QPushButton::clicked, this, &SocialNetworkWindow::b33Click);
    connect(ui->button44, &QPushButton::clicked, this, &SocialNetworkWindow::b44Click);
    connect(ui->button55, &QPushButton::clicked, this, &SocialNetworkWindow::b55Click);
    connect(ui->likeButton, &QPushButton::clicked, this, &SocialNetworkWindow::likeButtonClick);
    connect(ui->heartButton, &QPushButton::clicked, this, &SocialNetworkWindow::heartButtonClick);
    connect(ui->laughButton, &QPushButton::clicked, this, &SocialNetworkWindow::laughButtonClick);
}

SocialNetworkWindow::~SocialNetworkWindow()
{
    delete ui;
}


void SocialNetworkWindow::loginButtonClick(){
    QString inputText = ui->loginTextEdit->toPlainText().trimmed();
    std::vector<User*> curUsers = currentNetwork->getUsers();
    bool check = false;

    for(User* cur : curUsers){
        if(cur->getName()==inputText){
            check = true;
            loggedInUser = cur;
        }
    }

    if(check){
        ui->enterUserLabel->hide();
        ui->loginPushButton->hide();
        ui->loginTextEdit->hide();
        ui->invalidUserLabel->hide();

        displayPage(loggedInUser);


    }
    else{
        ui->invalidUserLabel->show();

    }


}

void SocialNetworkWindow::displayPage(User* curUser){
    ui->backToOwnProfile->hide();
    ui->addFriendButton->hide();
    ui->suggestTable->hide();
    ui->addReactionButton->hide();
    ui->addPostButton->show();
    ui->seeReactionsButton->hide();
    ui->postsLabel->show();
    ui->reactionsDoneButton->hide();
    ui->reactionsLabel->hide();
    userDisplayed = curUser;

    bool ownProfile = false;

    if(curUser==loggedInUser){
        ui->profileLabel->setText("My Profile");
        ui->profileLabel->setAlignment(Qt::AlignCenter);
        ui->profileLabel->show();
        ownProfile = true;
    }
    else{
        ui->profileLabel->setText(QString::fromStdString(curUser->getName()) + ("'s Profile"));
        ui->profileLabel->setAlignment(Qt::AlignCenter);
        ui->profileLabel->show();
        ui->backToOwnProfile->show();
        ui->addFriendButton->show();
    }

    if(ownProfile){
        ui->recentPostsLabel->setText(QString::fromStdString(curUser->getPostsString(5, false)));
        ui->seeReactionsButton->show();
    }
    else{
        ui->recentPostsLabel->setText(QString::fromStdString(curUser->getPostsString(5, true)));
        ui->addReactionButton->show();
    }

    ui->recentPostsLabel->show();

    std::set<int> curFriendIDs = curUser->getFriends();
    ui->friendsTable->setColumnCount(1);
    ui->friendsTable->setRowCount(curFriendIDs.size()+1);
    ui->friendsTable->setItem(0, 0, new QTableWidgetItem("FRIENDS LIST:"));

    int row = 1;

    for(int i: curFriendIDs){
        User* c = currentNetwork->getUser(i);

        QPushButton *button = new QPushButton(QString::fromStdString(c->getName()));

        ui->friendsTable->setCellWidget(row, 0, button);

        connect(button, &QPushButton::clicked, this, [=]() {
            displayPage(currentNetwork->getUser(i));
        });



        row++;
    }

    ui->friendsTable->setColumnWidth(0, 200);
    ui->friendsTable->show();

    if(ownProfile){
    int s;
    std::vector<int> curSFriends = currentNetwork->suggestFriends(curUser->getId(), s);
    ui->suggestTable->setColumnCount(2);
    ui->suggestTable->setRowCount(curSFriends.size()+1);
    ui->suggestTable->setItem(0, 0, new QTableWidgetItem("Suggested Friends:"));

    int row2 = 1;

    for(int j: curSFriends){
        User* c = currentNetwork->getUser(j);

        QPushButton *button = new QPushButton("Add Friend");
        button->setStyleSheet("background-color: blue; color: white;");

        ui->suggestTable->setCellWidget(row2, 1, button);
        ui->suggestTable->setItem(row2, 0, new QTableWidgetItem(QString::fromStdString(c->getName())));

        connect(button, &QPushButton::clicked, this, [=]() {
            userDisplayed = c;
            addFriend();
        });

        row2++;
    }

    ui->suggestTable->setColumnWidth(0, 150);
    ui->suggestTable->setColumnWidth(1, 150);
    ui->suggestTable->show();}


}

void SocialNetworkWindow::backButtonClick(){
    displayPage(loggedInUser);
}

void SocialNetworkWindow::addFriend(){
    currentNetwork->addConnection(loggedInUser->getName(), userDisplayed->getName());
    currentNetwork->writeUsers("users.txt");
    displayPage(userDisplayed);
}

void SocialNetworkWindow::Post(){

    QString iText = ui->postTextEdit->toPlainText().trimmed();
    std::vector<std::set<int>> temp;

    if(userDisplayed==loggedInUser){
        currentNetwork->addPost(userDisplayed->getId(), iText.toStdString(), false, loggedInUser->getName(), true, temp);
    }else{
        currentNetwork->addPost(userDisplayed->getId(), iText.toStdString(), true, loggedInUser->getName(), true, temp);
    }

    currentNetwork->writePosts("posts.txt");

    ui->addPostButton->show();
    ui->postButton->hide();
    ui->postTextEdit->hide();
    displayPage(userDisplayed);

}

void SocialNetworkWindow::addPost(){
    ui->postTextEdit->show();
    ui->recentPostsLabel->hide();
    ui->addPostButton->hide();
    ui->postButton->show();
    ui->postTextEdit->clear();
}

void SocialNetworkWindow::seeReactions(){
    ui->choosePostLabel->show();
    std::vector<class Post*> curM = loggedInUser->getPosts();
    if(curM.size() >= 1){
        ui->button1->show();
    }
    if(curM.size() >= 2){
        ui->button2->show();
    }
    if(curM.size() >= 3){
        ui->button3->show();
    }
    if(curM.size() >= 4){
        ui->button4->show();
    }
    if(curM.size() >= 5){
        ui->button5->show();
    }

}

void SocialNetworkWindow::b1Click(){
    ui->choosePostLabel->hide();
    ui->button1->hide();
    ui->button2->hide();
    ui->button3->hide();
    ui->button4->hide();
    ui->button5->hide();
    ui->reactionsLabel->show();
    ui->reactionsDoneButton->show();

    std::vector<class Post*> curPList = loggedInUser->getPosts();

    class Post* curP;

    if(curPList.size() > 4){
        curP =  curPList[curPList.size()-5];
    }
    else{
        curP = curPList[0];
    }

    std::string result;


    std::set<int> current = curP->getLikes();
    result += "👍:  ";

    for(int i : current){
        result += currentNetwork->getUser(i)->getName() + "  ";
    }
    result += "\n\n";

    current = curP->getHearts();
    result += "❤️:  ";

    for(int i : current){
        result += currentNetwork->getUser(i)->getName() + "  ";
    }
    result += "\n\n";

    current = curP->getLaughs();
    result += "😂:  ";

    for(int i : current){
        result += currentNetwork->getUser(i)->getName() + "  ";
    }


    ui->reactionsLabel->setText(QString::fromStdString(result));
    ui->reactionsLabel->setWordWrap(true);
    ui->reactionsLabel->show();

}

void SocialNetworkWindow::b2Click(){
    ui->choosePostLabel->hide();
    ui->button1->hide();
    ui->button2->hide();
    ui->button3->hide();
    ui->button4->hide();
    ui->button5->hide();
    ui->reactionsLabel->show();
    ui->reactionsDoneButton->show();

    std::vector<class Post*> curPList = loggedInUser->getPosts();

    class Post* curP;

    if(curPList.size() > 3){
        curP =  curPList[curPList.size()-4];
    }
    else{
        curP = curPList[1];
    }

    std::string result;


    std::set<int> current = curP->getLikes();
    result += "👍:  ";

    for(int i : current){
        result += currentNetwork->getUser(i)->getName() + "  ";
    }
    result += "\n\n";

    current = curP->getHearts();
    result += "❤️:  ";

    for(int i : current){
        result += currentNetwork->getUser(i)->getName() + "  ";
    }
    result += "\n\n";

    current = curP->getLaughs();
    result += "😂:  ";

    for(int i : current){
        result += currentNetwork->getUser(i)->getName() + "  ";
    }


    ui->reactionsLabel->setText(QString::fromStdString(result));
    ui->reactionsLabel->setWordWrap(true);
    ui->reactionsLabel->show();
}

void SocialNetworkWindow::b3Click(){
    ui->choosePostLabel->hide();
    ui->button1->hide();
    ui->button2->hide();
    ui->button3->hide();
    ui->button4->hide();
    ui->button5->hide();
    ui->reactionsDoneButton->show();

    std::vector<class Post*> curPList = loggedInUser->getPosts();

    class Post* curP;

    if(curPList.size() > 2){
        curP =  curPList[curPList.size()-3];
    }
    else{
        curP = curPList[2];
    }


    std::string result;


    std::set<int> current = curP->getLikes();
    result += "👍:  ";

    for(int i : current){
        result += currentNetwork->getUser(i)->getName() + "  ";
    }
    result += "\n\n";

    current = curP->getHearts();
    result += "❤️:  ";

    for(int i : current){
        result += currentNetwork->getUser(i)->getName() + "  ";
    }
    result += "\n\n";

    current = curP->getLaughs();
    result += "😂:  ";

    for(int i : current){
        result += currentNetwork->getUser(i)->getName() + "  ";
    }


    ui->reactionsLabel->setText(QString::fromStdString(result));
    ui->reactionsLabel->setWordWrap(true);
    ui->reactionsLabel->show();
}

void SocialNetworkWindow::b4Click(){
    ui->choosePostLabel->hide();
    ui->button1->hide();
    ui->button2->hide();
    ui->button3->hide();
    ui->button4->hide();
    ui->button5->hide();
    ui->reactionsDoneButton->show();
    ui->reactionsLabel->show();

    std::vector<class Post*> curPList = loggedInUser->getPosts();

    class Post* curP;

    if(curPList.size() > 1){
        curP =  curPList[curPList.size()-2];
    }
    else{
        curP = curPList[3];
    }


    std::string result;


    std::set<int> current = curP->getLikes();
    result += "👍:  ";

    for(int i : current){
        result += currentNetwork->getUser(i)->getName() + "  ";
    }
    result += "\n\n";

    current = curP->getHearts();
    result += "❤️:  ";

    for(int i : current){
        result += currentNetwork->getUser(i)->getName() + "  ";
    }
    result += "\n\n";

    current = curP->getLaughs();
    result += "😂:  ";

    for(int i : current){
        result += currentNetwork->getUser(i)->getName() + "  ";
    }


    ui->reactionsLabel->setText(QString::fromStdString(result));
    ui->reactionsLabel->setWordWrap(true);
    ui->reactionsLabel->show();
}

void SocialNetworkWindow::b5Click(){
    ui->choosePostLabel->hide();
    ui->button1->hide();
    ui->button2->hide();
    ui->button3->hide();
    ui->button4->hide();
    ui->button5->hide();
    ui->reactionsLabel->show();
    ui->reactionsDoneButton->show();

    std::vector<class Post*> curPList = loggedInUser->getPosts();

    class Post* curP;

    if(curPList.size() > 0){
        curP =  curPList[curPList.size()-1];
    }
    else{
        curP = curPList[4];
    }


    std::string result;


    std::set<int> current = curP->getLikes();
    result += "👍:  ";

    for(int i : current){
        result += currentNetwork->getUser(i)->getName() + "  ";
    }
    result += "\n\n";

    current = curP->getHearts();
    result += "❤️:  ";

    for(int i : current){
        result += currentNetwork->getUser(i)->getName() + "  ";
    }
    result += "\n\n";

    current = curP->getLaughs();
    result += "😂:  ";

    for(int i : current){
        result += currentNetwork->getUser(i)->getName() + "  ";
    }


    ui->reactionsLabel->setText(QString::fromStdString(result));
    ui->reactionsLabel->setWordWrap(true);
    ui->reactionsLabel->show();
}


void SocialNetworkWindow::rDoneClick(){
    ui->reactionsLabel->hide();
    ui->reactionsDoneButton->hide();
}


void SocialNetworkWindow::addReactionClick(){
    ui->choosePostLabel->show();
    std::vector<class Post*> curM = userDisplayed->getPosts();
    if(curM.size() >= 1){
        ui->button11->show();
    }
    if(curM.size() >= 2){
        ui->button22->show();
    }
    if(curM.size() >= 3){
        ui->button33->show();
    }
    if(curM.size() >= 4){
        ui->button44->show();
    }
    if(curM.size() >= 5){
        ui->button55->show();
    }

}

void SocialNetworkWindow::b11Click(){
    ui->choosePostLabel->hide();
    ui->button11->hide();
    ui->button22->hide();
    ui->button33->hide();
    ui->button44->hide();
    ui->button55->hide();
    ui->chooseReactionLabel->show();
    ui->likeButton->show();
    ui->heartButton->show();
    ui->laughButton->show();

    std::vector<class Post*> curPList = userDisplayed->getPosts();

    if(curPList.size() < 5){
        curPost = curPList[0];
    }else{
        curPost =  curPList[curPList.size()-5];
    }

}

void SocialNetworkWindow::b22Click(){
    ui->choosePostLabel->hide();
    ui->button11->hide();
    ui->button22->hide();
    ui->button33->hide();
    ui->button44->hide();
    ui->button55->hide();
    ui->chooseReactionLabel->show();
    ui->likeButton->show();
    ui->heartButton->show();
    ui->laughButton->show();

    std::vector<class Post*> curPList = userDisplayed->getPosts();

    if(curPList.size() < 5){
        curPost = curPList[1];
    }else{
        curPost =  curPList[curPList.size()-4];
    }


}

void SocialNetworkWindow::b33Click(){
    ui->choosePostLabel->hide();
    ui->button11->hide();
    ui->button22->hide();
    ui->button33->hide();
    ui->button44->hide();
    ui->button55->hide();
    ui->chooseReactionLabel->show();
    ui->likeButton->show();
    ui->heartButton->show();
    ui->laughButton->show();


    std::vector<class Post*> curPList = userDisplayed->getPosts();

    if(curPList.size() < 5){
        curPost = curPList[2];
    }else{
        curPost =  curPList[curPList.size()-3];
    }


}

void SocialNetworkWindow::b44Click(){
    ui->choosePostLabel->hide();
    ui->button11->hide();
    ui->button22->hide();
    ui->button33->hide();
    ui->button44->hide();
    ui->button55->hide();
    ui->chooseReactionLabel->show();
    ui->likeButton->show();
    ui->heartButton->show();
    ui->laughButton->show();

    std::vector<class Post*> curPList = userDisplayed->getPosts();

    if(curPList.size() < 5){
        curPost = curPList[3];
    }else{
        curPost =  curPList[curPList.size()-2];
    }

}

void SocialNetworkWindow::b55Click(){
    ui->choosePostLabel->hide();
    ui->button11->hide();
    ui->button22->hide();
    ui->button33->hide();
    ui->button44->hide();
    ui->button55->hide();
    ui->chooseReactionLabel->show();
    ui->likeButton->show();
    ui->heartButton->show();
    ui->laughButton->show();

    std::vector<class Post*> curPList = userDisplayed->getPosts();

    curPost = curPList[curPList.size()-1];


}


void SocialNetworkWindow::likeButtonClick(){
    ui->likeButton->hide();
    ui->heartButton->hide();
    ui->laughButton->hide();
    ui->chooseReactionLabel->hide();

    curPost->addReaction(0, loggedInUser->getId());
    currentNetwork->writePosts("posts.txt");
    displayPage(userDisplayed);

}

void SocialNetworkWindow::heartButtonClick(){
    ui->likeButton->hide();
    ui->heartButton->hide();
    ui->laughButton->hide();
    ui->chooseReactionLabel->hide();

    curPost->addReaction(1, loggedInUser->getId());
    currentNetwork->writePosts("posts.txt");
    displayPage(userDisplayed);
}

void SocialNetworkWindow::laughButtonClick(){
    ui->likeButton->hide();
    ui->heartButton->hide();
    ui->laughButton->hide();
    ui->chooseReactionLabel->hide();

    curPost->addReaction(2, loggedInUser->getId());
    currentNetwork->writePosts("posts.txt");
    displayPage(userDisplayed);
}
