#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <string>
#include "user.h"

class Network {
public:

    // Default constructor
    Network();

    // Stores all users in the network
    std::vector<User*> users_;

    // Adds a user to the network
    void addUser(User* user);

    // Creates a connection (friendship) between two users by name
    int addConnection(std::string s1, std::string s2);

    // Deletes a connection (friendship) between two users by name
    int deleteConnection(std::string s1, std::string s2);

    // Returns the user ID for a given username, or -1 if not found
    int getId(std::string name);

    // Reads user data from a file into the network
    int readUsers(const char* fname);

    // Writes user data from the network to a file
    int writeUsers(const char *fname);

    // Returns the total number of users in the network
    int numUsers();

    // Returns a pointer to a user by ID, or nullptr if not found
    User* getUser(int id);

    // Returns a vector of user IDs representing the shortest path between two users
    std::vector<int> shortestPath(int from, int to);

    // Returns a vector path from a user to another user at a specified distance
    std::vector<int> distanceUser(int from, int& to, int distance);

    // Suggests friends for a user, returning the IDs of the best matches
    std::vector<int> suggestFriends(int who, int& score);

    // Returns all connected components of the network (groups of users)
    std::vector<std::vector<int>> groups();

    // Recursive helper for DFS to find connected components
    void dfs(int cur, std::vector<bool> &visited, std::vector<int> &comp);

    // Adds a post to a user; can be incoming or authored by the logged-in user
    void addPost(int ownerId, std::string message, bool isIncoming, std::string author, bool isPublic, std::vector<std::set<int>> reactions_);

    // Returns a formatted string of posts for a user
    std::string getPostsString(int ownerId, int howMany, bool showOnlyPublic);

    // Reads posts from a file and adds them to the appropriate users
    int readPosts(const char* fname);

    // Writes all posts in the network to a file
    int writePosts(const char* fname);

    // Adds a reaction to a specific post by type (like, heart, laugh)
    void addReaction(int type, int userId, int postId);

    // Returns a vector of all users in the network
    std::vector<User*> getUsers();

private:

    // Helper to sort posts by ID
    static bool mySort(Post* i, Post* j);

    // Returns total number of posts in the network
    int getTotalPosts();
};

#endif
