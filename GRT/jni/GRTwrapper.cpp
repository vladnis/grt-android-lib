#include <jni.h>

/* Gesture Recognition Toolkit library */
#include "GRT.h"
using namespace GRT;

/* Asset manager */
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

/* Logging */
#include <android/log.h>

namespace grt_wrapper {

	/*
	 * Class:     com_example_grt_GRTexample
	 * Method:    GRTnative
	 * Signature: ()V
	 */
	static void test(JNIEnv *, jclass) {

		/* TODO
		#ifdef ANDROID
					__android_log_write(ANDROID_LOG_VERBOSE, "ARCH", "ANDROID");
		#endif
		*/
		LabelledClassificationData trainingData, testData;

		if (!trainingData.loadDatasetFromFile("/data/local/tmp/1.in")) {
			__android_log_write(ANDROID_LOG_ERROR, "GRT", "Training dataset could not be loaded.");
			return;
		}

		__android_log_write(ANDROID_LOG_VERBOSE, "GRT", "Training dataset was loaded.");

		testData = trainingData.partition(80);

		GestureRecognitionPipeline pipeline;

		pipeline.setClassifier(ANBC());

		if (!pipeline.train(trainingData)) {
			__android_log_write(ANDROID_LOG_ERROR, "GRT", "Failed to train.");
		}
		if (!pipeline.test(testData)) {
			__android_log_write(ANDROID_LOG_ERROR, "GRT", "Failed to test.");
		}

		__android_log_print(ANDROID_LOG_ERROR, "GRT", "%f", pipeline.getTestAccuracy());

	}

	static JNINativeMethod method_table[] = {
		{"test", "()V", (void *) test},
	};

}

using namespace grt_wrapper;

extern "C" jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
		__android_log_write(ANDROID_LOG_WARN, "JNI_OnLoad", "1");
    	return -1;
    }
    jclass clazz = env->FindClass("com/example/grt/GRTwrapper");
    if (!clazz) {
		__android_log_write(ANDROID_LOG_WARN, "JNI_OnLoad", "Class com/example/grt/GRTwrapper was not found.");
    	return -1;
    }
    env->RegisterNatives(clazz, method_table, sizeof(method_table) / sizeof(method_table[0]));
    env->DeleteLocalRef(clazz);

    return JNI_VERSION_1_6;
}
