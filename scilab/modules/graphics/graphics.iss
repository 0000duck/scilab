;##############################################################################################################
; Script d'installation Inno Setup (5.1.7) pour scilab
; Allan CORNET
; Version TRUNK
; Copyright INRIA 2007
;##############################################################################################################
;--------------------------------------------------------------------------------------------------------------
; graphics module
;--------------------------------------------------------------------------------------------------------------
;
#define GRAPHICS "graphics"
;
Source: modules\{#GRAPHICS}\VERSION; DestDir: {app}\modules\{#GRAPHICS}; Components: {#COMPN_GRAPHICS}; Check: set_with_graphics
Source: modules\{#GRAPHICS}\readme.txt; DestDir: {app}\modules\{#GRAPHICS}; Components: {#COMPN_GRAPHICS}
Source: modules\{#GRAPHICS}\licence.txt; DestDir: {app}\modules\{#GRAPHICS}; Components: {#COMPN_GRAPHICS}
Source: modules\{#GRAPHICS}\changelog.txt; DestDir: {app}\modules\{#GRAPHICS}; Components: {#COMPN_GRAPHICS}
;
Source: modules\{#GRAPHICS}\sci_gateway\graphics; DestDir: {app}\modules\{#GRAPHICS}\sci_gateway; Components: {#COMPN_GRAPHICS}
;
Source: modules\{#GRAPHICS}\etc\{#GRAPHICS}.quit; DestDir: {app}\modules\{#GRAPHICS}\etc; Components: {#COMPN_GRAPHICS}
Source: modules\{#GRAPHICS}\etc\{#GRAPHICS}.start; DestDir: {app}\modules\{#GRAPHICS}\etc; Components: {#COMPN_GRAPHICS}
;
Source: modules\{#GRAPHICS}\help\eng\*.htm; DestDir: {app}\modules\{#GRAPHICS}\help\eng; Components: {#COMPN_GRAPHICS}
Source: modules\{#GRAPHICS}\help\fr\*.htm; DestDir: {app}\modules\{#GRAPHICS}\help\fr; Components: {#COMPN_GRAPHICS}
Source: modules\{#GRAPHICS}\help\images\*.gif; DestDir: {app}\modules\{#GRAPHICS}\images; Components: {#COMPN_GRAPHICS}
;
Source: modules\{#GRAPHICS}\includes\*.h; DestDir: {app}\modules\{#GRAPHICS}\includes; Components: {#COMPN_GRAPHICS}
;
Source: modules\{#GRAPHICS}\macros\buildmacros.sce; DestDir: {app}\modules\{#GRAPHICS}\macros; Components: {#COMPN_GRAPHICS}
Source: modules\{#GRAPHICS}\macros\lib; DestDir: {app}\modules\{#GRAPHICS}\macros; Components: {#COMPN_GRAPHICS}
Source: modules\{#GRAPHICS}\macros\names; DestDir: {app}\modules\{#GRAPHICS}\macros; Components: {#COMPN_GRAPHICS}
Source: modules\{#GRAPHICS}\macros\*.bin; DestDir: {app}\modules\{#GRAPHICS}\macros; Components: {#COMPN_GRAPHICS}
Source: modules\{#GRAPHICS}\macros\*.sci; DestDir: {app}\modules\{#GRAPHICS}\macros; Components: {#COMPN_GRAPHICS}
;
Source: modules\{#GRAPHICS}\tcl\*.*; DestDir: {app}\modules\{#GRAPHICS}\tcl; Flags: recursesubdirs; Components: {#COMPN_GRAPHICS}
;
Source: modules\{#GRAPHICS}\fonts\*bdf; DestDir: {app}\modules\{#GRAPHICS}\fonts; Flags: recursesubdirs; Components: {#COMPN_GRAPHICS}
;
Source: modules\{#GRAPHICS}\demos\*.*; DestDir: {app}\modules\{#GRAPHICS}\demos; Flags: recursesubdirs; Components: {#COMPN_GRAPHICS}
;
;--------------------------------------------------------------------------------------------------------------
