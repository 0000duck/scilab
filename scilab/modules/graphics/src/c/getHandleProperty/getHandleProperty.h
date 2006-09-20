/*------------------------------------------------------------------------*/
/* file: getHandleProperty.h                                              */
/* Copyright INRIA 2006                                                   */
/* Authors : Fabrice Leray, Allan Cornet, Jean-Baptiste Silvy             */
/* desc : contains definitions of functions needed by sci_get             */
/*        Each function has the same signature int (sciPointObj *) and    */
/*        return a value in the scilab console                            */
/*------------------------------------------------------------------------*/

#ifndef _GET_HANDLE_PROPERTY_H_
#define _GET_HANDLE_PROPERTY_H_

#include "ObjectStructure.h"

int get_figures_id_property(          sciPointObj * pobj ) ;
int get_visible_property(             sciPointObj * pobj ) ;
int get_pixel_drawing_mode_property(  sciPointObj * pobj ) ;
int get_old_style_property(           sciPointObj * pobj ) ;
int get_figure_style_property(        sciPointObj * pobj ) ;
int get_auto_resize_property(         sciPointObj * pobj ) ;
int get_figure_position_property(     sciPointObj * pobj ) ;
int get_axes_size_property(           sciPointObj * pobj ) ;
int get_figure_size_property(         sciPointObj * pobj ) ;
int get_figure_name_property(         sciPointObj * pobj ) ;
int get_figure_id_property(           sciPointObj * pobj ) ;
int get_rotation_style_property(      sciPointObj * pobj ) ;
int get_immediate_drawing_property(   sciPointObj * pobj ) ;
int get_pixmap_property(              sciPointObj * pobj ) ;
int get_type_property(                sciPointObj * pobj ) ;
int get_parent_property(              sciPointObj * pobj ) ;
int get_current_axes_property(        sciPointObj * pobj ) ;
int get_current_figure_property(      sciPointObj * pobj ) ;
int get_current_entity_property(      sciPointObj * pobj ) ;
int get_children_property(            sciPointObj * pobj ) ;
int get_default_figure_property(      sciPointObj * pobj ) ;
int get_default_axes_property(        sciPointObj * pobj ) ;
int get_color_map_property(           sciPointObj * pobj ) ;
int get_interp_color_vector_property( sciPointObj * pobj ) ;
int get_interp_color_mode_property(   sciPointObj * pobj ) ;
int get_background_property(          sciPointObj * pobj ) ;
int get_foreground_property(          sciPointObj * pobj ) ;
int get_fill_mode_property(           sciPointObj * pobj ) ;
int get_thickness_property(           sciPointObj * pobj ) ;
int get_arrow_size_factor_property(   sciPointObj * pobj ) ;
int get_line_style_property(          sciPointObj * pobj ) ;
int get_line_mode_property(           sciPointObj * pobj ) ;
int get_surface_mode_property(        sciPointObj * pobj ) ;
int get_mark_style_property(          sciPointObj * pobj ) ;
int get_mark_mode_property(           sciPointObj * pobj ) ;
int get_mark_size_unit_property(      sciPointObj * pobj ) ;
int get_mark_size_property(           sciPointObj * pobj ) ;
int get_mark_foreground_property(     sciPointObj * pobj ) ;
int get_mark_background_property(     sciPointObj * pobj ) ;
int get_bar_layout_property(          sciPointObj * pobj ) ;
int get_bar_width_property(           sciPointObj * pobj ) ;
int get_x_shift_property(             sciPointObj * pobj ) ;
int get_y_shift_property(             sciPointObj * pobj ) ;
int get_z_shift_property(             sciPointObj * pobj ) ;
int get_polyline_style_property(      sciPointObj * pobj ) ;
int get_font_size_property(           sciPointObj * pobj ) ;
int get_font_angle_property(          sciPointObj * pobj ) ;
int get_font_foreground_property(     sciPointObj * pobj ) ;
int get_font_color_property(          sciPointObj * pobj ) ;
int get_font_style_property(          sciPointObj * pobj ) ;
int get_font_name_property(           sciPointObj * pobj ) ;
int get_text_box_mode_property(       sciPointObj * pobj ) ;
int get_auto_dimensionning_property(  sciPointObj * pobj ) ;
int get_alignment_property(           sciPointObj * pobj ) ;
int get_text_box_property(            sciPointObj * pobj ) ;
int get_text_property(                sciPointObj * pobj ) ;
int get_auto_clear_property(          sciPointObj * pobj ) ;
int get_auto_scale_property(          sciPointObj * pobj ) ;
int get_zoom_box_property(            sciPointObj * pobj ) ;
int get_zoom_state_property(          sciPointObj * pobj ) ;
int get_clip_box_property(            sciPointObj * pobj ) ;
int get_clip_state_property(          sciPointObj * pobj ) ;
int get_data_property(                sciPointObj * pobj ) ;
int get_callbackmevent_property(      sciPointObj * pobj ) ;
int get_callback_property(            sciPointObj * pobj ) ;
int get_x_label_property(             sciPointObj * pobj ) ;
int get_y_label_property(             sciPointObj * pobj ) ;
int get_z_label_property(             sciPointObj * pobj ) ;
int get_title_property(               sciPointObj * pobj ) ;
int get_log_flags_property(           sciPointObj * pobj ) ;
int get_tics_direction_property(      sciPointObj * pobj ) ;
int get_x_location_property(          sciPointObj * pobj ) ;
int get_y_location_property(          sciPointObj * pobj ) ;
int get_tight_limits_property(        sciPointObj * pobj ) ;
int get_closed_property(              sciPointObj * pobj ) ;
int get_auto_position_property(       sciPointObj * pobj ) ;
int get_auto_rotation_property(       sciPointObj * pobj ) ;
int get_position_property(            sciPointObj * pobj ) ;
int get_auto_ticks_property(          sciPointObj * pobj ) ;
int get_axes_reverse_property(        sciPointObj * pobj ) ;
int get_view_property(                sciPointObj * pobj ) ;
int get_axes_bounds_property(         sciPointObj * pobj ) ;
int get_data_bounds_property(         sciPointObj * pobj ) ;
int get_margins_property(             sciPointObj * pobj ) ;
int get_tics_color_property(          sciPointObj * pobj ) ;
int get_tics_style_property(          sciPointObj * pobj ) ;
int get_sub_tics_property(            sciPointObj * pobj ) ;
int get_tics_segment_property(        sciPointObj * pobj ) ;
int get_labels_font_size_property(    sciPointObj * pobj ) ;
int get_labels_font_color_property(   sciPointObj * pobj ) ;
int get_labels_font_style_property(   sciPointObj * pobj ) ;
int get_labels_format_n_property(     sciPointObj * pobj ) ;
int get_xtics_coord_property(         sciPointObj * pobj ) ;
int get_ytics_coord_property(         sciPointObj * pobj ) ;
int get_tics_label_property(          sciPointObj * pobj ) ;
int get_box_property(                 sciPointObj * pobj ) ;
int get_grid_property(                sciPointObj * pobj ) ;
int get_axes_visible_property(        sciPointObj * pobj ) ;
int get_hidden_color_property(        sciPointObj * pobj ) ;
int get_isoview_property(             sciPointObj * pobj ) ;
int get_cube_scaling_property(        sciPointObj * pobj ) ;
int get_arrow_size_property(          sciPointObj * pobj ) ;
int get_colored_property(             sciPointObj * pobj ) ;
int get_data_mapping_property(        sciPointObj * pobj ) ;
int get_rotation_angles_property(     sciPointObj * pobj ) ;
int get_color_mode_property(          sciPointObj * pobj ) ;
int get_color_flag_property(          sciPointObj * pobj ) ;
int get_cdata_mapping_property(       sciPointObj * pobj ) ;
int get_surface_color_property(       sciPointObj * pobj ) ;
int get_triangles_property(           sciPointObj * pobj ) ;
int get_z_bounds_property(            sciPointObj * pobj ) ;
int get_user_data_property(           sciPointObj * pobj ) ;
int get_handle_visible_property(      sciPointObj * pobj ) ;
int get_callback_type_property(       sciPointObj * pobj ) ;
int get_menu_enable_property(         sciPointObj * pobj ) ;
int get_hidden_axis_color_property(   sciPointObj * pobj ) ;
int get_x_ticks_property(             sciPointObj * pobj ) ;
int get_y_ticks_property(             sciPointObj * pobj ) ;
int get_z_ticks_property(             sciPointObj * pobj ) ;

#endif /* _GET_HANDLE_PROPERTY_H_ */
