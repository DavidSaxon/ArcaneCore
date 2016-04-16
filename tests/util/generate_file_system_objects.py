#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys

# variables
BASE_DIR = os.path.abspath('tests/data/file_system')
TEST_DIR = os.path.join(BASE_DIR, 'test_dir')
UNI_DIR = os.path.join(BASE_DIR, '測試_निर्देशिका')

# functions
def make_dir(p):
    if not os.path.exists(p):
        os.makedirs(p)

def touch_file(p):
    f = open(p, 'w+')
    f.close()

def make_symlink(source, link):
    if not os.path.exists(link):
        try:
            os.symlink(source, link)
        except FileExistsError:
            pass

# make directories
make_dir(TEST_DIR)
make_dir(os.path.join(TEST_DIR, 'test_dir'))
make_dir(UNI_DIR)
make_dir(os.path.join(UNI_DIR, '測試_निर्देशिका'))

# make files
touch_file(os.path.join(BASE_DIR, 'test_file.txt'))
touch_file(os.path.join(TEST_DIR, 'test_file.txt'))
touch_file(os.path.join(BASE_DIR, 'file with spaces.png'))
touch_file(os.path.join(BASE_DIR, 'ການທົດສອບ.טֶקסט'))
touch_file(os.path.join(UNI_DIR, 'ການທົດສອບ.טֶקסט'))

if sys.platform != 'win32':
    # make symbolic links to files
    make_symlink(
        os.path.join(TEST_DIR, 'test_file.txt'),
        os.path.join(BASE_DIR, 'symlink')
    )
    make_symlink(
        os.path.join(BASE_DIR, 'test_file.txt'),
        os.path.join(TEST_DIR, 'symlink')
    )
    make_symlink(
        os.path.join(BASE_DIR, 'ການທົດສອບ.טֶקסט'),
        os.path.join(UNI_DIR, 'प्रतिकात्मकਲਿੰਕ')
    )
    make_symlink(
        os.path.join(UNI_DIR, 'ການທົດສອບ.טֶקסט'),
        os.path.join(BASE_DIR, 'rəmzi링크')
    )
    # make symbolic links to directories
    make_symlink(
        os.path.join(TEST_DIR, 'test_dir'),
        os.path.join(BASE_DIR, 'dir_symlink')
    )
    make_symlink(
        TEST_DIR,
        os.path.join(TEST_DIR, 'dir_symlink')
    )
    # make broken symlinks
    make_symlink(
        os.path.join(BASE_DIR, 'garbage/path.txt'),
        os.path.join(BASE_DIR, 'broken_link')
    )
    make_symlink(
        os.path.join(TEST_DIR, 'another/garbage/path'),
        os.path.join(TEST_DIR, 'broken_link')
    )

# list structure
LIST_BASE = os.path.join(BASE_DIR, 'list_dir')
LIST_DIR_A_1 = os.path.join(LIST_BASE, 'dir_a_1')
LIST_DIR_A_2 = os.path.join(LIST_BASE, 'dir_a_2')

make_dir(LIST_BASE)
make_dir(LIST_DIR_A_1)
make_dir(LIST_DIR_A_2)
make_dir(os.path.join(LIST_DIR_A_1, 'dir_b_1'))
make_dir(os.path.join(LIST_DIR_A_1, 'dir_b_2'))
make_dir(os.path.join(LIST_DIR_A_2, 'dir_c_1'))
make_dir(os.path.join(LIST_DIR_A_2, 'dir_c_2'))

touch_file(os.path.join(LIST_BASE, 'file_a_1'))
touch_file(os.path.join(LIST_BASE, 'file_a_2'))
touch_file(os.path.join(LIST_DIR_A_1, 'file_b_1'))
touch_file(os.path.join(LIST_DIR_A_1, 'file_b_2'))
touch_file(os.path.join(LIST_DIR_A_1, 'dir_b_1/file_d_1'))
touch_file(os.path.join(LIST_DIR_A_1, 'dir_b_1/file_d_2'))
touch_file(os.path.join(LIST_DIR_A_1, 'dir_b_2/file_e_1'))
touch_file(os.path.join(LIST_DIR_A_1, 'dir_b_2/file_e_2'))
touch_file(os.path.join(LIST_DIR_A_2, 'file_c_1'))
touch_file(os.path.join(LIST_DIR_A_2, 'file_c_2'))
touch_file(os.path.join(LIST_DIR_A_2, 'dir_c_1/file_f_1'))
touch_file(os.path.join(LIST_DIR_A_2, 'dir_c_1/file_f_2'))
touch_file(os.path.join(LIST_DIR_A_2, 'dir_c_2/file_g_1'))
touch_file(os.path.join(LIST_DIR_A_2, 'dir_c_2/file_g_2'))


