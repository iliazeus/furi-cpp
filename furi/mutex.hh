#pragma once

#include <furi/core/mutex.h>

#include "furi/macros.hh"
#include "furi/own.hh"

namespace furi {
  using Mutex = ::FuriMutex;
  using MutexOwn = Own<::FuriMutex, ::furi_mutex_free>;

  namespace mutex {
    using Type = ::FuriMutexType;
    namespace type {
      FURI_HH_ALIAS Normal = ::FuriMutexTypeNormal;
      FURI_HH_ALIAS Recursive = ::FuriMutexTypeRecursive;
    }

    FURI_HH_ALIAS alloc = ::furi_mutex_alloc;
    FURI_HH_ALIAS free = ::furi_mutex_free;
    FURI_HH_ALIAS acquire = ::furi_mutex_acquire;
    FURI_HH_ALIAS release = ::furi_mutex_release;
    FURI_HH_ALIAS get_owner = ::furi_mutex_get_owner;
  }
}
