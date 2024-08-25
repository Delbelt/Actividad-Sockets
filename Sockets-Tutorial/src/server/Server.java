package server;

import java.net.ServerSocket;
import java.net.Socket;
import models.MasterSocket;
import utils.Definitions;
import java.io.IOException;


public class Server {

	public static void main(String[] args) throws IOException {
		ServerSocket server = new ServerSocket(Definitions.PORT);
		
		System.out.println("Esperando una conexion...");
		
		Socket socket = server.accept();
		
		MasterSocket masterSocket = new MasterSocket(socket, "server");		
		
		masterSocket.receiveMessage();
		
		masterSocket.sendMessage("Soy el servidor");
		
		server.close();
	}
}
