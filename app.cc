#include "examples/timer/app.hh"
#include "examples/tracker/app.hh"

extern "C" int32_t fap_main(void*) {
  timer_app::App::main();
  // tracker_app::App::main();

  return 0;
}
