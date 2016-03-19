/*
PROVIDED FILE
*/

/**
 * Title:        Concurrency Laboratory
 * Description:  An adaption of the roller coaster example
 * Copyright:    Copyright (c) 2002
 * Company:      Department of Computing, Imperial College
 * @author Jeff Magee
 * @version 1.0
 */

import display.*;

public class Passengers implements Runnable {

  protected Controller control;

  public Passengers(Controller c) {
     control =c;
  }

public void run() {
    try {
       while (true) {
          ThreadPanel.rotate(120);
          control.newPassenger();
          ThreadPanel.rotate(240);
       }
    } catch (InterruptedException e) {}
  }
}
