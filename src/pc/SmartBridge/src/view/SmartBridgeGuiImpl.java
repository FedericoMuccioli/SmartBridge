package view;

import java.awt.GridBagLayout;
import javax.swing.JFrame;
import javax.swing.JPanel;
import view.panel.ManualControlPanel;
import view.panel.SmartLightingStatePanel;
import view.panel.WaterLevelPanel;
import view.panel.WaterLevelStatePanel;
import view.utility.MyGridBagConstraints;

public class SmartBridgeGuiImpl implements SmartBridgeGui {
	
	private final JFrame frame;
	private final WaterLevelPanel waterLevel;
	private final SmartLightingStatePanel smartLightingState;
	private final WaterLevelStatePanel waterLevelState;
	private final ManualControlPanel manualControl;
	
	/**
	 * Implementation of the gui of the smart bridge. Show a chart with water level on the time.
	 * The states of water level, smart lighting and manual control.
	 * Allow to set motor position.
	 */
	public SmartBridgeGuiImpl() {
		frame = new JFrame();
		final JPanel panel = new JPanel(new GridBagLayout());
		smartLightingState = new SmartLightingStatePanel();
		waterLevelState = new WaterLevelStatePanel();
		waterLevel = new WaterLevelPanel();
		manualControl = new ManualControlPanel();
		
		panel.add(waterLevel, new MyGridBagConstraints(0,0,2,3));
		panel.add(smartLightingState, new MyGridBagConstraints(2,0,1,1));
		panel.add(waterLevelState, new MyGridBagConstraints(2,1,1,1));
		panel.add(manualControl, new MyGridBagConstraints(2,2,1,1));
		
		frame.add(panel);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setExtendedState(JFrame.MAXIMIZED_BOTH);
		frame.pack();
		frame.setResizable(false);
		frame.setVisible(true);
	}

	@Override
	public void printSmartLightingState(final String smartLightingState) {
		this.smartLightingState.setState(smartLightingState);
	}

	@Override
	public void printWaterLevelState(final String waterLevelState) {
		this.waterLevelState.setState(waterLevelState);
	}

	@Override
	public void printWaterLevel(final int value) {
		this.waterLevel.print(value);
	}

	@Override
	public int getPosition() {
		return manualControl.getPosition();
	}

	@Override
	public void printManualControl(final String mode) {
		manualControl.setMode(mode);
	}

	@Override
	public boolean isSwitchControlRequest() {
		return manualControl.isSwitchControlRequest();
	}
}
