const express = require("express");
const http = require("http");
const socketIo = require("socket.io");

const app = express();
const server = http.createServer(app);

const io = socketIo(server, {
  cors: { 
    origin: "http://localhost:8080", 
    methods: ["GET", "POST"], 
    credentials: true 
  }
});

// ==========================
// Random Functions
// ==========================
function getRandomFloat(min, max, decimals = 1) {
  return parseFloat((Math.random() * (max - min) + min).toFixed(decimals));
}

function getRandomInt(min, max) {
  return Math.floor(Math.random() * (max - min + 1)) + min;
}

// ==========================
// Client + Sensor Data
// ==========================
let clients = [];

let sensorData = {
  temperature: 30,
  humidity: 60,
  mq2Value: 300,
  distance: 50
};

io.on("connection", socket => {
  console.log("Client connected:", socket.id);
  clients.push(socket);

  socket.on("disconnect", () => {
    clients = clients.filter(s => s.id !== socket.id);
    console.log("Client disconnected:", socket.id);
  });
});

// ==========================
// Simulation Mode
// ==========================
setInterval(() => {
  sensorData.temperature = getRandomFloat(25, 35);
  sensorData.humidity = getRandomFloat(40, 80);
  sensorData.mq2Value = getRandomInt(100, 800);
  sensorData.distance = getRandomInt(5, 100);

  clients.forEach(socket => socket.emit("sensorData", sensorData));

  console.log("Sending:", sensorData);
}, 2000); // ส่งทุก 2 วินาที

server.listen(3000, () => {
  console.log("Simulation Server running on port 3000");
});