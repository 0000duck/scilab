;##############################################################################################################
; Script d'installation Inno Setup (5.2.1) pour scilab
; Allan CORNET
; Version TRUNK
; Copyright INRIA 2007
;##############################################################################################################
;--------------------------------------------------------------------------------------------------------------
; others module
;--------------------------------------------------------------------------------------------------------------
;
#define OTHERS "others"
;
Source: modules\{#OTHERS}\VERSION.xml; DestDir: {app}\modules\{#OTHERS}; Components: {#COMPN_OTHERS}; Check: set_with_others
Source: modules\{#OTHERS}\readme.txt; DestDir: {app}\modules\{#OTHERS}; Components: {#COMPN_OTHERS}
Source: modules\{#OTHERS}\licence.txt; DestDir: {app}\modules\{#OTHERS}; Components: {#COMPN_OTHERS}
Source: modules\{#OTHERS}\changelog.txt; DestDir: {app}\modules\{#OTHERS}; Components: {#COMPN_OTHERS}
;
Source: modules\{#OTHERS}\etc\{#OTHERS}.quit; DestDir: {app}\modules\{#OTHERS}\etc; Components: {#COMPN_OTHERS}
Source: modules\{#OTHERS}\etc\{#OTHERS}.start; DestDir: {app}\modules\{#OTHERS}\etc; Components: {#COMPN_OTHERS}
;
Source: modules\{#OTHERS}\help\addchapter.sce; DestDir: {app}\modules\{#OTHERS}\help; Flags: recursesubdirs; Components:  {#COMPN_OTHERS}
;
Source: modules\{#OTHERS}\help\*.htm; DestDir: {app}\modules\{#OTHERS}\help; Flags: recursesubdirs; Components: {#COMPN_OTHERS}
;
;
;Source: modules\{#OTHERS}\includes\*.h; DestDir: {app}\modules\{#OTHERS}\includes; Components: {#COMPN_OTHERS}
;
Source: modules\{#OTHERS}\macros\lib; DestDir: {app}\modules\{#OTHERS}\macros; Flags: recursesubdirs; Components: {#COMPN_OTHERS}
Source: modules\{#OTHERS}\macros\names; DestDir: {app}\modules\{#OTHERS}\macros; Flags: recursesubdirs; Components: {#COMPN_OTHERS}
Source: modules\{#OTHERS}\macros\*.bin; DestDir: {app}\modules\{#OTHERS}\macros; Flags: recursesubdirs; Components: {#COMPN_OTHERS}
Source: modules\{#OTHERS}\macros\*.sci; DestDir: {app}\modules\{#OTHERS}\macros; Flags: recursesubdirs; Components: {#COMPN_OTHERS}
Source: modules\{#OTHERS}\macros\buildmacros.sce; DestDir: {app}\modules\{#OTHERS}\macros; Flags: recursesubdirs; Components: {#COMPN_OTHERS}
Source: modules\{#OTHERS}\macros\cleanmacros.bat; DestDir: {app}\modules\{#OTHERS}\macros; Flags: recursesubdirs; Components: {#COMPN_OTHERS}
Source: modules\{#OTHERS}\macros\buildmacros.bat; DestDir: {app}\modules\{#OTHERS}\macros; Flags: recursesubdirs; Components: {#COMPN_OTHERS}
;
Source: modules\{#OTHERS}\demos\*.*; DestDir: {app}\modules\{#OTHERS}\demos; Flags: recursesubdirs; Components: {#COMPN_OTHERS}
;
Source: modules\{#OTHERS}\tests\*.*; DestDir: {app}\modules\{#OTHERS}\tests; Flags: recursesubdirs; Components: {#COMPN_OTHERS} and {#COMPN_TESTS}
;
;
;--------------------------------------------------------------------------------------------------------------
