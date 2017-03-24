{% if not options.header_only %}
#include <glad/glad_loader.h>
{% endif %}

#include <stddef.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif


static void* glad_get_dlopen_handle(const char *lib_names[], int length) {
    int i;
    void *handle;

    for (i = 0; i < length; ++i) {
#ifdef _WIN32
        handle = LoadLibraryA(lib_names[i]);
#else
        handle = dlopen(lib_names[i], RTLD_LAZY | RTLD_GLOBAL);
#endif
        if (handle != NULL) {
            return handle;
        }
    }

    return NULL;
}

static void glad_close_dlopen_handle(void* handle) {
    if (handle != NULL) {
#ifdef _WIN32
        FreeLibrary(handle);
#else
        dlclose(handle);
#endif
    }
}

static void* glad_dlsym_handle(void* handle, const char *name) {
    if (handle == NULL) {
        return NULL;
    }

#ifdef _WIN32
    return GetProcAddress(handle, name);
#else
    return dlsym(handle, name);
#endif
}


static void* glad_get_proc_from_userptr(const char* name, void *userptr) {
    return ((void* (*)(const char *name)userptr)(name);
}

{% include 'loader/egl.c' %}

{% include 'loader/gl.c' %}

{% include 'loader/gles.c' %}

{% include 'loader/glx.c' %}

{% include 'loader/wgl.c' %}