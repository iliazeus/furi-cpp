#pragma once

#include <notification/notification.h>
#include <notification/notification_messages.h>

#include "furi/macros.hh"
#include "furi/record.hh"
#include "furi/own.hh"

namespace furi {
  using NotificationApp = ::NotificationApp;

  namespace notification {
    inline NotificationApp* open_record() {
      return static_cast<NotificationApp*>(record::open(RECORD_NOTIFICATION));
    }

    inline void close_record(NotificationApp*) {
      return record::close(RECORD_NOTIFICATION);
    }
  }

  using NotificationAppOwn = Own<NotificationApp, notification::close_record>;

  namespace notification {
    FURI_HH_ALIAS message = ::notification_message;
    FURI_HH_ALIAS message_block = ::notification_message_block;
  }
}
