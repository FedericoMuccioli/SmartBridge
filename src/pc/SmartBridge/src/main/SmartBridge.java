package main;
import controller.SmartBridgeController;
import utility.SerialCommChannel;

public class SmartBridge {
	
	//private static final int BAUD = 9600;
	//private static final String PORT = "/dev/tty.usbmodem11401";
	public static void main(String[] args) throws Exception {
		
		//fare check numero argomenti
		final String port = args[0];
		final int baud = Integer.parseInt(args[1]);
		//mettere qui il SerialCommChannel e passarlo al controller
		SmartBridgeController smartBridgeController = new SmartBridgeController(port, baud);
		smartBridgeController.start();
		
		/*
		SerialCommChannel channel = new SerialCommChannel(PORT,BOUND);
		//attesa necessaria per fare in modo che Arduino completi il reboot 
		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(10000);
		System.out.println("Ready.");		
		
		new java.util.Timer().schedule( 
		        new java.util.TimerTask() {
		            @Override
		            public void run() {
		            	channel.sendMsg("180");
		            }
		        }, 0,
		        1000
		);
		
		while (true){
			
			String msg = channel.receiveMsg();
			System.out.println(msg);		
			//Thread.sleep(500);
			
			
			
		}
		*/
	}

}

