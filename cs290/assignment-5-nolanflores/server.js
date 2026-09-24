/*
 * Write your routing code in this file.  Make sure to add your name and
 * @oregonstate.edu email address below.
 *
 * Name: Nolan Flores
 * Email: florenol@oregonstate.edu
 */

var path = require('path')
var express = require('express')
var exphbs = require('express-handlebars')

var postData = require('./postData.json')

var port = process.env.PORT || 3001
var app = express()

app.set('views', path.join(__dirname, 'views'))
app.engine('handlebars', exphbs.engine({defaultLayout: 'main'}))
app.set('view engine', 'handlebars')

app.use(express.static('static'))

app.get('/', function (req, res) {
    res.status(200).render("index", {
        posts: postData
    });
})

app.get('/posts/:id', function (req, res, next) {
    console.log("== Post", req.params.id);
    var id = req.params.id;
    if (id >= 0 && id < postData.length) {
        res.status(200).render("partials/post", postData[id]);
    } else {
        res.status(404).render("404");
    }
})

app.get('*', function (req, res) {
    res.status(404).render("404");
})

app.listen(port, function () {
    console.log("== Server is listening on port", port);
})
