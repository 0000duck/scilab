;##############################################################################################################
; Script d'installation Inno Setup (5.1.7) pour scilab
; Allan CORNET
; Version TRUNK
; Copyright INRIA 2007
;##############################################################################################################
;--------------------------------------------------------------------------------------------------------------
; differential_equations module
;--------------------------------------------------------------------------------------------------------------
;
#define DIFFEQU "differential_equations"
;
Source: modules\{#DIFFEQU}\VERSION; DestDir: {app}\modules\{#DIFFEQU}; Components: {#COMPN_EQUDIF}; Check: set_with_differential_equations
Source: modules\{#DIFFEQU}\readme.txt; DestDir: {app}\modules\{#DIFFEQU}; Components: {#COMPN_EQUDIF}
Source: modules\{#DIFFEQU}\licence.txt; DestDir: {app}\modules\{#DIFFEQU}; Components: {#COMPN_EQUDIF}
Source: modules\{#DIFFEQU}\changelog.txt; DestDir: {app}\modules\{#DIFFEQU}; Components: {#COMPN_EQUDIF}
;
Source: modules\{#DIFFEQU}\sci_gateway\differential_equations; DestDir: {app}\modules\{#DIFFEQU}\sci_gateway; Components: {#COMPN_EQUDIF}
;
Source: modules\{#DIFFEQU}\etc\{#DIFFEQU}.quit; DestDir: {app}\modules\{#DIFFEQU}\etc; Components: {#COMPN_EQUDIF}
Source: modules\{#DIFFEQU}\etc\{#DIFFEQU}.start; DestDir: {app}\modules\{#DIFFEQU}\etc; Components: {#COMPN_EQUDIF}
;
Source: modules\{#DIFFEQU}\help\en_US\addchapter.sce; DestDir: {app}\modules\{#DIFFEQU}\help\en_US; Components:  {#COMPN_EQUDIF}
Source: modules\{#DIFFEQU}\help\en_US\removechapter.sce; DestDir: {app}\modules\{#DIFFEQU}\help\en_US; Components:  {#COMPN_EQUDIF}
;
Source: modules\{#DIFFEQU}\help\fr_FR\addchapter.sce; DestDir: {app}\modules\{#DIFFEQU}\help\fr_FR; Components:  {#COMPN_EQUDIF}
Source: modules\{#DIFFEQU}\help\fr_FR\removechapter.sce; DestDir: {app}\modules\{#DIFFEQU}\help\fr_FR; Components:  {#COMPN_EQUDIF}
;
Source: modules\{#DIFFEQU}\help\en_US\*.htm; DestDir: {app}\modules\{#DIFFEQU}\help\en_US; Components: {#COMPN_EQUDIF}
Source: modules\{#DIFFEQU}\help\fr_FR\*.htm; DestDir: {app}\modules\{#DIFFEQU}\help\fr_FR; Components: {#COMPN_EQUDIF}
;
Source: modules\{#DIFFEQU}\languages\en_US\*.xml; DestDir: {app}\modules\{#DIFFEQU}\languages\en_US; Components: {#COMPN_EQUDIF}
Source: modules\{#DIFFEQU}\languages\fr_FR\*.xml; DestDir: {app}\modules\{#DIFFEQU}\languages\fr_FR; Components: {#COMPN_EQUDIF}
;
;Source: modules\{#DIFFEQU}\includes\*.h; DestDir: {app}\modules\{#DIFFEQU}\includes; Components: {#COMPN_EQUDIF}
;
Source: modules\{#DIFFEQU}\macros\lib; DestDir: {app}\modules\{#DIFFEQU}\macros; Flags: recursesubdirs; Components: {#COMPN_EQUDIF}
Source: modules\{#DIFFEQU}\macros\names; DestDir: {app}\modules\{#DIFFEQU}\macros; Flags: recursesubdirs; Components: {#COMPN_EQUDIF}
Source: modules\{#DIFFEQU}\macros\*.bin; DestDir: {app}\modules\{#DIFFEQU}\macros; Flags: recursesubdirs; Components: {#COMPN_EQUDIF}
Source: modules\{#DIFFEQU}\macros\*.sci; DestDir: {app}\modules\{#DIFFEQU}\macros; Flags: recursesubdirs; Components: {#COMPN_EQUDIF}
Source: modules\{#DIFFEQU}\macros\buildmacros.sce; DestDir: {app}\modules\{#DIFFEQU}\macros; Flags: recursesubdirs; Components: {#COMPN_EQUDIF}
;
;Source: modules\{#DIFFEQU}\demos\*.*; DestDir: {app}\modules\{#DIFFEQU}\demos; Flags: recursesubdirs; Components: {#COMPN_EQUDIF}
;
;--------------------------------------------------------------------------------------------------------------
