
import java.io.*;
import java.net.ServerSocket;
import java.net.SocketException;
import java.net.Socket;
import java.util.ArrayList;
public class SafeWalkServer implements Runnable{
    /**
     * Construct the server, set up the socket.
     * 
     * @throws SocketException if the socket or port cannot be obtained properly.
     * @throws IOException if the port cannot be reused.
     */
    
    int port;
    ServerSocket seversocket;
    ArrayList<String[]> onHold = new ArrayList<String[]>();
    ArrayList<Socket> onHoldSocket = new ArrayList<Socket>();
    PrintWriter out;
    BufferedReader in;
    String[] event;
    public SafeWalkServer(int port) throws SocketException, IOException {
        //TODO: finish the method
        this.port = port;
        seversocket = new ServerSocket(port);
        seversocket.setReuseAddress(true);
        if (port < 1025 || port > 65535) {
            System.out.println("Invalid port, exit.");
        }
    }
    
    /**
     * Construct the server and let the system allocate it a port.
     * 
     * @throws SocketException if the socket or port cannot be obtained properly.
     * @throws IOException if the port cannot be reused.
     */
    public SafeWalkServer() throws SocketException, IOException {
        //TODO: finish the method
        seversocket = new ServerSocket(0);
        this.port = seversocket.getLocalPort();
        seversocket.setReuseAddress(true);
        System.out.println("Port not specified. Using free port "+ port +".");
    }
    
    /**
     * Return the port number on which the server is listening. 
     */
    public int getLocalPort() {
        //TODO: finish this method
        return this.port;
    }
    
    /**
     * Start a loop to accept incoming connections.
     * @throws IOException, SocketException 
     */
    public void run() {
        //TODO: finish this method
        while (true) {
            Socket client = null;
            String ans = "";
            boolean success = false;
            boolean run = true;
            try {
                client = seversocket.accept();
            } catch (IOException e) {
                System.err.println(e);
            }
            try {
                out.close();
                in.close();
                out = new PrintWriter(client.getOutputStream(), true);
                in = new BufferedReader(new InputStreamReader(client.getInputStream()));
                ans  = in.readLine();
            }
            catch (IOException e) {
                System.err.println(e);
            }
            try {
                int check = validityCheck(ans,client);
                if(check == 1) {
                    success = handleEvent(event,client);
                }
                else if (check > 1) {
                    run = handleRequest(check,client);
                }
                if(success) {
                    cleanUp(client);
                }
            }
            catch (IOException e) {
                System.err.println(e);
            }
            if(!run) {
                break;
            }
        }
    }
    
    /**
     * Check the validity
     * @throws IOException, SocketException 
     */
    public int validityCheck(String s,Socket c) throws SocketException, IOException {
        out.close();
        in.close();
        out = new PrintWriter(c.getOutputStream(), true);
        in = new BufferedReader(new InputStreamReader(c.getInputStream()));
        if (!s.substring(0,1).equals(":")) {  //request
            if (s.contains(",")) 
                event = s.split(",");
            if(event.length == 4) {
                return 1;
            }
            else {
                out.println("ERROR: invalid request");
                c.close();
                return 0;
            }
        }
        else {  //command
            if (s.equals(":LIST_PENDING_REQUESTS\n"))
                return 2;
            else if (s.equals(":RESET\n"))
                return 3;
            else if (s.equals(":SHUTDOWN\n"))
                return 4;
            else {
                out.println("ERROR: invalid command");
                c.close();
                return 0;
            }
        }
    }
    
    /**
     * handle requests and commands
     * @throws IOException, SocketException 
     */
    public boolean handleRequest(int s, Socket c) throws SocketException, IOException  {
        out.close();
        out = new PrintWriter(c.getOutputStream(), true);
        if(s == 2) { //:LIST_PENDING_REQUESTS
            String rVal = "";
            String[] temp;
            for(int i = 0; i < onHold.size(); i ++) {
                temp = onHold.get(i);
                rVal += "["+ temp[0] +", "+ temp[1] +", "+ temp[2] +", "+ temp[3] +"], ";
            }
            out.println("["+ rVal.substring(0,(rVal.length() - 2)) +"]");
            out.close();
            c.close();
            return true;
        }
        if(s == 3) { //:RESET
            Socket tempS;
            PrintWriter tout;
            for(int i = 0; i < onHold.size(); i ++){
                tempS = onHoldSocket.get(i);
                tout = new PrintWriter(tempS.getOutputStream(), true);
                tout.println("ERROR: connection reset");
                tout.close();
                tempS.close();
            }
            out.println("RESPONSE: success");
            out.close();
            c.close();
            onHold.clear();
            onHoldSocket.clear();
            return true;
        }
        if(s == 4) { //:SHUTDOWN
            Socket tempS;
            PrintWriter tout;
            for(int i = 0; i < onHold.size(); i ++){
                tempS = onHoldSocket.get(i);
                tout = new PrintWriter(tempS.getOutputStream(), true);
                tout.println("ERROR: connection reset");
                tout.close();
                tempS.close();
            }
            out.println("RESPONSE: sutting down");
            out.close();
            c.close();
            onHold.clear();
            onHoldSocket.clear();
            seversocket.close();
            return false;
        }
        return false;
    }
    
    public boolean handleEvent(String[] event,Socket c) throws SocketException, IOException  {
        out.close();
        in.close();
        out = new PrintWriter(c.getOutputStream(), true);
        in = new BufferedReader(new InputStreamReader(c.getInputStream()));
        boolean check = false;
        String[] temp;
        Socket tempS;
        for(int i = 0; i < onHold.size(); i ++){
            temp = onHold.get(i);
            tempS = onHoldSocket.get(i);
            if (event[1].equals(temp[1]) && (event[2].equals(temp[2]) || temp[2].equals("*"))) {
                out.println("RESPONSE: " + temp[0] + "," + temp[1] + "," + temp[2] + "," + temp[3]); 
                new PrintWriter(tempS.getOutputStream(), true).println("RESPONSE: " + event[0] + "," + event[1] + "," + event[2] + "," + event[3]);
                tempS.close();
                c.close();
                onHold.remove(i);
                onHoldSocket.remove(i);
                return true;
            }
        }
        //如果没有成功匹配 加入列表
        onHold.add(event);
        onHoldSocket.add(c);
        return false;
    }
    
    /**
     * Clean up
     * @throws IOException, SocketException 
     */
    public void cleanUp(Socket c)  throws SocketException, IOException {
        out.close();
        in.close();
        c.close();
    }
}
