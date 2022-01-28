"use strict";

const service = require('./services/service');

const express = require('express');
const app = express();
const _environment = process.environment || 'production';

var dataArray = new Array;


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
app.get("/sendDatas/:temp/:hum/:hic", (req, res) => {
    let datasFromMessage = req.params.temp + "," + req.params.hum + "," + req.params.hic
    dataArray.push(datasFromMessage);

    res.json({
        info: 'This is the /sendDatas rest call.'
    });

});

// ---- SERVE HTML ----
app.get("/htmlResponse", (req, res) => {
    res.status(200);
    res.setHeader('Access-Control-Allow-Origin', '*'); // allow cross origin


      service.createTable(dataArray).then(message => {
        res.send(  `
            <html>
            <head>
             <style>
              td {
              font-size: 20px;
              padding-right: 20px;
              padding-left: 20px;
              }
              .headRow {
              font-weight: bold;
              text-decoration: underline;
              }
              .listItem {
              text-align: center;
              }
              </style>
            </head>
            <body>
            <h1 class="test">Arduino Thermometer</h1>
            <h2>A puzzle project by Niklas and Lias</h2>
            ` +
            message
            +
            `
          </body>
          </html>
          `
        );
    });

});

app.get("/changeWebserver/:changing", (req) => {
    console.log("Changing is here");
    let changing = req.params.changing;

    // Turn webserver on / off
});

// ---- SERVE STATIC FILES ---- //
const angular_folder = process.env.ANGULAR_FOLDER || 'static';
app.get('*.*', express.static(angular_folder, {maxAge: '1d'}));

// ---- START WEBSERVER ---- //
const port = process.env.PORT || 8080;
app.listen(port, () => {
    console.log('Node Express server listening on port', port);
});
