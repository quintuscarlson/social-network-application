#ifndef POST_H
#define POST_H
#include <string>
#include <vector>
#include <set>

class Post {

public:

//default constructor
	Post();

//constructor with paramaters
	Post(int messageId, int ownerId, std::string message, std::vector<std::set<int>> reactions_);

//pre valid post object
//post return string of object values
	std::string toString();

//pre valid network object
//post return int messageId	
	int getMessageId();

//pre valid post object
//post return int OwnerId
	int getOwnerId();

//pre valid post object
//post return string of message value
		std::string getMessage();

//pre valid post object
//post return string of author value
//virtual keyword used for polymorphism
	virtual std::string getAuthor();

//pre valid post object
//post return bool is public
//virtual keyword used for polymorphism
	virtual bool getIsPublic();

	std::set<int> getHearts();

	std::set<int> getLaughs();

	std::set<int> getLikes();

	void addReaction(int type, int userId);

	int getNumLikes();

	int getNumHearts();

	int getNumLaughs();

private:

//private base class member variables
	int messageId_;
	int ownerId_;
	std::string message_;
	std::vector<std::set<int>> reactions;
};


class IncomingPost : public Post {

public:

//default constructor
	IncomingPost();

//constructor with paramters
	IncomingPost(int messageId, int ownerId, std::string message, bool isPublic, std::string author, std::vector<std::set<int>> reactions_);
	
//pre valid IncomingPost object
//post return string of object values
	std::string toString();

//pre valid IncomingPost object
//post return string of author value
	std::string getAuthor() override;

//pre valid IncomingPost object
//post return bool isPublic
	bool getIsPublic() override;

private:

//private member variables of inherited class
	std::string author_;
	bool isPublic_;

};

#endif


