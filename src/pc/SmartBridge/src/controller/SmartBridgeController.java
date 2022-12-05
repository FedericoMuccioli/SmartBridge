package controller;

import view.SmartBridgeGui;
import java.util.Timer;
import java.util.TimerTask;

public class SmartBridgeController implements Controller {
	
	private final MessageController messageController;
	private final SmartBridgeGui gui;
	private Timer timer;
	private TimerTask task;

	public SmartBridgeController(MessageController messageController, SmartBridgeGui gui) throws Exception {
		this.messageController = messageController;
		this.gui = gui;
	}
	
	@Override
	public void start() throws InterruptedException {//togliere eccezione
		timer = new Timer();
		task = getTask();
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
				boolean manualControl = messageController.getManualControl();
				gui.setManualControl(manualControl);
				if (manualControl) {
					task = getTask();
					timer.schedule(task, 0, 1000);
				} else {
					task.cancel();
					timer.purge();
				}
			}
			final int position = gui.isButtonPressed();
			if(position >= 0) {
				messageController.buttonPressed(position);
			}
		}
	}
	
	private TimerTask getTask() {
		return  new TimerTask() {
			@Override
			public void run() {
        		messageController.setPosition(gui.getPosition());
			}
		};
	}

}
