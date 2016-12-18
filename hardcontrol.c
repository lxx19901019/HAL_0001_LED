#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jni.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
static jint fd;

#include <android/log.h>  //liblog
//__android_log_print(ANDROID_LOG_DEBUG,"JNIDemo","native add ...")

jint ledOpen(JNIEnv *env, jobject cls)
{
	fd = open("/dev/leds", O_RDWR);
	__android_log_print(ANDROID_LOG_DEBUG,"LEDDemo","native ledOpen fd = %d", fd);
	if(fd <= 0)
		return -1;
	else 
		return 0;
	

	return 0;
}

void ledClose(JNIEnv *env, jobject cls)
{	
		__android_log_print(ANDROID_LOG_DEBUG,"LEDDemo","native ledClose");
		close(fd);
}


jint ledCtrl(JNIEnv *env, jobject cls, jint which ,jint status)
{

	int ret = ioctl(fd, status, which);
	__android_log_print(ANDROID_LOG_DEBUG,"LEDDemo","native ledCtrl : %d %d %d",which , status, ret);
	return 0;
}



static const JNINativeMethod methods[] ={
		{"ledOpen", "()I",(void *)ledOpen},
		{"ledClose", "()V",(void *)ledClose},
		{"ledCtrl", "(II)I",(void *)ledCtrl},
};


JNIEXPORT jint JNICALL 
JNI_OnLoad(JavaVM *jvm, void *reserved)
{
	JNIEnv *env;
	jclass *cls;

	if( (*jvm)->GetEnv(jvm, (void **)&env, JNI_VERSION_1_4) < 0) {
		return JNI_ERR;
	}

	cls = (*env)->FindClass(env, "com/smile/hardlibrary/HardControl");
	if (NULL == cls) {
		return JNI_ERR;
	}

	if ((*env)->RegisterNatives(env, cls, methods, sizeof(methods)/sizeof(methods[0])) < 0) {
		return JNI_ERR;
	}

	return JNI_VERSION_1_4;
		
}











