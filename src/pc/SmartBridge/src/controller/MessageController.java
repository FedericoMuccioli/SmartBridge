package controller;

public interface MessageController extends Controller {
	
	void updateMsg() throws InterruptedException;
	
	boolean isLightMsg();
	
	boolean isWaterMsg();
	
	boolean isWaterLevelMsg();
	
	int getSmartLightingState() throws InterruptedException;
	
	int getWaterLevelState() throws InterruptedException;
	
	int getWaterLevel() throws InterruptedException;
	
}
