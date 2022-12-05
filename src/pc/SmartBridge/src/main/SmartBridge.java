package main;
import communication.CommChannel;
import communication.MessageInterface;
import communication.MessageInterfaceImpl;
import communication.SerialCommChannel;
import controller.Controller;
import controller.SmartBridgeController;
import view.SmartBridgeGui;
import view.SmartBridgeGuiImpl;

public class SmartBridge {
	
	//private static final String PORT = "/dev/tty.usbmodem11401";
	private static final int BAUD = 9600;
	private static Controller controller;
	private static CommChannel commChannel;
	private static MessageInterface messageController;
	private static SmartBridgeGui gui;
	
	public static void main(String[] args) throws Exception {
		final String port = args[0];
		
		commChannel = new SerialCommChannel(port, BAUD);
		System.out.println("Waiting Arduino for rebooting...");
		Thread.sleep(5000);
		System.out.println("Ready.");
		
		messageController = new MessageInterfaceImpl(commChannel);
		gui = new SmartBridgeGuiImpl();
		controller = new SmartBridgeController(messageController, gui);
		controller.start();
		
	}

}

