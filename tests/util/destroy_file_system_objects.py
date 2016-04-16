#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os

# variables
BASE_DIR = os.path.abspath('tests/data/file_system')

for root, dirs, files in os.walk(BASE_DIR, topdown=False):
    for name in files:
        p = os.path.join(root, name)
        if os.path.islink(p):
            os.unlink(p)
        else:
            os.remove(p)
    for name in dirs:
        p = os.path.join(root, name)
        if os.path.islink(p):
            os.unlink(p)
        else:
            os.rmdir(p)
