package view.panel;

import javax.swing.JPanel;
import javax.swing.JSlider;


public class MotorPositionPanel extends JPanel {
	
	private final JSlider slider;	
	
	public MotorPositionPanel() {
		slider = new JSlider(JSlider.HORIZONTAL, 0, 180, 0);
		slider.setMajorTickSpacing(30);
		slider.setPaintTicks(true);
		slider.setPaintLabels(true);
		this.add(slider);
	}
	
	public int getPosition() {
		return 0;
	}

}
