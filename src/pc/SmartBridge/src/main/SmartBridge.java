package main;
import communication.CommChannel;
import communication.SmartBridgeMessageInterface;
import communication.SmartBridgeMessageInterfaceImpl;
import communication.SerialCommChannel;
import controller.SmartBridgeController;
import view.SmartBridgeGui;
import view.SmartBridgeGuiImpl;

public class SmartBridge {
	
	/**
	 * baud rate of the communication
	 */
	private static final int BAUD = 9600;
	//private static final String PORT = "/dev/tty.usbmodem11401";
	private static SmartBridgeController controller;
	private static CommChannel commChannel;
	private static SmartBridgeMessageInterface messageController;
	private static SmartBridgeGui gui;
	
	/**
	 * Launch program.
	 * 
	 * @param args one parameter, name of the port for the serial communication 
	 * @throws Exception if port incorrect
	 */
	public static void main(String[] args) throws Exception {
		final String port = args[0];
		
		commChannel = new SerialCommChannel(port, BAUD);
		System.out.println("Waiting Arduino for rebooting...");
		Thread.sleep(5000);
		System.out.println("Ready.");
		
		messageController = new SmartBridgeMessageInterfaceImpl(commChannel);
		gui = new SmartBridgeGuiImpl();
		controller = new SmartBridgeController(messageController, gui);
		controller.start();	
	}

}

