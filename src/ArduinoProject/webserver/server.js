"use strict";

const service = require('./services/service');

const express = require('express');
const app = express();
const _environment = process.environment || 'production';

if (_environment === 'production') {
    const rateLimit = require("express-rate-limit");
    const limiter = rateLimit({
        windowMs: 10000,
        max: 20,
        message: "Too many requests from this IP, please try again"
    });
    app.use(limiter);
}

// ---- SERVE REST CALLS ----
app.get("/sendDatas/:temp/:h/:hic", (req, res) => {
    console.log("Get api / info");
    console.log("Temp: " + req.params.temp);
    console.log("Hum: " + req.params.h);
    console.log("Hic: " + req.params.hic);


    res.json({
        info: 'This is the /sendDatas rest call.'
    });

});

// ---- SERVE HTML ----
app.get("/htmlResponse", (req, res) => {
    console.log("Html response");
    res.status(200);
    res.setHeader('Access-Control-Allow-Origin', '*'); // allow cross origin

    service.sayHelloAsync('day').then(message => {
        res.send(
            `
<html lang="en">
    <body>
        <h1>Html Response</h1>
        <p>Hello Lias</p>
        <img src="/images/puzzle.png" alt="Puzzle ITC logo"><br>
        <a href="/sendDatas">rest call</a>
    </body>
</html>
        `);
    });


});

// ---- SERVE STATIC FILES ---- //
const angular_folder = process.env.ANGULAR_FOLDER || 'static';
app.get('*.*', express.static(angular_folder, {maxAge: '1d'}));

// ---- START WEBSERVER ---- //
const port = process.env.PORT || 8080;
app.listen(port, () => {
    console.log('Node Express server listening on port', port);
});
