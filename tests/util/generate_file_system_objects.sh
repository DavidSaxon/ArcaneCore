#!/bin/bash

echo
echo "Generating file system objects for testing..."

# variables
CWD=$(pwd)
BASE_DIR="${CWD}/tests/data/file_system"
TEST_DIR="${BASE_DIR}/test_dir"
UNI_DIR1="${BASE_DIR}/測試_निर्देशिका"

# make directories
mkdir "${TEST_DIR}"
mkdir "${TEST_DIR}/test_dir"
mkdir "${UNI_DIR1}"
mkdir "${UNI_DIR1}/測試_निर्देशिका"

# make files
touch "${BASE_DIR}/test_file.txt"
touch "${TEST_DIR}/test_file.txt"
touch "${BASE_DIR}/file with spaces.png"
touch "${BASE_DIR}/ການທົດສອບ.טֶקסט"
touch "${UNI_DIR1}/ການທົດສອບ.טֶקסט"

# make symbolic links to files
ln -s "${TEST_DIR}/test_file.txt" "${BASE_DIR}/symlink"
ln -s "${BASE_DIR}/test_file.txt" "${TEST_DIR}/symlink"
ln -s "${UNI_DIR1}/ການທົດສອບ.טֶקסט" "${BASE_DIR}/rəmzi링크"
ln -s "${BASE_DIR}/ການທົດສອບ.טֶקסט" "${UNI_DIR1}/प्रतिकात्मकਲਿੰਕ"

# make symbolic links to directories
ln -s "${TEST_DIR}/test_dir" "${BASE_DIR}/dir_symlink"
ln -s "${TEST_DIR}" "${TEST_DIR}/dir_symlink"

# make broken symbolic links
ln -s "${BASE_DIR}/garbage/path.txt" "${BASE_DIR}/broken_link"
ln -s "${TEST_DIR}another/garbage/path" "${TEST_DIR}/broken_link"

echo "Done."
