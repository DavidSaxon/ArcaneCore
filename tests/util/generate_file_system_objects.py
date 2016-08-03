#!/usr/bin/env python
# -*- coding: utf-8 -*-

import codecs
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

# files to read
with open(os.path.join(BASE_DIR, 'empty_file'), 'bw+') as f:
    pass

with codecs.open(os.path.join(BASE_DIR, 'empty_file.utf8'), 'w', 'utf-8') as f:
    f.write(u'\ufeff')

with open(os.path.join(BASE_DIR, 'ascii.linux.txt'), 'bw+') as f:
    f.write(b'Hello World!\n')
    f.write(b'This is another line.\n')
    f.write(b'\n')
    f.write(b'\t\t     \t\t\n')
    f.write(b'And another line.\n')
    f.write(b'And some symbols:\n')
    f.write(b'$&*@$)@@\":\">?|\n')
    f.write(b'>>End of Transmission<<\n')

with open(os.path.join(BASE_DIR, 'ascii.windows.txt'), 'bw+') as f:
    f.write(b'Hello World!\r\n')
    f.write(b'This is another line.\r\n')
    f.write(b'\r\n')
    f.write(b'\t\t     \t\t\r\n')
    f.write(b'And another line.\r\n')
    f.write(b'And some symbols:\r\n')
    f.write(b'$&*@$)@@\":\">?|\r\n')
    f.write(b'>>End of Transmission<<\r\n')

with codecs.open(
        os.path.join(BASE_DIR, 'utf8.linux.txt'), 'bw+', 'utf-8-sig') as f:
    f.write(u'Hello World!\n')
    f.write(u'γειά σου Κόσμε\n')
    f.write(u'\n')
    f.write(u'\t\t     \t\t\n')
    f.write(u'this is a مزيج of text\n')
    f.write(u'간\n')
    f.write(u'𐂣\n')

with codecs.open(
        os.path.join(BASE_DIR, 'utf8.windows.txt'), 'bw+', 'utf-8-sig') as f:
    f.write(u'Hello World!\r\n')
    f.write(u'γειά σου Κόσμε\r\n')
    f.write(u'\r\n')
    f.write(u'\t\t     \t\t\r\n')
    f.write(u'this is a مزيج of text\r\n')
    f.write(u'간\r\n')
    f.write(u'𐂣\r\n')

with codecs.open(
        os.path.join(BASE_DIR, 'utf16le.linux.txt'), 'bw+') as f:
    f.write(codecs.BOM_UTF16_LE)
    f.write('Hello World!\n'.encode('utf-16-le'))
    f.write('γειά σου Κόσμε\n'.encode('utf-16-le'))
    f.write('\n'.encode('utf-16-le'))
    f.write('\t\t     \t\t\n'.encode('utf-16-le'))
    f.write('this is a مزيج of text\n'.encode('utf-16-le'))
    f.write('간\n'.encode('utf-16-le'))
    f.write('𐂣\n'.encode('utf-16-le'))

with codecs.open(
        os.path.join(BASE_DIR, 'utf16le.windows.txt'), 'bw+') as f:
    f.write(codecs.BOM_UTF16_LE)
    f.write('Hello World!\r\n'.encode('utf-16-le'))
    f.write('γειά σου Κόσμε\r\n'.encode('utf-16-le'))
    f.write('\r\n'.encode('utf-16-le'))
    f.write('\t\t     \t\t\r\n'.encode('utf-16-le'))
    f.write('this is a مزيج of text\r\n'.encode('utf-16-le'))
    f.write('간\r\n'.encode('utf-16-le'))
    f.write('𐂣\r\n'.encode('utf-16-le'))

with codecs.open(
        os.path.join(BASE_DIR, 'utf16be.linux.txt'), 'bw+') as f:
    f.write(codecs.BOM_UTF16_BE)
    f.write('Hello World!\n'.encode('utf-16-be'))
    f.write('γειά σου Κόσμε\n'.encode('utf-16-be'))
    f.write('\n'.encode('utf-16-be'))
    f.write('\t\t     \t\t\n'.encode('utf-16-be'))
    f.write('this is a مزيج of text\n'.encode('utf-16-be'))
    f.write('간\n'.encode('utf-16-be'))
    f.write('𐂣\n'.encode('utf-16-be'))

with codecs.open(
        os.path.join(BASE_DIR, 'utf16be.windows.txt'), 'bw+') as f:
    f.write(codecs.BOM_UTF16_BE)
    f.write('Hello World!\r\n'.encode('utf-16-be'))
    f.write('γειά σου Κόσμε\r\n'.encode('utf-16-be'))
    f.write('\r\n'.encode('utf-16-be'))
    f.write('\t\t     \t\t\r\n'.encode('utf-16-be'))
    f.write('this is a مزيج of text\r\n'.encode('utf-16-be'))
    f.write('간\r\n'.encode('utf-16-be'))
    f.write('𐂣\r\n'.encode('utf-16-be'))
