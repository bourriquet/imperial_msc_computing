/*
PROVIDED FILE
*/

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import display.*;

public class RollerCoasterFrame extends JFrame {
  JPanel contentPane;
  BorderLayout bd = new BorderLayout();

  /**Construct the frame*/
  public RollerCoasterFrame() {
    enableEvents(AWTEvent.WINDOW_EVENT_MASK);
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }
  /**Component initialization*/
  private void jbInit() throws Exception  {
    contentPane = (JPanel) this.getContentPane();
    contentPane.setLayout(bd);
    ThreadPanel tp1 = new ThreadPanel("Passengers",Color.blue);
    ThreadPanel tp2 = new ThreadPanel("Car(2)",Color.blue);
    ThreadPanel tp3 = new ThreadPanel("Car(3)",Color.blue);
    NumberCanvas nc1 = new NumberCanvas("Platform");
    NumberCanvas nc2 = new NumberCanvas("In Car(2)");
    NumberCanvas nc3 = new NumberCanvas("In Car(3)");
    Panel p1 = new Panel();
    p1.setLayout(new BorderLayout());
    Panel p2 = new Panel();
    p2.setLayout(new BorderLayout());
    Panel p3 = new Panel();
    p3.setLayout(new BorderLayout());
    p1.add(nc1,BorderLayout.CENTER);
    p1.add(tp1,BorderLayout.SOUTH);
    p2.add(nc2,BorderLayout.CENTER);
    p2.add(tp2,BorderLayout.SOUTH);
    p3.add(nc3,BorderLayout.CENTER);
    p3.add(tp3,BorderLayout.SOUTH);
    Panel grid = new Panel();
    grid.setLayout(new GridLayout(1,3));
    grid.add(p1);
    grid.add(p2);
    grid.add(p3);
    contentPane.add(grid,BorderLayout.CENTER);
    //construct threads, monitor & go button
    final Controller c = new Controller(nc1);
    final PlatformAccess pa = new PlatformAccess();
    Button go = new Button("Go Now");
    go.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
               c.goNow();
            }
        });
    contentPane.add(go,BorderLayout.SOUTH);
    tp1.start(new Passengers(c));
    tp2.start(new CoasterCar(2,c,pa,nc2));
    tp3.start(new CoasterCar(3,c,pa,nc3));
    this.setSize(new Dimension(470, 350));
    this.setTitle("Roller Coaster Laboratory Exercise");
  }
  /**Overridden so we can exit when window is closed*/
  protected void processWindowEvent(WindowEvent e) {
    super.processWindowEvent(e);
    if (e.getID() == WindowEvent.WINDOW_CLOSING) {
      System.exit(0);
    }
  }
}
