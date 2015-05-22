//  Project:   OTN 100G
//  Author:    Ciro Ceissler
//  Email:     ciroc at cpqd.com.br
//  Copyright: 2015 @ CPqD

#include <monitor.h>

Monitor::Monitor(sc_core::sc_module_name name) :
  sc_core::sc_module(name),
  target_socket("target_socket") {

  //  Register callback for incoming b_transport interface method call
  target_socket.register_b_transport(this, &Monitor::b_transport);
}

//  TLM-2 blocking transport method
void Monitor::b_transport(tlm::tlm_generic_payload& trans, sc_time& delay) {

  tlm::tlm_command cmd = trans.get_command();
  sc_dt::uint64    adr = trans.get_address() / 4;
  Package*         ptr = (Package *) trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();
  unsigned char*   byt = trans.get_byte_enable_ptr();
  unsigned int     wid = trans.get_streaming_width();

//  if (adr >= sc_dt::uint64(SIZE) || byt != 0 || len > 4 || wid < len)
//    SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");

  trans.set_response_status( tlm::TLM_OK_RESPONSE ); 

  std::cout << sc_time_stamp() << " : [monitor] b_transport - rcv = " << ptr->get_str() << std::endl;
}

