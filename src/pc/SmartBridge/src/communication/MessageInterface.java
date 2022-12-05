package communication;

public interface MessageInterface {
	
	void updateMsg();
	
	boolean isLightMsg();
	
	boolean isWaterMsg();
	
	boolean isWaterLevelMsg();
	
	boolean isSwitchControl();
	
	String getSmartLightingState();
	
	String getWaterLevelState();
	
	int getWaterLevel();
	
	boolean getManualControl();
	
	void sendPosition(int position);

	void sendSwitchControlRequest(int position);
	
}
