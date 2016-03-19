/*
Concurrency Coursework 2

Author: lc3311
Last updated: 28/02/16
*/

/**
 * Complete the implementation of this class in line with the FSP model
 */

import display.*;

public class Controller {

  public static int Max = 9;
  protected NumberCanvas passengers;

  // counts the number of passengers on the platform
  public int count;
  
  // button for allowing cars to leave if they aren't full
  public boolean button;

  public Controller(NumberCanvas nc) {
	  passengers = nc;
	  count = 0;
	  button = false;
  }

  public synchronized void newPassenger() throws InterruptedException {
	  
	  // wait if there are too many people on the platform...
	  while (count >= Max) {
		  wait();
	  }
	  
	  // new passenger allowed on the platform...
	  count++;
	  passengers.setValue(count);
	  notifyAll();
  }

  public synchronized int getPassengers(int mcar) throws InterruptedException {
	  
	  // number of people inside the car
	  int inCar = 0;
	  
	  // waiting conditions
	  while (mcar <= 0 || count <= 0 || (count < mcar && !button)) {
		  wait();
	  }
	  
	  // if the number of passengers on the platform > capacity of the car, fill the car
	  if (count >= mcar) {
		  inCar = mcar;
		  count -= mcar;
	  }
	  // else if the button is pressed, fill the car
	  else {
		  if (button) {
			  inCar = count;
			  count = 0;
			  button = false;
		  }
	  }
	  
	  // update the number of passengers on the platform
	  passengers.setValue(count);
	  notifyAll();
	  
	  return inCar;
  }

  public synchronized void goNow() {
	  
	  // if there are people on the platform, the car can leave - press the button
	  if (count > 0) {
		  button = true;
		  notifyAll();
	  }
  }

}
