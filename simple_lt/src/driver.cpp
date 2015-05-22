//  Author:    Ciro Ceissler
//  Email:     ciro at ceissler.com.br

#include <driver.h>

Driver::Driver(sc_core::sc_module_name name) :
  sc_core::sc_module(name),
  initiator_socket("initiator_socket") {

  SC_THREAD(request_thread);
}

void Driver::request_thread() {

  sc_time delay = SC_ZERO_TIME;

  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;

  for (unsigned int i = 10; i; --i) {
    std::string msg;

    msg = "driver msg number: " + std::to_string(static_cast<long long unsigned int>(i));

    std::cout << sc_time_stamp() << " : [driver] " << msg << std::endl;

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

