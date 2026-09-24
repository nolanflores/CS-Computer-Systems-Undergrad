const express = require("express");
const exphbs = require("express-handlebars");
const session = require("express-session");//middleware for session
const fs = require("fs");

let data = require("./data.json");
let words = require("./words.json");

const port = process.env.PORT || 3001;//change this number if the port is already in use
const app = express();

//initailize middleware and session
app.use(express.json());//parse bodies
app.use(express.urlencoded({extended: true}));
app.use(session({
    secret: "ILOVEHESS",
    resave: false,
    saveUninitialized: true
}));

//initialize handlebars engine
app.set("views", "./views");
app.engine("handlebars", exphbs.engine({defaultLayout: "main"}))
app.set("view engine", "handlebars")

app.use(express.static("static"));


/*
 * Routes
 * The following routes are used to render the pages
 * If the user does not have a username stored in the session,
 * all pages will redirect to the login page.
 * This is to ensure we have a name for the data.json file
*/

//middleware to check if user has a username stored in session
function checkUsername(req, res, next){
    if(req.session.username){
        next();
    }else{
        res.redirect("/login");
    }
}

app.get("/", checkUsername, (req, res) => {//home page
    res.status(200).render("home");
});

app.get("/tictactoe", checkUsername, (req, res) => {//tictactoe game
    res.status(200).render("tictactoe", {style: "tictactoe.css"});
});

app.get("/hangman", checkUsername, (req, res) => {//hangman game
    res.status(200).render("hangman", {style: "hangman.css"});
});

app.get("/cards", checkUsername, (req, res) => {//card game
    res.status(200).render("cardgame", {style: "cards.css"});
});

app.get("/stats", checkUsername, (req, res) => {//statistics page, displays data from data.json
    res.status(200).render("statistics", {statistics: data});
});

app.get("/login", (req, res) => {//login page
    res.status(200).render("login", {layout: false});
});

app.get("*", function (req, res) {//error 404 page
    res.status(404).render("404");
})

/*
 * Login Endpoint
*/
app.post("/login", (req, res) => {
    const {username} = req.body;
    if (username) {
        req.session.username = username; // Store username in session
        res.redirect("/"); // Redirect to home page
    } else {
        res.redirect("/login");
    }
});



/*
 * Game Endpoints
 * When the user completes a game, a post is sent to the server
 * Depending on the game, the server will handle the post and
 * update the user's statistics.
 * It will then write the updated data to the data.json file
*/

//write data to file
function writeData(filename = "./data.json" , writedata = data){
    fs.writeFile(filename, JSON.stringify(writedata), (err) => {
        if(err){
            console.error("Error writing data to file:", err);
        }
    });
}

/*
 * Handle win/loss for hangman game
 * results are in the body of the post
*/
app.post("/hangman", (req, res) => {
    const {username} = req.session;
    const {win} = req.body;
    if(username){
        for(let i = 0; i < data.length; i++){
            if(data[i].username === username){
                if(win)
                    data[i].hangman_wins++;
                else
                    data[i].hangman_losses++;
                writeData();
                return;
            }
        }
        if(win){
            data.push({username: username, hangman_wins: 1, hangman_losses: 0, tictactoe_games: 0});
        }else{
            data.push({username: username, hangman_wins: 0, hangman_losses: 1, tictactoe_games: 0});
        }
        writeData();
    }
});

/*
 * Adds words to the list of additional words for hangman
 * stored in words.json
 * If no new word is provided, the server will return the list of words
*/
app.post("/hangmanwords", (req, res) => {
    if(req.body.newWord){
        const {newWord, category} = req.body;
        if(!words[category]){
            words[category] = [];
        }
        words[category].push(newWord);
        writeData("./words.json", words);
    }else{
        res.status(200).json(words);
    }
});

/*
 * Handle completed tictactoe game
*/
app.post("/tictactoe", (req, res) => {
    const {username} = req.session;
    if(username){
        for(let i = 0; i < data.length; i++){
            if(data[i].username === username){
                data[i].tictactoe_games++;
                writeData();
                return;
            }
        }
        data.push({username: username, hangman_wins: 0, hangman_losses: 0, tictactoe_games: 1});
        writeData();
    }
});

/*
 * Handle completed card game
*/
app.post("/cards", (req, res) => {
    const {username} = req.session;
    if(username){
        for(let i = 0; i < data.length; i++){
            if(data[i].username === username){
                data[i].card_games++;
                writeData();
                return;
            }
        }
        data.push({username: username, hangman_wins: 0, hangman_losses: 0, tictactoe_games: 0, card_games: 1});
        writeData();
    }
});


/*
 * Start server
*/
app.listen(port, function () {
    console.log("== Server is listening on port", port);
})