# http_server    

# Multithreaded HTTP Server (C)

A simple multithreaded HTTP server written in C that serves static HTML files over **IPv4**.
This project demonstrates the low-level working of TCP-based HTTP communication — from socket creation and binding to sending valid HTTP responses to connected web clients.

---

## 🧠 Overview

This server is built using the **Berkeley socket API** and is capable of handling multiple clients simultaneously using the `fork()` system call (each client connection is handled in a separate process).

The server listens for HTTP requests (from browsers or other HTTP clients) and responds with an HTML file (`index.html` by default).

---

## ⚙️ Features

* **Multithreaded handling** – serves multiple clients at the same time using `fork()`.
* **IPv4-based communication** – designed specifically for IPv4 HTTP requests.
* **Static HTML serving** – sends only `.html` files as HTTP responses.
* **Client address logging** – displays the IP address of each connected client.
* **Proper HTTP response header** – sends a minimal but valid `HTTP/1.1 200 OK` response.

---

## 📁 Project Structure

```
.
├── server.c        # Main source file for the HTTP server
├── index.html      # HTML file served to clients
└── README.md       # Documentation file
```

---

## 🧩 How It Works

1. The server creates a TCP socket using `socket(AF_INET, SOCK_STREAM, 0)`.
2. It binds to port **8080** on all network interfaces (`INADDR_ANY`).
3. It listens for incoming connections using `listen()`.
4. When a client connects:

   * The server prints the client’s IP address.
   * A new process (via `fork()`) is created to handle that client.
   * The child process sends the HTTP header and the contents of `index.html`.
   * After sending, the client connection is closed.
5. The parent process continues listening for new connections.

---

## 🧪 Usage

### 1. Compile

```bash
gcc server.c -o server
```

### 2. Run the server

```bash
./server
```

### 3. Test it

Open your web browser and go to:

```
http://localhost:8080
```

You should see the contents of `index.html`.

---

## 🔒 Limitations

* Only supports **HTTP GET requests for HTML files**.
* No MIME type detection (only `text/html` is sent).
* Not suitable for production environments — meant for learning purposes only.
* Does not support IPv6 or HTTPS.

---

## 🚀 Future Improvements

* Add thread-based concurrency using `pthread` for better performance.
* Implement support for multiple file types (CSS, JS, images, etc.).
* Parse HTTP request headers for better request handling.
* Add simple logging and error handling mechanisms.

---

## 📜 License

This project is open-source under the **MIT License**.
Feel free to modify and experiment with it for educational purposes.
