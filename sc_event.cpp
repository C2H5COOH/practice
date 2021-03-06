#include <systemc.h>

SC_MODULE (events) {
  sc_in<bool> clock;

  sc_event  e1;
  sc_event  e2;

  void do_test1() {
    while (true) {
      // Wait for posedge of clock
      //wait();
      cout << "@" << sc_time_stamp() <<" Starting test"<<endl;
      // Wait for posedge of clock
      wait();
      cout << "@" << sc_time_stamp() <<" Triggering e1"<<endl;
      // Trigger event e1
      e1.notify(10,SC_NS);
      // Wait for posedge of clock
      wait();
      // Wait for event e2
      wait(e2);
      cout << "@" << sc_time_stamp() <<" Got Trigger e2"<<endl;
      // Wait for posedge of clock
      wait();
      cout<<"Terminating Simulation"<<endl;
      sc_stop(); // sc_stop triggers end of simulation
    }
  }

  void do_test2() {
    while (true) {
      // Wait for event e2
      wait(e1);
      cout << "@" << sc_time_stamp() <<" Got Trigger e1"<<endl;
      // Wait for 3 posedge of clock
      wait(3);
      cout << "@" << sc_time_stamp() <<" Triggering e2"<<endl;
      // Trigger event e2
      e2.notify();
    }
  }

  SC_CTOR(events) {
    SC_CTHREAD(do_test1,clock.pos());
    SC_CTHREAD(do_test2,clock.pos());
  }
}; 

int sc_main (int argc, char* argv[]) {
  sc_clock Tclock ("my_clock",1,SC_NS,0.5);
  cout<<"motherfucker"<<endl;
  //sc_event  E1,E2;

  events  object("events");
    object.clock (Tclock);
    //object.e1(E1);
    //object.e2(E2);


  sc_start();  // Run the simulation till sc_stop is encountered
  return 0;// Terminate simulation
}
