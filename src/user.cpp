#include "user.h"
#include <iostream>

User::User(){}

// Constructor to initialize a User with ID, name, year, zip, and friends
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

// Returns the set of friend IDs
std::set<int>& User::getFriends(){
    return friends_;
}

// Adds a friend if they aren't already in the friends set
void User::addFriend(int id){
    for(int val : friends_){
        if(id == val){
            return;
        }
    }
    friends_.insert(id);
}   

// Removes a friend by ID if they exist
void User::deleteFriend(int id){
    if(friends_.count(id) > 0){
        friends_.erase(id);
    }
}

// Adds a post to the user's messages
void User::addPost(Post* post){
    messages_.push_back(post);
}

// Adds a reaction to a specific post owned by the user
void User::addReaction(int type, int postId, int userId){
    for(Post* i : messages_){
        if(i->getMessageId() == postId){
            i->addReaction(type, userId);
        }
    }
}

// Returns all posts by the user
std::vector<Post*> User::getPosts(){
    return messages_;
}

// Returns a formatted string of the user's recent posts
// Optionally filters to only show public posts
std::string User::getPostsString(int howMany, bool showOnlyPublic){
    std::string result = "\n";
    int c = 1;

    if (messages_.size() <= howMany){
        for(Post* i : messages_){
            result += std::to_string(c) + ". " + i->toString() + "\n\n";
            c++;
        }
    }
    else{
        int index = messages_.size() - 5;
        int count = 0;

        while(count < howMany){
            if(!showOnlyPublic || messages_[index]->getIsPublic()){
                result += std::to_string(c) + ". " + messages_[index]->toString() + "\n\n";
                count++;
            }
            index++;
            c++;
        }
    }

    return result;
}
