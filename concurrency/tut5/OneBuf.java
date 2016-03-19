class OneBuf {

  Object slot = null;
  
  public synchronized void put(Object o) {
    while (slot != null) {
      try {
        wait();
      }
      catch (InterruptedException e) {
      }
      slot = o;
      notify();
    }
  }
  
  public synchronized void get() {
    while (slot == null) {
      try {
        wait();
      }
      catch (InterruptedException e) {
      }
      Object o = slot;
      slot = null;
      notify();
      return o;
    }
  }
}
