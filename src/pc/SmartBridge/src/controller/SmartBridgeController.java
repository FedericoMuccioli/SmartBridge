package controller;

import utility.SerialCommChannel;
import view.SmartBridgeGui;
import view.SmartBridgeGuiImpl;

public class SmartBridgeController implements Controller {
	
	private final MessageController messageController;
	private final SmartBridgeGui gui;
	private boolean manualControl;

	public SmartBridgeController(MessageController messageController, SmartBridgeGui gui) throws Exception {
		this.messageController = messageController;
		this.gui = gui;
		manualControl = false;
	}
	
	@Override
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
			if(messageController.isSwitchControl()) {
				manualControl = messageController.getManualControl();
				gui.setManualControl(manualControl);
			}
			final int position = gui.isButtonPressed();
			if(position >= 0) {
				messageController.buttonPressed(position);
			}
		}
	}

}
