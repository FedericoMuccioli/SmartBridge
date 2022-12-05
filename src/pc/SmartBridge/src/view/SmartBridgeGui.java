package view;

public interface SmartBridgeGui {
	
	void setSmartLightingState(String smartLightingState);
	
	void setWaterLevelState(String waterLevelState);
	
	void setWaterLevel(int waterLevel);
	
	int getPosition();

	int isButtonPressed();

	void setManualControl(boolean manualControl);

}
