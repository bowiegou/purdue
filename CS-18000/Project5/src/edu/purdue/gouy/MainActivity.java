package edu.purdue.gouy;

import edu.purdue.gouy.R;

import android.annotation.SuppressLint;
import android.app.ActionBar;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.FragmentTransaction;
import android.content.DialogInterface;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;

/*
 * @author gouy
 */

public class MainActivity extends Activity implements SubmitCallbackListener,
		StartOverCallbackListener {

	/**
	 * The ClientFragment used by the activity.
	 */
	private ClientFragment clientFragment;

	/**
	 * The ServerFragment used by the activity.
	 */
	private ServerFragment serverFragment;

	/**
	 * UI component of the ActionBar used for navigation.
	 */
	private Button left;
	private Button right;
	private TextView title;
//	private Spinner spinner1;
	private AlertDialog.Builder builder1;
	//private Spinner spinner2;
	/**
	 * Called once the activity is created.
	 */
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main_layout);

		this.clientFragment = ClientFragment.newInstance(this);
		this.serverFragment = ServerFragment.newInstance();
		
		
		builder1 = new AlertDialog.Builder(this);
        builder1.setMessage("Coded by gouy");
        builder1.setCancelable(true);
        builder1.setPositiveButton("Yes",
                new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int id) {
                dialog.cancel();
            }
        });


		FragmentTransaction ft = getFragmentManager().beginTransaction();
		ft.add(R.id.fl_main, this.clientFragment);
		ft.commit();
	}

	/**
	 * Creates the ActionBar: - Inflates the layout - Extracts the components
	 */
	@SuppressLint("InflateParams")
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		final ViewGroup actionBarLayout = (ViewGroup) getLayoutInflater()
				.inflate(R.layout.action_bar, null);

		// Set up the ActionBar
		final ActionBar actionBar = getActionBar();
		actionBar.setDisplayShowHomeEnabled(false);
		actionBar.setDisplayShowTitleEnabled(false);
		actionBar.setDisplayShowCustomEnabled(true);
		actionBar.setCustomView(actionBarLayout);

		// Extract the UI component.
		this.title = (TextView) actionBarLayout.findViewById(R.id.tv_title);
		this.left = (Button) actionBarLayout.findViewById(R.id.bu_left);
		this.right = (Button) actionBarLayout.findViewById(R.id.bu_right);
		this.right.setVisibility(View.INVISIBLE);

		return true;
	}

	/**
	 * Callback function called when the user click on the right button of the
	 * ActionBar.
	 * 
	 * @param v
	 */
	public void onRightClick(View v) {
		FragmentTransaction ft = getFragmentManager().beginTransaction();

		this.title.setText(this.getResources().getString(R.string.client));
		this.left.setVisibility(View.VISIBLE);
		this.right.setVisibility(View.INVISIBLE);
		ft.replace(R.id.fl_main, this.clientFragment);
		ft.commit();
	}

	/**
	 * Callback function called when the user click on the left button of the
	 * ActionBar.
	 * 
	 * @param v
	 */
	public void onLeftClick(View v) {
		FragmentTransaction ft = getFragmentManager().beginTransaction();

		this.title.setText(this.getResources().getString(R.string.server));
		this.left.setVisibility(View.INVISIBLE);
		this.right.setVisibility(View.VISIBLE);
		ft.replace(R.id.fl_main, this.serverFragment);
		ft.commit();

	}

	/**
	 * Callback function called when the user click on the submit button.
	 */
	@Override
	public void onSubmit() {
		// TODO: Get client info via client fragment
		String name = this.clientFragment.getName();
		int type = this.clientFragment.getPrefIndex();
		String fromLocation = this.clientFragment.getFrom();
		String toLocation = this.clientFragment.getTo();
		AlertDialog alert;

		// Server info
		String host = this.serverFragment.getHost(getResources().getString(
				R.string.default_host));
		int port = this.serverFragment.getPort(Integer.parseInt(getResources()
				.getString(R.string.default_port)));
		// TODO: sanity check the results of the previous two dialogs
		if(!checkClient(type,fromLocation,toLocation).equals("")){
			builder1.setMessage(checkClient(type,fromLocation,toLocation));
			alert = builder1.create();
			alert.show();
			return;
		}
		if(!checkServer(host,port).equals("")){
			builder1.setMessage(checkServer(host,port));
			alert = builder1.create();
			alert.show();
			return;
		}

		// TODO: Need to get command from client fragment
		String command = this.getResources()
				.getString(R.string.default_command);

		FragmentTransaction ft = getFragmentManager().beginTransaction();

		this.title.setText(getResources().getString(R.string.match));
		this.left.setVisibility(View.INVISIBLE);
		this.right.setVisibility(View.INVISIBLE);

		// TODO: You may want additional parameters here if you tailor
		// the match fragment
		MatchFragment frag = MatchFragment.newInstance(this, host, port,
				command,name,type,fromLocation,toLocation);

		ft.replace(R.id.fl_main, frag);
		ft.commit();
	}
	
	public String checkClient(int type, String from, String to) {
		String rVal = "";
//		if(type < 0 || type > 3)
//			rVal = false;
		if(from.equals(to))
			rVal = "Destination cannot be same as your departure location";
		if(type == 1 && to.equals("*"))
			rVal = "You are a requester; your destination should not be undetermined";
		
		return rVal;
	}
	
	public String checkServer(String host, int port) {
		String rVal = "";
		if(host == null || host.equals("") || host.contains(" ")) 
			rVal = "Server address invaild";
		if(port < 1 || port > 65535)
			rVal = "Server port invaild";
		return rVal;
	}
	

	/**
	 * Callback function call from MatchFragment when the user want to create a
	 * new request.
	 */
	@Override
	public void onStartOver() {
		onRightClick(null);
	}

}
