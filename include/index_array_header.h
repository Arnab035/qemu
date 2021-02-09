/* globals that are mostly involved in parsing the Intel PT packets */

#ifndef INDEX_ARRAY_H
#define INDEX_ARRAY_H

struct tip_address_info {
  char *address;
  int  is_useful;
  int  ip_bytes;
};

struct fup_address_info {
  char *address;
  char type;  // a single byte to indicate whether this is a FUP associated interrupt or VMEXIT
};

struct hash_buckets {
  int interrupt_number;   // is the value
  char *interrupt_handler_address;  // this is the key
  struct hash_buckets *pointer;
};

// hash table where the key is the interrupt handler 
// function pointer and interrupt number is the value
extern struct hash_buckets *interrupt_hash_table;  

extern unsigned long *tb_insn_array;
extern unsigned int size_of_tb_insn_array;

extern int is_within_block;

extern bool start_recording;

extern char *tnt_array;
extern struct tip_address_info *tip_addresses;
extern struct fup_address_info *fup_addresses;
extern unsigned long long index_array;
//extern char **pip_cr3_values;

extern int stopped_execution_of_tb_chain;
extern int index_tip_address;
extern int index_cr3_value;

extern int index_array_incremented;
extern int index_tip_address_incremented;

extern int is_io_instruction;
extern int is_handle_interrupt_in_userspace;

unsigned long do_strtoul(char *address);   // function declared

#endif
