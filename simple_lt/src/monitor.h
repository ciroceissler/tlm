//  Project:   OTN 100G
//  Author:    Ciro Ceissler
//  Email:     ciroc at cpqd.com.br
//  Copyright: 2015 @ CPqD

#ifndef MONITOR_H_
#define MONITOR_H_

#include <systemc.h>
#include <tlm.h>
#include "tlm_utils/simple_target_socket.h"
#include <package.h>

class Monitor : public sc_core::sc_module {
 private:
  virtual void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& delay);

 public:
  tlm_utils::simple_target_socket<Monitor> target_socket;

  // SC_HAS_PROCESS(Monitor);

  //  Constructor
  explicit Monitor(sc_core::sc_module_name name);
};


#endif  //  MONITOR_H_

