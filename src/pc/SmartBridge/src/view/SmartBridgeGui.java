package view;

public interface SmartBridgeGui {
	
	void printSmartLightingState(String smartLightingState);
	
	void printWaterLevelState(String waterLevelState);
	
	void printWaterLevel(int waterLevel);
	
	int getPosition();

	boolean isSwitchControlRequest();

	void printManualControl(boolean manualControl);

}
