//  Project:   OTN 100G
//  Author:    Ciro Ceissler
//  Email:     ciroc at cpqd.com.br
//  Copyright: 2015 @ CPqD

#ifndef DUT_H_
#define DUT_H_

#include <systemc.h>
#include <tlm.h>
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/simple_initiator_socket.h"
#include <package.h>

class DUT : public sc_core::sc_module {
 private:
  virtual void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& delay);

 public:
  tlm_utils::simple_initiator_socket<DUT> initiator_socket;
  tlm_utils::simple_target_socket<DUT> target_socket;

  SC_HAS_PROCESS(DUT);

  //  Constructor
  explicit DUT(sc_core::sc_module_name name);

  //  Communication Protocol
  void RequestThread();
};


#endif  //  DUT_H_
