#include "post.h"
#include <string>

Post::Post() {}  // Default constructor

// Constructor for Post with message ID, owner, content, and reactions
Post::Post(int messageId, int ownerId, std::string message, std::vector<std::set<int>> reactions_) {
    messageId_ = messageId;
    ownerId_ = ownerId;
    message_ = message;
    reactions = reactions_;
}

// Returns the post's message ID
int Post::getMessageId() {
    return messageId_;
}

// Returns the owner's user ID
int Post::getOwnerId() {
    return ownerId_;
}

// Returns the message content
std::string Post::getMessage() {
    return message_;
}

// Returns a string representation of the post including reaction counts
std::string Post::toString() {
    std::string likes = std::to_string(getNumLikes());
    std::string hearts = std::to_string(getNumHearts());
    std::string laughs = std::to_string(getNumLaughs());

    return message_ + "\nreactions: " + likes + "👍 " + hearts + "❤️ " + laughs + "😂 ";
}

// Returns the author (empty for base Post)
std::string Post::getAuthor() {
    return "";
}

// Returns visibility (always public for base Post)
bool Post::getIsPublic() {
    return true;
}

// Returns the set of user IDs who liked the post
std::set<int> Post::getLikes() {
    if (reactions.size() > 0) return reactions[0];
    return {};
}

// Returns the set of user IDs who reacted with hearts
std::set<int> Post::getHearts() {
    if (reactions.size() > 1) return reactions[1];
    return {};
}

// Returns the set of user IDs who reacted with laughs
std::set<int> Post::getLaughs() {
    if (reactions.size() > 2) return reactions[2];
    return {};
}

// Returns number of likes
int Post::getNumLikes() {
    if (reactions.size() > 0) return reactions[0].size();
    return 0;
}

// Returns number of hearts
int Post::getNumHearts() {
    if (reactions.size() > 1) return reactions[1].size();
    return 0;
}

// Returns number of laughs
int Post::getNumLaughs() {
    if (reactions.size() > 2) return reactions[2].size();
    return 0;
}

// Adds a reaction of a specific type (0=like,1=heart,2=laugh) by a user
void Post::addReaction(int type, int userId) {
    if (type == 0) reactions[0].insert(userId);
    else if (type == 1) reactions[1].insert(userId);
    else if (type == 2) reactions[2].insert(userId);
}

IncomingPost::IncomingPost() {}  // Default constructor

// Constructor for IncomingPost, initializes base Post and additional fields
IncomingPost::IncomingPost(int messageId, int ownerId, std::string message, bool isPublic, std::string author, std::vector<std::set<int>> reactions_)
    : Post(messageId, ownerId, message, reactions_) {
    author_ = author;
    isPublic_ = isPublic;
}

// Returns string representation including author and visibility
std::string IncomingPost::toString() {
    std::string result = author_ + " wrote";

    if (!isPublic_) result += "(private)";

    result += (": " + Post::toString());
    return result;
}

// Returns the author of the post
std::string IncomingPost::getAuthor() {
    return author_;
}

// Returns whether the post is public
bool IncomingPost::getIsPublic() {
    return isPublic_;
}
