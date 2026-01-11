#include "network.h"
#include <iostream>
#include <fstream>
#include<sstream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <queue>

Network::Network(){}

bool nextNonEmptyLine(std::ifstream& in, std::string& line) {
    while (std::getline(in, line)) {
        if (!line.empty()) return true;
    }
    return false;
}


void Network::addUser(User* user){
	users_.push_back(user);
}


User* Network::getUser(int id){
	for(User* cur : users_){
		if(cur->getId() == id){
			return cur;
		}
	}
	return nullptr;
}

//first checks if both Users exist then updates each User object accordingly
int Network::addConnection(std::string s1, std::string s2){

	bool check1 = false;
	bool check2 = false;

	for(User* cur : users_){
		if(cur->getName() == s1){
			check1 = true;
		}
		if(cur->getName() == s2){
			check2 = true;
		}

	}

	if(check1 == false || check2 == false){
		return -1;
	}

	User* user1 = nullptr;
	User* user2 = nullptr;
	int userId1 = -1;
	int userId2 = -1;


	for(User* cur : users_){
		if(cur->getName() == s1){
			userId1 = cur->getId();
			user1 = cur;
		} 
		if(cur->getName() == s2){
			userId2 = cur->getId();
			user2 = cur;
		}
	}

	user1->addFriend(userId2);
	user2->addFriend(userId1);

	return 0;
}

//first checks if both Users exist then updates each User object accordingly
int Network::deleteConnection(std::string s1, std::string s2){

	bool check1 = false;
	bool check2 = false;

	for(User* cur : users_){
		if(cur->getName() == s1){
			check1 = true;
		}
		if(cur->getName() == s2){
			check2 = true;
		}

	}

	if(check1 == false || check2 == false){
		return -1;
	}

	User* user1 = nullptr;
	User* user2 = nullptr;
	int userId1 = -1;
	int userId2 = -1;


	for(User* cur : users_){
		if(cur->getName() == s1){
			userId1 = cur->getId();
			user1 = cur;
		} 
		if(cur->getName() == s2){
			userId2 = cur->getId();
			user2 = cur;
		}
	}

	user1->deleteFriend(userId2);
	user2->deleteFriend(userId1);

	return 0;
}

int Network::getId(std::string name){
	for(User* cur : users_){
		if(cur->getName() == name){
			return cur->getId();
		}
	}

	return -1;
}

int Network::numUsers(){

	return users_.size();
}


//uses sstream and iostream to read input from a file and copy to the network object
int Network::readUsers(const char* fname){
	std::string myline;
	std::ifstream myfile(fname);

	getline(myfile, myline);

	while(getline(myfile, myline)) {
		
		int curId = std::stoi(myline);

		getline(myfile, myline);
		std::string curName = myline;
		curName.erase(std::remove(curName.begin(), curName.end(), '\t'),curName.end());


		getline(myfile, myline);
		int curYear = std::stoi(myline);


		getline(myfile, myline);
		int curZip = std::stoi(myline);

		getline(myfile, myline);
		std::stringstream ss(myline);
		std::set<int> curFriends;
		int friendId;

		while(ss >> friendId){
			curFriends.insert(friendId);
		}

		User* curUser = new User(curId, curName, curYear, curZip, curFriends);
		users_.push_back(curUser);
	}
	return 0;
}

//uses ofstream to copy data from User object to a txt file
int Network::writeUsers(const char* fname){
	std::ofstream myfile(fname);

	myfile << numUsers() << "\n";

	for(User* cur : users_){
		myfile << cur->getId() << "\n";
		myfile << "\t" << cur->getName() << "\n";
		myfile << "\t" << cur->getYear() << "\n";
		myfile << "\t" << cur->getZip() << "\n";

		std::set<int> curFriends = cur->getFriends();
		myfile << "\t";
		 for (int cur2 : curFriends){
		 	myfile << cur2 << " ";
		 }
		 myfile << "\n";
	}

	return 0;
}

//performs a BFS algorithm to determine the shortest path between two nodes in the network
std::vector<int> Network::shortestPath(int from, int to){
	int vSize = users_.size();

	std::vector<bool> visited(vSize, false);
	std::vector<int> connection(vSize, -1);
	std::queue<int> q;

	visited[from] = true;
	q.push(from);

	while(!q.empty()){
		int cur = q.front();
		q.pop();

		std::set<int> friends = getUser(cur)->getFriends();

		for(int i : friends){
			if(!visited[i]) {
				visited[i] = true;
				connection[i] = cur;
				q.push(i);
			}
		}
	}

	std::vector<int> result;
	int path = to;

	while(connection[path] != -1){
		result.push_back(path);
		path = connection[path];
	}
	result.push_back(from);

	std::reverse(result.begin(), result.end());

	return result;
}

//performs a BFS algorithm to return a path to a node that is exactly distance edges away from the paramter node: from
std::vector<int> Network::distanceUser(int from, int& to, int distance){
	int vSize = users_.size();

	std::vector<bool> visited(vSize, false);
	std::vector<int> dist(vSize, -1);
	std::queue<int> q;

	visited[from] = true;
	dist[from] = 0;
	q.push(from);

	while(!q.empty()){
		int cur = q.front();
		q.pop();

		std::set<int> friends = getUser(cur)->getFriends();

		for(int i : friends){
			if(!visited[i]) {
				visited[i] = true;
				dist[i] = dist[cur] + 1;
				q.push(i);

				if(dist[i] == distance){
					to = i;
					return shortestPath(from, to);
				}
			}
		}
	}

	to = -1;
	return std::vector<int>();
}

//uses a BFS to determine friends of friends and then determines each potential friends score so that it can return a vector of friend suggestions
std::vector<int> Network::suggestFriends(int who, int& score){
	int vSize = users_.size();

	std::vector<bool> visited(vSize, false);
	std::vector<int> dist(vSize, -1);
	std::queue<int> q;

	visited[who] = true;
	dist[who] = 0;
	q.push(who);

	while(!q.empty()){
		int cur = q.front();
		q.pop();

		std::set<int> friends = getUser(cur)->getFriends();

		for(int i : friends){
			if(!visited[i]) {
				visited[i] = true;
				dist[i] = dist[cur] + 1;
				q.push(i);
			}
		}
	}

	std::vector<int> potentialFriends;
	std::vector<int> scores;
	int maxScore = 0;

	for(int j = 0; j < dist.size(); j++){
		if(dist[j]==2){
			potentialFriends.push_back(users_[j]->getId());
		}
	}

	for(int i : potentialFriends){
		int s = 0;
		std::set<int> curFriends = getUser(i)->getFriends();
		std::set<int> whoFriends = getUser(who)->getFriends();
		for(int j : curFriends){
			for(int k : whoFriends){
				if(j==k){
					s++;
				}
			}
		}
		scores.push_back(s);
		if(s > maxScore){
			maxScore = s;
		}
	}

	std::vector<int> bestMatches;
	for(int g = 0; g < scores.size(); g++){
		if(scores[g] == maxScore){
			bestMatches.push_back(potentialFriends[g]);
		}
	}

	score = maxScore;
	return bestMatches;
}

//uses the DFS function to perform a DFS algorithm on the graph and return a vector of different components with their respective User Ids
std::vector<std::vector<int>> Network::groups(){
	int vSize = users_.size();

	std::vector<bool> visited(vSize, false);
	std::vector<std::vector<int>> result;

	for (int j = 0; j < users_.size(); j++){
		if (!visited[j]){
			std::vector<int> comp;
			dfs(j, visited, comp);
			result.push_back(comp);
		}
	}

	return result;
}

//uses recursion to perform a DFS on the network
void Network::dfs(int cur, std::vector<bool> &visited, std::vector<int> &comp){
	visited[cur]=true;
	comp.push_back(cur);

	std::set<int> curFriends = getUser(cur)->getFriends();

	for(int j : curFriends){
		if(!visited[j]){
			dfs(j, visited, comp);
		}
	}

}

void Network::addPost(int ownerId, std::string message, bool isIncoming, std::string author, bool isPublic, std::vector<std::set<int>> reactions_){
	if(isIncoming){
		int messageId = getTotalPosts();
        IncomingPost* cur = new IncomingPost(messageId, ownerId, message, isPublic, author, reactions_);
		getUser(ownerId)->addPost(cur);
	}
	else{
		int messageId = getTotalPosts();
        Post* cur = new Post(messageId, ownerId, message, reactions_);
		getUser(ownerId)->addPost(cur);
	}
}

int Network::getTotalPosts(){
	int count = 0;

	for (User* i : users_){
		std::vector<Post*> cur = i->getPosts();
		count += cur.size();
	}

	return count;
}


std::string Network::getPostsString(int ownerId, int howMany, bool showOnlyPublic){
	return getUser(ownerId)->getPostsString(howMany, showOnlyPublic);
}

int Network::readPosts(const char* fname){

	std::string myline;
	std::ifstream myfile(fname);

	if(!myfile.is_open()){
		return -1;
	}

	getline(myfile, myline);
    int totalPosts = std::stoi(myline);
	int count = 0;

	while(count < totalPosts) {

		getline(myfile, myline);
        getline(myfile, myline);
		std::string curMessage = myline;
		curMessage.erase(std::remove(curMessage.begin(), curMessage.end(), '\t'),curMessage.end());


        getline(myfile, myline);
        myline.erase(std::remove_if(myline.begin(), myline.end(), ::isspace), myline.end());
        int curOwnerId = std::stoi(myline);

		std::stringstream ss;
		std::set<int> curLikes;
		int likesId;

		if(nextNonEmptyLine(myfile, myline)){
			ss = std::stringstream(myline);
		while(ss >> likesId){
			curLikes.insert(likesId);
		}}

		std::set<int> curHearts;
		int heartsId;

		if(nextNonEmptyLine(myfile, myline)){
			ss = std::stringstream(myline);
		while(ss >> heartsId){
			curHearts.insert(heartsId);
		}}

		std::set<int> curLaughs;
		int laughsId;
	

		if(nextNonEmptyLine(myfile, myline)){
			ss = std::stringstream(myline);
		while(ss >> laughsId){
			curLaughs.insert(laughsId);
		}}

		std::vector<std::set<int>> curReactions;

		curReactions.push_back(curLikes);
		curReactions.push_back(curHearts);
		curReactions.push_back(curLaughs);

		getline(myfile, myline);
		std::string temp = myline;
		temp.erase(std::remove(temp.begin(), temp.end(), '\t'), temp.end());
		bool curIsPublic = (temp == "public");

		getline(myfile, myline);
		std::string curAuthor = myline;
		curAuthor.erase(std::remove(curAuthor.begin(), curAuthor.end(), '\t'),curAuthor.end());

		if(curAuthor != ""){
            addPost(curOwnerId, curMessage, true, curAuthor, curIsPublic, curReactions);
		}
		else{
            addPost(curOwnerId, curMessage, false, curAuthor, curIsPublic, curReactions);
		}
		count++;
	}

	return 0;
}

int Network::writePosts(const char* fname){
	std::ofstream myfile(fname);

	if(!myfile.is_open()){
		return -1;
	}

	std::vector<Post*> allPosts;

	for(User* i : users_){
		std::vector<Post*> curUser = i->getPosts();
		for(Post* j : curUser){
            if(j != nullptr){
			allPosts.push_back(j);
            }}
	}

	std::sort (allPosts.begin(), allPosts.end(), Network::mySort);



	myfile << getTotalPosts() << "\n";

	for(Post* cur : allPosts){
		myfile << cur->getMessageId() << "\n";
		myfile << "\t" << cur->getMessage() << "\n";
		myfile << "\t" << cur->getOwnerId() << "\n";


        std::set<int> curLikes = cur->getLikes();
        myfile << "\t";
        for (int cur : curLikes){
            myfile << cur << " ";
        }
        myfile << "\n";

        std::set<int> curHearts = cur->getHearts();
        myfile << "\t";
        for (int cur : curHearts){
            myfile << cur << " ";
        }
        myfile << "\n";

        std::set<int> curLaughs = cur->getLaughs();
        myfile << "\t";
        for (int cur : curLaughs){
            myfile << cur << " ";
        }
        myfile << "\n";

		if(cur->getAuthor() != ""){
			if(cur->getIsPublic()){
				myfile << "\tpublic\n";
			}
			else{
				myfile << "\tprivate\n";
			}

			myfile << "\t" << cur->getAuthor()<<"\n";
		}
		else{
			myfile <<"\n\n";
		}


    }

	return 0;
}

bool Network::mySort(Post* i, Post* j){
	return (i->getMessageId() < j->getMessageId());
}

std::vector<User*> Network::getUsers(){
    return users_;
}

void Network::addReaction(int type, int userId, int postId){
	for(User* i : users_){
       std::vector<Post*> curPosts = i->getPosts();
		for(Post* j : curPosts){
			if(j->getMessageId() == postId){
				i->addReaction(type, userId, postId);
			}
		}
	}
}
