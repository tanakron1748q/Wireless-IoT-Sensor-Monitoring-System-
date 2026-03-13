const express = require("express");
const http = require("http");
const { SerialPort } = require("serialport");
const { ReadlineParser } = require("@serialport/parser-readline");
const socketIo = require("socket.io");

const app = express();
const server = http.createServer(app);

const io = socketIo(server, {
  cors: { origin: "http://localhost:8080", methods: ["GET", "POST"], credentials: true }
});

// Serial Port
const port = new SerialPort({ path: "COM3", baudRate: 9600 });
const parser = port.pipe(new ReadlineParser({ delimiter: "\n" }));

// เก็บ client
let clients = [];
let sensorData = {
  temperature: "--",
  humidity: "--",
  mq2Value: "--",
  distance: "--"
};

io.on("connection", socket => {
  console.log("Client connected:", socket.id);
  clients.push(socket);

  socket.on("disconnect", () => {
    clients = clients.filter(s => s.id !== socket.id);
    console.log("Client disconnected:", socket.id);
  });
});

// แยกบรรทัด Serial แล้ว parse
parser.on("data", line => {
  line = line.trim();

  if (line.startsWith("Temperature:")) {
    sensorData.temperature = parseFloat(line.split(":")[1]);
  } else if (line.startsWith("Humidity:")) {
    sensorData.humidity = parseFloat(line.split(":")[1]);
  } else if (line.startsWith("MQ2 Value:")) {
    sensorData.mq2Value = parseInt(line.split(":")[1]);
  } else if (line.startsWith("Distance:")) {
    sensorData.distance = parseInt(line.split(":")[1]);
  }

  // ส่งข้อมูลให้ทุก client
  clients.forEach(socket => socket.emit("sensorData", sensorData));
});

server.listen(3000, () => {
  console.log("Server running on port 3000");
});