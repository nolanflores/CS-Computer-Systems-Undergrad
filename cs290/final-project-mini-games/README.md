# Mini Games
### CS 290 Fall 2024
A web-based collection of games and recorded statistics of game play activity.</br>
We currently have Tic Tac Toe, Hangman, and a memory based card matching game.

## How to Run
To run the game, you can either access it locally, or on the engineering server.</br>
You can also deploy it, but that requires further knowledge.
### Clone the Repository
Clone the repository onto your desired machine.
### Install Dependencies
> [!NOTE]
> You will need to have Nodejs installed on your machine</br>

Run the following commands to install the required libraries:
```
npm install fs
```
```
npm install handlebars
```
```
npm install express
```
```
npm install express-handlebars
```
```
npm install express-session
```
### Locally
Run the server with the following command:
```
npm run start
```
You can now access the webpage at http://localhost:3001
### Server
You will need to access the engineering server from a specifc flip.</br>
Rather than connecting to ```access.engr.oregonstate.edu```, you will need to connect to one of the 4 flip servers:</br>
```flip1.engr.oregonstate.edu```</br>
```flip2.engr.oregonstate.edu```</br>
```flip3.engr.oregonstate.edu```</br>
```flip4.engr.oregonstate.edu```</br>
Make note of the flip server number you connect to.</br>
Once connected to the server, navigate to or clone the repository.</br>
run the server with the following command:
```
npm run start
```
You can now access the webpage at http://flip[server_number].engr.oregonstate.edu:3001
### Server Port Error
If the port 3001 is being used by your machine or the engineering server, you will receive an error.</br>
To remedy this, change the port variable in server.js to an available port.</br>
You will then have to change the webpage url to reflect the port change.

## Contributors
Nolan Flores - florenol@oregonstate.edu</br>
Aiden Do - doph@oregonstate.edu</br>
Conner Dillavou - dillavoc@oregonstate.edu</br>
Artur Dubanaev - dubanaea@oreognstate.edu