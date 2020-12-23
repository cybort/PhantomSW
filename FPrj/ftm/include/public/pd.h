#ifndef _PD_H_
#define _PD_H_

#include "systemc.h"

#define MAX_PD_SIZE	12

struct pd {
    private:
    union {
        char data[MAX_PD_SIZE];
        struct {
            struct {
                unsigned flowID :18;
                unsigned length :14;
            };
            int  address; 
            bool result;
 //         long pdNum;            
        };
    };

    public:
        bool set_flowID(unsigned fID);
        unsigned get_flowID() const;
        bool set_length(unsigned len);
        unsigned get_length() const;
        bool set_addr(unsigned addr);
        unsigned get_addr() const;
        bool set_result(bool reslt);
        bool get_result() const;
        char* get_data();

	bool operator== (const pd& rhs) const
    {
        return (this->flowID == rhs.get_flowID() && this->length == rhs.get_length() && this->address ==  rhs.get_addr() && this->result == rhs.get_result());
    }
    friend std::ostream& operator<<(std::ostream& os, const pd& t) { return os<<t.flowID<<","<<t.length<<","<<t.address<<","<<t.result; }

	void dump()
	{
		for (int i = 0; i < MAX_PD_SIZE; i++)
			cout << data[i] << " ";
		cout << endl;
	}

    bool operator< (const pd&d) const
    {

    };

};

extern void sc_trace(sc_trace_file *tf, const pd& p, const sc_string& name);

#endif
