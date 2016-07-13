#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <X11/Xlib.h>

static int error = 0;

int x_error_handler(Display* display, XErrorEvent* event) {
  error = 1;
}

int main() {
  Display* display = XOpenDisplay(NULL);
  assert(display);

  XSetWindowAttributes attrs;
  attrs.override_redirect = True;
  Window win = XCreateWindow(display, DefaultRootWindow(display),
                             0, 0, 1, 1, 0, 24, InputOutput,
                             CopyFromParent, CWOverrideRedirect,
                             &attrs);

  XSetErrorHandler(x_error_handler);

  for (int i = 2; i < (1 << (8 * sizeof(int) - 2)); i <<= 1) {
    printf("%dx%d: ", i, i);
    XResizeWindow(display, win, i, i);
    XSync(display, False);
    if (!error) {
      printf("✓\n", i, i);
    } else {
      printf("✗\n", i, i);
      break;
    }
  }
}
