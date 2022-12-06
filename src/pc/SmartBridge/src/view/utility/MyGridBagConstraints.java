package view.utility;

import java.awt.GridBagConstraints;

/**
 * My personal constructor of the java.awt.GridBagConstraints
 * @author federico
 */
public class MyGridBagConstraints extends GridBagConstraints {

	/**
	 * Create a default gridBagConstraints with the parameters specified.
	 * @param x
	 * @param y
	 * @param width
	 * @param height
	 */
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
