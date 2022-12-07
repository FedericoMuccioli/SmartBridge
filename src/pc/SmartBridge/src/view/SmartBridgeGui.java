package view;

/**
 * Interface for smart bridge gui. Show water level, smart lighting and manual control state.
 * Show in real time water level and allows to manipulate position motor.
 * @author federico
 *
 */
public interface SmartBridgeGui {
	
	/**
	 * Update print smart lighting state.
	 * 
	 * @param smartLightingState state of smart lighting
	 */
	void printSmartLightingState(String smartLightingState);
	
	/**
	 * Update print water level state.
	 * 
	 * @param waterLevelState state of water level
	 */
	void printWaterLevelState(String waterLevelState);
	
	/**
	 * Update water level.
	 * 
	 * @param waterLevel value of water level
	 */
	void printWaterLevel(int waterLevel);
	
	/**
	 * Return position set.
	 * 
	 * @return the position
	 */
	int getPosition();

	/**
	 * Return if is request the switch of the control mode.
	 * 
	 * @return if switch control request
	 */
	boolean isSwitchControlRequest();

	/**
	 * Update manual control.
	 * 
	 * @param manualControl if manual control active or not.
	 */
	void printManualControl(String manualControl);

}
