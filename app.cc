#include "app/app.hh"
#include "app/second_timer.hh"

extern "C" int32_t fap_main(void*) {
  app::App::main();
  return 0;
}
