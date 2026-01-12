#ifndef USER_H
#define USER_H

#include <set>
#include <string>
#include <vector>
#include "post.h"

// User class represents a single user in the social network
class User {
    friend class Network;  // Network class can access private members

public:
    // --- Member variables ---
    int id_;                     // Unique user ID
    std::string name_;           // User's name
    int year_;                   // Birth year
    int zip_;                    // Zip code
    std::set<int> friends_;      // Set of user IDs representing friends
    std::vector<Post*> messages_; // Vector of pointers to posts created by this user

    // --- Constructors ---
    User();  // Default constructor
    User(int id, std::string name, int year, int zip, std::set<int> friends); // Parameterized constructor

    // --- Friend management ---
    void addFriend(int id);       // Add a friend by ID (if not already a friend)
    void deleteFriend(int id);    // Remove a friend by ID

    // --- Accessor methods ---
    int getId();                  // Return user ID
    std::string getName();        // Return user name
    int getYear();                // Return birth year
    int getZip();                 // Return zip code
    std::set<int>& getFriends();  // Return reference to friends set

    // --- Post management ---
    void addPost(Post* post);                    // Add a post pointer to messages vector
    std::vector<Post*> getPosts();              // Return vector of all posts
    std::string getPostsString(int howMany, bool showOnlyPublic); // Return formatted string of posts

    // --- Reactions ---
    void addReaction(int type, int postId, int userId); // Add reaction to a specific post
};

#endif
