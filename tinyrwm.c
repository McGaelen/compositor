// SPDX-FileCopyrightText: © 2026 Isaac Freund
// SPDX-License-Identifier: 0BSD

#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <wayland-client-protocol.h>
#include <wayland-util.h>

#include <river-window-management-v1-client-protocol.h>

struct river_window_manager_v1 *window_manager;

void registry_listener_global(void *data, struct wl_registry *wl_registry,
                              uint32_t name, const char *interface,
                              uint32_t version) {
  if (strcmp(interface, "river_window_manager_v1")) {
    window_manager = wl_registry_bind(wl_registry, name, &river_window_manager_v1_interface, 5);
  }
}

int main(void) {
  struct wl_display *display = wl_display_connect(NULL);
//   if (display == NULL) {
//     fprintf(stderr, "failed to connect to Wayland server\n");
//     return 1;
//   }
//
//   // Avoid passing WAYLAND_DEBUG on to our children.
//   // It only matters if it's set when the display is created.
//   unsetenv("WAYLAND_DEBUG");
//
//   // Ensure children are automatically reaped.
//   signal(SIGCHLD, SIG_IGN);

  struct wl_registry *registry = wl_display_get_registry(display);
  struct wl_registry_listener reg_listener = {
      .global = registry_listener_global,
  };
  wl_registry_add_listener(registry, &reg_listener, NULL);
  if (wl_display_roundtrip(display) < 0) {
    fprintf(stderr, "roundtrip failed\n");
    return 1;
  }

  if (window_manager == NULL) {
    fprintf(stderr, "river_window_manager_v1 or river_xkb_bindings_v1 "
                    "not supported by the Wayland server\n");
    return 1;
  }



  //
  // 	wm_init();
  //
  // 	river_window_manager_v1_add_listener(window_manager_v1, &wm_listener,
  // NULL);
  //
  // 	while (true) {
  // 		if (wl_display_dispatch(display) < 0) {
  // 			fprintf(stderr, "dispatch failed\n");
  // 			return 1;
  // 		}
  // 	}

  return 0;
}
