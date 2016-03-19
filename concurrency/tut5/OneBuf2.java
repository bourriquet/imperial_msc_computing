/*
Tutorial 5, Q 5.2
*/

class OneBuf2 {

  Semaphore full;             // counts number of objects in the buffer
  Semaphore empty;            // counts number of empty slots in the buffer
  
  // constructor
  OneBuf2() {
    Object slot = null;
    full = new Semaphore(0);
    empty = new Semaphore(1);
  }
  
  // put an object into the bounded buffer
  public synchronized void put(Object o) {
    // only put object in if the buffer is empty
    empty.down();
    slot = o;
    full.up();
  }
  
  // get an object from the bounded buffer
  public synchronized void get() {
    // only get an object if there buffer is not empty
    while (slot == null) {
      try {
        wait();
      }
      catch (InterruptedException e) {
      }
    }
    full.down();
    Object o = slot;
    slot = null;
    empty.up();
    return o;
  }
}
