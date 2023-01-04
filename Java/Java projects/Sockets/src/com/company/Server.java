package com.company;

import java.io.*;
import java.net.*;

public class Server {
    private ServerSocket serverSocket;
    private Socket clientSocket;
    private PrintWriter out;
    private BufferedReader in;

    public Server(int port) throws IOException {
        serverSocket = new ServerSocket(port);
        System.out.println("Waiting client connection...");
        clientSocket = serverSocket.accept();
        System.out.println("Client was connected");
        out = new PrintWriter(clientSocket.getOutputStream(), true);
        in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
    }

    public void stop() throws IOException {
        in.close();
        out.close();
        clientSocket.close();
        serverSocket.close();
    }

    public void sendMessage(String str) {
        out.println(str);
    }

    public String recieveMessage() throws IOException {
        return in.readLine();
    }
}
