/*
 * @Description:
 * @Author: f21538
 * @Date: 2021-01-21 14:32:14
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-23 11:35:17
 */
#include "testbench.h"

void testbench::generate()
{
    FlowStatusMessage current_flow;
    CreditInfo current_credit;
    int recv_num = 0;
    sc_bv<LINK_NUM> link = std::string(LINK_NUM, '1').c_str();

    for (int i = 0; i < 10; i++)
    {
        current_flow.set_flow_id(i);
        current_flow.set_dest_tm_id(i);
        current_flow.set_src_tm_id(0);
        current_flow.set_status(CreditRequestStatus::STATUS_NORMAL);
        flow_status_message_out.write(current_flow);
        flow_status_message_out_valid.write(true);
        log.prefix() << "write flow sts srcid " << current_flow.get_src_tm_id() << " flowid "
                     << current_flow.get_flow_id() << std::endl;
        if (credit_info_in_valid.read() == true)
        {
            current_credit = credit_info_in.read();
            recv_num++;
            log.prefix() << "recv credit " << current_credit.get_credit() << " send to tm "
                         << current_credit.get_dest_tm_id() << " flow " << current_credit.get_flow_id() << std::endl;
        }

        link_valid_out.write(link);
        wait();
    }
    for (int i = 0; i < 10; i++)
    {
        current_flow.set_flow_id(i);
        current_flow.set_dest_tm_id(i);
        current_flow.set_src_tm_id(0);
        current_flow.set_status(CreditRequestStatus::STATUS_OFF);
        flow_status_message_out.write(current_flow);
        flow_status_message_out_valid.write(true);
        log.prefix() << "write flow sts srcid " << current_flow.get_src_tm_id() << " flowid "
                     << current_flow.get_flow_id() << std::endl;
        if (credit_info_in_valid.read() == true)
        {
            current_credit = credit_info_in.read();
            recv_num++;
            log.prefix() << "recv credit " << current_credit.get_credit() << " send to tm "
                         << current_credit.get_dest_tm_id() << " flow " << current_credit.get_flow_id() << std::endl;
        }

        link_valid_out.write(link);
        wait();
    }
    flow_status_message_out_valid.write(false);

    for (int i = 0; i < 10; i++)
    {
        if (credit_info_in_valid.read() == true)
        {
            current_credit = credit_info_in.read();
            recv_num++;
            log.prefix() << "recv credit " << current_credit.get_credit() << " send to tm "
                         << current_credit.get_dest_tm_id() << " flow " << current_credit.get_flow_id() << std::endl;
        }
        link_valid_out.write(link);
        wait();
    }
    sc_stop();
}
