<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>tlm</name>
    <path>/home/f21538/systemc-2.3.3/src/</path>
    <filename>a00122</filename>
    <includes id="a00159" name="tlm_version.h" local="yes" imported="no">tlm_core/tlm_2/tlm_version.h</includes>
    <includes id="a00123" name="tlm_analysis.h" local="yes" imported="no">tlm_core/tlm_1/tlm_analysis/tlm_analysis.h</includes>
    <includes id="a00143" name="tlm_req_rsp.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_req_rsp.h</includes>
    <includes id="a00144" name="tlm_2_interfaces.h" local="yes" imported="no">tlm_core/tlm_2/tlm_2_interfaces/tlm_2_interfaces.h</includes>
    <includes id="a00149" name="tlm_generic_payload.h" local="yes" imported="no">tlm_core/tlm_2/tlm_generic_payload/tlm_generic_payload.h</includes>
    <includes id="a00157" name="tlm_sockets.h" local="yes" imported="no">tlm_core/tlm_2/tlm_sockets/tlm_sockets.h</includes>
    <includes id="a00154" name="tlm_quantum.h" local="yes" imported="no">tlm_core/tlm_2/tlm_quantum/tlm_quantum.h</includes>
  </compound>
  <compound kind="file">
    <name>tlm_analysis.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_analysis/</path>
    <filename>a00123</filename>
    <includes id="a00128" name="tlm_write_if.h" local="yes" imported="no">tlm_core/tlm_1/tlm_analysis/tlm_write_if.h</includes>
    <includes id="a00125" name="tlm_analysis_if.h" local="yes" imported="no">tlm_core/tlm_1/tlm_analysis/tlm_analysis_if.h</includes>
    <includes id="a00127" name="tlm_analysis_triple.h" local="yes" imported="no">tlm_core/tlm_1/tlm_analysis/tlm_analysis_triple.h</includes>
    <includes id="a00126" name="tlm_analysis_port.h" local="yes" imported="no">tlm_core/tlm_1/tlm_analysis/tlm_analysis_port.h</includes>
    <includes id="a00124" name="tlm_analysis_fifo.h" local="yes" imported="no">tlm_core/tlm_1/tlm_analysis/tlm_analysis_fifo.h</includes>
  </compound>
  <compound kind="file">
    <name>tlm_analysis_fifo.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_analysis/</path>
    <filename>a00124</filename>
    <includes id="a00135" name="tlm_fifo.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_channels/tlm_fifo/tlm_fifo.h</includes>
    <includes id="a00125" name="tlm_analysis_if.h" local="yes" imported="no">tlm_core/tlm_1/tlm_analysis/tlm_analysis_if.h</includes>
    <includes id="a00127" name="tlm_analysis_triple.h" local="yes" imported="no">tlm_core/tlm_1/tlm_analysis/tlm_analysis_triple.h</includes>
    <class kind="class">tlm::tlm_analysis_fifo</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_analysis_if.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_analysis/</path>
    <filename>a00125</filename>
    <includes id="a00128" name="tlm_write_if.h" local="yes" imported="no">tlm_core/tlm_1/tlm_analysis/tlm_write_if.h</includes>
    <class kind="class">tlm::tlm_analysis_if</class>
    <class kind="class">tlm::tlm_delayed_analysis_if</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_analysis_port.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_analysis/</path>
    <filename>a00126</filename>
    <includes id="a00125" name="tlm_analysis_if.h" local="yes" imported="no">tlm_core/tlm_1/tlm_analysis/tlm_analysis_if.h</includes>
    <class kind="class">tlm::tlm_analysis_port</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_analysis_triple.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_analysis/</path>
    <filename>a00127</filename>
    <class kind="struct">tlm::tlm_analysis_triple</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_write_if.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_analysis/</path>
    <filename>a00128</filename>
    <class kind="class">tlm::tlm_write_if</class>
    <class kind="class">tlm::tlm_delayed_write_if</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_core_ifs.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_req_rsp/tlm_1_interfaces/</path>
    <filename>a00129</filename>
    <includes id="a00132" name="tlm_tag.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_1_interfaces/tlm_tag.h</includes>
    <class kind="class">tlm::tlm_transport_if</class>
    <class kind="class">tlm::tlm_blocking_get_if</class>
    <class kind="class">tlm::tlm_blocking_put_if</class>
    <class kind="class">tlm::tlm_nonblocking_get_if</class>
    <class kind="class">tlm::tlm_nonblocking_put_if</class>
    <class kind="class">tlm::tlm_get_if</class>
    <class kind="class">tlm::tlm_put_if</class>
    <class kind="class">tlm::tlm_blocking_peek_if</class>
    <class kind="class">tlm::tlm_nonblocking_peek_if</class>
    <class kind="class">tlm::tlm_peek_if</class>
    <class kind="class">tlm::tlm_blocking_get_peek_if</class>
    <class kind="class">tlm::tlm_nonblocking_get_peek_if</class>
    <class kind="class">tlm::tlm_get_peek_if</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_fifo_ifs.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_req_rsp/tlm_1_interfaces/</path>
    <filename>a00130</filename>
    <includes id="a00129" name="tlm_core_ifs.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_1_interfaces/tlm_core_ifs.h</includes>
    <class kind="class">tlm::tlm_fifo_debug_if</class>
    <class kind="class">tlm::tlm_fifo_put_if</class>
    <class kind="class">tlm::tlm_fifo_get_if</class>
    <class kind="class">tlm::tlm_fifo_config_size_if</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_master_slave_ifs.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_req_rsp/tlm_1_interfaces/</path>
    <filename>a00131</filename>
    <includes id="a00129" name="tlm_core_ifs.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_1_interfaces/tlm_core_ifs.h</includes>
    <class kind="class">tlm::tlm_blocking_master_if</class>
    <class kind="class">tlm::tlm_blocking_slave_if</class>
    <class kind="class">tlm::tlm_nonblocking_master_if</class>
    <class kind="class">tlm::tlm_nonblocking_slave_if</class>
    <class kind="class">tlm::tlm_master_if</class>
    <class kind="class">tlm::tlm_slave_if</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_tag.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_req_rsp/tlm_1_interfaces/</path>
    <filename>a00132</filename>
    <class kind="class">tlm::tlm_tag</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_adapters.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_req_rsp/tlm_adapters/</path>
    <filename>a00133</filename>
    <includes id="a00131" name="tlm_master_slave_ifs.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_1_interfaces/tlm_master_slave_ifs.h</includes>
    <class kind="class">tlm::tlm_transport_to_master</class>
    <class kind="class">tlm::tlm_slave_to_transport</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>circular_buffer.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_req_rsp/tlm_channels/tlm_fifo/</path>
    <filename>a00134</filename>
    <class kind="class">tlm::circular_buffer</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_fifo.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_req_rsp/tlm_channels/tlm_fifo/</path>
    <filename>a00135</filename>
    <includes id="a00130" name="tlm_fifo_ifs.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_1_interfaces/tlm_fifo_ifs.h</includes>
    <includes id="a00134" name="circular_buffer.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_channels/tlm_fifo/circular_buffer.h</includes>
    <includes id="a00137" name="tlm_fifo_put_get.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_channels/tlm_fifo/tlm_fifo_put_get.h</includes>
    <includes id="a00136" name="tlm_fifo_peek.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_channels/tlm_fifo/tlm_fifo_peek.h</includes>
    <includes id="a00138" name="tlm_fifo_resize.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_channels/tlm_fifo/tlm_fifo_resize.h</includes>
    <class kind="class">tlm::tlm_fifo</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_fifo_peek.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_req_rsp/tlm_channels/tlm_fifo/</path>
    <filename>a00136</filename>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_fifo_put_get.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_req_rsp/tlm_channels/tlm_fifo/</path>
    <filename>a00137</filename>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_fifo_resize.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_req_rsp/tlm_channels/tlm_fifo/</path>
    <filename>a00138</filename>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_put_get_imp.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_req_rsp/tlm_channels/tlm_req_rsp_channels/</path>
    <filename>a00139</filename>
    <includes id="a00131" name="tlm_master_slave_ifs.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_1_interfaces/tlm_master_slave_ifs.h</includes>
    <class kind="class">tlm::tlm_put_get_imp</class>
    <class kind="class">tlm::tlm_master_imp</class>
    <class kind="class">tlm::tlm_slave_imp</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_req_rsp_channels.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_req_rsp/tlm_channels/tlm_req_rsp_channels/</path>
    <filename>a00140</filename>
    <includes id="a00133" name="tlm_adapters.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_adapters/tlm_adapters.h</includes>
    <includes id="a00135" name="tlm_fifo.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_channels/tlm_fifo/tlm_fifo.h</includes>
    <includes id="a00139" name="tlm_put_get_imp.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_channels/tlm_req_rsp_channels/tlm_put_get_imp.h</includes>
    <class kind="class">tlm::tlm_req_rsp_channel</class>
    <class kind="class">tlm::tlm_transport_channel</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_event_finder.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_req_rsp/tlm_ports/</path>
    <filename>a00141</filename>
    <includes id="a00132" name="tlm_tag.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_1_interfaces/tlm_tag.h</includes>
    <class kind="class">tlm::tlm_event_finder_t</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_nonblocking_port.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_req_rsp/tlm_ports/</path>
    <filename>a00142</filename>
    <includes id="a00129" name="tlm_core_ifs.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_1_interfaces/tlm_core_ifs.h</includes>
    <includes id="a00141" name="tlm_event_finder.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_ports/tlm_event_finder.h</includes>
    <class kind="class">tlm::tlm_nonblocking_get_port</class>
    <class kind="class">tlm::tlm_nonblocking_peek_port</class>
    <class kind="class">tlm::tlm_nonblocking_put_port</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_req_rsp.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_1/tlm_req_rsp/</path>
    <filename>a00143</filename>
    <includes id="a00129" name="tlm_core_ifs.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_1_interfaces/tlm_core_ifs.h</includes>
    <includes id="a00131" name="tlm_master_slave_ifs.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_1_interfaces/tlm_master_slave_ifs.h</includes>
    <includes id="a00140" name="tlm_req_rsp_channels.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_channels/tlm_req_rsp_channels/tlm_req_rsp_channels.h</includes>
    <includes id="a00142" name="tlm_nonblocking_port.h" local="yes" imported="no">tlm_core/tlm_1/tlm_req_rsp/tlm_ports/tlm_nonblocking_port.h</includes>
  </compound>
  <compound kind="file">
    <name>tlm_2_interfaces.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_2/tlm_2_interfaces/</path>
    <filename>a00144</filename>
    <includes id="a00145" name="tlm_dmi.h" local="yes" imported="no">tlm_core/tlm_2/tlm_2_interfaces/tlm_dmi.h</includes>
    <includes id="a00146" name="tlm_fw_bw_ifs.h" local="yes" imported="no">tlm_core/tlm_2/tlm_2_interfaces/tlm_fw_bw_ifs.h</includes>
  </compound>
  <compound kind="file">
    <name>tlm_dmi.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_2/tlm_2_interfaces/</path>
    <filename>a00145</filename>
    <class kind="class">tlm::tlm_dmi</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_fw_bw_ifs.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_2/tlm_2_interfaces/</path>
    <filename>a00146</filename>
    <includes id="a00149" name="tlm_generic_payload.h" local="yes" imported="no">tlm_core/tlm_2/tlm_generic_payload/tlm_generic_payload.h</includes>
    <includes id="a00145" name="tlm_dmi.h" local="yes" imported="no">tlm_core/tlm_2/tlm_2_interfaces/tlm_dmi.h</includes>
    <class kind="class">tlm::tlm_fw_nonblocking_transport_if</class>
    <class kind="class">tlm::tlm_bw_nonblocking_transport_if</class>
    <class kind="class">tlm::tlm_blocking_transport_if</class>
    <class kind="class">tlm::tlm_fw_direct_mem_if</class>
    <class kind="class">tlm::tlm_bw_direct_mem_if</class>
    <class kind="class">tlm::tlm_transport_dbg_if</class>
    <class kind="struct">tlm::tlm_base_protocol_types</class>
    <class kind="class">tlm::tlm_fw_transport_if</class>
    <class kind="class">tlm::tlm_bw_transport_if</class>
    <namespace>tlm</namespace>
    <member kind="enumeration">
      <name>tlm_sync_enum</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>adac10369502c45362dded44267fea971</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_ACCEPTED</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>adac10369502c45362dded44267fea971af6204a34490ffed0970e74a5a08fb389</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_UPDATED</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>adac10369502c45362dded44267fea971af9691927ab58a12f9e075fd128543271</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_COMPLETED</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>adac10369502c45362dded44267fea971a1f3b5d4718b9ee198afca7753e5b7910</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tlm_array.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_2/tlm_generic_payload/</path>
    <filename>a00147</filename>
    <class kind="class">tlm::tlm_array</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_endian_conv.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_2/tlm_generic_payload/</path>
    <filename>a00148</filename>
    <includes id="a00150" name="tlm_gp.h" local="yes" imported="no">tlm_core/tlm_2/tlm_generic_payload/tlm_gp.h</includes>
    <class kind="class">tlm::tlm_endian_context_pool</class>
    <class kind="class">tlm::tlm_endian_context</class>
    <class kind="class">tlm::tlm_bool</class>
    <namespace>tlm</namespace>
    <member kind="define">
      <type>#define</type>
      <name>uchar</name>
      <anchorfile>a00148.html</anchorfile>
      <anchor>aa8ddf20cdd716b652e76e23e5e700893</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>tlm_endian_context *</type>
      <name>establish_context</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a3d28c3714f7375334465f92755ed3e36</anchor>
      <arglist>(tlm_generic_payload *txn)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_db0</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a00c757c3a05f6f752c3517548d3d9bfc</anchor>
      <arglist>(uchar *src1, uchar *src2, uchar *dest1, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_dbtrue0</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>aa46881a54275e9de75dd42d68c596775</anchor>
      <arglist>(uchar *src1, uchar *, uchar *dest1, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_btrue0</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a56005dfa954345b1430b139de4b8d71b</anchor>
      <arglist>(uchar *, uchar *, uchar *, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_b0</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>ae0817f2a223b5c6d7b67573f9c2fcab7</anchor>
      <arglist>(uchar *, uchar *src2, uchar *, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_dbyb0</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a7f9767c130155d0424b2ccad468f75f5</anchor>
      <arglist>(uchar *src1, uchar *, uchar *dest1, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>loop_generic0</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a05d4d192746ca202086606dec7bacb82</anchor>
      <arglist>(int new_len, int new_stream_width, int orig_stream_width, int sizeof_databus, sc_dt::uint64 orig_start_address, sc_dt::uint64 new_start_address, int be_length, uchar *ie_data, uchar *ie_be, uchar *he_data, uchar *he_be)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tlm_from_hostendian_generic</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5be70eaa5ff8579d2e411208f58a6e48</anchor>
      <arglist>(tlm_generic_payload *txn, unsigned int sizeof_databus)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tlm_to_hostendian_generic</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>aac25bb86d1f480fd3155655502929131</anchor>
      <arglist>(tlm_generic_payload *txn, unsigned int sizeof_databus)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_d1</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a84cdb571cfc8732f851414f7d9bcd907</anchor>
      <arglist>(uchar *src1, uchar *src2, uchar *dest1, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_db1</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>ac1f531b30e3457e23cf7390af89d177c</anchor>
      <arglist>(uchar *src1, uchar *src2, uchar *dest1, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>true_b1</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a62d5cdda8e34c8d294c8bddfad2b430d</anchor>
      <arglist>(uchar *src1, uchar *src2, uchar *dest1, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_b1</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>ace6bc65e046b4e4462fee34350600937</anchor>
      <arglist>(uchar *src1, uchar *src2, uchar *dest1, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_dbyb1</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a857724d110a186851542ef0ed25bc988</anchor>
      <arglist>(uchar *src1, uchar *src2, uchar *dest1, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_dbytrue1</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a31284a38d814a73fadab6e4b7fd3f344</anchor>
      <arglist>(uchar *src1, uchar *src2, uchar *dest1, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>false_b1</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>abb2f8a63e8e66eb796f69f99b31ddd2f</anchor>
      <arglist>(uchar *dest1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>no_b1</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a51f3cb6b05cbcb2a0f3fec8fa61bf620</anchor>
      <arglist>(uchar *dest1)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loop_word1</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a2c4671fae3a52f0d9250c56535776cce</anchor>
      <arglist>(int bytes_left, int len0, int lenN, int sizeof_databus, uchar *start, uchar *end, uchar *src, uchar *bsrc, uchar *dest, uchar *bdest)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tlm_from_hostendian_word</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a0c2303006c0d0a9434b765387180f6c2</anchor>
      <arglist>(tlm_generic_payload *txn, unsigned int sizeof_databus)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tlm_to_hostendian_word</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a35b6acc377c3fde9939342bf09d2a688</anchor>
      <arglist>(tlm_generic_payload *txn, unsigned int sizeof_databus)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_d2</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5999c6d18647908c0e26d0f9904dc748</anchor>
      <arglist>(D *src1, D *src2, D *dest1, D *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_db2</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a8cbc0c1ac45d4daae88569377c49b76e</anchor>
      <arglist>(D *src1, D *src2, D *dest1, D *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_dbyb2</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a42e626507b6d547e498f97833c4c4a1c</anchor>
      <arglist>(D *src1, D *src2, D *dest1, D *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>loop_aligned2</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a8683423851f1e7bc2e4b4c7432e139c6</anchor>
      <arglist>(D *src1, D *src2, D *dest1, D *dest2, int words, int words_per_bus)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tlm_from_hostendian_aligned</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a90c3a9a3b2afd67bc8e174172e074e18</anchor>
      <arglist>(tlm_generic_payload *txn, unsigned int sizeof_databus)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tlm_to_hostendian_aligned</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>aa097d494385217cb589f046dc0adf62d</anchor>
      <arglist>(tlm_generic_payload *txn, unsigned int sizeof_databus)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tlm_from_hostendian_single</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a2c263fbf6cf9755d9f6eeca09dd23838</anchor>
      <arglist>(tlm_generic_payload *txn, unsigned int sizeof_databus)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tlm_to_hostendian_single</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>aa0b3eb97d390a24dd271eea549885fdf</anchor>
      <arglist>(tlm_generic_payload *txn, unsigned int sizeof_databus)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tlm_from_hostendian</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a7089b671b64863a5d1f59b8b5c9f648f</anchor>
      <arglist>(tlm_generic_payload *txn)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static tlm_endian_context_pool</type>
      <name>global_tlm_endian_context_pool</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a6b34372734d4a6bbcb6cafb771a130fe</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tlm_generic_payload.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_2/tlm_generic_payload/</path>
    <filename>a00149</filename>
    <includes id="a00151" name="tlm_helpers.h" local="yes" imported="no">tlm_core/tlm_2/tlm_generic_payload/tlm_helpers.h</includes>
    <includes id="a00152" name="tlm_phase.h" local="yes" imported="no">tlm_core/tlm_2/tlm_generic_payload/tlm_phase.h</includes>
    <includes id="a00150" name="tlm_gp.h" local="yes" imported="no">tlm_core/tlm_2/tlm_generic_payload/tlm_gp.h</includes>
    <includes id="a00148" name="tlm_endian_conv.h" local="yes" imported="no">tlm_core/tlm_2/tlm_generic_payload/tlm_endian_conv.h</includes>
  </compound>
  <compound kind="file">
    <name>tlm_gp.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_2/tlm_generic_payload/</path>
    <filename>a00150</filename>
    <includes id="a00147" name="tlm_array.h" local="yes" imported="no">tlm_core/tlm_2/tlm_generic_payload/tlm_array.h</includes>
    <class kind="class">tlm::tlm_mm_interface</class>
    <class kind="class">tlm::tlm_extension_base</class>
    <class kind="class">tlm::tlm_extension</class>
    <class kind="class">tlm::tlm_generic_payload</class>
    <namespace>tlm</namespace>
    <member kind="define">
      <type>#define</type>
      <name>TLM_BYTE_DISABLED</name>
      <anchorfile>a00150.html</anchorfile>
      <anchor>aee6c671fa7a49f01da4a966f33067175</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_BYTE_ENABLED</name>
      <anchorfile>a00150.html</anchorfile>
      <anchor>af8d2c3eb34ebd54e62bb2016614a827f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>tlm_command</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4afba0cb27464c4ef150b2f789f24b71</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_READ_COMMAND</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4afba0cb27464c4ef150b2f789f24b71a1538cd0007f7e145c31baab0c2ac1753</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_WRITE_COMMAND</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4afba0cb27464c4ef150b2f789f24b71aab9b159668e1dc31945911d21ffb067a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_IGNORE_COMMAND</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4afba0cb27464c4ef150b2f789f24b71a2222b571e251e54c5b6b233549f0c7cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>tlm_response_status</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5f8249b2be3f1d43dbe1c606f0ed20fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_OK_RESPONSE</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5f8249b2be3f1d43dbe1c606f0ed20fba79f0be38e413b4cfaac776a10ef1adf3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_INCOMPLETE_RESPONSE</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5f8249b2be3f1d43dbe1c606f0ed20fbae61def2069320c50021a70c32992eb12</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_GENERIC_ERROR_RESPONSE</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5f8249b2be3f1d43dbe1c606f0ed20fbaacb7bf66e73305034789abbaec9861db</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_ADDRESS_ERROR_RESPONSE</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5f8249b2be3f1d43dbe1c606f0ed20fba2a755caf4a4ca523938b58cba3757569</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_COMMAND_ERROR_RESPONSE</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5f8249b2be3f1d43dbe1c606f0ed20fbae5a49a5a273f26c14cc49def5095155a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_BURST_ERROR_RESPONSE</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5f8249b2be3f1d43dbe1c606f0ed20fba8cd3d40636f4e6241bdf37c16c5050c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_BYTE_ENABLE_ERROR_RESPONSE</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5f8249b2be3f1d43dbe1c606f0ed20fba997d04c01c857f77b2708d78d2e73087</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>tlm_gp_option</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a0fde6ca27eba0e951cd01159f1c20c5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_MIN_PAYLOAD</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a0fde6ca27eba0e951cd01159f1c20c5ea2020e97d7f0dbefe1a6b9b5cf37c3eeb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_FULL_PAYLOAD</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a0fde6ca27eba0e951cd01159f1c20c5eaa78f9c334dd18d32da0d156cda17d017</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_FULL_PAYLOAD_ACCEPTED</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a0fde6ca27eba0e951cd01159f1c20c5ea98e2ff9272ab162ebe3080bc839f2531</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>SC_API unsigned int</type>
      <name>max_num_extensions</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4b12c137cc2c98250b9c827f26530aed</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>SC_API_TEMPLATE_DECL_</type>
      <name>tlm_array&lt; tlm_extension_base * &gt;</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a1b128078b7c0f3ef54874fc55a6b890c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tlm_helpers.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_2/tlm_generic_payload/</path>
    <filename>a00151</filename>
    <namespace>tlm</namespace>
    <member kind="enumeration">
      <name>tlm_endianness</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>ad3ec82fe3e6948292e07afb8d40314cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_UNKNOWN_ENDIAN</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>ad3ec82fe3e6948292e07afb8d40314cfaf25081315ef066c9f708a2b5819266df</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_LITTLE_ENDIAN</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>ad3ec82fe3e6948292e07afb8d40314cfa1be4866a58af63ec96d8bf2a277d11ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_BIG_ENDIAN</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>ad3ec82fe3e6948292e07afb8d40314cfa0145acdbede3dcdddcb360d58c6c468d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>tlm_endianness</type>
      <name>get_host_endianness</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a60bacaed16f76e0420e79297aafbb475</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>host_has_little_endianness</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a94247be626723197f8f8bb67b9896826</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>has_host_endianness</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>ae3091d0317bcda0ccca3f44fe1a2da4c</anchor>
      <arglist>(tlm_endianness endianness)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tlm_phase.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_2/tlm_generic_payload/</path>
    <filename>a00152</filename>
    <class kind="class">tlm::tlm_phase</class>
    <namespace>tlm</namespace>
    <member kind="define">
      <type>#define</type>
      <name>TLM_DECLARE_EXTENDED_PHASE</name>
      <anchorfile>a00152.html</anchorfile>
      <anchor>a03ec06b65d3ffb10176b9149974abf6e</anchor>
      <arglist>(name_arg)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>DECLARE_EXTENDED_PHASE</name>
      <anchorfile>a00152.html</anchorfile>
      <anchor>a182e1fdfd98899160465a8549ecf6831</anchor>
      <arglist>(NameArg)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>aa42fd5fac3d38cf876c9efda37870de0</anchor>
      <arglist>(std::ostream &amp;s, const tlm_phase &amp;p)</arglist>
    </member>
    <member kind="variable">
      <type></type>
      <name>UNINITIALIZED_PHASE</name>
      <anchorfile>a00152.html</anchorfile>
      <anchor>aaf62ac93b29c135994fd941eaa1b8fea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type></type>
      <name>BEGIN_REQ</name>
      <anchorfile>a00152.html</anchorfile>
      <anchor>a80598f3be9e3363847ffffd9c583238e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type></type>
      <name>END_REQ</name>
      <anchorfile>a00152.html</anchorfile>
      <anchor>a1135e0988d6b87c0b5b98d4b37fb50cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type></type>
      <name>BEGIN_RESP</name>
      <anchorfile>a00152.html</anchorfile>
      <anchor>afb33be3f6df195c2948f2d784e0f5624</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tlm_global_quantum.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_2/tlm_quantum/</path>
    <filename>a00153</filename>
    <class kind="class">tlm::tlm_global_quantum</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_quantum.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_2/tlm_quantum/</path>
    <filename>a00154</filename>
    <includes id="a00153" name="tlm_global_quantum.h" local="yes" imported="no">tlm_core/tlm_2/tlm_quantum/tlm_global_quantum.h</includes>
  </compound>
  <compound kind="file">
    <name>tlm_base_socket_if.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_2/tlm_sockets/</path>
    <filename>a00155</filename>
    <class kind="class">tlm::tlm_base_socket_if</class>
    <namespace>tlm</namespace>
    <member kind="enumeration">
      <name>tlm_socket_category</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4c4ab9add0ec354433809466943bece8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_UNKNOWN_SOCKET</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4c4ab9add0ec354433809466943bece8a4cd503b53961644181c571e5c275bcdb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_INITIATOR_SOCKET</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4c4ab9add0ec354433809466943bece8a350f155f6138fa9947935852f90455fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_TARGET_SOCKET</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4c4ab9add0ec354433809466943bece8a0562a244fe6d3c16242621682ef7d6de</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_MULTI_SOCKET</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4c4ab9add0ec354433809466943bece8ae9a071e9be55c5888a0be7239a764945</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_MULTI_INITIATOR_SOCKET</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4c4ab9add0ec354433809466943bece8a4599b588ed8eefe565a508c35274b874</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_MULTI_TARGET_SOCKET</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4c4ab9add0ec354433809466943bece8a27978a1c11f50d8567b83f5389c42c99</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>tlm_initiator_socket.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_2/tlm_sockets/</path>
    <filename>a00156</filename>
    <includes id="a00155" name="tlm_base_socket_if.h" local="yes" imported="no">tlm_core/tlm_2/tlm_sockets/tlm_base_socket_if.h</includes>
    <includes id="a00146" name="tlm_fw_bw_ifs.h" local="yes" imported="no">tlm_core/tlm_2/tlm_2_interfaces/tlm_fw_bw_ifs.h</includes>
    <class kind="class">tlm::tlm_base_initiator_socket_b</class>
    <class kind="class">tlm::tlm_base_initiator_socket</class>
    <class kind="class">tlm::tlm_initiator_socket</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_sockets.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_2/tlm_sockets/</path>
    <filename>a00157</filename>
    <includes id="a00156" name="tlm_initiator_socket.h" local="yes" imported="no">tlm_core/tlm_2/tlm_sockets/tlm_initiator_socket.h</includes>
    <includes id="a00158" name="tlm_target_socket.h" local="yes" imported="no">tlm_core/tlm_2/tlm_sockets/tlm_target_socket.h</includes>
  </compound>
  <compound kind="file">
    <name>tlm_target_socket.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_2/tlm_sockets/</path>
    <filename>a00158</filename>
    <includes id="a00155" name="tlm_base_socket_if.h" local="yes" imported="no">tlm_core/tlm_2/tlm_sockets/tlm_base_socket_if.h</includes>
    <includes id="a00146" name="tlm_fw_bw_ifs.h" local="yes" imported="no">tlm_core/tlm_2/tlm_2_interfaces/tlm_fw_bw_ifs.h</includes>
    <class kind="class">tlm::tlm_base_target_socket_b</class>
    <class kind="class">tlm::tlm_base_target_socket</class>
    <class kind="class">tlm::tlm_target_socket</class>
    <namespace>tlm</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_version.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_core/tlm_2/</path>
    <filename>a00159</filename>
    <namespace>tlm</namespace>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_MAJOR</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>adf624a3e67d8577b0f9ea80185c47afa</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_MINOR</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>aa40e2beb2eb5cb8e70d6092f0a303112</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_PATCH</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>ab513103141dbdfecca0c54a924455201</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_ORIGINATOR</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>a21093b43486ddc2dd06121ee152d2ebf</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_SEPARATOR</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>a466b3dedc2e9cdf3babffdc20d9ce335</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_IS_PRERELEASE</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>a4bda3954a2b14fb0618d8887e5c0f9fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_PRERELEASE</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>ad921697b8da6857b36fd8b0a22781c57</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_RELEASE_YEAR</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>aac6ebfcefbd8aae75946396161e4f71c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_RELEASE_MONTH</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>a4e90c34a6804ff046a591b91813450f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_RELEASE_DAY</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>a743b721c52720fdb7ab45017c2f45bab</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_COPYRIGHT</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>a650da75b7d247ed4c1e18cb8544aa2c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_RELEASE_DATE</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>a5afb6aae3613d4574a679a18e50a0129</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_STR</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>a48f3886627d73e17088e9916c576232c</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_STR_HELPER</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>ae746148fc4401089c0fdb1530aa8fb0f</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_STRING_MAJOR</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>ac0070ea2be660bce2c45c7aae5c38b19</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_STRING_MINOR</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>a37f50cfec5227cecbd4838345671dc0d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_STRING_PATCH</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>a1fc01787d53f7e3e44deebc67f149ba8</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_STRING_MMP</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>a6117a68cf803a69b0249d3897556ded6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_STRING_PRE_START</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>a53fbdf9461423741a70029656a238413</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_STRING_PRE_END</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>a19b87f4ee27e080fa19a1f27ab1f77b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_STRING_PRERELEASE</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>a550e634db50ed598be96acf61affff3a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_STRING_RELEASE_DATE</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>aafdfed605b12afb242282e61b6c8833e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_STRING</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>ac8c5ab5b078e0a6ccce557d65f829d0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION_STRING_2</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>a73e1178263850d8b65bc155ea0abf3e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_VERSION</name>
      <anchorfile>a00159.html</anchorfile>
      <anchor>a77bde380d8ac22f2dd2878af89aca03c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>const unsigned int</type>
      <name>tlm_version_major</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a09597334db87928718c4d21c22e2a416</anchor>
      <arglist>(TLM_VERSION_MAJOR)</arglist>
    </member>
    <member kind="function">
      <type>const unsigned int</type>
      <name>tlm_version_minor</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>adf4ea8c51b2c3d9e90d2af2272124d86</anchor>
      <arglist>(TLM_VERSION_MINOR)</arglist>
    </member>
    <member kind="function">
      <type>const unsigned int</type>
      <name>tlm_version_patch</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>aae2599cf538be4e4c4c2239b6615d5cc</anchor>
      <arglist>(TLM_VERSION_PATCH)</arglist>
    </member>
    <member kind="function">
      <type>const bool</type>
      <name>tlm_is_prerelease</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>ae23b7b83f69c1c91dcc42902f0a88965</anchor>
      <arglist>(TLM_IS_PRERELEASE)</arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>tlm_version_string</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a9925b7ff309c82d1666f2799e5603e01</anchor>
      <arglist>(TLM_VERSION_STRING)</arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>tlm_version_originator</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5926a372a18955e64e3adf879f220f14</anchor>
      <arglist>(TLM_VERSION_ORIGINATOR)</arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>tlm_version_prerelease</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a07a3a67082dfe0c4676f05329942a2f0</anchor>
      <arglist>(TLM_VERSION_PRERELEASE)</arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>tlm_version_release_date</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4d75bd93c0d34cfcb8879c0b07910ea7</anchor>
      <arglist>(TLM_VERSION_STRING_RELEASE_DATE)</arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>tlm_copyright_string</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5c3855c05d2d1050c9c25e853c28ce78</anchor>
      <arglist>(TLM_COPYRIGHT)</arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>tlm_version_string_2</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a315db0266704eb11d18066b72418a4ac</anchor>
      <arglist>(TLM_VERSION_STRING_2)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>tlm_release</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a055cccc72aa9d415bdd2cd0c66ed1018</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>tlm_version</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a989c5732d3b85ac7aaede545a6ac144b</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>tlm_copyright</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4b9f14162997a4fb64f7edbfe874635f</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>convenience_socket_bases.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_utils/</path>
    <filename>a00160</filename>
    <class kind="class">tlm_utils::convenience_socket_base</class>
    <class kind="class">tlm_utils::simple_socket_base</class>
    <class kind="class">tlm_utils::passthrough_socket_base</class>
    <class kind="class">tlm_utils::multi_socket_base</class>
    <class kind="class">tlm_utils::convenience_socket_cb_holder</class>
    <namespace>sc_core</namespace>
    <namespace>tlm_utils</namespace>
    <member kind="variable">
      <type>class SC_API</type>
      <name>sc_object</name>
      <anchorfile>a00172.html</anchorfile>
      <anchor>a8eb02df3abf893e699a4802f7c7e029b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>instance_specific_extensions.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_utils/</path>
    <filename>a00161</filename>
    <includes id="a00162" name="instance_specific_extensions_int.h" local="yes" imported="no">tlm_utils/instance_specific_extensions_int.h</includes>
    <class kind="class">tlm_utils::instance_specific_extension</class>
    <class kind="class">tlm_utils::instance_specific_extension_carrier</class>
    <namespace>tlm_utils</namespace>
  </compound>
  <compound kind="file">
    <name>instance_specific_extensions_int.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_utils/</path>
    <filename>a00162</filename>
    <includes id="a00122" name="tlm" local="no" imported="no">tlm</includes>
    <class kind="class">tlm_utils::ispex_base</class>
    <class kind="class">tlm_utils::instance_specific_extensions_per_accessor</class>
    <class kind="class">tlm_utils::instance_specific_extension_container</class>
    <class kind="class">tlm_utils::instance_specific_extension_accessor</class>
    <namespace>tlm_utils</namespace>
    <namespace>tlm</namespace>
    <member kind="variable">
      <type>class SC_API</type>
      <name>ispex_base</name>
      <anchorfile>a00175.html</anchorfile>
      <anchor>ae90aaec960512b93e703d6c70957c85c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>class SC_API</type>
      <name>instance_specific_extension_accessor</name>
      <anchorfile>a00175.html</anchorfile>
      <anchor>af4498a4ef1856bf8061af3e07c4322a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>class SC_API</type>
      <name>instance_specific_extension_container</name>
      <anchorfile>a00175.html</anchorfile>
      <anchor>ac056aaffdba5da92f9fe5b9f943bb3d9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>multi_passthrough_initiator_socket.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_utils/</path>
    <filename>a00163</filename>
    <includes id="a00165" name="multi_socket_bases.h" local="yes" imported="no">multi_socket_bases.h</includes>
    <class kind="class">tlm_utils::multi_passthrough_initiator_socket</class>
    <class kind="class">tlm_utils::multi_passthrough_initiator_socket_optional</class>
    <namespace>tlm_utils</namespace>
  </compound>
  <compound kind="file">
    <name>multi_passthrough_target_socket.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_utils/</path>
    <filename>a00164</filename>
    <includes id="a00165" name="multi_socket_bases.h" local="yes" imported="no">tlm_utils/multi_socket_bases.h</includes>
    <class kind="class">tlm_utils::multi_passthrough_target_socket</class>
    <class kind="class">tlm_utils::multi_passthrough_target_socket_optional</class>
    <namespace>tlm_utils</namespace>
  </compound>
  <compound kind="file">
    <name>multi_socket_bases.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_utils/</path>
    <filename>a00165</filename>
    <includes id="a00122" name="tlm" local="no" imported="no">tlm</includes>
    <includes id="a00160" name="convenience_socket_bases.h" local="yes" imported="no">tlm_utils/convenience_socket_bases.h</includes>
    <class kind="struct">tlm_utils::fn_container</class>
    <class kind="class">tlm_utils::callback_binder_fw</class>
    <class kind="class">tlm_utils::callback_binder_bw</class>
    <class kind="class">tlm_utils::multi_init_base_if</class>
    <class kind="class">tlm_utils::multi_init_base</class>
    <class kind="class">tlm_utils::multi_target_base_if</class>
    <class kind="class">tlm_utils::multi_target_base</class>
    <class kind="class">tlm_utils::multi_to_multi_bind_base</class>
    <namespace>tlm_utils</namespace>
    <member kind="define">
      <type>#define</type>
      <name>TLM_DEFINE_FUNCTOR</name>
      <anchorfile>a00165.html</anchorfile>
      <anchor>a8eea231d314394acffe11478eaa2b745</anchor>
      <arglist>(name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_RET_VAL</name>
      <anchorfile>a00165.html</anchorfile>
      <anchor>a30545a4100e77d0433f075e33d4fcee7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_FULL_ARG_LIST</name>
      <anchorfile>a00165.html</anchorfile>
      <anchor>a74ef5947da19a5e1282238f7b8ef6236</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_ARG_LIST_WITHOUT_TYPES</name>
      <anchorfile>a00165.html</anchorfile>
      <anchor>a38237077f1029b767f52f9ad85b5fce5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_RET_VAL</name>
      <anchorfile>a00165.html</anchorfile>
      <anchor>a30545a4100e77d0433f075e33d4fcee7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_FULL_ARG_LIST</name>
      <anchorfile>a00165.html</anchorfile>
      <anchor>a74ef5947da19a5e1282238f7b8ef6236</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_ARG_LIST_WITHOUT_TYPES</name>
      <anchorfile>a00165.html</anchorfile>
      <anchor>a38237077f1029b767f52f9ad85b5fce5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_RET_VAL</name>
      <anchorfile>a00165.html</anchorfile>
      <anchor>a30545a4100e77d0433f075e33d4fcee7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_FULL_ARG_LIST</name>
      <anchorfile>a00165.html</anchorfile>
      <anchor>a74ef5947da19a5e1282238f7b8ef6236</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_ARG_LIST_WITHOUT_TYPES</name>
      <anchorfile>a00165.html</anchorfile>
      <anchor>a38237077f1029b767f52f9ad85b5fce5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_RET_VAL</name>
      <anchorfile>a00165.html</anchorfile>
      <anchor>a30545a4100e77d0433f075e33d4fcee7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_FULL_ARG_LIST</name>
      <anchorfile>a00165.html</anchorfile>
      <anchor>a74ef5947da19a5e1282238f7b8ef6236</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_ARG_LIST_WITHOUT_TYPES</name>
      <anchorfile>a00165.html</anchorfile>
      <anchor>a38237077f1029b767f52f9ad85b5fce5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_RET_VAL</name>
      <anchorfile>a00165.html</anchorfile>
      <anchor>a30545a4100e77d0433f075e33d4fcee7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_FULL_ARG_LIST</name>
      <anchorfile>a00165.html</anchorfile>
      <anchor>a74ef5947da19a5e1282238f7b8ef6236</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TLM_ARG_LIST_WITHOUT_TYPES</name>
      <anchorfile>a00165.html</anchorfile>
      <anchor>a38237077f1029b767f52f9ad85b5fce5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TLM_DEFINE_FUNCTOR</name>
      <anchorfile>a00175.html</anchorfile>
      <anchor>a390fa8d71631e38513ee2e9e0299c142</anchor>
      <arglist>(nb_transport)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TLM_DEFINE_FUNCTOR</name>
      <anchorfile>a00175.html</anchorfile>
      <anchor>a1141b46d17cd12eeb5d6ee4405aaf93d</anchor>
      <arglist>(b_transport)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TLM_DEFINE_FUNCTOR</name>
      <anchorfile>a00175.html</anchorfile>
      <anchor>ab02f9ff09e04a61d6722ce374004ca0a</anchor>
      <arglist>(debug_transport)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TLM_DEFINE_FUNCTOR</name>
      <anchorfile>a00175.html</anchorfile>
      <anchor>a9986c74b8d35ee3fe221ef5bdcb69d0c</anchor>
      <arglist>(get_dmi_ptr)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TLM_DEFINE_FUNCTOR</name>
      <anchorfile>a00175.html</anchorfile>
      <anchor>a29e24c8d62c4c6070fe7c6341f43e19c</anchor>
      <arglist>(invalidate_dmi)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>passthrough_target_socket.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_utils/</path>
    <filename>a00166</filename>
    <includes id="a00122" name="tlm" local="no" imported="no">tlm</includes>
    <includes id="a00160" name="convenience_socket_bases.h" local="yes" imported="no">tlm_utils/convenience_socket_bases.h</includes>
    <class kind="class">tlm_utils::passthrough_target_socket_b</class>
    <class kind="class">tlm_utils::passthrough_target_socket_b::process</class>
    <class kind="class">tlm_utils::passthrough_target_socket</class>
    <class kind="class">tlm_utils::passthrough_target_socket_optional</class>
    <class kind="class">tlm_utils::passthrough_target_socket_tagged_b</class>
    <class kind="class">tlm_utils::passthrough_target_socket_tagged_b::process</class>
    <class kind="class">tlm_utils::passthrough_target_socket_tagged</class>
    <class kind="class">tlm_utils::passthrough_target_socket_tagged_optional</class>
    <namespace>tlm_utils</namespace>
  </compound>
  <compound kind="file">
    <name>peq_with_cb_and_phase.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_utils/</path>
    <filename>a00167</filename>
    <includes id="a00122" name="tlm" local="no" imported="no">tlm</includes>
    <class kind="class">tlm_utils::time_ordered_list</class>
    <class kind="struct">tlm_utils::time_ordered_list::element</class>
    <class kind="class">tlm_utils::peq_with_cb_and_phase</class>
    <class kind="class">tlm_utils::peq_with_cb_and_phase::delta_list</class>
    <namespace>tlm_utils</namespace>
  </compound>
  <compound kind="file">
    <name>peq_with_get.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_utils/</path>
    <filename>a00168</filename>
    <class kind="class">tlm_utils::peq_with_get</class>
    <namespace>tlm_utils</namespace>
  </compound>
  <compound kind="file">
    <name>simple_initiator_socket.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_utils/</path>
    <filename>a00169</filename>
    <includes id="a00122" name="tlm" local="no" imported="no">tlm</includes>
    <includes id="a00160" name="convenience_socket_bases.h" local="yes" imported="no">tlm_utils/convenience_socket_bases.h</includes>
    <class kind="class">tlm_utils::simple_initiator_socket_b</class>
    <class kind="class">tlm_utils::simple_initiator_socket_b::process</class>
    <class kind="class">tlm_utils::simple_initiator_socket</class>
    <class kind="class">tlm_utils::simple_initiator_socket_optional</class>
    <class kind="class">tlm_utils::simple_initiator_socket_tagged_b</class>
    <class kind="class">tlm_utils::simple_initiator_socket_tagged_b::process</class>
    <class kind="class">tlm_utils::simple_initiator_socket_tagged</class>
    <class kind="class">tlm_utils::simple_initiator_socket_tagged_optional</class>
    <namespace>tlm_utils</namespace>
  </compound>
  <compound kind="file">
    <name>simple_target_socket.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_utils/</path>
    <filename>a00170</filename>
    <includes id="a00122" name="tlm" local="no" imported="no">tlm</includes>
    <includes id="a00160" name="convenience_socket_bases.h" local="yes" imported="no">tlm_utils/convenience_socket_bases.h</includes>
    <includes id="a00168" name="peq_with_get.h" local="yes" imported="no">tlm_utils/peq_with_get.h</includes>
    <class kind="class">tlm_utils::simple_target_socket_b</class>
    <class kind="class">tlm_utils::simple_target_socket_b::bw_process</class>
    <class kind="class">tlm_utils::simple_target_socket_b::fw_process</class>
    <class kind="class">tlm_utils::simple_target_socket_b::fw_process::process_handle_class</class>
    <class kind="class">tlm_utils::simple_target_socket_b::fw_process::process_handle_list</class>
    <class kind="struct">tlm_utils::simple_target_socket_b::fw_process::mm_end_event_ext</class>
    <class kind="class">tlm_utils::simple_target_socket</class>
    <class kind="class">tlm_utils::simple_target_socket_optional</class>
    <class kind="class">tlm_utils::simple_target_socket_tagged_b</class>
    <class kind="class">tlm_utils::simple_target_socket_tagged_b::bw_process</class>
    <class kind="class">tlm_utils::simple_target_socket_tagged_b::fw_process</class>
    <class kind="class">tlm_utils::simple_target_socket_tagged_b::fw_process::process_handle_class</class>
    <class kind="class">tlm_utils::simple_target_socket_tagged_b::fw_process::process_handle_list</class>
    <class kind="struct">tlm_utils::simple_target_socket_tagged_b::fw_process::mm_end_event_ext</class>
    <class kind="class">tlm_utils::simple_target_socket_tagged</class>
    <class kind="class">tlm_utils::simple_target_socket_tagged_optional</class>
    <namespace>tlm_utils</namespace>
  </compound>
  <compound kind="file">
    <name>tlm_quantumkeeper.h</name>
    <path>/home/f21538/systemc-2.3.3/src/tlm_utils/</path>
    <filename>a00171</filename>
    <includes id="a00153" name="tlm_global_quantum.h" local="yes" imported="no">tlm_core/tlm_2/tlm_quantum/tlm_global_quantum.h</includes>
    <class kind="class">tlm_utils::tlm_quantumkeeper</class>
    <namespace>tlm_utils</namespace>
  </compound>
  <compound kind="class">
    <name>sc_core::sc_export</name>
    <filename>a00033.html</filename>
  </compound>
  <compound kind="class">
    <name>sc_core::sc_interface</name>
    <filename>a00034.html</filename>
  </compound>
  <compound kind="class">
    <name>sc_core::sc_object</name>
    <filename>a00035.html</filename>
  </compound>
  <compound kind="class">
    <name>sc_core::sc_port</name>
    <filename>a00036.html</filename>
  </compound>
  <compound kind="namespace">
    <name>sc_core</name>
    <filename>a00172.html</filename>
    <member kind="variable">
      <type>class SC_API</type>
      <name>sc_object</name>
      <anchorfile>a00172.html</anchorfile>
      <anchor>a8eb02df3abf893e699a4802f7c7e029b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>tlm</name>
    <filename>a00174.html</filename>
    <class kind="class">tlm::tlm_analysis_fifo</class>
    <class kind="class">tlm::tlm_analysis_if</class>
    <class kind="class">tlm::tlm_delayed_analysis_if</class>
    <class kind="class">tlm::tlm_analysis_port</class>
    <class kind="struct">tlm::tlm_analysis_triple</class>
    <class kind="class">tlm::tlm_write_if</class>
    <class kind="class">tlm::tlm_delayed_write_if</class>
    <class kind="class">tlm::tlm_transport_if</class>
    <class kind="class">tlm::tlm_blocking_get_if</class>
    <class kind="class">tlm::tlm_blocking_put_if</class>
    <class kind="class">tlm::tlm_nonblocking_get_if</class>
    <class kind="class">tlm::tlm_nonblocking_put_if</class>
    <class kind="class">tlm::tlm_get_if</class>
    <class kind="class">tlm::tlm_put_if</class>
    <class kind="class">tlm::tlm_blocking_peek_if</class>
    <class kind="class">tlm::tlm_nonblocking_peek_if</class>
    <class kind="class">tlm::tlm_peek_if</class>
    <class kind="class">tlm::tlm_blocking_get_peek_if</class>
    <class kind="class">tlm::tlm_nonblocking_get_peek_if</class>
    <class kind="class">tlm::tlm_get_peek_if</class>
    <class kind="class">tlm::tlm_fifo_debug_if</class>
    <class kind="class">tlm::tlm_fifo_put_if</class>
    <class kind="class">tlm::tlm_fifo_get_if</class>
    <class kind="class">tlm::tlm_fifo_config_size_if</class>
    <class kind="class">tlm::tlm_blocking_master_if</class>
    <class kind="class">tlm::tlm_blocking_slave_if</class>
    <class kind="class">tlm::tlm_nonblocking_master_if</class>
    <class kind="class">tlm::tlm_nonblocking_slave_if</class>
    <class kind="class">tlm::tlm_master_if</class>
    <class kind="class">tlm::tlm_slave_if</class>
    <class kind="class">tlm::tlm_tag</class>
    <class kind="class">tlm::tlm_transport_to_master</class>
    <class kind="class">tlm::tlm_slave_to_transport</class>
    <class kind="class">tlm::circular_buffer</class>
    <class kind="class">tlm::tlm_fifo</class>
    <class kind="class">tlm::tlm_put_get_imp</class>
    <class kind="class">tlm::tlm_master_imp</class>
    <class kind="class">tlm::tlm_slave_imp</class>
    <class kind="class">tlm::tlm_req_rsp_channel</class>
    <class kind="class">tlm::tlm_transport_channel</class>
    <class kind="class">tlm::tlm_event_finder_t</class>
    <class kind="class">tlm::tlm_nonblocking_get_port</class>
    <class kind="class">tlm::tlm_nonblocking_peek_port</class>
    <class kind="class">tlm::tlm_nonblocking_put_port</class>
    <class kind="class">tlm::tlm_dmi</class>
    <class kind="class">tlm::tlm_fw_nonblocking_transport_if</class>
    <class kind="class">tlm::tlm_bw_nonblocking_transport_if</class>
    <class kind="class">tlm::tlm_blocking_transport_if</class>
    <class kind="class">tlm::tlm_fw_direct_mem_if</class>
    <class kind="class">tlm::tlm_bw_direct_mem_if</class>
    <class kind="class">tlm::tlm_transport_dbg_if</class>
    <class kind="struct">tlm::tlm_base_protocol_types</class>
    <class kind="class">tlm::tlm_fw_transport_if</class>
    <class kind="class">tlm::tlm_bw_transport_if</class>
    <class kind="class">tlm::tlm_array</class>
    <class kind="class">tlm::tlm_endian_context_pool</class>
    <class kind="class">tlm::tlm_endian_context</class>
    <class kind="class">tlm::tlm_bool</class>
    <class kind="class">tlm::tlm_mm_interface</class>
    <class kind="class">tlm::tlm_extension_base</class>
    <class kind="class">tlm::tlm_extension</class>
    <class kind="class">tlm::tlm_generic_payload</class>
    <class kind="class">tlm::tlm_phase</class>
    <class kind="class">tlm::tlm_global_quantum</class>
    <class kind="class">tlm::tlm_base_socket_if</class>
    <class kind="class">tlm::tlm_base_initiator_socket_b</class>
    <class kind="class">tlm::tlm_base_initiator_socket</class>
    <class kind="class">tlm::tlm_initiator_socket</class>
    <class kind="class">tlm::tlm_base_target_socket_b</class>
    <class kind="class">tlm::tlm_base_target_socket</class>
    <class kind="class">tlm::tlm_target_socket</class>
    <member kind="enumeration">
      <name>tlm_sync_enum</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>adac10369502c45362dded44267fea971</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_ACCEPTED</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>adac10369502c45362dded44267fea971af6204a34490ffed0970e74a5a08fb389</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_UPDATED</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>adac10369502c45362dded44267fea971af9691927ab58a12f9e075fd128543271</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_COMPLETED</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>adac10369502c45362dded44267fea971a1f3b5d4718b9ee198afca7753e5b7910</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>tlm_command</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4afba0cb27464c4ef150b2f789f24b71</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_READ_COMMAND</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4afba0cb27464c4ef150b2f789f24b71a1538cd0007f7e145c31baab0c2ac1753</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_WRITE_COMMAND</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4afba0cb27464c4ef150b2f789f24b71aab9b159668e1dc31945911d21ffb067a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_IGNORE_COMMAND</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4afba0cb27464c4ef150b2f789f24b71a2222b571e251e54c5b6b233549f0c7cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>tlm_response_status</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5f8249b2be3f1d43dbe1c606f0ed20fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_OK_RESPONSE</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5f8249b2be3f1d43dbe1c606f0ed20fba79f0be38e413b4cfaac776a10ef1adf3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_INCOMPLETE_RESPONSE</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5f8249b2be3f1d43dbe1c606f0ed20fbae61def2069320c50021a70c32992eb12</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_GENERIC_ERROR_RESPONSE</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5f8249b2be3f1d43dbe1c606f0ed20fbaacb7bf66e73305034789abbaec9861db</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_ADDRESS_ERROR_RESPONSE</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5f8249b2be3f1d43dbe1c606f0ed20fba2a755caf4a4ca523938b58cba3757569</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_COMMAND_ERROR_RESPONSE</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5f8249b2be3f1d43dbe1c606f0ed20fbae5a49a5a273f26c14cc49def5095155a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_BURST_ERROR_RESPONSE</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5f8249b2be3f1d43dbe1c606f0ed20fba8cd3d40636f4e6241bdf37c16c5050c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_BYTE_ENABLE_ERROR_RESPONSE</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5f8249b2be3f1d43dbe1c606f0ed20fba997d04c01c857f77b2708d78d2e73087</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>tlm_gp_option</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a0fde6ca27eba0e951cd01159f1c20c5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_MIN_PAYLOAD</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a0fde6ca27eba0e951cd01159f1c20c5ea2020e97d7f0dbefe1a6b9b5cf37c3eeb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_FULL_PAYLOAD</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a0fde6ca27eba0e951cd01159f1c20c5eaa78f9c334dd18d32da0d156cda17d017</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_FULL_PAYLOAD_ACCEPTED</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a0fde6ca27eba0e951cd01159f1c20c5ea98e2ff9272ab162ebe3080bc839f2531</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>tlm_endianness</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>ad3ec82fe3e6948292e07afb8d40314cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_UNKNOWN_ENDIAN</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>ad3ec82fe3e6948292e07afb8d40314cfaf25081315ef066c9f708a2b5819266df</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_LITTLE_ENDIAN</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>ad3ec82fe3e6948292e07afb8d40314cfa1be4866a58af63ec96d8bf2a277d11ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_BIG_ENDIAN</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>ad3ec82fe3e6948292e07afb8d40314cfa0145acdbede3dcdddcb360d58c6c468d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>tlm_socket_category</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4c4ab9add0ec354433809466943bece8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_UNKNOWN_SOCKET</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4c4ab9add0ec354433809466943bece8a4cd503b53961644181c571e5c275bcdb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_INITIATOR_SOCKET</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4c4ab9add0ec354433809466943bece8a350f155f6138fa9947935852f90455fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_TARGET_SOCKET</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4c4ab9add0ec354433809466943bece8a0562a244fe6d3c16242621682ef7d6de</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_MULTI_SOCKET</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4c4ab9add0ec354433809466943bece8ae9a071e9be55c5888a0be7239a764945</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_MULTI_INITIATOR_SOCKET</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4c4ab9add0ec354433809466943bece8a4599b588ed8eefe565a508c35274b874</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>TLM_MULTI_TARGET_SOCKET</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4c4ab9add0ec354433809466943bece8a27978a1c11f50d8567b83f5389c42c99</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>tlm_endian_context *</type>
      <name>establish_context</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a3d28c3714f7375334465f92755ed3e36</anchor>
      <arglist>(tlm_generic_payload *txn)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_db0</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a00c757c3a05f6f752c3517548d3d9bfc</anchor>
      <arglist>(uchar *src1, uchar *src2, uchar *dest1, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_dbtrue0</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>aa46881a54275e9de75dd42d68c596775</anchor>
      <arglist>(uchar *src1, uchar *, uchar *dest1, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_btrue0</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a56005dfa954345b1430b139de4b8d71b</anchor>
      <arglist>(uchar *, uchar *, uchar *, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_b0</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>ae0817f2a223b5c6d7b67573f9c2fcab7</anchor>
      <arglist>(uchar *, uchar *src2, uchar *, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_dbyb0</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a7f9767c130155d0424b2ccad468f75f5</anchor>
      <arglist>(uchar *src1, uchar *, uchar *dest1, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>loop_generic0</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a05d4d192746ca202086606dec7bacb82</anchor>
      <arglist>(int new_len, int new_stream_width, int orig_stream_width, int sizeof_databus, sc_dt::uint64 orig_start_address, sc_dt::uint64 new_start_address, int be_length, uchar *ie_data, uchar *ie_be, uchar *he_data, uchar *he_be)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tlm_from_hostendian_generic</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5be70eaa5ff8579d2e411208f58a6e48</anchor>
      <arglist>(tlm_generic_payload *txn, unsigned int sizeof_databus)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tlm_to_hostendian_generic</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>aac25bb86d1f480fd3155655502929131</anchor>
      <arglist>(tlm_generic_payload *txn, unsigned int sizeof_databus)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_d1</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a84cdb571cfc8732f851414f7d9bcd907</anchor>
      <arglist>(uchar *src1, uchar *src2, uchar *dest1, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_db1</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>ac1f531b30e3457e23cf7390af89d177c</anchor>
      <arglist>(uchar *src1, uchar *src2, uchar *dest1, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>true_b1</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a62d5cdda8e34c8d294c8bddfad2b430d</anchor>
      <arglist>(uchar *src1, uchar *src2, uchar *dest1, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_b1</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>ace6bc65e046b4e4462fee34350600937</anchor>
      <arglist>(uchar *src1, uchar *src2, uchar *dest1, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_dbyb1</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a857724d110a186851542ef0ed25bc988</anchor>
      <arglist>(uchar *src1, uchar *src2, uchar *dest1, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_dbytrue1</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a31284a38d814a73fadab6e4b7fd3f344</anchor>
      <arglist>(uchar *src1, uchar *src2, uchar *dest1, uchar *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>false_b1</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>abb2f8a63e8e66eb796f69f99b31ddd2f</anchor>
      <arglist>(uchar *dest1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>no_b1</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a51f3cb6b05cbcb2a0f3fec8fa61bf620</anchor>
      <arglist>(uchar *dest1)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>loop_word1</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a2c4671fae3a52f0d9250c56535776cce</anchor>
      <arglist>(int bytes_left, int len0, int lenN, int sizeof_databus, uchar *start, uchar *end, uchar *src, uchar *bsrc, uchar *dest, uchar *bdest)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tlm_from_hostendian_word</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a0c2303006c0d0a9434b765387180f6c2</anchor>
      <arglist>(tlm_generic_payload *txn, unsigned int sizeof_databus)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tlm_to_hostendian_word</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a35b6acc377c3fde9939342bf09d2a688</anchor>
      <arglist>(tlm_generic_payload *txn, unsigned int sizeof_databus)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_d2</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5999c6d18647908c0e26d0f9904dc748</anchor>
      <arglist>(D *src1, D *src2, D *dest1, D *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_db2</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a8cbc0c1ac45d4daae88569377c49b76e</anchor>
      <arglist>(D *src1, D *src2, D *dest1, D *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_dbyb2</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a42e626507b6d547e498f97833c4c4a1c</anchor>
      <arglist>(D *src1, D *src2, D *dest1, D *dest2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>loop_aligned2</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a8683423851f1e7bc2e4b4c7432e139c6</anchor>
      <arglist>(D *src1, D *src2, D *dest1, D *dest2, int words, int words_per_bus)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tlm_from_hostendian_aligned</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a90c3a9a3b2afd67bc8e174172e074e18</anchor>
      <arglist>(tlm_generic_payload *txn, unsigned int sizeof_databus)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tlm_to_hostendian_aligned</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>aa097d494385217cb589f046dc0adf62d</anchor>
      <arglist>(tlm_generic_payload *txn, unsigned int sizeof_databus)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tlm_from_hostendian_single</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a2c263fbf6cf9755d9f6eeca09dd23838</anchor>
      <arglist>(tlm_generic_payload *txn, unsigned int sizeof_databus)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tlm_to_hostendian_single</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>aa0b3eb97d390a24dd271eea549885fdf</anchor>
      <arglist>(tlm_generic_payload *txn, unsigned int sizeof_databus)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tlm_from_hostendian</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a7089b671b64863a5d1f59b8b5c9f648f</anchor>
      <arglist>(tlm_generic_payload *txn)</arglist>
    </member>
    <member kind="function">
      <type>SC_API unsigned int</type>
      <name>max_num_extensions</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4b12c137cc2c98250b9c827f26530aed</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>tlm_endianness</type>
      <name>get_host_endianness</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a60bacaed16f76e0420e79297aafbb475</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>host_has_little_endianness</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a94247be626723197f8f8bb67b9896826</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>has_host_endianness</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>ae3091d0317bcda0ccca3f44fe1a2da4c</anchor>
      <arglist>(tlm_endianness endianness)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>aa42fd5fac3d38cf876c9efda37870de0</anchor>
      <arglist>(std::ostream &amp;s, const tlm_phase &amp;p)</arglist>
    </member>
    <member kind="function">
      <type>const unsigned int</type>
      <name>tlm_version_major</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a09597334db87928718c4d21c22e2a416</anchor>
      <arglist>(TLM_VERSION_MAJOR)</arglist>
    </member>
    <member kind="function">
      <type>const unsigned int</type>
      <name>tlm_version_minor</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>adf4ea8c51b2c3d9e90d2af2272124d86</anchor>
      <arglist>(TLM_VERSION_MINOR)</arglist>
    </member>
    <member kind="function">
      <type>const unsigned int</type>
      <name>tlm_version_patch</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>aae2599cf538be4e4c4c2239b6615d5cc</anchor>
      <arglist>(TLM_VERSION_PATCH)</arglist>
    </member>
    <member kind="function">
      <type>const bool</type>
      <name>tlm_is_prerelease</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>ae23b7b83f69c1c91dcc42902f0a88965</anchor>
      <arglist>(TLM_IS_PRERELEASE)</arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>tlm_version_string</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a9925b7ff309c82d1666f2799e5603e01</anchor>
      <arglist>(TLM_VERSION_STRING)</arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>tlm_version_originator</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5926a372a18955e64e3adf879f220f14</anchor>
      <arglist>(TLM_VERSION_ORIGINATOR)</arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>tlm_version_prerelease</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a07a3a67082dfe0c4676f05329942a2f0</anchor>
      <arglist>(TLM_VERSION_PRERELEASE)</arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>tlm_version_release_date</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4d75bd93c0d34cfcb8879c0b07910ea7</anchor>
      <arglist>(TLM_VERSION_STRING_RELEASE_DATE)</arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>tlm_copyright_string</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a5c3855c05d2d1050c9c25e853c28ce78</anchor>
      <arglist>(TLM_COPYRIGHT)</arglist>
    </member>
    <member kind="function">
      <type>const std::string</type>
      <name>tlm_version_string_2</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a315db0266704eb11d18066b72418a4ac</anchor>
      <arglist>(TLM_VERSION_STRING_2)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>tlm_release</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a055cccc72aa9d415bdd2cd0c66ed1018</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>tlm_version</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a989c5732d3b85ac7aaede545a6ac144b</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>tlm_copyright</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a4b9f14162997a4fb64f7edbfe874635f</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static tlm_endian_context_pool</type>
      <name>global_tlm_endian_context_pool</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a6b34372734d4a6bbcb6cafb771a130fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>SC_API_TEMPLATE_DECL_</type>
      <name>tlm_array&lt; tlm_extension_base * &gt;</name>
      <anchorfile>a00174.html</anchorfile>
      <anchor>a1b128078b7c0f3ef54874fc55a6b890c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_analysis_fifo</name>
    <filename>a00051.html</filename>
    <templarg></templarg>
    <base>tlm::tlm_fifo</base>
    <base virtualness="virtual">tlm::tlm_analysis_if</base>
    <base virtualness="virtual">tlm_analysis_if&lt; tlm_analysis_triple&lt; T &gt; &gt;</base>
    <member kind="function">
      <type></type>
      <name>tlm_analysis_fifo</name>
      <anchorfile>a00051.html</anchorfile>
      <anchor>ad2fcfab1bc10ed8f4ec6af6cc91e4422</anchor>
      <arglist>(const char *nm)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_analysis_fifo</name>
      <anchorfile>a00051.html</anchorfile>
      <anchor>aa05a05cc9ce447366f863eeb86fd2731</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>write</name>
      <anchorfile>a00051.html</anchorfile>
      <anchor>abb8caeaff17439a37792c37a1d2cf0e4</anchor>
      <arglist>(const tlm_analysis_triple&lt; T &gt; &amp;t)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>write</name>
      <anchorfile>a00051.html</anchorfile>
      <anchor>ae10c090a5d94d0384ae2dd122eb1d628</anchor>
      <arglist>(const T &amp;t)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_analysis_if</name>
    <filename>a00052.html</filename>
    <templarg>T</templarg>
    <base virtualness="virtual">tlm::tlm_write_if</base>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_delayed_analysis_if</name>
    <filename>a00073.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">tlm::tlm_delayed_write_if</base>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_analysis_port</name>
    <filename>a00053.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">tlm::tlm_analysis_if</base>
    <member kind="function">
      <type></type>
      <name>tlm_analysis_port</name>
      <anchorfile>a00053.html</anchorfile>
      <anchor>afe8e69b543eca06c6b1739b130df47e7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_analysis_port</name>
      <anchorfile>a00053.html</anchorfile>
      <anchor>ab050b95ee53456e586c9b715eeaf1246</anchor>
      <arglist>(const char *nm)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>bind</name>
      <anchorfile>a00053.html</anchorfile>
      <anchor>a3a8198cf61dc2669336047c4b807c720</anchor>
      <arglist>(tlm_analysis_if&lt; T &gt; &amp;_if)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>a00053.html</anchorfile>
      <anchor>aca93ee2ea4ee3826a333a61a0bc99b5a</anchor>
      <arglist>(tlm_analysis_if&lt; T &gt; &amp;_if)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>unbind</name>
      <anchorfile>a00053.html</anchorfile>
      <anchor>a9a8a0800f4e6367ccc0fa959dc02133b</anchor>
      <arglist>(tlm_analysis_if&lt; T &gt; &amp;_if)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>write</name>
      <anchorfile>a00053.html</anchorfile>
      <anchor>ab200c87db02b8081980fefae5b2d4ce3</anchor>
      <arglist>(const T &amp;t)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>tlm::tlm_analysis_triple</name>
    <filename>a00054.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>tlm_analysis_triple</name>
      <anchorfile>a00054.html</anchorfile>
      <anchor>a2210a946fb322b20ac8c0cb91ae0ca92</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_analysis_triple</name>
      <anchorfile>a00054.html</anchorfile>
      <anchor>a536ea5201f8065df93413c6970a52dbe</anchor>
      <arglist>(const tlm_analysis_triple &amp;triple)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_analysis_triple</name>
      <anchorfile>a00054.html</anchorfile>
      <anchor>a7cb839455be5e8378eaf55b24505c7c9</anchor>
      <arglist>(const T &amp;t)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator T</name>
      <anchorfile>a00054.html</anchorfile>
      <anchor>a4030b2d8785833e49109cdbfab93d4ee</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator const T &amp;</name>
      <anchorfile>a00054.html</anchorfile>
      <anchor>a1b40d9415696532348e9f211e21319a9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable">
      <type>sc_core::sc_time</type>
      <name>start_time</name>
      <anchorfile>a00054.html</anchorfile>
      <anchor>ac3bd7afc43badfb62ca67f4f4428ce92</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>T</type>
      <name>transaction</name>
      <anchorfile>a00054.html</anchorfile>
      <anchor>a2063397e67a2c9b58549528a029cd125</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sc_core::sc_time</type>
      <name>end_time</name>
      <anchorfile>a00054.html</anchorfile>
      <anchor>a6765d8aa037f8ca0832e1f09c1a85c9e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_write_if</name>
    <filename>a00121.html</filename>
    <templarg>T</templarg>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>write</name>
      <anchorfile>a00121.html</anchorfile>
      <anchor>ad6255b234e4de3fd1cb9c4582a963d53</anchor>
      <arglist>(const T &amp;t)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_delayed_write_if</name>
    <filename>a00074.html</filename>
    <templarg></templarg>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>write</name>
      <anchorfile>a00074.html</anchorfile>
      <anchor>a30a4bdf64a877483975cca60940b396e</anchor>
      <arglist>(const T &amp;t, const sc_core::sc_time &amp;time)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_transport_if</name>
    <filename>a00119.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function" virtualness="pure">
      <type>virtual RSP</type>
      <name>transport</name>
      <anchorfile>a00119.html</anchorfile>
      <anchor>a2d276873385703711a4518bb56aadc56</anchor>
      <arglist>(const REQ &amp;)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>transport</name>
      <anchorfile>a00119.html</anchorfile>
      <anchor>a61735af8eb69a169ea6c2606ee2e20cc</anchor>
      <arglist>(const REQ &amp;req, RSP &amp;rsp)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_blocking_get_if</name>
    <filename>a00062.html</filename>
    <templarg>T</templarg>
    <member kind="function" virtualness="pure">
      <type>virtual T</type>
      <name>get</name>
      <anchorfile>a00062.html</anchorfile>
      <anchor>a1896a467a2abb84c83727fd4b430bb03</anchor>
      <arglist>(tlm_tag&lt; T &gt; *t=0)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>get</name>
      <anchorfile>a00062.html</anchorfile>
      <anchor>a74c2dc0f6c9e729eae1d0a1d59bf2067</anchor>
      <arglist>(T &amp;t)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_blocking_put_if</name>
    <filename>a00066.html</filename>
    <templarg>T</templarg>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>put</name>
      <anchorfile>a00066.html</anchorfile>
      <anchor>a290f17531327c121cdd6beb7c132fb28</anchor>
      <arglist>(const T &amp;t)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_nonblocking_get_if</name>
    <filename>a00097.html</filename>
    <templarg>T</templarg>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>nb_get</name>
      <anchorfile>a00097.html</anchorfile>
      <anchor>a9d83e8465db11c3bfb628369b5106148</anchor>
      <arglist>(T &amp;t)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>nb_can_get</name>
      <anchorfile>a00097.html</anchorfile>
      <anchor>af8bb0bcb1732f33c981c8dbf72c1fbb9</anchor>
      <arglist>(tlm_tag&lt; T &gt; *t=0) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const sc_core::sc_event &amp;</type>
      <name>ok_to_get</name>
      <anchorfile>a00097.html</anchorfile>
      <anchor>a8e340b3b95c7fbd60a6ce6872c9e3860</anchor>
      <arglist>(tlm_tag&lt; T &gt; *t=0) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_nonblocking_put_if</name>
    <filename>a00103.html</filename>
    <templarg>T</templarg>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>nb_put</name>
      <anchorfile>a00103.html</anchorfile>
      <anchor>a4342018a981d238b254d642d2114bac5</anchor>
      <arglist>(const T &amp;t)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>nb_can_put</name>
      <anchorfile>a00103.html</anchorfile>
      <anchor>a8f4b6891fbea8fa45dbf9dc8582a6f0d</anchor>
      <arglist>(tlm_tag&lt; T &gt; *t=0) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const sc_core::sc_event &amp;</type>
      <name>ok_to_put</name>
      <anchorfile>a00103.html</anchorfile>
      <anchor>ac42f9eccfa9004415b7eb19d89115d2f</anchor>
      <arglist>(tlm_tag&lt; T &gt; *t=0) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_get_if</name>
    <filename>a00090.html</filename>
    <templarg>T</templarg>
    <base virtualness="virtual">tlm::tlm_blocking_get_if</base>
    <base virtualness="virtual">tlm::tlm_nonblocking_get_if</base>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_put_if</name>
    <filename>a00109.html</filename>
    <templarg>T</templarg>
    <base virtualness="virtual">tlm::tlm_blocking_put_if</base>
    <base virtualness="virtual">tlm::tlm_nonblocking_put_if</base>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_blocking_peek_if</name>
    <filename>a00065.html</filename>
    <templarg>T</templarg>
    <member kind="function" virtualness="pure">
      <type>virtual T</type>
      <name>peek</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>ac35a8e1bc51bfdcd9425183fa4ad0a8e</anchor>
      <arglist>(tlm_tag&lt; T &gt; *t=0) const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>peek</name>
      <anchorfile>a00065.html</anchorfile>
      <anchor>a4a6de3379f1cf71691c209b54e41d73b</anchor>
      <arglist>(T &amp;t) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_nonblocking_peek_if</name>
    <filename>a00101.html</filename>
    <templarg>T</templarg>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>nb_peek</name>
      <anchorfile>a00101.html</anchorfile>
      <anchor>acda9f1feda9ee5f03ad90e3ac9838b64</anchor>
      <arglist>(T &amp;t) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>nb_can_peek</name>
      <anchorfile>a00101.html</anchorfile>
      <anchor>ac018695f84dcbe60afb5ea963ef96618</anchor>
      <arglist>(tlm_tag&lt; T &gt; *t=0) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const sc_core::sc_event &amp;</type>
      <name>ok_to_peek</name>
      <anchorfile>a00101.html</anchorfile>
      <anchor>aa0fa991cd69b6a1cafdf520e06cb5f97</anchor>
      <arglist>(tlm_tag&lt; T &gt; *t=0) const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_peek_if</name>
    <filename>a00106.html</filename>
    <templarg>T</templarg>
    <base virtualness="virtual">tlm::tlm_blocking_peek_if</base>
    <base virtualness="virtual">tlm::tlm_nonblocking_peek_if</base>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_blocking_get_peek_if</name>
    <filename>a00063.html</filename>
    <templarg>T</templarg>
    <base virtualness="virtual">tlm::tlm_blocking_get_if</base>
    <base virtualness="virtual">tlm::tlm_blocking_peek_if</base>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_nonblocking_get_peek_if</name>
    <filename>a00098.html</filename>
    <templarg>T</templarg>
    <base virtualness="virtual">tlm::tlm_nonblocking_get_if</base>
    <base virtualness="virtual">tlm::tlm_nonblocking_peek_if</base>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_get_peek_if</name>
    <filename>a00091.html</filename>
    <templarg>T</templarg>
    <base virtualness="virtual">tlm::tlm_get_if</base>
    <base virtualness="virtual">tlm::tlm_peek_if</base>
    <base virtualness="virtual">tlm::tlm_blocking_get_peek_if</base>
    <base virtualness="virtual">tlm::tlm_nonblocking_get_peek_if</base>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_fifo_debug_if</name>
    <filename>a00083.html</filename>
    <templarg></templarg>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>used</name>
      <anchorfile>a00083.html</anchorfile>
      <anchor>a506568e42b6e8057a451c47d400d2594</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int</type>
      <name>size</name>
      <anchorfile>a00083.html</anchorfile>
      <anchor>af8e6f2854877937d0a2dee43ac058b03</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>debug</name>
      <anchorfile>a00083.html</anchorfile>
      <anchor>a0d8d871e659416f40da29d8693a42706</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>nb_peek</name>
      <anchorfile>a00083.html</anchorfile>
      <anchor>ab3d0a0d3fd775c9ed190781019c3e8bd</anchor>
      <arglist>(T &amp;, int n) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>nb_poke</name>
      <anchorfile>a00083.html</anchorfile>
      <anchor>ae3ac1c7ae390e253bd7ca45fa274a33a</anchor>
      <arglist>(const T &amp;, int n=0)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_fifo_put_if</name>
    <filename>a00085.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">tlm::tlm_put_if</base>
    <base virtualness="virtual">tlm::tlm_fifo_debug_if</base>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_fifo_get_if</name>
    <filename>a00084.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">tlm::tlm_get_peek_if</base>
    <base virtualness="virtual">tlm::tlm_fifo_debug_if</base>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_fifo_config_size_if</name>
    <filename>a00082.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>nb_expand</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a446004fac35fe42eddf7099290eedd12</anchor>
      <arglist>(unsigned int n=1)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>nb_unbound</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>afb083196c8e73a8619350d90258ed3f9</anchor>
      <arglist>(unsigned int n=16)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>nb_reduce</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a85e57b2c19e152f85d51a627a6a9cea6</anchor>
      <arglist>(unsigned int n=1)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>nb_bound</name>
      <anchorfile>a00082.html</anchorfile>
      <anchor>a892f38b84dc3cac858225530e8798e9b</anchor>
      <arglist>(unsigned int n)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_blocking_master_if</name>
    <filename>a00064.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base virtualness="virtual">tlm_blocking_put_if&lt; REQ &gt;</base>
    <base virtualness="virtual">tlm_blocking_get_peek_if&lt; RSP &gt;</base>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_blocking_slave_if</name>
    <filename>a00067.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base virtualness="virtual">tlm_blocking_put_if&lt; RSP &gt;</base>
    <base virtualness="virtual">tlm_blocking_get_peek_if&lt; REQ &gt;</base>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_nonblocking_master_if</name>
    <filename>a00100.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base virtualness="virtual">tlm_nonblocking_put_if&lt; REQ &gt;</base>
    <base virtualness="virtual">tlm_nonblocking_get_peek_if&lt; RSP &gt;</base>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_nonblocking_slave_if</name>
    <filename>a00105.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base virtualness="virtual">tlm_nonblocking_put_if&lt; RSP &gt;</base>
    <base virtualness="virtual">tlm_nonblocking_get_peek_if&lt; REQ &gt;</base>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_master_if</name>
    <filename>a00094.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base virtualness="virtual">tlm_put_if&lt; REQ &gt;</base>
    <base virtualness="virtual">tlm_get_peek_if&lt; RSP &gt;</base>
    <base virtualness="virtual">tlm::tlm_blocking_master_if</base>
    <base virtualness="virtual">tlm::tlm_nonblocking_master_if</base>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_slave_if</name>
    <filename>a00112.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base virtualness="virtual">tlm_put_if&lt; RSP &gt;</base>
    <base virtualness="virtual">tlm_get_peek_if&lt; REQ &gt;</base>
    <base virtualness="virtual">tlm::tlm_blocking_slave_if</base>
    <base virtualness="virtual">tlm::tlm_nonblocking_slave_if</base>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_tag</name>
    <filename>a00115.html</filename>
    <templarg></templarg>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_transport_to_master</name>
    <filename>a00120.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base virtualness="virtual">tlm::tlm_transport_if</base>
    <member kind="function">
      <type></type>
      <name>tlm_transport_to_master</name>
      <anchorfile>a00120.html</anchorfile>
      <anchor>adc5926eda52414eaf58d105fd0e2dcd9</anchor>
      <arglist>(sc_core::sc_module_name nm)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_transport_to_master</name>
      <anchorfile>a00120.html</anchorfile>
      <anchor>adddc070bf33e3f2b467f24247b27971c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>RSP</type>
      <name>transport</name>
      <anchorfile>a00120.html</anchorfile>
      <anchor>aa31c475ce235dfabfa9e0b68ea154295</anchor>
      <arglist>(const REQ &amp;req)</arglist>
    </member>
    <member kind="variable">
      <type>sc_core::sc_export&lt; tlm_transport_if&lt; REQ, RSP &gt; &gt;</type>
      <name>target_export</name>
      <anchorfile>a00120.html</anchorfile>
      <anchor>aaac19d0224d56a4f2c9e2d8d1dea57e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sc_core::sc_port&lt; tlm_master_if&lt; REQ, RSP &gt; &gt;</type>
      <name>master_port</name>
      <anchorfile>a00120.html</anchorfile>
      <anchor>a23a5999f9ee712d3b247a81f9a70f240</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_slave_to_transport</name>
    <filename>a00114.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>SC_HAS_PROCESS</name>
      <anchorfile>a00114.html</anchorfile>
      <anchor>a0dfc8ef1f480e9f7bb0688f6a0e88b5a</anchor>
      <arglist>(tlm_slave_to_transport)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_slave_to_transport</name>
      <anchorfile>a00114.html</anchorfile>
      <anchor>a68783b29e2cb2178aa2ae0d44b6f16c8</anchor>
      <arglist>(sc_core::sc_module_name nm)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_slave_to_transport</name>
      <anchorfile>a00114.html</anchorfile>
      <anchor>af90ed795dbb355691a0cae7dc76ca60e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>sc_core::sc_port&lt; tlm_slave_if&lt; REQ, RSP &gt; &gt;</type>
      <name>slave_port</name>
      <anchorfile>a00114.html</anchorfile>
      <anchor>a23197c58d2d0c3592bd98a9e248d5245</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sc_core::sc_port&lt; tlm_transport_if&lt; REQ, RSP &gt; &gt;</type>
      <name>initiator_port</name>
      <anchorfile>a00114.html</anchorfile>
      <anchor>a2547a445e870a1b4dfe6ccabfc3b9613</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::circular_buffer</name>
    <filename>a00003.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>circular_buffer</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>ae1af1741ab5d7d50e081f1609bac07cb</anchor>
      <arglist>(int size=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~circular_buffer</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>a8d98c55929bafe0a2d4b630851e3eec2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>acfa261b17607c0b9c0295cb780047c8c</anchor>
      <arglist>(int size)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>ad5d77255a895f3f49464a3186d96d8b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>read</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>ae4f004ed263dd3ef619ab2e5df6a8af0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>write</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>a6f1b36ed6172a376e5850732e6274ca8</anchor>
      <arglist>(const T &amp;)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_empty</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>afdc4f3d002ba307a29a5c14dba2f7717</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_full</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>a3f90570c3a072c60668c821a824a10e8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>a87020999de4d20fb5ceb8e29ab79348b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>used</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>aa5d8e58517ef9f5ef0f173915e716821</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>free</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>a1d195c02736b4be497356227a00fa0e3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>read_data</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>acb6db27e7fbb4012c558e0ddb856921c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const T &amp;</type>
      <name>peek_data</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>a107fbb88e3eae0f27364eff5775ad374</anchor>
      <arglist>(int i) const </arglist>
    </member>
    <member kind="function">
      <type>T &amp;</type>
      <name>poke_data</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>aa693a3030d52c86487babdde8a1de41a</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>debug</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>abcac814dc408de7dd03dea237e031e6b</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_fifo</name>
    <filename>a00081.html</filename>
    <templarg></templarg>
    <base virtualness="virtual">tlm::tlm_fifo_get_if</base>
    <base virtualness="virtual">tlm::tlm_fifo_put_if</base>
    <member kind="function">
      <type></type>
      <name>tlm_fifo</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a9f1f90790e5d39ebf54745e5b88668b7</anchor>
      <arglist>(int size_=1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_fifo</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>aeddce65724b68157269992ee313b0024</anchor>
      <arglist>(const char *name_, int size_=1)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~tlm_fifo</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a6df572368f9de72b9c247c0a61d200c6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>get</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>adb00c2039a7299456ea986c266929dce</anchor>
      <arglist>(tlm_tag&lt; T &gt; *=0)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nb_get</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a114a4b71a75eb4d97b649c724be86bf4</anchor>
      <arglist>(T &amp;)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nb_can_get</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>aba28a238bab0ccc8b7ad404468621648</anchor>
      <arglist>(tlm_tag&lt; T &gt; *=0) const </arglist>
    </member>
    <member kind="function">
      <type>const sc_core::sc_event &amp;</type>
      <name>ok_to_get</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>acddf28b58fb3b5f54ea80d1835da373d</anchor>
      <arglist>(tlm_tag&lt; T &gt; *=0) const </arglist>
    </member>
    <member kind="function">
      <type>T</type>
      <name>peek</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a400f8ab0a9e5b93d243bcc2f0172385f</anchor>
      <arglist>(tlm_tag&lt; T &gt; *=0) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nb_peek</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a2bede967faf4bd56243e9ed68728bbb5</anchor>
      <arglist>(T &amp;) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nb_can_peek</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>adb64ff40304584f33fde221c004c105c</anchor>
      <arglist>(tlm_tag&lt; T &gt; *=0) const </arglist>
    </member>
    <member kind="function">
      <type>const sc_core::sc_event &amp;</type>
      <name>ok_to_peek</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a6f41d1bccae016767864c2dbea3a9b65</anchor>
      <arglist>(tlm_tag&lt; T &gt; *=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>put</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>af524acf04ccddc57681fff2ffbbdc49c</anchor>
      <arglist>(const T &amp;)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nb_put</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>acbc7ab6989faeb2316f2670358fed7d6</anchor>
      <arglist>(const T &amp;)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nb_can_put</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a951aa7c59bf0e98deff8641492c24ab9</anchor>
      <arglist>(tlm_tag&lt; T &gt; *=0) const </arglist>
    </member>
    <member kind="function">
      <type>const sc_core::sc_event &amp;</type>
      <name>ok_to_put</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a32b11964984c01d943a0163883f479e2</anchor>
      <arglist>(tlm_tag&lt; T &gt; *=0) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>nb_expand</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>add714fa3d116f7f4533358c94cfe5fab</anchor>
      <arglist>(unsigned int n=1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>nb_unbound</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a56debf3cf19c009b4fd4e4b33a4b96c9</anchor>
      <arglist>(unsigned int n=16)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nb_reduce</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a62ccdbae129fedca3822ed350b6cb8ce</anchor>
      <arglist>(unsigned int n=1)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nb_bound</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>aa286baba14fbad08df582abc1a211933</anchor>
      <arglist>(unsigned int n)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nb_peek</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a4e7aa62cc569ccc4a22184e195ee23f9</anchor>
      <arglist>(T &amp;, int n) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nb_poke</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>abdfffea8717fcdcafdb70bfbcfde9e4d</anchor>
      <arglist>(const T &amp;, int n=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>used</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a58f693070c319f06d7499cb7f34d2211</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a884ed93b9b09408c56fb37cfb5f2d33b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>debug</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a4724e105a6f6466cc9e749f1d9c4d8cb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>kind</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a4832b2f971a1adffe070b12e831f52db</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>kind_string</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>ae17b27ca3b552ad49e21ae7a60f7eb4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>sc_core::sc_event &amp;</type>
      <name>read_event</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>ae726b6843fca72ef9f0124f4bb378428</anchor>
      <arglist>(tlm_tag&lt; T &gt; *=0)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>update</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>aa8d74507db85547f0dd42ecbd9f8b12a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>init</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a3914f70c34b0007876f479326fcce956</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>circular_buffer&lt; T &gt;</type>
      <name>buffer</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>ad1d0b83ec45e9811e60c206df07157cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>m_size</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a96dd743bdafbaf2d5a7ef87bf683ce90</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>m_num_readable</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a0202596f1f911706eae62908183e39af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>m_num_read</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a5016c573b38fba7dbb071c2da86fc5eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>m_num_written</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>aab3e02f39644cb13d896c5b7f3ff3813</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>m_expand</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>ad7835b44b2a9e739464338642adacd27</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>m_num_read_no_notify</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a1a9ff5d9e33d2a8a98e08b04c03efa11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>sc_core::sc_event</type>
      <name>m_data_read_event</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>ab13c072b57cb34837abbcd2e032d617e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>sc_core::sc_event</type>
      <name>m_data_written_event</name>
      <anchorfile>a00081.html</anchorfile>
      <anchor>a770f13b5bd95a37e44c8dea1f284704f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_put_get_imp</name>
    <filename>a00108.html</filename>
    <templarg>PUT_DATA</templarg>
    <templarg>GET_DATA</templarg>
    <base virtualness="virtual">tlm_put_if&lt; PUT_DATA &gt;</base>
    <base virtualness="virtual">tlm_get_peek_if&lt; GET_DATA &gt;</base>
    <member kind="function">
      <type></type>
      <name>tlm_put_get_imp</name>
      <anchorfile>a00108.html</anchorfile>
      <anchor>aae145d1e327375feba7c0ff5f59152b8</anchor>
      <arglist>(tlm_put_if&lt; PUT_DATA &gt; &amp;p, tlm_get_peek_if&lt; GET_DATA &gt; &amp;g)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>put</name>
      <anchorfile>a00108.html</anchorfile>
      <anchor>a5fe89c7841501adff3d0677c0f0cb581</anchor>
      <arglist>(const PUT_DATA &amp;t)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nb_put</name>
      <anchorfile>a00108.html</anchorfile>
      <anchor>a89e548a662fe794fbd5b8ddbb5b635c4</anchor>
      <arglist>(const PUT_DATA &amp;t)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nb_can_put</name>
      <anchorfile>a00108.html</anchorfile>
      <anchor>ad70ee74b3e929955e96a91bd99b8b4e7</anchor>
      <arglist>(tlm_tag&lt; PUT_DATA &gt; *t=0) const </arglist>
    </member>
    <member kind="function">
      <type>const sc_core::sc_event &amp;</type>
      <name>ok_to_put</name>
      <anchorfile>a00108.html</anchorfile>
      <anchor>af21f6a461193714c8fe52e028420aab8</anchor>
      <arglist>(tlm_tag&lt; PUT_DATA &gt; *t=0) const </arglist>
    </member>
    <member kind="function">
      <type>GET_DATA</type>
      <name>get</name>
      <anchorfile>a00108.html</anchorfile>
      <anchor>a2ac73dfa35371fee66993954426b559c</anchor>
      <arglist>(tlm_tag&lt; GET_DATA &gt; *=0)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nb_get</name>
      <anchorfile>a00108.html</anchorfile>
      <anchor>a647ee735407f4193e2a07cd57e136748</anchor>
      <arglist>(GET_DATA &amp;t)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nb_can_get</name>
      <anchorfile>a00108.html</anchorfile>
      <anchor>a31b7c8dccf850c8ba624f6cba9c129d4</anchor>
      <arglist>(tlm_tag&lt; GET_DATA &gt; *t=0) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const sc_core::sc_event &amp;</type>
      <name>ok_to_get</name>
      <anchorfile>a00108.html</anchorfile>
      <anchor>ada356ec341c8bf528f17aeaddc647300</anchor>
      <arglist>(tlm_tag&lt; GET_DATA &gt; *t=0) const </arglist>
    </member>
    <member kind="function">
      <type>GET_DATA</type>
      <name>peek</name>
      <anchorfile>a00108.html</anchorfile>
      <anchor>aeeca43ef5ceffe08264af2ef6350ec15</anchor>
      <arglist>(tlm_tag&lt; GET_DATA &gt; *=0) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nb_peek</name>
      <anchorfile>a00108.html</anchorfile>
      <anchor>a4ea7c29e92cb29387829a8873b9f05d3</anchor>
      <arglist>(GET_DATA &amp;t) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>nb_can_peek</name>
      <anchorfile>a00108.html</anchorfile>
      <anchor>ae8742043423f5e3afb3a291fe0be63a0</anchor>
      <arglist>(tlm_tag&lt; GET_DATA &gt; *t=0) const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const sc_core::sc_event &amp;</type>
      <name>ok_to_peek</name>
      <anchorfile>a00108.html</anchorfile>
      <anchor>ac90d95cd3a8e1fb0f60f1155bbb93e49</anchor>
      <arglist>(tlm_tag&lt; GET_DATA &gt; *t=0) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_master_imp</name>
    <filename>a00095.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base protection="private">tlm_put_get_imp&lt; REQ, RSP &gt;</base>
    <base virtualness="virtual">tlm::tlm_master_if</base>
    <member kind="function">
      <type></type>
      <name>tlm_master_imp</name>
      <anchorfile>a00095.html</anchorfile>
      <anchor>a5f75dcc19d3362f4555b003f1e060336</anchor>
      <arglist>(tlm_put_if&lt; REQ &gt; &amp;req, tlm_get_peek_if&lt; RSP &gt; &amp;rsp)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_slave_imp</name>
    <filename>a00113.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <base protection="private">tlm_put_get_imp&lt; RSP, REQ &gt;</base>
    <base virtualness="virtual">tlm::tlm_slave_if</base>
    <member kind="function">
      <type></type>
      <name>tlm_slave_imp</name>
      <anchorfile>a00113.html</anchorfile>
      <anchor>a7e0602bf0398af9002ba53acda3a2fdb</anchor>
      <arglist>(tlm_get_peek_if&lt; REQ &gt; &amp;req, tlm_put_if&lt; RSP &gt; &amp;rsp)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_req_rsp_channel</name>
    <filename>a00111.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>tlm_req_rsp_channel</name>
      <anchorfile>a00111.html</anchorfile>
      <anchor>ab2a15b8268a793cfd1d6f79b31a79420</anchor>
      <arglist>(int req_size=1, int rsp_size=1)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_req_rsp_channel</name>
      <anchorfile>a00111.html</anchorfile>
      <anchor>ae55fd504c6f3563342ea3f8e42584ed5</anchor>
      <arglist>(sc_core::sc_module_name module_name, int req_size=1, int rsp_size=1)</arglist>
    </member>
    <member kind="variable">
      <type>sc_core::sc_export&lt; tlm_fifo_get_if&lt; REQ &gt; &gt;</type>
      <name>get_request_export</name>
      <anchorfile>a00111.html</anchorfile>
      <anchor>a35f17204cfafafd71974e764fd692fd7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sc_core::sc_export&lt; tlm_fifo_put_if&lt; RSP &gt; &gt;</type>
      <name>put_response_export</name>
      <anchorfile>a00111.html</anchorfile>
      <anchor>a5cabc07888ec62140c1165b9af6785e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sc_core::sc_export&lt; tlm_fifo_put_if&lt; REQ &gt; &gt;</type>
      <name>put_request_export</name>
      <anchorfile>a00111.html</anchorfile>
      <anchor>a1b26cee80c9c84db30ee940e2a44e1fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sc_core::sc_export&lt; tlm_fifo_get_if&lt; RSP &gt; &gt;</type>
      <name>get_response_export</name>
      <anchorfile>a00111.html</anchorfile>
      <anchor>aa6983daa5761fc2c96887387c87f4f00</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sc_core::sc_export&lt; tlm_master_if&lt; REQ, RSP &gt; &gt;</type>
      <name>master_export</name>
      <anchorfile>a00111.html</anchorfile>
      <anchor>ad5f6570bcfd15029354f906e47e80fe8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sc_core::sc_export&lt; tlm_slave_if&lt; REQ, RSP &gt; &gt;</type>
      <name>slave_export</name>
      <anchorfile>a00111.html</anchorfile>
      <anchor>aaa735e2868c9598de7329b0b9848c73b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>REQ_CHANNEL</type>
      <name>request_fifo</name>
      <anchorfile>a00111.html</anchorfile>
      <anchor>ac6e1012ffb102a481ec96716268565d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>RSP_CHANNEL</type>
      <name>response_fifo</name>
      <anchorfile>a00111.html</anchorfile>
      <anchor>a5ca53cf260d86a5cad95949c5b4cf2a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>tlm_master_imp&lt; REQ, RSP &gt;</type>
      <name>master</name>
      <anchorfile>a00111.html</anchorfile>
      <anchor>a6808a9dd3a33365cd5f64171271ee32b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>tlm_slave_imp&lt; REQ, RSP &gt;</type>
      <name>slave</name>
      <anchorfile>a00111.html</anchorfile>
      <anchor>afec042ba954aefe40b0112c42e3c329c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_transport_channel</name>
    <filename>a00117.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>tlm_transport_channel</name>
      <anchorfile>a00117.html</anchorfile>
      <anchor>a8bbdc3dbf67fcf3913e8c6cb0abcbdf6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_transport_channel</name>
      <anchorfile>a00117.html</anchorfile>
      <anchor>a06c06dfb3de5f873a36082d003eb310e</anchor>
      <arglist>(sc_core::sc_module_name nm)</arglist>
    </member>
    <member kind="variable">
      <type>sc_core::sc_export&lt; tlm_transport_if&lt; REQ, RSP &gt; &gt;</type>
      <name>target_export</name>
      <anchorfile>a00117.html</anchorfile>
      <anchor>ac1f4ed4af32df95c0ed2b868c3bcba04</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sc_core::sc_export&lt; tlm_fifo_get_if&lt; REQ &gt; &gt;</type>
      <name>get_request_export</name>
      <anchorfile>a00117.html</anchorfile>
      <anchor>a4ff244014142d6d4dfbf53ab4ae8f3d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sc_core::sc_export&lt; tlm_fifo_put_if&lt; RSP &gt; &gt;</type>
      <name>put_response_export</name>
      <anchorfile>a00117.html</anchorfile>
      <anchor>ad49a179e1d266c483a2a3168923210f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sc_core::sc_export&lt; tlm_slave_if&lt; REQ, RSP &gt; &gt;</type>
      <name>slave_export</name>
      <anchorfile>a00117.html</anchorfile>
      <anchor>a7cdd67bc3b613b4996d39be0c6c894c8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_event_finder_t</name>
    <filename>a00078.html</filename>
    <templarg>IF</templarg>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>tlm_event_finder_t</name>
      <anchorfile>a00078.html</anchorfile>
      <anchor>a5a8193aa99243b1ab98579d88e16333f</anchor>
      <arglist>(const sc_core::sc_port_base &amp;port_, const sc_core::sc_event &amp;(IF::*event_method_)(tlm_tag&lt; T &gt; *) const )</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~tlm_event_finder_t</name>
      <anchorfile>a00078.html</anchorfile>
      <anchor>ab408a87a34d4e6ae5c3b9d5cca704054</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const sc_core::sc_event &amp;</type>
      <name>find_event</name>
      <anchorfile>a00078.html</anchorfile>
      <anchor>a9c32823472448f34f764924cffa11f0d</anchor>
      <arglist>(sc_core::sc_interface *if_p=0) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_nonblocking_get_port</name>
    <filename>a00099.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>tlm_nonblocking_get_if&lt; T &gt;</type>
      <name>get_if_type</name>
      <anchorfile>a00099.html</anchorfile>
      <anchor>afe26505553762e20d253dfae1806a1b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_nonblocking_get_port</name>
      <anchorfile>a00099.html</anchorfile>
      <anchor>ae49d8554efefa1fc207081cc6d38ca12</anchor>
      <arglist>(const char *port_name)</arglist>
    </member>
    <member kind="function">
      <type>sc_core::sc_event_finder &amp;</type>
      <name>ok_to_get</name>
      <anchorfile>a00099.html</anchorfile>
      <anchor>a66530a1ab15409cb70ffd9dd826045ca</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_nonblocking_peek_port</name>
    <filename>a00102.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>tlm_nonblocking_peek_if&lt; T &gt;</type>
      <name>peek_if_type</name>
      <anchorfile>a00102.html</anchorfile>
      <anchor>a2d714c546d1d8db0b882fe5e76ddfa74</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_nonblocking_peek_port</name>
      <anchorfile>a00102.html</anchorfile>
      <anchor>a9a6844405c2d766d0848201d4ddeee9a</anchor>
      <arglist>(const char *port_name)</arglist>
    </member>
    <member kind="function">
      <type>sc_core::sc_event_finder &amp;</type>
      <name>ok_to_peek</name>
      <anchorfile>a00102.html</anchorfile>
      <anchor>af4b6d63c1c653f42034e7814ebd1658c</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_nonblocking_put_port</name>
    <filename>a00104.html</filename>
    <templarg></templarg>
    <member kind="typedef">
      <type>tlm_nonblocking_put_if&lt; T &gt;</type>
      <name>put_if_type</name>
      <anchorfile>a00104.html</anchorfile>
      <anchor>add17773dc38639db09d88ef0c871b0a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_nonblocking_put_port</name>
      <anchorfile>a00104.html</anchorfile>
      <anchor>a3350559710f974de36a2b9c8e0acdd21</anchor>
      <arglist>(const char *port_name)</arglist>
    </member>
    <member kind="function">
      <type>sc_core::sc_event_finder &amp;</type>
      <name>ok_to_put</name>
      <anchorfile>a00104.html</anchorfile>
      <anchor>a57115959eab98471d637aade1be8c0a7</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_dmi</name>
    <filename>a00075.html</filename>
    <member kind="enumeration">
      <name>dmi_access_e</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>a8fc92dc8c771f97369d6a12a13e8c1a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DMI_ACCESS_NONE</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>a8fc92dc8c771f97369d6a12a13e8c1a8a1a282b2058b3b43646a020de91913306</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DMI_ACCESS_READ</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>a8fc92dc8c771f97369d6a12a13e8c1a8ae37e04a9732cb484e65f03b4ce7b70ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DMI_ACCESS_WRITE</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>a8fc92dc8c771f97369d6a12a13e8c1a8a0c27d136e87e70b3d765ec83f34cb1bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DMI_ACCESS_READ_WRITE</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>a8fc92dc8c771f97369d6a12a13e8c1a8abe5d42f1c4ab9c8c9be6b5af1009a373</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_dmi</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>a51f02afce1495f9ea53c700e8a654cff</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>a1ae6d9f5a4218be540b95c13519189c8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>unsigned char *</type>
      <name>get_dmi_ptr</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>ad7e2d6a99d3d24221938ff7003e715fb</anchor>
      <arglist>(void) const </arglist>
    </member>
    <member kind="function">
      <type>sc_dt::uint64</type>
      <name>get_start_address</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>ab8d80541d4dad141aec0ca1ac23a0995</anchor>
      <arglist>(void) const </arglist>
    </member>
    <member kind="function">
      <type>sc_dt::uint64</type>
      <name>get_end_address</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>a72b1949ae03c106a8bcd351685d2973a</anchor>
      <arglist>(void) const </arglist>
    </member>
    <member kind="function">
      <type>sc_core::sc_time</type>
      <name>get_read_latency</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>a61a3bd8b54445bf6ed7af65632ed1914</anchor>
      <arglist>(void) const </arglist>
    </member>
    <member kind="function">
      <type>sc_core::sc_time</type>
      <name>get_write_latency</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>aa4b305a3b07cfb34cf61da5dfb576671</anchor>
      <arglist>(void) const </arglist>
    </member>
    <member kind="function">
      <type>dmi_access_e</type>
      <name>get_granted_access</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>a52b97b215e11d066e70ec91c0fcaa4c0</anchor>
      <arglist>(void) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_none_allowed</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>a334c74a79709c8b9f41eeae35bf0ae83</anchor>
      <arglist>(void) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_read_allowed</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>ac07cc53cb261f40e2b925f588a47f775</anchor>
      <arglist>(void) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_write_allowed</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>a18f7d5c847ec3e25adad444e417cffc7</anchor>
      <arglist>(void) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_read_write_allowed</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>a90635f60fdcfa4181da851135fa11d18</anchor>
      <arglist>(void) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_dmi_ptr</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>ab6a4f4d1651adaa1ecd34f9a323ed88b</anchor>
      <arglist>(unsigned char *p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_start_address</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>ade04e8aa0b5d239cac70d015ee05d3a2</anchor>
      <arglist>(sc_dt::uint64 addr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_end_address</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>af0cb3b46a1b291537734ade4521d1e81</anchor>
      <arglist>(sc_dt::uint64 addr)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_read_latency</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>afb8cff88a44137995b87bd817a6f5d20</anchor>
      <arglist>(sc_core::sc_time t)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_write_latency</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>a9ef94262d531b558cd228a3a8d994572</anchor>
      <arglist>(sc_core::sc_time t)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_granted_access</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>a20c6b24588c7e37cc3791cb1bda91fae</anchor>
      <arglist>(dmi_access_e a)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>allow_none</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>a2762bf2e1fe57edc0560f3a9b12020f0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>allow_read</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>aa06b17d31336935256ff4bcf069e4397</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>allow_write</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>aeb2c251526983084e48190a6951ef7cb</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>allow_read_write</name>
      <anchorfile>a00075.html</anchorfile>
      <anchor>a4a48dd5d8f1fcd9b4ec14e2cdfaddad8</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_fw_nonblocking_transport_if</name>
    <filename>a00087.html</filename>
    <templarg>TRANS</templarg>
    <templarg>PHASE</templarg>
    <member kind="function" virtualness="pure">
      <type>virtual tlm_sync_enum</type>
      <name>nb_transport_fw</name>
      <anchorfile>a00087.html</anchorfile>
      <anchor>a542b68459126ea6c9431174df4f97d14</anchor>
      <arglist>(TRANS &amp;trans, PHASE &amp;phase, sc_core::sc_time &amp;t)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_bw_nonblocking_transport_if</name>
    <filename>a00071.html</filename>
    <templarg>TRANS</templarg>
    <templarg>PHASE</templarg>
    <member kind="function" virtualness="pure">
      <type>virtual tlm_sync_enum</type>
      <name>nb_transport_bw</name>
      <anchorfile>a00071.html</anchorfile>
      <anchor>a3ec41ec9ff402632fae2d9a2c7f91022</anchor>
      <arglist>(TRANS &amp;trans, PHASE &amp;phase, sc_core::sc_time &amp;t)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_blocking_transport_if</name>
    <filename>a00068.html</filename>
    <templarg>TRANS</templarg>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>b_transport</name>
      <anchorfile>a00068.html</anchorfile>
      <anchor>a0d86fcef8ec8629e8325af784e34702f</anchor>
      <arglist>(TRANS &amp;trans, sc_core::sc_time &amp;t)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_fw_direct_mem_if</name>
    <filename>a00086.html</filename>
    <templarg>TRANS</templarg>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>get_direct_mem_ptr</name>
      <anchorfile>a00086.html</anchorfile>
      <anchor>ad6a97ca72a1d8a5c7306f56fb3272812</anchor>
      <arglist>(TRANS &amp;trans, tlm_dmi &amp;dmi_data)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_bw_direct_mem_if</name>
    <filename>a00070.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>invalidate_direct_mem_ptr</name>
      <anchorfile>a00070.html</anchorfile>
      <anchor>aaa1efc3defd487dc4be30e29dad7c5eb</anchor>
      <arglist>(sc_dt::uint64 start_range, sc_dt::uint64 end_range)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_transport_dbg_if</name>
    <filename>a00118.html</filename>
    <templarg>TRANS</templarg>
    <member kind="function" virtualness="pure">
      <type>virtual unsigned int</type>
      <name>transport_dbg</name>
      <anchorfile>a00118.html</anchorfile>
      <anchor>a52237c74db249fb83ebe6d34c0edb768</anchor>
      <arglist>(TRANS &amp;trans)=0</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>tlm::tlm_base_protocol_types</name>
    <filename>a00058.html</filename>
    <member kind="typedef">
      <type>tlm_generic_payload</type>
      <name>tlm_payload_type</name>
      <anchorfile>a00058.html</anchorfile>
      <anchor>adfbab7801136feef68a492b3a34952ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm_phase</type>
      <name>tlm_phase_type</name>
      <anchorfile>a00058.html</anchorfile>
      <anchor>a792bfa6063c683b4a5ad9335df0ff1be</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_fw_transport_if</name>
    <filename>a00088.html</filename>
    <templarg>TYPES</templarg>
    <base virtualness="virtual">tlm_fw_nonblocking_transport_if&lt; TYPES::tlm_payload_type, TYPES::tlm_phase_type &gt;</base>
    <base virtualness="virtual">tlm_blocking_transport_if&lt; TYPES::tlm_payload_type &gt;</base>
    <base virtualness="virtual">tlm_fw_direct_mem_if&lt; TYPES::tlm_payload_type &gt;</base>
    <base virtualness="virtual">tlm_transport_dbg_if&lt; TYPES::tlm_payload_type &gt;</base>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_bw_transport_if</name>
    <filename>a00072.html</filename>
    <templarg>TYPES</templarg>
    <base virtualness="virtual">tlm_bw_nonblocking_transport_if&lt; TYPES::tlm_payload_type, TYPES::tlm_phase_type &gt;</base>
    <base virtualness="virtual">tlm::tlm_bw_direct_mem_if</base>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_array</name>
    <filename>a00055.html</filename>
    <templarg>T</templarg>
    <member kind="function">
      <type></type>
      <name>tlm_array</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>a2f65ea225856ba501d14c7dc5c0070bb</anchor>
      <arglist>(size_type size=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>expand</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>a10bb5b3268013ba880d1ce1db597d062</anchor>
      <arglist>(size_type new_size)</arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>kind</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>a9dacb1a2cf6018c020e80a39484fdc22</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>insert_in_cache</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>af6086cbb8fc05678d33be9a81cc5549c</anchor>
      <arglist>(T *p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>free_entire_cache</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>a725a0288e9a71edbb7e18e71447bdeb3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const char *const</type>
      <name>kind_string</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>acf327bcde14c83f87e603deace64ad48</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; size_type &gt;</type>
      <name>m_entries</name>
      <anchorfile>a00055.html</anchorfile>
      <anchor>ae5d62eb66eaf6a3500364c1bc20d2e93</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_endian_context_pool</name>
    <filename>a00077.html</filename>
    <member kind="function">
      <type></type>
      <name>tlm_endian_context_pool</name>
      <anchorfile>a00077.html</anchorfile>
      <anchor>a55547e739563478725d4a5a089147050</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~tlm_endian_context_pool</name>
      <anchorfile>a00077.html</anchorfile>
      <anchor>afb3b7b00dfcbb56ff7c16e4b8423cec7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>tlm_endian_context *</type>
      <name>pop</name>
      <anchorfile>a00077.html</anchorfile>
      <anchor>aa38c31e12f7ccc9a2610442de40074a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>push</name>
      <anchorfile>a00077.html</anchorfile>
      <anchor>a9fdbced80c0806f06b828ee8d8abbe4d</anchor>
      <arglist>(tlm_endian_context *c)</arglist>
    </member>
    <member kind="variable">
      <type>tlm_endian_context *</type>
      <name>first</name>
      <anchorfile>a00077.html</anchorfile>
      <anchor>a73dea6477d0aa6498f04c664432c5a76</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_endian_context</name>
    <filename>a00076.html</filename>
    <base>tlm_extension&lt; tlm_endian_context &gt;</base>
    <member kind="function">
      <type></type>
      <name>tlm_endian_context</name>
      <anchorfile>a00076.html</anchorfile>
      <anchor>a4e4d0854fd319afef702cfc3d92d4225</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~tlm_endian_context</name>
      <anchorfile>a00076.html</anchorfile>
      <anchor>a6647f750726e6c2ac5edabe569dde4bd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>establish_dbuf</name>
      <anchorfile>a00076.html</anchorfile>
      <anchor>ae667b8c79527e2ac2fe5355e1e5854d5</anchor>
      <arglist>(int len)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>establish_bebuf</name>
      <anchorfile>a00076.html</anchorfile>
      <anchor>ae291fca8f514174828d9d17b3adbe4ba</anchor>
      <arglist>(int len)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>free</name>
      <anchorfile>a00076.html</anchorfile>
      <anchor>a260582657c6ebcd9f650d5df38242c7b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>tlm_extension_base *</type>
      <name>clone</name>
      <anchorfile>a00076.html</anchorfile>
      <anchor>a9cbad660fb75aef9f1f8cacc7104175c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_from</name>
      <anchorfile>a00076.html</anchorfile>
      <anchor>a3ae93523f40ea5aa42e29992a4ef2ac0</anchor>
      <arglist>(tlm_extension_base const &amp;)</arglist>
    </member>
    <member kind="variable">
      <type>sc_dt::uint64</type>
      <name>address</name>
      <anchorfile>a00076.html</anchorfile>
      <anchor>a9bdc4824409e45580b25760be2270836</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sc_dt::uint64</type>
      <name>new_address</name>
      <anchorfile>a00076.html</anchorfile>
      <anchor>a4b592ed6192127e7f2df6c810bbf1499</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uchar *</type>
      <name>data_ptr</name>
      <anchorfile>a00076.html</anchorfile>
      <anchor>a73fa2084a54be6b76aabc6f36ecbf6d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uchar *</type>
      <name>byte_enable</name>
      <anchorfile>a00076.html</anchorfile>
      <anchor>ae4a357d465b80c6c6b049e48a736d34b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>length</name>
      <anchorfile>a00076.html</anchorfile>
      <anchor>acaa2d690d4f526cbf6b39575033d717e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>stream_width</name>
      <anchorfile>a00076.html</anchorfile>
      <anchor>ad43407778698362ee2f0b92b9b43394a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>void(*</type>
      <name>from_f</name>
      <anchorfile>a00076.html</anchorfile>
      <anchor>ad6c5b6fb7e74f050d115825408688dab</anchor>
      <arglist>)(tlm_generic_payload *txn, unsigned int sizeof_databus)</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>sizeof_databus</name>
      <anchorfile>a00076.html</anchorfile>
      <anchor>addd9342d542c433f48b7b19af829bb43</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uchar *</type>
      <name>new_dbuf</name>
      <anchorfile>a00076.html</anchorfile>
      <anchor>a881e78625efff381112316271f8c0baa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>uchar *</type>
      <name>new_bebuf</name>
      <anchorfile>a00076.html</anchorfile>
      <anchor>a32ee9f4cae59221799c53558e01aff04</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>dbuf_size</name>
      <anchorfile>a00076.html</anchorfile>
      <anchor>a8e7bccafad1987ed0053e00f9ec422fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>bebuf_size</name>
      <anchorfile>a00076.html</anchorfile>
      <anchor>ac78a65ded76e412bac9973765c6d7ae5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>tlm_endian_context *</type>
      <name>next</name>
      <anchorfile>a00076.html</anchorfile>
      <anchor>a4c0fdcaea2fff64e1eeb8b3650bc8686</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_bool</name>
    <filename>a00069.html</filename>
    <templarg></templarg>
    <member kind="function">
      <type></type>
      <name>tlm_bool</name>
      <anchorfile>a00069.html</anchorfile>
      <anchor>a9824e7f98684f1894b3db42108be58ef</anchor>
      <arglist>(D &amp;d)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator bool</name>
      <anchorfile>a00069.html</anchorfile>
      <anchor>ac2c0edb8930df836dd5dc6803b571629</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static D</type>
      <name>make_uchar_array</name>
      <anchorfile>a00069.html</anchorfile>
      <anchor>a09a7ec73e84adb2c54878081e61e3799</anchor>
      <arglist>(uchar c)</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static D</type>
      <name>TLM_TRUE</name>
      <anchorfile>a00069.html</anchorfile>
      <anchor>a4d94e18943c3348ffc1a63d42dc7c05f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static D</type>
      <name>TLM_FALSE</name>
      <anchorfile>a00069.html</anchorfile>
      <anchor>a05e9260a8b590567d128501634a3c1f9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_mm_interface</name>
    <filename>a00096.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>free</name>
      <anchorfile>a00096.html</anchorfile>
      <anchor>a428e4d36bf979e7245b92597f0abbe56</anchor>
      <arglist>(tlm_generic_payload *)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~tlm_mm_interface</name>
      <anchorfile>a00096.html</anchorfile>
      <anchor>a8e908ba522d1e0c5ee375d129ba3de2d</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_extension_base</name>
    <filename>a00080.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual tlm_extension_base *</type>
      <name>clone</name>
      <anchorfile>a00080.html</anchorfile>
      <anchor>a2520d325fc19d3e1f6b867a8e76b0190</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>free</name>
      <anchorfile>a00080.html</anchorfile>
      <anchor>a114d964084785b50ce46306a87b81782</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>copy_from</name>
      <anchorfile>a00080.html</anchorfile>
      <anchor>ab164336798296e05d42baed18c3c0247</anchor>
      <arglist>(tlm_extension_base const &amp;)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~tlm_extension_base</name>
      <anchorfile>a00080.html</anchorfile>
      <anchor>ac515a916d517f888efe998b1a99f544b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static unsigned int</type>
      <name>register_extension</name>
      <anchorfile>a00080.html</anchorfile>
      <anchor>a0eedefafea27670b9732e7e71650ef41</anchor>
      <arglist>(const std::type_info &amp;)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_extension</name>
    <filename>a00079.html</filename>
    <templarg>T</templarg>
    <base>tlm::tlm_extension_base</base>
    <member kind="function" virtualness="pure">
      <type>virtual tlm_extension_base *</type>
      <name>clone</name>
      <anchorfile>a00079.html</anchorfile>
      <anchor>ac2eebc4a5fb60df5858592e9e1eadc7b</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>copy_from</name>
      <anchorfile>a00079.html</anchorfile>
      <anchor>ab3590e6a34dbfdbe1cdb9d3f9ad84427</anchor>
      <arglist>(tlm_extension_base const &amp;ext)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~tlm_extension</name>
      <anchorfile>a00079.html</anchorfile>
      <anchor>aa4161685295f1601d56a52776f7e0479</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const unsigned int</type>
      <name>ID</name>
      <anchorfile>a00079.html</anchorfile>
      <anchor>a27a8873f67f62f39d219dbc962742d03</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_generic_payload</name>
    <filename>a00089.html</filename>
    <member kind="function">
      <type></type>
      <name>tlm_generic_payload</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a6ba51f19440df501fabdb272a288b963</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_generic_payload</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>af1a022728ee53310794b1027d775fe43</anchor>
      <arglist>(tlm_mm_interface *mm)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>acquire</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a11f9bc5052c56b14846c136fb0e05ba7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a22e521dd2c5be0c917cb78fee1cf3174</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>get_ref_count</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>aa735dbdbf22e2935a82e992f89483283</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_mm</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>af6e4413d6bd7b4ff64ca27678c269499</anchor>
      <arglist>(tlm_mm_interface *mm)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>has_mm</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a79c68321052dcc98bf04eb2caea592aa</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a8eead3858931d65ad05fb124eb9962a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>deep_copy_from</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a58ae353b4d294a3f8f8c35269257b8e2</anchor>
      <arglist>(const tlm_generic_payload &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_original_from</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a6f2e6ebfbab3d63f926412fee3690b72</anchor>
      <arglist>(const tlm_generic_payload &amp;other, bool use_byte_enable_on_read=true)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>update_extensions_from</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a032e1b228cae4d310ffe5cafee29d199</anchor>
      <arglist>(const tlm_generic_payload &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>free_all_extensions</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a4478dd704b60287fbc730c8379bfc0db</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~tlm_generic_payload</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a5e405fd525802950f609cca3948047ca</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_read</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>aa99b26718e52fd5a49ab8475b44b8dac</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_read</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>aebcb00d1cb95884df808c3f04352daea</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_write</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a234bd44edb3ccb706b7ba030c3a2200d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_write</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a9ceb3bbb4520aa8ae729f84af921ca54</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>tlm_command</type>
      <name>get_command</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a7298ffbdfdfff7b938d5d91ed27bb113</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_command</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a640f6263956a81078274d6a98b4d7f2c</anchor>
      <arglist>(const tlm_command command)</arglist>
    </member>
    <member kind="function">
      <type>sc_dt::uint64</type>
      <name>get_address</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a56d9cf62de27f45e93a45bf5c144c288</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_address</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a486d7746584d058f148f6b3d6aab55c4</anchor>
      <arglist>(const sc_dt::uint64 address)</arglist>
    </member>
    <member kind="function">
      <type>unsigned char *</type>
      <name>get_data_ptr</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a195859527e5438cd8260d28eef1eb076</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_data_ptr</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a03a1359e212624b834b64ac4b36a82ba</anchor>
      <arglist>(unsigned char *data)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>get_data_length</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>ae1e9ec21a8dddd5fbf612d41814f54d7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_data_length</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a8bb2743225851e7d2e8d5c3f0213f379</anchor>
      <arglist>(const unsigned int length)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_response_ok</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a41652466f8769266463a165694b7f431</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_response_error</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>ab53c75bd7726f782ca269b058296c7e0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>tlm_response_status</type>
      <name>get_response_status</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a76330603b91d20a74c04489f1d5b2c34</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_response_status</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a3650a2bc77452b084a508dd6f2b0b915</anchor>
      <arglist>(const tlm_response_status response_status)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>get_response_string</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>af5ee428aea1184ebd204e4905e8ae409</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>get_streaming_width</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a8cc2025a351f5fa8cf3e91a03a089a81</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_streaming_width</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>abdd0e57c84918a6a1796248e577979f7</anchor>
      <arglist>(const unsigned int streaming_width)</arglist>
    </member>
    <member kind="function">
      <type>unsigned char *</type>
      <name>get_byte_enable_ptr</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a38b031e6dcbb51db9f368b494c4ff091</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_byte_enable_ptr</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>aef1f7d2a2d743aaa304a85d361e880db</anchor>
      <arglist>(unsigned char *byte_enable)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>get_byte_enable_length</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a76711646a3572d111dc6d80769e55158</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_byte_enable_length</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a465e5b08194660aa0b66d4e8219fa887</anchor>
      <arglist>(const unsigned int byte_enable_length)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_dmi_allowed</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a266a41f46155a5e32deb4b5db7684cb0</anchor>
      <arglist>(bool dmi_allowed)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_dmi_allowed</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>acf9895cd80b70cab8df0ee45aaa8b23e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>tlm_gp_option</type>
      <name>get_gp_option</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a81166ab430ae99b9275758ad2b9f544a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_gp_option</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a0e54344a791d5a2d772bb937245adde5</anchor>
      <arglist>(const tlm_gp_option gp_opt)</arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>set_extension</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a736d6fe355b64be5280ba32386566163</anchor>
      <arglist>(T *ext)</arglist>
    </member>
    <member kind="function">
      <type>tlm_extension_base *</type>
      <name>set_extension</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>ae90bba1b5f8a6160403ccf7c5aec5bfc</anchor>
      <arglist>(unsigned int index, tlm_extension_base *ext)</arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>set_auto_extension</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a9a228eacd0c64c70fec8151a83d769d2</anchor>
      <arglist>(T *ext)</arglist>
    </member>
    <member kind="function">
      <type>tlm_extension_base *</type>
      <name>set_auto_extension</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>af68c9a8d713f747e6e6d318173043d58</anchor>
      <arglist>(unsigned int index, tlm_extension_base *ext)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_extension</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a57e1f088841057cd1c2717701c240396</anchor>
      <arglist>(T *&amp;ext) const </arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>get_extension</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>aad054bc0ffe0225a825a40c72f4eca68</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>tlm_extension_base *</type>
      <name>get_extension</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>aa29f2d47d3b301f066f047164a95dafa</anchor>
      <arglist>(unsigned int index) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear_extension</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>ae8de55a98f8fc20e3e5fcc8e4f3e53ef</anchor>
      <arglist>(const T *ext)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear_extension</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a6240676b4b2a44c0322128159d278a25</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release_extension</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>ab0db1f5a799acd556b3a484b889c94de</anchor>
      <arglist>(T *ext)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>release_extension</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a7e35d5324c428b9df2882cb78f1e627d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize_extensions</name>
      <anchorfile>a00089.html</anchorfile>
      <anchor>a0f66e9fc193d584ba8acbf6837549f41</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_phase</name>
    <filename>a00107.html</filename>
    <member kind="function">
      <type></type>
      <name>tlm_phase</name>
      <anchorfile>a00107.html</anchorfile>
      <anchor>a9ab40e490ae1d88862686c4346196bf9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_phase</name>
      <anchorfile>a00107.html</anchorfile>
      <anchor>a84aee3098ccfa0ab4e8bca0fff9c27de</anchor>
      <arglist>(unsigned int id)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_phase</name>
      <anchorfile>a00107.html</anchorfile>
      <anchor>aa29eccb310f240eccd95115de40c4818</anchor>
      <arglist>(tlm_phase_enum standard)</arglist>
    </member>
    <member kind="function">
      <type>tlm_phase &amp;</type>
      <name>operator=</name>
      <anchorfile>a00107.html</anchorfile>
      <anchor>afd445b7f4be1a0d1acb4efc5a90540fb</anchor>
      <arglist>(tlm_phase_enum standard)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator unsigned int</name>
      <anchorfile>a00107.html</anchorfile>
      <anchor>ae394822d5f8817969c6fe4b469d8861d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const char *</type>
      <name>get_name</name>
      <anchorfile>a00107.html</anchorfile>
      <anchor>a3f40de11b7a12454bbe0cb6edaec27d4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>tlm_phase</name>
      <anchorfile>a00107.html</anchorfile>
      <anchor>aeed4127a1e63ff047937d217edc1e6d0</anchor>
      <arglist>(const std::type_info &amp;type, const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_global_quantum</name>
    <filename>a00092.html</filename>
    <member kind="function">
      <type>void</type>
      <name>set</name>
      <anchorfile>a00092.html</anchorfile>
      <anchor>a277e4602b4f619930e98cc9d3c742b50</anchor>
      <arglist>(const sc_core::sc_time &amp;t)</arglist>
    </member>
    <member kind="function">
      <type>const sc_core::sc_time &amp;</type>
      <name>get</name>
      <anchorfile>a00092.html</anchorfile>
      <anchor>a313cff19f8cb0a39023700d3c29a85c9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>sc_core::sc_time</type>
      <name>compute_local_quantum</name>
      <anchorfile>a00092.html</anchorfile>
      <anchor>ad265a9c3d73da7bf40de2673c728f83b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static tlm_global_quantum &amp;</type>
      <name>instance</name>
      <anchorfile>a00092.html</anchorfile>
      <anchor>aceb79e73e431280a04046bc4a71e2ccf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>tlm_global_quantum</name>
      <anchorfile>a00092.html</anchorfile>
      <anchor>a74ac4a67a86670dcb2fb0809f0f93e0d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>sc_core::sc_time</type>
      <name>m_global_quantum</name>
      <anchorfile>a00092.html</anchorfile>
      <anchor>a0ee092f0e644c2b2a05ca3f8d56eb49c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_base_socket_if</name>
    <filename>a00059.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual sc_core::sc_port_base &amp;</type>
      <name>get_port_base</name>
      <anchorfile>a00059.html</anchorfile>
      <anchor>a585c7287399674f0c81a643f03317749</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual sc_core::sc_port_base const &amp;</type>
      <name>get_port_base</name>
      <anchorfile>a00059.html</anchorfile>
      <anchor>a9952429b1b6a65d1944ab114560fe0f6</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual sc_core::sc_export_base &amp;</type>
      <name>get_export_base</name>
      <anchorfile>a00059.html</anchorfile>
      <anchor>ac1a5d48dae8a0037a3cae98ea8ff5e6b</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual sc_core::sc_export_base const &amp;</type>
      <name>get_export_base</name>
      <anchorfile>a00059.html</anchorfile>
      <anchor>af84ef5b6baffc117ce204d47da213bf9</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual unsigned int</type>
      <name>get_bus_width</name>
      <anchorfile>a00059.html</anchorfile>
      <anchor>ab9948b826b7933f08fce0edfdc23ca32</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual sc_core::sc_type_index</type>
      <name>get_protocol_types</name>
      <anchorfile>a00059.html</anchorfile>
      <anchor>ab51465d195bd6350a6172088ebf7dd81</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual tlm_socket_category</type>
      <name>get_socket_category</name>
      <anchorfile>a00059.html</anchorfile>
      <anchor>a78dd755c5d2abe0e59217675daf01f33</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~tlm_base_socket_if</name>
      <anchorfile>a00059.html</anchorfile>
      <anchor>a019499978858e8bc60354bd79e98c241</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_base_initiator_socket_b</name>
    <filename>a00057.html</filename>
    <templarg>BUSWIDTH</templarg>
    <templarg>FW_IF</templarg>
    <templarg>BW_IF</templarg>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~tlm_base_initiator_socket_b</name>
      <anchorfile>a00057.html</anchorfile>
      <anchor>a3f086c968a861e9d1fd720af5035b884</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual sc_core::sc_port_b&lt; FW_IF &gt; &amp;</type>
      <name>get_base_port</name>
      <anchorfile>a00057.html</anchorfile>
      <anchor>a1da569dccb5ed23c57ec360f80ee2d46</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual sc_core::sc_port_b&lt; FW_IF &gt; const &amp;</type>
      <name>get_base_port</name>
      <anchorfile>a00057.html</anchorfile>
      <anchor>a52a6dedcc9a3b9f9f1a81bffaffc8166</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual BW_IF &amp;</type>
      <name>get_base_interface</name>
      <anchorfile>a00057.html</anchorfile>
      <anchor>a6d2fdfe9f8b2da2492b076535e11ee5d</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual BW_IF const &amp;</type>
      <name>get_base_interface</name>
      <anchorfile>a00057.html</anchorfile>
      <anchor>a5d84a37a0968abb7eb44e3ced18157be</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual sc_core::sc_export&lt; BW_IF &gt; &amp;</type>
      <name>get_base_export</name>
      <anchorfile>a00057.html</anchorfile>
      <anchor>a62ecf8dcd21b9010ab80e9872516eebb</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual sc_core::sc_export&lt; BW_IF &gt; const &amp;</type>
      <name>get_base_export</name>
      <anchorfile>a00057.html</anchorfile>
      <anchor>a6f1aa6bf7a138c889d290d22914e7185</anchor>
      <arglist>() const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_base_initiator_socket</name>
    <filename>a00056.html</filename>
    <templarg>BUSWIDTH</templarg>
    <templarg>FW_IF</templarg>
    <templarg>BW_IF</templarg>
    <templarg>N</templarg>
    <templarg>POL</templarg>
    <base>tlm::tlm_base_socket_if</base>
    <base>tlm::tlm_base_initiator_socket_b</base>
    <member kind="typedef">
      <type>FW_IF</type>
      <name>fw_interface_type</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>a6474507942dcb5372c356fc812ca47b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>BW_IF</type>
      <name>bw_interface_type</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>a12559e76a2f99426b4e4c2a44dc55de7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>sc_core::sc_port&lt; fw_interface_type, N, POL &gt;</type>
      <name>port_type</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>acf9ef10b4a7a9224a7042bc4c5986b4f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>sc_core::sc_export&lt; bw_interface_type &gt;</type>
      <name>export_type</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>a4bc50478a2d5e8ea597c8e677a10264b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm_base_target_socket_b&lt; BUSWIDTH, fw_interface_type, bw_interface_type &gt;</type>
      <name>base_target_socket_type</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>a56643a7f23e3dfc722b1e348665c5a4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm_base_initiator_socket_b&lt; BUSWIDTH, fw_interface_type, bw_interface_type &gt;</type>
      <name>base_type</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>a98f6a1c0b3c2e06e2e17e6bcedfc4e63</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_base_initiator_socket</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>ad10ee7bb5a44a6b956850dc22661f2ce</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_base_initiator_socket</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>a53fb74b5688565dfb839ee3a0ee736d5</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const char *</type>
      <name>kind</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>ab51c9b17cd30f1c630d62cb717b2e464</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>bind</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>a7aa095043daf871f96c5f144c09dfae9</anchor>
      <arglist>(base_target_socket_type &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>af3caac15b81f94ca3a5f366390a7f6ed</anchor>
      <arglist>(base_target_socket_type &amp;s)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>bind</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>a3b1c18649587ed2f9cf11e8917571463</anchor>
      <arglist>(base_type &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>ae21ae51eeb84626d8e7cf1d71845b745</anchor>
      <arglist>(base_type &amp;s)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>bind</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>a81b09f858ba7412225a740f79d9fde55</anchor>
      <arglist>(bw_interface_type &amp;ifs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>ad84eb3c4c4e43fa02002f987fdb55629</anchor>
      <arglist>(bw_interface_type &amp;s)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_port_base &amp;</type>
      <name>get_port_base</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>ac2a6315343086c57c25355161217549c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_port_base const &amp;</type>
      <name>get_port_base</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>af1c21d760daeba61603be176de65f2b3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_export_base &amp;</type>
      <name>get_export_base</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>a3310026a4b72be9aef2ca48c41559659</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_export_base const &amp;</type>
      <name>get_export_base</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>ac08cfa249add5a77cce1dd3b7659b5c2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual unsigned int</type>
      <name>get_bus_width</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>a310cf76917ca07cd4b696d1508d3c5a9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual tlm_socket_category</type>
      <name>get_socket_category</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>aa6a44181e21f8bf920fa6f5ecf9f0d79</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_port_b&lt; FW_IF &gt; &amp;</type>
      <name>get_base_port</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>ac6a9a2c69a25850b149716fec977b2d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_port_b&lt; FW_IF &gt; const &amp;</type>
      <name>get_base_port</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>a31061d8ce3cef770d2b5d80039879087</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual BW_IF &amp;</type>
      <name>get_base_interface</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>a1ed131229499ac21be962a359ac4690e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual BW_IF const &amp;</type>
      <name>get_base_interface</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>a98c019f6054496da68fd829ce3cc1961</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_export&lt; BW_IF &gt; &amp;</type>
      <name>get_base_export</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>a1d5c7fa9309909e0192c646953d2fac5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_export&lt; BW_IF &gt; const &amp;</type>
      <name>get_base_export</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>a7130d409ce258bcd7aae3a16c2dd183d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>export_type</type>
      <name>m_export</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>a9f37eba5d2e603d77bbb6725c63b0557</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend">
      <type>friend class</type>
      <name>tlm_base_target_socket</name>
      <anchorfile>a00056.html</anchorfile>
      <anchor>a4f721a5d0bf26beaf797beb70e448e0f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_initiator_socket</name>
    <filename>a00093.html</filename>
    <templarg>BUSWIDTH</templarg>
    <templarg>TYPES</templarg>
    <templarg>N</templarg>
    <templarg>POL</templarg>
    <base>tlm_base_initiator_socket&lt; BUSWIDTH, tlm_fw_transport_if&lt; TYPES &gt;, tlm_bw_transport_if&lt; TYPES &gt;, N, POL &gt;</base>
    <member kind="function">
      <type></type>
      <name>tlm_initiator_socket</name>
      <anchorfile>a00093.html</anchorfile>
      <anchor>aab0fc5a2d74e87d3575186b86b0e4fd8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_initiator_socket</name>
      <anchorfile>a00093.html</anchorfile>
      <anchor>ab1168490734c6cc771502b9842453b71</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const char *</type>
      <name>kind</name>
      <anchorfile>a00093.html</anchorfile>
      <anchor>a57bba1d335c7d2f2b17c83c912917161</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_type_index</type>
      <name>get_protocol_types</name>
      <anchorfile>a00093.html</anchorfile>
      <anchor>a38ba0ad3af4cd20606e099e99502d4d8</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_base_target_socket_b</name>
    <filename>a00061.html</filename>
    <templarg>BUSWIDTH</templarg>
    <templarg>FW_IF</templarg>
    <templarg>BW_IF</templarg>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~tlm_base_target_socket_b</name>
      <anchorfile>a00061.html</anchorfile>
      <anchor>a02917ae899a58c6700d0fb51168dae14</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual sc_core::sc_port_b&lt; BW_IF &gt; &amp;</type>
      <name>get_base_port</name>
      <anchorfile>a00061.html</anchorfile>
      <anchor>a73373ac177ef0c158622c575dcf2c782</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual sc_core::sc_export&lt; FW_IF &gt; &amp;</type>
      <name>get_base_export</name>
      <anchorfile>a00061.html</anchorfile>
      <anchor>a693df4a44dd045f31daabc70db5ab1a4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual FW_IF &amp;</type>
      <name>get_base_interface</name>
      <anchorfile>a00061.html</anchorfile>
      <anchor>adc77672578afc12ffe5ab2ee31fd40dc</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_base_target_socket</name>
    <filename>a00060.html</filename>
    <templarg>BUSWIDTH</templarg>
    <templarg>FW_IF</templarg>
    <templarg>BW_IF</templarg>
    <templarg>N</templarg>
    <templarg>POL</templarg>
    <base>tlm::tlm_base_socket_if</base>
    <base>tlm::tlm_base_target_socket_b</base>
    <member kind="typedef">
      <type>FW_IF</type>
      <name>fw_interface_type</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>af49a4a5ac25c04f2ea84962de25682fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>BW_IF</type>
      <name>bw_interface_type</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a504fea355fa7219564fd06d90e756b18</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>sc_core::sc_port&lt; bw_interface_type, N, POL &gt;</type>
      <name>port_type</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a420c4bc3488cc7409b767e128b433e83</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>sc_core::sc_export&lt; fw_interface_type &gt;</type>
      <name>export_type</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>af3087bc8df0a8b2b66378b27fd9d50d1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm_base_initiator_socket_b&lt; BUSWIDTH, fw_interface_type, bw_interface_type &gt;</type>
      <name>base_initiator_socket_type</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a434f354e12c8d834bda5bdc073ee5670</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm_base_target_socket_b&lt; BUSWIDTH, fw_interface_type, bw_interface_type &gt;</type>
      <name>base_type</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a891428398ec243ce05193e0e3b900929</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_base_target_socket</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a38702c2548199812729e3a8399236ce7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_base_target_socket</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a5e5f84a9200b440ad5debe00320ffe43</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const char *</type>
      <name>kind</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a14299e6342ffdf9ca489ec0db5f87a7b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>bind</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a35abc92f95f9468c5c624e2da2bb6898</anchor>
      <arglist>(base_initiator_socket_type &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a87d861ffc3f304764def237339db81ca</anchor>
      <arglist>(base_initiator_socket_type &amp;s)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>bind</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a5ff20a7c6bda002b5cb31a859cbfd1b8</anchor>
      <arglist>(base_type &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a8c06d6972d114167b40bf04012946a05</anchor>
      <arglist>(base_type &amp;s)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>bind</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>afadb3606b07edcc2569557167a750ce1</anchor>
      <arglist>(fw_interface_type &amp;ifs)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a1076e5285db8751c6cc092fc428e3acf</anchor>
      <arglist>(fw_interface_type &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>size</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a244fe416da5af500dd1616e1351847c0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bw_interface_type *</type>
      <name>operator-&gt;</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>ab5cd0be9b3dbab76ca9f0bb1fba45d07</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bw_interface_type *</type>
      <name>operator[]</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>aa6c6613e225f3b6bdc19ed6b98e60264</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_port_base &amp;</type>
      <name>get_port_base</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a2d24d1cb81af4420a268f10dddad30ad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_port_base const &amp;</type>
      <name>get_port_base</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a8d430de7356f09b4b20915cc59c55476</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_export_base &amp;</type>
      <name>get_export_base</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a55cc6bf6656e3f7339464bc8d666bb88</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_export_base const &amp;</type>
      <name>get_export_base</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>ab6fd69536ca870d12e34c9e7ff8fc993</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual unsigned int</type>
      <name>get_bus_width</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a4c29126b6886ec08a061666e46644288</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual tlm_socket_category</type>
      <name>get_socket_category</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a6a498ce74ccc5e15e27697e85ccee165</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_port_b&lt; BW_IF &gt; &amp;</type>
      <name>get_base_port</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a725b54330bd4f74139adc5f64666cc97</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_port_b&lt; BW_IF &gt; const &amp;</type>
      <name>get_base_port</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>aa41adc1121ff9e5f89250e45601755fd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual FW_IF &amp;</type>
      <name>get_base_interface</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a5dbd7dbeb4f7efec075c99da7e89964d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual FW_IF const &amp;</type>
      <name>get_base_interface</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a637aa2a0d92870e1148307f4e60f7332</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_export&lt; FW_IF &gt; &amp;</type>
      <name>get_base_export</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a83e96d7ae01d2904db725db377c21441</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_export&lt; FW_IF &gt; const &amp;</type>
      <name>get_base_export</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a109cfe5c29a90a1da64681a4132e2cbe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>port_type</type>
      <name>m_port</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a27bfe37ca7eb9d6e81a5a25e7ffa3fd6</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend">
      <type>friend class</type>
      <name>tlm_base_initiator_socket</name>
      <anchorfile>a00060.html</anchorfile>
      <anchor>a042bfd7a592d1f17872b75f528f958c2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm::tlm_target_socket</name>
    <filename>a00116.html</filename>
    <templarg>BUSWIDTH</templarg>
    <templarg>TYPES</templarg>
    <templarg>N</templarg>
    <templarg>POL</templarg>
    <base>tlm_base_target_socket&lt; BUSWIDTH, tlm_fw_transport_if&lt; TYPES &gt;, tlm_bw_transport_if&lt; TYPES &gt;, N, POL &gt;</base>
    <member kind="function">
      <type></type>
      <name>tlm_target_socket</name>
      <anchorfile>a00116.html</anchorfile>
      <anchor>a5dc9e401d556bf8bca1c41e204c55705</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tlm_target_socket</name>
      <anchorfile>a00116.html</anchorfile>
      <anchor>aa0c3f07b57f7c4fe8e48da276901446b</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const char *</type>
      <name>kind</name>
      <anchorfile>a00116.html</anchorfile>
      <anchor>a3b383a3102a5eb8f8c4449bd6ace6122</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_type_index</type>
      <name>get_protocol_types</name>
      <anchorfile>a00116.html</anchorfile>
      <anchor>af322fc9aa2a3fd7222ce3e2ad3661b28</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>tlm_utils</name>
    <filename>a00175.html</filename>
    <class kind="class">tlm_utils::convenience_socket_base</class>
    <class kind="class">tlm_utils::simple_socket_base</class>
    <class kind="class">tlm_utils::passthrough_socket_base</class>
    <class kind="class">tlm_utils::multi_socket_base</class>
    <class kind="class">tlm_utils::convenience_socket_cb_holder</class>
    <class kind="class">tlm_utils::instance_specific_extension</class>
    <class kind="class">tlm_utils::instance_specific_extension_carrier</class>
    <class kind="class">tlm_utils::ispex_base</class>
    <class kind="class">tlm_utils::instance_specific_extensions_per_accessor</class>
    <class kind="class">tlm_utils::instance_specific_extension_container</class>
    <class kind="class">tlm_utils::instance_specific_extension_accessor</class>
    <class kind="class">tlm_utils::multi_passthrough_initiator_socket</class>
    <class kind="class">tlm_utils::multi_passthrough_initiator_socket_optional</class>
    <class kind="class">tlm_utils::multi_passthrough_target_socket</class>
    <class kind="class">tlm_utils::multi_passthrough_target_socket_optional</class>
    <class kind="struct">tlm_utils::fn_container</class>
    <class kind="class">tlm_utils::callback_binder_fw</class>
    <class kind="class">tlm_utils::callback_binder_bw</class>
    <class kind="class">tlm_utils::multi_init_base_if</class>
    <class kind="class">tlm_utils::multi_init_base</class>
    <class kind="class">tlm_utils::multi_target_base_if</class>
    <class kind="class">tlm_utils::multi_target_base</class>
    <class kind="class">tlm_utils::multi_to_multi_bind_base</class>
    <class kind="class">tlm_utils::passthrough_target_socket_b</class>
    <class kind="class">tlm_utils::passthrough_target_socket</class>
    <class kind="class">tlm_utils::passthrough_target_socket_optional</class>
    <class kind="class">tlm_utils::passthrough_target_socket_tagged_b</class>
    <class kind="class">tlm_utils::passthrough_target_socket_tagged</class>
    <class kind="class">tlm_utils::passthrough_target_socket_tagged_optional</class>
    <class kind="class">tlm_utils::time_ordered_list</class>
    <class kind="class">tlm_utils::peq_with_cb_and_phase</class>
    <class kind="class">tlm_utils::peq_with_get</class>
    <class kind="class">tlm_utils::simple_initiator_socket_b</class>
    <class kind="class">tlm_utils::simple_initiator_socket</class>
    <class kind="class">tlm_utils::simple_initiator_socket_optional</class>
    <class kind="class">tlm_utils::simple_initiator_socket_tagged_b</class>
    <class kind="class">tlm_utils::simple_initiator_socket_tagged</class>
    <class kind="class">tlm_utils::simple_initiator_socket_tagged_optional</class>
    <class kind="class">tlm_utils::simple_target_socket_b</class>
    <class kind="class">tlm_utils::simple_target_socket</class>
    <class kind="class">tlm_utils::simple_target_socket_optional</class>
    <class kind="class">tlm_utils::simple_target_socket_tagged_b</class>
    <class kind="class">tlm_utils::simple_target_socket_tagged</class>
    <class kind="class">tlm_utils::simple_target_socket_tagged_optional</class>
    <class kind="class">tlm_utils::tlm_quantumkeeper</class>
    <member kind="function">
      <type></type>
      <name>TLM_DEFINE_FUNCTOR</name>
      <anchorfile>a00175.html</anchorfile>
      <anchor>a390fa8d71631e38513ee2e9e0299c142</anchor>
      <arglist>(nb_transport)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TLM_DEFINE_FUNCTOR</name>
      <anchorfile>a00175.html</anchorfile>
      <anchor>a1141b46d17cd12eeb5d6ee4405aaf93d</anchor>
      <arglist>(b_transport)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TLM_DEFINE_FUNCTOR</name>
      <anchorfile>a00175.html</anchorfile>
      <anchor>ab02f9ff09e04a61d6722ce374004ca0a</anchor>
      <arglist>(debug_transport)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TLM_DEFINE_FUNCTOR</name>
      <anchorfile>a00175.html</anchorfile>
      <anchor>a9986c74b8d35ee3fe221ef5bdcb69d0c</anchor>
      <arglist>(get_dmi_ptr)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>TLM_DEFINE_FUNCTOR</name>
      <anchorfile>a00175.html</anchorfile>
      <anchor>a29e24c8d62c4c6070fe7c6341f43e19c</anchor>
      <arglist>(invalidate_dmi)</arglist>
    </member>
    <member kind="variable">
      <type>class SC_API</type>
      <name>ispex_base</name>
      <anchorfile>a00175.html</anchorfile>
      <anchor>ae90aaec960512b93e703d6c70957c85c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>class SC_API</type>
      <name>instance_specific_extension_accessor</name>
      <anchorfile>a00175.html</anchorfile>
      <anchor>af4498a4ef1856bf8061af3e07c4322a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>class SC_API</type>
      <name>instance_specific_extension_container</name>
      <anchorfile>a00175.html</anchorfile>
      <anchor>ac056aaffdba5da92f9fe5b9f943bb3d9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::convenience_socket_base</name>
    <filename>a00004.html</filename>
    <member kind="function">
      <type>void</type>
      <name>display_warning</name>
      <anchorfile>a00004.html</anchorfile>
      <anchor>afa136ebc830378def302914d60ac7d09</anchor>
      <arglist>(const char *msg) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>display_error</name>
      <anchorfile>a00004.html</anchorfile>
      <anchor>abc2e7f1d01201c9bcedec558200e9fc3</anchor>
      <arglist>(const char *msg) const </arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~convenience_socket_base</name>
      <anchorfile>a00004.html</anchorfile>
      <anchor>a83d412113887b92f4e577965507bfec5</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::simple_socket_base</name>
    <filename>a00043.html</filename>
    <base>tlm_utils::convenience_socket_base</base>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>elaboration_check</name>
      <anchorfile>a00043.html</anchorfile>
      <anchor>ab3087c4716729fb6e9c97f710c500c9b</anchor>
      <arglist>(const char *action) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::passthrough_socket_base</name>
    <filename>a00024.html</filename>
    <base>tlm_utils::convenience_socket_base</base>
  </compound>
  <compound kind="class">
    <name>tlm_utils::multi_socket_base</name>
    <filename>a00020.html</filename>
    <base>tlm_utils::convenience_socket_base</base>
  </compound>
  <compound kind="class">
    <name>tlm_utils::convenience_socket_cb_holder</name>
    <filename>a00005.html</filename>
    <member kind="function">
      <type>void</type>
      <name>display_warning</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a5465a7ef2972a11ed44900fe0596ad90</anchor>
      <arglist>(const char *msg) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>display_error</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a961e77384e25c69c507d4c6c80a686e0</anchor>
      <arglist>(const char *msg) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>convenience_socket_cb_holder</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a383b4ae7cff63ebc93068dc32eaf791e</anchor>
      <arglist>(convenience_socket_base *owner)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::instance_specific_extension</name>
    <filename>a00008.html</filename>
    <templarg></templarg>
    <base>tlm_utils::ispex_base</base>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~instance_specific_extension</name>
      <anchorfile>a00008.html</anchorfile>
      <anchor>ae86416d763315ab5dade2e42d3503113</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const unsigned int</type>
      <name>priv_id</name>
      <anchorfile>a00008.html</anchorfile>
      <anchor>a9d48527402f547cba59857fc4ecd2f9d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::instance_specific_extension_carrier</name>
    <filename>a00010.html</filename>
    <base>tlm_extension&lt; instance_specific_extension_carrier &gt;</base>
    <member kind="function">
      <type></type>
      <name>instance_specific_extension_carrier</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>ad02d2ac504322215d8dc9e268b9d7178</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual tlm::tlm_extension_base *</type>
      <name>clone</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>a265a6ecec86bbcb4414a33d67e15c027</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>copy_from</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>ae0fe025d25253a805c26d0cb7d0053fd</anchor>
      <arglist>(tlm::tlm_extension_base const &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>free</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>a5b8539d41255875bb86be0b66572929e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>instance_specific_extension_accessor</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>ada2ab752ae94391b8a8d1afb2ad54f29</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::ispex_base</name>
    <filename>a00013.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ispex_base</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>afed46549cbda7a71b6e3aa7a3f540224</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static unsigned int</type>
      <name>register_private_extension</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>a922987c7673d887a2bef36f0aa7626b7</anchor>
      <arglist>(const std::type_info &amp;)</arglist>
    </member>
    <member kind="friend">
      <type>friend class</type>
      <name>tlm::tlm_array&lt; ispex_base * &gt;</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>a212143d5cb039e16216541ef529fb5af</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::instance_specific_extensions_per_accessor</name>
    <filename>a00012.html</filename>
    <member kind="typedef">
      <type>instance_specific_extension_container</type>
      <name>container_type</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>aeed8152d6082fc6a73a5e9cc75472944</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>instance_specific_extensions_per_accessor</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>a3fa3912616df14f92cde75b77c4f83c3</anchor>
      <arglist>(container_type *container)</arglist>
    </member>
    <member kind="function">
      <type>T *</type>
      <name>set_extension</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>ac77e67a2ea0afe5c1f9ed9174d0bf4fa</anchor>
      <arglist>(T *ext)</arglist>
    </member>
    <member kind="function">
      <type>ispex_base *</type>
      <name>set_extension</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>ad4095f15e9508a88b7fdb310db5721f8</anchor>
      <arglist>(unsigned int index, ispex_base *ext)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>get_extension</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>a8135b004215a1638e5bf31391c7ae5ea</anchor>
      <arglist>(T *&amp;ext) const </arglist>
    </member>
    <member kind="function">
      <type>ispex_base *</type>
      <name>get_extension</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>a9359464ca1c7bc6a3f1c2a550ee685c7</anchor>
      <arglist>(unsigned int index) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear_extension</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>add42d938f7b397aae1583d75e7de50a0</anchor>
      <arglist>(const T *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear_extension</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>a6952e1be05ef77e591525bf5cb1ed291</anchor>
      <arglist>(unsigned int index)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>resize_extensions</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>a41dc49d4c5392cfdc421421735a570ee</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::instance_specific_extension_container</name>
    <filename>a00011.html</filename>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>instance_specific_extension_accessor</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>ada2ab752ae94391b8a8d1afb2ad54f29</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>instance_specific_extension_carrier</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>af0cd21a3b5928dadc8458e97a966c277</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>instance_specific_extension_container_pool</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>a46ad79920f36945ea015dcbb980f4b6d</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>instance_specific_extensions_per_accessor</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>ac902468d232e1fca0f49d05881ed8570</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::instance_specific_extension_accessor</name>
    <filename>a00009.html</filename>
    <member kind="function">
      <type></type>
      <name>instance_specific_extension_accessor</name>
      <anchorfile>a00009.html</anchorfile>
      <anchor>a5c88f0ad0a89b1ecd977bda2220bd73f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>instance_specific_extensions_per_accessor &amp;</type>
      <name>operator()</name>
      <anchorfile>a00009.html</anchorfile>
      <anchor>a0d3c91b1a1933a542d3579ded181960c</anchor>
      <arglist>(T &amp;txn)</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>release_carrier</name>
      <anchorfile>a00009.html</anchorfile>
      <anchor>ac8a6a3fbcd38503b3a757af6d37f2204</anchor>
      <arglist>(instance_specific_extension_carrier *, void *txn)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>m_index</name>
      <anchorfile>a00009.html</anchorfile>
      <anchor>ab7ccc45359ccf73306d2cd5eca6b8153</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::multi_passthrough_initiator_socket</name>
    <filename>a00016.html</filename>
    <templarg>MODULE</templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg>TYPES</templarg>
    <templarg>N</templarg>
    <templarg>POL</templarg>
    <base>tlm_utils::multi_init_base</base>
    <member kind="typedef">
      <type>TYPES::tlm_payload_type</type>
      <name>transaction_type</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>ae79de77c20d9b10cf2f92103b6350f62</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TYPES::tlm_phase_type</type>
      <name>phase_type</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a7b6f94171743062801eca26edde24efc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_sync_enum</type>
      <name>sync_enum_type</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a08b034d03da58f38e132f501d320406d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>sync_enum_type(MODULE::*</type>
      <name>nb_cb</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a9badafae6c38735558b937d4ed197179</anchor>
      <arglist>)(int, transaction_type &amp;, phase_type &amp;, sc_core::sc_time &amp;)</arglist>
    </member>
    <member kind="typedef">
      <type>void(MODULE::*</type>
      <name>dmi_cb</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a0191077f22bab9c26316c137a5ede0aa</anchor>
      <arglist>)(int, sc_dt::uint64, sc_dt::uint64)</arglist>
    </member>
    <member kind="typedef">
      <type>multi_init_base&lt; BUSWIDTH, TYPES, N, POL &gt;</type>
      <name>base_type</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>ab076a2edda514af2a99ce43f570c7751</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>base_type::base_target_socket_type</type>
      <name>base_target_socket_type</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a412be3159f765aab119920bdf9dbd8b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>multi_passthrough_initiator_socket</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>af33d0a46b7a060d2ef6c1974bb3d5deb</anchor>
      <arglist>(const char *name=default_name())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~multi_passthrough_initiator_socket</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a1b1df1846b3b2ee6d3ca96712452ea06</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_nb_transport_bw</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>aa71818a86f768d9e55c5a7e20f1cdb63</anchor>
      <arglist>(MODULE *mod, sync_enum_type(MODULE::*cb)(int, transaction_type &amp;, phase_type &amp;, sc_core::sc_time &amp;))</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_invalidate_direct_mem_ptr</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>acb90f0f47ec64a9b3a47bd9c90f6884c</anchor>
      <arglist>(MODULE *mod, void(MODULE::*cb)(int, sc_dt::uint64, sc_dt::uint64))</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual tlm::tlm_bw_transport_if&lt; TYPES &gt; &amp;</type>
      <name>get_base_interface</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a9d4d6d139eacaa8ad6acf87ae3889115</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const tlm::tlm_bw_transport_if&lt; TYPES &gt; &amp;</type>
      <name>get_base_interface</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a8385ef79c55c98d8e4e0c77d792e6563</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_export&lt; tlm::tlm_bw_transport_if&lt; TYPES &gt; &gt; &amp;</type>
      <name>get_base_export</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a35beeda7838ceda497f6717549211d19</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const sc_core::sc_export&lt; tlm::tlm_bw_transport_if&lt; TYPES &gt; &gt; &amp;</type>
      <name>get_base_export</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a7a2e0805879fb43160ecacb159ed5608</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>bind</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a20878da423e58059408a3a420068d2f5</anchor>
      <arglist>(base_target_socket_type &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>af732774c680a658512af6860f21037d1</anchor>
      <arglist>(base_target_socket_type &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>before_end_of_elaboration</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a6c55374f7d5e9b6c4b0f4c9ee4f7e456</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>bind</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>aa8d9e98bde1201f096482a1b0732099d</anchor>
      <arglist>(base_type &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a14200c1b573e7e096913535b0f2e3e6f</anchor>
      <arglist>(base_type &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>tlm::tlm_fw_transport_if&lt; TYPES &gt; *</type>
      <name>operator[]</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a41797e7abe235f3c5e6efd3c246b8d8a</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>size</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a7c2d6187d9de379f06007c4085ce7d32</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>default_name</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>ada9321fcc4dddcb32a46bb0cc2dfbd05</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>base_type *</type>
      <name>get_hierarch_bind</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>af160c9ebe2b88f8b3f266effea94d571</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>disable_cb_bind</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>aa5dcdec260f84b5dfa514726f9b3b694</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>std::vector&lt; callback_binder_bw&lt; TYPES &gt; * &gt; &amp;</type>
      <name>get_binders</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a4bcf3102e9bc2a903675b413c6b249aa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>std::vector&lt; tlm::tlm_fw_transport_if&lt; TYPES &gt; * &gt; &amp;</type>
      <name>get_sockets</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>af2eab34a10975b7566e385d0ee7cb04e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; tlm::tlm_fw_transport_if&lt; TYPES &gt; * &gt;</type>
      <name>m_sockets</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a51a25ff90a86be76a0039fd94063790b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; tlm::tlm_fw_transport_if&lt; TYPES &gt; * &gt;</type>
      <name>m_used_sockets</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a55b13a553f43a092ad6a97ca7d98c8a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; callback_binder_bw&lt; TYPES &gt; * &gt;</type>
      <name>m_binders</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a4abda8ae69c353b31ed06065ef7afcfd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>base_type *</type>
      <name>m_hierarch_bind</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>ac8f30a18afbb343f48a3b204555181fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>m_beoe_disabled</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>aef91eeb042540b72d334be6ef94be5b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>callback_binder_bw&lt; TYPES &gt;</type>
      <name>m_dummy</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>ad52c193b2ea265be7410b0ee9632d786</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>callback_binder_bw&lt; TYPES &gt;::nb_func_type</type>
      <name>m_nb_f</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a3b6a674752ec8fcd72d4d1d3fd2280ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>callback_binder_bw&lt; TYPES &gt;::dmi_func_type</type>
      <name>m_dmi_f</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>a806e9dbf3da5c3942be01215e476e1f4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::multi_passthrough_initiator_socket_optional</name>
    <filename>a00017.html</filename>
    <templarg></templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg></templarg>
    <templarg>N</templarg>
    <base>multi_passthrough_initiator_socket&lt; MODULE, BUSWIDTH, TYPES, N, sc_core::SC_ZERO_OR_MORE_BOUND &gt;</base>
    <member kind="function">
      <type></type>
      <name>multi_passthrough_initiator_socket_optional</name>
      <anchorfile>a00017.html</anchorfile>
      <anchor>aa08ad9c172e3d7c9d4b70337d5c893b0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>multi_passthrough_initiator_socket_optional</name>
      <anchorfile>a00017.html</anchorfile>
      <anchor>ab948635f47363d534136f4f2fe2e60ab</anchor>
      <arglist>(const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::multi_passthrough_target_socket</name>
    <filename>a00018.html</filename>
    <templarg>MODULE</templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg>TYPES</templarg>
    <templarg>N</templarg>
    <templarg>POL</templarg>
    <base>tlm_utils::multi_target_base</base>
    <base>tlm_utils::multi_to_multi_bind_base</base>
    <member kind="typedef">
      <type>TYPES::tlm_payload_type</type>
      <name>transaction_type</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>aec647d3b9c3487051267c1d173ebcce2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TYPES::tlm_phase_type</type>
      <name>phase_type</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a3d8ab5fa9336bfb2fdb1800ea864f87b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_sync_enum</type>
      <name>sync_enum_type</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a2157ba87a62bbba14744d7e8d4e71377</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>sync_enum_type(MODULE::*</type>
      <name>nb_cb</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>ad6e6f261ed6aadc08b8d7bbb205fbf45</anchor>
      <arglist>)(int, transaction_type &amp;, phase_type &amp;, sc_core::sc_time &amp;)</arglist>
    </member>
    <member kind="typedef">
      <type>void(MODULE::*</type>
      <name>b_cb</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a8f43550af4a23911add98b8d599c1a32</anchor>
      <arglist>)(int, transaction_type &amp;, sc_core::sc_time &amp;)</arglist>
    </member>
    <member kind="typedef">
      <type>unsigned int(MODULE::*</type>
      <name>dbg_cb</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a221bf9564233d506621ff970aed79928</anchor>
      <arglist>)(int, transaction_type &amp;txn)</arglist>
    </member>
    <member kind="typedef">
      <type>bool(MODULE::*</type>
      <name>dmi_cb</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a5a5a908915b50bda5ed172c20dca51fd</anchor>
      <arglist>)(int, transaction_type &amp;txn, tlm::tlm_dmi &amp;dmi)</arglist>
    </member>
    <member kind="typedef">
      <type>multi_target_base&lt; BUSWIDTH, TYPES, N, POL &gt;</type>
      <name>base_type</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a458a6cf75552df1eaca088d6795af64b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>base_type::base_initiator_socket_type</type>
      <name>base_initiator_socket_type</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a8b6255a7f8da77d0391e6c0f8211d807</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>multi_passthrough_target_socket</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a4046d5fdb77cd3236e1a1be40b2c5c71</anchor>
      <arglist>(const char *name=default_name())</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~multi_passthrough_target_socket</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a36c7e975e8fa3949daffb93204089c36</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>check_export_binding</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a8f6f3cb48354b3e57f273f46d8f3f837</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_nb_transport_fw</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>ae3fd3a28bd9a1eafca122bc5e9dd7a5c</anchor>
      <arglist>(MODULE *mod, nb_cb cb)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_b_transport</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>ad55d7072ab4226012c84b3d6b146e9fb</anchor>
      <arglist>(MODULE *mod, b_cb cb)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_transport_dbg</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a551123b8402877778918e796c9e5d259</anchor>
      <arglist>(MODULE *mod, dbg_cb cb)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_get_direct_mem_ptr</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a437cf9e7f479a86bced10a3fd4785f7c</anchor>
      <arglist>(MODULE *mod, dmi_cb cb)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual tlm::tlm_fw_transport_if&lt; TYPES &gt; &amp;</type>
      <name>get_base_interface</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a900daa42a839712c1c849e53e85ee001</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const tlm::tlm_fw_transport_if&lt; TYPES &gt; &amp;</type>
      <name>get_base_interface</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>ae7aa4d08953aebf6a86dcbabd1048de8</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_export&lt; tlm::tlm_fw_transport_if&lt; TYPES &gt; &gt; &amp;</type>
      <name>get_base_export</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a2b76eeda3e46bd4976bad7611f8e2052</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const sc_core::sc_export&lt; tlm::tlm_fw_transport_if&lt; TYPES &gt; &gt; &amp;</type>
      <name>get_base_export</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a43f19cbc525967bef504a012fbd8d092</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>end_of_elaboration</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a28a6bd16ef2f6734399c6c41e2925da2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>bind</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a928893a2fcceb11721b3c7574a8a69ad</anchor>
      <arglist>(base_type &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a2cadb2e9029a786c1bbfd92fa802d619</anchor>
      <arglist>(base_type &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>tlm::tlm_bw_transport_if&lt; TYPES &gt; *</type>
      <name>operator[]</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a83dcfb9ee6723761931c8453859a0052</anchor>
      <arglist>(int i)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>size</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a52282bc1eed89307c9730c8c2dc5844e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>default_name</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>addf82e035a5acd1ed75267b71fc87412</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>base_type *</type>
      <name>get_hierarch_bind</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a61110e08d949a82405281b39ebe33b1d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>std::map&lt; unsigned int, tlm::tlm_bw_transport_if&lt; TYPES &gt; * &gt; &amp;</type>
      <name>get_multi_binds</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a165f94d6b4a771f3e6f05242ca1223d9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>set_hierarch_bind</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a2d6de8a2efa121fc7916efffe649a4b5</anchor>
      <arglist>(base_type *h)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>tlm::tlm_fw_transport_if&lt; TYPES &gt; *</type>
      <name>get_last_binder</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a42e37bb76180fe585ea2d1e27cda0f7f</anchor>
      <arglist>(tlm::tlm_bw_transport_if&lt; TYPES &gt; *other)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>disable_cb_bind</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a8149d174826744005af19a0612c60d34</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>std::vector&lt; callback_binder_fw&lt; TYPES &gt; * &gt; &amp;</type>
      <name>get_binders</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>ad2648d05e5dbea4a43854bc8424ba940</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::map&lt; unsigned int, tlm::tlm_bw_transport_if&lt; TYPES &gt; * &gt;</type>
      <name>m_multi_binds</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>af8809fbaf64f7b1094800c00d197245e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; tlm::tlm_bw_transport_if&lt; TYPES &gt; * &gt;</type>
      <name>m_sockets</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a21833df2daf8f4412d360d43289412e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; callback_binder_fw&lt; TYPES &gt; * &gt;</type>
      <name>m_binders</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a04e91d988371f22394dbacd872403215</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>base_type *</type>
      <name>m_hierarch_bind</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a7e9e13514ee7bc498c75914dcbc59ed1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>m_eoe_disabled</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a59eaa6ded69f29bd8cdaddac15b98b46</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>m_export_callback_created</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a4ef4c49624611b6bdf441aa522d3fb0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>callback_binder_fw&lt; TYPES &gt;::nb_func_type</type>
      <name>m_nb_f</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>ae24bfbc0e40f7674196ade223ac92193</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>callback_binder_fw&lt; TYPES &gt;::b_func_type</type>
      <name>m_b_f</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>ad5c7e8e78eb1bec160a71facdf3cae3b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>callback_binder_fw&lt; TYPES &gt;::debug_func_type</type>
      <name>m_dbg_f</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a1e561aae8501e351d4f7fd6a7ff24086</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>callback_binder_fw&lt; TYPES &gt;::dmi_func_type</type>
      <name>m_dmi_f</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>a0bf0a44728962268a815678d038beb8c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::multi_passthrough_target_socket_optional</name>
    <filename>a00019.html</filename>
    <templarg></templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg></templarg>
    <templarg>N</templarg>
    <base>multi_passthrough_target_socket&lt; MODULE, BUSWIDTH, TYPES, N, sc_core::SC_ZERO_OR_MORE_BOUND &gt;</base>
    <member kind="function">
      <type></type>
      <name>multi_passthrough_target_socket_optional</name>
      <anchorfile>a00019.html</anchorfile>
      <anchor>ac88d7d82c131ae4cbbded94a2e73f4b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>multi_passthrough_target_socket_optional</name>
      <anchorfile>a00019.html</anchorfile>
      <anchor>a9066789cfb067027ee06a06e3b06cbf8</anchor>
      <arglist>(const char *name)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>tlm_utils::fn_container</name>
    <filename>a00007.html</filename>
    <templarg></templarg>
    <member kind="variable">
      <type>signature</type>
      <name>function</name>
      <anchorfile>a00007.html</anchorfile>
      <anchor>ae06279b583d28c50c02cd531917fe162</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::callback_binder_fw</name>
    <filename>a00002.html</filename>
    <templarg>TYPES</templarg>
    <base>tlm::tlm_fw_transport_if</base>
    <base protection="protected">tlm_utils::convenience_socket_cb_holder</base>
    <member kind="typedef">
      <type>TYPES::tlm_payload_type</type>
      <name>transaction_type</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a2ffd5af7b887450c7db7a5cc88ce5527</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TYPES::tlm_phase_type</type>
      <name>phase_type</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>aa522794b3b564136592bebcd756264b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_sync_enum</type>
      <name>sync_enum_type</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>aee6780e841d3f314b0d7f21e6b705832</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>nb_transport_functor&lt; TYPES &gt;</type>
      <name>nb_func_type</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a55e4b658477bceb019742f5f73f91070</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>b_transport_functor&lt; TYPES &gt;</type>
      <name>b_func_type</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>aa179ac21c6743e01ba335d1eb3540e5c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>debug_transport_functor&lt; TYPES &gt;</type>
      <name>debug_func_type</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a2f685921043c770c4da2f663f86ec0b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>get_dmi_ptr_functor&lt; TYPES &gt;</type>
      <name>dmi_func_type</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a02dbc2a2fd17c90dd702e6e7189c323a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>callback_binder_fw</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a3809f41b3a14e05c35a8c00c08999a3a</anchor>
      <arglist>(multi_socket_base *owner, int id)</arglist>
    </member>
    <member kind="function">
      <type>sync_enum_type</type>
      <name>nb_transport_fw</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>aca4d674fd5a32bfb688d4d6b9054645d</anchor>
      <arglist>(transaction_type &amp;txn, phase_type &amp;p, sc_core::sc_time &amp;t)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>b_transport</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a8d570f0310e4183f680ed86bbb2270c8</anchor>
      <arglist>(transaction_type &amp;trans, sc_core::sc_time &amp;t)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>get_direct_mem_ptr</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a9c9c5f08913425426482827eed06c21f</anchor>
      <arglist>(transaction_type &amp;trans, tlm::tlm_dmi &amp;dmi_data)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>transport_dbg</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>adae94867ee608a2d90c378923b91fc0d</anchor>
      <arglist>(transaction_type &amp;trans)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_port</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a26ea0810a5e47514fa9425c72d09c05f</anchor>
      <arglist>(sc_core::sc_port_base &amp;b, const char *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_callbacks</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>af860cbda7b94fb0c8f687530f4c9bf2f</anchor>
      <arglist>(nb_func_type &amp;cb1, b_func_type &amp;cb2, dmi_func_type &amp;cb3, debug_func_type &amp;cb4)</arglist>
    </member>
    <member kind="function">
      <type>sc_core::sc_port_base *</type>
      <name>get_other_side</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>a9ae1cab032dc01e99df4f18e39181859</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::callback_binder_bw</name>
    <filename>a00001.html</filename>
    <templarg>TYPES</templarg>
    <base>tlm::tlm_bw_transport_if</base>
    <base protection="protected">tlm_utils::convenience_socket_cb_holder</base>
    <member kind="typedef">
      <type>TYPES::tlm_payload_type</type>
      <name>transaction_type</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>ae9b0670df173b3803ea26d8b92191c66</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TYPES::tlm_phase_type</type>
      <name>phase_type</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a2de2d9d75fa6b7a05a919c66a58ab497</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_sync_enum</type>
      <name>sync_enum_type</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a42c17ed2c79207e89d63b28b89358524</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>nb_transport_functor&lt; TYPES &gt;</type>
      <name>nb_func_type</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>ad50bd062b615f2d248a32a5ac1d07afb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>invalidate_dmi_functor&lt; TYPES &gt;</type>
      <name>dmi_func_type</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>ad204860bfa00750a79f30d7b7de360f0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>callback_binder_bw</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>ab1b1e6f05b57f6d4efcf2f54c33dd5d9</anchor>
      <arglist>(multi_socket_base *owner, int id)</arglist>
    </member>
    <member kind="function">
      <type>sync_enum_type</type>
      <name>nb_transport_bw</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a30ae951c74bcc1672dfa2749e1bec486</anchor>
      <arglist>(transaction_type &amp;txn, phase_type &amp;p, sc_core::sc_time &amp;t)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>invalidate_direct_mem_ptr</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>ad33af4e1236b00d58a36456d10c2ac38</anchor>
      <arglist>(sc_dt::uint64 l, sc_dt::uint64 u)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_callbacks</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a4fe3c4de09bc86fb5f1daba52a34b837</anchor>
      <arglist>(nb_func_type &amp;cb1, dmi_func_type &amp;cb2)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::multi_init_base_if</name>
    <filename>a00015.html</filename>
    <templarg></templarg>
    <member kind="function" virtualness="pure">
      <type>virtual std::vector&lt; callback_binder_bw&lt; TYPES &gt; * &gt; &amp;</type>
      <name>get_binders</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>acddc40701e3a4f5fa34d9cd71619f6e7</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::vector&lt; tlm::tlm_fw_transport_if&lt; TYPES &gt; * &gt; &amp;</type>
      <name>get_sockets</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>a5de7a10b4894f6a1f423872c6cea6ab5</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~multi_init_base_if</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>add54852a65148d28d12bf627fea2ac7f</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::multi_init_base</name>
    <filename>a00014.html</filename>
    <templarg>BUSWIDTH</templarg>
    <templarg></templarg>
    <templarg>N</templarg>
    <templarg>POL</templarg>
    <base>tlm::tlm_initiator_socket</base>
    <base>tlm_utils::multi_init_base_if</base>
    <base protection="protected">tlm_utils::multi_socket_base</base>
    <member kind="typedef">
      <type>tlm::tlm_initiator_socket&lt; BUSWIDTH, TYPES, N, POL &gt;</type>
      <name>base_type</name>
      <anchorfile>a00014.html</anchorfile>
      <anchor>a2056d8316b6dd5193c7e9c7e7fc4003e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>disable_cb_bind</name>
      <anchorfile>a00014.html</anchorfile>
      <anchor>ab5d7a458a633f87ad6ba4ca00b8df6de</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual multi_init_base *</type>
      <name>get_hierarch_bind</name>
      <anchorfile>a00014.html</anchorfile>
      <anchor>a46385159a53dc1e8e5cfe0dd452b1293</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual tlm::tlm_socket_category</type>
      <name>get_socket_category</name>
      <anchorfile>a00014.html</anchorfile>
      <anchor>a661c1c2d6ebd9e16a36b2b4445fde852</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~multi_init_base</name>
      <anchorfile>a00014.html</anchorfile>
      <anchor>a0a1966af80cf4e8ea8b59292949af60c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>multi_init_base</name>
      <anchorfile>a00014.html</anchorfile>
      <anchor>a1a07c0c0d76788d54847c8bffab5b1b0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>multi_init_base</name>
      <anchorfile>a00014.html</anchorfile>
      <anchor>ad1f95759003604b94be4f9b301bc62f9</anchor>
      <arglist>(const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::multi_target_base_if</name>
    <filename>a00022.html</filename>
    <templarg></templarg>
    <member kind="function" virtualness="pure">
      <type>virtual std::vector&lt; callback_binder_fw&lt; TYPES &gt; * &gt; &amp;</type>
      <name>get_binders</name>
      <anchorfile>a00022.html</anchorfile>
      <anchor>a431cce655ac2270ae08670c563d20be6</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::map&lt; unsigned int, tlm::tlm_bw_transport_if&lt; TYPES &gt; * &gt; &amp;</type>
      <name>get_multi_binds</name>
      <anchorfile>a00022.html</anchorfile>
      <anchor>a3bec73a6b50860d0817974d503d840e4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual</type>
      <name>~multi_target_base_if</name>
      <anchorfile>a00022.html</anchorfile>
      <anchor>af0e1e4407c576397ec4190012ff11c0c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::multi_target_base</name>
    <filename>a00021.html</filename>
    <templarg>BUSWIDTH</templarg>
    <templarg></templarg>
    <templarg>N</templarg>
    <templarg>POL</templarg>
    <base>tlm::tlm_target_socket</base>
    <base>tlm_utils::multi_target_base_if</base>
    <base protection="protected">tlm_utils::multi_socket_base</base>
    <member kind="typedef">
      <type>tlm::tlm_target_socket&lt; BUSWIDTH, TYPES, N, POL &gt;</type>
      <name>base_type</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>a76554a5d0a5f77d7f5158ba5a610c7f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual multi_target_base *</type>
      <name>get_hierarch_bind</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>afb941d2b43f615640e66380b042dc827</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>set_hierarch_bind</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>abab0009c7fc6a97b924e16500dc04c54</anchor>
      <arglist>(multi_target_base *)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual tlm::tlm_socket_category</type>
      <name>get_socket_category</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>aff5658303d8c5d007e08f30c92b40733</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~multi_target_base</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>adf03dc930fca17ce85a79ede15e3601e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>multi_target_base</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>a470fb98b629a20d27c67c01a557befa4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>multi_target_base</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>a500d3fc438d8348182842903304f0aea</anchor>
      <arglist>(const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::multi_to_multi_bind_base</name>
    <filename>a00023.html</filename>
    <templarg>TYPES</templarg>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~multi_to_multi_bind_base</name>
      <anchorfile>a00023.html</anchorfile>
      <anchor>ab823b6c7c9cac9785e29f2461a9ac6ab</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual tlm::tlm_fw_transport_if&lt; TYPES &gt; *</type>
      <name>get_last_binder</name>
      <anchorfile>a00023.html</anchorfile>
      <anchor>aeffa42d92a2c57baf0d0510ec2da208e</anchor>
      <arglist>(tlm::tlm_bw_transport_if&lt; TYPES &gt; *)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::passthrough_target_socket_b</name>
    <filename>a00026.html</filename>
    <templarg>MODULE</templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg>TYPES</templarg>
    <templarg>POL</templarg>
    <base>tlm_target_socket&lt; BUSWIDTH, TYPES, 1, POL &gt;</base>
    <base protection="protected">tlm_utils::passthrough_socket_base</base>
    <class kind="class">tlm_utils::passthrough_target_socket_b::process</class>
    <member kind="typedef">
      <type>TYPES::tlm_payload_type</type>
      <name>transaction_type</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>a810fee9ce0dcbba1f0e3715edd576a62</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TYPES::tlm_phase_type</type>
      <name>phase_type</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>a4a4ae69a1978db3dec300bcc78c40383</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_sync_enum</type>
      <name>sync_enum_type</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>a04f60602ab865051bb505685a6231fa1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_fw_transport_if&lt; TYPES &gt;</type>
      <name>fw_interface_type</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>ace64ad47058ed29efc19b09a61244662</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_bw_transport_if&lt; TYPES &gt;</type>
      <name>bw_interface_type</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>a05a0e38b09df63cf7de5f2ebdcfac611</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_target_socket&lt; BUSWIDTH, TYPES, 1, POL &gt;</type>
      <name>base_type</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>ac80df8a2b3ea738ad26ff88fe905650a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>passthrough_target_socket_b</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>a5860c95bc38e529e6e8b0edfa1ae6483</anchor>
      <arglist>(const char *n=default_name())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_nb_transport_fw</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>ad53c9e25b6d46c3fc4a23ed302659a77</anchor>
      <arglist>(MODULE *mod, sync_enum_type(MODULE::*cb)(transaction_type &amp;, phase_type &amp;, sc_core::sc_time &amp;))</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_b_transport</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>afd80ca71863e6e65f12a4699aee3b706</anchor>
      <arglist>(MODULE *mod, void(MODULE::*cb)(transaction_type &amp;, sc_core::sc_time &amp;))</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_transport_dbg</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>a08282a0fcbd342f0a7b0efd7011a977a</anchor>
      <arglist>(MODULE *mod, unsigned int(MODULE::*cb)(transaction_type &amp;))</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_get_direct_mem_ptr</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>a2239039fa89ae5007d3284fe6e58f67e</anchor>
      <arglist>(MODULE *mod, bool(MODULE::*cb)(transaction_type &amp;, tlm::tlm_dmi &amp;))</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>default_name</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>a06ce2ece79e2ec0af172c27931ae8652</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::passthrough_target_socket</name>
    <filename>a00025.html</filename>
    <templarg></templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg></templarg>
    <base>passthrough_target_socket_b&lt; MODULE, BUSWIDTH, TYPES &gt;</base>
    <member kind="function">
      <type></type>
      <name>passthrough_target_socket</name>
      <anchorfile>a00025.html</anchorfile>
      <anchor>ad863fc4d66efd8805b41bc2136537fd3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>passthrough_target_socket</name>
      <anchorfile>a00025.html</anchorfile>
      <anchor>ac8d1fb438ebd089bee358196ebe434bb</anchor>
      <arglist>(const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::passthrough_target_socket_optional</name>
    <filename>a00027.html</filename>
    <templarg></templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg></templarg>
    <base>passthrough_target_socket_b&lt; MODULE, BUSWIDTH, TYPES, sc_core::SC_ZERO_OR_MORE_BOUND &gt;</base>
    <member kind="function">
      <type></type>
      <name>passthrough_target_socket_optional</name>
      <anchorfile>a00027.html</anchorfile>
      <anchor>a7efa558893b0259d768ee0d1c3acb713</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>passthrough_target_socket_optional</name>
      <anchorfile>a00027.html</anchorfile>
      <anchor>a44a55c69bb1ea283c716b2533cd127bb</anchor>
      <arglist>(const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::passthrough_target_socket_tagged_b</name>
    <filename>a00029.html</filename>
    <templarg>MODULE</templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg>TYPES</templarg>
    <templarg>POL</templarg>
    <base>tlm_target_socket&lt; BUSWIDTH, TYPES, 1, POL &gt;</base>
    <base protection="protected">tlm_utils::passthrough_socket_base</base>
    <class kind="class">tlm_utils::passthrough_target_socket_tagged_b::process</class>
    <member kind="typedef">
      <type>TYPES::tlm_payload_type</type>
      <name>transaction_type</name>
      <anchorfile>a00029.html</anchorfile>
      <anchor>ae1f296e22c14261fae7b8f7749c4a494</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TYPES::tlm_phase_type</type>
      <name>phase_type</name>
      <anchorfile>a00029.html</anchorfile>
      <anchor>a982ed9f53cd77094aae5db971c609f64</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_sync_enum</type>
      <name>sync_enum_type</name>
      <anchorfile>a00029.html</anchorfile>
      <anchor>a14e23ef1ca2597c3b89f1cd611c27ba8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_fw_transport_if&lt; TYPES &gt;</type>
      <name>fw_interface_type</name>
      <anchorfile>a00029.html</anchorfile>
      <anchor>a347ed6896883d28160844d7ce67d0743</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_bw_transport_if&lt; TYPES &gt;</type>
      <name>bw_interface_type</name>
      <anchorfile>a00029.html</anchorfile>
      <anchor>a3af2f8e885093e471086eabeca6ae909</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_target_socket&lt; BUSWIDTH, TYPES, 1, POL &gt;</type>
      <name>base_type</name>
      <anchorfile>a00029.html</anchorfile>
      <anchor>a85f663432c4a33342f4409e9d11c5e67</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>passthrough_target_socket_tagged_b</name>
      <anchorfile>a00029.html</anchorfile>
      <anchor>a3f60194bbbc810935110090746f8c935</anchor>
      <arglist>(const char *n=default_name())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_nb_transport_fw</name>
      <anchorfile>a00029.html</anchorfile>
      <anchor>a8191a8ddbd8febfda1554ab94a78bf68</anchor>
      <arglist>(MODULE *mod, sync_enum_type(MODULE::*cb)(int id, transaction_type &amp;, phase_type &amp;, sc_core::sc_time &amp;), int id)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_b_transport</name>
      <anchorfile>a00029.html</anchorfile>
      <anchor>aeaa2c49856e611178e259fade0c8e410</anchor>
      <arglist>(MODULE *mod, void(MODULE::*cb)(int id, transaction_type &amp;, sc_core::sc_time &amp;), int id)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_transport_dbg</name>
      <anchorfile>a00029.html</anchorfile>
      <anchor>a3e382e9447d339428cd730353fa88f11</anchor>
      <arglist>(MODULE *mod, unsigned int(MODULE::*cb)(int id, transaction_type &amp;), int id)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_get_direct_mem_ptr</name>
      <anchorfile>a00029.html</anchorfile>
      <anchor>af8576f1599283130daffc6fa498e976b</anchor>
      <arglist>(MODULE *mod, bool(MODULE::*cb)(int id, transaction_type &amp;, tlm::tlm_dmi &amp;), int id)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>default_name</name>
      <anchorfile>a00029.html</anchorfile>
      <anchor>a7e5b0a92a84cfc0f91b812fb086715f6</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::passthrough_target_socket_tagged</name>
    <filename>a00028.html</filename>
    <templarg></templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg></templarg>
    <base>passthrough_target_socket_tagged_b&lt; MODULE, BUSWIDTH, TYPES &gt;</base>
    <member kind="function">
      <type></type>
      <name>passthrough_target_socket_tagged</name>
      <anchorfile>a00028.html</anchorfile>
      <anchor>a9c9ccb3a01d1cc2d15e41281f4797373</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>passthrough_target_socket_tagged</name>
      <anchorfile>a00028.html</anchorfile>
      <anchor>a9305e170bf52e685bb8039799f9c3eb0</anchor>
      <arglist>(const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::passthrough_target_socket_tagged_optional</name>
    <filename>a00030.html</filename>
    <templarg></templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg></templarg>
    <base>passthrough_target_socket_tagged_b&lt; MODULE, BUSWIDTH, TYPES, sc_core::SC_ZERO_OR_MORE_BOUND &gt;</base>
    <member kind="function">
      <type></type>
      <name>passthrough_target_socket_tagged_optional</name>
      <anchorfile>a00030.html</anchorfile>
      <anchor>a50cf062db1ec0fbd4e34075ab3981d36</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>passthrough_target_socket_tagged_optional</name>
      <anchorfile>a00030.html</anchorfile>
      <anchor>ae4babe000ab18a3b7a25647c086276e5</anchor>
      <arglist>(const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::time_ordered_list</name>
    <filename>a00050.html</filename>
    <templarg></templarg>
    <class kind="struct">tlm_utils::time_ordered_list::element</class>
    <member kind="function">
      <type></type>
      <name>time_ordered_list</name>
      <anchorfile>a00050.html</anchorfile>
      <anchor>afb402fc1aee3b96981ba2788897191da</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~time_ordered_list</name>
      <anchorfile>a00050.html</anchorfile>
      <anchor>a9283201c52ffc0e76669ec85a1ff1027</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>a00050.html</anchorfile>
      <anchor>a4ffcf7433e3fcb571345886735b489aa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>insert</name>
      <anchorfile>a00050.html</anchorfile>
      <anchor>a74bce485ff3032a6313c96b544a5b99c</anchor>
      <arglist>(const PAYLOAD &amp;p, sc_core::sc_time t)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>delete_top</name>
      <anchorfile>a00050.html</anchorfile>
      <anchor>a649901c28b1dd0c9571ef3abd6b55ad6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>get_size</name>
      <anchorfile>a00050.html</anchorfile>
      <anchor>a3658d9b2394bf83d52adab24ac7984ad</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>PAYLOAD &amp;</type>
      <name>top</name>
      <anchorfile>a00050.html</anchorfile>
      <anchor>a2ffbb7a19f09bb3f045c5620ce4473dc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>sc_core::sc_time</type>
      <name>top_time</name>
      <anchorfile>a00050.html</anchorfile>
      <anchor>a2fdeb6100df03a345f071b7eb7bc3ac5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>sc_dt::uint64 &amp;</type>
      <name>top_delta</name>
      <anchorfile>a00050.html</anchorfile>
      <anchor>a3643bc2ee1dc07c3762c2af7575c4273</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>sc_core::sc_time</type>
      <name>next_time</name>
      <anchorfile>a00050.html</anchorfile>
      <anchor>ae43186c0dfe55abe0a9ed177c1469d59</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>element *</type>
      <name>nill</name>
      <anchorfile>a00050.html</anchorfile>
      <anchor>a2a45e5cc54405eb6aa96fa38aba28df3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>element *</type>
      <name>empties</name>
      <anchorfile>a00050.html</anchorfile>
      <anchor>acbc38ec28414bc85e91987ba07b084a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>element *</type>
      <name>list</name>
      <anchorfile>a00050.html</anchorfile>
      <anchor>ac5bad49f56fcf465f7fe8e65e3f8cf66</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned int</type>
      <name>size</name>
      <anchorfile>a00050.html</anchorfile>
      <anchor>ad3b03580b5cbd53ab724bd356e735da4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>tlm_utils::time_ordered_list::element</name>
    <filename>a00006.html</filename>
    <member kind="function">
      <type></type>
      <name>element</name>
      <anchorfile>a00006.html</anchorfile>
      <anchor>afc2857ee1414efaa2e21049ee4d22116</anchor>
      <arglist>(PAYLOAD &amp;p, sc_core::sc_time t, sc_dt::uint64 d)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>element</name>
      <anchorfile>a00006.html</anchorfile>
      <anchor>a2a9412e3f30b0f6e444d8a243a40e6d5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>struct element *</type>
      <name>next</name>
      <anchorfile>a00006.html</anchorfile>
      <anchor>a36056c24d6f2e37354c240aca9053871</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>PAYLOAD</type>
      <name>p</name>
      <anchorfile>a00006.html</anchorfile>
      <anchor>a0b6ae02f83ebcbee5a134a3fe9c186bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sc_core::sc_time</type>
      <name>t</name>
      <anchorfile>a00006.html</anchorfile>
      <anchor>ac090b629cbb9e901b98f6881a518f9dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>sc_dt::uint64</type>
      <name>d</name>
      <anchorfile>a00006.html</anchorfile>
      <anchor>ad9b24bdb184a44c6f6f2abbe783d36f4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::peq_with_cb_and_phase</name>
    <filename>a00031.html</filename>
    <templarg></templarg>
    <templarg></templarg>
    <class kind="class">tlm_utils::peq_with_cb_and_phase::delta_list</class>
    <member kind="function">
      <type></type>
      <name>peq_with_cb_and_phase</name>
      <anchorfile>a00031.html</anchorfile>
      <anchor>a07a9512002bba9ff58448b9b2e2cbf34</anchor>
      <arglist>(OWNER *_owner, cb _cb)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>peq_with_cb_and_phase</name>
      <anchorfile>a00031.html</anchorfile>
      <anchor>a56ce5d59d37c5dda71134cafff12f115</anchor>
      <arglist>(const char *_name, OWNER *_owner, cb _cb)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~peq_with_cb_and_phase</name>
      <anchorfile>a00031.html</anchorfile>
      <anchor>a10c1a23faab438cb14049a08c472287b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>notify</name>
      <anchorfile>a00031.html</anchorfile>
      <anchor>afbf86082069f1c1b35a6597edfb1e421</anchor>
      <arglist>(tlm_payload_type &amp;t, const tlm_phase_type &amp;p, const sc_core::sc_time &amp;when)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>notify</name>
      <anchorfile>a00031.html</anchorfile>
      <anchor>af8d68079416c8b246ca11706617e4c7a</anchor>
      <arglist>(tlm_payload_type &amp;t, const tlm_phase_type &amp;p)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cancel_all</name>
      <anchorfile>a00031.html</anchorfile>
      <anchor>a5a1653274947d8852d20850609b23f5b</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::peq_with_get</name>
    <filename>a00032.html</filename>
    <templarg>PAYLOAD</templarg>
    <member kind="typedef">
      <type>PAYLOAD</type>
      <name>transaction_type</name>
      <anchorfile>a00032.html</anchorfile>
      <anchor>a3564410e7e3862db40bfd563c5de5aa1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::pair&lt; const sc_core::sc_time, transaction_type * &gt;</type>
      <name>pair_type</name>
      <anchorfile>a00032.html</anchorfile>
      <anchor>a4905cbccbeb1bd27ede23d6f5257bb9d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>peq_with_get</name>
      <anchorfile>a00032.html</anchorfile>
      <anchor>a5f62ba2f9636c9ac14c41f349f4ca20a</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>notify</name>
      <anchorfile>a00032.html</anchorfile>
      <anchor>afa58f46a9d53dfba4dd192d053b6d20b</anchor>
      <arglist>(transaction_type &amp;trans, const sc_core::sc_time &amp;t)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>notify</name>
      <anchorfile>a00032.html</anchorfile>
      <anchor>a74fcf1ab258b031242fb67eb3fcb9f38</anchor>
      <arglist>(transaction_type &amp;trans)</arglist>
    </member>
    <member kind="function">
      <type>transaction_type *</type>
      <name>get_next_transaction</name>
      <anchorfile>a00032.html</anchorfile>
      <anchor>a3d81c728a7bad793414115b924ec18f3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>sc_core::sc_event &amp;</type>
      <name>get_event</name>
      <anchorfile>a00032.html</anchorfile>
      <anchor>ab4baeffd5b0384d2edbbcddf0bc42120</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cancel_all</name>
      <anchorfile>a00032.html</anchorfile>
      <anchor>ad92d27e5959a53bbd4a7fb1e99d38aa7</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::simple_initiator_socket_b</name>
    <filename>a00038.html</filename>
    <templarg>MODULE</templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg>TYPES</templarg>
    <templarg>POL</templarg>
    <base>tlm_initiator_socket&lt; BUSWIDTH, TYPES, 1, POL &gt;</base>
    <base protection="protected">tlm_utils::simple_socket_base</base>
    <class kind="class">tlm_utils::simple_initiator_socket_b::process</class>
    <member kind="typedef">
      <type>TYPES::tlm_payload_type</type>
      <name>transaction_type</name>
      <anchorfile>a00038.html</anchorfile>
      <anchor>a7d1164cc9722545e423070727767bb0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TYPES::tlm_phase_type</type>
      <name>phase_type</name>
      <anchorfile>a00038.html</anchorfile>
      <anchor>a67177e2f0717c962367c389ff2965c8b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_sync_enum</type>
      <name>sync_enum_type</name>
      <anchorfile>a00038.html</anchorfile>
      <anchor>a4d9998bf5a6880fec1ef9452f4f98898</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_fw_transport_if&lt; TYPES &gt;</type>
      <name>fw_interface_type</name>
      <anchorfile>a00038.html</anchorfile>
      <anchor>ad899a1c0dbba0835735f5f00d63402b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_bw_transport_if&lt; TYPES &gt;</type>
      <name>bw_interface_type</name>
      <anchorfile>a00038.html</anchorfile>
      <anchor>a9aca863bba4e01f847b5023aec36daf8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_initiator_socket&lt; BUSWIDTH, TYPES, 1, POL &gt;</type>
      <name>base_type</name>
      <anchorfile>a00038.html</anchorfile>
      <anchor>a67d7ea5247a926ae3ad27912b7cb472b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>simple_initiator_socket_b</name>
      <anchorfile>a00038.html</anchorfile>
      <anchor>abb4b4c02e250f151e028f8ce4056ea96</anchor>
      <arglist>(const char *n=default_name())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_nb_transport_bw</name>
      <anchorfile>a00038.html</anchorfile>
      <anchor>a424ba011643fcbdb35079246c9d40544</anchor>
      <arglist>(MODULE *mod, sync_enum_type(MODULE::*cb)(transaction_type &amp;, phase_type &amp;, sc_core::sc_time &amp;))</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_invalidate_direct_mem_ptr</name>
      <anchorfile>a00038.html</anchorfile>
      <anchor>a9f920956dc437025d0af361a20133359</anchor>
      <arglist>(MODULE *mod, void(MODULE::*cb)(sc_dt::uint64, sc_dt::uint64))</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>default_name</name>
      <anchorfile>a00038.html</anchorfile>
      <anchor>a128daf21149d5ec34591bd8974ce65b6</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::simple_initiator_socket</name>
    <filename>a00037.html</filename>
    <templarg></templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg></templarg>
    <base>simple_initiator_socket_b&lt; MODULE, BUSWIDTH, TYPES &gt;</base>
    <member kind="function">
      <type></type>
      <name>simple_initiator_socket</name>
      <anchorfile>a00037.html</anchorfile>
      <anchor>a7b00387aa7a627fb3ec9448a9fe6a6d4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>simple_initiator_socket</name>
      <anchorfile>a00037.html</anchorfile>
      <anchor>a2dcd03139c6aba4bf3f54b9bc3aefd22</anchor>
      <arglist>(const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::simple_initiator_socket_optional</name>
    <filename>a00039.html</filename>
    <templarg></templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg></templarg>
    <base>simple_initiator_socket_b&lt; MODULE, BUSWIDTH, TYPES, sc_core::SC_ZERO_OR_MORE_BOUND &gt;</base>
    <member kind="function">
      <type></type>
      <name>simple_initiator_socket_optional</name>
      <anchorfile>a00039.html</anchorfile>
      <anchor>a3374f4b2fc2ee3f760488459fa188889</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>simple_initiator_socket_optional</name>
      <anchorfile>a00039.html</anchorfile>
      <anchor>a048a57f8fe38df47d982c70876d588ff</anchor>
      <arglist>(const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::simple_initiator_socket_tagged_b</name>
    <filename>a00041.html</filename>
    <templarg>MODULE</templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg>TYPES</templarg>
    <templarg>POL</templarg>
    <base>tlm_initiator_socket&lt; BUSWIDTH, TYPES, 1, POL &gt;</base>
    <base protection="protected">tlm_utils::simple_socket_base</base>
    <class kind="class">tlm_utils::simple_initiator_socket_tagged_b::process</class>
    <member kind="typedef">
      <type>TYPES::tlm_payload_type</type>
      <name>transaction_type</name>
      <anchorfile>a00041.html</anchorfile>
      <anchor>a09c1b54246a5b0e5721530c60c0e0770</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TYPES::tlm_phase_type</type>
      <name>phase_type</name>
      <anchorfile>a00041.html</anchorfile>
      <anchor>a8429ba9d9d3b0a0f773481c4d7337a9d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_sync_enum</type>
      <name>sync_enum_type</name>
      <anchorfile>a00041.html</anchorfile>
      <anchor>a548cc80d716449bda51e447fbfedec42</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_fw_transport_if&lt; TYPES &gt;</type>
      <name>fw_interface_type</name>
      <anchorfile>a00041.html</anchorfile>
      <anchor>ab7f09435912fa73fd7cdf97622fffd86</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_bw_transport_if&lt; TYPES &gt;</type>
      <name>bw_interface_type</name>
      <anchorfile>a00041.html</anchorfile>
      <anchor>aecfdf2f74891c59d1a7fdff381a5a8be</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_initiator_socket&lt; BUSWIDTH, TYPES, 1, POL &gt;</type>
      <name>base_type</name>
      <anchorfile>a00041.html</anchorfile>
      <anchor>a805bdf6bff887273dd1208d76c5f9a4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>simple_initiator_socket_tagged_b</name>
      <anchorfile>a00041.html</anchorfile>
      <anchor>a1b03ed8552fce379d074b98262a7a60c</anchor>
      <arglist>(const char *n=default_name())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_nb_transport_bw</name>
      <anchorfile>a00041.html</anchorfile>
      <anchor>a55f8d636f9a20c7a4ea90ad3e4b67ead</anchor>
      <arglist>(MODULE *mod, sync_enum_type(MODULE::*cb)(int, transaction_type &amp;, phase_type &amp;, sc_core::sc_time &amp;), int id)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_invalidate_direct_mem_ptr</name>
      <anchorfile>a00041.html</anchorfile>
      <anchor>a9944d4250e9eda42577b06ccc5777857</anchor>
      <arglist>(MODULE *mod, void(MODULE::*cb)(int, sc_dt::uint64, sc_dt::uint64), int id)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>default_name</name>
      <anchorfile>a00041.html</anchorfile>
      <anchor>a00bc3a938a6cc3ad3a4c7a88bd589aea</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::simple_initiator_socket_tagged</name>
    <filename>a00040.html</filename>
    <templarg></templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg></templarg>
    <base>simple_initiator_socket_tagged_b&lt; MODULE, BUSWIDTH, TYPES &gt;</base>
    <member kind="function">
      <type></type>
      <name>simple_initiator_socket_tagged</name>
      <anchorfile>a00040.html</anchorfile>
      <anchor>ad89f74f8ab2b2042a5ee84f1899ada68</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>simple_initiator_socket_tagged</name>
      <anchorfile>a00040.html</anchorfile>
      <anchor>ad3ff3f8d619ff3ecb40c359e291c7007</anchor>
      <arglist>(const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::simple_initiator_socket_tagged_optional</name>
    <filename>a00042.html</filename>
    <templarg></templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg></templarg>
    <base>simple_initiator_socket_tagged_b&lt; MODULE, BUSWIDTH, TYPES, sc_core::SC_ZERO_OR_MORE_BOUND &gt;</base>
    <member kind="function">
      <type></type>
      <name>simple_initiator_socket_tagged_optional</name>
      <anchorfile>a00042.html</anchorfile>
      <anchor>ad9cc35e7436758122fb65772a59fc424</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>simple_initiator_socket_tagged_optional</name>
      <anchorfile>a00042.html</anchorfile>
      <anchor>af40275eff5aa299f75feaf8c035a18b0</anchor>
      <arglist>(const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::simple_target_socket_b</name>
    <filename>a00045.html</filename>
    <templarg>MODULE</templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg>TYPES</templarg>
    <templarg>POL</templarg>
    <base>tlm_target_socket&lt; BUSWIDTH, TYPES, 1, POL &gt;</base>
    <base protection="protected">tlm_utils::simple_socket_base</base>
    <class kind="class">tlm_utils::simple_target_socket_b::bw_process</class>
    <class kind="class">tlm_utils::simple_target_socket_b::fw_process</class>
    <member kind="typedef">
      <type>TYPES::tlm_payload_type</type>
      <name>transaction_type</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>a5602f73176a03128128c314b4671178b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TYPES::tlm_phase_type</type>
      <name>phase_type</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>a7d268470c3856d1371bfbd34f50bbd47</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_sync_enum</type>
      <name>sync_enum_type</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>aa4f964aef6013dee8f3d017fff63d548</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_fw_transport_if&lt; TYPES &gt;</type>
      <name>fw_interface_type</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>a9ffa83a528f9e2483e3de8db42668712</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_bw_transport_if&lt; TYPES &gt;</type>
      <name>bw_interface_type</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>a17f5b4bd8614efd68c1f4a1ac62964e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_target_socket&lt; BUSWIDTH, TYPES, 1, POL &gt;</type>
      <name>base_type</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>abd15840d60961c19f950c8a2f2c52fe4</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>simple_target_socket_b</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>a2c268f5934ec7b4110855e1caf2ab128</anchor>
      <arglist>(const char *n=default_name())</arglist>
    </member>
    <member kind="function">
      <type>tlm::tlm_bw_transport_if&lt; TYPES &gt; *</type>
      <name>operator-&gt;</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>a7cc9fcd8dbde62139a7e61b437240c21</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_nb_transport_fw</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>a6ae2e0bb8cae1a50cf71d8c574bfc270</anchor>
      <arglist>(MODULE *mod, sync_enum_type(MODULE::*cb)(transaction_type &amp;, phase_type &amp;, sc_core::sc_time &amp;))</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_b_transport</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>a5950af6948f742dcc59077d908f5e312</anchor>
      <arglist>(MODULE *mod, void(MODULE::*cb)(transaction_type &amp;, sc_core::sc_time &amp;))</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_transport_dbg</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>a9f808a54e845b6a131a346c9d3f5cae7</anchor>
      <arglist>(MODULE *mod, unsigned int(MODULE::*cb)(transaction_type &amp;))</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_get_direct_mem_ptr</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>a78897eb2f00f13156ae9d61c9b870acc</anchor>
      <arglist>(MODULE *mod, bool(MODULE::*cb)(transaction_type &amp;, tlm::tlm_dmi &amp;))</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>default_name</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>a7089565d92090e5f181e8a31530c3675</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>start_of_simulation</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>a52cbb697c1c6f8181ae4f34b481c6915</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>fw_process</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>af8e4ac1acc1a93c6fa01e40d5df17c3b</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>bw_process</name>
      <anchorfile>a00045.html</anchorfile>
      <anchor>a3cb722031862b7dea13b51ccbbf96b1e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::simple_target_socket</name>
    <filename>a00044.html</filename>
    <templarg></templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg></templarg>
    <base>simple_target_socket_b&lt; MODULE, BUSWIDTH, TYPES &gt;</base>
    <member kind="function">
      <type></type>
      <name>simple_target_socket</name>
      <anchorfile>a00044.html</anchorfile>
      <anchor>a41395d8676fe2f2ad6614efe1a6c9fb9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>simple_target_socket</name>
      <anchorfile>a00044.html</anchorfile>
      <anchor>a245817b821e1018665f86d525b712be1</anchor>
      <arglist>(const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::simple_target_socket_optional</name>
    <filename>a00046.html</filename>
    <templarg></templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg></templarg>
    <base>simple_target_socket_b&lt; MODULE, BUSWIDTH, TYPES, sc_core::SC_ZERO_OR_MORE_BOUND &gt;</base>
    <member kind="function">
      <type></type>
      <name>simple_target_socket_optional</name>
      <anchorfile>a00046.html</anchorfile>
      <anchor>a0c1ad2841aedfd185400da7787319169</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>simple_target_socket_optional</name>
      <anchorfile>a00046.html</anchorfile>
      <anchor>a65793998ea41d6f2b34de8b27c3b3112</anchor>
      <arglist>(const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::simple_target_socket_tagged_b</name>
    <filename>a00048.html</filename>
    <templarg>MODULE</templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg>TYPES</templarg>
    <templarg>POL</templarg>
    <base>tlm_target_socket&lt; BUSWIDTH, TYPES, 1, POL &gt;</base>
    <base protection="protected">tlm_utils::simple_socket_base</base>
    <class kind="class">tlm_utils::simple_target_socket_tagged_b::bw_process</class>
    <class kind="class">tlm_utils::simple_target_socket_tagged_b::fw_process</class>
    <member kind="typedef">
      <type>TYPES::tlm_payload_type</type>
      <name>transaction_type</name>
      <anchorfile>a00048.html</anchorfile>
      <anchor>a936c976117254ea42da0a7c3fce709ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TYPES::tlm_phase_type</type>
      <name>phase_type</name>
      <anchorfile>a00048.html</anchorfile>
      <anchor>a975a6f358464288d5b161189bf86deb2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_sync_enum</type>
      <name>sync_enum_type</name>
      <anchorfile>a00048.html</anchorfile>
      <anchor>a91c3803a16e651d10d9bc5848c159680</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_fw_transport_if&lt; TYPES &gt;</type>
      <name>fw_interface_type</name>
      <anchorfile>a00048.html</anchorfile>
      <anchor>abc4c67911bc1f34a52613e9fbeca8f24</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_bw_transport_if&lt; TYPES &gt;</type>
      <name>bw_interface_type</name>
      <anchorfile>a00048.html</anchorfile>
      <anchor>a7f9c67f45bbf7b1fbb2a433046b71d2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>tlm::tlm_target_socket&lt; BUSWIDTH, TYPES, 1, POL &gt;</type>
      <name>base_type</name>
      <anchorfile>a00048.html</anchorfile>
      <anchor>a49f31061e6b87f42d7c566c6381d8427</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>simple_target_socket_tagged_b</name>
      <anchorfile>a00048.html</anchorfile>
      <anchor>ab22c2caba82402b7bc7969d90d43ec44</anchor>
      <arglist>(const char *n=default_name())</arglist>
    </member>
    <member kind="function">
      <type>tlm::tlm_bw_transport_if&lt; TYPES &gt; *</type>
      <name>operator-&gt;</name>
      <anchorfile>a00048.html</anchorfile>
      <anchor>a8722df276d6dceabe6ceaa40d1cc9746</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_nb_transport_fw</name>
      <anchorfile>a00048.html</anchorfile>
      <anchor>a0969a1260cb220b25988f9c17184dfd1</anchor>
      <arglist>(MODULE *mod, sync_enum_type(MODULE::*cb)(int id, transaction_type &amp;, phase_type &amp;, sc_core::sc_time &amp;), int id)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_b_transport</name>
      <anchorfile>a00048.html</anchorfile>
      <anchor>ad9825dd09151893edb2f20ef46022f7a</anchor>
      <arglist>(MODULE *mod, void(MODULE::*cb)(int id, transaction_type &amp;, sc_core::sc_time &amp;), int id)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_transport_dbg</name>
      <anchorfile>a00048.html</anchorfile>
      <anchor>a3373896f5ba43004e4fa7e61187abf8f</anchor>
      <arglist>(MODULE *mod, unsigned int(MODULE::*cb)(int id, transaction_type &amp;), int id)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>register_get_direct_mem_ptr</name>
      <anchorfile>a00048.html</anchorfile>
      <anchor>a8076a060a6d4b2cd09936235cafed7cd</anchor>
      <arglist>(MODULE *mod, bool(MODULE::*cb)(int id, transaction_type &amp;, tlm::tlm_dmi &amp;), int id)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const char *</type>
      <name>default_name</name>
      <anchorfile>a00048.html</anchorfile>
      <anchor>ad557379cc4945ee570cd673f9d3ea6d9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>start_of_simulation</name>
      <anchorfile>a00048.html</anchorfile>
      <anchor>a33fafacae2cf4d99e8645542e6bb227c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>fw_process</name>
      <anchorfile>a00048.html</anchorfile>
      <anchor>af8e4ac1acc1a93c6fa01e40d5df17c3b</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>bw_process</name>
      <anchorfile>a00048.html</anchorfile>
      <anchor>a3cb722031862b7dea13b51ccbbf96b1e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::simple_target_socket_tagged</name>
    <filename>a00047.html</filename>
    <templarg></templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg></templarg>
    <base>simple_target_socket_tagged_b&lt; MODULE, BUSWIDTH, TYPES &gt;</base>
    <member kind="function">
      <type></type>
      <name>simple_target_socket_tagged</name>
      <anchorfile>a00047.html</anchorfile>
      <anchor>a709e11894992b07548df6c3d734f3c0e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>simple_target_socket_tagged</name>
      <anchorfile>a00047.html</anchorfile>
      <anchor>adb841a9e5c3adefd001f1171f7b94473</anchor>
      <arglist>(const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::simple_target_socket_tagged_optional</name>
    <filename>a00049.html</filename>
    <templarg></templarg>
    <templarg>BUSWIDTH</templarg>
    <templarg></templarg>
    <base>simple_target_socket_tagged_b&lt; MODULE, BUSWIDTH, TYPES, sc_core::SC_ZERO_OR_MORE_BOUND &gt;</base>
    <member kind="function">
      <type></type>
      <name>simple_target_socket_tagged_optional</name>
      <anchorfile>a00049.html</anchorfile>
      <anchor>abb996b820ed964ff11ea80f17c6d4413</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>simple_target_socket_tagged_optional</name>
      <anchorfile>a00049.html</anchorfile>
      <anchor>a339bbb335bc4babf3406a8fcb848a09d</anchor>
      <arglist>(const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tlm_utils::tlm_quantumkeeper</name>
    <filename>a00110.html</filename>
    <member kind="function">
      <type></type>
      <name>tlm_quantumkeeper</name>
      <anchorfile>a00110.html</anchorfile>
      <anchor>a35858eac6c535107bf7c7142e7dda9c0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~tlm_quantumkeeper</name>
      <anchorfile>a00110.html</anchorfile>
      <anchor>ad4ce9ad2cb14fc12027cea162c67d7a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>inc</name>
      <anchorfile>a00110.html</anchorfile>
      <anchor>a74fdd20ba60d97dfcc0b732d6a12492b</anchor>
      <arglist>(const sc_core::sc_time &amp;t)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>set</name>
      <anchorfile>a00110.html</anchorfile>
      <anchor>a4f4aab4e00b24361bff36aa5937af9ac</anchor>
      <arglist>(const sc_core::sc_time &amp;t)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>need_sync</name>
      <anchorfile>a00110.html</anchorfile>
      <anchor>a118c9663fe60e4cea19300967d7665a1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>sync</name>
      <anchorfile>a00110.html</anchorfile>
      <anchor>a531e23d9764c696b123e04fc54c20b10</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_and_sync</name>
      <anchorfile>a00110.html</anchorfile>
      <anchor>a3f81b5a7465df0888e33f56d577415c0</anchor>
      <arglist>(const sc_core::sc_time &amp;t)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>reset</name>
      <anchorfile>a00110.html</anchorfile>
      <anchor>ae458d08fba65c7b370093f758c7b97b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_time</type>
      <name>get_current_time</name>
      <anchorfile>a00110.html</anchorfile>
      <anchor>a79d67c356b13a4ebcb583565e0770c7c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual sc_core::sc_time</type>
      <name>get_local_time</name>
      <anchorfile>a00110.html</anchorfile>
      <anchor>a1dfa3d1256255335c730707203dfa283</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>set_global_quantum</name>
      <anchorfile>a00110.html</anchorfile>
      <anchor>a593a827007f2f4cc8494e35a2e715ce3</anchor>
      <arglist>(const sc_core::sc_time &amp;t)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static const sc_core::sc_time &amp;</type>
      <name>get_global_quantum</name>
      <anchorfile>a00110.html</anchorfile>
      <anchor>a3e21817fdd18bdcb435d2c0b39990a07</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual sc_core::sc_time</type>
      <name>compute_local_quantum</name>
      <anchorfile>a00110.html</anchorfile>
      <anchor>af40c6531805e3056969defe452bc038b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>sc_core::sc_time</type>
      <name>m_next_sync_point</name>
      <anchorfile>a00110.html</anchorfile>
      <anchor>a1e0c04f47473f073cc8e2d5aaf65c462</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>sc_core::sc_time</type>
      <name>m_local_time</name>
      <anchorfile>a00110.html</anchorfile>
      <anchor>ab0854e0289159947c444c25204b3c79e</anchor>
      <arglist></arglist>
    </member>
  </compound>
</tagfile>
