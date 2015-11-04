package edu.purdue.gouy;

import java.io.BufferedReader;
import java.io.Closeable;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;
import java.sql.Time;
import java.text.SimpleDateFormat;
import java.util.Date;

import edu.purdue.gouy.R;
import android.app.Fragment;
import android.util.Log;
import android.view.View.OnClickListener;
import android.os.Bundle;
import android.os.AsyncTask;
import android.os.StrictMode;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

/**
 * This fragment is the "page" where the application display the log from the
 * server and wait for a match.
 *
 * @author gouy
 */
public class MatchFragment extends Fragment implements OnClickListener {

	private static final String DEBUG_TAG = "DEBUG";

	/**
	 * Activity which have to receive callbacks.
	 */
	private StartOverCallbackListener activity;

	/**
	 * AsyncTask sending the request to the server.
	 */
	private Client client;

	/**
	 * Coordinate of the server.
	 */
	private String host;
	private int port;

	/**
	 * Command the user should send.
	 */
	private String command;
	
	private int type;
	private String name;
	private String fromLocation;
	private String toLocation;
	
	private boolean reachableServer;
	
	private String result;
	

	
	private PrintWriter out;
	private BufferedReader in;
	private Socket s;
	
	//Elements form the Layout here 
	private TextView tv_log;
	private TextView tv_fromLocation;
	private TextView tv_toLocation;
	private TextView tv_name;
	private TextView tv_status;

	// TODO: your own class fields here

	// Class methods
	/**
	 * Creates a MatchFragment
	 * 
	 * @param activity
	 *            activity to notify once the user click on the start over
	 *            Button.
	 * @param host
	 *            address or IP address of the server.
	 * @param port
	 *            port number.
	 * 
	 * @param command
	 *            command you have to send to the server.
	 * 
	 * @return the fragment initialized.
	 */
	// TODO: you can add more parameters, follow the way we did it.
	// ** DO NOT CREATE A CONSTRUCTOR FOR MatchFragment **
	public static MatchFragment newInstance(StartOverCallbackListener activity,
			String host, int port, String command,String name,int type, String fromLocation, String toLocation) {
		MatchFragment f = new MatchFragment();

		f.activity = activity;
		f.host = host;
		f.port = port;
		f.command = command;
		f.type = type;
		f.name = name;
		f.fromLocation = fromLocation;
		f.toLocation = toLocation;
				

		return f;
	}

	/**
	 * Called when the fragment will be displayed.
	 */
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		StrictMode.setThreadPolicy(new StrictMode.ThreadPolicy.Builder()
		.detectDiskReads()
		.detectDiskWrites()
		.detectNetwork()   // or .detectAll() for all detectable problems
		.penaltyLog()
		.build());
		StrictMode.setVmPolicy(new StrictMode.VmPolicy.Builder()
		.detectLeakedSqlLiteObjects()
		.detectLeakedClosableObjects()
		.penaltyLog()
		.penaltyDeath()
		.build());
		
		
		if (container == null) {
			return null;
		}

		View view = inflater.inflate(R.layout.match_fragment_layout, container,
				false);

		/**
		 * Register this fragment to be the OnClickListener for the startover
		 * button.
		 */
		view.findViewById(R.id.bu_start_over).setOnClickListener(this);
		
		this.tv_fromLocation = (TextView) view.findViewById(R.id.tv_logFrom);
		this.tv_toLocation = (TextView) view.findViewById(R.id.tv_logTo);
		this.tv_name = (TextView) view.findViewById(R.id.tv_logName);
		this.tv_log = (TextView) view.findViewById(R.id.tv_log);
		this.tv_status = (TextView) view.findViewById(R.id.tv_logStatus);
		
		// TODO: import your Views from the layout here. See example in
		// ServerFragment.

		/**
		 * Launch the AsyncTask
		 */
		
		this.client = new Client();
		this.client.execute("");


		return view;
	}

	/**
	 * Callback function for the OnClickListener interface.
	 */
	@Override
	public void onClick(View v) {
		/**
		 * Close the AsyncTask if still running.
		 */
		this.client.close();
		updateStatus("Closed");

		/**
		 * Notify the Activity.
		 */
		this.activity.onStartOver();
	}
	
	
	public static String getCurrentTimeStamp(){
	    try {

	        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
	        String currentTimeStamp = dateFormat.format(new Date()); // Find todays date

	        return currentTimeStamp;
	    } catch (Exception e) {
	        e.printStackTrace();

	        return null;
	    }
	}
	
	public void updateLog(String str) {
		String rVal = tv_log.getText().toString();
		rVal += ("[" + getCurrentTimeStamp() + "]" + " " + str + "\n"); 
		tv_log.setText(rVal);
	}
	public void updateStatus(String msg) {
		tv_status.setText(msg);
	}
	public static boolean isReachable(String host, int port, int timeout) {
	    try {
	        Socket socket = new Socket();
	        SocketAddress socketAddress = new InetSocketAddress(host, port);
	        socket.connect(socketAddress, timeout);
	        socket.close();
	        return true;
	    } catch (IOException e) {
	        return false;
	    }
	}
	
	

	class Client extends AsyncTask<String, String, String> implements Closeable {

		/**
		 * NOTE: you can access MatchFragment field from this class:
		 * 
		 * Example: The statement in doInBackground will print the message in
		 * the Eclipse LogCat view.
		 */

		/**
		 * The system calls this to perform work in a worker thread and delivers
		 * it the parameters given to AsyncTask.execute()
		 */
		protected String doInBackground(String... params) {

			/**
			 * TODO: Your Client code here.
			 */
			if(reachableServer){
			Log.d(DEBUG_TAG, String
					.format("The Server at the address %s uses the port %d",
							host, port));

			Log.d(DEBUG_TAG, String.format(
					"The Client will send the command: %s", command));
			
	        try {
	                s = new Socket(host, port);
	        		
	                out = new PrintWriter(s.getOutputStream(), true);
	                in = new BufferedReader(new InputStreamReader(s.getInputStream()));
	            
        			if(s != null) { publishProgress("Connected to Server" , "Connected");}
	                out.println(name + "," + fromLocation + "," +
	                		toLocation + "," + type);
	                publishProgress("Request Sent to Server, Waiting for Matching" , "Requested");
	                for (;;) {
	                    result = in.readLine();
	                    if (result.startsWith("RESPONSE: ")) { 
	            			Log.d(DEBUG_TAG, result.substring(9).trim());
	                    	String[] rVal = result.substring(9).trim().split(",");
	                    	
	                    	publishProgress("Match Found!" ,"Matched", rVal[0], rVal[1], rVal[2] , rVal[3]);
	                    	out.println(":ACK");
	                    	break;
	                    }
	                    
	                    if (result.startsWith("ERROR: ")) {
	                    	publishProgress(("Error message from server: " + result.substring(5).trim()),"Error" );
	                    	break;
	                    }
	                    
	                }
	            } catch (IOException e) {
	                publishProgress("Local IO Error", "Error");
	            }
			}


			return "";
		}
		public void close() {
			try {
				out.close();
				in.close();
				s.close();
			} catch (Exception e) {
			}
			//updateStatus("Closed");
                    // TODO: Clean up the client
		}

		/**
		 * The system calls this to perform work in the UI thread and delivers
		 * the result from doInBackground()
		 */

		// TODO: use the following method to update the UI.
		// ** DO NOT TRY TO CALL UI METHODS FROM doInBackground!!!!!!!!!! **

		/**
		 * Method executed just before the task.
		 */
		@Override
		protected void onPreExecute() {
			
			tv_fromLocation.setText(fromLocation);
			if(!toLocation.equals("*")) tv_toLocation.setText(toLocation);
			else tv_toLocation.setText("Pending");
			tv_name.setText("Pending");
			tv_log.setText("");
			tv_status.setText("Establishing Connection");
			
			
			updateLog("Testing Connection, Timeout: 1000ms");
			Log.d(DEBUG_TAG, "Testing Connection");
			reachableServer = isReachable(host,port,1000);
			if(reachableServer) {
				updateLog("Connection Test Success");
				updateLog(String.format("Connecting to the Server at the address %s uses the port %d",
						host, port));
			}else {
				updateLog("Connection Test Fail");
				updateStatus("Disconnected");
				Log.d(DEBUG_TAG, "Test Fail");
			}
			
		}

		/**
		 * Method executed once the task is completed.
		 */
		@Override
		protected void onPostExecute(String result) {
			updateLog("Session Over, Disconnecting from the Server");
			close();
			updateLog("Disconnected");

			
		}

		/**
		 * Method executed when progressUpdate is called in the doInBackground
		 * function.
		 */
		@Override
		protected void onProgressUpdate(String... result) {
			if(!result[1].equals("Matched")) {
				updateLog(result[0]);
				updateStatus(result[1]);
			} else {
				updateLog(result[0]);
				updateStatus(result[1]);
				tv_name.setText(result[2]);
				tv_fromLocation.setText(result[3]);
				if(!result[4].equals("*")) tv_toLocation.setText(result[4]);
			}
			
			
			
		}
	}

}
