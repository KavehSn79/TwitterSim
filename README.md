# TwitterSim
This is a simple twitter written in C++ with a Database and a client.

db.cpp file: It has 2 parts. First part is DBMS implementation and the other part is server implementation

Database part:

The DBMS allows you to create, insert, select, delete, and update data in various tables. It also provides basic operations like union and intersection on table data.

Usage

1. Compile the code using a C++ compiler:
   
   ```shell
   
   g++ main.cpp -o dbms
   

2. Run the program:
   
	./dbms

3. Choose one of the following options:

Enter 1 to start the DBMS shell.

Enter 2 to run the server.


Database Functionality:

The DBMS supports basic CRUD (Create, Read, Update, Delete) operations on tables.

Tables are defined in a schema file (schema.txt) that specifies the table structure, including field names, data types, and uniqueness constraints.

Tables are stored in separate text files (e.g., table_name.txt).

You can insert data into tables, select data based on conditions, delete rows based on conditions, and update rows based on conditions.

The code includes functions for parsing SQL-like queries, handling data types (e.g., INTEGER, BOOLEAN, CHAR), and performing set operations (UNION and INTERSECTION).


Classes:

DB: Represents the Database class, which handles table operations.

insert(): Inserts data into a table.

select(): Selects data from a table based on conditions.

Delete(): Deletes data from a table based on conditions.

update(): Updates data in a table based on conditions.

... (other helper functions)


server: Represents a server class 

register_new_user(): Registers a new user.

login(): Logs in a user.

... (other functions related to user interactions)


Server part: The server code is written in C++ and implements a simple social media server. It listens for incoming client connections, processes client requests, and interacts with text files to store user and tweet data.

Code Structure:

server Class:

The main functionality of the server is encapsulated within the server class. This class includes methods for handling various client requests and interactions. Here are the key methods and their descriptions:

server(): The constructor method initializes the server, creates a socket, binds it to a specific IP address and port, and starts listening for incoming connections.

register_new_user(string newName, string newPass): This method is responsible for registering new users. It reads user data from a text file, checks if the provided username is already taken, and then adds the new user to the user database file.

login(string s): Handles user login requests. It verifies the provided username against the user database and sends a welcome message or an error message to the client.

tweet(string u, string tweet1): Allows a logged-in user to create and post a tweet. The tweet data is stored in a tweet database file.

view(): Retrieves and sends tweets to the client. It reads tweet data from the tweet database, formats it, and sends it to the client.

like(string Uzer, string tweet_Id): Handles the process of a user liking a tweet. It stores the like information in a separate likes database file.

view_likes_of_tweet(string s): Retrieves and sends the list of users who liked a specific tweet to the client.

retweet(string user_wants_to_retweet, string tweet_to_retweet_id): Allows a user to retweet a tweet. It finds the original tweet, creates a new tweet, and stores it in the tweet database.

delteAccount(string name): Handles account deletion. It removes the user's data from the user database, deletes their tweets, and updates the likes database.

re(string s): A helper method for retweeting that adds a timestamp to the retweeted tweet.

currentDateTime(): A helper method to get the current date and time for timestamps in tweets.

Initialization and Socket Handling:

In the constructor (server()), the code initializes a socket, binds it to a specified IP address and port (54000), and starts listening for incoming connections.

Main Loop:

The code enters a main loop where it waits for client connections using accept(). Once a client is connected, it processes the client's requests based on the initial character of the message (e.g., '1' for registration, '2' for login, etc.). The loop continues until the client disconnects.

Data Storage:

User data is stored in a text file named users_table.txt, tweet data in tweets_table.txt, and like data in likes_table.txt. These files are read from and written to during various operations.

Usage:

1.	Compile the C++ code using a C++ compiler.

2.	Run the compiled server executable.
  
3.	Clients can connect to the server and send requests using a client program (not provided in this code). Clients should connect to the server's IP address and port 54000.
  
4.	Clients can perform actions like registration, login, tweeting, viewing tweets, liking tweets, retweeting, and account deletion by sending messages to the server.

Client.cpp file: allows users to register, log in, post tweets, view tweets, like tweets, view likes on tweets, retweet, and delete their account. This client connects to a server that handles these operations.

Usage:
1. Clone the repository or download the source code files.
2. Compile the code using a C++ compiler.
3. Run the compiled executable
4. The client will establish a connection to the server, and you will be presented with a menu of options:
1. to register
2. to login
3. to tweet
4. to view tweets
5. to like a tweet
6. to view likes of tweet
7. to retweet
8. to delete account
