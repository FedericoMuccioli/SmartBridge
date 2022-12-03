package view;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;

import javax.swing.JFrame;
import javax.swing.JPanel;

import view.panel.MotorPositionPanel;
import view.panel.SmartLightingStatePanel;
import view.panel.WaterLevelPanel;
import view.panel.WaterLevelStatePanel;

public class SmartBridgeGuiImpl implements SmartBridgeGui {
	
	private final JFrame frame;
	private final WaterLevelPanel waterLevel;
	private final SmartLightingStatePanel smartLightingState;
	private final WaterLevelStatePanel waterLevelState;
	private final MotorPositionPanel motorPosition;
	
	
	public SmartBridgeGuiImpl() {
		frame = new JFrame();
		final JPanel panel = new JPanel(new GridBagLayout());
		smartLightingState = new SmartLightingStatePanel();
		waterLevelState = new WaterLevelStatePanel();
		waterLevel = new WaterLevelPanel();
		motorPosition = new MotorPositionPanel();
		
		panel.add(waterLevel, getGbc(0,0,2,3));
		panel.add(smartLightingState, getGbc(2,0,1,1));
		panel.add(waterLevelState, getGbc(2,1,1,1));
		panel.add(motorPosition, getGbc(2,2,1,1));
		
		frame.add(panel);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setExtendedState(JFrame.MAXIMIZED_BOTH);
		frame.pack();
		frame.setResizable(false);
		frame.setVisible(true);
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
	@Override
	public void setSmartLightingState(final int smartLightingState) {
		this.smartLightingState.setState(smartLightingState);
	}

	@Override
	public void setWaterLevelState(final int waterLevelState) {
		this.waterLevelState.setState(waterLevelState);
		
	}

	@Override
	public void setWaterLevel(final int value) {
		this.waterLevel.printWaterLevel(value);
	}

	@Override
	public int getWaterLevel() {
		// TODO Auto-generated method stub
		return 0;
	}

}
