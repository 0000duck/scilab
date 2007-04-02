;##############################################################################################################
; Script d'installation Inno Setup (5.1.7) pour scilab
; Allan CORNET
; Version TRUNK
; Copyright INRIA 2007
;##############################################################################################################
;--------------------------------------------------------------------------------------------------------------
; linear_algebra module
;--------------------------------------------------------------------------------------------------------------
;
#define LINALG "linear_algebra"
;
Source: bin\linear_algebra.dll; DestDir: {app}\bin; Components: {#COMPN_LINALG}
Source: bin\linear_algebra_f.dll; DestDir: {app}\bin; Components: {#COMPN_LINALG}
;
Source: modules\{#LINALG}\VERSION; DestDir: {app}\modules\{#LINALG}; Components: {#COMPN_LINALG}; Check: set_with_linear_algebra
Source: modules\{#LINALG}\readme.txt; DestDir: {app}\modules\{#LINALG}; Components: {#COMPN_LINALG}
Source: modules\{#LINALG}\licence.txt; DestDir: {app}\modules\{#LINALG}; Components: {#COMPN_LINALG}
Source: modules\{#LINALG}\changelog.txt; DestDir: {app}\modules\{#LINALG}; Components: {#COMPN_LINALG}
;
Source: modules\{#LINALG}\sci_gateway\linear_algebra; DestDir: {app}\modules\{#LINALG}\sci_gateway; Components: {#COMPN_LINALG}
;
Source: modules\{#LINALG}\etc\{#LINALG}.quit; DestDir: {app}\modules\{#LINALG}\etc; Components: {#COMPN_LINALG}
Source: modules\{#LINALG}\etc\{#LINALG}.start; DestDir: {app}\modules\{#LINALG}\etc; Components: {#COMPN_LINALG}
;
Source: modules\{#LINALG}\help\addchapter.sce; DestDir: {app}\modules\{#LINALG}\help; Flags: recursesubdirs; Components:  {#COMPN_LINALG}
Source: modules\{#LINALG}\help\removechapter.sce; DestDir: {app}\modules\{#LINALG}\help; Flags: recursesubdirs; Components: {#COMPN_LINALG}
;
Source: modules\{#LINALG}\help\*.htm; DestDir: {app}\modules\{#LINALG}\help; Flags: recursesubdirs; Components: {#COMPN_LINALG}
;
Source: modules\{#LINALG}\languages\*.xml; DestDir: {app}\modules\{#LINALG}\languages; Flags: recursesubdirs; Components: {#COMPN_LINALG}
;
Source: modules\{#LINALG}\includes\*.h; DestDir: {app}\modules\{#LINALG}\includes; Components: {#COMPN_LINALG}
;
Source: modules\{#LINALG}\macros\buildmacros.sce; DestDir: {app}\modules\{#LINALG}\macros; Components: {#COMPN_LINALG}
Source: modules\{#LINALG}\macros\lib; DestDir: {app}\modules\{#LINALG}\macros; Components: {#COMPN_LINALG}
Source: modules\{#LINALG}\macros\names; DestDir: {app}\modules\{#LINALG}\macros; Components: {#COMPN_LINALG}
Source: modules\{#LINALG}\macros\*.bin; DestDir: {app}\modules\{#LINALG}\macros; Components: {#COMPN_LINALG}
Source: modules\{#LINALG}\macros\*.sci; DestDir: {app}\modules\{#LINALG}\macros; Components: {#COMPN_LINALG}
;
;Source: modules\{#LINALG}\demos\*.*; DestDir: {app}\modules\{#LINALG}\demos; Flags: recursesubdirs;  Components: {#COMPN_LINALG}
;
Source: modules\{#LINALG}\examples\*.*; DestDir: {app}\modules\{#LINALG}\examples; Flags: recursesubdirs;  Components: {#COMPN_LINALG}
;
;--------------------------------------------------------------------------------------------------------------
