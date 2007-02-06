;##############################################################################################################
; Script d'installation Inno Setup (5.1.7) pour scilab
; Allan CORNET
; Version TRUNK
; Copyright INRIA 2007
;##############################################################################################################
;--------------------------------------------------------------------------------------------------------------
; gui module
;--------------------------------------------------------------------------------------------------------------
;
#define GUI "gui"
;
Source: modules\{#GUI}\VERSION; DestDir: {app}\modules\{#GUI}; Components: {#COMPN_SCILAB}
Source: modules\{#GUI}\readme.txt; DestDir: {app}\modules\{#GUI}; Components: {#COMPN_SCILAB}
Source: modules\{#GUI}\licence.txt; DestDir: {app}\modules\{#GUI}; Components: {#COMPN_SCILAB}
Source: modules\{#GUI}\changelog.txt; DestDir: {app}\modules\{#GUI}; Components: {#COMPN_SCILAB}
;
Source: modules\{#GUI}\sci_gateway\gui; DestDir: {app}\modules\{#GUI}\sci_gateway; Components: {#COMPN_SCILAB}
;
Source: modules\{#GUI}\etc\{#GUI}.quit; DestDir: {app}\modules\{#GUI}\etc; Components: {#COMPN_SCILAB}
Source: modules\{#GUI}\etc\{#GUI}.start; DestDir: {app}\modules\{#GUI}\etc; Components: {#COMPN_SCILAB}
;
Source: modules\{#GUI}\help\en\addchapter.sce; DestDir: {app}\modules\{#GUI}\help\en; Components:  {#COMPN_SCILAB}
Source: modules\{#GUI}\help\en\removechapter.sce; DestDir: {app}\modules\{#GUI}\help\en; Components: {#COMPN_SCILAB}
;
Source: modules\{#GUI}\help\fr\addchapter.sce; DestDir: {app}\modules\{#GUI}\help\fr; Components:  {#COMPN_SCILAB}
Source: modules\{#GUI}\help\fr\removechapter.sce; DestDir: {app}\modules\{#GUI}\help\fr; Components: {#COMPN_SCILAB}
;
Source: modules\{#GUI}\help\en\*.htm; DestDir: {app}\modules\{#GUI}\help\en; Components: {#COMPN_SCILAB}
Source: modules\{#GUI}\help\fr\*.htm; DestDir: {app}\modules\{#GUI}\help\fr; Components: {#COMPN_SCILAB}
;
Source: modules\{#GUI}\includes\*.h; DestDir: {app}\modules\{#GUI}\includes; Components: {#COMPN_SCILAB}
;
Source: modules\{#GUI}\macros\lib; DestDir: {app}\modules\{#GUI}\macros; Flags: recursesubdirs; Components: {#COMPN_SCILAB}
Source: modules\{#GUI}\macros\names; DestDir: {app}\modules\{#GUI}\macros; Flags: recursesubdirs; Components: {#COMPN_SCILAB}
Source: modules\{#GUI}\macros\*.bin; DestDir: {app}\modules\{#GUI}\macros; Flags: recursesubdirs; Components: {#COMPN_SCILAB}
Source: modules\{#GUI}\macros\*.sci; DestDir: {app}\modules\{#GUI}\macros; Flags: recursesubdirs; Components: {#COMPN_SCILAB}
Source: modules\{#GUI}\macros\buildmacros.sce; DestDir: {app}\modules\{#GUI}\macros; Flags: recursesubdirs; Components: {#COMPN_SCILAB}
;
Source: modules\{#GUI}\demos\*.*; DestDir: {app}\modules\{#GUI}\demos; Flags: recursesubdirs; Components: {#COMPN_SCILAB}
;
;--------------------------------------------------------------------------------------------------------------
