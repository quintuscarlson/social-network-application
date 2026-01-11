#include "user.h"
#include <iostream>

User::User(){}

User::User(int id, std::string name, int year, int zip, std::set<int> friends){
	id_ = id;
	name_ = name;
	year_ = year;
	zip_ = zip;
	friends_ = friends;

	}

int User::getId(){
	return id_;
}

std::string User::getName(){
	return name_;
}

int User::getYear(){
	return year_;
}

int User::getZip(){
	return zip_;
}

std::set<int>& User::getFriends(){
		return friends_;
	}

void User::addFriend(int id){

	//loop through friends_ set checking if the friend already exists
	for(int val : friends_){
		if(id == val){
			return;
		}
	}

	friends_.insert(id);

	return;
}	

void User::deleteFriend(int id){

	bool check = false;

	//loops through friends_ set to check if the paramter id exists
	for(int val : friends_){

		if(val == id){
			check = true;
		}
	}

	if(check == true){
		friends_.erase(id);
	}

	return;
}


void User::addPost(Post* post){
	messages_.push_back(post);
}

void User::addReaction(int type, int postId, int userId){

    Post* curPost = nullptr;


	for(Post* i : messages_){
		if(i->getMessageId() == postId){
            curPost = i;
            curPost->addReaction(type, userId);
		}
	}
}


std::vector<Post*> User::getPosts(){
	return messages_;
}

std::string User::getPostsString(int howMany, bool showOnlyPublic){

    std::string result = "\n";
    int c = 1;

	if (messages_.size() <= howMany){
		for(Post* i : messages_){
            result += std::to_string(c) + ". " + i->toString();
			result += "\n\n";
            c++;
		}
	}
	else{
        int index = messages_.size() - 5;
		int count = 0;

//outputs the correct number of posts and only includes public posts if that is specified in the parameter
		while(count < howMany){
			if(!showOnlyPublic || messages_[index]->getIsPublic()){
            result += std::to_string(c) + ". " + messages_[index]->toString();
			result += "\n\n";
			count++;}
            index++;
            c++;
		}

	}

	return result;
}

