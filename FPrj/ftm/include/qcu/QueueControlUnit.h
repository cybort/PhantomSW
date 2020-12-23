#ifndef _VOQ_MANAGER_H_
#define _VOQ_MANAGER_H_

#include "CreditGenerator.h"
#include "CreditInfo.h"
#include "CreditManager.h"
#include "DeQueueCommand.h"
#include "DeQueueReport.h"
#include "EnQueueReport.h"
#include "FlowStatusMessage.h"
#include "QueueManager.h"
#include "config.h"
#include "pd.h"

SC_MODULE(QueueControlUnit)
{
private:
    sc_signal<DeQueueCommand> dequeue_command;
    sc_signal<bool> dequeue_command_valid;
    sc_signal<EnQueueReport> enqueue_report;
    sc_signal<bool> enqueue_report_valid;
    sc_signal<DeQueueReport> dequeue_report_to_cm;
    sc_signal<bool> dequeue_report_to_cm_valid;
    // sc_signal<FlowStatusMessage> flow_status_message;
    // sc_signal<bool> flow_status_message_valid;
    // sc_signal<CreditInfo> credit_info;
    // sc_signal<bool> credit_info_valid;

public:
    sc_in<bool> clk;
    sc_in<data_bus> packet_in;
    sc_in<bool> packet_in_valid;
    sc_in<bool> packet_in_sop;
    sc_in<bool> packet_in_eop;
    sc_in<int> packet_in_mod;

    sc_in<pd> packet_descriptor_in;
    sc_in<bool> packet_descriptor_in_valid;

    sc_in<unsigned> addr_in;
    sc_in<bool> addr_in_valid;

    sc_in<FlowStatusMessage> flow_status_message_in;
    sc_in<bool> flow_status_message_in_valid;

    sc_in<CreditInfo> credit_info_in;
    sc_in<bool> credit_info_in_valid;

    sc_out<unsigned> addr_out;
    sc_out<bool> addr_out_valid;

    sc_out<bool> packet_descriptor_fc;
    sc_out<bool> packet_read;

    sc_out<data_bus> packet_out;
    sc_out<bool> packet_out_valid;
    sc_out<bool> packet_out_sop;
    sc_out<bool> packet_out_eop;
    sc_out<int> packet_out_mod;

    sc_out<FlowStatusMessage> flow_status_message_out;
    sc_out<bool> flow_status_message_out_valid;

    sc_out<CreditInfo> credit_info_out;
    sc_out<bool> credit_info_out_valid;

    sc_out<DeQueueReport> dequeue_report_to_cavd_out;
    sc_out<bool> dequeue_report_to_cavd_out_valid;

    QueueManager queue_manager;
    CreditManager credit_manager;
    CreditGenerator credit_generator;

    SC_CTOR(QueueControlUnit) : queue_manager("qm"), credit_manager("cm"), credit_generator("cg")
    {
        /*queue manager*/
        queue_manager.clk(clk);
        queue_manager.packet_in(packet_in);
        queue_manager.packet_in_sop(packet_in_sop);
        queue_manager.packet_in_eop(packet_in_eop);
        queue_manager.packet_in_valid(packet_in_valid);
        queue_manager.packet_in_mod(packet_in_mod);
        queue_manager.packet_read(packet_read);

        queue_manager.packet_descriptor_in(packet_descriptor_in);
        queue_manager.packet_descriptor_in_valid(packet_descriptor_in_valid);
        queue_manager.packet_descriptor_fc(packet_descriptor_fc);

        queue_manager.packet_out(packet_out);
        queue_manager.packet_out_sop(packet_out_sop);
        queue_manager.packet_out_eop(packet_out_eop);
        queue_manager.packet_out_valid(packet_out_valid);
        queue_manager.packet_out_mod(packet_out_mod);

        queue_manager.addr_in(addr_in);
        queue_manager.addr_in_valid(addr_in_valid);

        queue_manager.addr_out(addr_out);
        queue_manager.addr_out_valid(addr_out_valid);

        queue_manager.enqueue_report_out(enqueue_report);
        queue_manager.enqueue_report_out_valid(enqueue_report_valid);

        queue_manager.dequeue_command_in(dequeue_command);
        queue_manager.dequeue_command_in_valid(dequeue_command_valid);

        queue_manager.dequeue_report_to_cm_out(dequeue_report_to_cm);
        queue_manager.dequeue_report_to_cm_out_valid(dequeue_report_to_cm_valid);

        queue_manager.dequeue_report_to_cavd_out(dequeue_report_to_cavd_out);
        queue_manager.dequeue_report_to_cavd_out_valid(dequeue_report_to_cavd_out_valid);

        queue_manager.init_dest_table();

        /*Credit Manager*/
        credit_manager.clk(clk);
        credit_manager.enqueue_report(enqueue_report);
        credit_manager.enqueue_report_valid(enqueue_report_valid);

        credit_manager.dequeue_report(dequeue_report_to_cm);
        credit_manager.dequeue_report_valid(dequeue_report_to_cm_valid);

        credit_manager.dequeue_command(dequeue_command);
        credit_manager.dequeue_command_valid(dequeue_command_valid);

        credit_manager.flow_status_message_out(flow_status_message_out);
        credit_manager.flow_status_message_out_valid(flow_status_message_out_valid);

        credit_manager.credit_info_in(credit_info_in);
        credit_manager.credit_info_in_valid(credit_info_in_valid);

        /*Credit Generator*/
        credit_generator.clk(clk);
        credit_generator.credit_info_out(credit_info_out);
        credit_generator.credit_info_out_valid(credit_info_out_valid);

        credit_generator.flow_status_message_in(flow_status_message_in);
        credit_generator.flow_status_message_in_valid(flow_status_message_in_valid);
    }
};

#endif
