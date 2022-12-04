package view.panel;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JSlider;

import controller.SmartBridgeController;


public class MotorPositionPanel extends JPanel {
	
	private final JSlider slider;	
	private final JButton button;
	
	public MotorPositionPanel(final SmartBridgeController sBC) {
		this.setLayout(new GridBagLayout());
		slider = new JSlider(JSlider.HORIZONTAL, 0, 180, 0);
		slider.setMajorTickSpacing(30);
		slider.setPaintTicks(true);
		slider.setPaintLabels(true);
		
		button = new JButton("Manual Control OFF");
		button.addActionListener((e)->sBC.switchManualControl());
		
		this.add(slider, getGbc(0,0,1,2));
		this.add(button, getGbc(0,2,1,1));
	}
	
	public int getPosition() {
		return slider.getValue();
	}
	
	public void setManualControl(boolean manualControl) {
		if(manualControl) {
			button.setText("Manual Control ON");
		} else {
			button.setText("Manual Control OFF");
		}
	}
	
	private GridBagConstraints getGbc(final int x, final int y, final int width, final int height) {
		final var gbc = new GridBagConstraints();
		gbc.fill = GridBagConstraints.BOTH;
		gbc.gridx = x;
		gbc.gridy = y;
		gbc.gridwidth = width;
        gbc.gridheight = height;
		gbc.weightx=1.0;
		gbc.weighty=1.0;
		return gbc;
	}

}
