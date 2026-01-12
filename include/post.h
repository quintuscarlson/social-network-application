#ifndef POST_H
#define POST_H

#include <string>
#include <vector>
#include <set>

// Base Post class representing a generic social media post
class Post {
public:
    // Default constructor
    Post();

    // Constructor with parameters
    Post(int messageId, int ownerId, std::string message, std::vector<std::set<int>> reactions_);

    // Returns a formatted string representing the post and its reactions
    std::string toString();

    // Getters
    int getMessageId();
    int getOwnerId();
    std::string getMessage();

    // Virtual functions for polymorphism (overridden by IncomingPost)
    virtual std::string getAuthor();
    virtual bool getIsPublic();

    // Reaction accessors
    std::set<int> getLikes();
    std::set<int> getHearts();
    std::set<int> getLaughs();

    // Add a reaction to the post: type 0=like, 1=heart, 2=laugh
    void addReaction(int type, int userId);

    // Returns the number of reactions by type
    int getNumLikes();
    int getNumHearts();
    int getNumLaughs();

private:
    int messageId_;
    int ownerId_;
    std::string message_;
    std::vector<std::set<int>> reactions; // 0=likes, 1=hearts, 2=laughs
};

// Derived class representing a post that includes author and visibility info
class IncomingPost : public Post {
public:
    // Default constructor
    IncomingPost();

    // Constructor with parameters including author and visibility
    IncomingPost(int messageId, int ownerId, std::string message, bool isPublic, std::string author, std::vector<std::set<int>> reactions_);

    // Overrides Post::toString() to include author and visibility
    std::string toString();

    // Overrides base class virtual functions
    std::string getAuthor() override;
    bool getIsPublic() override;

private:
    std::string author_;
    bool isPublic_;
};

#endif
