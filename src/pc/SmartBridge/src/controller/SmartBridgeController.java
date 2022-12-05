package controller;

import view.SmartBridgeGui;
import java.util.Timer;
import java.util.TimerTask;

import communication.MessageInterface;

public class SmartBridgeController implements Controller {
	
	private final MessageInterface messageController;
	private final SmartBridgeGui gui;
	private Timer timer;
	private TimerTask task;

	public SmartBridgeController(MessageInterface messageController, SmartBridgeGui gui) throws Exception {
		this.messageController = messageController;
		this.gui = gui;
	}
	
	@Override
	public void start() {
		timer = new Timer();
		task = getTask();
		while(true) {
			messageController.updateMsg();
			if(messageController.isWaterLevelMsg()) {
				gui.printWaterLevel(messageController.getWaterLevel());
			}
			if(messageController.isWaterMsg()) {
				gui.printWaterLevelState(messageController.getWaterLevelState());
			}
			if(messageController.isLightMsg()) {
				gui.printSmartLightingState(messageController.getSmartLightingState());
			}
			if(gui.isSwitchControlRequest()) {
				messageController.sendSwitchControlRequest(gui.getPosition());
			}
			if(messageController.isSwitchControl()) {
				boolean manualControl = messageController.getManualControl();
				gui.printManualControl(manualControl);
				if (manualControl) {
					task = getTask();
					timer.schedule(task, 0, 1000);
				} else {
					task.cancel();
					timer.purge();
				}
			}
		}
	}
	
	private TimerTask getTask() {
		return  new TimerTask() {
			@Override
			public void run() {
        		messageController.sendPosition(gui.getPosition());
			}
		};
	}

}
