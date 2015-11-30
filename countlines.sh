#!/bin/bash
cd ./source/src
find . -name '*.cpp' | xargs wc -l
cd ../header
find . -name '*.h' | xargs wc -l
