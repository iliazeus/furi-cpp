#pragma once

#include <furi.h>

#include "furi/macros.hh"
#include "furi/own.hh"

namespace furi {
  using MessageQueue = ::FuriMessageQueue;
  using MessageQueueOwn = Own<::FuriMessageQueue, ::furi_message_queue_free>;

  namespace message_queue {
    FURI_HH_ALIAS alloc = ::furi_message_queue_alloc;
    FURI_HH_ALIAS free = ::furi_message_queue_free;

    FURI_HH_ALIAS put = ::furi_message_queue_put;
    FURI_HH_ALIAS get = ::furi_message_queue_get;

    FURI_HH_ALIAS get_capacity = ::furi_message_queue_get_capacity;
    FURI_HH_ALIAS get_message_size = ::furi_message_queue_get_message_size;
    FURI_HH_ALIAS get_count = ::furi_message_queue_get_count;
    FURI_HH_ALIAS get_space = ::furi_message_queue_get_space;

    FURI_HH_ALIAS reset = ::furi_message_queue_reset;
  }
}