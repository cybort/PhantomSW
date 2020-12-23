#include "CreditGrantConverter.h"
#include "port.h"

void CreditGrantConverter::convert()
{
    while (true)
    {
        cell_credit c;
        if (true == valid_credit_info.read())
        {
            CreditInfo current_grant(credit_info.read());

            c.type = CellType::Credit;
            c.flow_id(current_grant.get_flow_id());
            c.dest_id(current_grant.get_dest_tm_id());
            c.source_id(SRC_TM_ID);

            cell_grant.write(c);
            valid_cell_grant.write(true);
            log.prefix() << "credit grant flow " << c.flow_id() << std::endl;
        }
        else
        {
            valid_cell_grant.write(false);
        }
        wait();
    }
}