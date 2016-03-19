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

public class CoasterCar implements Runnable{

  protected Controller control;
  protected PlatformAccess access;
  protected NumberCanvas incar;
  protected int MCar;

  public CoasterCar(int N, Controller c, PlatformAccess p, NumberCanvas nc) {
    control = c;
    access = p;
    incar = nc;
    MCar = N;
  }

  public void run() {
    try {
       while (true) {
          ThreadPanel.rotate(168);
          access.arrive();
          ThreadPanel.rotate(12);
          int n = control.getPassengers(MCar);
          incar.setValue(n);
          ThreadPanel.rotate(12);
          access.depart();
          ThreadPanel.rotate(168);
          incar.setValue(0);
       }
    } catch (InterruptedException e) {}
  }

}
