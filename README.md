# Social Network Application

## Overview
This project is a **desktop-based social network simulator** built using **C++** and **Qt** for the GUI. It allows users to:
- Create and manage profiles
- Add friends and see friend suggestions
- Post messages
- React to posts (Like, Heart, Laugh)
- View posts and reactions
- Navigate between their own and friends’ profiles

The application models a social network graph internally and persists data using text files.

## Features
### User Management 
- Users have a **unique ID, name, birth year, zip code,** and a **list of friends.**
- Ability to **add and remove friends.**
- Displays friend suggestions based on mutual connections.

### Posts and Reactions
- Users can create posts with optional visibility settings.
- Posts can receive **three types of reactions:**
  - 👍 Like
  - ❤️ Heart
  - 😂 Laugh
- Reactions are stored per post and displayed alongside the post content.

### Profile Navigation
- View **your own profile** or navigate to a friend’s profile.
- Shows recent posts (up to 5) and reactions.
- Options to add reactions to friends' posts.

### Graph and Network Features
- Internally, the network uses a **graph model:**
  - Users are nodes
  - Friend connections are edges
- Supports:
  - Shortest path calculation between users
  - Suggested friends based on network connections
  - Graph components (groups) detection

### Data Persistence
- Users and posts are **read from and written to text files** (`users.txt`, `posts.txt`).
- Ensures that all changes to profiles, friendships, posts, and reactions are saved.

## Requirements 
- **C++17** or later
- **Qt 5** or **Qt 6** (for GUI components)
- Standard C++ libraries: `<vector>`, `<string>`, `<set>`, `<iostream>`

## How to Use
**1. Login**
- Enter your username from `users.txt`.
- Invalid usernames will display an error.

**2. Profile Navigation**
- View your own profile or a friend’s profile.
- Use buttons to return to your own profile.
  
**3. Friend Management**
- Add friends using the "Add Friend" button.
- See friend suggestions in your profile and add them.
   
**4. Posts**
- Add a new post via the “Add Post” button.
- Posts can be **public or private** depending on context.
  
**5. Reactions**
- View reactions on posts.
- Add reactions to friends’ posts using 👍, ❤️, 😂.
