package controller;

import utility.SerialCommChannel;
import view.SmartBridgeGui;
import view.SmartBridgeGuiImpl;

public class SmartBridgeController implements Controller {
	
	private final MessageController messageController;
	private final SmartBridgeGuiImpl gui;

	public SmartBridgeController(final String port, final int baud) throws Exception {
		messageController = new MessageControllerImpl(new SerialCommChannel(port, baud));
		System.out.println("Waiting Arduino for rebooting...");
		Thread.sleep(5000);
		System.out.println("Ready.");
		gui = new SmartBridgeGuiImpl();
	}
	
	public void start() throws InterruptedException {//togliere eccezione
		
		while(true) {
			messageController.updateMsg();
			if(messageController.isWaterLevelMsg()) {
				gui.setWaterLevel(messageController.getWaterLevel());
			}
			if(messageController.isWaterMsg()) {
				gui.setWaterLevelState(messageController.getWaterLevelState());
			}
			if(messageController.isLightMsg()) {
				gui.setSmartLightingState(messageController.getSmartLightingState());
			}
			
		}
	}
	
	
	
	
	@Override
	public void close() {
		// TODO Auto-generated method stub
		
	}

}
