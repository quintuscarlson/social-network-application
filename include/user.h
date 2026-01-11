#ifndef USER_H
#define USER_H
#include <set>
#include <string>
#include "post.h"

class User {
	friend class Network;

		public:

		//member variables	
		int id_;
		std::string name_;
		int year_;
		int zip_;
		std::set<int> friends_;
		std::vector<Post*> messages_;

		//default constructor
		//Pre: None
		//Post: default User object created
		User();

		//Pre: none
		//Post: User object created with paramter values
		User(int id, std::string name, int year, int zip, std::set<int> friends);void addFriend(int id);

		//pre id is a valid user id
		//post friend connection has been deleted from set
		void deleteFriend(int id);

		//pre valid User object
		//post ID of user object returned
		int getId();

		//pre valid User object
		//post string returned containing name of User object
		std::string getName();

		//pre valid User object
		//post int is returned containing birth year of User
		int getYear();

		//pre valid User object
		//post int is returned containing zip code of User
		int getZip();

		//pre valid User object
		//post refernece returned to friends_ set
		std::set<int>& getFriends();

		//pre valid User object
		//post adds a post pointer to messages vector
		void addPost(Post* post);

		//pre valid User object
		//post refernece returned to messages_ vector
		std::vector<Post*> getPosts();

		//pre valid User object
		//post returns string of all messages in the User object
		std::string getPostsString(int howMany, bool showOnlyPublic);

		void addReaction(int type, int postId, int userId);
};

#endif
