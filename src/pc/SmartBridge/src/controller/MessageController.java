package controller;

public interface MessageController {
	
	void updateMsg() throws InterruptedException;
	
	boolean isLightMsg();
	
	boolean isWaterMsg();
	
	boolean isWaterLevelMsg();
	
	String getSmartLightingState() throws InterruptedException;
	
	String getWaterLevelState() throws InterruptedException;
	
	int getWaterLevel() throws InterruptedException;
	
	void setPosition(int position);

	void buttonPressed(int position);

	boolean isSwitchControl();

	boolean getManualControl() throws InterruptedException;
	
}
