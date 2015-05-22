//  Author:    Ciro Ceissler
//  Email:     ciro at ceissler.com.br

#include <dut.h>

DUT::DUT(sc_core::sc_module_name name) :
  sc_core::sc_module(name),
  target_socket("target_socket"),
  initiator_socket("initiator_socket") {

  //  Register callback for incoming b_transport interface method call
  target_socket.register_b_transport(this, &DUT::b_transport);

  SC_THREAD(request_thread);
}

void DUT::request_thread() {

  sc_time delay = sc_time(5, SC_NS);

  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;

  for (unsigned i = 10; i; --i) {
    std::string msg;

    wait(e_wait_data);

    wait(delay);

    msg = "dut msg number: " + std::to_string(static_cast<long long unsigned int>(i));

    std::cout << sc_time_stamp() << " : [dut] " << msg << std::endl;

    tlm::tlm_command cmd = tlm::TLM_WRITE_COMMAND;

    trans->set_command( cmd );
    trans->set_address( 0 );
    trans->set_data_ptr( (unsigned char*) msg.c_str() );
    trans->set_data_length( 4 );
    trans->set_streaming_width( 4 );
    trans->set_byte_enable_ptr( 0 );
    trans->set_dmi_allowed( false );
    trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );

    initiator_socket->b_transport( *trans, delay );

    if ( trans->is_response_error() ) {
      SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
    }
  }
}

//  TLM-2 blocking transport method
void DUT::b_transport(tlm::tlm_generic_payload& trans, sc_time& delay) {

  sc_time internal_delay = sc_time(10, SC_NS);

  tlm::tlm_command cmd = trans.get_command();
  sc_dt::uint64    adr = trans.get_address() / 4;
  unsigned char*   ptr = trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();
  unsigned char*   byt = trans.get_byte_enable_ptr();
  unsigned int     wid = trans.get_streaming_width();

  std::cout << sc_time_stamp() << " : [dut] b_transport - rcv = " << ptr << std::endl;

  e_wait_data.notify();

  wait(internal_delay);

  trans.set_response_status( tlm::TLM_OK_RESPONSE );
}

