;##############################################################################################################
; Script d'installation Inno Setup (5.1.7) pour scilab
; Allan CORNET
; Version TRUNK
; Copyright INRIA 2007
;##############################################################################################################
;--------------------------------------------------------------------------------------------------------------
; special_functions module
;--------------------------------------------------------------------------------------------------------------
;
#define SPFUNCTIONS "special_functions"
;
Source: modules\{#SPFUNCTIONS}\VERSION; DestDir: {app}\modules\{#SPFUNCTIONS}; Components: {#COMPN_SCILAB}
Source: modules\{#SPFUNCTIONS}\readme.txt; DestDir: {app}\modules\{#SPFUNCTIONS}; Components: {#COMPN_SCILAB}
Source: modules\{#SPFUNCTIONS}\licence.txt; DestDir: {app}\modules\{#SPFUNCTIONS}; Components: {#COMPN_SCILAB}
Source: modules\{#SPFUNCTIONS}\changelog.txt; DestDir: {app}\modules\{#SPFUNCTIONS}; Components: {#COMPN_SCILAB}
;
Source: modules\{#SPFUNCTIONS}\sci_gateway\special_functions; DestDir: {app}\modules\{#SPFUNCTIONS}\sci_gateway; Components: {#COMPN_SCILAB}
;
Source: modules\{#SPFUNCTIONS}\etc\{#SPFUNCTIONS}.quit; DestDir: {app}\modules\{#SPFUNCTIONS}\etc; Components: {#COMPN_SCILAB}
Source: modules\{#SPFUNCTIONS}\etc\{#SPFUNCTIONS}.start; DestDir: {app}\modules\{#SPFUNCTIONS}\etc; Components: {#COMPN_SCILAB}
;
Source: modules\{#SPFUNCTIONS}\help\en\addchapter.sce; DestDir: {app}\modules\{#SPFUNCTIONS}\help\en; Components:  {#COMPN_SCILAB}
Source: modules\{#SPFUNCTIONS}\help\en\removechapter.sce; DestDir: {app}\modules\{#SPFUNCTIONS}\help\en; Components: {#COMPN_SCILAB}
;
Source: modules\{#SPFUNCTIONS}\help\fr\addchapter.sce; DestDir: {app}\modules\{#SPFUNCTIONS}\help\fr; Components:  {#COMPN_SCILAB}
Source: modules\{#SPFUNCTIONS}\help\fr\removechapter.sce; DestDir: {app}\modules\{#SPFUNCTIONS}\help\fr; Components: {#COMPN_SCILAB}
;
Source: modules\{#SPFUNCTIONS}\help\en\*.htm; DestDir: {app}\modules\{#SPFUNCTIONS}\help\en; Components: {#COMPN_SCILAB}
Source: modules\{#SPFUNCTIONS}\help\fr\*.htm; DestDir: {app}\modules\{#SPFUNCTIONS}\help\fr; Components: {#COMPN_SCILAB}
;
;Source: modules\{#SPFUNCTIONS}\includes\*.h; DestDir: {app}\modules\{#SPFUNCTIONS}\includes; Components: {#COMPN_SCILAB}
;
;Source: modules\{#SPFUNCTIONS}\macros\lib; DestDir: {app}\modules\{#SPFUNCTIONS}\macros; Flags: recursesubdirs; Components: {#COMPN_SCILAB}
;Source: modules\{#SPFUNCTIONS}\macros\names; DestDir: {app}\modules\{#SPFUNCTIONS}\macros; Flags: recursesubdirs; Components: {#COMPN_SCILAB}
;Source: modules\{#SPFUNCTIONS}\macros\*.bin; DestDir: {app}\modules\{#SPFUNCTIONS}\macros; Flags: recursesubdirs; Components: {#COMPN_SCILAB}
;Source: modules\{#SPFUNCTIONS}\macros\*.sci; DestDir: {app}\modules\{#SPFUNCTIONS}\macros; Flags: recursesubdirs; Components: {#COMPN_SCILAB}
Source: modules\{#SPFUNCTIONS}\macros\buildmacros.sce; DestDir: {app}\modules\{#SPFUNCTIONS}\macros; Flags: recursesubdirs; Components: {#COMPN_SCILAB}
;
;Source: modules\{#SPFUNCTIONS}\demos\*.*; DestDir: {app}\modules\{#SPFUNCTIONS}\demos; Flags: recursesubdirs; Components: {#COMPN_SCILAB}
;
;--------------------------------------------------------------------------------------------------------------
