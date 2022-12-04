package controller;

import utility.CommChannel;

public class MessageControllerImpl implements MessageController {
	
	private final CommChannel commChannel;
	private int smartLightState;
	private int waterLevelState;
	private int waterLevel;
	private boolean manualControl;
	private boolean isLightMsg;
	private boolean isWaterMsg;
	private boolean isWaterLevelMsg;
	private boolean isSwitchControl;

	public MessageControllerImpl(final CommChannel commChannel) {
		this.commChannel = commChannel;
		smartLightState = 0;
		waterLevelState = 0;
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
	public int getSmartLightingState() throws InterruptedException {
		isLightMsg = false;
		return smartLightState;
	}

	@Override
	public int getWaterLevelState() throws InterruptedException {
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
	
	@Override
	public void close() {
		// TODO Auto-generated method stub
		
	}
	
	private void updateValue(final String msg) {
		try {
			char typeValue = msg.charAt(0);
			final String value = msg.substring(1);
			if (typeValue == 'l') {
				smartLightState=Integer.valueOf(value);
				isLightMsg = true;
			} else if (typeValue == 'w') {
				waterLevelState=Integer.valueOf(value);
				isWaterMsg = true;
			} else if (typeValue == 'v'){
				waterLevel=Integer.valueOf(value);
				isWaterLevelMsg = true;
			} else if (typeValue == 'c'){
				manualControl = Boolean.valueOf(value);
				isSwitchControl = true;
			} else {
				System.out.println(msg);
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
