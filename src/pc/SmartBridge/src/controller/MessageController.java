package controller;

public interface MessageController extends Controller {
	
	int getSmartLightingState() throws InterruptedException;
	
	int getWaterLevelState() throws InterruptedException;
	
	int getWaterLevel() throws InterruptedException;
	
}
