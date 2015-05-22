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
  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
  sc_time delay = sc_time(20, SC_NS);

  for (int i = 100; i; --i) {
    std::string msg;

    msg = "dut msg number: " + i;

    std::cout << sc_time_stamp() << " : [dut] " << msg << std::endl;

    tlm::tlm_command cmd = tlm::TLM_WRITE_COMMAND;

    trans->set_command( cmd );
    trans->set_address( 0 );
    trans->set_data_ptr( reinterpret_cast<unsigned char*>(msg) );
    trans->set_data_length( 4 );
    trans->set_streaming_width( 4 );
    trans->set_byte_enable_ptr( 0 );
    trans->set_dmi_allowed( false );
    trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );

    initiator_socket->b_transport( *trans, delay );

    if ( trans->is_response_error() ) {
      SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
    }

    wait(delay);
  }
}

//  TLM-2 blocking transport method
void DUT::b_transport(tlm::tlm_generic_payload& trans, sc_time& delay) {

  tlm::tlm_command cmd = trans.get_command();
  sc_dt::uint64    adr = trans.get_address() / 4;
  unsigned char*   ptr = trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();
  unsigned char*   byt = trans.get_byte_enable_ptr();
  unsigned int     wid = trans.get_streaming_width();

  trans.set_response_status( tlm::TLM_OK_RESPONSE ); 

  std::cout << sc_time_stamp() << " : [dut] b_transport - rcv = " << ptr << std::endl;
}

