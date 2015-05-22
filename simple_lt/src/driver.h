//  Author:    Ciro Ceissler
//  Email:     ciro at ceissler.com.br

#ifndef SRC_DRIVER_H_
#define SRC_DRIVER_H_

#include <systemc.h>
#include <tlm.h>
#include "tlm_utils/simple_initiator_socket.h"

class Driver : public sc_core::sc_module {
 public:
  tlm_utils::simple_initiator_socket<Driver> initiator_socket;

  SC_HAS_PROCESS(Driver);

  explicit Driver(sc_core::sc_module_name name);

  void request_thread();
};

#endif  //  SRC_DRIVER_H_

