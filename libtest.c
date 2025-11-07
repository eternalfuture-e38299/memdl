/*******************************************************************************
 * File: libtest.c
 * Project: memdl test library
 * Created: 2025/11/7
 * Author: eternalfuture-e38299
 * Github: https://github.com/eternalfuture-e38299
 *
 * MIT License
 *
 * Copyright (c) 2025 EternalFuture
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *******************************************************************************/

#include <stdio.h>
#include <string.h>

// 平台特定的日志输出
#ifdef __ANDROID__
#include <android/log.h>
#define LOG_TAG "LIBTEST"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#else
#define LOGI(...) printf(__VA_ARGS__)
#endif

// 简单的测试函数 - 无参数无返回值
__attribute__((visibility("default")))
void native_test(void) {
    LOGI("🎉 native_test() called successfully!\n");
    printf("✅ Native test function executed!\n");
}

// 计算函数 - 带参数和返回值
__attribute__((visibility("default")))
int calculate_sum(int a, int b) {
    int result = a + b;
    LOGI("🔢 calculate_sum(%d, %d) = %d\n", a, b, result);
    return result;
}

// 字符串返回函数
__attribute__((visibility("default")))
const char* get_message(void) {
    LOGI("💬 get_message() called\n");
    return "Hello from libtest.so! Memory loading works! 🚀";
}

// 带参数的字符串函数
__attribute__((visibility("default")))
const char* format_message(const char* name, int value) {
    static char buffer[256];
    snprintf(buffer, sizeof(buffer), "Hello %s! The value is %d", name, value);
    LOGI("📝 format_message(%s, %d) = %s\n", name, value, buffer);
    return buffer;
}

// 浮点数计算函数
__attribute__((visibility("default")))
double calculate_area(double radius) {
    double area = 3.14159 * radius * radius;
    LOGI("📐 calculate_area(%.2f) = %.2f\n", radius, area);
    return area;
}

// 结构体操作函数
typedef struct {
    int x;
    int y;
    char name[32];
} Point;

__attribute__((visibility("default")))
Point create_point(int x, int y, const char* name) {
    Point p;
    p.x = x;
    p.y = y;
    strncpy(p.name, name, sizeof(p.name) - 1);
    p.name[sizeof(p.name) - 1] = '\0';
    LOGI("📍 create_point(%d, %d, %s)\n", x, y, name);
    return p;
}

__attribute__((visibility("default")))
void print_point(Point p) {
    LOGI("📋 Point: name=%s, x=%d, y=%d\n", p.name, p.x, p.y);
    printf("Point: %s (%d, %d)\n", p.name, p.x, p.y);
}

// 回调函数测试
typedef void (*callback_t)(const char* message);

__attribute__((visibility("default")))
void test_callback(callback_t callback) {
    LOGI("📞 test_callback() called\n");
    if (callback) {
        callback("This is a callback from libtest.so!");
    }
}

// 数组操作函数
__attribute__((visibility("default")))
void process_array(int* array, int size) {
    LOGI("📊 process_array() called with size %d\n", size);
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    LOGI("📊 Array sum: %d\n", sum);
    printf("Array processed - Sum: %d\n", sum);
}

// 字符串反转函数
__attribute__((visibility("default")))
void reverse_string(char* str) {
    if (!str) return;

    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
    LOGI("🔁 reverse_string() result: %s\n", str);
}

// 库初始化函数（可选）
__attribute__((visibility("default")))
void library_init(void) {
    LOGI("🏁 libtest.so initialized!\n");
    printf("========================================\n");
    printf("   libtest.so - Test Library Loaded!   \n");
    printf("========================================\n");
}

// 库清理函数（可选）
__attribute__((visibility("default")))
void library_cleanup(void) {
    LOGI("🧹 libtest.so cleanup called\n");
    printf("========================================\n");
    printf("   libtest.so - Cleanup Complete!       \n");
    printf("========================================\n");
}

// 版本信息函数
__attribute__((visibility("default")))
const char* get_version(void) {
    return "1.0.0-memory-loaded";
}

// 复杂的数学运算
__attribute__((visibility("default")))
double complex_calculation(double a, double b, int operation) {
    double result = 0.0;
    const char* op_name = "";

    switch (operation) {
        case 0: // 加法
            result = a + b;
            op_name = "addition";
            break;
        case 1: // 减法
            result = a - b;
            op_name = "subtraction";
            break;
        case 2: // 乘法
            result = a * b;
            op_name = "multiplication";
            break;
        case 3: // 除法
            result = (b != 0) ? a / b : 0.0;
            op_name = "division";
            break;
        default:
            op_name = "unknown";
            break;
    }

    LOGI("🧮 complex_calculation(%.2f, %.2f, %d) = %.2f (%s)\n",
          a, b, operation, result, op_name);
    return result;
}

// JNI兼容函数（用于Android测试）
#ifdef __ANDROID__
#include <jni.h>

__attribute__((visibility("default")))
jstring Java_com_example_test_NativeHelper_getNativeVersion(JNIEnv* env, jobject thiz) {
    return (*env)->NewStringUTF(env, get_version());
}
#endif

// 全局变量测试
__attribute__((visibility("default")))
int global_counter = 0;

__attribute__((visibility("default")))
int increment_counter(void) {
    global_counter++;
    LOGI("🔢 increment_counter() = %d\n", global_counter);
    return global_counter;
}

__attribute__((visibility("default")))
int get_counter(void) {
    return global_counter;
}

// 线程安全的计数器（简单演示）
#include <pthread.h>
static pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
static int thread_safe_counter = 0;

__attribute__((visibility("default")))
int increment_thread_safe(void) {
    pthread_mutex_lock(&counter_mutex);
    thread_safe_counter++;
    int result = thread_safe_counter;
    pthread_mutex_unlock(&counter_mutex);
    LOGI("🔒 increment_thread_safe() = %d\n", result);
    return result;
}