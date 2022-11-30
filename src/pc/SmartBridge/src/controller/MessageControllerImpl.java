package controller;

import utility.CommChannel;

public class MessageControllerImpl implements MessageController {
	
	private final CommChannel commChannel;
	private int smartLightState;
	private int waterLevelState;
	private int waterLevel;

	public MessageControllerImpl(final CommChannel commChannel) {
		this.commChannel = commChannel;
		smartLightState = 0;
		waterLevelState = 0;
		waterLevel = 0;
	}

	@Override
	public int getSmartLightingState() throws InterruptedException {
		updateValues();
		return smartLightState;
	}

	@Override
	public int getWaterLevelState() throws InterruptedException {
		updateValues();
		return waterLevelState;
	}

	@Override
	public int getWaterLevel() throws InterruptedException {
		updateValues();
		return waterLevel;
	}
	
	@Override
	public void close() {
		// TODO Auto-generated method stub
		
	}
	
	private void updateValues() throws InterruptedException {
		while(commChannel.isMsgAvailable()) {
			final String msg = commChannel.receiveMsg();
			updateValue(msg);
		}
	}
	
	private void updateValue(final String msg) {
		if( msg.length() == 0) {
			return;
		}
		char typeValue = msg.charAt(0);
		final String value = msg.substring(1);
		if (typeValue == 'l') {
			smartLightState=Integer.valueOf(value);
		} else if (typeValue == 'w') {
			waterLevelState=Integer.valueOf(value);
		} else {
			waterLevel=Integer.valueOf(value);
		}
	}

}
