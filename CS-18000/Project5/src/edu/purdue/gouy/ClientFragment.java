package edu.purdue.gouy;

import edu.purdue.gouy.R;
import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Spinner;

/**
 * This fragment is the "page" where the user inputs information about the
 * request, he/she wishes to send.
 *
 * @author gouy
 */
public class ClientFragment extends Fragment implements OnClickListener {

	/**
	 * Activity which have to receive callbacks.
	 */
	private SubmitCallbackListener activity;

	/**
	 * Creates a ProfileFragment
	 * 
	 * @param activity
	 *            activity to notify once the user click on the submit Button.
	 * 
	 *            ** DO NOT CREATE A CONSTRUCTOR FOR MatchFragment **
	 * 
	 * @return the fragment initialized.
	 */
	
	private Spinner spinner1;
	private Spinner spinner2;
	private EditText name;  
	private RadioButton rb;
	private RadioGroup select;
	private View thisView;
	// ** DO NOT CREATE A CONSTRUCTOR FOR ProfileFragment **
	public static ClientFragment newInstance(SubmitCallbackListener activity) {
		ClientFragment f = new ClientFragment();

		f.activity = activity;
		return f;
	}

	/**
	 * Called when the fragment will be displayed.
	 */
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		if (container == null) {
			return null;
		}

		View view = inflater.inflate(R.layout.client_fragment_layout,
				container, false);
		this.thisView = view;

		/**
		 * Register this fragment to be the OnClickListener for the submit
		 * Button.
		 */
		view.findViewById(R.id.bu_submit).setOnClickListener(this);
		this.spinner1 = (Spinner) view.findViewById(R.id.spinner1);
		// Create an ArrayAdapter using the string array and a default spinner layout
		ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(getActivity().getBaseContext(),
		        R.array.locationsWithoutStar, android.R.layout.simple_spinner_item);
		// Specify the layout to use when the list of choices appears
		adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		// Apply the adapter to the spinner
		spinner1.setAdapter(adapter);
		this.spinner2 = (Spinner) view.findViewById(R.id.spinner2);
		// Create an ArrayAdapter using the string array and a default spinner layout
		// Specify the layout to use when the list of choices appears
		// Apply the adapter to the spinner
		adapter = ArrayAdapter.createFromResource(getActivity().getBaseContext(),
		        R.array.locations, android.R.layout.simple_spinner_item);
		// Specify the layout to use when the list of choices appears
		adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		spinner2.setAdapter(adapter);
		
		this.name =  (EditText) view.findViewById(R.id.et_name);
		
		this.select = (RadioGroup) view.findViewById(R.id.radioGroup1);
		


		// TODO: import your Views from the layout here. See example in
		// ServerFragment.

		return view;
	}

	/**
	 * Callback function for the OnClickListener interface.
	 */
	@Override
	public void onClick(View v) {
		this.activity.onSubmit();
	}
	public String getName() {
		return name.getText().toString();
	}
/*	public String getLocation() {
		rb = (RadioButton) thisView.findViewById(select.getCheckedRadioButtonId());
		return rb.getText().toString();
	}*/
	public int getPrefIndex() {
		rb = (RadioButton) thisView.findViewById(select.getCheckedRadioButtonId());
		return this.select.indexOfChild(rb);
	}
	public String getFrom() {
		return spinner1.getSelectedItem().toString(); 
	}
	public String getTo() {
		return spinner2.getSelectedItem().toString();
	}
}

