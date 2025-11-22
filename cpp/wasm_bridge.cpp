#include <emscripten.h>
#include <cmath> // Required for sin, cos, tan
// bringing in our math logic from before
#include "add.h"
#include "subtract.h"
#include "multiply.h"
#include "divide.h"

//helper to convert to radians
double to_rad(double degrees) {
    return degrees * M_PI / 180.0;
}
// extern "C" tells the c++ compiler not to mangle the names
// so javascript can actually find them
extern "C" {

    // EMSCRIPTEN_KEEPALIVE tells the compiler:
    // "hey, don't delete this function to save space,
    // we need it for the website"

    EMSCRIPTEN_KEEPALIVE
    double api_add(double a, double b) {
        return add(a, b);
    }

    EMSCRIPTEN_KEEPALIVE
    double api_subtract(double a, double b) {
        return subtract(a, b);
    }

    EMSCRIPTEN_KEEPALIVE
    double api_multiply(double a, double b) {
        return multiply(a, b);
    }

    EMSCRIPTEN_KEEPALIVE
    double api_divide(double a, double b) {
        bool ok = true;
        double result = divide(a, b, ok);
        // if we divide by zero, return a specific error code
        // or we can handle it in js. for now, lets return infinity if bad.
        if (!ok) return 999999999; 
        return result;
    }
    //trig functions
    EMSCRIPTEN_KEEPALIVE
    double api_sin(double a) { return sin(to_rad(a)); }

    EMSCRIPTEN_KEEPALIVE
    double api_cos(double a) { return cos(to_rad(a)); }

    EMSCRIPTEN_KEEPALIVE
    double api_tan(double a) { return tan(to_rad(a)); }
}