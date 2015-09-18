//
// Created by Administrator on 2015/9/10 0010.
//
#include <string.h>
#include <jni.h>
#include <android/log.h>

#ifndef LOG_TAG
#define LOG_TAG "hello"
#endif

#define LOGD(...)__android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)


#define CLASS_MODEL  "com/wawov/nativeapp/activity/MainActivity"
#define CONTAINER_MODEL  "com/wawov/nativeapp/model/Container"
#define TRANSPORTATION_MODEL  "com/wawov/nativeapp/model/Transportation"

jstring stringFromJni(JNIEnv *env,jobject thiz){
    return env->NewStringUTF("hello jni");
}

void arrayFromJni(JNIEnv *env,jobject thiz,jintArray arr){
    __android_log_print(ANDROID_LOG_DEBUG,"hello","arrayFromJni!!");
    int size = env->GetArrayLength(arr);
    jint *cArr = env->GetIntArrayElements(arr, JNI_FALSE);
    //jintArray jArr = env->NewIntArray(size);
    jint i;
    const jint *temp = &i;
    for(i = 0;i<size;i++){
        env->SetIntArrayRegion(arr,i,1,temp);
    }
    __android_log_print(ANDROID_LOG_DEBUG,"hello","end for !!");
    //return arr;
}

void jniContainer(JNIEnv *env,jobject thiz,jobject arrayList){
    jclass clazz = env->GetObjectClass(arrayList);//ArrayList
    jmethodID getMethodID = env->GetMethodID(clazz,"get","(I)Ljava/lang/Object;");
    jmethodID sizeMethodID = env->GetMethodID(clazz,"size","()I");
    int size = env->CallIntMethod(arrayList,sizeMethodID);
    LOGD("arrayList size is %d",size);
    jclass containerClazz = env->FindClass(CONTAINER_MODEL);
    if(containerClazz == NULL){
        LOGD("containerClazz is null");
    }
    //jmethodID container_construct = env->GetMethodID(containerClazz,"<init>","(I,Ljava/lang/String;,Z)V");
    //jobject containerOj = env->CallObjectMethod(containerClazz,container_construct,21,"nic",false);
    for(int i = 0;i<size;i++){
        jobject job = env->CallObjectMethod(arrayList,getMethodID,i);
        LOGD("jniContainer");
        jfieldID idFiled = env->GetFieldID(containerClazz,"id","I");
        jfieldID nameFiled = env->GetFieldID(containerClazz,"name","Ljava/lang/String;");
        jfieldID expireFiled = env->GetFieldID(containerClazz,"expire","Z");
        jint id = env->GetIntField(job,idFiled);
        LOGD("object id =%d",id);
    }
}

void jniCreateArray(JNIEnv *env,jobject thiz,jobject arrayList){
    jclass arrayListClazz = env->GetObjectClass(arrayList);
    jclass containerClazz = env->FindClass(CONTAINER_MODEL);
    if(containerClazz == NULL){
        LOGD("containerClazz is null");
    }
    jmethodID getMethodID = env->GetMethodID(arrayListClazz,"add","(Ljava/lang/Object;)Z");
    LOGD(" getMethodID end");
    jmethodID container_construct = env->GetMethodID(containerClazz,"<init>","(ILjava/lang/String;Z)V");
    LOGD(" container_construct end");
    jobject containerOj = env->NewObject(containerClazz,container_construct,21,env->NewStringUTF("nihao"),true);
    if(containerOj == NULL){
        LOGD(" containerOj is null");
    }
    LOGD(" containerOj end");
    jboolean success = env->CallBooleanMethod(arrayList,getMethodID,containerOj);
    LOGD(" jniCreateArray end");
}


static JNINativeMethod gMethods []= {
        {"stringFromJni",          "()Ljava/lang/String;",         (void*)stringFromJni},
        {"arrayFromJni",           "([I)V",                        (void*)arrayFromJni},
        {"jniContainer",           "(Ljava/util/ArrayList;)V",     (void*)jniContainer},
        {"jniCreateArray",         "(Ljava/util/ArrayList;)V",     (void*)jniCreateArray},
};

#ifndef NELEM
# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
#endif

int registerMethod(JNIEnv *env){
    jclass clazz = env->FindClass(CLASS_MODEL);
    if(clazz == NULL){
        return JNI_ERR;
    }
    __android_log_print(ANDROID_LOG_DEBUG,"hello","RegisterNatives start!!");
    if(env->RegisterNatives(clazz,gMethods,NELEM(gMethods))<0){
        return JNI_ERR;
    }
    __android_log_print(ANDROID_LOG_DEBUG,"hello","RegisterNatives end!!");
    return JNI_OK;
}

JNIEXPORT jint JNI_OnLoad(JavaVM* jvm, void* reserved){
    JNIEnv *env = NULL;
    __android_log_print(ANDROID_LOG_DEBUG,"hello","hello jni start!!");
    if(jvm->GetEnv(reinterpret_cast<void **>(&env),JNI_VERSION_1_4) != JNI_OK){
        return JNI_ERR;
    }
    if(registerMethod(env) == JNI_ERR){
        return JNI_ERR;
    }
    return JNI_VERSION_1_4;

}


JNIEXPORT void JNI_OnUnload(JavaVM* jvm, void* reserved) {

}