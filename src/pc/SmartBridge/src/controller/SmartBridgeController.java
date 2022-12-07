package controller;

import view.SmartBridgeGui;

import java.util.Optional;
import java.util.Timer;
import java.util.TimerTask;

import communication.SmartBridgeMessageInterface;

public class SmartBridgeController {
	
	private final SmartBridgeMessageInterface messageController;
	private final SmartBridgeGui gui;
	private Timer timer;
	private Optional<TimerTask> task;

	/**
	 * Smart bridge controller. Check the arrived messages, update the gui and command the sending of messages.
	 * 
	 * @param messageInterface  the interface for the communication
	 * @param gui graphical user interface
	 */
	public SmartBridgeController(SmartBridgeMessageInterface messageInterface, SmartBridgeGui gui) {
		this.messageController = messageInterface;
		this.gui = gui;
	}
	
	/**
	 * Start the behavior of the controller. Update states and water level, check manual control and send motor position.
	 */
	public void start() {
		timer = new Timer();
		task = Optional.empty();
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
			if(messageController.isManualControlMsg()) {
				String manualControl = messageController.getManualControl();
				gui.printManualControl(manualControl);
				if (manualControl.compareTo("SOFTWARE") == 0) {
					task = getPositionTask();
					timer.schedule(task.get(), 0, 1000);
				} else if (task.isPresent()){
					task.get().cancel();
					task = Optional.empty();
					timer.purge();
				}
			}
		}
	}
	
	/**
	 * Return task for update motor position.
	 * @return Optional of TimerTask
	 */
	private Optional<TimerTask> getPositionTask() {
		return Optional.of(new TimerTask() {
			@Override
			public void run() {
        		messageController.sendPosition(gui.getPosition());
			}
		});
	}
	
}
