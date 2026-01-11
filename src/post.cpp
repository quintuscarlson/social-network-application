#include "post.h"
#include <string>

Post::Post(){}


Post::Post(int messageId, int ownerId, std::string message, std::vector<std::set<int>> reactions_){
	messageId_ = messageId;
	ownerId_ = ownerId;
	message_ = message;
	reactions = reactions_;
}


int Post::getMessageId(){
	return messageId_;
}


int Post::getOwnerId(){
	return ownerId_;
}


std::string Post::getMessage(){
	return message_;
}


std::string Post::toString(){
    std::string likes = std::to_string(getNumLikes());
    std::string hearts = std::to_string(getNumHearts());
    std::string laughs = std::to_string(getNumLaughs());

    return message_ + "\nreactions: " + likes + "👍 " + hearts + "❤️ " + laughs + "😂 ";
}


std::string Post::getAuthor(){
	return "";
}


bool Post::getIsPublic(){
	return true;
}

std::set<int> Post::getLikes(){
    if(reactions.size() > 0){
	return reactions[0];
    }
    return {};
}

std::set<int> Post::getHearts(){
    if(reactions.size() > 1){
        return reactions[1];
    }
    return {};
}


std::set<int> Post::getLaughs(){
    if(reactions.size() > 2){
        return reactions[2];
    }
    return {};
}

int Post::getNumLikes(){
    if(reactions.size()>0){
	return reactions[0].size();
    }
    return 0;
}

int Post::getNumHearts(){
    if(reactions.size()>1){
        return reactions[1].size();
    }
    return 0;
}

int Post::getNumLaughs(){
    if(reactions.size()>2){
        return reactions[2].size();
    }
    return 0;
}

void Post::addReaction(int type, int userId){
	if(type == 0){
        reactions[0].insert(userId);
	}
	else if(type == 1){
        reactions[1].insert(userId);
	}
	else if(type == 2){
        reactions[2].insert(userId);
	}
}


IncomingPost::IncomingPost(){}

//accesses post class to assign values to private base class member variables
IncomingPost::IncomingPost(int messageId, int ownerId, std::string message, bool isPublic, std::string author, std::vector<std::set<int>> reactions_):Post(messageId, ownerId, message, reactions_){
	author_ = author;
	isPublic_ = isPublic;
}

std::string IncomingPost::toString(){

	std::string result = author_ + " wrote";

	if(!isPublic_){
		result += "(private)";
	}

	result += (": " + Post::toString());

	return result;
}


std::string IncomingPost::getAuthor(){
	return author_;
}


bool IncomingPost::getIsPublic(){
	return isPublic_;
}
