#!/bin/bash

# variables
CWD=$(pwd)
BASE_DIR="${CWD}/tests/data/file_system"
TEST_DIR="${BASE_DIR}/test_dir"
UNI_DIR1="${BASE_DIR}/測試_निर्देशिका"

# remove files
rm "${BASE_DIR}/test_file.txt" 2> /dev/null
rm "${TEST_DIR}/test_file.txt" 2> /dev/null
rm "${BASE_DIR}/file with spaces.png" 2> /dev/null
rm "${BASE_DIR}/ການທົດສອບ.טֶקסט" 2> /dev/null
rm "${UNI_DIR1}/ການທົດສອບ.טֶקסט" 2> /dev/null

# remove symbolic links to files
rm "${BASE_DIR}/symlink" 2> /dev/null
rm "${TEST_DIR}/symlink" 2> /dev/null
rm "${BASE_DIR}/rəmzi링크" 2> /dev/null
rm "${UNI_DIR1}/प्रतिकात्मकਲਿੰਕ" 2> /dev/null

# remove symbolic links to directories
rm "${BASE_DIR}/dir_symlink" 2> /dev/null
rm "${TEST_DIR}/dir_symlink" 2> /dev/null

# remove broken symbolic links
rm "${BASE_DIR}/broken_link" 2> /dev/null
rm "${TEST_DIR}/broken_link" 2> /dev/null

# remove directories
rm "${TEST_DIR}" 2> /dev/null
rm "${TEST_DIR}/test_dir" 2> /dev/null
rm "${UNI_DIR1}" 2> /dev/null
rm "${UNI_DIR1}/測試_निर्देशिका" 2> /dev/null

# list structure
LIST_BASE="${BASE_DIR}/list_dir"
LIST_DIR_A_1="${LIST_BASE}/dir_a_1"
LIST_DIR_A_2="${LIST_BASE}/dir_a_2"

rm "${LIST_BASE}/file_a_1" 2> /dev/null
rm "${LIST_BASE}/file_a_2" 2> /dev/null
rm "${LIST_DIR_A_1}/file_b_1" 2> /dev/null
rm "${LIST_DIR_A_1}/file_b_2" 2> /dev/null
rm "${LIST_DIR_A_1}/dir_b_1/file_d_1" 2> /dev/null
rm "${LIST_DIR_A_1}/dir_b_1/file_d_2" 2> /dev/null
rm "${LIST_DIR_A_1}/dir_b_2/file_e_1" 2> /dev/null
rm "${LIST_DIR_A_1}/dir_b_2/file_e_2" 2> /dev/null
rm "${LIST_DIR_A_2}/file_c_1" 2> /dev/null
rm "${LIST_DIR_A_2}/file_c_2" 2> /dev/null
rm "${LIST_DIR_A_2}/dir_c_1/file_f_1" 2> /dev/null
rm "${LIST_DIR_A_2}/dir_c_1/file_f_2" 2> /dev/null
rm "${LIST_DIR_A_2}/dir_c_2/file_g_1" 2> /dev/null
rm "${LIST_DIR_A_2}/dir_c_2/file_g_2" 2> /dev/null

rm "${LIST_BASE}" 2> /dev/null
rm "${LIST_DIR_A_1}" 2> /dev/null
rm "${LIST_DIR_A_2}" 2> /dev/null
rm "${LIST_DIR_A_1}/dir_b_1" 2> /dev/null
rm "${LIST_DIR_A_1}/dir_b_2" 2> /dev/null
rm "${LIST_DIR_A_2}/dir_c_1" 2> /dev/null
rm "${LIST_DIR_A_2}/dir_c_2" 2> /dev/null


