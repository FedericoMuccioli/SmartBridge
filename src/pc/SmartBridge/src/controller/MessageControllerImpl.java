package controller;

import utility.CommChannel;

public class MessageControllerImpl implements MessageController {
	
	private final CommChannel commChannel;
	private int smartLightState;
	private int waterLevelState;
	private int waterLevel;
	private boolean isLightMsg;
	private boolean isWaterMsg;
	private boolean isWaterLevelMsg;

	public MessageControllerImpl(final CommChannel commChannel) {
		this.commChannel = commChannel;
		smartLightState = 0;
		waterLevelState = 0;
		waterLevel = 0;
		isLightMsg = false;
		isWaterMsg = false;
		isWaterLevelMsg = false;
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
			} else {
				System.out.println(msg);
			}
		} catch (Exception e) {
			return;
		}
	}

	@Override
	public void setPosition(final int position) {
		commChannel.sendMsg(String.valueOf(position));
	}

}
