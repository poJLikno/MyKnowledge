package com.company;

import java.io.*;
import java.net.*;

public class Client {
    private Socket clientSocket;
    private PrintWriter out;
    private BufferedReader in;

    public Client(String ip, int port) throws IOException {
        clientSocket = new Socket(ip, port);
        out = new PrintWriter(clientSocket.getOutputStream(), true);
        in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
    }

    public void stop() throws IOException {
        in.close();
        out.close();
        clientSocket.close();
    }

    public void sendMessage(String str) {
        out.println(str);
    }

    public String recieveMessage() throws IOException {
        return in.readLine();
    }
}
