package models;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

public class MasterSocket {

	private Socket socket;
	private String alias;

	public MasterSocket(Socket socket, String alias) {
		super();
		this.socket = socket;
		this.alias = alias.toUpperCase() + ": ";
	}

	public Socket getSocket() {
		return socket;
	}

	public void setSocket(Socket socket) {
		this.socket = socket;
	}

	public String getAlias() {
		return alias;
	}

	public void setAlias(String alias) {
		this.alias = alias;
	}

	public void sendMessage(String message) throws IOException {

		PrintWriter sender = null;

		sender = new PrintWriter(socket.getOutputStream());
		sender.println(message);
		sender.flush();
	}

	public void showMessage() throws IOException {
	
		InputStreamReader receiver = new InputStreamReader(socket.getInputStream());
		BufferedReader buffer = new BufferedReader(receiver);

		String receiveMessage = buffer.readLine();		

		System.out.println(receiveMessage);
	}
	
    public String receiveMessage() throws IOException {
        BufferedReader buffer = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        String receiveMessage = buffer.readLine();

        return receiveMessage;
    }

}
