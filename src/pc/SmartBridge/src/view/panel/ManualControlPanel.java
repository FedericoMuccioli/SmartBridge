package view.panel;

import java.awt.GridBagLayout;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JSlider;
import view.utility.MyGridBagConstraints;


public class ManualControlPanel extends JPanel {
	
	private final JSlider slider;	
	private final JButton button;
	private boolean isButtonPressed;
	
	/**
	 * Panel which allows to set value motor position.
	 */
	public ManualControlPanel() {
		this.setLayout(new GridBagLayout());
		slider = new JSlider(JSlider.HORIZONTAL, 0, 180, 0);
		slider.setMajorTickSpacing(30);
		slider.setPaintTicks(true);
		slider.setPaintLabels(true);
		
		isButtonPressed = false;
		
		button = new JButton("Manual Control OFF");
		button.addActionListener((e)-> isButtonPressed = true);
		
		this.add(slider, new MyGridBagConstraints(0,0,1,2));
		this.add(button, new MyGridBagConstraints(0,2,1,1));
	}
	
	/**
	 * Return position set.
	 * 
	 * @return the position
	 */
	public int getPosition() {
		return slider.getValue();
	}
	
	/**
	 * Return if is request the switch of the control mode.
	 * 
	 * @return if switch control request
	 */
	public boolean isSwitchControlRequest() {
		boolean isPressed = isButtonPressed;
		isButtonPressed = false;
		return isPressed;
	}
	
	/**
	 * Update manual control.
	 * 
	 * @param mode if manual control active or not.
	 */
	public void setMode(final String mode) {
		button.setText("Manual Control: " + mode);
	}

}
