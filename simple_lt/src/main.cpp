//  Author:    Ciro Ceissler
//  Email:     ciro at ceissler.com.br

#define SC_INCLUDE_DYNAMIC_PROCESS

#include <stdio.h>
#include <systemc.h>
#include <dut.h>
#include <driver.h>
#include <monitor.h>

int sc_main(int argc, char *argv[]) {

  std::cout << "\n == Simple example using Loosely-Timed ==\n" << std::endl;

  DUT     *dut     = new DUT("dut");
  Driver  *driver  = new Driver("driver");
  Monitor *monitor = new Monitor("monitor");

  driver->initiator_socket.bind(dut->target_socket);
  dut->initiator_socket.bind(monitor->target_socket);

  sc_start();

  return 0;
}

