package controller;

import utility.SerialCommChannel;
import view.SmartBridgeGui;
import view.SmartBridgeGuiImpl;

public class SmartBridgeController implements Controller {
	
	private final MessageController messageController;
	private final SmartBridgeGuiImpl gui;
	private boolean checkManualControl;
	private boolean manualControl;

	public SmartBridgeController(final String port, final int baud) throws Exception {
		messageController = new MessageControllerImpl(new SerialCommChannel(port, baud));
		System.out.println("Waiting Arduino for rebooting...");
		Thread.sleep(5000);
		System.out.println("Ready.");
		gui = new SmartBridgeGuiImpl(this);
		checkManualControl = false;
		manualControl = false;
	}
	
	public void start() throws InterruptedException {//togliere eccezione
		new java.util.Timer().schedule( 
		        new java.util.TimerTask() {
		            @Override
		            public void run() {
		            	if(manualControl) {
		            		messageController.setPosition(gui.getPosition());
		            	}
		            }
		        }, 0,
		        1000
		);
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
			if(messageController.switchCheckControl()) {
				checkManualControl = !checkManualControl;
				if(!checkManualControl) {
					gui.setManualControl(false);
					manualControl = false;
				}
			}
			
		}
	}
	
	public void switchManualControl() {
		if(checkManualControl) {
			manualControl = !manualControl;
			if(manualControl) {
				gui.setManualControl(true);
			} else {
				gui.setManualControl(false);
			}
		}
	}
	
	
	@Override
	public void close() {
		// TODO Auto-generated method stub
		
	}

}
