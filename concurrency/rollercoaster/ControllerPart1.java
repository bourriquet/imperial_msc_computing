/*
Concurrency Coursework 2

Author: lc3311
Last updated: 28/02/16
*/

/**
 * Complete the implementation of this class in line with the FSP model
 */

import display.*;

public class ControllerPartI {

  public static void main(String[] args) {
	  System.out.println("run");

  }
	
  public static int Max = 9;
  protected NumberCanvas passengers;

  // counts the number of passengers on the platform
  private int count;
  
  
  public ControllerPartI(NumberCanvas nc) {
	  passengers = nc;
	  count = 0;
  }

  public synchronized void newPassenger() throws InterruptedException {
	  
	  // wait if there are too many people on the platform...
	  while (count >= Max) {
		  wait();
	  }
	  
	  // new passenger allowed on the platform...
	  passengers.setValue(++count);
	  notifyAll();
  }

  public synchronized int getPassengers(int mcar) throws InterruptedException {
	  
	  // waiting conditions
	  while (mcar <= 0 || count <= 0 || count < mcar) {
		  wait();
	  }
	  
	  // put the passengers in the car
	  count -= mcar;
	  passengers.setValue(count);
	  notifyAll();
	  
	  return mcar;
  }

  public synchronized void goNow() {
    // complete implementation for part II
  }

}
