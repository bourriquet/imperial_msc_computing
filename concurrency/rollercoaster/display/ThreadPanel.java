/*
PROVIDED FILE
*/

//@author: j.n.magee 11/11/96
package display;
import java.awt.*;
import java.awt.event.*;

/********************************************************/

public class ThreadPanel extends Panel {

    Button run;
    Button pause;
    Scrollbar bar_;
    DisplayThread thread_;
    GraphicCanvas canvas_;
    boolean hasSlider;

    public ThreadPanel(String title, Color c) {
        this(title,c,false);
    }

    public ThreadPanel(String title, Color c, boolean hasSlider) {
        super();
        this.hasSlider=hasSlider;
        // Set up Buttons
        this.setFont(new Font("Helvetica",Font.BOLD,14));
        Panel p = new Panel();
        run=new Button("Run");
        run.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
               thread_.activate();
            }
        });
        pause=new Button("Pause");
        pause.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
               thread_.passivate();
            }
        });
        p.add(run);
        p.add(pause);
        setLayout(new BorderLayout());
        add("South",p);
        canvas_ = new GraphicCanvas(title,c);
        add("North",canvas_);
        bar_ = new Scrollbar(Scrollbar.HORIZONTAL, 30, 10, 2, 58);
        bar_.addAdjustmentListener(new AdjustmentListener() {
           public void adjustmentValueChanged(AdjustmentEvent e) {
              thread_.setSplit(bar_.getValue());
           }
        });
        if (hasSlider) add("Center",bar_);
    }

    public static boolean rotate() throws InterruptedException {
        return DisplayThread.rotate();
    }

    public static void rotate(int degrees) throws InterruptedException {
        for(int i=0;i<degrees;i+=6)
            DisplayThread.rotate();
    }

    public static void setSegmentColor(Color c) {
        DisplayThread.setSegmentColor(c);
    }

    public void start(Runnable r) {
        thread_ = new DisplayThread(canvas_,r,100,hasSlider?bar_.getValue():0,true);
        thread_.start();
    }

    public Thread start(Runnable r, boolean suspended) {
        thread_ = new DisplayThread(canvas_,r,100,hasSlider?bar_.getValue():0,suspended);
        thread_.start();
        return thread_;
    }

    public void stop() {
        thread_.interrupt();
    }

 }

/********************************************************/

class DisplayThread extends Thread {

    GraphicCanvas display_;
    boolean suspended = true;
    int angle_=0;
    int segStart_=9999;
    int segEnd_=9999;
    int rate_;
    final static int step = 6;
    int barValue_;
    Color segColor_=Color.cyan;

    Runnable target_;

    DisplayThread(GraphicCanvas g, Runnable target, int rate, int split, boolean susp) {
        display_ = g;
        target_=target;
        rate_=rate;
        setSplit(split);
        suspended= susp;
        if (suspended)
            display_.setColor(Color.red);
        else
            display_.setColor(Color.green);
    }

    synchronized void mysuspend() throws InterruptedException{
        while (suspended) wait();
    }

    void passivate() {
        if (!suspended) {
            suspended = true;
            display_.setColor(Color.red);
           }
    }

    void activate() {
        if (suspended) {
            suspended = false;
            display_.setColor(Color.green);
            synchronized(this) {notify();}
        }
    }

    static boolean rotate() throws InterruptedException {
        DisplayThread d = (DisplayThread)Thread.currentThread();
        synchronized(d) {
            d.mysuspend();
            d.angle_=(d.angle_+step)%360;
            d.display_.setAngle(d.angle_);
            Thread.sleep(d.rate_);
            return (d.angle_>=d.segStart_ && d.angle_<=d.segEnd_);
        }
    }

    static void setSegmentColor(Color c) {
        DisplayThread d = (DisplayThread)Thread.currentThread();
        synchronized(d) {
            d.segColor_=c;
            d.display_.setSegment(d.segStart_,d.segEnd_,d.segColor_);
        }
    }


    synchronized void setSplit(int i) {
        barValue_ = i;
        segStart_=(60-i)*3;
        segEnd_ = segStart_+i*6;
        display_.setSegment(segStart_,segEnd_,segColor_);
    }

    public void run() {
        try {
          mysuspend();
          target_.run();
          display_.setColor(Color.white);
          display_.setAngle(0);
        } catch (InterruptedException e){}
     }
 }


/********************************************************/

class GraphicCanvas extends Canvas {
    int angle_ = 0;
    String title_;
    Color arcColor_ = Color.blue;
    int segStart_ = 9999;
    int segEnd_ = 9999;
    Color segColor_ = Color.yellow;

    Font f1 = new Font("Times",Font.ITALIC+Font.BOLD,24);

    final static int Cx = 30;
    final static int Cy = 45;

    GraphicCanvas(String title, Color c) {
        super();
        title_=title;
        setSize(150,150);
        arcColor_=c;
  	}

    public void setColor(Color c){
        setBackground(c);
        repaint();
    }

    public void setAngle(int a){
        angle_ = a;
        repaint();
    }

    public void setSegment(int start, int end, Color c) {
        segStart_ = start;
        segEnd_ = end;
        segColor_ = c;
    }

    public void paint(Graphics g){
        update(g);
    }

    Image offscreen;
    Dimension offscreensize;
    Graphics offgraphics;

    public synchronized void update(Graphics g){
        Dimension d = getSize();
	    if ((offscreen == null) || (d.width != offscreensize.width)
	                            || (d.height != offscreensize.height)) {
	        offscreen = createImage(d.width, d.height);
	        offscreensize = d;
	        offgraphics = offscreen.getGraphics();
	        offgraphics.setFont(getFont());
        /*
        Graphics2D g2d = (Graphics2D)offgraphics;
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                           RenderingHints.VALUE_ANTIALIAS_ON);
        g2d.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING,
                           RenderingHints.VALUE_TEXT_ANTIALIAS_OFF);
        g2d.setRenderingHint(RenderingHints.KEY_FRACTIONALMETRICS,
                           RenderingHints.VALUE_FRACTIONALMETRICS_OFF);
        */
	    }
	    offgraphics.setColor(getBackground());
	    offgraphics.fillRect(0, 0, d.width, d.height);

             // Display the title
         offgraphics.setColor(Color.black);
         offgraphics.setFont(f1);
         FontMetrics fm = offgraphics.getFontMetrics();
         int w = fm.stringWidth(title_);
         int h = fm.getHeight();
         int x = (getSize().width - w)/2;
         int y = h;
         offgraphics.drawString(title_, x, y);
         offgraphics.drawLine(x,y+3,x+w,y+3);
         // Display the arc
         if (angle_>0) {
             if (angle_<segStart_ || segStart_==segEnd_) {
                offgraphics.setColor(arcColor_);
                offgraphics.fillArc(Cx,Cy,90,90,0,angle_);
             } else if ( angle_>=segStart_ && angle_<segEnd_) {
                offgraphics.setColor(arcColor_);
                offgraphics.fillArc(Cx,Cy,90,90,0,segStart_);
                if (angle_-segStart_>0) {
                    offgraphics.setColor(segColor_);
                    offgraphics.fillArc(Cx,Cy,90,90,segStart_,angle_-segStart_);
                }
             } else  {
                offgraphics.setColor(arcColor_);
                offgraphics.fillArc(Cx,Cy,90,90,0,segStart_);
                offgraphics.setColor(segColor_);
                offgraphics.fillArc(Cx,Cy,90,90,segStart_,segEnd_-segStart_);
                if (angle_-segEnd_>0){
                    offgraphics.setColor(arcColor_);
                    offgraphics.fillArc(Cx,Cy,90,90,segEnd_,angle_-segEnd_);
                }
             }
         }
         g.drawImage(offscreen, 0, 0, null);
    }
}

/****************************************************************************/
