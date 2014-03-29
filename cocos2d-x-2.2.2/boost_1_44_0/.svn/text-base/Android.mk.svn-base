LOCAL_PATH := $(call my-dir)
# boost/date_time
include $(CLEAR_VARS)

LOCAL_CPPFLAGS += -fexceptions -D_LITTLE_ENDIAN

LOCAL_MODULE := boost
LOCAL_MODULE := libboost
LOCAL_SRC_FILES := \
libs/date_time/src/gregorian/date_generators.cpp \
libs/date_time/src/gregorian/greg_month.cpp \
libs/date_time/src/gregorian/greg_weekday.cpp \
libs/date_time/src/gregorian/gregorian_types.cpp \
libs/date_time/src/posix_time/posix_time_types.cpp \
 \
libs/math/src/tr1/acosh.cpp \
libs/math/src/tr1/acoshf.cpp \
libs/math/src/tr1/acoshl.cpp \
libs/math/src/tr1/asinh.cpp \
libs/math/src/tr1/asinhf.cpp \
libs/math/src/tr1/asinhl.cpp \
libs/math/src/tr1/assoc_laguerre.cpp \
libs/math/src/tr1/assoc_laguerref.cpp \
libs/math/src/tr1/assoc_laguerrel.cpp \
libs/math/src/tr1/assoc_legendre.cpp \
libs/math/src/tr1/assoc_legendref.cpp \
libs/math/src/tr1/assoc_legendrel.cpp \
libs/math/src/tr1/atanh.cpp \
libs/math/src/tr1/atanhf.cpp \
libs/math/src/tr1/atanhl.cpp \
libs/math/src/tr1/beta.cpp \
libs/math/src/tr1/betaf.cpp \
libs/math/src/tr1/betal.cpp \
libs/math/src/tr1/cbrt.cpp \
libs/math/src/tr1/cbrtf.cpp \
libs/math/src/tr1/cbrtl.cpp \
libs/math/src/tr1/comp_ellint_1.cpp \
libs/math/src/tr1/comp_ellint_1f.cpp \
libs/math/src/tr1/comp_ellint_1l.cpp \
libs/math/src/tr1/comp_ellint_2.cpp \
libs/math/src/tr1/comp_ellint_2f.cpp \
libs/math/src/tr1/comp_ellint_2l.cpp \
libs/math/src/tr1/comp_ellint_3.cpp \
libs/math/src/tr1/comp_ellint_3f.cpp \
libs/math/src/tr1/comp_ellint_3l.cpp \
libs/math/src/tr1/copysign.cpp \
libs/math/src/tr1/copysignf.cpp \
libs/math/src/tr1/copysignl.cpp \
libs/math/src/tr1/cyl_bessel_i.cpp \
libs/math/src/tr1/cyl_bessel_if.cpp \
libs/math/src/tr1/cyl_bessel_il.cpp \
libs/math/src/tr1/cyl_bessel_j.cpp \
libs/math/src/tr1/cyl_bessel_jf.cpp \
libs/math/src/tr1/cyl_bessel_jl.cpp \
libs/math/src/tr1/cyl_bessel_k.cpp \
libs/math/src/tr1/cyl_bessel_kf.cpp \
libs/math/src/tr1/cyl_bessel_kl.cpp \
libs/math/src/tr1/cyl_neumann.cpp \
libs/math/src/tr1/cyl_neumannf.cpp \
libs/math/src/tr1/cyl_neumannl.cpp \
libs/math/src/tr1/ellint_1.cpp \
libs/math/src/tr1/ellint_1f.cpp \
libs/math/src/tr1/ellint_1l.cpp \
libs/math/src/tr1/ellint_2.cpp \
libs/math/src/tr1/ellint_2f.cpp \
libs/math/src/tr1/ellint_2l.cpp \
libs/math/src/tr1/ellint_3.cpp \
libs/math/src/tr1/ellint_3f.cpp \
libs/math/src/tr1/ellint_3l.cpp \
libs/math/src/tr1/erf.cpp \
libs/math/src/tr1/erfc.cpp \
libs/math/src/tr1/erfcf.cpp \
libs/math/src/tr1/erfcl.cpp \
libs/math/src/tr1/erff.cpp \
libs/math/src/tr1/erfl.cpp \
libs/math/src/tr1/expint.cpp \
libs/math/src/tr1/expintf.cpp \
libs/math/src/tr1/expintl.cpp \
libs/math/src/tr1/expm1.cpp \
libs/math/src/tr1/expm1f.cpp \
libs/math/src/tr1/expm1l.cpp \
libs/math/src/tr1/fmax.cpp \
libs/math/src/tr1/fmaxf.cpp \
libs/math/src/tr1/fmaxl.cpp \
libs/math/src/tr1/fmin.cpp \
libs/math/src/tr1/fminf.cpp \
libs/math/src/tr1/fminl.cpp \
libs/math/src/tr1/fpclassify.cpp \
libs/math/src/tr1/fpclassifyf.cpp \
libs/math/src/tr1/fpclassifyl.cpp \
libs/math/src/tr1/hermite.cpp \
libs/math/src/tr1/hermitef.cpp \
libs/math/src/tr1/hermitel.cpp \
libs/math/src/tr1/hypot.cpp \
libs/math/src/tr1/hypotf.cpp \
libs/math/src/tr1/laguerre.cpp \
libs/math/src/tr1/laguerref.cpp \
libs/math/src/tr1/laguerrel.cpp \
libs/math/src/tr1/legendre.cpp \
libs/math/src/tr1/legendref.cpp \
libs/math/src/tr1/legendrel.cpp \
libs/math/src/tr1/lgamma.cpp \
libs/math/src/tr1/lgammaf.cpp \
libs/math/src/tr1/lgammal.cpp \
libs/math/src/tr1/llround.cpp \
libs/math/src/tr1/llroundf.cpp \
libs/math/src/tr1/llroundl.cpp \
libs/math/src/tr1/log1p.cpp \
libs/math/src/tr1/log1pf.cpp \
libs/math/src/tr1/log1pl.cpp \
libs/math/src/tr1/lround.cpp \
libs/math/src/tr1/lroundf.cpp \
libs/math/src/tr1/lroundl.cpp \
libs/math/src/tr1/nextafter.cpp \
libs/math/src/tr1/nextafterf.cpp \
libs/math/src/tr1/nextafterl.cpp \
libs/math/src/tr1/nexttoward.cpp \
libs/math/src/tr1/nexttowardf.cpp \
libs/math/src/tr1/nexttowardl.cpp \
libs/math/src/tr1/riemann_zeta.cpp \
libs/math/src/tr1/riemann_zetaf.cpp \
libs/math/src/tr1/riemann_zetal.cpp \
libs/math/src/tr1/round.cpp \
libs/math/src/tr1/roundf.cpp \
libs/math/src/tr1/roundl.cpp \
libs/math/src/tr1/sph_bessel.cpp \
libs/math/src/tr1/sph_besself.cpp \
libs/math/src/tr1/sph_bessell.cpp \
libs/math/src/tr1/sph_legendre.cpp \
libs/math/src/tr1/sph_legendref.cpp \
libs/math/src/tr1/sph_legendrel.cpp \
libs/math/src/tr1/sph_neumann.cpp \
libs/math/src/tr1/sph_neumannf.cpp \
libs/math/src/tr1/sph_neumannl.cpp \
libs/math/src/tr1/tgamma.cpp \
libs/math/src/tr1/tgammaf.cpp \
libs/math/src/tr1/tgammal.cpp \
libs/math/src/tr1/trunc.cpp \
libs/math/src/tr1/truncf.cpp \
libs/math/src/tr1/truncl.cpp \
 \
libs/regex/src/c_regex_traits.cpp \
libs/regex/src/cpp_regex_traits.cpp \
libs/regex/src/cregex.cpp \
libs/regex/src/fileiter.cpp \
libs/regex/src/icu.cpp \
libs/regex/src/instances.cpp \
libs/regex/src/posix_api.cpp \
libs/regex/src/regex_debug.cpp \
libs/regex/src/regex_raw_buffer.cpp \
libs/regex/src/regex_traits_defaults.cpp \
libs/regex/src/regex.cpp \
libs/regex/src/static_mutex.cpp \
libs/regex/src/usinstances.cpp \
libs/regex/src/w32_regex_traits.cpp \
libs/regex/src/wc_regex_traits.cpp \
libs/regex/src/wide_posix_api.cpp \
libs/regex/src/winstances.cpp

LOCAL_SRC_FILES += \
libs/system/src/error_code.cpp

LOCAL_SRC_FILES += \
libs/filesystem/v2/src/v2_operations.cpp \
libs/filesystem/v2/src/v2_path.cpp \
libs/filesystem/v2/src/v2_portability.cpp \
libs/filesystem/v3/src/codecvt_error_category.cpp \
libs/filesystem/v3/src/operations.cpp \
libs/filesystem/v3/src/path_traits.cpp \
libs/filesystem/v3/src/path.cpp \
libs/filesystem/v3/src/portability.cpp \
libs/filesystem/v3/src/unique_path.cpp \
libs/filesystem/v3/src/utf8_codecvt_facet.cpp \
libs/filesystem/v3/src/windows_file_codecvt.cpp

prebuilt_stdcxx_PATH := $(NDK_HOME)/sources/cxx-stl/gnu-libstdc++/4.6
TARGET_CPU_ABI := armeabi
LOCAL_C_INCLUDES := \
$(prebuilt_stdcxx_PATH)/include \
$(prebuilt_stdcxx_PATH)/libs/$(TARGET_CPU_ABI)/include \
$(LOCAL_PATH)/libs/math/src/tr1
LOCAL_CFLAGS := -D__ANDROID__ -DANDROID
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH) 
LOCAL_EXPORT_CFLAGS := 
LOCAL_EXPORT_LDLIBS := 
LOCAL_ARM_MODE          := arm

include $(BUILD_STATIC_LIBRARY)
