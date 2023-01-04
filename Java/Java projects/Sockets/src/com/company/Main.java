package com.company;

import java.io.IOException;
import java.util.Scanner;

public class Main {
    private static Scanner val;

    public static void main(String[] args) {
        val = new Scanner(System.in);
        System.out.print("Chose s or c: ");
        String who = val.nextLine();
        //val.skip("\n");

        if (who.equals("s")) {
            start_server();
        }
        else if (who.equals("c")) {
            start_client();
        }
        else System.out.println("Wrong chose");
    }

    public static void start_server() {
        System.out.print("Enter the port: ");
        int port = val.nextInt();
        //val.skip("\n");

        try {
            Server server = new Server(port);
            System.out.println("Server was created with port " + port);
            System.out.println("Waiting message...");
            System.out.println(server.recieveMessage());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void start_client() {
        System.out.print("Enter the IP: ");
        String ip = val.nextLine();
        //val.skip("\n");
        System.out.print("Enter the port: ");
        int port = val.nextInt();
        val.skip("\n");

        try {
            Client client = new Client(ip, port);
            System.out.print("Enter the message: ");
            String message = val.nextLine();
            client.sendMessage(message);
            System.out.print("Press Enter to exit...");
            val.skip("\n");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
