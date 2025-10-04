# http_server    

# Simple Multithreaded HTTP Server in C

A lightweight multithreaded HTTP server built in C that serves static HTML files.
This project demonstrates how socket programming works under the hood of web servers — from handling TCP connections to sending HTTP responses manually.

---

## 📘 Overview

This server accepts multiple simultaneous client connections (like web browsers) using `fork()` to handle each client in a separate process.
It supports **only IPv4** connections and is designed to send **only HTML files** in response to HTTP requests.

The goal is simplicity: understand how a real server talks to a browser using raw sockets, without any heavy frameworks or libraries.

---

## ⚙️ Features

* **Multithreaded (via `fork`)** – can handle multiple clients at the same time.
* **Static HTML Serving** – responds to HTTP requests by sending an HTML file.
* **IPv4 Only** – listens for connections over IPv4.
* **Client IP Display** – prints the address of each connected client.
* **Basic HTTP Response Handling** – sends correct HTTP headers for HTML content.

---

## 🧠 How It Works

1. **Socket Creation:**
   The server creates a TCP socket using `socket(AF_INET, SOCK_STREAM, 0)`.

2. **Binding:**
   It binds the socket to port **8080** using `bind()`.

3. **Listening:**
   The server listens for incoming connections with `listen()`.

4. **Accepting Clients:**
   When a client connects, `accept()` returns a new socket for that client.
   The server prints the client’s IPv4 address.

5. **Handling Clients:**
   Each client is handled in a separate process (via `fork()`).
   The child process:

   * Sends a simple HTTP header.
   * Reads the `index.html` file.
   * Sends it to the client.
   * Closes the connection.

6. **Response:**
   The browser receives the HTTP response and renders the HTML page.

---

## 🖥️ Example Output

When you run the server, you’ll see logs like:

```
socket creation successful
bind to port 8080 successfull
server is listening to port 8080....

client(127.0.0.1) connected
html file send successfully to client
client disconnected
```

---

## 📂 Project Structure

```
├── server.c        # The main server code
├── index.html      # The HTML file served to clients
└── README.md       # Project documentation
```

---

## 🚀 How to Run

### 1. Compile the Server

```bash
gcc server.c -o server
```

### 2. Run the Server

```bash
./server
```

### 3. Test it in a Browser

Open your browser and go to:

```
http://localhost:8080
```

You should see your `index.html` page load.

---

## ⚠️ Notes & Limitations

* Only serves `index.html` (no directory traversal or MIME-type detection).
* Not meant for production use — for learning and demonstration only.
* Doesn’t support persistent connections or binary file transfers.
* Browser requests are expected to be well-formed HTTP requests.

---

## 🧩 Future Improvements

* Add support for multiple file types (CSS, JS, images).
* Implement simple routing logic to serve different files based on request path.
* Add graceful shutdown and better error handling.
* Replace `fork()` with pthreads for more control over concurrency.
* Log request details and timestamps.

---

## 📚 Learn More

This project touches on:

* Socket programming in C
* Basic HTTP protocol structure
* Process management (`fork`)
* Network byte ordering (`htons`, `inet_ntop`)

to go deeper, there's more to read about **epoll**, **select**, or **non-blocking I/O** — the technologies that power modern web servers.
