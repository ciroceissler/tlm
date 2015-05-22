//  Author:    Ciro Ceissler
//  Email:     ciro at ceissler.com.br

#ifndef SRC_DUT_H_
#define SRC_DUT_H_

#include <systemc.h>
#include <tlm.h>
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/simple_initiator_socket.h"

class DUT : public sc_core::sc_module {
 private:
  virtual void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& delay);

 public:
  tlm_utils::simple_initiator_socket<DUT> initiator_socket;
  tlm_utils::simple_target_socket<DUT> target_socket;

  SC_HAS_PROCESS(DUT);

  explicit DUT(sc_core::sc_module_name name);

  void request_thread();
};


#endif  //  SRC_DUT_H_
