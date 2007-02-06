;##############################################################################################################
; Script d'installation Inno Setup (5.1.7) pour scilab
; Allan CORNET
; Version TRUNK
; Copyright INRIA 2007
;##############################################################################################################
;--------------------------------------------------------------------------------------------------------------
; scipad module
;--------------------------------------------------------------------------------------------------------------
;
#define SCIPAD "scipad"
;
Source: modules\{#SCIPAD}\VERSION; DestDir: {app}\modules\{#SCIPAD}; Components: {#COMPN_SCIPAD}; Check: set_with_scipad
Source: modules\{#SCIPAD}\readme.txt; DestDir: {app}\modules\{#SCIPAD}; Components: {#COMPN_SCIPAD}
Source: modules\{#SCIPAD}\licence.txt; DestDir: {app}\modules\{#SCIPAD}; Components: {#COMPN_SCIPAD}
Source: modules\{#SCIPAD}\changelog.txt; DestDir: {app}\modules\{#SCIPAD}; Components: {#COMPN_SCIPAD}
;
Source: modules\{#SCIPAD}\etc\{#SCIPAD}.quit; DestDir: {app}\modules\{#SCIPAD}\etc; Components: {#COMPN_SCIPAD}
Source: modules\{#SCIPAD}\etc\{#SCIPAD}.start; DestDir: {app}\modules\{#SCIPAD}\etc; Components: {#COMPN_SCIPAD}
;
Source: modules\{#SCIPAD}\help\en\addchapter.sce; DestDir: {app}\modules\{#SCIPAD}\help\en; Components:  {#COMPN_SCIPAD}
Source: modules\{#SCIPAD}\help\en\removechapter.sce; DestDir: {app}\modules\{#SCIPAD}\help\en; Components: {#COMPN_SCIPAD}
;
Source: modules\{#SCIPAD}\help\fr\addchapter.sce; DestDir: {app}\modules\{#SCIPAD}\help\fr; Components:  {#COMPN_SCIPAD}
Source: modules\{#SCIPAD}\help\fr\removechapter.sce; DestDir: {app}\modules\{#SCIPAD}\help\fr; Components: {#COMPN_SCIPAD}
;
Source: modules\{#SCIPAD}\help\en\*.htm; DestDir: {app}\modules\{#SCIPAD}\help\en; Components: {#COMPN_SCIPAD}
Source: modules\{#SCIPAD}\help\fr\*.htm; DestDir: {app}\modules\{#SCIPAD}\help\fr; Components: {#COMPN_SCIPAD}
;
Source: modules\{#SCIPAD}\macros\lib; DestDir: {app}\modules\{#SCIPAD}\macros; Components: {#COMPN_SCIPAD}
Source: modules\{#SCIPAD}\macros\names; DestDir: {app}\modules\{#SCIPAD}\macros; Components: {#COMPN_SCIPAD}
Source: modules\{#SCIPAD}\macros\*.bin; DestDir: {app}\modules\{#SCIPAD}\macros; Components: {#COMPN_SCIPAD}
Source: modules\{#SCIPAD}\macros\*.sci; DestDir: {app}\modules\{#SCIPAD}\macros; Components: {#COMPN_SCIPAD}
;
Source: modules\{#SCIPAD}\macros\scipad_internals\lib; DestDir: {app}\modules\{#SCIPAD}\macros\scipad_internals; Components: {#COMPN_SCIPAD}
Source: modules\{#SCIPAD}\macros\scipad_internals\names; DestDir: {app}\modules\{#SCIPAD}\macros\scipad_internals; Components: {#COMPN_SCIPAD}
Source: modules\{#SCIPAD}\macros\scipad_internals\*.sci; DestDir: {app}\modules\{#SCIPAD}\macros\scipad_internals; Components: {#COMPN_SCIPAD}
Source: modules\{#SCIPAD}\macros\scipad_internals\*.bin; DestDir: {app}\modules\{#SCIPAD}\macros\scipad_internals; Components: {#COMPN_SCIPAD}
Source: modules\{#SCIPAD}\macros\scipad_internals\dynamickeywords.sce; DestDir: {app}\modules\{#SCIPAD}\macros\scipad_internals; Components: {#COMPN_SCIPAD}
;
Source: modules\{#SCIPAD}\macros\buildmacros.sce; DestDir: {app}\modules\{#SCIPAD}\macros; Components: {#COMPN_SCIPAD}
;
Source: modules\{#SCIPAD}\tcl\*.*; DestDir: {app}\modules\{#SCIPAD}\tcl; Flags: recursesubdirs; Components: {#COMPN_SCIPAD}
;
;--------------------------------------------------------------------------------------------------------------
