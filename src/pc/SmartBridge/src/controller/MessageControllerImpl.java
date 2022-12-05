package controller;

import utility.CommChannel;

public class MessageControllerImpl implements MessageController {
	
	private final CommChannel commChannel;
	private String smartLightState;
	private String waterLevelState;
	private int waterLevel;
	private boolean manualControl;
	private boolean isLightMsg;
	private boolean isWaterMsg;
	private boolean isWaterLevelMsg;
	private boolean isSwitchControl;

	public MessageControllerImpl(final CommChannel commChannel) {
		this.commChannel = commChannel;
		smartLightState = "";
		waterLevelState = "";
		waterLevel = 0;
		isLightMsg = false;
		isWaterMsg = false;
		isWaterLevelMsg = false;
		isSwitchControl = false;
	}
	
	@Override
	public void updateMsg() throws InterruptedException {
		while(commChannel.isMsgAvailable()) {
			final String msg = commChannel.receiveMsg();
			updateValue(msg);
		}
	}
	
	@Override
	public boolean isLightMsg() {
		return isLightMsg;
	}

	@Override
	public boolean isWaterMsg() {
		return isWaterMsg;
	}

	@Override
	public boolean isWaterLevelMsg() {
		return isWaterLevelMsg;
	}
	
	@Override
	public boolean isSwitchControl() {
		return isSwitchControl;
	}

	@Override
	public String getSmartLightingState() throws InterruptedException {
		isLightMsg = false;
		return smartLightState;
	}

	@Override
	public String getWaterLevelState() throws InterruptedException {
		isWaterMsg = false;
		return waterLevelState;
	}

	@Override
	public int getWaterLevel() throws InterruptedException {
		isWaterLevelMsg = false;
		return waterLevel;
	}
	
	@Override
	public boolean getManualControl() throws InterruptedException {
		isSwitchControl = false;
		return manualControl;
	}
	
	private void updateValue(final String msg) {
		try {
			char typeValue = msg.charAt(0);
			final String value = msg.substring(1);
			if (typeValue == 'l') {
				smartLightState = value;
				isLightMsg = true;
			} else if (typeValue == 'w') {
				waterLevelState = value;
				isWaterMsg = true;
			} else if (typeValue == 'v'){
				waterLevel=Integer.valueOf(value);
				isWaterLevelMsg = true;
			} else if (typeValue == 'c'){
				manualControl = Boolean.valueOf(value);
				isSwitchControl = true;
			}
		} catch (Exception e) {
			return;
		}
	}

	@Override
	public void buttonPressed(final int position) {
		commChannel.sendMsg("-".concat(String.valueOf(position)));
	}
	
	@Override
	public void setPosition(final int position) {
		commChannel.sendMsg(String.valueOf(position));
	}

}
