package view.utility;

import java.awt.GridBagConstraints;

public class MyGridBagConstraints extends GridBagConstraints {

	public MyGridBagConstraints(final int x, final int y, final int width, final int height) {
		super();
		fill = GridBagConstraints.BOTH;
		gridx = x;
		gridy = y;
		gridwidth = width;
        gridheight = height;
		weightx=1.0;
		weighty=1.0;
	}
	
}
