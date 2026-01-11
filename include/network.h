#ifndef NETWORK_H
#define NETWORK_H
#include <vector>
#include <string>
#include "user.h"

class Network {
	public:

		//default constructor
		Network();



		//member variable
		std::vector<User*> users_;

		//pre valid Network object
		//post a User object is added to the network using the User pointer paramter
		void addUser(User* user);

		//pre valid network object
		//post connection established between two user objects using data from parameter
		int addConnection(std::string s1, std::string s2);

		//pre valid network object
		//post connection deleted between two user objects using data from parameter
		int deleteConnection(std::string s1, std::string s2);

		//pre valid network object
		//post return int id using name of user from parameter
		int getId(std::string name);

		//pre valid network object
		//post data from a txt file is copied onto the network
        int readUsers(const char* fname);

		//pre valid network object
		//post data from network is copied onto a txt file
        int writeUsers(const char *fname);

		//pre valid network object
		//post int containing number of Users on the network is returned
		int numUsers();

		//pre valid network object
		//post a pointer to a User object with the paramter id is returned
		User* getUser(int id);

		//pre valid network object from and to are valid User Ids
		//post a vector containing the path of User Ids that connect the paramters in the shortest way
		std::vector<int> shortestPath(int from, int to);

		//pre valid network object from and distance are both valid User Ids or distances
		//post a vector containing the path between from and a node that has the specified distance is returned
		std::vector<int> distanceUser(int from, int& to, int distance);

		//pre valid network object and who is a Valid User Id
		//post a vector of User Ids is returned containing potential friends with the highest scores
		std::vector<int> suggestFriends(int who, int& score);

		//pre valid network object
		//post a vector of vectors of User Ids are returned each containing a different component of the graph
		std::vector<std::vector<int>> groups();

		//pre valid network object, cur is a valid node, visited and comp are valid vectors
		//post nodes are updated based upon the DFS formula
		void dfs(int cur, std::vector<bool> &visited, std::vector<int> &comp);

		//pre valid network object
		//post adds a post to the specified user object in the network
		void addPost(int ownerId, std::string message, bool isIncoming, std::string author, bool isPublic, std::vector<std::set<int>> reactions_);

		//pre valid network object
		//post returns the string of messages from the specified user
		std::string getPostsString(int ownerId, int howMany, bool showOnlyPublic);

		//pre valid network object
		//post reads data from a txt file and copies it to the intended User and Post objects
        int readPosts(const char* fname);

		//pre valid network object
		//post writes all data from the network posts to a specified txt file
        int writePosts(const char* fname);

        void addReaction(int type, int userId, int postId);

        std::vector<User*> getUsers();
        
	private:

		//compares two Ids of post objects used to sort the vector containing all messages on the network
		static bool mySort(Post* i, Post* j);

		//returns the total number of posts in the network
		int getTotalPosts();

};

#endif

