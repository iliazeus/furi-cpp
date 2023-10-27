#pragma once

#include "examples/tracker/tracker.hh"

namespace tracker_app {
  static auto song() {
    using namespace tracker_app::tracker;
    using namespace tracker_app::tracker::note;

    return Song {
      .qpm = 140,
      .commands = {
        { .note = C(4), .len32 = 2 },
        { .note = D(4), .len32 = 2 },
        { .note = F(4), .len32 = 2 },
        { .note = D(4), .len32 = 2 },

        { .note = A(4), .len32 = 3 },
        { .len32 = 3, .vol = 0 },
        { .note = A(4), .len32 = 3 },
        { .len32 = 3, .vol = 0 },
        { .note = G(4), .len32 = 8 },
        { .len32 = 4, .vol = 0 },

        { .note = C(4), .len32 = 2 },
        { .note = D(4), .len32 = 2 },
        { .note = F(4), .len32 = 2 },
        { .note = D(4), .len32 = 2 },

        { .note = G(4), .len32 = 3 },
        { .len32 = 3, .vol = 0 },
        { .note = G(4), .len32 = 3 },
        { .len32 = 3, .vol = 0 },
        { .note = F(4), .len32 = 6 },
        { .note = E(4), .len32 = 2 },
        { .note = D(4), .len32 = 4 },
      },
    };
  }

  class App {
    static void main() {
      Tracker tracker;
      tracker.play(song());
    }
  };
}
