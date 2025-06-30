#!/bin/bash

REPORT="Report.txt"
BUILD_LOG="build.log"
VALGRIND_LOG="valgrind.log"


>"$REPORT"
>"$BUILD_LOG"

echo "------- GIT PULL -----------" >> "$REPORT"
git pull > "$REPORT" 2>&1

echo -e "\n------- BUILD ---------" >> "$REPORT"
make clean > "$BUILD_LOG" 2>&1
make linux > "$BUILD_LOG" 2>&1

echo -e "\n------- Warnings ----------" >> "$REPORT"
grep -i "Warning:" "$BUILD_LOG" >> "$REPORT"
BUILD_RESULT=$?

if [ $BUILD_RESULT -ne 0 ]; then
    echo "\nNo Warning Found" >> "$REPORT"
fi

echo -e "\n----- STATIC ANALYSIS (CPPCHECK) -------" >> "$REPORT"
cppcheck --enable=all --inconclusive --std=c99 . 2>> "$REPORT"

echo -e "\n------Memory Leak--------------">> "$REPORT"
BINARY_SRC="release/TimerApp"
BINARY="./$BINARY_SRC"

if [ -x "$BINARY" ]; then
    valgrind --leak-check=full "$BINARY" 2>> "$REPORT"
else
    echo -e "\nBinary not found" >> "$REPORT"
fi