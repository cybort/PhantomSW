/*
 * @Author: your name
 * @Date: 2021-01-20 16:43:55
 * @LastEditors: f21538
 * @LastEditTime: 2021-01-23 14:38:40
 * @Description: file content
 */
#ifndef _VOQ_MANAGER_H_
#define _VOQ_MANAGER_H_

#include "CreditGenerator.h"
#include "CreditInfo.h"
#include "CreditManager.h"
#include "DeQueueCommand.h"
#include "DeQueueProcessor.h"
#include "DeQueueReport.h"
#include "EnQueueProcessor.h"
#include "EnQueueReport.h"
#include "FlowStatusMessage.h"
#include "QueueListManager.h"
#include "QueueSch.h"
#include "config.h"
#include "pd.h"

SC_MODULE(QueueControlUnit)
{
private:
    /*EnQueueProcessor & QueueListManager*/
    sc_signal<pd> packet_descriptor_en_queue_procssor_to_queue_list_manager;
    sc_signal<bool> packet_descriptor_valid_en_queue_procssor_to_queue_list_manager;
    sc_signal<bool> write_packet_descriptor_complete_signal;
    /*EnQueueProcessor & QueueSch*/
    sc_signal<EnQueueReport> en_queue_report_en_queue_processor_to_queue_sch;
    sc_signal<bool> en_queue_report_valid_en_queue_processor_to_queue_sch;
    /*EnQueueProcessor & CreditManager*/
    sc_signal<EnQueueReport> en_queue_report_en_queue_processor_to_credit_manager;
    sc_signal<bool> en_queue_report_valid_en_queue_processor_to_credit_manager;
    /*QueueSch & CreditManager*/
    sc_signal<CreditInfo> credit_info_credit_manager_to_queue_sch;
    sc_signal<bool> credit_info_valid_credit_manager_to_queue_sch;
    /*DeQueueProcessor & QueueListManager*/
    sc_signal<unsigned> de_queue_flow_id_de_queue_processor_to_queue_list_manager;
    sc_signal<bool> de_queue_flow_id_valid_de_queue_processor_to_queue_list_manager;
    sc_signal<unsigned> de_queue_flow_id_release_de_queue_processor_to_queue_list_manager;
    sc_signal<bool> de_queue_flow_id_release_valid_de_queue_processor_to_queue_list_manager;
    sc_signal<pd> packet_descriptor_queue_list_manager_to_de_queue_processor;
    sc_signal<bool> packet_descriptor_valid_queue_list_manager_to_de_queue_processor;
    /*DeQueueProcessor & CreditManager*/
    sc_signal<DeQueueReport> de_queue_report_de_queue_processor_to_credit_manager;
    sc_signal<bool> de_queue_report_valid_de_queue_processor_to_credit_manager;
    /*DeQueueProcessor & QueueSch*/
    sc_signal<DeQueueCommand> de_queue_command_queue_sch_to_de_queue_processor;
    sc_signal<bool> de_queue_command_valid_queue_sch_to_de_queue_processor;
    sc_signal<DeQueueReport> de_queue_report_de_queue_processor_to_queue_sch;
    sc_signal<bool> de_queue_report_valid_de_queue_processor_to_queue_sch;

    CreditManager credit_manager;
    // CreditGenerator credit_generator;
    QueueSch queue_scheduler;

    EnQueueProcessor en_queue_processor;
    DeQueueProcessor de_queue_processor;
    QueueListManager queue_list_manager;

public:
    sc_in<bool> clk;
    /*EnQueueProcessor*/
    sc_in<data_bus> packet_in;
    sc_in<bool> packet_in_valid;
    sc_in<bool> packet_in_sop;
    sc_in<bool> packet_in_eop;
    sc_in<int> packet_in_mod;
    sc_in<pd> packet_descriptor_in;
    sc_in<bool> packet_descriptor_in_valid;
    sc_in<bool> write_packet_complete_signal_in;
    sc_out<data_bus> packet_out;
    sc_out<bool> packet_out_valid;
    sc_out<bool> packet_out_sop;
    sc_out<bool> packet_out_eop;
    sc_out<int> packet_out_mod;
    sc_out<bool> packet_read;
    sc_out<bool> packet_descriptor_fc;
    sc_out<unsigned> write_logic_addr_out;
    /*DeQueueProcessor*/
    sc_in<bool> read_packet_complete_signal_in;
    sc_out<unsigned> read_logic_addr_out;
    sc_out<bool> read_logic_addr_out_valid;
    sc_out<DeQueueReport> de_queue_report_out;
    sc_out<bool> de_queue_report_out_valid;
    /*CreditManager*/
    sc_in<CreditInfo> credit_info_in;
    sc_in<bool> credit_info_in_valid;
    sc_out<FlowStatusMessage> flow_status_message_out;
    sc_out<bool> flow_status_message_out_valid;
    /*CreditGenerator*/
    // sc_in<FlowStatusMessage> flow_status_message_in;
    // sc_in<bool> flow_status_message_in_valid;
    // sc_out<CreditInfo> credit_info_out;
    // sc_out<bool> credit_info_out_valid;

    SC_CTOR(QueueControlUnit)
        : en_queue_processor("en_queue_processor"), de_queue_processor("de_queue_processor"),
          queue_scheduler("queue_scheduler"), queue_list_manager("queue_list_manager"), credit_manager("credit_manager")
    {
        /*Internal Signal*/
        /*-EnQueueProcessor-*/

        en_queue_processor.packet_descriptor_out(packet_descriptor_en_queue_procssor_to_queue_list_manager);
        en_queue_processor.packet_descriptor_out_valid(packet_descriptor_valid_en_queue_procssor_to_queue_list_manager);
        en_queue_processor.enqueue_report_to_queue_sch_out(en_queue_report_en_queue_processor_to_queue_sch);
        en_queue_processor.enqueue_report_to_queue_sch_out_valid(en_queue_report_valid_en_queue_processor_to_queue_sch);
        en_queue_processor.enqueue_report_to_credit_manager_out(en_queue_report_en_queue_processor_to_credit_manager);
        en_queue_processor.enqueue_report_to_credit_manager_out_valid(
            en_queue_report_valid_en_queue_processor_to_credit_manager);
        en_queue_processor.write_packet_descriptor_complete_signal_in(write_packet_descriptor_complete_signal);

        /*-QueueListManager-*/

        queue_list_manager.packet_descriptor_in(packet_descriptor_en_queue_procssor_to_queue_list_manager);
        queue_list_manager.packet_descriptor_in_valid(packet_descriptor_valid_en_queue_procssor_to_queue_list_manager);
        queue_list_manager.save_packet_descriptor_complete_signal_out(write_packet_descriptor_complete_signal);
        queue_list_manager.flow_id_in(de_queue_flow_id_de_queue_processor_to_queue_list_manager);
        queue_list_manager.flow_id_in_valid(de_queue_flow_id_valid_de_queue_processor_to_queue_list_manager);
        queue_list_manager.flow_id_release_in(de_queue_flow_id_release_de_queue_processor_to_queue_list_manager);
        queue_list_manager.flow_id_release_in_valid(
            de_queue_flow_id_release_valid_de_queue_processor_to_queue_list_manager);
        queue_list_manager.packet_descriptor_out(packet_descriptor_queue_list_manager_to_de_queue_processor);
        queue_list_manager.packet_descriptor_out_valid(
            packet_descriptor_valid_queue_list_manager_to_de_queue_processor);

        /*-DeQueueProcessor-*/

        de_queue_processor.de_queue_flow_id_out(de_queue_flow_id_de_queue_processor_to_queue_list_manager);
        de_queue_processor.de_queue_flow_id_out_valid(de_queue_flow_id_valid_de_queue_processor_to_queue_list_manager);
        de_queue_processor.de_queue_flow_id_release_out(
            de_queue_flow_id_release_de_queue_processor_to_queue_list_manager);
        de_queue_processor.de_queue_flow_id_release_out_valid(
            de_queue_flow_id_release_valid_de_queue_processor_to_queue_list_manager);
        de_queue_processor.packet_descriptor_in(packet_descriptor_queue_list_manager_to_de_queue_processor);
        de_queue_processor.packet_descriptor_in_valid(packet_descriptor_valid_queue_list_manager_to_de_queue_processor);
        de_queue_processor.de_queue_report_out_to_queue_sch(de_queue_report_de_queue_processor_to_queue_sch);
        de_queue_processor.de_queue_report_out_to_queue_sch_valid(
            de_queue_report_valid_de_queue_processor_to_queue_sch);
        de_queue_processor.de_queue_report_out_to_credit_manager(de_queue_report_de_queue_processor_to_credit_manager);
        de_queue_processor.de_queue_report_out_to_credit_manager_valid(
            de_queue_report_valid_de_queue_processor_to_credit_manager);
        de_queue_processor.de_queue_command_in(de_queue_command_queue_sch_to_de_queue_processor);
        de_queue_processor.de_queue_command_in_valid(de_queue_command_valid_queue_sch_to_de_queue_processor);

        /*-QueueSch-*/

        queue_scheduler.en_queue_report_in(en_queue_report_en_queue_processor_to_queue_sch);
        queue_scheduler.en_queue_report_in_valid(en_queue_report_valid_en_queue_processor_to_queue_sch);
        queue_scheduler.de_queue_report_in(de_queue_report_de_queue_processor_to_queue_sch);
        queue_scheduler.de_queue_report_in_valid(de_queue_report_valid_de_queue_processor_to_queue_sch);
        queue_scheduler.de_queue_command_out(de_queue_command_queue_sch_to_de_queue_processor);
        queue_scheduler.de_queue_command_out_valid(de_queue_command_valid_queue_sch_to_de_queue_processor);
        queue_scheduler.credit_info_in(credit_info_credit_manager_to_queue_sch);
        queue_scheduler.credit_info_in_valid(credit_info_valid_credit_manager_to_queue_sch);

        /*-CreditManager-*/

        credit_manager.en_queue_report_in(en_queue_report_en_queue_processor_to_credit_manager);
        credit_manager.en_queue_report_in_valid(en_queue_report_valid_en_queue_processor_to_credit_manager);
        credit_manager.credit_info_out(credit_info_credit_manager_to_queue_sch);
        credit_manager.credit_info_out_valid(credit_info_valid_credit_manager_to_queue_sch);
        credit_manager.de_queue_report_in(de_queue_report_de_queue_processor_to_credit_manager);
        credit_manager.de_queue_report_in_valid(de_queue_report_valid_de_queue_processor_to_credit_manager);

        /*Outter Signal*/
        /*clk*/

        en_queue_processor.clk(clk);
        credit_manager.clk(clk);
        queue_scheduler.clk(clk);
        de_queue_processor.clk(clk);
        queue_list_manager.clk(clk);
        // credit_generator.clk(clk);

        /*-EnQueueProcessor-*/

        en_queue_processor.packet_in(packet_in);
        en_queue_processor.packet_in_valid(packet_in_valid);
        en_queue_processor.packet_in_sop(packet_in_sop);
        en_queue_processor.packet_in_eop(packet_in_eop);
        en_queue_processor.packet_in_mod(packet_in_mod);
        en_queue_processor.packet_descriptor_in(packet_descriptor_in);
        en_queue_processor.packet_descriptor_in_valid(packet_descriptor_in_valid);
        en_queue_processor.write_packet_complete_signal_in(write_packet_complete_signal_in);
        en_queue_processor.packet_out(packet_out);
        en_queue_processor.packet_out_valid(packet_out_valid);
        en_queue_processor.packet_out_sop(packet_out_sop);
        en_queue_processor.packet_out_eop(packet_out_eop);
        en_queue_processor.packet_out_mod(packet_out_mod);
        en_queue_processor.packet_read(packet_read);
        en_queue_processor.packet_descriptor_fc(packet_descriptor_fc);
        en_queue_processor.logic_addr_out(write_logic_addr_out);

        /*-DeQueueProcessor-*/

        de_queue_processor.read_packet_complete_signal_in(read_packet_complete_signal_in);
        de_queue_processor.logic_addr_out(read_logic_addr_out);
        de_queue_processor.logic_addr_out_valid(read_logic_addr_out_valid);
        de_queue_processor.de_queue_report_out_to_cavd(de_queue_report_out);
        de_queue_processor.de_queue_report_out_to_cavd_valid(de_queue_report_out_valid);

        /*-CreditManager-*/

        credit_manager.credit_info_in(credit_info_in);
        credit_manager.credit_info_in_valid(credit_info_in_valid);
        credit_manager.flow_status_message_out(flow_status_message_out);
        credit_manager.flow_status_message_out_valid(flow_status_message_out_valid);

        /*-CreditGenerator-*/

        // credit_generator.credit_info_out(credit_info_out);
        // credit_generator.credit_info_out_valid(credit_info_out_valid);
        // credit_generator.flow_status_message_in(flow_status_message_in);
        // credit_generator.flow_status_message_in_valid(flow_status_message_in_valid);
    }
};

#endif
