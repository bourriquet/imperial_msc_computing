/*
PROVIDED FILE
*/

/********************************************************/
// j.n.magee 16.4.98
package display;

import java.awt.*;
import java.applet.*;

public class NumberCanvas extends Canvas {
    int value_ = 0;
    String title_;

    Font f1 = new Font("Helvetica",Font.BOLD,36);
    Font f2 = new Font("Times",Font.ITALIC+Font.BOLD,24);

    public NumberCanvas(String title) {
        this(title,Color.cyan);
    }

    public NumberCanvas(String title,Color c) {
        super();
        title_=title;
        setBackground(c);
        setSize(150,100);
	}

    public void setColor(Color c){
        setBackground(c);
        repaint();
    }

    public void setValue(int newval){
        value_ = newval;
        repaint();
    }

    public void paint(Graphics g){

            g.setColor(Color.black);

         // Display the title
            g.setFont(f2);
            FontMetrics fm = g.getFontMetrics();
            int w = fm.stringWidth(title_);
            int h = fm.getHeight();
            int x = (getSize().width - w)/2;
            int y = h;
            g.drawString(title_, x, y);
            g.drawLine(x,y+3,x+w,y+3);


         // Display the value
            g.setFont(f1);
            fm = g.getFontMetrics();
            String s1 = String.valueOf(value_);
            w = fm.stringWidth(s1);
            h = fm.getHeight();
            x = (getSize().width - w)/2;
            y = (getSize().height+ h)/2;
            g.drawString(s1, x, y);
         }
}
