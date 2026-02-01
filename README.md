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

## Interface Preview
**Login Page (Only works if the user name entered can be found on the Network, otherwise "Invalid User" flag appears)**
<img width="794" height="592" alt="SocialNetworkScreenshot2" src="https://github.com/user-attachments/assets/c8e7187e-7f2a-4da6-b062-e3718640c7c2" />
**Profile view & Friend Suggestions**
<img width="796" height="593" alt="SocialNetworkScreenshot1" src="https://github.com/user-attachments/assets/c44e1453-8e04-4765-a63c-c1f0fa91016d" />
**Specific User Reactions View**
<img width="791" height="592" alt="SocialNetworkScreenshot3" src="https://github.com/user-attachments/assets/d127ff04-8451-4839-9619-ac53c25d8468" />  
**Note:** The UI was engineered using the Qt Framework, implementing dynamic widget updates to reflect real-time changes in the social graph.




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

## How to Build
1. Make sure you have **Qt (5 or 6)** installed on your system.
2. Open the `SocialNetwork.pro` project file in **Qt Creator**.
3. Build the project:
    - Click **Build > Build Project** or press `Ctrl + B`.
4. Run the program:
    - Click **Run > Start Debugging** or press `Ctrl + R`.
  
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

## Design Notes
- Object-Oriented Design:
  - `User` class stores profile information and posts.
  - `Post` class handles message content, reactions, and visibility.
  - `IncomingPost` inherits `Post` to include author and visibility metadata.
  - `Network` class manages users, friend connections, post storage, and graph operations.
- GUI Design:
  - Qt Widgets are used for all interface elements.
  - Buttons and tables dynamically update to display friends, posts, and reactions.
  - Multiple post selection buttons allow viewing or reacting to recent posts.
- Persistence:
  - Changes to users, friendships, and posts are immediately saved to text files for persistence between sessions.
 
## Future Improvements
- Add profile pictures and richer post content.
- Add search functionality to quickly find users.
- Improve friend suggestions using more advanced network analysis.

## Originality Note
This project was developed for a class assignment with a minimal starter skeleton provided by the instructor. The design, implementation of the
social network functionality, user interface, post and reaction handling, and all supporting logic reflect my own work. This README does not 
claim exclusive authorship over the original skeleton, only over the code and features that I added.


