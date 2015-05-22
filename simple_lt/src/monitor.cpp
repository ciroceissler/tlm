//  Author:    Ciro Ceissler
//  Email:     ciro at ceissler.com.br

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
  unsigned char*   ptr = trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();
  unsigned char*   byt = trans.get_byte_enable_ptr();
  unsigned int     wid = trans.get_streaming_width();

  trans.set_response_status( tlm::TLM_OK_RESPONSE ); 

  std::cout << sc_time_stamp() << " : [monitor] b_transport - rcv = " << ptr << std::endl;
}

