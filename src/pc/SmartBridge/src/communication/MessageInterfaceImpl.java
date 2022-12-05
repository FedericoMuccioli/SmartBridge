package communication;

public class MessageInterfaceImpl implements MessageInterface {
	
	private final CommChannel commChannel;
	private String smartLightState;
	private String waterLevelState;
	private int waterLevel;
	private boolean manualControl;
	private boolean isLightMsg;
	private boolean isWaterMsg;
	private boolean isWaterLevelMsg;
	private boolean isSwitchControl;

	public MessageInterfaceImpl(final CommChannel commChannel) {
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
	public void updateMsg() {
		while(commChannel.isMsgAvailable()) {
			try {
				String msg = commChannel.receiveMsg();
				updateValue(msg);
			} catch (InterruptedException e) {
				return;
			}
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
	public String getSmartLightingState() {
		isLightMsg = false;
		return smartLightState;
	}

	@Override
	public String getWaterLevelState() {
		isWaterMsg = false;
		return waterLevelState;
	}

	@Override
	public int getWaterLevel() {
		isWaterLevelMsg = false;
		return waterLevel;
	}
	
	@Override
	public boolean getManualControl() {
		isSwitchControl = false;
		return manualControl;
	}

	@Override
	public void sendSwitchControlRequest(final int position) {
		commChannel.sendMsg("-".concat(String.valueOf(position)));
	}
	
	@Override
	public void sendPosition(final int position) {
		commChannel.sendMsg(String.valueOf(position));
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
}
