;##############################################################################################################
; Script d'installation Inno Setup (5.2.1) pour scilab
; Allan CORNET
; Version TRUNK
; Copyright INRIA 2007
;##############################################################################################################
;--------------------------------------------------------------------------------------------------------------
; FFTW module
;--------------------------------------------------------------------------------------------------------------
;
#define FFTW "fftw"
;

Source: modules\{#FFTW}\VERSION.xml; DestDir: {app}\modules\{#FFTW}; Components: {#COMPN_FFTW}; Check: set_with_fftw
Source: modules\{#FFTW}\readme.txt; DestDir: {app}\modules\{#FFTW}; Components: {#COMPN_FFTW}
Source: modules\{#FFTW}\licence.txt; DestDir: {app}\modules\{#FFTW}; Components: {#COMPN_FFTW}
Source: modules\{#FFTW}\changelog.txt; DestDir: {app}\modules\{#FFTW}; Components: {#COMPN_FFTW}
;
Source: modules\{#FFTW}\sci_gateway\fftw_gateway.xml; DestDir: {app}\modules\{#FFTW}\sci_gateway; Components: {#COMPN_FFTW}
;
Source: modules\{#FFTW}\etc\{#FFTW}.quit; DestDir: {app}\modules\{#FFTW}\etc; Components: {#COMPN_FFTW}
Source: modules\{#FFTW}\etc\{#FFTW}.start; DestDir: {app}\modules\{#FFTW}\etc; Components: {#COMPN_FFTW}
;
Source: modules\{#FFTW}\help\addchapter.sce; DestDir: {app}\modules\{#FFTW}\help; Flags: recursesubdirs; Components:  {#COMPN_FFTW}
;
;Source: modules\{#FFTW}\demos\*.*; DestDir: {app}\modules\{#FFTW}\demos; Flags: recursesubdirs; Components: {#COMPN_FFTW}
;
;Source: modules\{#FFTW}\help\*.htm; DestDir: {app}\modules\{#FFTW}\help; Flags: recursesubdirs; Components: {#COMPN_FFTW}
;
;
Source: modules\{#FFTW}\includes\*.h; Flags: recursesubdirs; DestDir: {app}\modules\{#FFTW}\includes; Components: {#COMPN_FFTW}
;
;Source: modules\{#FFTW}\macros\lib; DestDir: {app}\modules\{#FFTW}\macros; Components: {#COMPN_FFTW}
;Source: modules\{#FFTW}\macros\names; DestDir: {app}\modules\{#FFTW}\macros; Components: {#COMPN_FFTW}
;Source: modules\{#FFTW}\macros\*.bin; DestDir: {app}\modules\{#FFTW}\macros; Components: {#COMPN_FFTW}
;Source: modules\{#FFTW}\macros\*.sci; DestDir: {app}\modules\{#FFTW}\macros; Components: {#COMPN_FFTW}
Source: modules\{#FFTW}\macros\buildmacros.sce; DestDir: {app}\modules\{#FFTW}\macros; Components: {#COMPN_FFTW}
Source: modules\{#FFTW}\macros\buildmacros.bat; DestDir: {app}\modules\{#FFTW}\macros; Components: {#COMPN_FFTW}
Source: modules\{#FFTW}\macros\cleanmacros.bat; DestDir: {app}\modules\{#FFTW}\macros; Components: {#COMPN_FFTW}
;
Source: bin\fftw.dll; DestDir: {app}\bin; DestName: fftw.dll; Components: {#COMPN_FFTW}
Source: bin\nofftw.dll; DestDir: {app}\bin; DestName: fftw.dll; Components: not ({#COMPN_FFTW})
;
;Source: modules\{#FFTW}\nonreg_tests\*.*; DestDir: {app}\modules\{#FFTW}\nonreg_tests; Flags: recursesubdirs; Components: {#COMPN_FFTW} and {#COMPN_NO_REGRESSION_TESTS}
;
;Source: modules\{#FFTW}\unit_tests\*.ref; DestDir: {app}\modules\{#FFTW}\unit_tests; Flags: recursesubdirs; Components: {#COMPN_FFTW} and {#COMPN_UNIT_TESTS}
;Source: modules\{#FFTW}\unit_tests\*.tst; DestDir: {app}\modules\{#FFTW}\unit_tests; Flags: recursesubdirs; Components: {#COMPN_FFTW} and {#COMPN_UNIT_TESTS}
;
;--------------------------------------------------------------------------------------------------------------
