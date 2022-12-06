package communication;


/**
 * Interface for encode messages between application and communication channel
 * @author federico
 */
public interface SmartBridgeMessageInterface {
	
	/**
	 * Update messages received. Call this function before get information.
	 */
	void updateMsg();
	
	/**
	 * Verify if a new light state message is available.
	 * 
	 * @return if new light state message available
	 */
	boolean isLightMsg();
	
	/**
	 * Verify if a new water state message is available.
	 * 
	 * @return if new water state message available
	 */
	boolean isWaterMsg();
	
	/**
	 * Verify if a new water level message is available.
	 * 
	 * @return if new water level message available
	 */
	boolean isWaterLevelMsg();
	
	/**
	 * Verify if a new manual control message is available.
	 * 
	 * @return if new manual control message available
	 */
	boolean isManualControlMsg();
	
	/**
	 * Get last smart lighting state message.
	 * 
	 * @return smart lighting state
	 */
	String getSmartLightingState();
	
	/**
	 * Get last water level state message.
	 * 
	 * @return water level state
	 */
	String getWaterLevelState();
	
	/**
	 * Get last water level message.
	 * 
	 * @return water level
	 */
	int getWaterLevel();
	
	/**
	 * Get last manual control message.
	 * 
	 * @return manual control mode
	 */
	boolean getManualControl();
	
	/**
	 * Manual control is on, send position of motor.
	 * 
	 * @param position from 0 to 180
	 */
	void sendPosition(int position);

	
	/**
	 * Send request for switch manual control.
	 * 
	 * @param position if manual control allow update with position specified
	 */
	void sendSwitchControlRequest(int position);
	
}
