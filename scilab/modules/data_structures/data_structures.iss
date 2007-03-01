;##############################################################################################################
; Script d'installation Inno Setup (5.1.7) pour scilab
; Allan CORNET
; Version TRUNK
; Copyright INRIA 2007
;##############################################################################################################
;--------------------------------------------------------------------------------------------------------------
; data_structures module
;--------------------------------------------------------------------------------------------------------------
;
#define DATASTRUCT "data_structures"
;
Source: modules\{#DATASTRUCT}\VERSION; DestDir: {app}\modules\{#DATASTRUCT}; Components: {#COMPN_SCILAB}
Source: modules\{#DATASTRUCT}\readme.txt; DestDir: {app}\modules\{#DATASTRUCT}; Components: {#COMPN_SCILAB}
Source: modules\{#DATASTRUCT}\licence.txt; DestDir: {app}\modules\{#DATASTRUCT}; Components: {#COMPN_SCILAB}
Source: modules\{#DATASTRUCT}\changelog.txt; DestDir: {app}\modules\{#DATASTRUCT}; Components: {#COMPN_SCILAB}
;
Source: modules\{#DATASTRUCT}\sci_gateway\data_structures; DestDir: {app}\modules\{#DATASTRUCT}\sci_gateway; Components: {#COMPN_SCILAB}
;
Source: modules\{#DATASTRUCT}\etc\{#DATASTRUCT}.quit; DestDir: {app}\modules\{#DATASTRUCT}\etc; Components: {#COMPN_SCILAB}
Source: modules\{#DATASTRUCT}\etc\{#DATASTRUCT}.start; DestDir: {app}\modules\{#DATASTRUCT}\etc; Components: {#COMPN_SCILAB}
;
Source: modules\{#DATASTRUCT}\help\en_US\addchapter.sce; DestDir: {app}\modules\{#DATASTRUCT}\help\en_US; Components:  {#COMPN_SCILAB}
Source: modules\{#DATASTRUCT}\help\en_US\removechapter.sce; DestDir: {app}\modules\{#DATASTRUCT}\help\en_US; Components:  {#COMPN_SCILAB}
;
Source: modules\{#DATASTRUCT}\help\fr_FR\addchapter.sce; DestDir: {app}\modules\{#DATASTRUCT}\help\fr_FR; Components:  {#COMPN_SCILAB}
Source: modules\{#DATASTRUCT}\help\fr_FR\removechapter.sce; DestDir: {app}\modules\{#DATASTRUCT}\help\fr_FR; Components:  {#COMPN_SCILAB}
;
Source: modules\{#DATASTRUCT}\help\en_US\*.htm; DestDir: {app}\modules\{#DATASTRUCT}\help\en_US; Components: {#COMPN_SCILAB}
Source: modules\{#DATASTRUCT}\help\fr_FR\*.htm; DestDir: {app}\modules\{#DATASTRUCT}\help\fr_FR; Components: {#COMPN_SCILAB}
;
Source: modules\{#DATASTRUCT}\languages\en_US\*.xml; DestDir: {app}\modules\{#DATASTRUCT}\languages\en_US; Components: {#COMPN_SCILAB}
Source: modules\{#DATASTRUCT}\languages\fr_FR\*.xml; DestDir: {app}\modules\{#DATASTRUCT}\languages\fr_FR; Components: {#COMPN_SCILAB}
;
Source: modules\{#DATASTRUCT}\includes\*.h; DestDir: {app}\modules\{#DATASTRUCT}\includes; Components: {#COMPN_SCILAB}
;
Source: modules\{#DATASTRUCT}\macros\lib; DestDir: {app}\modules\{#DATASTRUCT}\macros; Components: {#COMPN_SCILAB}
Source: modules\{#DATASTRUCT}\macros\names; DestDir: {app}\modules\{#DATASTRUCT}\macros; Components: {#COMPN_SCILAB}
Source: modules\{#DATASTRUCT}\macros\*.bin; DestDir: {app}\modules\{#DATASTRUCT}\macros; Components: {#COMPN_SCILAB}
Source: modules\{#DATASTRUCT}\macros\*.sci; DestDir: {app}\modules\{#DATASTRUCT}\macros; Components: {#COMPN_SCILAB}
Source: modules\{#DATASTRUCT}\macros\buildmacros.sce; DestDir: {app}\modules\{#DATASTRUCT}\macros; Components: {#COMPN_SCILAB}
;
;Source: modules\{#DATASTRUCT}\demos\*.*; DestDir: {app}\modules\{#DATASTRUCT}\demos; Flags: recursesubdirs; Components: {#COMPN_SCILAB}
;
;--------------------------------------------------------------------------------------------------------------
