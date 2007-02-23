;##############################################################################################################
; Script d'installation Inno Setup (5.1.7) pour scilab
; Allan CORNET
; Version TRUNK
; Copyright INRIA 2007
;##############################################################################################################
;--------------------------------------------------------------------------------------------------------------
; core module
;--------------------------------------------------------------------------------------------------------------
;
#define CORE "core"
;
Source: modules\{#CORE}\VERSION; DestDir: {app}\modules\{#CORE}; Components: {#COMPN_SCILAB}
Source: modules\{#CORE}\readme.txt; DestDir: {app}\modules\{#CORE}; Components: {#COMPN_SCILAB}
Source: modules\{#CORE}\licence.txt; DestDir: {app}\modules\{#CORE}; Components: {#COMPN_SCILAB}
Source: modules\{#CORE}\changelog.txt; DestDir: {app}\modules\{#CORE}; Components: {#COMPN_SCILAB}
;
Source: modules\{#CORE}\sci_gateway\core; DestDir: {app}\modules\{#CORE}\sci_gateway; Components: {#COMPN_SCILAB}
;
Source: modules\{#CORE}\etc\{#CORE}.quit; DestDir: {app}\modules\{#CORE}\etc; Components: {#COMPN_SCILAB}
Source: modules\{#CORE}\etc\{#CORE}.start; DestDir: {app}\modules\{#CORE}\etc; Components: {#COMPN_SCILAB}
;
Source: modules\{#CORE}\help\en_US\addchapter.sce; DestDir: {app}\modules\{#CORE}\help\en_US; Components:  {#COMPN_SCILAB}
Source: modules\{#CORE}\help\en_US\removechapter.sce; DestDir: {app}\modules\{#CORE}\help\en_US; Components:  {#COMPN_SCILAB}
;
Source: modules\{#CORE}\help\fr_FR\addchapter.sce; DestDir: {app}\modules\{#CORE}\help\fr_FR; Components:  {#COMPN_SCILAB}
Source: modules\{#CORE}\help\fr_FR\removechapter.sce; DestDir: {app}\modules\{#CORE}\help\fr_FR; Components:  {#COMPN_SCILAB}
;
Source: modules\{#CORE}\help\en_US\*.htm; DestDir: {app}\modules\{#CORE}\help\en_US; Components: {#COMPN_SCILAB}
Source: modules\{#CORE}\help\fr_FR\*.htm; DestDir: {app}\modules\{#CORE}\help\fr_FR; Components: {#COMPN_SCILAB}
;
Source: modules\{#CORE}\includes\*.h; DestDir: {app}\modules\{#CORE}\includes; Components: {#COMPN_SCILAB}
;
Source: modules\{#CORE}\macros\buildmacros.sce; DestDir: {app}\modules\{#CORE}\macros; Components: {#COMPN_SCILAB}
Source: modules\{#CORE}\macros\lib; DestDir: {app}\modules\{#CORE}\macros; Components: {#COMPN_SCILAB}
Source: modules\{#CORE}\macros\names; DestDir: {app}\modules\{#CORE}\macros; Components: {#COMPN_SCILAB}
Source: modules\{#CORE}\macros\*.bin; DestDir: {app}\modules\{#CORE}\macros; Components: {#COMPN_SCILAB}
Source: modules\{#CORE}\macros\*.sci; DestDir: {app}\modules\{#CORE}\macros; Components: {#COMPN_SCILAB}
;
Source: modules\{#CORE}\demos\*.*; DestDir: {app}\modules\{#CORE}\demos; Flags: recursesubdirs; Components: {#COMPN_SCILAB}
;
Source: modules\{#CORE}\examples\*.*; DestDir: {app}\modules\{#CORE}\examples; Flags: recursesubdirs; Components: {#COMPN_SCILAB}
;
;--------------------------------------------------------------------------------------------------------------
