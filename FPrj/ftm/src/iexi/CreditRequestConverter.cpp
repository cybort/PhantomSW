/*
 * @Description:
 * @Author: f21538
 * @Date: 2020-12-15 17:48:52
 * @LastEditors: f21538
 * @LastEditTime: 2020-12-26 15:19:00
 */
#include "CreditRequestConverter.h"
#include "port.h"

void CreditRequestConverter::convert()
{
    while (true)
    {
        cell_flowsts c;
        if (true == valid_flow_status.read())
        {
            FlowStatusMessage current_request(flow_status.read());

            c.type = CellType::FlowSts;
            c.flow_id(current_request.get_flow_id());
            c.request(current_request.get_status());
            c.request_id(current_seq);
            c.dest_id(current_request.get_dest_tm_id());
            c.source_id(SRC_TM_ID);
            if (SRC_TM_ID == 0) c.dest_id(1);
            else c.dest_id(0);

            cell_request.write(c);
            valid_cell_request.write(true);
            current_seq = (current_seq + 1) % INT_MAX;
        }
        else
        {
            valid_cell_request.write(false);
        }

        wait();
    }
}
