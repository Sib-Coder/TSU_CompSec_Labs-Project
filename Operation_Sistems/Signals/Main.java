import java.io.*;
import java.net.*;

public class Main {

    public static void main(String[] args) {
        try {
            ServerSocket serverSocket = new ServerSocket(6666);

            while (true) {
                Socket clientSocket = serverSocket.accept();
                System.out.println("Подключение с такого адреса: " + clientSocket.getInetAddress() + " "+ String.valueOf( clientSocket.getLocalPort()));
                new Thread(new ClientHandler(clientSocket)).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static class ClientHandler implements Runnable {
        private Socket clientSocket;

        public ClientHandler(Socket clientSocket) {
            this.clientSocket = clientSocket;
        }

        @Override
        public void run() {
            try {
                BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                //PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);

                String inputLine;
                while ((inputLine = in.readLine()) != null) {
                    // Обработка входящих сообщений от клиента
                    System.out.println("Клиент "+clientSocket.getInetAddress() +" прислал : " + inputLine);
                    //out.println("Server received: " + inputLine);
                }
                in.close();
                //out.close();
                clientSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}

