/*
 * @Author: Zhao Yunpeng
 * @Date: 2020-11-30 09:20:25
 * @LastEditors: Zhao Yunpeng
 * @LastEditTime: 2020-12-26 18:04:40
 * @Description: file content
 */
#include "CreditGenerator.h"

void CreditGenerator::generate()
{
    if (flow_status_message_in_valid.read())
    {
        FlowStatusMessage message = flow_status_message_in.read();
        unsigned flow_id = -1;
        unsigned dest_tm_id = -1;
        FlowStatus status;
        try
        {
            flow_id = message.get_flow_id();
            status = message.get_status();
            dest_tm_id = message.get_src_tm_id();
            creditInfo_local.set_flow_id(flow_id);
            creditInfo_local.set_dest_tm_id(dest_tm_id);
            creditInfo_local.set_src_tm_id(_TM_ID_);
        }
        catch (Exception & e)
        {
            std::cout << "Exception:"
                      << " " << e.ToString() << std::endl
                      << "Stack:"
                      << " " << e.Stack() << std::endl;
        }
        switch (status)
        {
        case FLOW_STATUS_MESSAGE_REQUIRE_OFF:
            creditInfo_local.set_credit(CREDIT_INFO_CREDIT_OFF);
            log.prefix() << "dest_tm_id: " << dest_tm_id << "flow_id : " << flow_id << ", "
                         << "credit : " << CREDIT_INFO_CREDIT_OFF << endl;
            break;
        case FLOW_STATUS_MESSAGE_REQUIRE_SLOW:
            creditInfo_local.set_credit(CREDIT_INFO_CREDIT_SLOW);
            log.prefix() << "dest_tm_id: " << dest_tm_id << "flow_id : " << flow_id << ", "
                         << "credit : " << CREDIT_INFO_CREDIT_SLOW << endl;
            break;
        case FLOW_STATUS_MESSAGE_REQUIRE_NORMAL:
            creditInfo_local.set_credit(CREDIT_INFO_CREDIT_NORMAL);
            log.prefix() << "dest_tm_id: " << dest_tm_id << "flow_id : " << flow_id << ", "
                         << "credit : " << CREDIT_INFO_CREDIT_NORMAL << endl;
            break;
        default:
            creditInfo_local.set_credit(CREDIT_INFO_CREDIT_OFF);
        }
        credit_info_out_valid.write(true);
        credit_info_out.write(creditInfo_local);
    }
    else
    {
        credit_info_out_valid.write(false);
    }
}
