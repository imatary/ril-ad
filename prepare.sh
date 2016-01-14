#!/usr/bin/env bash
adb wait-for-device
adb root

sleep 2

adb push ./adapter.cfg /data/local/tmp/adapter.cfg
adb shell 'mv /data/local/tmp/libwrapper_ril.so /data/local/tmp/libwrapper_ril.so.backup'
adb push ./out/libwrapper_ril.so /data/local/tmp/libwrapper_ril.so
PID=$(adb shell ps | grep rild | awk '{print $2}')
adb shell "kill -9 ${PID}"