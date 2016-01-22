#!/usr/bin/env python

# this script is a prototype for what Sigma will be able to do..

import os
import shutil
import sys


# --- globals ---

ARGS = [ 'all', 'tests', 'libs', 'deploy' ]
TEST_LOG_PATH = 'logs/tests/log.xml'
BUILD_DIR = 'build/linux_x86'
SRC_DIR = 'src/cxx'

DIVIDER = '-' * 80


# --- read args ---

if len( sys.argv ) > 2:
    print( 'ERROR: No more than one build argument may be provided.' )
    exit()

mode = ARGS[ 0 ]
if len( sys.argv ) > 1:
    mode = sys.argv[ 1 ]

if not mode in ARGS:
    print( 'ERROR: Unknown mode: {0}.'.format( mode ) )
    exit()


# --- compile ---

if mode != 'deploy':

    print( DIVIDER )
    print( '                                    compiling...' )
    print( DIVIDER )

    # TODO: compile for windows

    make_command = 'make '
    if mode == 'libs':
        make_command += 'chaoscore_base chaoscore_io chaoscore_gfx chaoscore_test'
    else:
        make_command += mode

    os.system( make_command )

# --- run tests ---

test_passed = True
# if mode == 'all' or mode == 'tests':

#     # TODO: path for windows

#     test_command = \
#             './build/linux_x86/tests --stdout pretty 3 --fileout {0} xml 3' \
#             .format( TEST_LOG_PATH )

#     os.system( test_command )

#     with open( TEST_LOG_PATH, 'r' ) as f:
#         for line in f:
#             if line.startswith( '  <FinalSummary' ):
#                 components = line.strip().split( ' ' )
#                 for comp in components:
#                     if comp.startswith( 'UnitsFailed' ) or \
#                        comp.startswith( 'UnitsErrored' ):
#                         count = int( comp.split( '=' )[ 1 ] )
#                         if count != 0:
#                             test_passed = False


# --- deploy ---

if mode == 'all' or mode == 'deploy':

    print( DIVIDER )
    print( '                                    deploying...' )
    print( DIVIDER )

    if not test_passed:
        print( 'TESTS FAILED: Deployment halted.' )
        exit()

    # get semantic version
    major = 0
    minor = 0
    patch = 0
    with open( 'semver', 'r' ) as f:
        for line in f:
            if line.startswith( 'MAJOR' ):
                major = int( line.split( ' ' )[ 1 ] )
            elif line.startswith( 'MINOR' ):
                minor = int( line.split( ' ' )[ 1 ] )
            elif line.startswith( 'PATCH' ):
                patch = int( line.split( ' ' )[ 1 ] )

    # increment patch
    patch += 1

    # generate deployment name name
    deploy_name = 'ChaosCore-{0}.{1}.{2}'.format( major, minor, patch )
    deploy_location = 'deploy/' + deploy_name

    # does it exist?
    if os.path.exists( deploy_location ):
        print( 'ERROR: deployment directory already exists. Halting.' )
        exit()

    os.makedirs( deploy_location )

    # create the lib directory
    libs_location = deploy_location + '/lib'
    os.makedirs( libs_location )

    # move libs in
    for f in os.listdir( BUILD_DIR ):
        if f.endswith( '.so' ) or f.endswith( '.dll' ):
            shutil.copy( BUILD_DIR + '/' + f, libs_location )

    # create the include directory
    include_location = deploy_location + '/include'
    os.makedirs( include_location )

    # traverse src dir and copy headers
    for root, dirs, files in os.walk( SRC_DIR ):
        current_dir = include_location + root[ len( SRC_DIR ) : ]
        # create the directories
        for d in dirs:
            os.makedirs( current_dir + '/' + d )
        # copy files
        for f in files:
            if not f.startswith( '__' ) and f.endswith( '.hpp' ):
                shutil.copy( root + '/' + f, current_dir )

    # write back to semantic version file
    with open( 'semver', 'w' ) as f:
        f.write( 'MAJOR {0}\n'.format( major ) )
        f.write( 'MINOR {0}\n'.format( minor ) )
        f.write( 'PATCH {0}\n'.format( patch ) )

    print( '\nDEPLOYMENT NAME: {0}\n'.format( deploy_name ) )


print( DIVIDER )
print( '                                      done' )
print( DIVIDER )
