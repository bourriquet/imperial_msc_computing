/*
Tutorial 5, Q 5.4
*/

class Barrier {
  
  int n;
  int blocked = 0;
  
  // constructor
  Barrier(int n) {
    this.n = n;
  }
  
  public synchronized void sync() throws InterruptedException{
    
    ++blocked;
    
    // can only proceed if n processes have called sync()
    if (blocked < n) {
      wait();
    }
    else {
      notifyAll();
      blocked = 0;
    }
  }
}
