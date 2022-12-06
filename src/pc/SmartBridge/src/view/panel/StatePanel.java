package view.panel;

import java.awt.GridBagLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;

/**
 * State panel. Allows to show state.
 * @author federico
 */
public abstract class StatePanel extends JPanel {
	
	private final JLabel value;
	
	/**
	 * Create state panel of the name state specified.
	 * 
	 * @param stateName the name of the state
	 */
	public StatePanel(final String stateName){
		this.setLayout(new GridBagLayout());
		JLabel state = new JLabel(stateName + ": ");
		value = new JLabel();
		this.add(state);
		this.add(value);
	}
	
	/**
	 * Set state to view.
	 * 
	 * @param state state to view
	 */
	public void setState(final String state) {
		value.setText(state);
	}

}
