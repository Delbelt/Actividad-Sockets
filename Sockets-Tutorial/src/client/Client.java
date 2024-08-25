package client;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import models.MasterSocket;
import utils.Definitions;

public class Client {

	public static final int VALUE_ASCII = 48;

	public static void clearConsole() {
		try {
			if (System.getProperty("os.name").contains("Windows")) {
				new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
			} else {
				new ProcessBuilder("clear").inheritIO().start().waitFor();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	static void addLineBreak() {
		System.out.println("");
	}

	public static int mainMenu() throws IOException {
		int optionSwitch;
		int optionReturn;

		do {
			addLineBreak();
			System.out.println("*** 1- GENERAR NOMBRE DE USUARIO ***");
			addLineBreak();
			System.out.println("*** 2- GENERAR CLAVE DE USUARIO ***");
			addLineBreak();
			System.out.println("*** 3- SALIR DEL PROGRAMA ***");
			addLineBreak();
			System.out.print("ELIJA UNA OPCION: ");

			int input = System.in.read();
			System.in.read();

			optionSwitch = input - VALUE_ASCII;
			optionReturn = input - VALUE_ASCII;

			switch (optionSwitch) {
			case 1:
			case 2:
			case 3:
				optionSwitch = 3;
				break;
			default:
				clearConsole();
				System.out.print("OPCION INCORRECTA, ELIJA DE NUEVO POR FAVOR: ");
			}

		} while (optionSwitch != 3);

		return optionReturn;

	}

	public static void main(String[] args) throws IOException {
		Socket socket = new Socket(Definitions.HOST, Definitions.PORT);

		MasterSocket masterSocket = new MasterSocket(socket, "client");

		int option = mainMenu();

		String response = Integer.toString(option);

		masterSocket.sendMessage(response);

		response = masterSocket.receiveMessage();

		System.out.println(response);

		System.in.read();
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		String inputLine = reader.readLine();

		option = Integer.parseInt(inputLine.trim());

		response = Integer.toString(option);

		masterSocket.sendMessage(response);

		masterSocket.showMessage();

		socket.close();
	}

}
