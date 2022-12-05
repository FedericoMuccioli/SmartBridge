package view.panel;

import java.awt.BorderLayout;
import javax.swing.JPanel;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.time.Millisecond;
import org.jfree.data.time.TimeSeries;
import org.jfree.data.time.TimeSeriesCollection;
import org.jfree.data.xy.XYDataset;


public class WaterLevelPanel extends JPanel {
	
	private static final double MIN_WATER_LEVEL = 0;
	private static final double MAX_WATER_LEVEL = 100; //100cm
	private static final double TIME_LAPSE = 60000.0; //60s
	

    /** The time series data. */
    private TimeSeries series;
   

    public WaterLevelPanel() {
    	this.setLayout(new BorderLayout());
        this.series = new TimeSeries("Random Data");
        final TimeSeriesCollection dataset = new TimeSeriesCollection(this.series);
        final JFreeChart chart = createChart(dataset);
        final ChartPanel chartPanel = new ChartPanel(chart);
        this.add(chartPanel);
    }

    /**
     * Creates a sample chart.
     * 
     * @param dataset  the dataset.
     * 
     * @return A sample chart.
     */
    private JFreeChart createChart(final XYDataset dataset) {
        final JFreeChart result = ChartFactory.createTimeSeriesChart(
            "Dynamic Data Demo", 
            "Time", 
            "Value",
            dataset, 
            true, 
            true, 
            false
        );
        final XYPlot plot = result.getXYPlot();
        ValueAxis axis = plot.getDomainAxis();
        axis.setAutoRange(true);
        axis.setFixedAutoRange(TIME_LAPSE);
        axis = plot.getRangeAxis();
        axis.setRange(MIN_WATER_LEVEL, MAX_WATER_LEVEL);
        return result;
    }
    
    public void print(final int waterLevel) {
    	series.add(new Millisecond(), waterLevel);
    }
}
