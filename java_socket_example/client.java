import java.io.*;
import java.net.*;
import java.util.*;

public class client {
    
    public static void main(String[] args) throws Exception {

        try (var socket = new Socket("127.0.0.1", 55550)) {
            
            System.out.println("Enter text to send to the server. Use Ctrl+Z or Ctrl+C to quit");
            
            var scanner = new Scanner(System.in);
            var input = new Scanner(socket.getInputStream());
            var output = new PrintWriter(socket.getOutputStream(), true);
            
            System.out.print("Message to send to server: ");
            
            // send messages to server and respond
            while (scanner.hasNextLine()) {
                output.println(scanner.nextLine());
                System.out.println("Sent message to the server!");
                System.out.println("Message recieved from server: " + input.nextLine());
                System.out.print("Message to send to server: ");
            }
        }
        catch(Exception e){
        	System.out.println("Connection closed with server.");
        }
    }
}
