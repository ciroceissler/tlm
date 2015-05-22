//  Author:    Ciro Ceissler
//  Email:     ciro at ceissler.com.br

#ifndef SRC_MONITOR_H_
#define SRC_MONITOR_H_

#include <systemc.h>
#include <tlm.h>
#include "tlm_utils/simple_target_socket.h"

class Monitor : public sc_core::sc_module {
 private:
  virtual void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& delay);

 public:
  tlm_utils::simple_target_socket<Monitor> target_socket;

  explicit Monitor(sc_core::sc_module_name name);
};


#endif  //  SRC_MONITOR_H_

