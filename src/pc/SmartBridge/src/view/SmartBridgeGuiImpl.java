package view;

import java.awt.BorderLayout;
import java.awt.Dimension;

import javax.swing.JFrame;
import javax.swing.JPanel;

import view.panel.MotorPositionPanel;
import view.panel.SmartLightingStatePanel;
import view.panel.WaterLevelPanel;

public class SmartBridgeGuiImpl implements SmartBridgeGui {
	
	private final JFrame frame;
	private final WaterLevelPanel waterLevel;
	private final SmartLightingStatePanel smartLightingState;
	private final MotorPositionPanel motorPosition;
	
	
	public SmartBridgeGuiImpl() {
		frame = new JFrame();
		JPanel panel = new JPanel(new BorderLayout());
		smartLightingState = new SmartLightingStatePanel();
		waterLevel = new WaterLevelPanel();
		motorPosition = new MotorPositionPanel();
		panel.add(motorPosition);
		frame.add(panel);
		
 		
		
		
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		//frame.setExtendedState(JFrame.MAXIMIZED_BOTH);
		frame.pack();
		frame.setVisible(true);
	}

	@Override
	public void setSmartLightingState(int smartLightingState) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void setWaterLevelState(int waterLevelState) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void setWaterLevel(int waterLevel) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public int getWaterLevel() {
		// TODO Auto-generated method stub
		return 0;
	}

}
