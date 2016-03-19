/*
Concurrency Coursework 2

Author: lc3311
Last updated: 28/02/16
*/

/**
 * Complete the implementation of this class in line with the FSP model
 */

public class PlatformAccess {

  public boolean carPlatform;

  public PlatformAccess() {
	  carPlatform = false;
  }
  
  public synchronized void arrive() throws InterruptedException {
  
	  // wait if there is already a car at the platform...
	  while (carPlatform) {
    	wait();
	  }
	  
	  // the car can arrive
	  carPlatform = true;
	  notifyAll();
  }

  public synchronized void depart() throws InterruptedException {
	  
	  // wait if there is no car at the platform
	  while (!carPlatform) {
		  wait();
	  }
	  
	  // the car can leave
	  carPlatform = false;
	  notifyAll();
  }

}
