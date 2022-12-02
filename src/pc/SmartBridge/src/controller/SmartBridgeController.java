package controller;

import utility.SerialCommChannel;

public class SmartBridgeController implements Controller {
	
	private final MessageController messageController;

	public SmartBridgeController(final String port, final int baud) throws Exception {
		messageController = new MessageControllerImpl(new SerialCommChannel(port, baud));
		System.out.println("Waiting Arduino for rebooting...");
		Thread.sleep(5000);
		System.out.println("Ready.");
	}
	
	public void start() throws InterruptedException {//togliere eccezione
		while(true) {
			//System.out.println("light: " + messageController.getSmartLightingState());
			//System.out.println("water: " + messageController.getWaterLevelState());
			int waterL = messageController.getWaterLevel();
			if(waterL >= 0) {
				System.out.println("waterL: " + waterL);
			}
		}
	}
	
	
	
	
	@Override
	public void close() {
		// TODO Auto-generated method stub
		
	}

}
