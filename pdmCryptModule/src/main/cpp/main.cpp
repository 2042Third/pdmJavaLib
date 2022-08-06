// Write C++ code here.
//
// Do not forget to dynamically load the C++ library into your application.
//
// For instance,
//
// In MainActivity.java:
//    static {
//       System.loadLibrary("main");
//    }
//
// Or, in MainActivity.kt:
//    companion object {
//      init {
//         System.loadLibrary("main")
//      }
//    }

#include <jni.h>
#include <iostream>
extern "C" {
#include "cc20_wrapper.h"
    void getLib(){
        char a[1024] = "hello";
        char b[1024] ;
        char c[1024];
        hash_wrap(a,5,b);

    }

}