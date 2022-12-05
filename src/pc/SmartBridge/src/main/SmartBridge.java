package main;
import controller.Controller;
import controller.MessageController;
import controller.MessageControllerImpl;
import controller.SmartBridgeController;
import utility.CommChannel;
import utility.SerialCommChannel;
import view.SmartBridgeGui;
import view.SmartBridgeGuiImpl;

public class SmartBridge {
	
	//private static final int BAUD = 9600;
	//private static final String PORT = "/dev/tty.usbmodem11401";
	private static Controller controller;
	private static CommChannel commChannel;
	private static MessageController messageController;
	private static SmartBridgeGui gui;
	
	public static void main(String[] args) throws Exception {
		final String port = args[0];
		final int baud = Integer.parseInt(args[1]);
		
		commChannel = new SerialCommChannel(port, baud);
		System.out.println("Waiting Arduino for rebooting...");
		Thread.sleep(5000);
		System.out.println("Ready.");
		
		messageController = new MessageControllerImpl(commChannel);
		gui = new SmartBridgeGuiImpl();
		controller = new SmartBridgeController(messageController, gui);
		controller.start();
		
	}

}

