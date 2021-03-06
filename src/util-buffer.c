/* Copyright (C) 2007-2012 Open Information Security Foundation
 *
 * You can copy, redistribute or modify this Program under the terms of
 * the GNU General Public License version 2 as published by the Free
 * Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

/**
 * \file
 *
 * \author Anoop Saldanha <anoopsaldanha@gmail.com>
 */

#include "suricata-common.h"
#include "suricata.h"
#include "util-debug.h"
#include "util-buffer.h"

/* 10 mb */
#define MAX_LIMIT 10485760

MemBuffer *MemBufferCreateNew(uint32_t size)
{
    if (size > MAX_LIMIT) {
        SCLogWarning(SC_ERR_MEM_BUFFER_API, "Mem buffer asked to create "
                     "buffer with size greater than API limit - %d", MAX_LIMIT);
        return NULL;
    }

    uint32_t total_size = size + sizeof(MemBuffer);

    MemBuffer *buffer = SCMalloc(total_size);
    if (buffer == NULL) {
        return NULL;
    }
    memset(buffer, 0, total_size);

    buffer->size = size;
    buffer->buffer = (uint8_t *)buffer + sizeof(MemBuffer);

    return buffer;
}

void MemBufferFree(MemBuffer *buffer)
{
    SCFree(buffer);

    return;
}
