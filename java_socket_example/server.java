import java.io.*;
import java.net.*;
import java.util.*;
import java.util.concurrent.*;

public class server {

    public static void main(String[] args) throws Exception {

    	// Establish the server
        try (var listener = new ServerSocket(55550)) {
            System.out.println("The server is now listening for connections...");
            var pool = Executors.newFixedThreadPool(10);
            // Start a new thread for each connection
            while (true) {
                pool.execute(new chatConnection(listener.accept()));
            }
        }
    }

    private static class chatConnection implements Runnable {
        
        private Socket socket;

        chatConnection(Socket socket) {
            this.socket = socket;
        }

        @Override
        public void run() {
            System.out.println("Client connected: " + socket);
            try {
            	var scanner = new Scanner(System.in);
                var input = new Scanner(socket.getInputStream());
                var output = new PrintWriter(socket.getOutputStream(), true);
                
                // recieve messages from client and respond
                while (input.hasNextLine()) {
                	System.out.println("Message from Client: " + input.nextLine());
                	System.out.print("Send to Client:");
                    output.println(scanner.nextLine());
                }
            } catch (Exception e) {
                System.out.println("Error:" + socket);
            } finally {
                try {
                    socket.close();
                } catch (IOException e) {
                }
                System.out.println("Closed connection: " + socket);
            }
        }
    }
}
