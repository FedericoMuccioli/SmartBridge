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
	
	public int getPosition() {
		return slider.getValue();
	}
	
	public boolean isSwitchControlRequest() {
		boolean isPressed = isButtonPressed;
		isButtonPressed = false;
		return isPressed;
	}
	
	public void setMode(boolean mode) {
		if(mode) {
			button.setText("Manual Control ON");
		} else {
			button.setText("Manual Control OFF");
		}
	}

}