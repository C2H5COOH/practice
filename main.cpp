#include "systemc.h"
#include "stim.h"
#include "exor2.h"

int sc_main(int argc, char* argv[])
{
  sc_signal<bool> ASig, BSig, FSig;
  sc_clock TestClk("TestClock", 10, SC_NS,0.5);

  stim Stim1("Stimulus");
  Stim1.A(ASig);
  Stim1.B(BSig);
  Stim1.Clk(TestClk);

  exor2 DUT("exor2");
  DUT.A(ASig);
  DUT.B(BSig);
  DUT.F(FSig);

 sc_trace_file* tf = sc_create_vcd_trace_file("wave");
 sc_trace(tf,ASig,"Asig");
 sc_trace(tf,BSig,"Bsig");
 sc_trace(tf,FSig,"Fsig");
 sc_trace(tf,TestClk,"TestClk");

 sc_start();  // run forever
 sc_close_vcd_trace_file(tf);
  return 0;

}