
set-android:
    xmake f -p android -a arm64-v8a --ndk=~/Android/Sdk/ndk/28.0.12674087/ --android_sdk=~/Android/Sdk/ --ndk_sdkver=28 -c -v

set-jetson:
    xmake f -p linux -a arm64 -c -v

set-default:
    xmake f -p linux -a x86_64 -c
