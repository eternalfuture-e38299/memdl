/*******************************************************************************
 * File: test.c
 * Project: memdl
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
#include <stdlib.h>
#include "memdl.h"

// 测试函数类型
typedef void (*test_func_t)(void);
typedef int (*calculate_t)(int, int);
typedef const char* (*get_message_t)(void);

int main() {
    printf("memdl Test - Platform: %d\n", memdl_get_platform());

    // 从文件读取SO数据（这里需要你先准备一个测试SO文件）
    FILE* file = fopen("test_lib.dll", "rb");
    if (!file) {
        printf("❌ Cannot open test library file\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    const size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);

    void* data = malloc(size);
    if (!data) {
        fclose(file);
        printf("❌ Memory allocation failed\n");
        return 1;
    }

    fread(data, 1, size, file);
    fclose(file);

    printf("📁 Library size: %zu bytes\n", size);

    // 验证文件格式
    if (memdl_validate(data, size) != 0) {
        printf("❌ Invalid library format: %s\n", memdl_error());
        free(data);
        return 1;
    }
    printf("✅ Library format validated\n");

    // 获取架构信息
    int arch = memdl_get_arch(data, size);
    printf("🏗️  Library architecture: %d\n", arch);

    // 内存加载
    memdl_handle_t handle = memdl_open(data, size, MEMDL_NOW | MEMDL_LOCAL);
    if (!handle) {
        printf("❌ Load failed: %s\n", memdl_error());
        free(data);
        return 1;
    }
    printf("✅ Library loaded successfully from memory!\n");

    // 测试符号查找
    test_func_t test_func = memdl_sym(handle, "native_test");
    calculate_t calc_func = memdl_sym(handle, "calculate_sum");
    get_message_t msg_func = memdl_sym(handle, "get_message");

    if (test_func) {
        printf("🔧 Calling native_test...\n");
        test_func();
    } else {
        printf("⚠️  native_test not found: %s\n", memdl_error());
    }

    if (calc_func) {
        const int result = calc_func(10, 20);
        printf("🔢 calculate_sum(10, 20) = %d\n", result);
    }

    if (msg_func) {
        const char* msg = msg_func();
        printf("💬 get_message() = %s\n", msg);
    }

    // 清理
    memdl_close(handle);
    free(data);

    printf("✅ Test completed successfully!\n");
    return 0;
}
