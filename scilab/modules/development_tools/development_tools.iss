;##############################################################################################################
; Script d'installation Inno Setup (5.1.7) pour scilab
; Allan CORNET
; Version TRUNK
; Copyright INRIA 2007
;##############################################################################################################
;--------------------------------------------------------------------------------------------------------------
; development_tools module
;--------------------------------------------------------------------------------------------------------------
;
#define DEVTOOLS "development_tools"
;
Source: modules\{#DEVTOOLS}\VERSION; DestDir: {app}\modules\{#DEVTOOLS}; Components: {#COMPN_DEVTOOLS}; Check: set_with_{#COMPN_DEVTOOLS}
Source: modules\{#DEVTOOLS}\readme.txt; DestDir: {app}\modules\{#DEVTOOLS}; Components: {#COMPN_DEVTOOLS}
Source: modules\{#DEVTOOLS}\licence.txt; DestDir: {app}\modules\{#DEVTOOLS}; Components: {#COMPN_DEVTOOLS}
Source: modules\{#DEVTOOLS}\changelog.txt; DestDir: {app}\modules\{#DEVTOOLS}; Components: {#COMPN_DEVTOOLS}
;
Source: modules\{#DEVTOOLS}\etc\{#DEVTOOLS}.quit; DestDir: {app}\modules\{#DEVTOOLS}\etc; Components: {#COMPN_DEVTOOLS}
Source: modules\{#DEVTOOLS}\etc\{#DEVTOOLS}.start; DestDir: {app}\modules\{#DEVTOOLS}\etc; Components: {#COMPN_DEVTOOLS}
;
Source: modules\{#DEVTOOLS}\help\fr_FR\addchapter.sce; DestDir: {app}\modules\{#DEVTOOLS}\help\fr_FR; Components:  {#COMPN_DEVTOOLS}
Source: modules\{#DEVTOOLS}\help\fr_FR\removechapter.sce; DestDir: {app}\modules\{#DEVTOOLS}\help\fr_FR; Components:  {#COMPN_DEVTOOLS}
;
Source: modules\{#DEVTOOLS}\help\en_US\addchapter.sce; DestDir: {app}\modules\{#DEVTOOLS}\help\en_US; Components:  {#COMPN_DEVTOOLS}
Source: modules\{#DEVTOOLS}\help\en_US\removechapter.sce; DestDir: {app}\modules\{#DEVTOOLS}\help\en_US; Components:  {#COMPN_DEVTOOLS}
;
;Source: modules\{#DEVTOOLS}\help\en_US\*.htm; DestDir: {app}\modules\{#DEVTOOLS}\help\en_US; Components: {#COMPN_DEVTOOLS}
;Source: modules\{#DEVTOOLS}\help\fr_FR\*.htm; DestDir: {app}\modules\{#DEVTOOLS}\help\fr_FR; Components: {#COMPN_DEVTOOLS}
;
Source: modules\{#DEVTOOLS}\languages\en_US\*.xml; DestDir: {app}\modules\{#DEVTOOLS}\languages\en_US; Components: {#COMPN_DEVTOOLS}
Source: modules\{#DEVTOOLS}\languages\fr_FR\*.xml; DestDir: {app}\modules\{#DEVTOOLS}\languages\fr_FR; Components: {#COMPN_DEVTOOLS}
;
;Source: modules\{#DEVTOOLS}\includes\*.h; DestDir: {app}\modules\{#DEVTOOLS}\includes; Components: {#COMPN_DEVTOOLS}
;
Source: modules\{#DEVTOOLS}\macros\lib; DestDir: {app}\modules\{#DEVTOOLS}\macros; Components: {#COMPN_DEVTOOLS}
Source: modules\{#DEVTOOLS}\macros\names; DestDir: {app}\modules\{#DEVTOOLS}\macros; Components: {#COMPN_DEVTOOLS}
Source: modules\{#DEVTOOLS}\macros\*.bin; DestDir: {app}\modules\{#DEVTOOLS}\macros; Components: {#COMPN_DEVTOOLS}
Source: modules\{#DEVTOOLS}\macros\*.sci; DestDir: {app}\modules\{#DEVTOOLS}\macros; Components: {#COMPN_DEVTOOLS}
Source: modules\{#DEVTOOLS}\macros\buildmacros.sce; DestDir: {app}\modules\{#DEVTOOLS}\macros; Components: {#COMPN_DEVTOOLS}
;
;Source: modules\{#DEVTOOLS}\demos\*.*; DestDir: {app}\modules\{#DEVTOOLS}\demos; Flags: recursesubdirs; Components: {#COMPN_DEVTOOLS}
;
Source: modules\{#DEVTOOLS}\examples\*.*; DestDir: {app}\modules\{#DEVTOOLS}\examples; Flags: recursesubdirs; Components: {#COMPN_DEVTOOLS}
;
;--------------------------------------------------------------------------------------------------------------
