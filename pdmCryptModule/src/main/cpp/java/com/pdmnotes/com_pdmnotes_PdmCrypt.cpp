//
// Created by Yi Yang on 8/6/2022.
//


#include <iostream>
#include <complex>
#include "com_pdmnotes_PdmCrypt.h"
#include <stdio.h>

// PDM imports
#include "cc20_wrapper.h"
#include "empp.h"
#define STRING_RETURN "Hello world!"
#define STRING_CALLBACK "Hello world callback!"
#define STRING_CALLBACK_STATIC "Hello world static callback!"
#define STRING_PAYLOAD "Simple payload string"

extern "C" JNIEXPORT jstring JNICALL Java_com_pdmnotes_PdmCrypt_getHash
        (JNIEnv *env, jobject thiz, jstring a){

    std::string s = env->GetStringUTFChars(a, NULL);
    std::string hash_out= get_hash(s);
    return env->NewStringUTF(hash_out.data());
}

extern "C" JNIEXPORT jstring JNICALL Java_com_pdmnotes_PdmCrypt_help
        (JNIEnv *env, jobject thiz, jstring a){
    std::string s = env->GetStringUTFChars(a, NULL);
    std::cout << "NOW IN NATIVE STRING ENVIRONMENT!!" << std::endl;
    std::cout << "Your caller says: " << s << std::endl;
    std::cout << "Now iterating over the given string array." << std::endl;
    s.append("::::::THIS IS APPENDED TEXT!!!! WARNING!!! WARNING!!!! :)");
    return env->NewStringUTF(s.data());
}
extern "C" JNIEXPORT jstring JNICALL Java_com_pdmnotes_PdmCrypt_loaderCheck
        (JNIEnv *env, jobject thiz, jstring a, jstring b){
    std::string k = env->GetStringUTFChars(a, NULL);
    std::string bi = env->GetStringUTFChars(b, NULL);
    std::string ao = loader_check(k,bi);
    return env->NewStringUTF(ao.data());
}
extern "C" JNIEXPORT jstring JNICALL Java_com_pdmnotes_PdmCrypt_loaderOut
        (JNIEnv *env, jobject thiz, jstring a, jstring b){
    std::string k = env->GetStringUTFChars(a, NULL);
    std::string bi = env->GetStringUTFChars(b, NULL);
    std::string ao = loader_out(k,bi);
    return env->NewStringUTF(ao.data());
}