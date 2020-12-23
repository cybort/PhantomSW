#ifndef _DE_QUEUE_COMMAND_H
#define _DE_QUEUE_COMMAND_H

#include "Exception.h"
#include "config.h"
#include "systemc.h"

struct DeQueueCommand
{
    private:
    unsigned flow_id;

    public:
    void set_flow_id(unsigned flow_id);
    unsigned get_flow_id();
    bool operator==(const DeQueueCommand &rhs) const { return (rhs.flow_id == flow_id); }
    friend std::ostream& operator<<(std::ostream& os, const DeQueueCommand& t) { return os<<t.flow_id; }

    DeQueueCommand() : flow_id(-1) {}

    DeQueueCommand(unsigned flow_id) { this->flow_id = flow_id; }
};

extern void sc_trace(sc_trace_file *tf, const DeQueueCommand &v, const std::string &name);

#endif
