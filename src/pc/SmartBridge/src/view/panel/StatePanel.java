package view.panel;

import java.awt.GridBagLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;

public abstract class StatePanel extends JPanel {
	
	private final JLabel value;
	
	public StatePanel(final String stateName){
		this.setLayout(new GridBagLayout());
		JLabel state = new JLabel(stateName + ": ");
		value = new JLabel();
		this.add(state);
		this.add(value);
	}
	
	public void setState(final String state) {
		value.setText(state);
	}

}
