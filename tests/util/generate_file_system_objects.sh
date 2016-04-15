#!/bin/bash

# variables
CWD=$(pwd)
BASE_DIR="${CWD}/tests/data/file_system"
TEST_DIR="${BASE_DIR}/test_dir"
UNI_DIR1="${BASE_DIR}/測試_निर्देशिका"

# make directories
mkdir "${TEST_DIR}" 2> /dev/null
mkdir "${TEST_DIR}/test_dir" 2> /dev/null
mkdir "${UNI_DIR1}" 2> /dev/null
mkdir "${UNI_DIR1}/測試_निर्देशिका" 2> /dev/null

# make files
touch "${BASE_DIR}/test_file.txt" 2> /dev/null
touch "${TEST_DIR}/test_file.txt" 2> /dev/null
touch "${BASE_DIR}/file with spaces.png" 2> /dev/null
touch "${BASE_DIR}/ການທົດສອບ.טֶקסט" 2> /dev/null
touch "${UNI_DIR1}/ການທົດສອບ.טֶקסט" 2> /dev/null

# make symbolic links to files
ln -s "${TEST_DIR}/test_file.txt" "${BASE_DIR}/symlink" 2> /dev/null
ln -s "${BASE_DIR}/test_file.txt" "${TEST_DIR}/symlink" 2> /dev/null
ln -s "${UNI_DIR1}/ການທົດສອບ.טֶקסט" "${BASE_DIR}/rəmzi링크" 2> /dev/null
ln -s "${BASE_DIR}/ການທົດສອບ.טֶקסט" "${UNI_DIR1}/प्रतिकात्मकਲਿੰਕ" 2> /dev/null

# make symbolic links to directories
ln -s "${TEST_DIR}/test_dir" "${BASE_DIR}/dir_symlink" 2> /dev/null
ln -s "${TEST_DIR}" "${TEST_DIR}/dir_symlink" 2> /dev/null

# make broken symbolic links
ln -s "${BASE_DIR}/garbage/path.txt" "${BASE_DIR}/broken_link" 2> /dev/null
ln -s "${TEST_DIR}another/garbage/path" "${TEST_DIR}/broken_link" 2> /dev/null
