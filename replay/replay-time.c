/*
 * replay-time.c
 *
 * Copyright (c) 2010-2015 Institute for System Programming
 *                         of the Russian Academy of Sciences.
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 *
 */

#include "qemu/osdep.h"
#include "index_array_header.h"
#include "qemu-common.h"
#include "sysemu/replay.h"
#include "replay-internal.h"
#include "qemu/error-report.h"

int64_t replay_save_clock(ReplayClockKind kind, int64_t clock)
{
    /*
    if (replay_file) {
        //g_assert(replay_mutex_locked());

        replay_save_instructions();
        replay_put_event(EVENT_CLOCK + kind);
        replay_put_qword(clock);
    }*/
    if (arnab_host_clock_replay_file) {
        if (start_recording) {
            arnab_replay_put_event(EVENT_CLOCK + kind, "host-clock");
            arnab_replay_put_qword(clock, "host-clock");
        }
    }
    return clock;
}

void replay_read_next_clock(ReplayClockKind kind)
{
    unsigned int read_kind = replay_state.data_kind - EVENT_CLOCK;

    assert(read_kind == kind);

    int64_t clock = replay_get_qword();

    replay_check_error();
    replay_finish_event();

    replay_state.cached_clock[read_kind] = clock;
}

/*! Reads next clock event from the input. */
int64_t replay_read_clock(ReplayClockKind kind, int64_t clock)
{
    //g_assert(replay_file && replay_mutex_locked());

    //replay_account_executed_instructions();
    if (arnab_host_clock_replay_file) 
    {
        int64_t ret;
        uint8_t event;
        event = arnab_replay_get_byte("host-clock");
        if (event == EVENT_CLOCK + kind) {
            ret = arnab_replay_get_qword("host-clock");
            printf("Reading clock of type %d. Value: %ld\n", event, ret);
            return ret;
        }
        else {
            printf("Incorrect clock event read. The incorrect clock type is %d\n", event);
        }
    }
    else {
        error_report("REPLAY INTERNAL ERROR %d", __LINE__);
        exit(1);
    }
    return clock;
}

