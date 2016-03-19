/*
Tutorial 5, Q 5.1
*/

class OneBuf {

  Object slot = null;
  
  // put an object into the bounded buffer
  public synchronized void put(Object o) {
    // only put object in if the buffer is empty
    while (slot != null) {
      try {
        wait();
      }
      catch (InterruptedException e) {
      }
    }
    slot = o;
    notify();
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
    Object o = slot;
    slot = null;
    notify();
    return o;
  }
}
