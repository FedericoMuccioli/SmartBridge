package view.panel;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JSlider;


public class MotorPositionPanel extends JPanel {
	
	private final JSlider slider;	
	
	public MotorPositionPanel() {
		this.setLayout(new GridBagLayout());
		slider = new JSlider(JSlider.HORIZONTAL, 0, 180, 0);
		slider.setMajorTickSpacing(30);
		slider.setPaintTicks(true);
		slider.setPaintLabels(true);
		
		slider.addChangeListener((e)-> {
			
			    JSlider source = (JSlider)e.getSource();
			    if (!source.getValueIsAdjusting()) {
			        int value = (int)source.getValue();
			        System.out.println(value);
			    }
			
		});
		
		final var button = new JButton("Manual Control");
		
		this.add(slider, getGbc(0,0,1,2));
		this.add(button, getGbc(0,2,1,1));
		
	}
	
	public int getPosition() {
		return 0;
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
