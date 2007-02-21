;##############################################################################################################
; Script d'installation Inno Setup (5.1.7) pour scilab
; Allan CORNET
; Version TRUNK
; Copyright INRIA 2007
;##############################################################################################################
;--------------------------------------------------------------------------------------------------------------
; mexlib module
;--------------------------------------------------------------------------------------------------------------
;
#define MEXLIB "mexlib"
;
Source: bin\libmx.dll; DestDir: {app}\bin; Components: {#COMPN_MEXLIB}; Check: set_with_mexlib
Source: bin\libmex.dll; DestDir: {app}\bin; Components: {#COMPN_MEXLIB}
Source: bin\libmat.dll; DestDir: {app}\bin; Components: {#COMPN_MEXLIB}
;
Source: modules\{#MEXLIB}\VERSION; DestDir: {app}\modules\{#MEXLIB}; Components: {#COMPN_MEXLIB}
Source: modules\{#MEXLIB}\readme.txt; DestDir: {app}\modules\{#MEXLIB}; Components: {#COMPN_MEXLIB}
Source: modules\{#MEXLIB}\licence.txt; DestDir: {app}\modules\{#MEXLIB}; Components: {#COMPN_MEXLIB}
Source: modules\{#MEXLIB}\changelog.txt; DestDir: {app}\modules\{#MEXLIB}; Components: {#COMPN_MEXLIB}
;
Source: modules\{#MEXLIB}\etc\{#MEXLIB}.quit; DestDir: {app}\modules\{#MEXLIB}\etc; Components: {#COMPN_MEXLIB}
Source: modules\{#MEXLIB}\etc\{#MEXLIB}.start; DestDir: {app}\modules\{#MEXLIB}\etc; Components: {#COMPN_MEXLIB}
;
Source: modules\{#MEXLIB}\help\en_US\addchapter.sce; DestDir: {app}\modules\{#MEXLIB}\help\en_US; Components:  {#COMPN_MEXLIB}
Source: modules\{#MEXLIB}\help\en_US\removechapter.sce; DestDir: {app}\modules\{#MEXLIB}\help\en_US; Components: {#COMPN_MEXLIB}
;
Source: modules\{#MEXLIB}\help\fr_FR\addchapter.sce; DestDir: {app}\modules\{#MEXLIB}\help\fr_FR; Components:  {#COMPN_MEXLIB}
Source: modules\{#MEXLIB}\help\fr_FR\removechapter.sce; DestDir: {app}\modules\{#MEXLIB}\help\fr_FR; Components: {#COMPN_MEXLIB}
;
;
;Source: modules\{#MEXLIB}\help\en_US\*.htm; DestDir: {app}\modules\{#MEXLIB}\help\en_US; Components: {#COMPN_MEXLIB}
;Source: modules\{#MEXLIB}\help\fr_FR\*.htm; DestDir: {app}\modules\{#MEXLIB}\help\fr_FR; Components: {#COMPN_MEXLIB}
;
Source: modules\{#MEXLIB}\includes\*.h; DestDir: {app}\modules\{#MEXLIB}\includes; Components: {#COMPN_MEXLIB}
;
;Source: modules\{#MEXLIB}\macros\lib; DestDir: {app}\modules\{#MEXLIB}\macros; Components: {#COMPN_MEXLIB}
;Source: modules\{#MEXLIB}\macros\names; DestDir: {app}\modules\{#MEXLIB}\macros; Components: {#COMPN_MEXLIB}
;Source: modules\{#MEXLIB}\macros\*.bin; DestDir: {app}\modules\{#MEXLIB}\macros; Components: {#COMPN_MEXLIB}
;Source: modules\{#MEXLIB}\macros\*.sci; DestDir: {app}\modules\{#MEXLIB}\macros; Components: {#COMPN_MEXLIB}
Source: modules\{#MEXLIB}\macros\buildmacros.sce; DestDir: {app}\modules\{#MEXLIB}\macros; Components: {#COMPN_MEXLIB}
;
;Source: modules\{#MEXLIB}\demos\*.*; DestDir: {app}\modules\{#MEXLIB}\demos; Flags: recursesubdirs; Components: {#COMPN_MEXLIB}
;
Source: modules\{#MEXLIB}\examples\*.*; DestDir: {app}\modules\{#MEXLIB}\examples; Flags: recursesubdirs; Components: {#COMPN_MEXLIB}
;
;--------------------------------------------------------------------------------------------------------------
