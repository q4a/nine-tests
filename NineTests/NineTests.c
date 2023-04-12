/*
 * Copyright 2005, 2007-2008 Henri Verbeet
 * Copyright (C) 2007-2013 Stefan DÃ¶singer(for CodeWeavers)
 * Copyright (C) 2008 Jason Green(for TransGaming)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* These tests are directly adapted from wine d3d9 tests, thanks to the original authors.
 * The code was modified in 2016 */

#include <math.h>
#include <d3d9.h>
#ifndef _WIN32
#include "Xnine.h"

#include <unistd.h>
#endif
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
//#include "visual_mod.h"
#include "visual.h"

typedef void (*TestFunc)();

struct test_map {
    const char *name;
    TestFunc    func;
};

static const struct test_map w_test_map[] = {
    { "test_sanity", test_sanity },
    { "depth_clamp_test", depth_clamp_test },
    { "stretchrect_test", stretchrect_test },
    { "lighting_test", lighting_test },
    { "test_specular_lighting", test_specular_lighting },
    { "test_clear_different_size_surfaces", test_clear_different_size_surfaces },
    { "color_fill_test", color_fill_test },
    { "fog_test", fog_test },
    { "test_cube_wrap", test_cube_wrap },
    { "z_range_test", z_range_test },
    { "maxmip_test", maxmip_test },
    { "offscreen_test", offscreen_test },
    { "ds_size_test", ds_size_test },
    { "test_blend", test_blend },
    { "test_shademode", test_shademode },
    { "srgbtexture_test", srgbtexture_test },
    { "release_buffer_test", release_buffer_test },
    { "float_texture_test", float_texture_test },
    { "g16r16_texture_test", g16r16_texture_test },
    { "pixelshader_blending_test", pixelshader_blending_test },
    { "texture_transform_flags_test", texture_transform_flags_test },
    { "fixed_function_decl_test", fixed_function_decl_test },
    { "conditional_np2_repeat_test", conditional_np2_repeat_test },
    { "fixed_function_bumpmap_test", fixed_function_bumpmap_test },
    { "tssargtemp_test", tssargtemp_test },
    { "np2_stretch_rect_test", np2_stretch_rect_test },
    { "yuv_color_test", yuv_color_test },
    { "yuv_layout_test", yuv_layout_test },
    { "zwriteenable_test", zwriteenable_test },
    { "alphatest_test", alphatest_test },
    { "test_viewport", test_viewport },
    { "test_constant_clamp_vs", test_constant_clamp_vs },
    { "test_compare_instructions", test_compare_instructions },
    { "test_mova", test_mova },
    { "loop_index_test", loop_index_test },
    { "sgn_test", sgn_test },
    { "clip_planes_test", clip_planes_test },
    { "test_vshader_input", test_vshader_input },
    { "test_vshader_float16", test_vshader_float16 },
    { "stream_test", stream_test },
    { "fog_with_shader_test", fog_with_shader_test },
    { "texbem_test", texbem_test },
    { "texdepth_test", texdepth_test },
    { "texkill_test", texkill_test },
    { "volume_v16u16_test", volume_v16u16_test },
    { "constant_clamp_ps_test", constant_clamp_ps_test },
    { "cnd_test", cnd_test },
    { "dp2add_ps_test", dp2add_ps_test },
    { "unbound_sampler_test", unbound_sampler_test },
    { "nested_loop_test", nested_loop_test },
    { "pretransformed_varying_test", pretransformed_varying_test },
    { "vface_register_test", vface_register_test },
    { "test_fragment_coords", test_fragment_coords },
    { "multiple_rendertargets_test", multiple_rendertargets_test },
    { "texop_test", texop_test },
    { "texop_range_test", texop_range_test },
    { "alphareplicate_test", alphareplicate_test },
    { "dp3_alpha_test", dp3_alpha_test },
    { "depth_buffer_test", depth_buffer_test },
    { "depth_buffer2_test", depth_buffer2_test },
    { "intz_test", intz_test },
    { "shadow_test", shadow_test },
    { "fp_special_test", fp_special_test },
    { "depth_bounds_test", depth_bounds_test },
    { "srgbwrite_format_test", srgbwrite_format_test },
    { "update_surface_test", update_surface_test },
    { "multisample_get_rtdata_test", multisample_get_rtdata_test },
    { "test_multisample_get_front_buffer_data", test_multisample_get_front_buffer_data },
    { "zenable_test", zenable_test },
    { "fog_special_test", fog_special_test },
    { "volume_srgb_test", volume_srgb_test },
    { "volume_dxtn_test", volume_dxtn_test },
    { "add_dirty_rect_test", add_dirty_rect_test },
    { "multisampled_depth_buffer_test", multisampled_depth_buffer_test },
    { "resz_test", resz_test },
    { "stencil_cull_test", stencil_cull_test },
    { "test_per_stage_constant", test_per_stage_constant },
    { "test_3dc_formats", test_3dc_formats },
    { "test_fog_interpolation", test_fog_interpolation },
    { "test_negative_fixedfunction_fog", test_negative_fixedfunction_fog },
    { "test_position_index", test_position_index },
    { "test_table_fog_zw", test_table_fog_zw },
    { "test_table_shader_fog", test_table_shader_fog },
    { "test_signed_formats", test_signed_formats },
    { "test_multisample_mismatch", test_multisample_mismatch },
    { "test_texcoordindex", test_texcoordindex },
    { "test_vertex_blending", test_vertex_blending },
    { "test_updatetexture", test_updatetexture },
    { "test_depthbias", test_depthbias },
    { "test_flip", test_flip },
    { "test_uninitialized_varyings", test_uninitialized_varyings },
    { "test_multisample_init", test_multisample_init },
    { "test_depth_stencil_init", test_depth_stencil_init },
    { "test_texture_blending", test_texture_blending },
    { "test_color_clamping", test_color_clamping },
    { "test_line_antialiasing_blending", test_line_antialiasing_blending },
    { "test_dsy", test_dsy },
    { "test_evict_bound_resources", test_evict_bound_resources },
    { "test_max_index16", test_max_index16 },
    { "test_backbuffer_resize", test_backbuffer_resize },
    { "test_drawindexedprimitiveup", test_drawindexedprimitiveup },
    { "test_vertex_texture", test_vertex_texture },
    { "test_mvp_software_vertex_shaders", test_mvp_software_vertex_shaders },
    { "test_null_format", test_null_format },
    { "test_color_vertex", test_color_vertex },
    { "test_sysmem_draw", test_sysmem_draw },
    { "test_nrm_instruction", test_nrm_instruction },
    { "test_mismatched_sample_types", test_mismatched_sample_types },
    { "test_draw_mapped_buffer", test_draw_mapped_buffer },
    { "test_alpha_to_coverage", test_alpha_to_coverage },
    { "test_sample_mask", test_sample_mask }
};


int main(int argc, char *argv[]) {
#ifndef _WIN32
    if (!Xnine_init(-1, &priv))
      return 1;
#endif

    for (unsigned i = 0; i < sizeof(w_test_map) / sizeof(w_test_map[0]); i++) {
      if ((argc == 1) || !strcmp(argv[1], w_test_map[i].name)) {
        w_test_map[i].func();
      }
    }

#ifndef _WIN32
    Xnine_close(priv);
#endif
    return 0;
}
