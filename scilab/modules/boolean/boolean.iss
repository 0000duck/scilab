;##############################################################################################################
; Script d'installation Inno Setup (5.1.7) pour scilab
; Allan CORNET
; Version TRUNK
; Copyright INRIA 2007
;##############################################################################################################
;--------------------------------------------------------------------------------------------------------------
; boolean module
;--------------------------------------------------------------------------------------------------------------
;
#define BOOLEAN "boolean"
;
Source: modules\{#BOOLEAN}\VERSION; DestDir: {app}\modules\{#BOOLEAN}; Components: {#COMPN_SCILAB}
Source: modules\{#BOOLEAN}\readme.txt; DestDir: {app}\modules\{#BOOLEAN}; Components: {#COMPN_SCILAB}
Source: modules\{#BOOLEAN}\licence.txt; DestDir: {app}\modules\{#BOOLEAN}; Components: {#COMPN_SCILAB}
Source: modules\{#BOOLEAN}\changelog.txt; DestDir: {app}\modules\{#BOOLEAN}; Components: {#COMPN_SCILAB}
;
Source: modules\{#BOOLEAN}\sci_gateway\boolean; DestDir: {app}\modules\{#BOOLEAN}\sci_gateway; Components: {#COMPN_SCILAB}
;
Source: modules\{#BOOLEAN}\etc\{#BOOLEAN}.quit; DestDir: {app}\modules\{#BOOLEAN}\etc; Components: {#COMPN_SCILAB}
Source: modules\{#BOOLEAN}\etc\{#BOOLEAN}.start; DestDir: {app}\modules\{#BOOLEAN}\etc; Components: {#COMPN_SCILAB}
;
Source: modules\{#BOOLEAN}\help\eng\*.htm; DestDir: {app}\modules\{#BOOLEAN}\help\eng; Components: {#COMPN_SCILAB}
Source: modules\{#BOOLEAN}\help\fr\*.htm; DestDir: {app}\modules\{#BOOLEAN}\help\fr; Components: {#COMPN_SCILAB}
;
Source: modules\{#BOOLEAN}\includes\*.h; DestDir: {app}\modules\{#BOOLEAN}\includes; Components: {#COMPN_SCILAB}
;
;Source: modules\{#BOOLEAN}\macros\lib; DestDir: {app}\modules\{#BOOLEAN}\macros; Components: {#COMPN_SCILAB}
;Source: modules\{#BOOLEAN}\macros\names; DestDir: {app}\modules\{#BOOLEAN}\macros; Components: {#COMPN_SCILAB}
;Source: modules\{#BOOLEAN}\macros\*.bin; DestDir: {app}\modules\{#BOOLEAN}\macros; Components: {#COMPN_SCILAB}
;Source: modules\{#BOOLEAN}\macros\*.sci; DestDir: {app}\modules\{#BOOLEAN}\macros; Components: {#COMPN_SCILAB}
Source: modules\{#BOOLEAN}\macros\buildmacros.sce; DestDir: {app}\modules\{#BOOLEAN}\macros; Components: {#COMPN_SCILAB}
;
;Source: modules\{#BOOLEAN}\demos\*.*; DestDir: {app}\modules\{#BOOLEAN}\demos; Components: {#COMPN_SCILAB}
;
;--------------------------------------------------------------------------------------------------------------

