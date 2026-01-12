#include "network.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <queue>

Network::Network() {}  // Default constructor

// Helper function: reads next non-empty line from a file
bool nextNonEmptyLine(std::ifstream& in, std::string& line) {
    while (std::getline(in, line)) {
        if (!line.empty()) return true;
    }
    return false;
}

// Adds a user to the network
void Network::addUser(User* user) {
    users_.push_back(user);
}

// Returns a pointer to a user by ID, or nullptr if not found
User* Network::getUser(int id) {
    for (User* cur : users_) {
        if (cur->getId() == id) {
            return cur;
        }
    }
    return nullptr;
}

// Adds a connection between two users by name
// Returns -1 if either user does not exist, 0 on success
int Network::addConnection(std::string s1, std::string s2) {
    bool check1 = false;
    bool check2 = false;

    for (User* cur : users_) {
        if (cur->getName() == s1) check1 = true;
        if (cur->getName() == s2) check2 = true;
    }

    if (!check1 || !check2) return -1;

    User* user1 = nullptr;
    User* user2 = nullptr;
    int userId1 = -1, userId2 = -1;

    for (User* cur : users_) {
        if (cur->getName() == s1) { userId1 = cur->getId(); user1 = cur; }
        if (cur->getName() == s2) { userId2 = cur->getId(); user2 = cur; }
    }

    user1->addFriend(userId2);
    user2->addFriend(userId1);

    return 0;
}

// Deletes a connection between two users by name
int Network::deleteConnection(std::string s1, std::string s2) {
    bool check1 = false;
    bool check2 = false;

    for (User* cur : users_) {
        if (cur->getName() == s1) check1 = true;
        if (cur->getName() == s2) check2 = true;
    }

    if (!check1 || !check2) return -1;

    User* user1 = nullptr;
    User* user2 = nullptr;
    int userId1 = -1, userId2 = -1;

    for (User* cur : users_) {
        if (cur->getName() == s1) { userId1 = cur->getId(); user1 = cur; }
        if (cur->getName() == s2) { userId2 = cur->getId(); user2 = cur; }
    }

    user1->deleteFriend(userId2);
    user2->deleteFriend(userId1);

    return 0;
}

// Returns the ID of a user by name, -1 if not found
int Network::getId(std::string name) {
    for (User* cur : users_) {
        if (cur->getName() == name) return cur->getId();
    }
    return -1;
}

// Returns total number of users in the network
int Network::numUsers() {
    return users_.size();
}

// Reads users from a file and populates the network
int Network::readUsers(const char* fname) {
    std::string myline;
    std::ifstream myfile(fname);

    getline(myfile, myline);  // skip first line (number of users)

    while (getline(myfile, myline)) {
        int curId = std::stoi(myline);

        getline(myfile, myline);
        std::string curName = myline;
        curName.erase(std::remove(curName.begin(), curName.end(), '\t'), curName.end());

        getline(myfile, myline);
        int curYear = std::stoi(myline);

        getline(myfile, myline);
        int curZip = std::stoi(myline);

        getline(myfile, myline);
        std::stringstream ss(myline);
        std::set<int> curFriends;
        int friendId;

        while (ss >> friendId) {
            curFriends.insert(friendId);
        }

        User* curUser = new User(curId, curName, curYear, curZip, curFriends);
        users_.push_back(curUser);
    }
    return 0;
}

// Writes user data to a file
int Network::writeUsers(const char* fname) {
    std::ofstream myfile(fname);
    myfile << numUsers() << "\n";

    for (User* cur : users_) {
        myfile << cur->getId() << "\n";
        myfile << "\t" << cur->getName() << "\n";
        myfile << "\t" << cur->getYear() << "\n";
        myfile << "\t" << cur->getZip() << "\n";

        std::set<int> curFriends = cur->getFriends();
        myfile << "\t";
        for (int cur2 : curFriends) myfile << cur2 << " ";
        myfile << "\n";
    }

    return 0;
}

// Finds the shortest path between two users using BFS
std::vector<int> Network::shortestPath(int from, int to) {
    int vSize = users_.size();
    std::vector<bool> visited(vSize, false);
    std::vector<int> connection(vSize, -1);
    std::queue<int> q;

    visited[from] = true;
    q.push(from);

    while (!q.empty()) {
        int cur = q.front(); q.pop();
        std::set<int> friends = getUser(cur)->getFriends();

        for (int i : friends) {
            if (!visited[i]) {
                visited[i] = true;
                connection[i] = cur;
                q.push(i);
            }
        }
    }

    std::vector<int> result;
    int path = to;

    while (connection[path] != -1) {
        result.push_back(path);
        path = connection[path];
    }
    result.push_back(from);
    std::reverse(result.begin(), result.end());
    return result;
}

// Returns a path to a user exactly 'distance' away using BFS
std::vector<int> Network::distanceUser(int from, int& to, int distance) {
    int vSize = users_.size();
    std::vector<bool> visited(vSize, false);
    std::vector<int> dist(vSize, -1);
    std::queue<int> q;

    visited[from] = true;
    dist[from] = 0;
    q.push(from);

    while (!q.empty()) {
        int cur = q.front(); q.pop();
        std::set<int> friends = getUser(cur)->getFriends();

        for (int i : friends) {
            if (!visited[i]) {
                visited[i] = true;
                dist[i] = dist[cur] + 1;
                q.push(i);

                if (dist[i] == distance) {
                    to = i;
                    return shortestPath(from, to);
                }
            }
        }
    }

    to = -1;
    return std::vector<int>();
}

// Suggests friends for a user based on friends-of-friends and mutual connections
std::vector<int> Network::suggestFriends(int who, int& score) {
    int vSize = users_.size();
    std::vector<bool> visited(vSize, false);
    std::vector<int> dist(vSize, -1);
    std::queue<int> q;

    visited[who] = true;
    dist[who] = 0;
    q.push(who);

    while (!q.empty()) {
        int cur = q.front(); q.pop();
        std::set<int> friends = getUser(cur)->getFriends();

        for (int i : friends) {
            if (!visited[i]) {
                visited[i] = true;
                dist[i] = dist[cur] + 1;
                q.push(i);
            }
        }
    }

    std::vector<int> potentialFriends;
    std::vector<int> scores;
    int maxScore = 0;

    // Collect users at distance 2 (friends-of-friends)
    for (int j = 0; j < dist.size(); j++) {
        if (dist[j] == 2) potentialFriends.push_back(users_[j]->getId());
    }

    // Score potential friends based on mutual friends
    for (int i : potentialFriends) {
        int s = 0;
        std::set<int> curFriends = getUser(i)->getFriends();
        std::set<int> whoFriends = getUser(who)->getFriends();
        for (int j : curFriends) {
            for (int k : whoFriends) {
                if (j == k) s++;
            }
        }
        scores.push_back(s);
        if (s > maxScore) maxScore = s;
    }

    // Return best matches
    std::vector<int> bestMatches;
    for (int g = 0; g < scores.size(); g++) {
        if (scores[g] == maxScore) bestMatches.push_back(potentialFriends[g]);
    }

    score = maxScore;
    return bestMatches;
}

// Returns all connected groups in the network using DFS
std::vector<std::vector<int>> Network::groups() {
    int vSize = users_.size();
    std::vector<bool> visited(vSize, false);
    std::vector<std::vector<int>> result;

    for (int j = 0; j < users_.size(); j++) {
        if (!visited[j]) {
            std::vector<int> comp;
            dfs(j, visited, comp);
            result.push_back(comp);
        }
    }

    return result;
}

// Recursive DFS helper function
void Network::dfs(int cur, std::vector<bool> &visited, std::vector<int> &comp) {
    visited[cur] = true;
    comp.push_back(cur);

    std::set<int> curFriends = getUser(cur)->getFriends();
    for (int j : curFriends) {
        if (!visited[j]) dfs(j, visited, comp);
    }
}

// Adds a post to a user's feed (incoming or outgoing)
void Network::addPost(int ownerId, std::string message, bool isIncoming, std::string author, bool isPublic, std::vector<std::set<int>> reactions_) {
    int messageId = getTotalPosts();
    if (isIncoming) {
        IncomingPost* cur = new IncomingPost(messageId, ownerId, message, isPublic, author, reactions_);
        getUser(ownerId)->addPost(cur);
    } else {
        Post* cur = new Post(messageId, ownerId, message, reactions_);
        getUser(ownerId)->addPost(cur);
    }
}

// Returns total number of posts in the network
int Network::getTotalPosts() {
    int count = 0;
    for (User* i : users_) {
        std::vector<Post*> cur = i->getPosts();
        count += cur.size();
    }
    return count;
}

// Returns string representation of posts for a user
std::string Network::getPostsString(int ownerId, int howMany, bool showOnlyPublic) {
    return getUser(ownerId)->getPostsString(howMany, showOnlyPublic);
}

// Reads posts from a file and populates the network
int Network::readPosts(const char* fname) {
    std::string myline;
    std::ifstream myfile(fname);
    if (!myfile.is_open()) return -1;

    getline(myfile, myline);
    int totalPosts = std::stoi(myline);
    int count = 0;

    while (count < totalPosts) {
        getline(myfile, myline); // message ID
        getline(myfile, myline); // message content
        std::string curMessage = myline;
        curMessage.erase(std::remove(curMessage.begin(), curMessage.end(), '\t'), curMessage.end());

        getline(myfile, myline); // owner ID
        myline.erase(std::remove_if(myline.begin(), myline.end(), ::isspace), myline.end());
        int curOwnerId = std::stoi(myline);

        std::stringstream ss;
        std::set<int> curLikes, curHearts, curLaughs;
        int id;

        if (nextNonEmptyLine(myfile, myline)) { ss = std::stringstream(myline); while (ss >> id) curLikes.insert(id); }
        if (nextNonEmptyLine(myfile, myline)) { ss = std::stringstream(myline); while (ss >> id) curHearts.insert(id); }
        if (nextNonEmptyLine(myfile, myline)) { ss = std::stringstream(myline); while (ss >> id) curLaughs.insert(id); }

        std::vector<std::set<int>> curReactions = {curLikes, curHearts, curLaughs};

        getline(myfile, myline);
        bool curIsPublic = (myline.erase(std::remove(myline.begin(), myline.end(), '\t'), myline.end()) == "public");

        getline(myfile, myline);
        std::string curAuthor = myline;
        curAuthor.erase(std::remove(curAuthor.begin(), curAuthor.end(), '\t'), curAuthor.end());

        if (curAuthor != "")
            addPost(curOwnerId, curMessage, true, curAuthor, curIsPublic, curReactions);
        else
            addPost(curOwnerId, curMessage, false, curAuthor, curIsPublic, curReactions);

        count++;
    }

    return 0;
}

// Writes all posts to a file
int Network::writePosts(const char* fname) {
    std::ofstream myfile(fname);
    if (!myfile.is_open()) return -1;

    std::vector<Post*> allPosts;
    for (User* i : users_) {
        std::vector<Post*> curUser = i->getPosts();
        for (Post* j : curUser) if (j != nullptr) allPosts.push_back(j);
    }

    std::sort(allPosts.begin(), allPosts.end(), Network::mySort);

    myfile << getTotalPosts() << "\n";

    for (Post* cur : allPosts) {
        myfile << cur->getMessageId() << "\n";
        myfile << "\t" << cur->getMessage() << "\n";
        myfile << "\t" << cur->getOwnerId() << "\n";

        for (const auto &reaction : {cur->getLikes(), cur->getHearts(), cur->getLaughs()}) {
            myfile << "\t";
            for (int r : reaction) myfile << r << " ";
            myfile << "\n";
        }

        if (cur->getAuthor() != "") {
            myfile << "\t" << (cur->getIsPublic() ? "public" : "private") << "\n";
            myfile << "\t" << cur->getAuthor() << "\n";
        } else {
            myfile << "\n\n";
        }
    }

    return 0;
}

// Helper for sorting posts by message ID
bool Network::mySort(Post* i, Post* j) {
    return (i->getMessageId() < j->getMessageId());
}

// Returns all users in the network
std::vector<User*> Network::getUsers() {
    return users_;
}

// Adds a reaction to a post
void Network::addReaction(int type, int userId, int postId) {
    for (User* i : users_) {
        std::vector<Post*> curPosts = i->getPosts();
        for (Post* j : curPosts) {
            if (j->getMessageId() == postId) {
                i->addReaction(type, userId, postId);
            }
        }
    }
}
