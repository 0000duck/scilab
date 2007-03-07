;##############################################################################################################
; Script d'installation Inno Setup (5.1.7) pour scilab
; Allan CORNET
; Version TRUNK
; Copyright INRIA 2007
;##############################################################################################################
;--------------------------------------------------------------------------------------------------------------
; SCI2C module
;--------------------------------------------------------------------------------------------------------------
;
#define SCI2C "sci2c"
;
Source: modules\{#SCI2C}\VERSION; DestDir: {app}\modules\{#SCI2C}; Components: {#COMPN_SCI2C}; Check: set_with_SCI2C
Source: modules\{#SCI2C}\readme.txt; DestDir: {app}\modules\{#SCI2C}; Components: {#COMPN_SCI2C}
Source: modules\{#SCI2C}\licence.txt; DestDir: {app}\modules\{#SCI2C}; Components: {#COMPN_SCI2C}
Source: modules\{#SCI2C}\changelog.txt; DestDir: {app}\modules\{#SCI2C}; Components: {#COMPN_SCI2C}
;
Source: modules\{#SCI2C}\sci_gateway\SCI2C; DestDir: {app}\modules\{#SCI2C}\sci_gateway; Components: {#COMPN_SCI2C}
;
Source: modules\{#SCI2C}\etc\{#SCI2C}.quit; DestDir: {app}\modules\{#SCI2C}\etc; Components: {#COMPN_SCI2C}
Source: modules\{#SCI2C}\etc\{#SCI2C}.start; DestDir: {app}\modules\{#SCI2C}\etc; Components: {#COMPN_SCI2C}
;
Source: modules\{#SCI2C}\help\en_US\addchapter.sce; DestDir: {app}\modules\{#SCI2C}\help\en_US; Components:  {#COMPN_SCI2C}
Source: modules\{#SCI2C}\help\en_US\removechapter.sce; DestDir: {app}\modules\{#SCI2C}\help\en_US; Components: {#COMPN_SCI2C}
;
Source: modules\{#SCI2C}\help\fr_FR\addchapter.sce; DestDir: {app}\modules\{#SCI2C}\help\fr_FR; Components:  {#COMPN_SCI2C}
Source: modules\{#SCI2C}\help\fr_FR\removechapter.sce; DestDir: {app}\modules\{#SCI2C}\help\fr_FR; Components: {#COMPN_SCI2C}
;
Source: modules\{#SCI2C}\help\en_US\*.htm; DestDir: {app}\modules\{#SCI2C}\help\en_US; Components: {#COMPN_SCI2C}
Source: modules\{#SCI2C}\help\fr_FR\*.htm; DestDir: {app}\modules\{#SCI2C}\help\fr_FR; Components: {#COMPN_SCI2C}
;
Source: modules\{#SCI2C}\languages\en_US\*.xml; DestDir: {app}\modules\{#SCI2C}\languages\en_US; Components: {#COMPN_SCI2C}
Source: modules\{#SCI2C}\languages\fr_FR\*.xml; DestDir: {app}\modules\{#SCI2C}\languages\fr_FR; Components: {#COMPN_SCI2C}
;
Source: modules\{#SCI2C}\includes\*.h; DestDir: {app}\modules\{#SCI2C}\includes; Components: {#COMPN_SCI2C}
;
;Source: modules\{#SCI2C}\macros\lib; DestDir: {app}\modules\{#SCI2C}\macros; Flags: recursesubdirs; Components: {#COMPN_SCI2C}
;Source: modules\{#SCI2C}\macros\names; DestDir: {app}\modules\{#SCI2C}\macros; Flags: recursesubdirs; Components: {#COMPN_SCI2C}
;Source: modules\{#SCI2C}\macros\*.bin; DestDir: {app}\modules\{#SCI2C}\macros; Flags: recursesubdirs; Components: {#COMPN_SCI2C}
;Source: modules\{#SCI2C}\macros\*.sci; DestDir: {app}\modules\{#SCI2C}\macros; Flags: recursesubdirs; Components: {#COMPN_SCI2C}
Source: modules\{#SCI2C}\macros\buildmacros.sce; DestDir: {app}\modules\{#SCI2C}\macros; Flags: recursesubdirs; Components: {#COMPN_SCI2C}
;
Source: modules\{#SCI2C}\demos\*.*; DestDir: {app}\modules\{#SCI2C}\demos; Flags: recursesubdirs; Components: {#COMPN_SCI2C}
;
;--------------------------------------------------------------------------------------------------------------
